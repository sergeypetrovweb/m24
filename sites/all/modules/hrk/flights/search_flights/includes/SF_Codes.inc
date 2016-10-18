<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 13.09.14
 * Time: 14:55
 */

namespace includes;


class SF_Codes
{
    private static $instance;

    private $_countries = array();
    private $_cities = array();
    private $_airports = array();
    private $_airlines = array();
    private $_airplanes = array();

    private $_db_search = array();

    private function __construct()
    {
    }

    private function __clone()
    {
    }

    public static function getInstance()
    {
        if (null === self::$instance) {
            self::$instance = new self();
        }

        return self::$instance;
    }

    public function getCode($type, $code)
    {
        $type = $this->_type_compatibility($type);
        return $this->_getCodes($type, array($code));
    }

    public function getCodes($type, $codes)
    {
        $type = $this->_type_compatibility($type);
        return $this->_getCodes($type, $codes);
    }

    public function delayCodes($type, $codes)
    {
        $type = $this->_type_compatibility($type);

        if (!isset($this->_db_search[$type])) {
            $this->_db_search[$type] = $codes;
        } else {
            $this->_db_search[$type] = array_replace_recursive($this->_db_search[$type], $codes);
        }
    }

    public function delayCode($type, $code)
    {
        $type = $this->_type_compatibility($type);
        $this->_db_search[$type][] = $code;
    }

    public function delayStart()
    {
        if (!empty($this->_db_search)) {

            foreach ($this->_db_search as $type => $codes) {
                if (property_exists($this, '_' . $type)) {
                    $this->_getCodes($type, $codes);
                }
                unset($this->_db_search[$type]);
            }
        }
    }


    private function _getCodes($type, $codes)    {

        $ex_codes = array_flip($codes);

        if ($codes && property_exists($this, '_' . $type)) {
            $property_name = '_' . $type;
            $dif_codes = array_diff_key($ex_codes, $this->$property_name);

            if (!empty($dif_codes)) {
                $this->_saveCodes($type, array_keys($dif_codes));
            }

            foreach ($ex_codes as $code => $value) {
                $codes_array = $this->$property_name;
                if (isset($codes_array[$code])) {
                    $ex_codes[$code] = $codes_array[$code];
                }
            }
        }

        return $ex_codes;
    }

    private function _saveCodes($type, $codes)
    {

        switch ($type) {
            case 'countries':
                $query = db_select('hrk_sf_countries', 'c');
                $query->fields('c', array('code', 'name_ru', 'name_en', 'phone_code', 'three_letter_code'));
                $query->condition('code', $codes, 'IN');

                $result = $query->execute();

                foreach ($result as $row) {
                    $this->_countries[$row->code] = array(
                        'code' => $row->code,
                        'name_ru' => $row->name_ru,
                        'name_en' => $row->name_en,
                        'phone_code' => $row->phone_code,
                        'three_letter_code' => $row->three_letter_code,
                    );
                }
                break;
            case 'cities':
                $query = db_select('hrk_sf_cities', 'ct');
                $query->leftJoin('hrk_sf_countries', 'c', 'ct.cid = c.cid');
                $query->fields('ct', array('code', 'name_ru', 'name_en'));
                $query->fields('c', array('code', 'name_ru', 'name_en', 'phone_code', 'three_letter_code'));
                $query->condition('ct.code', $codes, 'IN');

                $result = $query->execute();

                foreach ($result as $row) {
                    $this->_cities[$row->code] = array(
                        'code' => $row->code,
                        'name_ru' => $row->name_ru,
                        'name_en' => $row->name_en,
                        'country' => array(
                            'code' => $row->c_code,
                            'name_ru' => $row->c_name_ru,
                            'name_en' => $row->c_name_en,
                            'phone_code' => $row->phone_code,
                            'three_letter_code' => $row->three_letter_code,
                        )
                    );
                }

                break;
            case 'airports':
                $query = db_select('hrk_sf_airports', 'a');
                $query->leftJoin('hrk_sf_cities', 'ct', 'a.ctid = ct.ctid');
                $query->leftJoin('hrk_sf_countries', 'c', 'a.cid = c.cid');
                $query->fields('a', array('code', 'name_ru', 'name_en'));
                $query->fields('ct', array('code', 'name_ru', 'name_en'));
                $query->fields('c', array('code', 'name_ru', 'name_en', 'phone_code', 'three_letter_code'));
                $query->condition('a.code', $codes, 'IN');

                $result = $query->execute();

                foreach ($result as $row) {
                    $this->_airports[$row->code] = array(
                        'code' => $row->code,
                        'name_ru' => $row->name_ru,
                        'name_en' => $row->name_en,
                        'city' => array(
                            'code' => $row->ct_code,
                            'name_ru' => $row->ct_name_ru,
                            'name_en' => $row->ct_name_en,
                        ),
                        'country' => array(
                            'code' => $row->c_code,
                            'name_ru' => $row->c_name_ru,
                            'name_en' => $row->c_name_en,
                            'phone_code' => $row->phone_code,
                            'three_letter_code' => $row->three_letter_code,
                        )
                    );
                }

                break;
            case 'airlines':
                $query = db_select('hrk_sf_airlines', 'a');
                $query->fields('a', array('code', 'name'));
                $query->condition('a.code', $codes, 'IN');

                $result = $query->execute();

                foreach ($result as $row) {
                    $this->_airlines[$row->code] = array(
                        'code' => $row->code,
                        'name' => $row->name
                    );
                }

                break;
            case 'airplanes':
                $query = db_select('hrk_sf_airplanes', 'a');
                $query->fields('a', array('code', 'name'));
                $query->condition('a.code', $codes, 'IN');

                $result = $query->execute();

                foreach ($result as $row) {
                    $this->_airplanes[$row->code] = array(
                        'code' => $row->code,
                        'name' => $row->name
                    );
                }

                break;
        }
    }

    private function _type_compatibility($type)
    {
        switch ($type) {
            case 'city':
                $type = 'cities';
                break;
            case 'airport':
                $type = 'airports';
                break;
            case 'country':
                $type = 'countries';
                break;
            case 'airline':
                $type = 'airlines';
                break;
            case 'airplane':
                $type = 'airplanes';
                break;
        }

        return $type;
    }
} 