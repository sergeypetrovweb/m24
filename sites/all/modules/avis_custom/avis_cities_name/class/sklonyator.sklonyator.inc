<?php

/**
 * Implements class Sklonyator
 */
class Sklonyator {
  private static $inst;
  private $fix_names;

  /**
   * Function return custom word in needed declension.
   * $type - type of request, maybe "city", or "country".
   * $code - letters city code.
   * $padej - declensions: imenitelniy,roditelniy,datelniy,vinitelniy,tvoritelniy,predlojniy.
   */
  public function get_fixed_name($type, $code, $padej) {
    $rez = '';
    if (!empty($this->fix_names) && isset($this->fix_names[$code])) {
      $rez = $this->fix_names[$code];
    }

    if (empty($rez)) {
      $rez = get_all_form_name($code, $type);
      if ($rez == NULL) {
        return FALSE;
      }

      $this->fix_names[$code] = $rez;
    }
    return $rez->$padej;
  }

  /**
   * Implements init()
   */
  public static function init() {
    if (empty(self::$inst)) {
      self::$inst = new Sklonyator;
    }
    return self::$inst;
  }
}