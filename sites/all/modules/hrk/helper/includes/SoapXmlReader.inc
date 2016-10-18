<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 10.09.14
 * Time: 16:10
 */

namespace includes;


class SoapXmlReader
{
    static public function create()
    {
        return new SoapXmlReader();
    }

    static public function parse($response)
    {
        $xmlString = preg_replace("/(<\/?)(\w+):([^>]*>)/", "$1$2$3", $response);
        $doc = new \DOMDocument();
        $doc->loadXML($xmlString);
        return simplexml_load_string($doc->saveXML());
    }

    static public function xml_attr(\SimpleXMLElement $object, $attribute, $default = FALSE)
    {
        if (isset($object[$attribute])) $default = (string)$object[$attribute];
        return $default;
    }

    static public function xml_value(\SimpleXMLElement $object, $name, $default = FALSE)
    {
        if (isset($object->$name)) $default = (string)$object->$name->__toString();
        return $default;
    }
}