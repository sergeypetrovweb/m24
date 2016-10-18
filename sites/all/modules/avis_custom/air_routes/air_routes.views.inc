<?php

/**
 * Implements hook_views_data()
 */
function air_routes_views_data() {
  $data['avis_parsing_directions']['table']['group'] = t('Air Routes');

  $data['avis_parsing_directions']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Air Routes'),
    'help' => t('Table contains data about air routes'),
  );

  $fields = array(
    'title' => 'Заголовок направления',
    'code_from' => 'Откуда',
    'code_to' => 'Куда',
    'parsed' => 'Создан дамп',
  );

  foreach ($fields as $field_name => $field_title) {
    $data['avis_parsing_directions'][$field_name] = array(
      'title' => $field_title,
      'help' => $field_title,
      'group' => t('Air'),
      'field' => array('handler' => 'views_handler_field'),
      'sort' => array('handler' => 'views_handler_sort'),
      'filter' => array('handler' => 'views_handler_filter_string'),
    );
  }

  $data['air_combinations']['table']['group'] = t('Air combinations');
  $data['air_combinations']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Air combinations'),
    'help' => t('Table contains data about air combinations'),
  );

  $fields = array(
    'cid' => 'Cid для заказа',
    'airline_code' => 'Код авиалиний',
    'price' => 'Цена',
    'time_in_air' => 'Время в полёте',
    'transfer_flights' => 'Количество пересадок',
    'arrival' => 'Время прибытия',
    'city_arrival' => 'Куда',
    'city_departure' => 'Откуда',
    'plain' => 'Самолёт',
    'design_quantity' => 'Количество мест',
  );

  foreach ($fields as $field_name => $field_title) {
    switch ($field_name) {
      case 'time_in_air':
      case 'arrival':
        $field = array('handler' => 'views_handler_field_date');
        $sort = array('handler' => 'views_handler_sort_date');
        $filter = array('handler' => 'views_handler_filter_date');
        break;

      case 'price':
      case 'transfer_flights':
      case 'design_quantity':
        $field = array('handler' => 'views_handler_field');
        $sort = array('handler' => 'views_handler_sort');
        $filter = array('handler' => 'views_handler_filter_numeric');
        break;

      default:
        $field = array('handler' => 'views_handler_field');
        $sort = array('handler' => 'views_handler_sort');
        $filter = array('handler' => 'views_handler_filter_string');
        break;
    }

    $data['air_combinations'][$field_name] = array(
      'title' => $field_title,
      'help' => $field_title,
      'group' => t('Air'),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
        'name field' => $field_name, // display this field in the summary
      ),
      'field' => $field,
      'sort' => $sort,
      'filter' => $filter,
    );
  }

  return $data;
}


