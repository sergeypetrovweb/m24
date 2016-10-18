<?php
/**
 * Config form.
 */

function _avis_forms_form($form, $form_state) {
  $form = array();

  $form['id_textarea'] = array( // Определяем виджет ввода id форм
    '#type' => 'textarea',
    '#title' => 'Пути',
    '#default_value' => variable_get('id_textarea', 'example'),
    '#description' => 'Зарезервируйте пути для форм. Один путь в строке',
  );

  $ids = explode("\n", trim(variable_get('id_textarea', 'example')));

  foreach ($ids as $id) {
    $id = trim($id);

    $form[$id] = array(
      '#type' => 'fieldset',
      '#title' => $id,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form[$id]['avis_forms_' . $id . '_type'] = array(
      '#type' => 'select',
      '#title' => 'Тип обработчика',
      '#default_value' => variable_get('avis_forms_' . $id . '_type', 'default'),
      '#options' => array(
        'default' => "По умолчанию",
        'webform' => "Webform",
        'comment' => "Форма комментария"
      ),
    );

    $form[$id]['avis_forms_' . $id . '_id'] = array(
      '#type' => 'textfield',
      '#title' => 'Id формы / Nid ноды',
      '#default_value' => variable_get('avis_forms_' . $id . '_id', ''),
      '#description' => "По умолчанию используется ID формы. Для типа Webform и Сomment, используется Nid"
    );

    $form[$id]['avis_forms_' . $id . '_title'] = array(
      '#type' => 'textfield',
      '#title' => 'Заголовок',
      '#default_value' => variable_get('avis_forms_' . $id . '_title', ''),
    );

    $form[$id]['avis_forms_' . $id . '_message'] = array(
      '#type' => 'textarea',
      '#title' => 'Сообщение об успешном выполнении',
      '#default_value' => variable_get('avis_forms_' . $id . '_message', ''),
    );

  }

  return system_settings_form($form);
}