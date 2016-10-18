<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 24.10.14
 * Time: 18:09
 */

namespace requests;


use includes\SoapXmlWriter;

class CL_HotelPaymentReference
{
    const SOAP_ACTION = 'http://tempuri.org/IDynamicDataService/ServiceRequest';

    private $_session_id;
    private $_hotels_id;
    private $_package_id;
    private $_cancellation = FALSE;

    static public function create($session_id, $hotel_id, $package_id, $include_cancellation = FALSE)
    {
        return new CL_HotelPaymentReference($session_id, $hotel_id, $package_id, $include_cancellation);
    }

    public function __construct($session_id, $hotel_id, $package_id, $include_cancellation = FALSE)
    {
        $this->_session_id = $session_id;
        $this->_hotels_id = $hotel_id;
        $this->_package_id = $package_id;
        $this->_cancellation = $include_cancellation;
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
                    ->container('Request', array('xmlns' => '', 'i:type' => 'HotelPaymentPreferencesRequest'))
                        ->container('ClientIP', array('i:nil' => 'true'))->end('ClientIP')
                        ->element('HotelID', $this->_hotels_id)
                        ->element('IncludeCancellationPolicy', ($this->_cancellation) ? 'true' : 'false')
                        ->element('PackageID', $this->_package_id)
                    ->end('Request')
                    ->xml('<RequestType xmlns="">GetPaymentPreferences</RequestType>')
                    ->xml('<SessionID xmlns="">' . $this->_session_id . '</SessionID>')
                    ->xml('<TypeOfService xmlns="">Hotels</TypeOfService>')
                ->end('rqst')
            ->end('ServiceRequest');

        return $xml->getXml();
    }
}
