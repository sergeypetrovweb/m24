<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 29.09.14
 * Time: 19:12
 */

namespace requests;


use includes\SoapXmlWriter;

class Ep_LCC
{
    const SOAP_ACTION = 'http://epowerv5.amadeus.com.tr/WS/GetRequiredParametersForLCC';

    private $_recommendationID;
    private $_combinationID;

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

    public function getRequest()
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('GetRequiredParametersForLCC', array('xmlns' => 'http://epowerv5.amadeus.com.tr/WS'))
                ->container('RequiredParametersRQ', array('RecommendationID' => $this->_recommendationID, 'CombinationID' => $this->_combinationID))->end('RequiredParametersRQ')
            ->end('GetRequiredParametersForLCC');

        return $xml->getXml();
    }
}

