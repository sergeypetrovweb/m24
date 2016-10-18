<?php

function unitailer_test_page() {
  return render(drupal_get_form('unitailer_test_form'));
}

function unitailer_test_form($form, &$form_state) {
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create test order'),
    '#submit' => array('unitailer_test_form_submit'),
  );
  return $form;
}

function unitailer_test_form_submit($form, &$form_state) {
  $uuid = uuid_generate();
  unitailer_write_payment($uuid, 1, 0, 'test');
  drupal_set_message('Test order created');
}