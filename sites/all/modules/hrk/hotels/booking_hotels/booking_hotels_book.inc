<?php

function booking_hotels_book($bid)
{
    $book = hrk_bh_book($bid);
    $book = (object)$book;

  /*RETURN PAGE_NOT_FOUND:IF NO BOOK WITH THIS BID*/
  if ((empty($book->bid) || $book->is_deleted) && !user_access('management_hotels_booking')) drupal_not_found();

  $hotel = (object)$book->data;
  /*GET FREE CANCELLATION DATE*/
  $free_cancellation_date = strtotime('-1 days', strtotime($hotel->cancellation_policy[0]['date_from']));
  $time = '';
  $left_time = '';

  if (!hrk_bh_is_expire($free_cancellation_date)) {
    $site_default_time_zone = new DateTimeZone(date_default_timezone(FALSE));
    $time_limit = new DateTime(date('Y-m-d H:i:s', $free_cancellation_date), $site_default_time_zone);
    $user_time = new DateTime('now', $site_default_time_zone);

    $diff_time = date_diff($time_limit, $user_time);
    $left_time = format_interval(((($diff_time->y * 365.25 + $diff_time->m * 30 + $diff_time->d) * 24 + $diff_time->h) * 60 + $diff_time->i) * 60 + $diff_time->s);
    $time = format_date($time_limit->getTimestamp(), 'medium', 'j F G:i \\G\\M\\T(O)');
  }

  $out = '<div class="hotel-container">';
  $buy = FALSE;
  if ($payment = unitailer_get_payment_by_target($book->uuid, $book->bid)) {
    $buy = render(drupal_get_form('unitailer_form', $payment));
  }

    if ($book->is_paid == 1 && $book->is_cancel != 1) {
        $type = 'paid';
    } else if ($book->is_cancel == 1) {
        $type = 'cancel';
    } else {
        $type = 'book';
    }

  $out .= theme('bh_book_modern', array(
    'hotel' => $hotel,
    'addition_info' => $hotel->_sh_params,
    'book' => $book,
    'buy' => $buy,
    'type' => $type,
    'bonus' => $book->data['summ_pay_from_bonus'],
  ));
  $out .= '</div>';
  drupal_add_js(drupal_get_path('module', 'booking_hotels') . '/js/book.js');
  return $out;
}


//OLD

//function booking_hotels_book_form($form, &$form_state, $book)
//{
//    $form['#prefix'] = '<div class="hotel-container">';
//    $form['#suffix'] = '</div>';
//
//    /*HEADER*/
//
//    $hotel = (object)$book->data;
//    /*GET FREE CANCELLATION DATE*/
//    $free_cancellation_date = strtotime('-1 days', strtotime($hotel->cancellation_policy[0]['date_from']));
//
//    $time = '';
//    $left_time = '';
//
//    if (!hrk_bh_is_expire($free_cancellation_date)) {
//        $site_default_time_zone = new DateTimeZone(date_default_timezone(FALSE));
//        $time_limit = new DateTime(date('Y-m-d H:i:s', $free_cancellation_date), $site_default_time_zone);
//        $user_time = new DateTime('now', $site_default_time_zone);
//
//        $diff_time = date_diff($time_limit, $user_time);
//        $left_time = format_interval(((($diff_time->y * 365.25 + $diff_time->m * 30 + $diff_time->d) * 24 + $diff_time->h) * 60 + $diff_time->i) * 60 + $diff_time->s);
//        $time = format_date($time_limit->getTimestamp(), 'medium', 'j F G:i \\G\\M\\T(O)');
//    }
//
//
//    $form['book_rooms'] = array(
//        '#type' => 'container',
//        '#prefix' => '<div class="hotel-block">',
//        '#suffix' => '</div>',
//    );
//    $room_number = 0;
//    foreach ($hotel->package['rooms'] as $room) {
//        $room_obj = (object)$room;
//
//        $room['free_cancellation'] = $free_cancellation_date;
//
//        if (!empty($hotel->images)) {
//            $image_key = array_rand($hotel->images, 1);
//            $room['image'] = $hotel->images[$image_key];
//        }
//
//        $room_number++;
//    }
//
//    if (!$book->is_cancel) {
//        /*CREATE NEW PAYMENT IF NOT EXIST*/
//        if (empty($book->azid)) {
//            $az = hrk_az_create_payment(ceil($hotel->price['price']), $hotel->price['currency']);
//
//            if ($az) {
//                /*UPDATE BOOK RECORD*/
//                db_update('hrk_bh_book')->fields(array('azid' => $az['azid']))->condition('bid', $book->bid)->execute();
//            }
//        } else {
//            $az = hrk_az_get_payment($book->azid);
//        }
//
//        if ($az) {
//            /*UPDATE AZ PAYMENT : IF CURRENCY CHANGED*/
//            $form = array_merge($form, azericard_payment_form($form, $form_state, $az));
//
//            $form['actions'] = array('#type' => 'actions');
//
//            $form['actions']['buy'] = array(
//                '#type' => 'submit',
//                '#value' => t('Buy'),
//            );
//        }
//    }
//
//    $form['summary_output'] = array(
//        '#markup' => theme('bh_book_modern', array('hotel' => $hotel, 'addition_info' => $hotel->_sh_params, 'header' => $form['header'], 'book' => $book, 'submit' => $form['actions']['buy'])),
//    );
//
//
//    drupal_add_js(drupal_get_path('module', 'booking_hotels') . '/js/book.js');
//    dsm($form);
//    return $form;
//}

