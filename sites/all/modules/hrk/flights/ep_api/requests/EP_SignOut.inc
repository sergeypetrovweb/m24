<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 08.09.14
 * Time: 17:38
 */

namespace requests;


use includes\SoapXmlWriter;

class EP_SignOut
{

    public function getRequest()
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();
        $xml->container('SignOut', array('xmlns' => 'http://epowerv5.amadeus.com.tr/WS'))->end('SignOut');
        return $xml->getXml();
    }
} 