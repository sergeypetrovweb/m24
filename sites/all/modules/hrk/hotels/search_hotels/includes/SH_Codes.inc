<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 13.09.14
 * Time: 14:55
 */

namespace includes;


class SH_Codes
{
    private static $instance;

    private $_countries = array();
    private $_cities = array();

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
                $query = db_select('hrk_sh_countries', 'c');
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
                $query = db_select('hrk_sh_cities', 'ct');
                $query->leftJoin('hrk_sh_countries', 'c', 'ct.cid = c.cid');
                $query->fields('ct', array('lid', 'name_ru', 'name_en','latitude','longitude'));
                $query->fields('c', array('code', 'name_ru', 'name_en', 'phone_code', 'three_letter_code'));
                $query->condition('ct.lid', $codes, 'IN');

                $result = $query->execute();

                foreach ($result as $row) {
                    $this->_cities[$row->lid] = array(
                        'lid' => $row->lid,
                        'name_ru' => $row->name_ru,
                        'name_en' => $row->name_en,
                        'latitude' => $row->latitude,
                        'longitude' => $row->longitude,
                        'country' => array(
                            'code' => (!empty($row->c_code))?$row->c_code:'',
                            'name_ru' => $row->c_name_ru,
                            'name_en' => $row->c_name_en,
                            'phone_code' => $row->phone_code,
                            'three_letter_code' => $row->three_letter_code,
                        )
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
            case 'country':
                $type = 'countries';
                break;
        }

        return $type;
    }
} 