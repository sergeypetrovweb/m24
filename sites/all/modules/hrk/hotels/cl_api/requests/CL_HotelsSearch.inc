<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 13.10.14
 * Time: 17:54
 */

namespace requests;


use includes\SoapXmlWriter;

class CL_HotelsSearch {

    const SOAP_ACTION = 'http://tempuri.org/IDynamicDataService/ServiceRequest';

    private $_session_id;
    private $_currency = '';
    private $_country_code = '';
    private $_details = 'Low';
    private $_location_id = 0;
    private $_check_in;
    private $_check_out;
    private $_nights = 1;
    private $_rooms = array();

    static public function create($session_id, $details = 'Low')
    {
        return new CL_HotelsSearch($session_id, $details);
    }

    public function __construct($session_id, $details = 'Low')
    {
        $this->_session_id = $session_id;
        $this->_details = $details;
        $this->_currency = currency_get_active_currency();
    }

    public function setCurrency($currency){
        $this->_currency = $currency;
        return $this;
    }

    public function setCountry($code){
        $this->_country_code = $code;
        return $this;
    }

    public function setLocationID($location_id){
        $this->_location_id = $location_id;
        return $this;
    }

    public function setDates($check_in,$check_out){
        $this->_check_in = strtotime($check_in);
        $this->_check_out = strtotime($check_out);

        $date_check_in = new \DateTime($check_in);
        $date_check_out = new \DateTime($check_out);

        $this->_nights = $date_check_out->diff($date_check_in)->format("%a");

        return $this;
    }

    public function setRooms($rooms){
        $this->_rooms = $rooms;
        return $this;
    }

    public function getRequest()
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('ServiceRequest', array('xmlns' => 'http://tempuri.org/'))
                ->container('rqst',array('xmlns:i'=>'http://www.w3.org/2001/XMLSchema-instance'))
                    ->container('Request', array('i:type' => 'HotelsServiceSearchRequest', 'xmlns' => ''))
                        ->container('ClientIP', array('i:nil' => 'true'))->end('ClientIP')
                        ->element('DesiredResultCurrency', strtoupper('rub'))
                        ->element('Residency',$this->_country_code)
                        ->element('CheckIn', date('Y-m-d\TH:i:s', $this->_check_in))
                        ->element('CheckOut', date('Y-m-d\TH:i:s', $this->_check_out))
                        ->container('ContractIds',array('xmlns:a'=>'http://schemas.microsoft.com/2003/10/Serialization/Arrays'))->end('ContractIds')
                        ->element('DetailLevel', $this->_details)
                        ->element('ExcludeHotelDetails', 'false')
                        ->container('HotelIds',array('xmlns:a'=>'http://schemas.microsoft.com/2003/10/Serialization/Arrays'))->end('HotelIds')
                        ->element('HotelLocation', $this->_location_id)
                        ->element('IncludeCityTax', 'false')
                        ->element('Nights', $this->_nights)
                        ->container('Rooms');

                        foreach($this->_rooms as $room){
                            $xml->container('HotelRoomRequest')
                                    ->element('AdultsCount', $room['adt']);

                            if(!empty($room['chd'])){
                                $xml->container('KidsAges', array('xmlns:d8p1' => 'http://schemas.microsoft.com/2003/10/Serialization/Arrays'));
                                for ($i = 1; $i <= $room['chd']; $i++) {
                                    $xml->element('d8p1:int', $room['age']);
                                }
                                $xml->end('KidsAges');
                            }else{
                                $xml->container('KidsAges', array('xmlns:d8p1' => 'http://schemas.microsoft.com/2003/10/Serialization/Arrays'))->end('KidsAges');
                            }

                            $xml->end('HotelRoomRequest');
                        }

                    $xml->end('Rooms')
                        ->container('SupplierIds', array('xmlns:a'=>'http://schemas.microsoft.com/2003/10/Serialization/Arrays'))->end('SupplierIds')
                    ->end('Request')
                    ->xml('<RequestType xmlns="">Search</RequestType>')
                    ->xml('<SessionID xmlns="">'.$this->_session_id.'</SessionID>')
                    ->xml('<TypeOfService xmlns="">Hotels</TypeOfService>')
                ->end('rqst')
            ->end('ServiceRequest');

        return $xml->getXml();
    }

}