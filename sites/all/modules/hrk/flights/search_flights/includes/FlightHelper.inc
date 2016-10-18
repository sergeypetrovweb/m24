<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 11.09.14
 * Time: 15:24
 */


namespace includes;


class FlightHelper
{

    public static function create()
    {
        return new FlightHelper();
    }

    public function make_results_page_link($params)
    {
        return 'flights/results/' . $params['des'] . '/' . $params['date'] . '/' . $params['pas'] . '/' . $params['c'] . '/' . $params['m'];
    }

    public function get_results_params_from_results_page_link($link, $full = FALSE)
    {
        $url_pieces = explode('/', $link);

        if (empty($url_pieces[2]) && empty($url_pieces[3]) && empty($url_pieces[4]) && empty($url_pieces[5]) && empty($url_pieces[6])) return FALSE;

        $params = array('des' => $url_pieces[2], 'date' => $url_pieces[3], 'pas' => $url_pieces[4], 'c' => $url_pieces[5], 'm' => $url_pieces[6]);

        return ($full) ? hrk_sf_uncompress_request_param($params) : $params;
    }

    public function compress_request_param($params)
    {
        $query = '';

        switch ($params['direction_type']) {
            case 'round_trip':
                $query['m'] = 1;
                break;
            case 'one_way':
                $query['m'] = 0;
                break;
            case 'multi_stop':
                $query['m'] = 2;
                break;
        }

        foreach ($params['trip'] as $index => $trip) {
            $trip = (object)$trip;
            if (empty($query['des'])) $query['des'] = '';
            if (empty($query['date'])) $query['date'] = '';

            $from = (object)$trip->direction_from;
            $to = (object)$trip->direction_to;

            $query['des'] .= $from->type[0] . '_' . $from->code . '-';
            $query['des'] .= $to->type[0] . '_' . $to->code;

            if (isset($params['trip'][$index + 1])) {
                $query['des'] .= '->';
            }

            $query['date'] .= date('ymd', strtotime($trip->departure));
            if (!empty($trip->return)) {
                $query['date'] .= '-' . date('ymd', strtotime($trip->return));
            }

            if (isset($params['trip'][$index + 1])) {
                $query['date'] .= '->';
            }
        }

        $query['pas'] = $params['passengers']['adt'];
        $query['pas'] .= !empty($params['passengers']['chd']) ? $params['passengers']['chd'] : 0;
        $query['pas'] .= !empty($params['passengers']['inf']) ? $params['passengers']['inf'] : 0;

        $query['c'] = $params['cabin_type'];

        return $query;
    }

    public function uncompress_request_param($query_array)
    {
        $params = array();

        if (isset($query_array['m'])) {
            switch ($query_array['m']) {
                case '1':
                    $params['direction_type'] = 'round_trip';
                    break;
                case '0':
                    $params['direction_type'] = 'one_way';
                    break;
                case '2':
                    $params['direction_type'] = 'multi_stop';
                    break;
            }
        }

        if (!empty($query_array['des'])) {
            $trips = explode('->', $query_array['des']);

            foreach ($trips as $trips_index => $trips_str) {
                if (!empty($trips_str)) {
                    $trip_des = explode('-', $trips_str);
                    foreach ($trip_des as $trip_index => $trip_str) {
                        if (!empty($trip_str)) {
                            $trip_index++;
                            $dir = ($trip_index % 2) ? 'direction_from' : 'direction_to';
                            $trip = explode('_', $trip_str);

                            $params['trip'][$trips_index + 1][$dir]['code'] = $trip[1];
                            $params['trip'][$trips_index + 1][$dir]['type'] = ($trip[0] == 'c') ? 'city' : 'airport';
                        }
                    }
                }
            }
        }

        if (!empty($query_array['date'])) {
            $dates = explode('->', $query_array['date']);

            foreach ($dates as $dates_index => $date_str) {
                if ($date_str) {
                    $dates = explode('-', $date_str);
                    $params['trip'][$dates_index + 1]['departure'] = date('Y-m-d', strtotime(implode('-', str_split($dates[0], 2))));

                    if (!empty($dates[1])) {
                        $params['trip'][$dates_index + 1]['return'] = date('Y-m-d', strtotime(implode('-', str_split($dates[1], 2))));
                    }
                }
            }
        }

        if (!empty($query_array['pas'])) {
            if (isset($query_array['pas'][0])) {
                $params['passengers']['adt'] = $query_array['pas'][0];
            }
            if (isset($query_array['pas'][1])) {
                $params['passengers']['chd'] = $query_array['pas'][1];
            }
            if (isset($query_array['pas'][2])) {
                $params['passengers']['inf'] = $query_array['pas'][2];
            }
        }

        if (!empty($query_array['c'])) {
            $params['cabin_type'] = $query_array['c'];
        }

        return $params;
    }

