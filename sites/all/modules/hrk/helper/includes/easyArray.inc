<?php

/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 11.09.14
 * Time: 12:47
 */

function easyA($newArray){
    return easyArray::getInstance()->loadArray($newArray);
}

class easyArray
{
    private static $instance;
    private $Array;

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

    /**
     * Method required to transfer to the class of the new array for processing.
     *
     * @access public
     *
     * @param array $newArray
     *
     *  @throws $error if not passed an array
     *
     * @return easyArray
     */
    public function loadArray($newArray)
    {
        if (is_array($newArray)) {
            $this->Array = $newArray;
            return $this;
        } else {
            $error = 'Unfortunately you have passed an array.';
            throw new Exception($error);
        }
    }

    /**
     * Method that returns an array used without further treatment.
     *
     * @access public
     *
     * @return array $this->Array
     */
    public function arrayReturn()
    {
        return $this->Array;
    }

    /**
     * Magic method to return values ​​of associative arrays.
     *
     * @access public
     *
     * @param string $index
     *
     *  @throws $error if no key in the array
     *
     * @return $this->Array[$index]
     * or
     * @return easyArray
     */
    public function __get($index)
    {
        if (isset($this->Array[$index])) {
            if (is_array($this->Array[$index])) {
                $this->loadArray($this->Array[$index]);
                return $this;
            } else {
                return $this->Array[$index];
            }
        } else {
            $error = 'There is no key (' . $index . ') in the array';
            throw new Exception($error);
        }
    }
}