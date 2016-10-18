<?php
/**
 * @file
 * Page: flights/book/%
 */

/**
 * Callback for [flights/book/%] hook_menu
 */
function booking_flights_book($bid) {

  $reset = date_default_timezone_get();

  $book = (object) hrk_bf_book($bid);
  $base_currency = Currency::init()->get_base_currency();

  // Return page_not_found if no book with this bid.
  if ((empty($book->bid) || $book->is_deleted) && !user_access('management_flights_booking')) {
    drupal_not_found();
  }

  $book_info = $book->data['book'];
  $book_info = (object)$book_info;

  $search_params = $book->data['search_params'];

  $airline = $book_info->codes['airlines'][$book->data['airline']];

  $path = drupal_get_path('theme', 'flight_modern');
  global $language;
  $l_prefix = ($language->language == 'en') ? 'en' : 'ru';

  $depart_info = $book_info->codes['airports'][$book_info->flights[0][0][0]['departure_airport']];
  $arrival_info = $book_info->codes['airports'][$book_info->flights[0][0][0]['arrival_airport']];

  // Return page book if tid is empty.
  if (!$book->tid) {
    $out = '<div id="booking-flights-book-form" class="container">';

    $out .= '
    <div id="breadcrumbs">
        <div class="container">
            <img src="/' . $path . '/images/breadcrumbs_home.png"> <a href="#">' . $depart_info['city']['name_' . $l_prefix] . ' - ' . $arrival_info['city']['name_' . $l_prefix] . '</a>
        </div>
    </div>';

    $out .= '<div id ="content"><div class="container">';

    /*CHECK CANCEL BOOKING: IF EXPIRE UPDATE BOOK RECORD*/
    if (hrk_bf_is_expire($book->expire) && !$book->is_cancel) {
      hrk_bf_update_book($book->bid, array('is_cancel' => 1));
      $book->is_cancel = TRUE;
      bf_mail_book($book->email, $book->bid);
    }

    /*IF BOOK IS CANCEL*/
    if ($book->is_cancel) {
      /*HEADER*/
      $out .= theme('bf_book_header', array('airline' => $airline));

      /*MESSAGE*/
      $out .= theme('bf_book_message', array('type' => 'cancel'));
    }
    else {
      /*IF BOOK NOT EXPIRE*/
      /*MESSAGE*/
      $site_default_time_zone = new DateTimeZone(date_default_timezone(FALSE));
      $user_time = new DateTime(date('Y-m-d H:i:s', REQUEST_TIME), $site_default_time_zone);
      $time_limit = new DateTime(date('Y-m-d H:i:s', $book->expire), $site_default_time_zone);

      date_default_timezone_set($reset);

      $diff_time = date_diff($time_limit, $user_time);
      $left_seconds = ($diff_time->h * 3600) + ($diff_time->i * 60) + $diff_time->s;
      $left_time = format_interval($left_seconds);
      $buy = FALSE;
      if ($payment = unitailer_get_payment_by_target($book->uuid, $book->bid)) {
        $buy = render(drupal_get_form('unitailer_form', $payment));
      }

      $out .= theme('bf_book_message', array(
        'time' => format_date($book->expire, 'medium', 'j F G:i \\G\\M\\T(O)'),
        'left_time' => $left_time,
        'left_seconds' => $left_seconds,
        'type' => 'book',
        'context_id' => reset($book_info->context_id),
        'buy' => $buy,
      ));
    }

    /*TRIP INFO*/
    $out .= theme('bf_book_trip_info', array(
      'book' => $book_info,
      'flights' => $book_info->flights,
      'search_params' => $search_params,
      'codes' => $book_info->codes,
      'bonus' => $book->data['summ_pay_from_bonus'],
    ));

    $out .= '</div></div>';

    drupal_add_js(drupal_get_path('module', 'booking_flights') . '/js/book.js');

    return $out . '</div>';

  }

  $out = '<div id="booking-flights-book-form" class="container book-fix">';

  $airline = $book_info->codes['airlines'][$book->data['airline']];

  $rules = !empty($book_info->penalties) ? $book_info->penalties : array();

  /*HEADER*/
//  $out .= theme('bf_book_header', array(
//    'airline' => $airline,
//    'rules' => $rules
//  ));

  /*MESSAGE*/
  $out .= theme('bf_book_message', array(
    'type' => 'ticket',
    'context_id' => end($book_info->context_id)
  ));

  /*PASSENGERS*/
//  $out = theme('bf_book_passengers', array('passengers' => $book_info->passenger));

  /*TRIP INFO*/

  $out .= theme('bf_book_trip_info', array(
    'book' => $book_info,
    'flights' => $book_info->flights,
    'search_params' => $search_params,
    'codes' => $book_info->codes,
    'bonus' => $book->data['summ_pay_from_bonus'],
  ));

  drupal_add_js(drupal_get_path('module', 'booking_flights') . '/js/book.js');

  return $out . '</div>';
}