    public function validate_request_param($params, $default = false)
    {
        global $language;

        $validated_params = array();

        //validate direction_type
        if (empty($params['direction_type'])) return $default;
        $params['direction_type'] = filter_var($params['direction_type'], FILTER_SANITIZE_FULL_SPECIAL_CHARS);

        if (!in_array($params['direction_type'], array('round_trip', 'one_way', 'multi_stop'))) return $default;
        $validated_params['direction_type'] = $params['direction_type'];

        //validate trips
        if (empty($params['trip']) && !is_array($params['trip'])) return $default;

        switch ($validated_params['direction_type']) {
            case 'round_trip':
                if (count($params['trip']) > 1) return $default;
                break;
            case 'one_way':
                if (count($params['trip']) > 1) return $default;
                break;
            case 'multi_stop':
                if (count($params['trip']) > 6) return $default;
                break;
        }

        foreach ($params['trip'] as $index => $trip) {
            if (!in_array($trip['direction_from']['type'], array('city', 'airport')) || !in_array($trip['direction_to']['type'], array('city', 'airport'))) return $default;
            switch ($validated_params['direction_type']) {
                case 'round_trip':
                    if (empty($trip['departure']) && !self::validate_date($trip['departure'], 'Y-m-d') && $trip['departure'] < strtotime('+365 days')) return $default;
                    if (empty($trip['return']) && !self::validate_date($trip['return'], 'Y-m-d') && $trip['return'] < strtotime('+365 days')) return $default;

                    $validated_params['trip'][$index] = array(
                        'departure' => $trip['departure'],
                        'return' => $trip['return']
                    );
                    break;
                default:
                    if (empty($trip['departure']) && !self::validate_date($trip['departure'], 'Y-m-d')) return $default;
                    $validated_params['trip'][$index]['departure'] = $trip['departure'];
                    break;
            }
            $codes[$trip['direction_from']['type']][] = $trip['direction_from']['code'];
            $codes[$trip['direction_to']['type']][] = $trip['direction_to']['code'];
        }

        if (empty($codes)) return $default;

        $l_prefix = ($language->language == 'en') ? 'en' : 'ru';
        $name_field = 'name_' . $l_prefix;

        $direction_types = array('city', 'airport');

        foreach ($direction_types as $type) {
            if (!empty($codes[$type])) {
                $table_name = ($type == 'city') ? 'hrk_sf_cities' : 'hrk_sf_airports';

                $query = db_select($table_name, 'sf');
                $query->fields('sf', array($name_field, 'code'));
                $query->condition('sf.code', $codes[$type], 'IN');
                $results = $query->execute();

                foreach ($results as $row) {
                    $db_codes[$type][$row->code] = array(
                        'q' => $row->$name_field,
                        'code' => $row->code,
                        'type' => $type
                    );
                }
            }
        }

        if (empty($db_codes)) return $default;

        foreach ($params['trip'] as $index => $trip) {
            $from_type = $trip['direction_from']['type'];
            $to_type = $trip['direction_to']['type'];

            $from_code = $trip['direction_from']['code'];
            $to_code = $trip['direction_to']['code'];

            if (empty($db_codes[$from_type][$from_code]) || empty($db_codes[$to_type][$to_code])) return $default;

            $validated_params['trip'][$index]['direction_from'] = array(
                'q' => $db_codes[$from_type][$from_code]['q'],
                'code' => $from_code,
                'type' => $from_type
            );

            $validated_params['trip'][$index]['direction_to'] = array(
                'q' => $db_codes[$to_type][$to_code]['q'],
                'code' => $to_code,
                'type' => $to_type
            );

        }

        //validate passengers
        if (empty($params['passengers']) && !is_array($params['passengers'])) return $default;

        if (empty($params['passengers']['adt'])) return $default;

        if (!filter_var($params['passengers']['adt'], FILTER_VALIDATE_INT)) return $default;
        $validated_params['passengers']['adt'] = $params['passengers']['adt'];

        if (!empty($params['passengers']['chd'])) {
            if (!filter_var($params['passengers']['chd'], FILTER_VALIDATE_INT)) return $default;
            if ($validated_params['passengers']['adt'] + $params['passengers']['chd'] > SEARCH_FLIGHTS_MODULE_MAX_TRIPS_COUNT) return $default;
            $validated_params['passengers']['chd'] = $params['passengers']['chd'];
        }

        if (!empty($params['passengers']['inf'])) {
            if (!filter_var($params['passengers']['inf'], FILTER_VALIDATE_INT)) return $default;
            if ($validated_params['passengers']['adt'] < $params['passengers']['inf']) return $default;
            $validated_params['passengers']['inf'] = $params['passengers']['inf'];
        }

        //validate cabin_type
        if (empty($params['cabin_type']) && !in_array($params['cabin_type'], array('E', 'F', 'B'))) return $default;
        $validated_params['cabin_type'] = $params['cabin_type'];

        return $validated_params;
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
        if ($xml->soapBody->SearchFlightResponse) {
            $response = & $xml->soapBody->SearchFlightResponse->OTA_AirLowFareSearchRS;

            if ($response->Errors) {
                //check if error is "No available flights"
                if (!is_array($response->Errors) && ($this->xml_attr($response->Errors, 'ShortText') == 'No available flights' || $this->xml_attr($response->Errors, 'ShortText') == 'EPowerException.EPowerException.No Available Flights')) {
                    $result['empty'] = TRUE;
                }

                $error_xml = simplexml_load_string($response->Errors->asXml());
                $errors = $error_xml->xpath('//Error');
                foreach ($errors as $error) {
                    $result['errors'][] = array(
                        'type' => $this->xml_attr($error, 'Type'),
                        'text' => $this->xml_attr($error, 'ShortText'),
                        'code' => $this->xml_attr($error, 'Code'),
                    );
                }

                return $result;
            }

            //if no errors
            currency_include('convert');

            $priced_it_xml = simplexml_load_string($response->asXml());
            $priced_it = $priced_it_xml->xpath('//PricedItinerary');
            $priced_it_owc = $priced_it_xml->xpath('//PricedItineraryForOWC');   // One Way Combinable Fares


            unset($priced_it_xml);

            //TODO: Удалите это, если Вы уже добавили Компинированные перелты. Это временная мера.
            if (empty($priced_it) and empty($priced_it_owc)) {
                $result['errors'][] = array(
                  'type' => 'EpowerInternalError',
                  'text' => 'EPowerException.EPowerException.No Available Flights',
                  'code' => 'A000',
                );
                return $result;
            }

            foreach ($priced_it as $priced_it_unit) {
                $seg = simplexml_load_string($priced_it_unit->asXML());

                //segments
                $flight_seg = $seg->xpath('//OriginDestinationOption');
                $comb_seg = $seg->xpath('//OriginDestinationCombination');
                $price_segms = $seg->xpath('//ItinTotalFare');
                $price_seg = reset($price_segms);
                $fare_break_down_seg = $seg->xpath('//PTC_FareBreakdown');

                unset($seg);

                //$priced_it_unit attributes
                $sequence_num = self::xml_attr($priced_it_unit, 'SequenceNumber');

                //set all flights to result array
                foreach ($flight_seg as $flight_seg_unit) {
                    //$flight_seg_unit attributes
                    $ref_num = self::xml_attr($flight_seg_unit, 'RefNumber');
                    $dir_id = self::xml_attr($flight_seg_unit, 'DirectionId');
                    $elapsed_time_piece = str_split(self::xml_attr($flight_seg_unit, 'ElapsedTime', ''), 2);
                    $elapsed_time = 3600 * intval($elapsed_time_piece[0]) + 60 * intval($elapsed_time_piece[1]);
                    $flight_xml = simplexml_load_string($flight_seg_unit->asXml());
                    $flights = $flight_xml->xpath('//FlightSegment');
                    unset($flight_xml);

                    foreach ($flights as $index => $flight) {
                        $tmp_flight = (object)array();

                        $tmp_flight->ref_number = $ref_num;
                        $tmp_flight->direction_id = $dir_id;
                        $tmp_flight->elapsed_time = $elapsed_time;
                        $tmp_flight->departure = strtotime(self::xml_attr($flight, 'DepartureDateTime'));
                        $tmp_flight->arrival = strtotime(self::xml_attr($flight, 'ArrivalDateTime'));
                        $tmp_flight->flight_number = self::xml_attr($flight, 'FlightNumber');
                        $tmp_flight->design_code = self::xml_attr($flight, 'ResBookDesigCode');
                        $tmp_flight->departure_airport = $tmp_flight->departure_airport_code = self::xml_attr($flight->DepartureAirport, 'LocationCode');
                        $tmp_flight->arrival_airport = $tmp_flight->arrival_airport_code = self::xml_attr($flight->ArrivalAirport, 'LocationCode');
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
                        $result['flights'][$sequence_num][$ref_num][$dir_id][$index] = (array)$tmp_flight;
                    }
                }

                //prepare commission and prices
                $currency = self::xml_attr($priced_it_unit, 'Currency');
                $provider = self::xml_attr($priced_it_unit, 'ProviderType');
                $total_fare_com = self::xml_attr($price_seg->TotalFare, 'Amount');



                //prepare price
                $price = array(
                    'SOURCE' => array(
                      'currency' => $currency,
                      'total_fare' => $total_fare_com,
                    ),
                    'AZN' => currency_convert($total_fare_com, $currency, 'AZN'),
                    'RUB' => currency_convert($total_fare_com, $currency, 'RUB'),
                    'EUR' => currency_convert($total_fare_com, $currency, 'EUR'),
                    'USD' => currency_convert($total_fare_com, $currency, 'USD'),
                );

                //prepare designators

                $fare_break_down = array();

                foreach ($fare_break_down_seg as $fare_break_down_unit) {
                    $code = self::xml_attr($fare_break_down_unit->PassengerTypeQuantity, 'Code');
                    $fare_break_down[$code] = array(
                        'code' => $code,
                        'quantity' => self::xml_attr($fare_break_down_unit->PassengerTypeQuantity, 'Quantity'),
                        'base_fare' => self::xml_attr($fare_break_down_unit->PassengerFare->BaseFare, 'Amount'),
                        'tax' => self::xml_attr($fare_break_down_unit->PassengerFare->Taxes->Tax, 'Amount'),
                        'total_fare' => self::xml_attr($fare_break_down_unit->PassengerFare->TotalFare, 'Amount'),
                    );

                    $ticket_designators_xml = simplexml_load_string($fare_break_down_unit->TicketDesignators->asXml());
                    //was cases when tiket designators was empty,i am add check
                    if (is_object($ticket_designators_xml)) {
                        $ticket_designators = $ticket_designators_xml->xpath('//TicketDesignator');
                        unset($ticket_designators_xml);

                        foreach ($ticket_designators as $ticket_designator) {
                            $fare_break_down[$code]['designators'][] = array(
                                'code' => self::xml_attr($ticket_designator, 'TicketDesignatorCode'),
                                'ext' => self::xml_attr($ticket_designator, 'TicketDesignatorExtension')
                            );
                        }
                    }
                }

                //set all combinations to result array
                foreach ($comb_seg as $comb) {
                    $index_list = self::xml_attr($comb, 'IndexList');
                    $index_array = explode(';', $index_list);

                    $tmp_comb = (object)array();

                    //get all combination elapsed_time
                    $first_flight = null;
                    $tmp_comb->elapsed_time = 0;
                    $tmp_comb->direct = 1;
                    foreach ($index_array as $dir => $ref) {
                        if (count($result['flights'][$sequence_num][$ref][$dir]) - 1) {
                            $tmp_comb->direct = 0;
                        }

                        foreach ($result['flights'][$sequence_num][$ref][$dir] as $flight_unit) {
                            if (!$first_flight) {
                                $first_flight = $flight_unit;
                            }
                            $tmp_comb->elapsed_time += $flight_unit['elapsed_time'];
                        }
                    }
                    $service_fee_amount = self::xml_attr($comb, 'ServiceFeeAmount');

                    $commission = array(
                        'AZN' => currency_convert($service_fee_amount, $currency, 'AZN'),
                        'EUR' => currency_convert($service_fee_amount, $currency, 'EUR'),
                        'USD' => currency_convert($service_fee_amount, $currency, 'USD'),
                        'RUB' => currency_convert($service_fee_amount, $currency, 'RUB'),
                    );


                    $tmp_comb->validating_airline_code = self::xml_attr($comb, 'ValidatingAirlineCode');
                    $tmp_comb->force_e_ticket = self::xml_attr($comb, 'ForceETicket');
                    $tmp_comb->index_list = $index_array;
                    $tmp_comb->combination_id = self::xml_attr($comb, 'CombinationID');
                    $tmp_comb->sequence_number = $sequence_num;
                    $tmp_comb->commission = $commission;
                    $tmp_comb->full_price = $total_fare_com + $service_fee_amount;
                    $tmp_comb->price = $price;

                    $tmp_comb->fare_break_down = $fare_break_down;
                    $tmp_comb->provider = strtolower(str_replace('Provider', '', $provider));
										$tmp_comb->owc = '';

                    $result['combinations'][$first_flight['marketing_airline']][$tmp_comb->sequence_number . $tmp_comb->combination_id] = (array)$tmp_comb;
                }
            }


						// AI: GETTING ONE WAY COMBINABLE FARES
						
            foreach ($priced_it_owc as $priced_it_unit_owc) {
                $seg = simplexml_load_string($priced_it_unit_owc->asXML());

                $flight_seg = $seg->xpath('//OriginDestinationOption');
                $comb_seg = $seg->xpath('//OriginDestinationCombination');

                unset($seg);
						
                //$priced_it_unit attributes
                $sequence_num = self::xml_attr($priced_it_unit_owc, 'SequenceNumber');

                //prepare commission and prices
                $currency = self::xml_attr($priced_it_unit_owc, 'Currency');

                //set all flights, prices, providers and designators and  to result array
                foreach ($flight_seg as $flight_seg_unit) {
                    //$flight_seg_unit attributes
                    $ref_num = self::xml_attr($flight_seg_unit, 'RefNumber');
                    $dir_id = self::xml_attr($flight_seg_unit, 'DirectionId');
                    $elapsed_time_piece = str_split(self::xml_attr($flight_seg_unit, 'ElapsedTime', ''), 2);
                    $elapsed_time = 3600 * intval($elapsed_time_piece[0]) + 60 * intval($elapsed_time_piece[1]);
                    $flight_xml = simplexml_load_string($flight_seg_unit->asXml());
                    $flights = $flight_xml->xpath('//FlightSegment');

				            $price_segms = $flight_xml->xpath('//ItinTotalFare');
				            $price_seg = reset($price_segms);
                    $result['provider'][$sequence_num][$ref_num][$dir_id] = self::xml_attr($flight_seg_unit, 'ProviderType');
										$result['price'][$sequence_num][$ref_num][$dir_id] = self::xml_attr($price_seg->TotalFare, 'Amount');

                    unset($flight_xml);

                    foreach ($flights as $index => $flight) {
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
                        $result['flights'][$sequence_num][$ref_num][$dir_id][$index] = (array)$tmp_flight;
                    }
                }


                //set all combinations to result array
                foreach ($comb_seg as $comb) {
                    $index_list = self::xml_attr($comb, 'IndexList');
                    $index_array = explode(';', $index_list);

                    $tmp_comb = (object)array();

                    //get all combination elapsed_time
                    $first_flight = null;
                    $tmp_comb->elapsed_time = 0;
                    $tmp_comb->direct = 1;
										$total_fare_com = 0;
                    foreach ($index_array as $dir => $ref) {
												$total_fare_com += $result['price'][$sequence_num][$ref][$dir];
                        if (count($result['flights'][$sequence_num][$ref][$dir]) - 1) {
                            $tmp_comb->direct = 0;
                        }

                        foreach ($result['flights'][$sequence_num][$ref][$dir] as $flight_unit) {
                            if (!$first_flight) {
                                $first_flight = $flight_unit;
                            }
                            $tmp_comb->elapsed_time += $flight_unit['elapsed_time'];
                        }
                    }
										//echo($total_fare_com.'<br>');
                    $service_fee_amount = self::xml_attr($comb, 'ServiceFeeAmount');

                    $commission = array(
                        'AZN' => currency_convert($service_fee_amount, $currency, 'AZN'),
                        'EUR' => currency_convert($service_fee_amount, $currency, 'EUR'),
                        'USD' => currency_convert($service_fee_amount, $currency, 'USD'),
                        'RUB' => currency_convert($service_fee_amount, $currency, 'RUB'),
                    );


                //prepare price
                $price = array(
                    'SOURCE' => array(
                      'currency' => $currency,
                      'total_fare' => $total_fare_com,
                    ),
                    'AZN' => currency_convert($total_fare_com, $currency, 'AZN'),
                    'RUB' => currency_convert($total_fare_com, $currency, 'RUB'),
                    'EUR' => currency_convert($total_fare_com, $currency, 'EUR'),
                    'USD' => currency_convert($total_fare_com, $currency, 'USD'),
                );

                    $tmp_comb->validating_airline_code = self::xml_attr($comb, 'ValidatingAirlineCode');
                    $tmp_comb->force_e_ticket = self::xml_attr($comb, 'ForceETicket');
                    $tmp_comb->index_list = $index_array;
                    $tmp_comb->combination_id = self::xml_attr($comb, 'CombinationID');
                    $tmp_comb->sequence_number = $sequence_num;
                    $tmp_comb->commission = $commission;
                    $tmp_comb->full_price = $total_fare_com + $service_fee_amount;
                    $tmp_comb->price = $price;

                    $tmp_comb->fare_break_down = $fare_break_down;
                    $tmp_comb->provider = strtolower(str_replace('Provider', '', $provider));
										$tmp_comb->owc = 'OWC';

                    $result['combinations'][$first_flight['marketing_airline']][$tmp_comb->sequence_number . $tmp_comb->combination_id] = (array)$tmp_comb;
                }

						}

						
						// --- AI: END OF ONE WAY COMBINABLE FARES


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
            $error = 'Response empty or not SearchFlightResponse';
            throw new \Exception($error);
        }

        return $result;
    }


