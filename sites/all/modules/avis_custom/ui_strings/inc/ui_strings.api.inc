<?php

//Функция возвращает настройки всех форм на сайте, или одной конкретной по ключу.
function _avis_get_form_config($key = FALSE) {
  $settings = array();
  //Получим все настройки из модулей.
  $settings = module_invoke_all('ui_strings_form_settings', $settings);
  //Вернем нужные настройки в зависимости от переданного агрумента
  if ($key) {
    if (isset($settings[$key])) {
      return $settings[$key];
    }
    else {
      return FALSE;
    }
  }

  return $settings;
}