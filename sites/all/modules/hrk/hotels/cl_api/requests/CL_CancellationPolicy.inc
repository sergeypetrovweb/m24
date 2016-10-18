<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 23.10.14
 * Time: 10:49
 */

namespace requests;


use includes\SoapXmlWriter;

class CL_CancellationPolicy
{
    const SOAP_ACTION = 'http://tempuri.org/IDynamicDataService/ServiceRequest';

    private $_session_id;
    private $_hotels_id;
    private $_package_id;

    static public function create($session_id, $hotel_id, $package_id)
    {
        return new CL_CancellationPolicy($session_id, $hotel_id, $package_id);
    }

    public function __construct($session_id, $hotel_id, $package_id)
    {
        $this->_session_id = $session_id;
        $this->_hotels_id = $hotel_id;
        $this->_package_id = $package_id;
    }

    public function getRequest()
    {
        if (empty($this->_session_id)) throw new \Exception('Session ID is required');
        if (empty($this->_hotels_id)) throw new \Exception('Hotel ID is required');
        if (empty($this->_package_id)) throw new \Exception('Package ID is required');

        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('ServiceRequest', array('xmlns' => 'http://tempuri.org/'))
                ->container('rqst', array('xmlns:i' => 'http://www.w3.org/2001/XMLSchema-instance'))
                    ->container('Request', array('xmlns' => '', 'i:type' => 'HotelCancellationPolicyRequest'))
                        ->container('ClientIP', array('i:nil' => 'true'))->end('ClientIP')
                        ->element('HotelID', $this->_hotels_id)
                        ->element('PackageID', $this->_package_id)
                    ->end('Request')
                    ->xml('<RequestType xmlns="">GetCancelationPolicy</RequestType>')
                    ->xml('<SessionID xmlns="">' . $this->_session_id . '</SessionID>')
                    ->xml('<TypeOfService xmlns="">Hotels</TypeOfService>')
                ->end('rqst')
            ->end('ServiceRequest');

        return $xml->getXml();
    }
}