function booking_flights_book_form($form, &$form_state, $book) {
  $book_info = $book->data['book'];
  $book_info = (object) $book_info;
  $search_params = $book->data['search_params'];

  $airline = $book_info->codes['airlines'][$book->data['airline']];

  $path = drupal_get_path('theme', 'flight_modern');
  global $language;
  $l_prefix = ($language->language == 'en') ? 'en' : 'ru';

  $depart_info = $book_info->codes['airports'][$book_info->flights[0][0][0]['departure_airport']];
  $arrival_info = $book_info->codes['airports'][$book_info->flights[0][0][0]['arrival_airport']];

  $form['breadcrumbs']['#markup'] = '
    <div id="breadcrumbs">
        <div class="container">
            <img src="/' . $path . '/images/breadcrumbs_home.png"> <a href="#">' . $depart_info['city']['name_' . $l_prefix] . ' - ' . $arrival_info['city']['name_' . $l_prefix] . '</a>
        </div>
    </div>';

  $form['container_main_start']['#markup'] = '<div id ="content"><div class="container">';


  /*CHECK CANCEL BOOKING: IF EXPIRE UPDATE BOOK RECORD*/
  if (hrk_bf_is_expire($book->expire) && !$book->is_cancel) {
    hrk_bf_update_book($book->bid, array('is_cancel' => 1));
    $book->is_cancel = TRUE;
    bf_mail_book($book->email, $book->bid);
  }

  /*IF BOOK IS CANCEL*/
  if ($book->is_cancel) {
    /*HEADER*/
    $form['header'] = array('#markup' => theme('bf_book_header', array('airline' => $airline)));

    /*MESSAGE*/
    $form['message'] = array('#markup' => theme('bf_book_message', array('type' => 'cancel')));
  }
  else {
    /*IF BOOK NOT EXPIRE*/

    /*HEADER*/
    //$form['header'] = array('#markup' => theme('bf_book_header', array('airline' => $airline, 'rules' => $book_info->penalties)));

    /*MESSAGE*/
    $site_default_time_zone = new DateTimeZone(date_default_timezone(FALSE));
    $time_limit = new DateTime($book_info->ticket_limit['limit'], $site_default_time_zone);
    $user_time = new DateTime('now', $site_default_time_zone);

    $diff_time = date_diff($time_limit, $user_time);
    $left_time = format_interval(($diff_time->h * 3600) + ($diff_time->s * 60) + $diff_time->i);

    $form['info']['#markup'] = theme('bf_book_message', array(
      'time' => format_date($time_limit->getTimestamp(), 'medium', 'j F G:i \\G\\M\\T(O)'),
      'left_time' => $left_time,
      'type' => 'book',
      'context_id' => reset($book_info->context_id)
    ));

    if (empty($book->tid)) {

      $price = $book_info->price;

      $user_active_currency = strtoupper(currency_get_active_currency($price['currency']));


      $amount = ceil($price['fare'][$user_active_currency] + $price['commission'][$user_active_currency]);

      /*CREATE NEW PAYMENT IF NOT EXIST*/
      if (empty($book->azid)) {
        $az = hrk_az_create_payment($amount, $user_active_currency);

        if ($az) {
          /*UPDATE BOOK RECORD*/
          db_update('hrk_bf_book')
            ->fields(array('azid' => $az['azid']))
            ->condition('bid', $book->bid)
            ->execute();
        }
      }
      else {
        $az = hrk_az_get_payment($book->azid);
      }

      if ($az) {
        /*UPDATE AZ PAYMENT : IF CURRENCY CHANGED*/
        if ($az['currency'] != $user_active_currency) {
          hrk_az_update_payment($az['azid'], array(
            'currency' => $user_active_currency,
            'amount' => $amount
          ));

        }
        $form = array_merge($form, azericard_payment_form($form, $form_state, $az));

        /*PRICE*/
        $site_currency = strtoupper(currency_get_active_currency());
        $price = ceil($book_info->price['fare'][$site_currency]);
        $commission = ceil($book_info->price['commission'][$site_currency]);
      }
    }
  }

  /*TRIP INFO*/
  $form['trip_info'] = array(
    '#markup' => theme('bf_book_trip_info', array(
      'book' => $book_info,
      'flights' => $book_info->flights,
      'search_params' => $search_params,
      'codes' => $book_info->codes,
      'bonus' => $book->data['summ_pay_from_bonus'],
    ))
  );

  $form['container_main_end']['#markup'] = '</div></div>';

  drupal_add_js(drupal_get_path('module', 'booking_flights') . '/js/book.js');
  return $form;
}

function booking_flights_ticket_form($form, &$form_state, $book) {
  $book_info = $book->data['ticket'];
  $book_info = (object) $book_info;
  $search_params = $book->data['search_params'];

  $airline = $book_info->codes['airlines'][$book->data['airline']];

  $rules = !empty($book_info->penalties) ? $book_info->penalties : array();

  /*HEADER*/
  $form['header'] = array(
    '#markup' => theme('bf_book_header', array(
      'airline' => $airline,
      'rules' => $rules
    ))
  );

  /*MESSAGE*/
  $form['message'] = array(
    '#markup' => theme('bf_book_message', array(
      'type' => 'ticket',
      'context_id' => end($book_info->context_id)
    ))
  );

  /*PASSENGERS*/
  $form['passengers'] = array('#markup' => theme('bf_book_passengers', array('passengers' => $book_info->passenger)));

  /*TRIP INFO*/
  $form['trip_info'] = array(
    '#markup' => theme('bf_book_trip_info', array(
      'flights' => $book_info->flights,
      'search_params' => $search_params,
      'codes' => $book_info->codes,
      'bonus' => $book->data['summ_pay_from_bonus'],
    ))
  );

  drupal_add_js(drupal_get_path('module', 'booking_flights') . '/js/book.js');
  return $form;
}