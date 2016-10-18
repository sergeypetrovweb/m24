<?php
/**
 * Settings form.
 */
function unitailer_settings_form($form, $form_state) {

  $form = array();

  $form['unitailer_idp'] = array(
    '#type' => 'textfield',
    '#title' => t('Shop_IDP'),
    '#size' => 60,
    '#maxlength' => 128,
    '#default_value' => variable_get('unitailer_idp', ''),
    '#required' => TRUE,
  );

  $form['unitailer_login'] = array(
    '#type' => 'textfield',
    '#title' => t('Site login'),
    '#size' => 60,
    '#maxlength' => 128,
    '#default_value' => variable_get('unitailer_login', ''),
    '#required' => TRUE,
  );

  $form['unitailer_pass'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#size' => 60,
    '#maxlength' => 128,
    '#default_value' => variable_get('unitailer_pass', ''),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}