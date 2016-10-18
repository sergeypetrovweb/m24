<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 27.09.14
 * Time: 0:35
 */

namespace includes;


class BookingParse
{
    private $_xml = null;


    public function  __construct(\SimpleXMLElement $xml)
    {
        $this->_xml = $xml;
    }

    public function flightRules()
    {
        $result = array();
        if ($this->_xml && $this->_xml->soapBody->GetFlightRulesResponse) {
            $response = & $this->_xml->soapBody->GetFlightRulesResponse->OTA_AirRulesRS;

            $response_xml = simplexml_load_string($response->asXml());
            $errors = $response_xml->xpath('//Errors');

            /*CHECK ERRORS*/
            if ($errors && is_array($errors)) {
                foreach ($errors as $error) {
                    $result['errors'][] = array(
                        'type' => $this->xml_attr($error->Error, 'Type'),
                        'text' => $this->xml_attr($error->Error, 'ShortText'),
                        'code' => $this->xml_attr($error->Error, 'Code'),
                    );
                }
                return $result;
            }

            /*GET PENALTIES*/
            $fare_rules = $response_xml->xpath('//FareRules');

            if ($fare_rules && is_array($fare_rules)) {
                foreach ($fare_rules as $fare_rule) {
                    if ($fare_rule) {
                        $fare_rule_xml = simplexml_load_string($fare_rule->asXml());
                        $sub_sections = $fare_rule_xml->xpath('//SubSection');

                        if ($sub_sections && is_array($sub_sections)) {
                            foreach ($sub_sections as $sub_section) {
                                if ($this->xml_attr($sub_section, 'SubCode') == 'PE') {
                                    $sub_section_xml = simplexml_load_string($sub_section->asXMl());

                                    $paragraphs = $sub_section_xml->xpath('//Paragraph');
                                    if ($paragraphs && is_array($paragraphs)) {
                                        foreach ($paragraphs as $paragraph) {
                                            $paragraph_xml = simplexml_load_string($paragraph->asXMl());
                                            $texts = $paragraph_xml->xpath('//Text');

                                            if ($texts && is_array($texts)) {
                                                $result['penalties'] = array();
                                                foreach ($texts as $text) {

                                                    if (str_word_count($text[0]) <= 2) {
                                                        $result['penalties'][] = array('type' => 'title', 'text' => $text[0]->__toString());
                                                        continue;
                                                    }

                                                    $result['penalties'][] = array('type' => 'description', 'text' => $text[0]->__toString());
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            $error = 'Response empty or not GetFlightRulesResponse';
            throw new \Exception($error);
        }
        return $result;
    }

    public function booking()
    {
        $result = array();

        if ($this->_xml && $this->_xml->soapBody->BookFlightResponse) {
            $response = & $this->_xml->soapBody->BookFlightResponse->OTA_AirBookRS;

            $response_xml = simplexml_load_string($response->asXml());
            $errors = $response_xml->xpath('//Errors');

            if ($errors && is_array($errors)) {
                foreach ($errors as $error) {
                    $step = $this->xml_attr($error->Error, 'NodeList');
                    switch ($step) {
                        case 'BOOK_WITH_PRICECHARGE':
                            $result['change_request'] = array(
                                'type' => 'BOOK_WITH_PRICECHARGE',
                                'reference_number' => self::xml_attr($response, 'ReferenceNumber')
                            );
                            return $result;
                            break;
                        case 'BOOK_WITH_PRICECHANGE':
                            $total_fare = $response->NewPrice->ItinTotalFare->TotalFare;

                            currency_include('convert');

                            $currency = self::xml_attr($total_fare, 'Currency');
                            $total_fare = self::xml_attr($total_fare, 'Amount');

                            $new_price['currency'] = $currency;
                            $new_price['fare']['AZN'] = currency_convert($total_fare, $currency, 'AZN');
                            $new_price['fare']['EUR'] = currency_convert($total_fare, $currency, 'EUR');
                            $new_price['fare']['USD'] = currency_convert($total_fare, $currency, 'USD');
                            $new_price['fare']['RUB'] = currency_convert($total_fare, $currency, 'RUB');

                            $result['change_request'] = array(
                                'type' => 'BOOK_WITH_PRICECHANGE',
                                'reference_number' => self::xml_attr($response, 'ReferenceNumber'),
                                'new_price' => $new_price
                            );
                            break;
                        case 'BOOK_WITH_CARDVERIFICATION':
                            $result['change_request'] = array(
                                'type' => 'BOOK_WITH_CARDVERIFICATION',
                                'reference_number' => self::xml_attr($response, 'ReferenceNumber'),
                                'url' => $this->xml_attr($error->Error, 'DocURL'),
                            );
                            return $result;
                            break;
                        default:
                            $result['errors'][] = array(
                                'type' => $this->xml_attr($error->Error, 'Type'),
                                'text' => $this->xml_attr($error->Error, 'ShortText'),
                                'code' => $this->xml_attr($error->Error, 'Code'),
                                'node_list' => $this->xml_attr($error->Error, 'NodeList'),
                            );
                            return $result;
                            break;
                    }
                }
            }

            /*GET CONTEXT ID INFO*/
            $books = $response_xml->xpath('//BookingReferenceID');

            if (!$books) return $result;

            foreach ($books as $book) {
                $result['context_id'][] = self::xml_attr($book, 'ID_Context');
            }

            /*GET FLIGHTS INFO*/
            $destinations = $response_xml->xpath('//OriginDestinationOption');

            if ($destinations && is_array($destinations)) {
                foreach ($destinations as $index => $destination) {

                    $ref_num = self::xml_attr($destination, 'RefNumber');
                    $dir_id = self::xml_attr($destination, 'DirectionId');
                    $elapsed_time_piece = str_split(self::xml_attr($destination, 'ElapsedTime', ''), 2);
                    $elapsed_time = 3600 * intval($elapsed_time_piece[0]) + 60 * intval($elapsed_time_piece[1]);

                    $flight_xml = simplexml_load_string($destination->asXml());
                    $flights = $flight_xml->xpath('//FlightSegment');
                    unset($flight_xml);

                    foreach ($flights as $key => $flight) {
                        $tmp_flight = (object)array();

                        $tmp_flight->ref_number = $ref_num;
                        $tmp_flight->direction_id = $dir_id;
                        $tmp_flight->elapsed_time = $elapsed_time;
                        $tmp_flight->departure = strtotime(self::xml_attr($flight, 'DepartureDateTime'));
                        $tmp_flight->arrival = strtotime(self::xml_attr($flight, 'ArrivalDateTime'));
                        $tmp_flight->flight_number = self::xml_attr($flight, 'FlightNumber');
                        $tmp_flight->design_code = self::xml_attr($flight, 'ResBookDesigCode');
                        $tmp_flight->departure_airport = self::xml_attr($flight->DepartureAirport, 'LocationCode');
                        $tmp_flight->arrival_airport = self::xml_attr($flight->ArrivalAirport, 'LocationCode');
                        $tmp_flight->operating_airline = self::xml_attr($flight->OperatingAirline, 'Code');
                        $tmp_flight->equipment = self::xml_attr($flight->Equipment, 'AirEquipType');
                        $tmp_flight->marketing_airline = self::xml_attr($flight->MarketingAirline, 'Code');
                        $tmp_flight->design_quantity = self::xml_attr($flight->BookingClassAvails->BookingClassAvail, 'ResBookDesigQuantity');
                        $tmp_flight->design_cabin_code = self::xml_attr($flight->BookingClassAvails->BookingClassAvail, 'ResBookDesigCabinCode');
                        $tmp_flight->fare_basis = self::xml_attr($flight->BookingClassAvails->BookingClassAvail, 'FareBasis');


                        //save the country codes, airports, airlines
                        //then we make a couple of queries to the database to find out their names
                        hrk_sf_codes()->delayCodes('airports', array($tmp_flight->departure_airport, $tmp_flight->arrival_airport));
                        hrk_sf_codes()->delayCodes('airlines', array($tmp_flight->operating_airline, $tmp_flight->marketing_airline));
                        hrk_sf_codes()->delayCode('airplanes', $tmp_flight->equipment);

                        $result['codes']['airports'][$tmp_flight->departure_airport] = null;
                        $result['codes']['airports'][$tmp_flight->arrival_airport] = null;
                        $result['codes']['airlines'][$tmp_flight->operating_airline] = null;
                        $result['codes']['airlines'][$tmp_flight->marketing_airline] = null;
                        $result['codes']['airplanes'][$tmp_flight->equipment] = null;

                        //save $tmp_result to $results['flights']
                        $result['flights'][$ref_num][$dir_id][$key] = (array)$tmp_flight;
                    }

                }
            }

            /*GET PRICE INFO*/
            $price_info_array = $response_xml->xpath('//PriceInfo');
            $price_info = reset($price_info_array);

            if ($price_info) {
                currency_include('convert');

                $currency = self::xml_attr($price_info->ItinTotalFare->TotalFare, 'Currency');
                $service_fee_amount = self::xml_attr($price_info->ServiceFees->ServiceFee, 'Amount');
                $total_fare = self::xml_attr($price_info->ItinTotalFare->TotalFare, 'Amount');

                $result['price']['currency'] = $currency;
                $result['price']['fare']['AZN'] = currency_convert($total_fare, $currency, 'AZN');
                $result['price']['fare']['EUR'] = currency_convert($total_fare, $currency, 'EUR');
                $result['price']['fare']['USD'] = currency_convert($total_fare, $currency, 'USD');
                $result['price']['fare']['RUB'] = currency_convert($total_fare, $currency, 'RUB');

                $result['price']['commission']['AZN'] = currency_convert($service_fee_amount, $currency, 'AZN');
                $result['price']['commission']['EUR'] = currency_convert($service_fee_amount, $currency, 'EUR');
                $result['price']['commission']['USD'] = currency_convert($service_fee_amount, $currency, 'USD');
                $result['price']['commission']['RUB'] = currency_convert($service_fee_amount, $currency, 'RUB');
            }


            /*GET PASSENGERS INFO*/
            $travelers = $response_xml->xpath('//AirTraveler');

            if ($travelers && is_array($travelers)) {
                foreach ($travelers as $traveler) {
                    $type = self::xml_attr($traveler, 'PassengerTypeCode');
                    $traveler_xml = simplexml_load_string($traveler->asXml());
                    $documents = $traveler_xml->xpath('//Document');
                    $document = reset($documents);
                    if ($type != 'INF') {
                        $result['passenger'][$type][] = array(
                          'sex' => $traveler->PersonName->NamePrefix->__toString(),
                          'first_name' => $traveler->PersonName->GivenName->__toString(),
                          'last_name' => $traveler->PersonName->Surname->__toString(),
                          'phone' => array(
                            'type' => self::xml_attr($traveler->Telephone, 'PhoneType'),
                            'number' => self::xml_attr($traveler->Telephone, 'LocationCode'),
                          ),
                          'email' => $traveler->Email->__toString(),
                          'birthday' => $traveler->BirthDate->__toString(),
                          'document' => array(
                            'id' => self::xml_attr($document, 'DocID'),
                            'type' => self::xml_attr($document, 'DocType'),
                            'doc_type' => self::xml_attr($document, 'InnerDocType'),
                            'expire' => self::xml_attr($document, 'ExpireDate'),
                            'country' => self::xml_attr($document, 'DocIssueCountry'),
                          )
                        );
                    } else {
                        $result['passenger'][$type][] = array(
                          'sex' => $traveler->PersonName->NamePrefix->__toString(),
                          'first_name' => $traveler->PersonName->GivenName->__toString(),
                          'last_name' => $traveler->PersonName->Surname->__toString(),
                          'phone' => array(
                            'type' => 'Home',
                            'number' => 'no data',
                          ),
                          'email' => 'no data',
                          'birthday' => $traveler->BirthDate->__toString(),
                          'document' => array(
                            'id' => '000000',
                            'type' => 'Passport',
                            'doc_type' => 'DOCS',
                            'expire' => '2018-05-31',
                            'country' => 'CA',
                          )
                        );
                    }
                }
            }

            /*GET TICKETING LIMITS INFO*/
            $ticketing_limits = $response_xml->xpath('//Ticketing');
            $ticketing_limit = reset($ticketing_limits);

            if ($ticketing_limit) {
                $result['ticket_limit'] = array(
                    'limit' => self::xml_attr($ticketing_limit, 'TicketTimeLimit'),
                    'type' => self::xml_attr($ticketing_limit, 'TicketType'),
                );
            }

            /*GET RULES*/
            $rules = $response_xml->xpath('//FareRules');

            if ($rules && is_array($rules)) {
                foreach ($rules as $rule) {
                    $rule_xml = simplexml_load_string($rule->asXml());
                    $sections = $rule_xml->xpath('//SubSection');
                    if ($sections && is_array($sections)) {
                        foreach ($sections as $section) {

                            if (self::xml_attr($section, 'SubCode') == 'PE') {

                                $section_xml = simplexml_load_string($section->asXMl());
                                $paragraphs = $section_xml->xpath('//Paragraph');

                                if ($paragraphs && is_array($paragraphs)) {
                                    foreach ($paragraphs as $paragraph) {
                                        $paragraph_xml = simplexml_load_string($paragraph->asXMl());
                                        $texts = $paragraph_xml->xpath('//Text');

                                        if ($texts && is_array($texts)) {
                                            $result['penalties'] = array();
                                            foreach ($texts as $text) {

                                                if (str_word_count($text[0]) <= 2) {
                                                    $result['penalties'][] = array('type' => 'title', 'text' => $text[0]->__toString());
                                                    continue;
                                                }

                                                $result['penalties'][] = array('type' => 'description', 'text' => $text[0]->__toString());
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            /*GET CODES*/

            //get codes from db
            if (!empty($result['codes'])) {
                hrk_sf_codes()->delayStart();
                foreach ($result['codes'] as $type => $code) {
                    foreach ($code as $cd => $value) {
                        $codes = hrk_sf_codes()->getCode($type, $cd);
                        $result['codes'][$type][$cd] = reset($codes);
                    }
                }
            }
        } else {
            $error = 'Response empty or not BookFlightResponse';
            throw new \Exception($error);
        }

        return $result;
    }

    public function lcc()
    {
        $result = array();
        $response = & $this->_xml->soapBody->GetRequiredParametersForLCCResponse->RequiredParametersRS;
        $response_xml = simplexml_load_string($response->asXml());


        /*GET REQUIRED PARAMS*/
        $req_params = $response_xml->xpath('//LCCRequiredParameter');

        if ($req_params && is_array($req_params)) {
            foreach ($req_params as $param) {
                if ($param->Mandatory->__toString() === 'true') {
                    if ($param->PerPassenger->__toString() === 'true') {
                        $result['per_passenger'][$param->Info->__toString()] = $param->Info->__toString();
                    } else {
                        $result['lcc'] [$param->Info->__toString()] = $param->Info->__toString();
                    }
                }
            }
        }

        /*GET SUPPORTED CARD*/
        $supported_cards = $response_xml->xpath('//LCCSupportedCard');

        if ($supported_cards && is_array($supported_cards)) {
            foreach ($supported_cards as $supported_card) {
                $result['card'][self::xml_attr($supported_card, 'Code')] = array(
                    'code' => self::xml_attr($supported_card, 'Code'),
                    'amount' => self::xml_attr($supported_card, 'Amount'),
                    'currency' => self::xml_attr($supported_card, 'Currency'),
                );
            }

        }

        /*GET BAGS INFO*/
        $bags = $response_xml->xpath('//LCCBaggageFee');

        if ($bags && is_array($bags)) {
            currency_include('convert');
            foreach ($bags as $bag) {
                $currency = self::xml_attr($bag, 'Currency');
                $amount = self::xml_attr($bag, 'Amount');
                $result['bags'][] = array(
                    'price' => array(
                        'AZN' => currency_convert($amount, 'AZN', $currency),
                        'USD' => currency_convert($amount, 'USD', $currency),
                        'EUR' => currency_convert($amount, 'EUR', $currency),
                        'RUB' => currency_convert($amount, 'EUR', $currency),
                    ),
                    'weight' => self::xml_attr($bag, 'Weight'),
                    'max_weight' => self::xml_attr($bag, 'MaxWeight'),
                    'quantity' => self::xml_attr($bag, 'Quantity'),
                );
            }

        }

        /*GET RULE LING*/
        $links = $response_xml->xpath('//LCCRuleLink');
        $supplier_names = $response_xml->xpath('//SupplierName');

        if ($links && $supplier_names) {
            $path = reset($links);
            $title = reset($supplier_names);
            $result['rule_link'] = array(
                'path' => $path->__toString(),
                'title' => $title->__toString(),
            );
        }

        return $result;
    }

    public function create_ticket()
    {
        $result = array();

        if ($this->_xml && $this->_xml->soapBody->CreateTicketResponse) {
            $response = & $this->_xml->soapBody->CreateTicketResponse->OTA_AirBookRS;

            $response_xml = simplexml_load_string($response->asXml());
            $errors = $response_xml->xpath('//Errors');

            if ($errors && is_array($errors)) {
                foreach ($errors as $error) {
                    $step = $this->xml_attr($error->Error, 'NodeList');
                    switch ($step) {
                        case 'BOOK_WITH_PRICECHARGE':
                            $result['change_request'] = array(
                                'type' => 'BOOK_WITH_PRICECHARGE',
                                'reference_number' => self::xml_attr($response, 'ReferenceNumber')
                            );
                            return $result;
                            break;
                        case 'BOOK_WITH_PRICECHANGE':
                            $total_fare = $response->NewPrice->ItinTotalFare->TotalFare;

                            currency_include('convert');

                            $currency = self::xml_attr($total_fare, 'Currency');
                            $total_fare = self::xml_attr($total_fare, 'Amount');

                            $new_price['currency'] = $currency;
                            $new_price['fare']['AZN'] = currency_convert($total_fare, $currency, 'AZN');
                            $new_price['fare']['EUR'] = currency_convert($total_fare, $currency, 'EUR');
                            $new_price['fare']['USD'] = currency_convert($total_fare, $currency, 'USD');
                            $new_price['fare']['RUB'] = currency_convert($total_fare, $currency, 'RUB');

                            $result['change_request'] = array(
                                'type' => 'BOOK_WITH_PRICECHANGE',
                                'reference_number' => self::xml_attr($response, 'ReferenceNumber'),
                                'new_price' => $new_price
                            );
                            break;
                        case 'BOOK_WITH_CARDVERIFICATION':
                            $result['change_request'] = array(
                                'type' => 'BOOK_WITH_CARDVERIFICATION',
                                'reference_number' => self::xml_attr($response, 'ReferenceNumber'),
                                'url' => $this->xml_attr($error->Error, 'DocURL'),
                            );
                            return $result;
                            break;
                        default:
                            $result['errors'][] = array(
                                'type' => $this->xml_attr($error->Error, 'Type'),
                                'text' => $this->xml_attr($error->Error, 'ShortText'),
                                'code' => $this->xml_attr($error->Error, 'Code'),
                                'node_list' => $this->xml_attr($error->Error, 'NodeList'),
                            );
                            return $result;
                            break;
                    }
                }
            }

            /*GET CONTEXT ID INFO*/
            $books = $response_xml->xpath('//BookingReferenceID');

            if (!$books) return $result;

            foreach ($books as $book) {
                $result['context_id'][] = self::xml_attr($book, 'ID_Context');
            }

            /*GET FLIGHTS INFO*/
            $destinations = $response_xml->xpath('//OriginDestinationOption');

            if ($destinations && is_array($destinations)) {
                foreach ($destinations as $index => $destination) {

                    $ref_num = self::xml_attr($destination, 'RefNumber');
                    $dir_id = self::xml_attr($destination, 'DirectionId');
                    $elapsed_time_piece = str_split(self::xml_attr($destination, 'ElapsedTime', ''), 2);
                    $elapsed_time = 3600 * intval($elapsed_time_piece[0]) + 60 * intval($elapsed_time_piece[1]);

                    $flight_xml = simplexml_load_string($destination->asXml());
                    $flights = $flight_xml->xpath('//FlightSegment');
                    unset($flight_xml);

                    foreach ($flights as $key => $flight) {
                        $tmp_flight = (object)array();

                        $tmp_flight->ref_number = $ref_num;
                        $tmp_flight->direction_id = $dir_id;
                        $tmp_flight->elapsed_time = $elapsed_time;
                        $tmp_flight->departure = strtotime(self::xml_attr($flight, 'DepartureDateTime'));
                        $tmp_flight->arrival = strtotime(self::xml_attr($flight, 'ArrivalDateTime'));
                        $tmp_flight->flight_number = self::xml_attr($flight, 'FlightNumber');
                        $tmp_flight->design_code = self::xml_attr($flight, 'ResBookDesigCode');
                        $tmp_flight->departure_airport = self::xml_attr($flight->DepartureAirport, 'LocationCode');
                        $tmp_flight->arrival_airport = self::xml_attr($flight->ArrivalAirport, 'LocationCode');
                        $tmp_flight->operating_airline = self::xml_attr($flight->OperatingAirline, 'Code');
                        $tmp_flight->equipment = self::xml_attr($flight->Equipment, 'AirEquipType');
                        $tmp_flight->marketing_airline = self::xml_attr($flight->MarketingAirline, 'Code');
                        $tmp_flight->design_quantity = self::xml_attr($flight->BookingClassAvails->BookingClassAvail, 'ResBookDesigQuantity');
                        $tmp_flight->design_cabin_code = self::xml_attr($flight->BookingClassAvails->BookingClassAvail, 'ResBookDesigCabinCode');
                        $tmp_flight->fare_basis = self::xml_attr($flight->BookingClassAvails->BookingClassAvail, 'FareBasis');


                        //save the country codes, airports, airlines
                        //then we make a couple of queries to the database to find out their names
                        hrk_sf_codes()->delayCodes('airports', array($tmp_flight->departure_airport, $tmp_flight->arrival_airport));
                        hrk_sf_codes()->delayCodes('airlines', array($tmp_flight->operating_airline, $tmp_flight->marketing_airline));
                        hrk_sf_codes()->delayCode('airplanes', $tmp_flight->equipment);

                        $result['codes']['airports'][$tmp_flight->departure_airport] = null;
                        $result['codes']['airports'][$tmp_flight->arrival_airport] = null;
                        $result['codes']['airlines'][$tmp_flight->operating_airline] = null;
                        $result['codes']['airlines'][$tmp_flight->marketing_airline] = null;
                        $result['codes']['airplanes'][$tmp_flight->equipment] = null;

                        //save $tmp_result to $results['flights']
                        $result['flights'][$ref_num][$dir_id][$key] = (array)$tmp_flight;
                    }

                }
            }

            /*GET PRICE INFO*/
            $price_info_array = $response_xml->xpath('//PriceInfo');
            $price_info = reset($price_info_array);

            if ($price_info) {
                currency_include('convert');

                $currency = self::xml_attr($price_info->ItinTotalFare->TotalFare, 'Currency');
                $service_fee_amount = self::xml_attr($price_info->ServiceFees->ServiceFee, 'Amount');
                $total_fare = self::xml_attr($price_info->ItinTotalFare->TotalFare, 'Amount');

                $result['price']['currency'] = $currency;
                $result['price']['fare']['AZN'] = currency_convert($total_fare, $currency, 'AZN');
                $result['price']['fare']['EUR'] = currency_convert($total_fare, $currency, 'EUR');
                $result['price']['fare']['USD'] = currency_convert($total_fare, $currency, 'USD');
                $result['price']['fare']['RUB'] = currency_convert($total_fare, $currency, 'RUB');

                $result['price']['commission']['AZN'] = currency_convert($service_fee_amount, $currency, 'AZN');
                $result['price']['commission']['EUR'] = currency_convert($service_fee_amount, $currency, 'EUR');
                $result['price']['commission']['USD'] = currency_convert($service_fee_amount, $currency, 'USD');
                $result['price']['commission']['RUB'] = currency_convert($service_fee_amount, $currency, 'RUB');

            }


            /*GET PASSENGERS INFO*/
            $travelers = $response_xml->xpath('//AirTraveler');

            if ($travelers && is_array($travelers)) {
                foreach ($travelers as $traveler) {
                    $type = self::xml_attr($traveler, 'PassengerTypeCode');
                    $traveler_xml = simplexml_load_string($traveler->asXml());
                    $documents = $traveler_xml->xpath('//Document');
                    $document = reset($documents);
                    if ($type != 'INF') {
                        $result['passenger'][$type][] = array(
                          'sex' => $traveler->PersonName->NamePrefix->__toString(),
                          'first_name' => $traveler->PersonName->GivenName->__toString(),
                          'last_name' => $traveler->PersonName->Surname->__toString(),
                          'phone' => array(
                            'type' => self::xml_attr($traveler->Telephone, 'PhoneType'),
                            'number' => self::xml_attr($traveler->Telephone, 'LocationCode'),
                          ),
                          'email' => $traveler->Email->__toString(),
                          'birthday' => $traveler->BirthDate->__toString(),
                          'document' => array(
                            'id' => self::xml_attr($document, 'DocID'),
                            'type' => self::xml_attr($document, 'DocType'),
                            'doc_type' => self::xml_attr($document, 'InnerDocType'),
                            'expire' => self::xml_attr($document, 'ExpireDate'),
                            'country' => self::xml_attr($document, 'DocIssueCountry'),
                          )
                        );
                    } else {
                        $result['passenger'][$type][] = array(
                          'sex' => $traveler->PersonName->NamePrefix->__toString(),
                          'first_name' => $traveler->PersonName->GivenName->__toString(),
                          'last_name' => $traveler->PersonName->Surname->__toString(),
                          'phone' => array(
                            'type' => 'Home',
                            'number' => 'no data',
                          ),
                          'email' => 'no data',
                          'birthday' => $traveler->BirthDate->__toString(),
                          'document' => array(
                            'id' => '000000',
                            'type' => 'Passport',
                            'doc_type' => 'DOCS',
                            'expire' => '2018-05-31',
                            'country' => 'CA',
                          )
                        );
                    }
                }
            }

            /*GET TICKETING LIMITS INFO*/
            $ticketing_limits = $response_xml->xpath('//Ticketing');
            $ticketing_limit = reset($ticketing_limits);

            if ($ticketing_limit) {
                $result['ticket_limit'] = array(
                    'limit' => self::xml_attr($ticketing_limit, 'TicketTimeLimit'),
                    'type' => self::xml_attr($ticketing_limit, 'TicketType'),
                );
            }

            /*GET RULES*/
            $rules = $response_xml->xpath('//FareRules');

            if ($rules && is_array($rules)) {
                foreach ($rules as $rule) {
                    $rule_xml = simplexml_load_string($rule->asXml());
                    $sections = $rule_xml->xpath('//SubSection');
                    if ($sections && is_array($sections)) {
                        foreach ($sections as $section) {

                            if (self::xml_attr($section, 'SubCode') == 'PE') {

                                $section_xml = simplexml_load_string($section->asXMl());
                                $paragraphs = $section_xml->xpath('//Paragraph');

                                if ($paragraphs && is_array($paragraphs)) {
                                    foreach ($paragraphs as $paragraph) {
                                        $paragraph_xml = simplexml_load_string($paragraph->asXMl());
                                        $texts = $paragraph_xml->xpath('//Text');

                                        if ($texts && is_array($texts)) {
                                            $result['penalties'] = array();
                                            foreach ($texts as $text) {

                                                if (str_word_count($text[0]) <= 2) {
                                                    $result['penalties'][] = array('type' => 'title', 'text' => $text[0]->__toString());
                                                    continue;
                                                }

                                                $result['penalties'][] = array('type' => 'description', 'text' => $text[0]->__toString());
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            /*GET CODES*/

            //get codes from db
            if (!empty($result['codes'])) {
                hrk_sf_codes()->delayStart();
                foreach ($result['codes'] as $type => $code) {
                    foreach ($code as $cd => $value) {
                        $codes = hrk_sf_codes()->getCode($type, $cd);
                        $result['codes'][$type][$cd] = reset($codes);
                    }
                }
            }
        } else {
            $error = 'Response empty or not BookFlightResponse';
            throw new \Exception($error);
        }

        return $result;
    }

    public function cancel()
    {
        $result = array();

        if ($this->_xml && $this->_xml->soapBody->CancelResponse) {
            $response = & $this->_xml->soapBody->CancelResponse->OTA_CancelRS;

            $response_xml = simplexml_load_string($response->asXml());
            $errors = $response_xml->xpath('//Errors');

            if ($errors && is_array($errors)) {
                foreach ($errors as $error) {
                    $result['errors'][] = array(
                        'type' => $this->xml_attr($error->Error, 'Type'),
                        'text' => $this->xml_attr($error->Error, 'ShortText'),
                        'code' => $this->xml_attr($error->Error, 'Code'),
                        'node_list' => $this->xml_attr($error->Error, 'NodeList'),
                    );
                }
            }else{
                $result['success'] = TRUE;
            }
        }
        return $result;
    }

    static public function xml_attr(\SimpleXMLElement $object, $attribute, $default = FALSE)
    {
        if (isset($object[$attribute])) $default = (string)$object[$attribute];
        return $default;
    }
}