//function booking_hotels_paid_form($form, &$form_state, $book)
//{
//
//    $form['#prefix'] = '<div class="hotel-container">';
//    $form['#suffix'] = '</div>';
//
//    /*HEADER*/
//
//    $hotel = (object)$book->data;
//    /*GET FREE CANCELLATION DATE*/
//    $free_cancellation_date = strtotime('-1 days', strtotime($hotel->cancellation_policy[0]['date_from']));
//
//    $time = '';
//    $left_time = '';
//
//    if (!hrk_bh_is_expire($free_cancellation_date)) {
//        $site_default_time_zone = new DateTimeZone(date_default_timezone(FALSE));
//        $time_limit = new DateTime(date('Y-m-d H:i:s', $free_cancellation_date), $site_default_time_zone);
//        $user_time = new DateTime('now', $site_default_time_zone);
//
//        $diff_time = date_diff($time_limit, $user_time);
//        $left_time = format_interval(((($diff_time->y * 365.25 + $diff_time->m * 30 + $diff_time->d) * 24 + $diff_time->h) * 60 + $diff_time->i) * 60 + $diff_time->s);
//        $time = format_date($time_limit->getTimestamp(), 'medium', 'j F G:i \\G\\M\\T(O)');
//    }
//
//    $form['header'] = array(
//        '#markup' => theme('bh_book_header', array(
//            'hotel' => $hotel,
//            'addition_info' => $hotel->_sh_params,
//            'time' => $time,
//            'left_time' => $left_time,
//            'type' => 'paid',
//            'book_id' => $book->bkid,
//            'order_id' => $book->orid,
//            'segment_id' => $book->seid,
//        )),
//        '#prefix' => '<div class="hotel-block">',
//        '#suffix' => '</div>',
//    );
//
//    $form['book_rooms'] = array(
//        '#type' => 'container',
//        '#prefix' => '<div class="hotel-block">',
//        '#suffix' => '</div>',
//    );
//    $room_number = 0;
//    foreach ($hotel->package['rooms'] as $room) {
//        $room_obj = (object)$room;
//
//        $room['free_cancellation'] = $free_cancellation_date;
//
//        $form['book_rooms'][$room_number]['quests'] = array(
//            '#markup' => theme('bh_book_guests', array('guests' => $room_obj->guests)),
//            '#prefix' => '<div class="hotel-block">',
//        );
//
//        if (!empty($hotel->images)) {
//            $image_key = array_rand($hotel->images, 1);
//            $room['image'] = $hotel->images[$image_key];
//        }
//
//        $form['book_rooms'][$room_number]['room'] = array(
//            '#markup' => theme('bh_book_room', array('room' => $room)),
//            '#suffix' => '</div>',
//        );
//        $room_number++;
//    }
//
//    drupal_add_js(drupal_get_path('module', 'booking_hotels') . '/js/book.js');
//    return $form;
//}
