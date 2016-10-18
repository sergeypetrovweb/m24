<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 23.10.14
 * Time: 16:35
 */

namespace requests;

use includes\SoapXmlWriter;

class CL_BookingCreditCard {

    const SOAP_ACTION = 'http://tempuri.org/IDynamicDataService/ServiceRequest';

    private $_session_id;
    private $_hotel_id;
    private $_package_id;
    private $_rooms;
    private $_price;
    private $_credit_card;


    static public function create($session_id, $hotel_id, $package_id, $rooms, $price, $credit_card)
    {
        return new CL_BookingCreditCard($session_id, $hotel_id, $package_id, $rooms, $price, $credit_card);
    }

    public function __construct($session_id, $hotel_id, $package_id, $rooms, $price, $credit_card)
    {
        $this->_session_id = $session_id;
        $this->_hotel_id = $hotel_id;
        $this->_package_id = $package_id;
        $this->_rooms = $rooms;
        $this->_price = $price;
        $this->_credit_card = $credit_card;
    }

    public function getRequest()
    {
        if (empty($this->_session_id)) throw new \Exception('Session ID is required');
        if (empty($this->_hotel_id)) throw new \Exception('Hotel ID is required');
        if (empty($this->_package_id)) throw new \Exception('Package ID is required');
        if (empty($this->_rooms)) throw new \Exception('Rooms is required');
        if (empty($this->_price)) throw new \Exception('Price is required');
        if (empty($this->_credit_card)) throw new \Exception('Credit card is required');

        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $pax_id =  $this->gen_uuid();
        $first_room = reset($this->_rooms);

        $xml->container('ServiceRequest', array('xmlns' => 'http://tempuri.org/'))
                ->container('rqst', array('xmlns:i' => 'http://www.w3.org/2001/XMLSchema-instance'))
                    ->container('Request', array('i:type' => 'HotelBookRequest', 'xmlns' => ''))
                        ->container('ClientIP', array('i:nil'=>'true'))->end('ClientIP')
                        ->element('BookingPrice', $this->_price)
                        ->container('Card', array('xmlns:d6p1'=>'http://schemas.datacontract.org/2004/07/IsuBe.Public.Enteties.Payment'))
                            ->element('d6p1:AddressLine', str_replace('_', ' ', $this->_credit_card['address']))
                            ->element('d6p1:CVV', $this->_credit_card['code'])
                            ->element('d6p1:CardNumber', $this->_credit_card['number'])
                            ->element('d6p1:CardType', $this->_credit_card['type'])
                            ->element('d6p1:City', $this->_credit_card['city'])
                            ->element('d6p1:Country', $this->_credit_card['country'])
                            ->element('d6p1:ExpireDate', date('Y-m-d\T00:00:00', strtotime($this->_credit_card['expire'])))
                            ->element('d6p1:HolderName', $this->_credit_card['first_name'].' '.$this->_credit_card['second_name'])
                            ->element('d6p1:ZipCode', $this->_credit_card['zip_code'].' '.$this->_credit_card['zip_code'])
                        ->end('Card')
                        ->element('HotelID', $this->_hotel_id)
                        ->element('InternalAgentRef1', '')
                        ->element('InternalAgentRef2', '')
                        ->element('LeadPaxId', $pax_id)
                        ->element('LeadPaxRoomId', $first_room['id'])
                        ->element('PackageID', $this->_package_id)
                        ->container('Passengers');

                        foreach ($this->_rooms as $room) {
                            foreach ($room['guests'] as $guests) {

                                foreach ($guests as $guest) {
                                    $pax_id = (!isset($pax_id)) ? $this->gen_uuid() : $pax_id;

                                    $xml->container('CustomerInfo')
                                            ->container('Address');
                                                if (!empty($guest['address'])) {
                                                    $xml->element('AddressLine', $guest['address']);
                                                }
                                                if (!empty($guest['city'])) {
                                                    $xml->element('CityName', $guest['city']);
                                                }

                                                $xml->container('CountryName')->end('CountryName');

                                                if (!empty($guest['postal_code'])) {
                                                    $xml->element('PostalCode', $guest['postal_code']);
                                                }
                                        $xml->end('Address')
                                            ->element('Allocation', $room['id'])
                                            ->container('Email');
                                                if (!empty($guest['email'])) {
                                                    $xml->element('Value', $guest['email']);
                                                }else{
                                                    $xml->container('Value',array('i:nil'=>'true'))->end('Value');
                                                }
                                        $xml->end('Email')
                                            ->element('Id',$pax_id)
                                            ->container('PersonDetails')
                                                ->container('Name')
                                                    ->element('GivenName',$guest['first_name'])
                                                    ->element('NamePrefix',$guest['sex'])
                                                    ->element('Surname',$guest['last_name'])
                                                ->end('Name')
                                                ->element('Type',$guest['type'])
                                            ->end('PersonDetails')
                                            ->container('Telephone');
                                                if(!empty($guest['phone'])){
                                                    $xml->element('PhoneNumber',$guest['phone']);
                                                }else{
                                                    $xml->container('PhoneNumber', array('i:nil' => 'true'))->end('PhoneNumber');
                                                }
                                        $xml->end('Telephone')
                                        ->end('CustomerInfo');
                                    unset($pax_id);
                                }
                            }
                        }
                
                        $xml->end('Passengers')
                            ->container('RoomsRemarks',array('xmlns:d6p1'=>'http://schemas.microsoft.com/2003/10/Serialization/Arrays'));

                            foreach ($this->_rooms as $room) {
                                $xml->element('d6p1:Key',$room['id']);
                                if(!empty($room['remark'])){
                                    $xml->element('d6p1:Value',check_plain($room['remark']));
                                }else{
                                    $xml->container('d6p1:Value',array('i:nil'=>'true'))->end();
                                }
                            }

                        $xml->end('RoomsRemarks')
                        ->element('SelectedPaymentMethod','Cash')
                    ->end('Request')
                    ->xml('<RequestType xmlns="">Book</RequestType>')
                    ->xml('<SessionID xmlns="">' . $this->_session_id . '</SessionID>')
                    ->xml('<TypeOfService xmlns="">Hotels</TypeOfService>')
                ->end('rqst')
            ->end('ServiceRequest');

        return $xml->getXml();
    }

