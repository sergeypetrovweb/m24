<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 24.09.14
 * Time: 14:51
 */

namespace requests;


use includes\SoapXmlWriter;

class EP_Calendar{
    const SOAP_ACTION = 'http://epowerv5.amadeus.com.tr/WS/SearchFlightCalendar';
    const PROVIDER_AMADEUS = 'OnlyAmadeus';
    const PROVIDER_AMADEUS_AND_EXT_PROVIDERS = 'AmadeusAndExtProviders';
    const PROVIDER_ONLY_EXT_PROVIDERS = 'OnlyExtProviders';

    const REFUNDABLE_TYPE_ALL_FLIGHTS = 'AllFlights';
    const REFUNDABLE_TYPE_ONLY_REFUNDABLE = 'OnlyRefundable';
    const REFUNDABLE_TYPE_ONLY_NON_REFUNDABLE = 'OnlyNonRefundable';

    const CABIN_TYPE_ECONOMY = 'Economy';
    const CABIN_TYPE_FIRST = 'First';
    const CABIN_TYPE_BUSINESS = 'Business';

    private $_trips = array();
    private $_passengers = array();
    private $_cabin_type = '';

    public function setTrips($trips)
    {
        $this->_trips = $trips;
        return $this;
    }

    public function setPassengers($passengers)
    {
        $this->_passengers = $passengers;
        return $this;
    }

    public function setCabinType($type)
    {
        $cabin_types = array('E' => self::CABIN_TYPE_ECONOMY, 'F' => self::CABIN_TYPE_FIRST, 'B' => self::CABIN_TYPE_BUSINESS);
        $this->_cabin_type = !empty($cabin_types[$type]) ? $cabin_types[$type] : self::CABIN_TYPE_ECONOMY;
        return $this;
    }

    public function getRequest($provider = self::PROVIDER_AMADEUS_AND_EXT_PROVIDERS, $refundable_type = self::REFUNDABLE_TYPE_ALL_FLIGHTS)
    {
        if (!$this->_isEnable()) return FALSE;

        helper_include('SoapXmlWriter');

        $xml = new SoapXmlWriter();

        $xml->container('SearchFlightCalendar', array('xmlns' => 'http://epowerv5.amadeus.com.tr/WS'));

        $xml->container('OTA_AirLowFareSearchRQ', array(
            'ProviderType' => $provider,
            'RefundableType' => $refundable_type,
            'Version' => 0,
            'xmlns:xsi' => 'http://www.w3.org/2001/XMLSchema-instance',
            'xmlns:xsd' => 'http://www.w3.org/2001/XMLSchema'));

        //set trips
        foreach ($this->_trips as $index => $trip) {
            $trip = (object)$trip;

            $xml->container('OriginDestinationInformation')
                ->element('DepartureDateTime', date('Y-m-d\TH:01:s', strtotime($trip->departure)))
                ->container('OriginLocation', array(
                    'LocationCode' => $trip->direction_from['code'],
                    'MultiAirportCityInd' => ($trip->direction_from['type'] == 'city') ? 'true' : 'false'
                ))->end('OriginLocation')
                ->container('DestinationLocation', array(
                    'LocationCode' => $trip->direction_to['code'],
                    'MultiAirportCityInd' => ($trip->direction_to['type'] == 'city') ? 'true' : 'false'
                ))->end('DestinationLocation')
                ->end('OriginDestinationInformation');

            if (!empty($trip->return)) {
                $xml->container('OriginDestinationInformation')
                    ->element('DepartureDateTime', date('Y-m-d\TH:01:s', strtotime($trip->return)))
                    ->container('OriginLocation', array(
                        'LocationCode' => $trip->direction_to['code'],
                        'MultiAirportCityInd' => ($trip->direction_to['type'] == 'city') ? 'true' : 'false'
                    ))->end('OriginLocation')
                    ->container('DestinationLocation', array(
                        'LocationCode' => $trip->direction_from['code'],
                        'MultiAirportCityInd' => ($trip->direction_from['type'] == 'city') ? 'true' : 'false'
                    ))->end('DestinationLocation')
                    ->end('OriginDestinationInformation');
            }
        }

        //set cabin type
        $xml->container('TravelPreferences')
            ->container('CabinPref', array('Cabin' => $this->_cabin_type))
            ->end('CabinPref')
            ->end('TravelPreferences');

        //set passengers
        $xml->container('TravelerInfoSummary')
            ->container('AirTravelerAvail');

        foreach ($this->_passengers as $type => $count) {
            if ($count) {
                for ($i = 1; $i <= $count; $i++) {
                    $xml->container('PassengerTypeQuantity', array('Code' => strtoupper($type)))->end('PassengerTypeQuantity');
                }
            }
        }

        $xml->end('AirTravelerAvail')
            ->end('TravelerInfoSummary');


        //end OTA_AirLowFareSearchRQ
        $xml->end('OTA_AirLowFareSearchRQ');

        //end SearchFlight
        $xml->end('SearchFlight');

        return $xml->getXml();
    }

    private function _isEnable()
    {
        if (empty($this->_trips) || empty($this->_passengers)) return FALSE;

        return TRUE;
    }
} 