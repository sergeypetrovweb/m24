<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 23.10.14
 * Time: 11:02
 */

namespace includes;


class BH_Helper
{

    public static function parseCancellationPolicy($response)
    {
        helper_include('SoapXmlReader');
        $xml = SoapXmlReader::create()->parse($response);

        $result = array();

        //check if response is SearchFlightResponse
        if ($xml->sBody->ServiceRequestResponse) {
            $request_result = & $xml->sBody->ServiceRequestResponse->ServiceRequestResult;

            /*CHECK IF WE HAVE ERRORS*/
            if (get_object_vars($request_result->Errors)) {
                $result['error'] = array(
                    'code' => SoapXmlReader::xml_value($request_result->Errors->Error, 'ErrorCode'),
                    'text' => SoapXmlReader::xml_value($request_result->Errors->Error, 'ErrorText'),
                    'message' => SoapXmlReader::xml_value($request_result->Errors->Error, 'Message'),
                );

                return $result;
            }

            $service_request_result_xml = simplexml_load_string($request_result->asXML());
            $cancellation_policies = $service_request_result_xml->xpath('//CancellationPolicy');
            $book_remarks = $service_request_result_xml->xpath('//BookingRemarks');

            /*RETURN ERROR NO RESULTS FOUND.*/
            if (!$cancellation_policies) {
                $result['error'] = array(
                    'code' => 'I0404',
                    'text' => 'No results found.',
                    'message'=>''
                );

                return $result;
            }

            if ($book_remarks) {
                foreach ($book_remarks as $index => $remark) {
                    $result['cancellation_remarks'][$index] = SoapXmlReader::xml_value($remark, 0);
                }

            }

            /*GET POLICY*/

            foreach ($cancellation_policies as $index => $policy) {
                $result['cancellation_policy'][$index] = array(
                    'currency' => SoapXmlReader::xml_value($policy->CancellationFee, 'Currency'),
                    'price' => SoapXmlReader::xml_value($policy->CancellationFee, 'FinalPrice'),
                    'final_price_in_currency' => SoapXmlReader::xml_value($policy->CancellationFee, 'FinalPriceInSupplierCurrency'),
                    'original_price' => SoapXmlReader::xml_value($policy->CancellationFee, 'OriginalPrice'),
                    'original_price_in_currency' => SoapXmlReader::xml_value($policy->CancellationFee, 'OriginalPriceInSupplierCurrency'),
                    'supplier_currency' => SoapXmlReader::xml_value($policy->CancellationFee, 'SupplierCurrency'),
                    'date_from' => SoapXmlReader::xml_value($policy, 'DateFrom'),
                    'date_to' => SoapXmlReader::xml_value($policy, 'DateTo'),
                    'description' => SoapXmlReader::xml_value($policy, 'Description'),
                );
            }

        } else {
            $error = 'Response empty or not SearchFlightResponse';
            throw new \Exception($error);
        }

        return $result;
    }


