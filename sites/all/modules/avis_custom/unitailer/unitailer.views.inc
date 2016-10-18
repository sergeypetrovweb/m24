<?php

/**
 * Implements hook_views_data()
 */
function unitailer_views_data() {
  $data['unitailer_payment']['table']['group'] = t('Unitailer');
  $data['unitailer_payment']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Unitailer'),
    'help' => t('Table contains data about payments from unitaler'),
  );

  $fields = array(
    'id' => 'Id',
    'uuid' => 'Уникальный id заказа',
    'entity_id' => 'Id заказа',
    'entity' => 'Тип заказа',
    'status' => 'Статус заказа',
    'amount' => 'Сумма',
  );

  foreach ($fields as $field_name => $field_title) {

    $data['unitailer_payment'][$field_name] = array(
      'title' => $field_title,
      'help' => $field_title,
      'group' => t('Unitailer'),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
        'name field' => $field_name, // display this field in the summary
      ),
      'field' => array('handler' => 'views_handler_field'),
      'sort' => array('handler' => 'views_handler_sort'),
      'filter' => array('handler' => 'views_handler_filter_string'),
    );
  }

  return $data;
}


