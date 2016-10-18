<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 01.10.14
 * Time: 2:07
 */

namespace requests;


use includes\SoapXmlWriter;

class EP_TicketReference
{

    const SOAP_ACTION = 'http://epowerv5.amadeus.com.tr/WS/CreateTicket';

    private $_reference_number;

    public function setReferenceNumber($number){
        $this->_reference_number = $number;
        return $this;
    }

    public function getRequest()
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('CreateTicket', array('xmlns' => 'http://epowerv5.amadeus.com.tr/WS'))
                ->container('OTA_AirBookRQ', array('ReferenceNumber' => $this->_reference_number, 'ControlNumber' => $this->_generateControlNumber()))
                ->end('OTA_AirBookRQ')
            ->end('CreateTicket');

        return $xml->getXml();
    }

    private function _generateControlNumber()
    {
        $configuration = (object)variable_get('e_power', array());
        $mode = $configuration->mode;
        $mode_option = $configuration->$mode;
        $secure_code = $mode_option['secure_code'];

        return base64_encode(sha1($this->_reference_number . $secure_code, true));
    }

} 