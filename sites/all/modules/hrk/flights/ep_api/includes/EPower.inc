<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 08.09.14
 * Time: 14:19
 */

namespace includes;


use requests\EP_Ping;
use requests\EP_SignOut;

class EPower
{
    private $_params = array(
        'trace' => 1
    );
    /** @var  \SoapClient */
    private $_client;

    private $_request_url;
    private $_client_url;

    private $_login;
    private $_password;

    private $_enable = FALSE; //flag need to check if all configuration settings is set

    public function __construct($mode = '')
    {
        $settings = variable_get('e_power', array('mode' => 'test'));

        if ($settings) {
            $mode = empty($mode) ? $settings['mode'] : $mode;

            $config = isset($settings[$mode]) ? (object)$settings[$mode] : (object)array();

            if ($config) {
                if ($config->request_url && $config->client_url && $config->login && $config->password) {
                    $this->_request_url = $config->request_url;
                    $this->_client_url = $config->client_url;
                    $this->_login = $config->login;
                    $this->_password = $config->password;

                    $this->_setEnable(TRUE);
                }
            }
        }
    }

    public function connect($session = array())
    {
        if($this->_isEnable()){
            $this->_client = new \SoapClient($this->_client_url, $this->_params);

            if ($session) {
                foreach ($session as $name => $value) {
                    foreach ($value as $index => $val) {
                        $this->_client->_cookies[$name][$index] = $val;
                    };
                }
            }
        }
        return $this->_isEnable();
    }

    public function disconnect()
    {
        ep_api_include('EP_SignOut', 'requests');
        $soap_action = 'http://epowerv5.amadeus.com.tr/WS/SignOut';

        $request = new EP_SignOut();

        $request = $this->_Request($request->getRequest(), false);

        $result = 0;

        if ( is_object($this->_client) ) {
            $result = $this->_client->__doRequest($request, $this->_request_url, $soap_action, 1);
        }
        return $result;
    }

    static public function createSession()
    {
        ep_api_include('EP_Ping', 'requests');
        $soap_action = 'http://epowerv5.amadeus.com.tr/WS/Ping';

        $request = new EP_Ping();

        $ep = new EPower();

        if ($ep->connect()) {
            $soap = new \SoapClient($ep->_client_url, $ep->_params);
            $request = $ep->_Request($request->getRequest(), true);

            $soap->__doRequest($request, $ep->_request_url, $soap_action, 1);

            if ($soap->_cookies) {
                $query = db_insert('hrk_ep_sessions');
                $query->fields(array(
                    'created' => REQUEST_TIME,
                    'session' => serialize($soap->_cookies)
                ));

                $sid = $query->execute();

                if ($sid) {
                    $db_session = array(
                        'sid' => $sid,
                        'created' => REQUEST_TIME,
                        'session' => $soap->_cookies
                    );
                }
            }
        }
        if(module_exists('dump')) dump(!empty($db_session) ? $db_session : FALSE, 'Создание сессии');

        return !empty($db_session) ? $db_session : FALSE;
    }

    static public function getSession($sid)
    {
        $query = db_select('hrk_ep_sessions', 's');
        $query->fields('s', array('sid', 'created', 'session'));
        $query->condition('sid', $sid);
        $result = $query->execute();

        foreach ($result as $row) {
            $db_session = array(
                'sid' => $row->sid,
                'created' => $row->created,
                'session' => unserialize($row->session)
            );
        }

        if(module_exists('dump')) dump(!empty($db_session) ? $db_session : FALSE, 'Запрос получения сессии');

        return !empty($db_session) ? $db_session : FALSE;
    }

    static public function deleteSession($sid)
    {
        $query = db_delete('hrk_ep_sessions');
        $query->condition('sid', $sid, (is_array($sid) ? 'IN' : '='));

        return $query->execute();
    }

    public function doRequest($request, $soap_action, $header = true)
    {

      $xml = $this->_doRequest($request, $soap_action, $header = true);

      if (variable_get('test_request_xml_log')) {
        $directory = variable_get('file_public_path') . '/custom_log';
        if (!file_exists($directory)) {
          mkdir($directory, 0777, true);
        }
        $action = array_pop(explode('/', $soap_action));
        file_put_contents($directory . '/' . $action . '_request_' . REQUEST_TIME . '.xml', $request);
        file_put_contents($directory . '/' . $action . '_responce_' . REQUEST_TIME . '.xml', $xml);
      }

      return $xml;
    }

    private function _doRequest($request, $soap_action, $header = true)
    {
        if (!$this->_isEnable()) return FALSE;

        $request = $this->_Request($request, $header);

        return $this->_client->__doRequest($request, $this->_request_url, $soap_action, 1);
    }

    private function _setEnable($state = TRUE)
    {
        $this->_enable = $state;
    }

    private function _isEnable()
    {
        return $this->_enable;
    }

    private function _Request($request, $header)
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        //add wrapper xml

        $xml->container('soap:Envelope', array(
            'xmlns:xsi' => 'http://www.w3.org/2001/XMLSchema-instance',
            'xmlns:xsd' => 'http://www.w3.org/2001/XMLSchema',
            'xmlns:soap' => 'http://schemas.xmlsoap.org/soap/envelope/'
        ));

        //add header
        if ($header) {
            $xml->container('soap:Header');

            $xml->container('AuthenticationSoapHeader', array('xmlns' => 'http://epowerv5.amadeus.com.tr/WS'))
                ->element('WSUserName', $this->_login)
                ->element('WSPassword', $this->_password)
                ->end('AuthenticationSoapHeader');

            $xml->end('soap:Header');
        }

        //add body
        $xml->container('soap:Body')->xml($request)->end('soap:Body');

        //end wrapper
        $xml->end('soap:Envelope');

        return $xml->getXml();
    }

}