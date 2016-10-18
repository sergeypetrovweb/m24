<?php
function ui_string_form($form, &$form_state, $key) {
  //Прерываем работу, в случае если $key не передан.
  if (empty($key)) {
    return;
  }

  //Зададим ключ к форме. Будем учитывать его при генерации глобальных переменных.
  $form['key'] = array('#type' => 'value', '#value' => $key);
  //Мы заменяем блок #ключ_формы, при нажатии кнопок "Довавить", "Удалить".
  //Значит нам надо при вызове формы отдавать обертку каждый раз заново.
  $form['#prefix'] = '<div id="' . $form['key']['#value'] . '">';
  $form['#suffix'] = '</div>';

  //Поучим настройки и значения этой формы, если такие заданы и сохраним их в массиве $form
  $settings = ui_settings::init();
  $values = $settings->get_values_by_form($key);

  //Сгенерируем содержимое формы, получив ее содержимое по ключу.
  foreach ($settings->forms[$key]['content'] as $id => $element) {
    $element['#default_value'] = isset($values[$id]) ? $values[$id] : NULL;
    $form[$id] = $element;
  }


  $name = isset($settings->forms[$key]['settings']['save_name']) ? $settings->forms[$key]['settings']['save_name'] : t(
    'Save'
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $name,
    '#attributes' => array('class' => array('btn btn-primary'))
  );

  return $form;
}

function ui_string_form_submit($form, &$form_state) {
  $values_for_save = array();
  $key = $form['key']['#value'];
  foreach (ui_settings::init()->forms[$key]['content'] as $element_key => $element) {
    $values_for_save[$element_key] = $form_state['values'][$element_key];
  }
  if (!empty($form_state['files_to_save'])) {
    foreach ($form_state['files_to_save'] as $path) {
      $fid = drupal_array_get_nested_value($form_state['values'], $path);
      if (!empty($fid)) {
        $file = file_load($fid);
        $file->status = FILE_STATUS_PERMANENT;
        file_save($file);
        file_usage_add($file, 'ui_string', 'ui_string', $fid);
      }
    }
  }

  variable_set('avis_' . $form['key']['#value'], $values_for_save);
}