<?php

class SystemSessionApi
{
    // module name
    private $_module = null;
    //custom prefix
    private $_prefix = '';

    public function __construct($module, $prefix)
    {
        $this->_module = $module;
        $this->_prefix = $prefix;
    }

    public static function init($module, $prefix)
    {
        return new SystemSessionApi($module, $prefix);
    }

    public function setSession($data, $replace = FALSE)
    {
        if (!isset($_SESSION[$this->_module][$this->_prefix])) {
            $_SESSION[$this->_module][$this->_prefix] = array();
        }
        if (!$replace) {
            $_SESSION[$this->_module][$this->_prefix] = array_replace_recursive($_SESSION[$this->_module][$this->_prefix], $data);
        } else {
            $_SESSION[$this->_module][$this->_prefix] = $data;
        }

        return $this;
    }

    public function getSession($keys = null, $default = null)
    {
        $data = isset($_SESSION[$this->_module][$this->_prefix]) ? $_SESSION[$this->_module][$this->_prefix] : $default;
        if ($keys && $data) {
            switch (gettype($keys)) {
                case 'array':
                    $tmp = $data;
                    if (is_object($tmp)) $tmp = (array)$tmp;

                    foreach ($keys as $key) {
                        if (is_object($tmp)) $tmp = (array)$tmp;
                        $tmp = isset($tmp[$key]) ? $tmp[$key] : $default;
                        if (!$tmp) break;
                    }
                    $data = $tmp;
                    break;
                default:
                    if (is_object($data)) $data = (array)$data;
                    $data = isset($data[$keys]) ? $data[$keys] : $default;
                    break;
            }
        }

        return $data;
    }

    public function destroy($keys = null)
    {
        if ($keys) {
            switch (gettype($keys)) {
                case 'array':
                    $tmp = & $_SESSION[$this->_module][$this->_prefix];
                    $last_key = end($keys);

                    foreach ($keys as $key) {
                        if (!$tmp) break;

                        if ($key != $last_key) {
                            switch (gettype($tmp)) {
                                case 'object':
                                    $tmp = & $tmp->$key;
                                    break;
                                default:
                                    if (isset($tmp[$key])) {
                                        $tmp = & $tmp[$key];
                                    } else {
                                        $tmp = null;
                                    }
                                    break;
                            }
                        }
                    }
                    unset($tmp[$last_key]);
                    break;
                default:
                    if (is_object($_SESSION[$this->_module][$this->_prefix])) {
                        unset($_SESSION[$this->_module][$this->_prefix]->$keys);
                    } else {
                        unset($_SESSION[$this->_module][$this->_prefix][$keys]);
                    }
            }
        } else {
            unset($_SESSION[$this->_module][$this->_prefix]);
        }

        return $this;
    }
} 