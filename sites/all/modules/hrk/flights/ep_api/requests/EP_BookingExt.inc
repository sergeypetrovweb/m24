<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 30.09.14
 * Time: 17:12
 */

namespace requests;


use includes\SoapXmlWriter;

class EP_BookingExt {

    const SOAP_ACTION = 'http://epowerv5.amadeus.com.tr/WS/BookFlight';

    private $_recommendationID;
    private $_combinationID;
    private $_passengers = array();
    private $_contacts = array();
    private $_credit_card = array();
    private $_lcc = array();
    private $_billing = array();

    public function setRecommendationID($id)
    {
        $this->_recommendationID = $id;
        return $this;
    }

    public function setCombinationID($id)
    {
        $this->_combinationID = $id;
        return $this;
    }

    public function setPassengers($passengers)
    {
        $this->_passengers = $passengers;
        return $this;
    }

    public function setContacts($contacts)
    {
        $this->_contacts = $contacts;
        return $this;
    }

    public function setCreditCard($credit_card)
    {
        $this->_credit_card = $credit_card;
        return $this;
    }

    public function setLCC($lcc)
    {
        $this->_lcc = $lcc;
        return $this;
    }

    public function setBilling($billing)
    {
        $this->_billing = $billing;
        return $this;
    }


    public function getRequest()
    {
        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('BookFlight', array('xmlns' => 'http://epowerv5.amadeus.com.tr/WS'))
            ->container('OTA_AirBookRQ', array('RecommendationID' => $this->_recommendationID, 'CombinationID' => $this->_combinationID))
            ->container('POS')->end('POS');

        $xml->container('TravelerInfo');
        $bags_state = FALSE;
        foreach ($this->_passengers as $type => $passengers_by_type) {
            foreach ($passengers_by_type as $index => $passenger) {
                $passenger = (object)$passenger;
                $phone = substr($this->_contacts['phone'], -7);
                $cityCode = str_replace($phone, '', $this->_contacts['phone']);
                $bags = !empty($this->_lcc['NumberOfBags'])?$this->_lcc['NumberOfBags']:0;

                $xml->container('AirTraveler', array('PassengerTypeCode'=>strtoupper($type)))
                        ->container('PersonName')
                            ->element('GivenName',$passenger->first_name)
                            ->element('NamePrefix',$passenger->sex)
                            ->element('Surname',$passenger->last_name)
                        ->end('PersonName')
                        ->element('BirthDate', $passenger->birthday)
                        ->container('Telephone', array('CountryCode' => $this->_contacts['code'], 'AreaCityCode' => $cityCode, 'PhoneNumber' => $phone))->end('Telephone')
                        ->xml('<Email EmailType="1">'.$this->_contacts['email'].'</Email>')
                        ->container('Document', array('DocType' => 'DOCS', 'DocID' => $passenger->passport, 'DocIssueCountry' => $passenger->nationality, 'ExpireDate' => $passenger->expire, 'InnerDocType' => 'Passport'))->end('Document');

                if(!$bags_state && strtoupper($type)== 'ADT'){
                   $bags_state = TRUE;//Багаж отправлен,нужен чтобы 6не оправить больше багажа,так как у нас общий выбор багажа,а не по каждому пассажиру
                   $xml->element('NumberOfBaggages',$bags);
                }

                if(!empty($passenger->lcc)){
                    if(!empty($lcc_pas_attr)) $xml->container('LCCParameters',$passenger->lcc)->end('LCCParameters');
                }

                $xml->end('AirTraveler');
            }
        }
        $xml->end('TravelerInfo');

        $xml->container('Fulfillment')
                ->container('PaymentDetails')
                    ->container('PaymentDetail', array('PaymentType'=>'CreditCard'))
                        ->container('BillingAddress')
                            ->element('AddressLine', $this->_billing['address'])
                            ->element('CityName', $this->_billing['city'])
                            ->container('CountryName',array('Code'=>$this->_billing['country']))->end('CountryName')
                            ->element('PostalCode',$this->_billing['postal_code'])
                        ->end('BillingAddress')
                        ->container('PaymentCard',array(
                                        'CardType'=>$this->_credit_card['type'],
                                        'SecurityNumber'=>$this->_credit_card['code'],
                                        'CardNumber'=>$this->_credit_card['number'],
                                        'ExpireDate'=>$this->_credit_card['expire']))
                        ->end('PaymentCard');

                    if($this->_lcc){
                        foreach ($this->_lcc as $name=>$value) {
                            $lcc_attr[$name]=$value;
                        }
                        if(!empty($lcc_attr)) $xml->container('LCCParameters',$lcc_attr)->end('LCCParameters');
                    }

                    $xml->end('PaymentDetail')
                ->end('PaymentDetails')
            ->end('Fulfillment');

        $xml->container('Ticketing',array('TicketType'=>'Ticketless'))->end('Ticketing');

        $xml->end('OTA_AirBookRQ')->end('BookFlight');

        return $xml->getXml();
    }
} 