    public static function parsePaymentReference($response)
    {
        helper_include('SoapXmlReader');
        $xml = SoapXmlReader::create()->parse($response);

        $result = array();

        //check if response is SearchFlightResponse
        if ($xml->sBody->ServiceRequestResponse) {
            $request_result = & $xml->sBody->ServiceRequestResponse->ServiceRequestResult;

            /*CHECK IF WE HAVE ERRORS*/
            if (get_object_vars($request_result->Errors)) {
                $result['error'] = array(
                    'code' => SoapXmlReader::xml_value($request_result->Errors->Error, 'ErrorCode'),
                    'text' => SoapXmlReader::xml_value($request_result->Errors->Error, 'ErrorText'),
                    'message' => SoapXmlReader::xml_value($request_result->Errors->Error, 'Message'),
                );

                return $result;
            }

            $service_request_result_xml = simplexml_load_string($request_result->asXML());
            $payment_preferences = $service_request_result_xml->xpath('//aPaymentPreference');

            /*RETURN ERROR NO RESULTS FOUND.*/
            if (!$payment_preferences) {
                $result['error'] = array(
                    'code' => 'I0404',
                    'text' => 'No results found.'
                );

                return $result;
            }

            /*GET PAYMENT PREFERENCES*/

            foreach ($payment_preferences as $payment_preference) {
                $type = SoapXmlReader::xml_value($payment_preference, 'aType');

                $result['payment_preferences'][$type]['type'] = $type;
                if ($type != 'Cash' && $type != 'PayOnArrival') {

                    $credit_cards_xml = simplexml_load_string($payment_preference->asXML());
                    $credit_cards = $credit_cards_xml->xpath('//aCreditCardPaymentCommision');

                    if ($credit_cards) {
                        $result['payment_preferences'][$type]['credit_cards'] = array();
                        $tmp_credit_cards = & $result['payment_preferences'][$type]['credit_cards'];
                        foreach ($credit_cards as $credit_card) {
                            $card_type = SoapXmlReader::xml_value($credit_card, 'aCardType');
                            if ($card_type) {
                                $tmp_credit_cards[$card_type] = array(
                                    'type' => $card_type,
                                    'currency' => SoapXmlReader::xml_value($credit_card, 'aChargingCurrency'),
                                    'commission' => SoapXmlReader::xml_value($credit_card, 'aCommision'),
                                    'conversion_rate' => SoapXmlReader::xml_value($credit_card, 'aConversionRate'),
                                    'flat_fee' => SoapXmlReader::xml_value($credit_card, 'FlatFee'),
                                );
                            }
                        }
                    }
                }
            }
        } else {
            $error = 'Response empty or not SearchFlightResponse';
            throw new \Exception($error);
        }

        return $result;
    }

    static public function parseBookingResponse($response)
    {
        helper_include('SoapXmlReader');
        $xml = SoapXmlReader::create()->parse($response);

        $result = array();

        //check if response is SearchFlightResponse
        if ($xml->sBody->ServiceRequestResponse) {
            $request_result = & $xml->sBody->ServiceRequestResponse->ServiceRequestResult;

            /*CHECK IF WE HAVE ERRORS*/
            if (get_object_vars($request_result->Errors)) {
                $result['error'] = array(
                    'code' => SoapXmlReader::xml_value($request_result->Errors->Error, 'ErrorCode'),
                    'text' => SoapXmlReader::xml_value($request_result->Errors->Error, 'ErrorText'),
                    'message' => SoapXmlReader::xml_value($request_result->Errors->Error, 'Message'),
                );

                return $result;
            }

            $service_request_result_xml = simplexml_load_string($request_result->asXML());
            $hotel_book_segments = $service_request_result_xml->xpath('//HotelBookSegment');

            /*RETURN ERROR NO RESULTS FOUND.*/
            if (!$hotel_book_segments) {
                $result['error'] = array(
                    'code' => 'I0404',
                    'text' => 'No results found.',
                    'message'=>''
                );

                return $result;
            }

            /*GET BOOKING INFO*/
            $hotel_book_segment = reset($hotel_book_segments);

            $result = array(
                'booking_id' => SoapXmlReader::xml_value($hotel_book_segment, 'BookingID'),
                'reference' => SoapXmlReader::xml_value($hotel_book_segment, 'BookingReference'),
                'order_id' => SoapXmlReader::xml_value($hotel_book_segment, 'OrderId'),
                'segment_id' => SoapXmlReader::xml_value($hotel_book_segment, 'SegmentId'),
                'status' => SoapXmlReader::xml_value($hotel_book_segment, 'Status')
            );

            /*GET REMARKS*/
            if (!empty($hotel_book_segment->BookingRemarks)) {
                $remarks_xml = simplexml_load_string($hotel_book_segment->BookingRemarks->asXML());
                $remarks = $remarks_xml->xpath('//bstring');

                if ($remarks) {
                    foreach ($remarks as $remark) {
                        $result['remarks'][] = SoapXmlReader::xml_value($remark, 0);
                    }
                }
            }

            /*GET PRICE*/
            $result['price'] = array(
                'currency' => SoapXmlReader::xml_value($hotel_book_segment->TotalPrice, 'Currency'),
                'price' => SoapXmlReader::xml_value($hotel_book_segment->TotalPrice, 'FinalPrice'),
                'final_price_in_currency' => SoapXmlReader::xml_value($hotel_book_segment->TotalPrice, 'FinalPriceInSupplierCurrency'),
                'original_price' => SoapXmlReader::xml_value($hotel_book_segment->TotalPrice, 'OriginalPrice'),
                'original_price_in_currency' => SoapXmlReader::xml_value($hotel_book_segment->TotalPrice, 'OriginalPriceInSupplierCurrency'),
                'supplier_currency' => SoapXmlReader::xml_value($hotel_book_segment->TotalPrice, 'SupplierCurrency'),
            );
        } else {
            $error = 'Response empty or not SearchFlightResponse';
            throw new \Exception($error);
        }

        return $result;
    }

