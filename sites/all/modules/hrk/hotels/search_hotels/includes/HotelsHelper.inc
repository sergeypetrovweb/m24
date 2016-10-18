<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 12.10.14
 * Time: 15:37
 */

namespace includes;


class HotelsHelper
{

    private $test;

    public static function create()
    {
        return new HotelsHelper();
    }

    public function compress_request_param($params)
    {
        $compressed = array();

        if (!empty($params['location_id'])) {
            $compressed['l'] = $params['location_id'];
        }

        if (!empty($params['check_in']) || !empty($params['check_out'])) {
            $compressed['d'] = date('ymd', strtotime($params['check_in'])) . '-' . date('ymd', strtotime($params['check_out']));
        }
        if (!empty($params['rooms']) && is_array($params['rooms'])) {
            $compressed['r'] = '';
            foreach ($params['rooms'] as $room) {
                $compressed['r'] .= $room['adt'] . $room['chd'] . $room['age'];
            }
        }

        if (!empty($params['nationality'])) {
            $compressed['n'] = $params['nationality'];
        }

        if (!empty($params['rating'])) {
            $compressed['rt'] = $params['rating'];
        }

        return $compressed;
    }

    public function uncompress_request_param($compressed_params)
    {
        $params = array();

        if (!empty($compressed_params['l'])) {
            $params['location_id'] = $compressed_params['l'];
        }

        if (!empty($compressed_params['d'])) {
            $dates = explode('-', $compressed_params['d']);
            $params['check_in'] = date('Y-m-d', strtotime(implode('-', str_split($dates[0], 2))));
            $params['check_out'] = date('Y-m-d', strtotime(implode('-', str_split($dates[1], 2))));
        }

        if (!empty($compressed_params['r'])) {
            $rooms = str_split($compressed_params['r'], 3);

            foreach ($rooms as $room) {
                $params['rooms'][] = array(
                    'adt' => $room[0],
                    'chd' => $room[1],
                    'age' => $room[2],
                );
            }
        }

        if (!empty($compressed_params['n'])) {
            $params['nationality'] = $compressed_params['n'];
        }

        $params['rating'] = !empty($compressed_params['rt']) ? $compressed_params['rt'] : 0;

        return $params;
    }

    public function validate_request_param($params, $default = false)
    {
        $validated_params = array();

        //validate location_id
        if (empty($params['location_id'])) return $default;

        $query = db_select('hrk_sh_cities', 'ct');
        $query->leftJoin('hrk_sh_countries', 'c', 'c.cid = ct.cid');
        $query->fields('ct', array('lid', 'latitude', 'longitude'));
        $query->fields('c', array('code'));
        $query->condition('lid', $params['location_id']);

        $result = $query->execute()->fetchAssoc();

        if (!$result) return $default;

        $validated_params['location_id'] = $result['lid'];
        $validated_params['latitude'] = $result['latitude'];
        $validated_params['longitude'] = $result['longitude'];
        $validated_params['country'] = $result['code'];

        //validate dates
        if (empty($params['check_in']) && !self::validate_date($params['check_in'], 'Y-m-d') && $params['check_in'] < strtotime('+365 days')) return $default;
        if (empty($params['check_out']) && !self::validate_date($params['check_out'], 'Y-m-d') && $params['check_out'] < strtotime('+365 days')) return $default;

        if (strtotime($params['check_in']) > strtotime($params['check_out'])) return $default;

        $validated_params['check_in'] = $params['check_in'];
        $validated_params['check_out'] = $params['check_out'];


        //validate rooms
        if (empty($params['rooms']) || !is_array($params['rooms'])) return $default;

        foreach ($params['rooms'] as $index => $room) {
            if (empty($room['adt']) || $room['adt'] > 4 || $room['chd'] > 2 || $room['age'] > 12 || $room['age'] < 0) {
                return $default;
            }
            $validated_params['rooms'][$index] = array(
                'adt' => $room['adt'],
                'chd' => $room['chd'],
                'age' => $room['age']
            );
        }

        //validate nationality
        if (empty($params['nationality'])) return $default;

        $result = db_select('hrk_sh_countries', 'c')
            ->fields('c', array())
            ->condition('cid', $params['nationality'])
            ->execute()
            ->fetchAssoc(); //check nationality

        if (!$result) return $default;

        $validated_params['nationality'] = $params['nationality'];


        //validate rating
        if (empty($params['rating'])) {
            $validated_params['rating'] = 0;
        } else {
            $validated_params['rating'] = intval($params['rating']);
        }

        return $validated_params;
    }