		// AI: PARSING +/-3days CALENDAR
    public function makeArrayFromCalendarResponse(\SimpleXMLElement $xml, $direction_type)
    {
       	//check if response is SearchFlightResponse
       	if ($xml->soapBody->SearchFlightCalendarResponse) {
       			$response = & $xml->soapBody->SearchFlightCalendarResponse->OTA_AirLowFareSearchRS;

            //if no errors
            currency_include('convert');

            $priced_it_xml = simplexml_load_string($response->asXml());
            $priced_it = $priced_it_xml->xpath('//PricedItinerary');
            unset($priced_it_xml);

            foreach ($priced_it as $priced_it_unit) {
                $seg = simplexml_load_string($priced_it_unit->asXML());

                $flight_seg = $seg->xpath('//OriginDestinationOption');
                $comb_seg = $seg->xpath('//OriginDestinationCombination');
                $price_segms = $seg->xpath('//ItinTotalFare');
                $price_seg = reset($price_segms);

                unset($seg);

                //$priced_it_unit attributes
                $sequence_num = self::xml_attr($priced_it_unit, 'SequenceNumber');
								$flight_dates = array();

                foreach ($flight_seg as $flight_seg_unit) {
                    $ref_num = self::xml_attr($flight_seg_unit, 'RefNumber');
                    $dir_id = self::xml_attr($flight_seg_unit, 'DirectionId');
                    $flight_xml = simplexml_load_string($flight_seg_unit->asXml());
                    $flights = $flight_xml->xpath('//FlightSegment');
										$flight = reset($flights);
                    unset($flight_xml);

                    $tmp_flight = (object)array();
                    $tmp_flight->ref_number = $ref_num;
                    $tmp_flight->direction_id = $dir_id;
                    $tmp_flight->marketing_airline = self::xml_attr($flight->MarketingAirline, 'Code');
                    $tmp_flight->departure = format_date(strtotime(self::xml_attr($flight, 'DepartureDateTime')), 'custom', 'd-m-Y');
                    $flight_dates[$sequence_num][$ref_num][$dir_id] = (array)$tmp_flight;
								}


               //prepare commission and prices
                $currency = self::xml_attr($priced_it_unit, 'Currency');
                $provider = self::xml_attr($priced_it_unit, 'ProviderType');
                $total_fare_com = self::xml_attr($price_seg->TotalFare, 'Amount');

                //prepare price
                $price = array(
                    'SOURCE' => array(
                      'currency' => $currency,
                      'total_fare' => $total_fare_com,
                    ),
                    'AZN' => currency_convert($total_fare_com, $currency, 'AZN'),
                    'RUB' => currency_convert($total_fare_com, $currency, 'RUB'),
                    'EUR' => currency_convert($total_fare_com, $currency, 'EUR'),
                    'USD' => currency_convert($total_fare_com, $currency, 'USD'),
                );

                //set all combinations to result array
                foreach ($comb_seg as $comb) {
                    $index_list = self::xml_attr($comb, 'IndexList');
                    $index_array = explode(';', $index_list);

                    $tmp_comb = (object)array();

										foreach ($index_array as $dir => $ref) {
											if ($dir == 0){
												$tmp_comb->departure = $flight_dates[$sequence_num][$ref][$dir]['departure'];
											}
											else{
												$tmp_comb->arrival = $flight_dates[$sequence_num][$ref][$dir]['departure'];
											}
												//$tmp_comb->airline = $flight_dates[$sequence_num][$ref][$dir]['marketing_airline'];
										}

                    $service_fee_amount = self::xml_attr($comb, 'ServiceFeeAmount');

                    $commission = array(
                        'AZN' => currency_convert($service_fee_amount, $currency, 'AZN'),
                        'EUR' => currency_convert($service_fee_amount, $currency, 'EUR'),
                        'USD' => currency_convert($service_fee_amount, $currency, 'USD'),
                        'RUB' => currency_convert($service_fee_amount, $currency, 'RUB'),
                    );

                    $tmp_comb->airline = self::xml_attr($comb, 'ValidatingAirlineCode');
                    $tmp_comb->index_list = $index_array;
                    $tmp_comb->combination_id = self::xml_attr($comb, 'CombinationID');
                    $tmp_comb->sequence_number = $sequence_num;
                    $tmp_comb->commission = $commission;
                    $tmp_comb->full_price = $total_fare_com + $service_fee_amount;
                    $tmp_comb->price = $price;
										if ($direction_type == 'one_way') {
											$result['combinations'][$tmp_comb->departure] = (array)$tmp_comb;
										}
										else {
											$result['combinations'][$tmp_comb->departure][$tmp_comb->arrival] = (array)$tmp_comb;
										}
			
                }
						}
				}			

			return $result;
		}
		// --- AI: END OF CALENDAR PARSING


    static public function xml_attr(\SimpleXMLElement $object, $attribute, $default = FALSE)
    {
        if (isset($object[$attribute])) $default = (string)$object[$attribute];
        return $default;
    }
} 