    public static function parseCancelResponse($response){
        helper_include('SoapXmlReader');
        $xml = SoapXmlReader::create()->parse($response);

        $result = array();

        //check if response is SearchFlightResponse
        if ($xml->sBody->ServiceRequestResponse) {
            $request_result = & $xml->sBody->ServiceRequestResponse->ServiceRequestResult;

            /*CHECK IF WE HAVE ERRORS*/
            if (get_object_vars($request_result->Errors)) {
                $result['error'] = array(
                    'code' => SoapXmlReader::xml_value($request_result->Errors->Error, 'ErrorCode'),
                    'text' => SoapXmlReader::xml_value($request_result->Errors->Error, 'ErrorText'),
                    'message' => SoapXmlReader::xml_value($request_result->Errors->Error, 'Message'),
                );

                return $result;
            }

            $service_request_result_xml = simplexml_load_string($request_result->asXML());
            $hotel_book_cancel = $service_request_result_xml->xpath('//HotelBookCancelResponse');

            /*RETURN ERROR NO RESULTS FOUND.*/
            if (!$hotel_book_cancel) {
                $result['error'] = array(
                    'code' => 'I0404',
                    'text' => 'No results found.',
                    'message'=>''
                );

                return $result;
            }

            /*GET BOOKING INFO*/
            $hotel_book_cancel = reset($hotel_book_cancel);

            $result = array(
                'cancel_id'=>SoapXmlReader::xml_value($hotel_book_cancel,'BookCancelID'),
                'comment'=>SoapXmlReader::xml_value($hotel_book_cancel,'CancellationComment'),
                'fee'=>SoapXmlReader::xml_value($hotel_book_cancel,'CancellationFee'),
                'status'=>SoapXmlReader::xml_value($hotel_book_cancel,'Status'),
            );
        } else {
            $error = 'Response empty or not SearchFlightResponse';
            throw new \Exception($error);
        }

        return $result;
    }

    public static function parseCheckBookingStatusResponse($response){
        helper_include('SoapXmlReader');
        $xml = SoapXmlReader::create()->parse($response);

        $result = array();

        //check if response is SearchFlightResponse
        if ($xml->sBody->ServiceRequestResponse) {
            $request_result = & $xml->sBody->ServiceRequestResponse->ServiceRequestResult;

            /*CHECK IF WE HAVE ERRORS*/
            if (get_object_vars($request_result->Errors)) {
                $result['error'] = array(
                    'code' => SoapXmlReader::xml_value($request_result->Errors->Error, 'ErrorCode'),
                    'text' => SoapXmlReader::xml_value($request_result->Errors->Error, 'ErrorText'),
                    'message' => SoapXmlReader::xml_value($request_result->Errors->Error, 'Message'),
                );

                return $result;
            }

            $service_request_result_xml = simplexml_load_string($request_result->asXML());
            $hotel_book_info = $service_request_result_xml->xpath('//HotelBookInfoResponse');

            /*RETURN ERROR NO RESULTS FOUND.*/
            if (!$hotel_book_info) {
                $result['error'] = array(
                    'code' => 'I0404',
                    'text' => 'No results found.',
                    'message'=>''
                );

                return $result;
            }

            /*GET BOOKING INFO*/
            $hotel_book_info = reset($hotel_book_info);

            $result = array(
                'status'=>SoapXmlReader::xml_value($hotel_book_info,'Status'),
            );
        } else {
            $error = 'Response empty or not SearchFlightResponse';
            throw new \Exception($error);
        }

        return $result;
    }

} 