    public function make_results_page_link($params)
    {
        $compressed = $this->compress_request_param($params);
        $rating = ($compressed['rt']) ? '-' . $compressed['rt'] : '';
        return 'hotels/results/' . $compressed['l'] . '/' . $compressed['d'] . '/' . $compressed['r'] . '/' . $compressed['n'] . $rating;
    }

    public function get_results_params_from_results_page_link($link, $full = FALSE)
    {
        $url_pieces = explode('/', $link);

        if (empty($url_pieces[2]) && empty($url_pieces[3]) && empty($url_pieces[4])) return FALSE;

        $params = array('l' => $url_pieces[2], 'd' => $url_pieces[3], 'r' => $url_pieces[4]);

        return ($full) ? hrk_sh_uncompress_request_param($params) : $params;
    }

    static function validate_date($date, $format = 'Y-m-d H:i:s')
    {
        $d = \DateTime::createFromFormat($format, $date);
        return $d && $d->format($format) == $date;
    }

    public function makeArrayFromSearchResponse(\SimpleXMLElement $xml)
    {
        $result = array();

        //check if response is SearchFlightResponse
        if ($xml->sBody->ServiceRequestResponse) {
            $response = &$xml->sBody->ServiceRequestResponse->ServiceRequestResult;

            /*CHECK IF WE HAVE ERRORS*/
            if (get_object_vars($response->Errors)) {
                $result['error'] = array(
                    'code' => self::xml_value($response->Errors->Error, 'ErrorCode'),
                    'text' => self::xml_value($response->Errors->Error, 'ErrorText')
                );

                return $result;
            }

            $service_request_result_xml = simplexml_load_string($response->asXML());
            $hotels = $service_request_result_xml->xpath('//Hotel');

            /*RETURN ERROR NO RESULTS FOUND.*/
            if (!$hotels) {
                $result['error'] = array(
                    'code' => 'I0404',
                    'text' => 'No results found.'
                );

                return $result;
            }

            /* GET HOTELS*/
            foreach ($hotels as $hotel) {
                /** @var  $hotel \SimpleXMLElement */
                $hotel_ID = self::xml_value($hotel, 'ID');
                $result['hotels'][$hotel_ID] = array();
                $tmp_hotel = &$result['hotels'][$hotel_ID];

                $tmp_hotel = array(
                    'id' => $hotel_ID,
                    'address' => self::xml_value($hotel, 'Address'),
                    'area' => self::xml_value($hotel, 'Area'),
                    'img_src' => trim(self::xml_value($hotel->DefaultImage, 'FullSize')),
                    'name' => self::xml_value($hotel, 'DisplayName'),
                    'district' => self::xml_value($hotel, 'District'),
                    'location' => array(
                        'latitude' => self::xml_value($hotel->GeoLocation, 'Latitude'),
                        'longitude' => self::xml_value($hotel->GeoLocation, 'Longitude'),
                    ),
                    'rating' => self::xml_value($hotel, 'StarRating')
                );

                if (!empty($hotel->TripAdvisor)) {
                    $tmp_hotel['trip_adv'] = array(
                        'rating' => self::xml_value($hotel->TripAdvisor, 'Rating'),
                        'img_src' => trim(self::xml_value($hotel->TripAdvisor, 'RatingImageUrl')),
                        'reviews' => trim(self::xml_value($hotel->TripAdvisor, 'ReviewsCount')),
                    );
                }

                /*GET PACKAGES*/
                $hotel_xml = simplexml_load_string($hotel->asXML());
                $packages = $hotel_xml->xpath('//RoomsPackage');

                foreach ($packages as $package) {
                    /** @var  $package \SimpleXMLElement */
                    $package_ID = self::xml_value($package, 'PackageId');
                    $tmp_hotel['packages'][$package_ID] = array();
                    $tmp_package = &$tmp_hotel['packages'][$package_ID];

                    $package_price = self::xml_value($package, 'SimplePrice');
                    if (empty($tmp_hotel['lower_price'])) $tmp_hotel['lower_price'] = $package_price;

                    if ($tmp_hotel['lower_price'] > $package_price) $tmp_hotel['lower_price'] = $package_price;

                    $tmp_package = array(
                        'id' => $package_ID,
                        'refund' => self::xml_value($package, 'Refundability'),
                        'price' => $package_price,
                        'supplier_name' => self::xml_value($package, 'SupplierName'),
                    );
                    /*GET ROOMS*/
                    $package_xml = simplexml_load_string($package->asXML());
                    $rooms = $package_xml->xpath('//Room');

                    foreach ($rooms as $room) {
                        /** @var  $room \SimpleXMLElement */
                        $room_ID = self::xml_value($room, 'Id');
                        $tmp_package['rooms'][$room_ID] = array();
                        $tmp_room = &$tmp_package['rooms'][$room_ID];

                        $tmp_room = array(
                            'id' => $room_ID,
                            'adt' => self::xml_value($room, 'AdultsCount'),
                            'availability' => self::xml_value($room, 'Availability'),
                            'description' => $this->_getDescription($room->Description),
                        );

                        $room_xml = simplexml_load_string($room->asXML());
                        $kids = $room_xml->xpath('//KidsAges');

                        $tmp_room['kids'] = (self::xml_value($room, 'KidsAges')) ? count($kids) : 0;

                        $tmp_room['basis'] = self::xml_value($room, 'RoomBasis');
                        $tmp_room['class'] = self::xml_value($room, 'RoomClass');
                        $tmp_room['type'] = self::xml_value($room, 'RoomType');
                    }
                }
            }
        } else {
            $error = 'Response empty or not SearchFlightResponse';
            throw new \Exception($error);
        }
        return $result;
    }

