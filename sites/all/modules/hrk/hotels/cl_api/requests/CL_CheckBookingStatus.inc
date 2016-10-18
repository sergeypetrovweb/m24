<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 08.11.14
 * Time: 12:45
 */

namespace requests;


use includes\SoapXmlWriter;

class CL_CheckBookingStatus {
    const SOAP_ACTION = 'http://tempuri.org/IDynamicDataService/ServiceRequest';

    private $_session_id;
    private $_segment_id;

    static public function create($session_id, $_segment_id)
    {
        return new CL_CheckBookingStatus($session_id, $_segment_id);
    }

    public function __construct($session_id, $_segment_id)
    {
        $this->_session_id = $session_id;
        $this->_segment_id = $_segment_id;
    }

    public function getRequest()
    {
        if (empty($this->_session_id)) throw new \Exception('Session ID is required');
        if (empty($this->_segment_id)) throw new \Exception('Segment ID is required');

        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('ServiceRequest', array('xmlns' => 'http://tempuri.org/'))
                ->container('rqst', array('xmlns:i' => 'http://www.w3.org/2001/XMLSchema-instance'))
                    ->container('Request', array('xmlns' => '', 'i:type' => 'HotelBookInfoRequest'))
                        ->container('ClientIP', array('i:nil' => 'true'))->end('ClientIP')
                        ->element('SegmentID', $this->_segment_id)
                    ->end('Request')
                ->xml('<RequestType xmlns="">CheckBookingStatus</RequestType>')
                ->xml('<SessionID xmlns="">' . $this->_session_id . '</SessionID>')
                ->xml('<TypeOfService xmlns="">Hotels</TypeOfService>')
                ->end('rqst')
            ->end('ServiceRequest');

        return $xml->getXml();
    }
}