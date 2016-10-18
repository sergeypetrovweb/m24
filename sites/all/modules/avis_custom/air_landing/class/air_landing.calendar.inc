<?php

/**
 * Implements AirLandingCalendar class.
 */
class AirLandingCalendar {
  private static $_instance;
  public $dirTable = 'avis_parsing_directions';

  /**
   * Implements init().
   */
  public static function init() {
    if (empty(self::$_instance)) {
      self::$_instance = new AirLandingCalendar;
    }
    return self::$_instance;
  }

  function __construct() {

  }

  /**
   * Function return items with empty date.
   */
  public function getFirstEmptyDate($from, $to) {
    db_set_active('stage');
    $route = db_select('air_calendar', 'ac');
    $route->leftJoin('avis_parsing_directions', 'apd', 'ac.did = apd.id');
    $route = $route->fields('ac', array('id', 'month', 'did'))
      ->fields('apd', array('code_from', 'code_to'))
      ->condition('ac.time', '')
      ->condition('ac.id', $from, '>=')
      ->condition('ac.id', $to, '<=')
      ->range(0, 1)
      ->execute()->fetchAll();
    db_set_active('default');
    if (!empty($route[0])) {
      return $route[0];
    }
    return FALSE;
  }

  /**
   * Function for issets flights by direction id.
   */
  public function hasFlights($did) {
    db_set_active('stage');
    $route = db_select('air_directions_time', 'adt')
      ->fields('adt', array('time'))
      ->condition('adt.did', $did)->execute()->fetchField(0);
    db_set_active('default');
    return $route;
  }

  /**
   * Function return current mount and 11 next in array
   */
  public function getCalendarColumns() {
    $dates = array();
    $date = new DateTime();

    $dates[] = $date->format("Y-m");

    for ($i = 1; $i < 12; $i++) {
      $date->modify('+1 month');
      $dates[] = $date->format("Y-m");
    }
    return $dates;
  }

  /**
   * Function install Calendar
   */
  public function installCalendar() {
    db_set_active('stage');
    // Drupal 7, dynamic query, вариант 1
    $count = db_select('air_calendar', 'ac')->countQuery()->execute()
      ->fetchField();
    if ($count > 0) {
      return FALSE;
    }

    $dates = $this->getCalendarColumns();

    $routes = db_select('avis_parsing_directions', 'dir')
      ->fields('dir', array('id'))
      ->execute()
      ->fetchAllKeyed(0, 0);

    $transaction = db_transaction();
    try {
      foreach ($routes as $route) {
        $insert = db_insert('air_calendar')->fields(array(
          'did',
          'month',
          'price'
        ));
        foreach ($dates as $date) {
          $insert->values(array(
            'did' => $route,
            'month' => $date,
            'price' => 0,
          ));
        }
        $insert->execute();
      }
    }
    catch (Exception $e) {
      $transaction->rollback();
      watchdog_exception('Calendar Building', $e);
    }
    db_set_active('default');
  }
}