<?php

class ui_settings {
  public $forms_list = array();
  public $views_list = array();
  public $forms = array();

  private static $_instance;

  public function get_values_by_view($key) {
    //Поучим настройки и значения этой формы, если такие заданы.
    $values = variable_get(
      'avis_' . $this->views_list[$key]['form_key'],
      NULL
    );

    return $values;
  }

  public function get_values_by_form($key) {
    //Поучим настройки и значения этой формы, если такие заданы.
    $values = variable_get(
      'avis_' . $key,
      NULL
    );

    return $values;
  }

  public static function init() {
    if (empty(self::$_instance)) {
      self::$_instance = new ui_settings();
    }

    return self::$_instance;
  }

  function __construct() {
    $settings = array();
    $settings = module_invoke_all('ui_strings_form_settings', $settings);

    //Формируем индекс отображений, список форм.
    foreach ($settings as $key => $form) {
      $this->forms_list[] = $key;
      if (!empty($form['settings']['views'])) {
        foreach ($form['settings']['views'] as $view_name => $view_title) {
          //Индекс отображений.
          $this->views_list[$view_name] = array(
            'form_key' => $key,
            'view_title' => $view_title,
          );
        }
      }
    }

    $this->forms = $settings;
  }
}