    public function getPackagesFromHotelDetailsResponse(\SimpleXMLElement $xml)
    {
        $result = array();

        //check if response is SearchFlightResponse
        if ($xml->sBody->ServiceRequestResponse) {
            $response = &$xml->sBody->ServiceRequestResponse->ServiceRequestResult;

            /*CHECK IF WE HAVE ERRORS*/
            if (get_object_vars($response->Errors)) {
                $result['error'] = array(
                    'code' => self::xml_value($response->Errors->Error, 'ErrorCode'),
                    'text' => self::xml_value($response->Errors->Error, 'ErrorText')
                );

                return $result;
            }

            $service_request_result_xml = simplexml_load_string($response->asXML());
            $hotels = $service_request_result_xml->xpath('//Hotel');

            /*RETURN ERROR NO RESULTS FOUND.*/
            if (!$hotels) {
                $result['error'] = array(
                    'code' => 'E4301',
                    'text' => 'No matching item found.'
                );

                return $result;
            }

            $hotel = reset($hotels);

            /*GET PACKAGES*/
            $hotel_xml = simplexml_load_string($hotel->asXML());
            $packages = $hotel_xml->xpath('//RoomsPackage');

            foreach ($packages as $package) {
                /** @var  $package \SimpleXMLElement */
                $package_ID = self::xml_value($package, 'PackageId');

                $result['packages'][$package_ID] = array();
                $tmp_package = &$result['packages'][$package_ID];

                $tmp_package = array(
                    'id' => $package_ID,
                    'hotel_id' => self::xml_value($package, 'HotelId'),
                    'contract_id' => self::xml_value($package, 'ContractId'),
                    'refund' => self::xml_value($package, 'Refundability'),
                    'price' => self::xml_value($package, 'SimplePrice'),
                    'supplier_id' => self::xml_value($package, 'SupplierId'),
                    'supplier_name' => self::xml_value($package, 'SupplierName'),
                );

                /*GET PACKAGES PRICE*/
                $package_xml = simplexml_load_string($package->asXML());
                $package_price = $package_xml->xpath('//PackagePrice');
                $package_price = (is_array($package_price)) ? reset($package_price) : array();

                if ($package_price) {
                    $tmp_package['package_price'] = array(
                        'currency' => self::xml_value($package_price, 'Currency'),
                        'final_price' => self::xml_value($package_price, 'FinalPrice'),
                        'final_price_in_currency' => self::xml_value($package_price, 'FinalPriceInSupplierCurrency'),
                        'original_price' => self::xml_value($package_price, 'OriginalPrice'),
                        'original_price_in_currency' => self::xml_value($package_price, 'OriginalPriceInSupplierCurrency'),
                        'supplier_currency' => self::xml_value($package_price, 'SupplierCurrency'),
                    );
                }

                /*GET ROOMS*/
                $package_xml = simplexml_load_string($package->asXML());
                $rooms = $package_xml->xpath('//Room');

                foreach ($rooms as $room) {
                    /** @var  $room \SimpleXMLElement */
                    $room_ID = self::xml_value($room, 'Id');
                    $tmp_package['rooms'][$room_ID] = array();
                    $tmp_room = &$tmp_package['rooms'][$room_ID];

                    $tmp_room = array(
                        'id' => $room_ID,
                        'adt' => self::xml_value($room, 'AdultsCount'),
                        'availability' => self::xml_value($room, 'Availability'),
                        'description' => $this->_getDescription($room->Description),
                    );

                    $kids_xml = simplexml_load_string($room->KidsAges->asXML());
                    $kids = $kids_xml->xpath('//aint');

                    $tmp_room['kids'] = count($kids);

                    $tmp_room['basis'] = self::xml_value($room, 'RoomBasis');
                    $tmp_room['basis_original'] = self::xml_value($room, 'RoomBasisOriginal');
                    $tmp_room['class'] = self::xml_value($room, 'RoomClass');
                    $tmp_room['class_original'] = self::xml_value($room, 'RoomClassOriginal');
                    $tmp_room['type'] = self::xml_value($room, 'RoomType');
                    $tmp_room['type_original'] = self::xml_value($room, 'RoomTypeOriginal');
                }
            }
        } else {
            $error = 'Response empty or not SearchFlightResponse';
            throw new \Exception($error);
        }
        return $result;
    }

