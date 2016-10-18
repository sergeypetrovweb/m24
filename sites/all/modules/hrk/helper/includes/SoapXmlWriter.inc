<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 09.09.14
 * Time: 14:41
 */

namespace includes;


class SoapXmlWriter
{

    private $_xml_writer;

    public function __construct($start_element = false, $version = '1.0', $encoding = null)
    {
        $this->_xml_writer = new \XMLWriter();
        $this->_xml_writer->openMemory();

        if (!empty($start_element)) {
            $this->_xml_writer->startDocument($version, $encoding);
        }
        return $this;
    }

    public function container($container, $attributes = array())
    {
        $this->_xml_writer->startElement(trim($container));

        if ($attributes) {
            foreach ($attributes as $name => $value) {
                $this->_xml_writer->writeAttribute(trim($name), $value);
            }
        }
        return $this;
    }

    public function end($string = '')
    {
        $this->_xml_writer->endElement();
        return $this;
    }

    public function element($name, $content = null, $attributes = array())
    {
        $this->_xml_writer->writeElement(trim($name), $content);

            foreach ($attributes as $name => $value) {
                $this->_xml_writer->writeAttribute(trim($name), $value);
            }

        return $this;
    }

    public function xml($xml)
    {
        $this->_xml_writer->writeRaw($xml);
        return $this;
    }

    public function getXml()
    {
        return $this->_xml_writer->outputMemory();
    }
} 