<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 02.10.14
 * Time: 12:53
 */

namespace requests;


use includes\SoapXmlWriter;

class EP_LTD
{

    const SOAP_ACTION = 'http://epowerv5.amadeus.com.tr/WS/GetLastTicketingDate';

    private $_pnr = 0;

    public function setPNR($pnr)
    {
        $this->_pnr = $pnr;
        return $this;
    }

    public function setVerName($surname)
    {
        $this->_ver_name = $surname;
        return $this;
    }

    public function getRequest()
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('GetLastTicketingDate', array('xmlns' => 'http://epowerv5.amadeus.com.tr/WS','PnrNo'=>$this->_pnr))->end('GetLastTicketingDate');

        return $xml->getXml();
    }
}

