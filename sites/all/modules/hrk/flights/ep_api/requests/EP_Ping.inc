<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 09.09.14
 * Time: 15:29
 */

namespace requests;


use includes\SoapXmlWriter;

class EP_Ping{

   public function getRequest(){
       helper_include('SoapXmlWriter');

       $xml = new SoapXmlWriter();
       $xml->container('Ping',array('xmlns'=>'http://epowerv5.amadeus.com.tr/WS'))
                ->container('OTA_PingRQ')
                    ->element('EchoData','Ping Data')
                ->end('OTA_PingRQ')
           ->end('Ping');

       return $xml->getXml();
   }
} 