    public function getHotelInfoFromHotelDetailsResponse(\SimpleXMLElement $xml)
    {
        $result = array();

        //check if response is SearchFlightResponse
        if ($xml->sBody->ServiceRequestResponse) {
            $response = &$xml->sBody->ServiceRequestResponse->ServiceRequestResult;

            /*CHECK IF WE HAVE ERRORS*/
            if (get_object_vars($response->Errors)) {
                $result['error'] = array(
                    'code' => self::xml_value($response->Errors->Error, 'ErrorCode'),
                    'text' => self::xml_value($response->Errors->Error, 'ErrorText')
                );

                return $result;
            }

            $service_request_result_xml = simplexml_load_string($response->asXML());
            $hotel_supplier_details = $service_request_result_xml->xpath('//HotelSupplierDetails');
            $hotel_supplier_detail = reset($hotel_supplier_details);

            /*RETURN ERROR NO RESULTS FOUND.*/
            if (!$hotel_supplier_details) {
                $result['error'] = array(
                    'code' => 'E4301',
                    'text' => 'No matching item found.'
                );

                return $result;
            }

            /*GET GENERAL DETAILS*/
            $result = array(
                'description' => $this->_getDescription($hotel_supplier_detail->Description),
                'address' => self::xml_value($hotel_supplier_detail->GeneralDetails, 'Address', ''),
                'name' => self::xml_value($hotel_supplier_detail->GeneralDetails, 'DisplayName', ''),
                'rating' => self::xml_value($hotel_supplier_detail->GeneralDetails, 'StarRating', 0),
                'latitude' => self::xml_value($hotel_supplier_detail, 'Latitude', 0),
                'longitude' => self::xml_value($hotel_supplier_detail, 'Longitude', 0),
            );

            if (!empty($hotel_supplier_detail->GeneralDetails->TripAdvisor)) {
                $result['trip_adv'] = array(
                    'rating' => self::xml_value($hotel_supplier_detail->GeneralDetails->TripAdvisor, 'Rating'),
                    'img_src' => trim(self::xml_value($hotel_supplier_detail->GeneralDetails->TripAdvisor, 'RatingImageUrl')),
                    'reviews' => trim(self::xml_value($hotel_supplier_detail->GeneralDetails->TripAdvisor, 'ReviewsCount')),
                );
            }

            /*GET FACILITIES*/
            $facilities_xml = simplexml_load_string($hotel_supplier_detail->HotelFacilities->asXML());
            $facilities = $facilities_xml->xpath('//astring');

            if ($facilities) {
                foreach ($facilities as $index => $facility) {
                    $result['facilities'][$index] = self::xml_value($facility, 0, '');
                }
            }

            /*GET PICTURES*/
            $pictures_xml = simplexml_load_string($hotel_supplier_detail->Pictures->asXML());
            $pictures = $pictures_xml->xpath('//Picture');

            if ($pictures) {
                foreach ($pictures as $index => $picture) {
                    $result['images'][$index] = array(
                        'src' => trim(self::xml_value($picture, 'FullSize', '')),
                        'description' => $this->_getDescription($picture->PicDescription),
                        'thumb_src' => trim(self::xml_value($picture, 'Thumb', '')),
                    );
                }
            }
        } else {
            $error = 'Response empty or not SearchFlightResponse';
            throw new \Exception($error);
        }
        return $result;
    }

    static public function xml_attr(\SimpleXMLElement $object, $attribute, $default = FALSE)
    {
        if (isset($object[$attribute])) $default = (string)$object[$attribute];
        return $default;
    }

    static public function xml_value(\SimpleXMLElement $object, $name, $default = FALSE)
    {
        if (isset($object->$name)) $default = (string)$object->$name->__toString();
        return $default;
    }

    private function _getDescription(\SimpleXMLElement $object)
    {
        $description = array();
        if ($object) {
            $description_xml = simplexml_load_string($object->asXML());
            $descriptions_arr = $description_xml->xpath('//astring');

            foreach ($descriptions_arr as $index => $desc) {
                $description[$index] = self::xml_value($desc, 0, '');
            }

        }

        return $description;
    }
} 