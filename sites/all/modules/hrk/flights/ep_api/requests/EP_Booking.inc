<?php
/**
 * Created by PhpStorm.
 * User: Eugenia
 * Date: 27.09.14
 * Time: 17:08
 */

namespace requests;

use includes\SoapXmlWriter;

class EP_Booking
{
    const SOAP_ACTION = 'http://epowerv5.amadeus.com.tr/WS/BookFlight';

    private $_recommendationID;
    private $_combinationID;
    private $_passengers = array();
    private $_contacts = array();

    public function setRecommendationID($id)
    {
        $this->_recommendationID = $id;
        return $this;
    }

    public function setCombinationID($id)
    {
        $this->_combinationID = $id;
        return $this;
    }

    public function setPassengers($passengers)
    {
        $this->_passengers = $passengers;
        return $this;
    }

    public function setContacts($contacts)
    {
        $this->_contacts = $contacts;
        return $this;
    }


    public function getRequest()
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('BookFlight', array('xmlns' => 'http://epowerv5.amadeus.com.tr/WS'))
            ->container('OTA_AirBookRQ', array('RecommendationID' => $this->_recommendationID, 'CombinationID' => $this->_combinationID))
            ->container('POS')->end('POS');

        $xml->container('TravelerInfo');
        foreach ($this->_passengers as $type => $passengers_by_type) {
            foreach ($passengers_by_type as $index => $passenger) {
                $passenger = (object)$passenger;
                $phone = substr($this->_contacts['phone'], -7);
                $cityCode = str_replace($phone, '', $this->_contacts['phone']);

                $xml->container('AirTraveler', array('PassengerTypeCode'=>strtoupper($type)))
                    ->container('PersonName')
                        ->element('GivenName',$passenger->first_name)
                        ->element('NamePrefix',$passenger->sex)
                        ->element('Surname',$passenger->last_name)
                    ->end('PersonName')
                    ->element('BirthDate', $passenger->birthday)
                    ->container('Telephone', array('CountryCode' => $this->_contacts['code'], 'AreaCityCode' => $cityCode, 'PhoneNumber' => $phone))->end('Telephone')
                    ->xml('<Email EmailType="1">'.$this->_contacts['email'].'</Email>')
                    ->container('Document', array('DocType' => 'DOCS', 'DocID' => $passenger->passport, 'DocIssueCountry' => $passenger->nationality, 'ExpireDate' => $passenger->expire, 'InnerDocType' => 'Passport'))->end('Document')
                    ->end('AirTraveler');
            }
        }
        $xml->end('TravelerInfo');

        $xml->container('Fulfillment')->container('PaymentDetails')->container('PaymentDetail', array('PaymentType'=>'None'))->end('PaymentDetail')->end('PaymentDetails')->end('Fulfillment');

        $xml->container('Ticketing',array('TicketType'=>'BookingOnly'))->end('Ticketing');

        $xml->end('OTA_AirBookRQ')->end('BookFlight');

        return $xml->getXml();
    }
} 