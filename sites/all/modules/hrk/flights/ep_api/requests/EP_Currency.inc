<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 10.09.14
 * Time: 15:51
 */

namespace requests;


use includes\SoapXmlWriter;

class EP_Currency
{
    const SOAP_ACTION = 'http://epowerv5.amadeus.com.tr/WS/CurrencyConversion';

    public function getRequest($from, $to, $amount)
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('CurrencyConversion', array('xmlns' => 'http://epowerv5.amadeus.com.tr/WS'))
                ->container('OTA_CurrencyConversionRQ', array(
                    'FromCurrency'=>$from,
                    'ToCurrency'=>$to,
                    'Amount'=>$amount
                ))
                ->end('OTA_CurrencyConversionRQ')
            ->end('CurrencyConversion');

        return $xml->getXml();
    }
}
