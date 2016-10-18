<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 02.10.14
 * Time: 14:04
 */

namespace requests;

use includes\SoapXmlWriter;

class EP_CreateTicket {

    const SOAP_ACTION = 'http://epowerv5.amadeus.com.tr/WS/CreateTicket';

    private $_context_id;
    private $_passengers = array();

    public function setPassengers($passengers)
    {
        $this->_passengers = $passengers;
        return $this;
    }

    public function setContentID($contentID)
    {
        $this->_context_id = $contentID;
        return $this;
    }


    public function getRequest()
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('CreateTicket',array('xmlns'=>'http://epowerv5.amadeus.com.tr/WS'))
                ->container('OTA_AirBookRQ')
                    ->container('BookingReferenceID',array('ID_Context'=>$this->_context_id))->end('BookingReferenceID')
                        ->container('TravelerInfo');
                   foreach ($this->_passengers as $type => $passengers_by_type) {
                       foreach ($passengers_by_type as $index => $passenger) {
                           $passenger = (object)$passenger;
                           $xml->container('AirTraveler', array('PassengerTypeCode'=>strtoupper($type)))
                                    ->container('PersonName')
                                       ->element('GivenName',$passenger->first_name)
                                       ->element('NamePrefix',$passenger->sex)
                                       ->element('Surname',$passenger->last_name)
                                    ->end('PersonName')
                                    ->element('BirthDate', $passenger->birthday)
                                    ->container('Document', array('DocType' => 'DOCS', 'DocID' => $passenger->document['id'], 'DocIssueCountry' => $passenger->document['country'], 'ExpireDate' => $passenger->document['expire'], 'InnerDocType' => 'Passport'))->end('Document')
                               ->end('AirTraveler');
                       }
                   }
                    $xml->end('TravelerInfo')
                ->end('OTA_AirBookRQ')
            ->end('CreateTicket');

        return $xml->getXml();
    }
}
