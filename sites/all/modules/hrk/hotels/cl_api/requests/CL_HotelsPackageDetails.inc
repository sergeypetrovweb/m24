<?php

namespace requests;

use includes\SoapXmlWriter;

class CL_HotelsPackageDetails
{

    const SOAP_ACTION = 'http://tempuri.org/IDynamicDataService/ServiceRequest';

    private $_session_id;
    private $_include_package;
    private $_hotels_id;
    private $_package_id = '00000000-0000-0000-0000-000000000000';

    static public function create($session_id, $include_package_details = FALSE)
    {
        return new CL_HotelsPackageDetails($session_id, $include_package_details);
    }

    public function __construct($session_id, $include_package_details = FALSE)
    {
        $this->_session_id = $session_id;
        $this->_include_package = $include_package_details;
    }

    public function setHotelID($hotel_id)
    {
        $this->_hotels_id = $hotel_id;
        return $this;
    }

    public function setPackageID($package_id)
    {
        $this->_package_id = $package_id;
        return $this;
    }

    public function getRequest()
    {
        if (empty($this->_session_id)) throw new \Exception('Session ID is required');
        if (empty($this->_hotels_id)) throw new \Exception('Hotel ID is required');

        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('ServiceRequest', array('xmlns' => 'http://tempuri.org/'))
                ->container('rqst', array('xmlns:i' => 'http://www.w3.org/2001/XMLSchema-instance'))
                    ->container('Request', array('xmlns' => '', 'i:type' => 'HotelsSupplierDetailsRequest'))
                        ->container('ClientIP', array('i:nil' => 'true'))->end('ClientIP')
                        ->element('HotelID', $this->_hotels_id)
                        ->element('IncludePackageDetails', ($this->_include_package) ? 1 : 0)
                        ->element('PackageID', $this->_package_id)
                        ->element('SupplierID', 0)
                    ->end('Request')
                    ->xml('<RequestType xmlns="">GetAdditionalDetails</RequestType>')
                    ->xml('<SessionID xmlns="">' . $this->_session_id . '</SessionID>')
                    ->xml('<TypeOfService xmlns="">Hotels</TypeOfService>')
                ->end('rqst')
            ->end('ServiceRequest');

        return $xml->getXml();
    }
}