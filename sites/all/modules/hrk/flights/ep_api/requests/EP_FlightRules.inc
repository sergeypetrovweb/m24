<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 26.09.14
 * Time: 17:43
 */

namespace requests;


use includes\SoapXmlWriter;

class EP_FlightRules
{

    const SOAP_ACTION = 'http://epowerv5.amadeus.com.tr/WS/GetFlightRules';

    private $_rec_id = null;
    private $_com_id = null;
    private $_type = 'ADT';

    public function setRecommendationID($rec_id)
    {
        $this->_rec_id = $rec_id;
        return $this;
    }

    public function setCombinationID($com_id)
    {
        $this->_com_id = $com_id;
        return $this;
    }

    public function setPassengerType($type)
    {
        $this->_type = $type;
        return $this;
    }

    public function getRequest()
    {

        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();
        $xml->container('GetFlightRules', array('xmlns' => 'http://epowerv5.amadeus.com.tr/WS'))
                ->container('OTA_AirRulesRQ', array('RecommendationID' => $this->_rec_id, 'CombinationID' => $this->_com_id, 'PassengerType' => $this->_type))->end('GetFlightRules')
            ->end('GetFlightRules');

        return $xml->getXml();
    }
}
