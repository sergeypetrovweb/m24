<?php
function ui_strings_element_info_alter(&$elements) {
  $elements['managed_file']['#process'][] = '_avis_settings_file_process';
  $elements['text_format']['#process'] = array_merge(
    array('_avis_settings_text_format_process'),
    $elements['text_format']['#process']
  );
}

function _ui_strings_file_remove($form, &$form_state) {
  $trigger = $form_state['triggering_element'];
  $path = $trigger['#parents'];
  unset($path[count($path) - 1]);
  $value = drupal_array_get_nested_value($form_state['values'], $path);
  unset($form_state['files_to_save'][$value]);
}

function _ui_strings_file_upload($form, &$form_state) {
  $trigger = $form_state['triggering_element'];
  $path = $trigger['#parents'];
  unset($path[count($path) - 1]);
  $form_state['files_to_save'][] = $path;
}

function _avis_settings_text_format_process($element, $form_state, $form) {
  if (!isset($form['key']['#value'])) {
    return $element;
  }
  if (!empty($element['#default_value'])) {
    $element['#format'] = $element['#default_value']['format'];
    $element['#default_value'] = $element['#default_value']['value'];
  }

  return $element;
}

function _avis_settings_file_process($element, $form_state, $form) {
  if (!isset($form['key']['#value'])) {
    return $element;
  }
  /*
    if (!empty($element['#file'])) {
      $element['#prefix'] = theme(
        'image_style',
        array(
          'style_name' => 'thumbnail',
          'path' => $element['#file']->uri,
        ));
    }*/

  /*  if (!empty($element['remove_button'])) {
      $element['remove_button']['#submit'][] = '_ui_strings_file_remove';
    }*/
  if (!empty($element['upload_button'])) {
    $element['upload_button']['#submit'][] = '_ui_strings_file_upload';
  }

  return $element;
}
