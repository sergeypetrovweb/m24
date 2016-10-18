<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 12.10.14
 * Time: 13:22
 */

namespace requests;


use includes\SoapXmlWriter;

class CL_Login
{

    const SOAP_ACTION = 'http://tempuri.org/IDynamicDataService/ServiceRequest';

    private $_user_name = '';
    private $_password = '';

    static public function create($user_name, $password){
        return new CL_Login($user_name, $password);
    }

    public function __construct($user_name, $password)
    {
        $this->_user_name = $user_name;
        $this->_password = $password;
    }


    public function getRequest()
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('ServiceRequest', array('xmlns' => 'http://tempuri.org/'))
                ->container('rqst',array('xmlns:i'=>'http://www.w3.org/2001/XMLSchema-instance'))
                    ->container('Credentials',array('xmlns'=>''))
                        ->element('Password',$this->_password)
                        ->element('UserName',$this->_user_name)
                    ->end('Credentials')
                    ->xml('<RequestType xmlns="">Login</RequestType>')
                    ->xml('<TypeOfService xmlns="">Unknown</TypeOfService>')
                ->end('rqst')
            ->end('ServiceRequest');

        return $xml->getXml();
    }
}
