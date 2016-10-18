<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 08.10.14
 * Time: 12:01
 */

namespace requests;


use includes\SoapXmlWriter;

class EP_Cancel
{

    const SOAP_ACTION = 'http://epowerv5.amadeus.com.tr/WS/Cancel';

    private $_context_ID = '';
    private $_verification_surname = '';

    public function setContextID($context_id){
        $this->_context_ID = $context_id;
        return $this;
    }

    public function setVerificationSurName($surname){
        $this->_verification_surname = $surname;
        return $this;
    }

    public function getRequest()
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('Cancel', array('xmlns' => 'http://epowerv5.amadeus.com.tr/WS'))
            ->container('OTA_CancelRQ',
                array(
                    'xmlns:xsi' => 'http://www.w3.org/2001/XMLSchema-instance',
                    'xmlns:xsd' => 'http://www.w3.org/2001/XMLSchema',
                    'Version' => 0,
                    'CancelType' => 'Initiate'
                ))->container('BookingReferenceID',array('Type'=>'F','ID_Context'=>$this->_context_ID))->end('BookingReferenceID')
                    ->container('Verification')
                        ->container('PersonName')
                            ->element('Surname',strtolower($this->_verification_surname))
                        ->end('PersonName')
                    ->end('Verification')
            ->end('OTA_CancelRQ')
            ->end('Cancel');

        return $xml->getXml();
    }
}