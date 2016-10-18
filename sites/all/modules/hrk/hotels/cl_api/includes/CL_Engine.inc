<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 08.09.14
 * Time: 14:19
 */

namespace includes;


use requests\CL_Login;

class CL_Engine
{
    private $_params = array(
        'trace' => 1
    );
    /** @var  \SoapClient */
    private $_client;

    private $_request_url;

    private $_login;
    private $_password;

    private $_enable = FALSE; //flag need to check if all configuration settings is set


    public function __construct($mode = '')
    {
        $settings = variable_get('carsolize', array('mode' => 'test'));

        if ($settings) {
            $mode = empty($mode) ? $settings['mode'] : $mode;

            $config = isset($settings[$mode]) ? (object)$settings[$mode] : (object)array();

            if ($config) {
                if ($config->request_url && $config->login && $config->password) {
                    $this->_request_url = $config->request_url;
                    $this->_login = $config->login;
                    $this->_password = $config->password;

                    $this->_setEnable(TRUE);
                }
            }
        }
    }

    public function connect()
    {
        return $this->_isEnable();
    }

    static public function createSession($mode = '')
    {
        $cl = new CL_Engine($mode);
        if ($cl->connect()) {
            cl_api_include('CL_Login', 'requests');
            $response = $cl->_doRequest(CL_Login::create($cl->_login, $cl->_password)->getRequest(), CL_Login::SOAP_ACTION);

            if ($response) {
                helper_include('SoapXmlReader');
                $response = SoapXmlReader::create()->parse($response);
                $session_id = NULL;

                if(!empty($response->sBody->ServiceRequestResponse->ServiceRequestResult)){
                    $session_id =  SoapXmlReader::xml_value($response->sBody->ServiceRequestResponse->ServiceRequestResult, 'SessionID');
                }

                if ($session_id) {
                    $query = db_insert('hrk_cl_sessions');
                    $query->fields(array(
                        'created' => REQUEST_TIME,
                        'session' => $session_id
                    ));

                    $sid = $query->execute();

                    if ($sid) {
                        $db_session = array(
                            'sid' => $sid,
                            'created' => REQUEST_TIME,
                            'session' => $session_id
                        );
                    }
                }
            }
        }

        return !empty($db_session) ? $db_session : FALSE;
    }

    static public function getSession($sid)
    {
        $query = db_select('hrk_cl_sessions', 's');
        $query->fields('s', array('sid', 'created', 'session'));
        $query->condition('sid', $sid);
        $result = $query->execute();

        foreach ($result as $row) {
            $db_session = array(
                'sid' => $row->sid,
                'created' => $row->created,
                'session' => $row->session
            );
        }

        return !empty($db_session) ? $db_session : FALSE;
    }

    static public function deleteSession($sid)
    {
        $query = db_delete('hrk_cl_sessions');
        $query->condition('sid', $sid, (is_array($sid) ? 'IN' : '='));

        return $query->execute();
    }

    public function doRequest($request, $soap_action)
    {
        return $this->_doRequest($request, $soap_action);
    }

    private function _doRequest($request, $soap_action)
    {
        if (!$this->_isEnable()) return FALSE;

        $request = $this->_Request($request);

        $headers = array(
            "Content-type: text/xml;charset=\"utf-8\"",
            "Accept: text/xml",
            "Cache-Control: no-cache",
            "SOAPAction: " . $soap_action . "",
            "Pragma: no-cache",
            "Content-length: " . strlen($request)

        );

        $ch = curl_init();
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
        curl_setopt($ch, CURLOPT_URL, $this->_request_url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
        curl_setopt($ch, CURLOPT_TIMEOUT, 120);
        curl_setopt($ch, CURLOPT_POST, true);
        curl_setopt($ch, CURLOPT_POSTFIELDS, $request); // the SOAP request
        curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);

        $response = curl_exec($ch);
        curl_close($ch);

        return $response;
    }

    private function _setEnable($state = TRUE)
    {
        $this->_enable = $state;
    }

    private function _isEnable()
    {
        return $this->_enable;
    }

    private function _Request($request)
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        //add wrapper xml

        $xml->container('s:Envelope', array('xmlns:s' => 'http://schemas.xmlsoap.org/soap/envelope/'));
        //add body
        $xml->container('s:Body')->xml($request)->end('s:Body');

        //end wrapper
        $xml->end('s:Envelope');

        return $xml->getXml();
    }
}