    public function gen_uuid() {
        return sprintf( '%04x%04x-%04x-%04x-%04x-%04x%04x%04x',
            // 32 bits for "time_low"
            mt_rand( 0, 0xffff ), mt_rand( 0, 0xffff ),

            // 16 bits for "time_mid"
            mt_rand( 0, 0xffff ),

            // 16 bits for "time_hi_and_version",
            // four most significant bits holds version number 4
            mt_rand( 0, 0x0fff ) | 0x4000,

            // 16 bits, 8 bits for "clk_seq_hi_res",
            // 8 bits for "clk_seq_low",
            // two most significant bits holds zero and one for variant DCE1.1
            mt_rand( 0, 0x3fff ) | 0x8000,

            // 48 bits for "node"
            mt_rand( 0, 0xffff ), mt_rand( 0, 0xffff ), mt_rand( 0, 0xffff )
        );
    }
}
//<Card xmlns:d6p1="http://schemas.datacontract.org/2004/07/IsuBe.Public.Enteties.Payment">
//						<d6p1:AddressLine>sad fasdf</d6p1:AddressLine>
//						<d6p1:CVV>333</d6p1:CVV>
//						<d6p1:CardNumber>4111111111111111</d6p1:CardNumber>
//						<d6p1:CardType>Visa</d6p1:CardType>
//						<d6p1:City>tel aviv</d6p1:City>
//						<d6p1:Country>IL</d6p1:Country>
//						<d6p1:ExpireDate>2016-01-01T00:00:00</d6p1:ExpireDate>
//						<d6p1:HolderName>asdfa dfas</d6p1:HolderName>
//						<d6p1:ZipCode>12345</d6p1:ZipCode>
//					</Card>