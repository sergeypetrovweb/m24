<?php

function search_hotels_results_city ($location_id) {

  $now = time() + 3600;
  $end = $now + 86400*2;

  _get_hotels_result_page(
    $location_id,
    date('Y-m-d', $now),
    date('Y-m-d', $end),
    array(
      0 => array(
        'adt' => 1,
        'chd' => 0,
        'chd_hidden' => 0,
        'age' => 0,
      ),
    ),
    161
  );



}

function search_hotels_results($location_id, $dates, $rooms, $nationality_and_rating, $session = FALSE)
{

    ctools_class_add(array('full-width'));

    $nationality_and_rating = explode('-', $nationality_and_rating);
    $nationality = $nationality_and_rating[0];
    $rating = !(empty($nationality_and_rating[1])) ? $nationality_and_rating[1] : '_none';

    $sh_request_params = array('l' => $location_id, 'd' => $dates, 'r' => $rooms, 'n' => $nationality_and_rating[0]);

    /*RETURN ERROR_VALIDATING: IF INVALID REQUEST PARAMS*/
    $sh_request_params = hrk_sh_validate_request_param(hrk_sh_uncompress_request_param($sh_request_params));
    if (!$sh_request_params) {
      return hrk_sh_popup('validation');
    }

    /*SAVE DESTINATION TO HISTORY*/
    hrk_rs_save_history(current_path(), 'hotel');

    /*GET COUNTRY NATIONALITY INFO*/
    $nationality = db_select('hrk_sh_countries', 'c')->fields('c', array())->condition('cid', $sh_request_params['nationality'])->execute()->fetchAssoc();

    /*CREATE HASH IDENTIFIER*/
    $sh_request_params['currency'] = currency_get_active_currency();

    $hash = hash('sha256', drupal_http_build_query($sh_request_params));

    /*RETURN DB RESULT:IF WE HAVE ACTIVE EP_SESSION AND SAVED DB RESULT*/
    $session = hrk_system_session('search_hotels', 'result_sessions');
    $pre_loader = hrk_system_session('preloader', 'search_hotels');

    $session_hash = $session->getSession($hash);

    if ($session_hash) {
        $db_session = hrk_cl_get_session($session_hash['sid']);

        /*IF ACTIVE EP_SESSION*/
        if ($db_session && !cl_check_db_session_expire($db_session)) {
            $result = hrk_sh_results($session_hash['rid']);

            /*RETURN DB RESULT: IF IT IS*/
            if ($result) {
                __sh_pagination_localize();
                drupal_add_js(array('sh' => array('map' => $sh_request_params, 'rating' => $sh_request_params['rating'])), 'setting');
                __sh_results_add_scripts(); //add all needed scripts

                  $pre_loader->destroy($hash);
                  $result['session'] = $session->getSession($hash);
                  $result['request_params'] = $sh_request_params;
                  __sh_add_hotels_filters($result);

                $result['filters']['default'] = array('rating' => $rating);

                return theme('sh_results', $result);
            }
        }

        /*CLEAN UP IF WE CAN'T USE DB_RESULT*/
        db_delete('hrk_sh_results')->condition('rid', $session_hash['rid'])->execute();
        $session->destroy($hash);
    }

    /* IF WE REACHED HERE THAT WE HAVE NO ACTIVE SESSION AND(OR)DB_RESULT IS EMPTY */

    /*RETURN PRELOADER:IF THE REQUEST WAS NOT SEND FROM THE SEARCH FORM*/
    if (!$pre_loader->getSession($hash, FALSE)) {
        drupal_add_js(drupal_get_path('module', 'search_hotels') . '/js/pre_load.js', array('scope' => 'footer'));
        $pre_loader->setSession(array($hash => TRUE));
        return '';
    }

    /*CREATE NEW CL_SESSION*/
    $cl_session = hrk_cl_create_session();
    $cl = hrk_cl_engine();

    /*RETURN ERROR_CONNECTION:IF WE CAN'T GET NEW CL_SESSION*/
    if (empty($cl_session) || !$cl->connect()) {
        if (!empty($cl_session['sid'])) $cl->deleteSession($cl_session['sid']);
        return hrk_sf_popup('connection_failed');
    }


    /* CREATE SEARCH HOTELS WITH LOW DETAILS REQUEST*/
    $request = hrk_cl_search_hotels_request($cl_session['session'])
        ->setCountry($nationality['code'])
        ->setCurrency(currency_get_active_currency())
        ->setDates($sh_request_params['check_in'], $sh_request_params['check_out'])
        ->setRooms($sh_request_params['rooms'])
        ->setLocationID($sh_request_params['location_id']);
    $request_xml = $request->getRequest();

    /*DO SEARCH HOTELS REQUEST*/
    $response = $cl->doRequest($request_xml, $request::SOAP_ACTION);

    /*RETURN ERROR "CONNECTION_FAILED": IF RESPONSE IS EMPTY*/
    if (!$response) {
        hrk_cl_delete_session($cl_session['sid']);
        return hrk_sh_popup('connection_failed');
    }

    // dsm($response, '$result');

    /*PARSE RESPONSE*/
    $result = hrk_sh_parse_response($response);

    /*RETURN ERROR "NO AVAILABLE FLIGHTS": IF RESPONSE FLIGHTS IS EMPTY*/
    if (!empty($result['error']['code']) && $result['error']['code'] == 'I0404') return hrk_sh_popup('no_available_hotels');

    /*RETURN ERROR "SERVER_ERROR" AND SAVE ERRORS TO DB: IF HAVE ERRORS*/
    if (!empty($result['error'])) {
        hrk_cl_delete_session($cl_session['sid']);
        $session->destroy($hash);
        hrk_cl_errors()->save($cl_session['session'], array($result['error']), \includes\CL_Errors::ERROR_SEARCH);
        return hrk_sh_popup('show_error', array('text' => $result['error']['text']));
    }

    /*SAVE SEARCH RESULT TO DB*/
    $rid = db_insert('hrk_sh_results')->fields(array(
        'hash' => $hash,
        'sid' => $cl_session['sid'],
        'created' => REQUEST_TIME,
        'result' => hrk_helper_result_encode($result)
    ))->execute();

    /*RETURN ERROR "SERVER_ERROR": IF RESULT DON'T SAVED TO DB*/
    if (!$rid) return hrk_sh_popup('server_error');

    /*SAVED INFO ABOUT RESULT IN LOCAL SESSION*/
    $session->setSession(array(
        $hash => array('sid' => $cl_session['sid'],
            'rid' => $rid,
            'hash' => $hash,
            'created' => REQUEST_TIME)
    ));

    /*RETURN NEW RESULT:IF ALL OK*/
    __sh_pagination_localize();
    drupal_add_js(array('sh' => array('map' => $sh_request_params, 'rating' => $sh_request_params['rating'])), 'setting');
    __sh_results_add_scripts(); //add all needed scripts

    $pre_loader->destroy($hash);
    $result['session'] = $session->getSession($hash);
    $result['request_params'] = $sh_request_params;
    __sh_add_hotels_filters($result);

    $result['filters']['default'] = array('rating' => $rating);

    return theme('sh_results', $result);
}


function __sh_pagination_localize()
{
    drupal_add_js(array('sh' => array(
        'pager_first' => t('First'),
        'pager_last' => t('Last'),
        'pager_prev' => t('Previous'),
        'pager_next' => t('Next'),
    )), 'setting');
}

function __sh_results_add_scripts()
{
    global $language;

    $l_prefix = ($language->language == 'en') ? 'en' : 'ru';

    libraries_load('mixup');
    libraries_load('tooltiper', 'shadow');
    libraries_load('pagination', 'min');
    libraries_load('search_meme');
    drupal_add_js('https://maps.googleapis.com/maps/api/js?sensor=false&language=' . $l_prefix, array('scope' => 'footer'));
    libraries_load('marker_clusterer');
    drupal_add_js(drupal_get_path('module', 'search_hotels') . '/js/search_results.js', array('scope' => 'footer'));
}

function __sh_results_hotel_detail_add_scripts()
{
    global $language;

    $l_prefix = ($language->language == 'en') ? 'en' : 'ru';

    libraries_load('mixup');
    drupal_add_js('https://maps.googleapis.com/maps/api/js?sensor=false&language=' . $l_prefix, array('scope' => 'footer'));
    libraries_load('marker_clusterer');
    flexslider_add();
    drupal_add_js(drupal_get_path('module', 'search_hotels') . '/js/search_results_hotel_detail.js', array('scope' => 'footer'));
}

function __sh_add_hotels_filters(&$result)
{
    if (!empty($result['hotels'])) {
        $result['filters'] = array();
        foreach ($result['hotels'] as &$hotel) {
            __sh_add_hotel_filters($result['filters'], $hotel);
        }
    }
}

function __sh_add_hotel_filters(&$filters, &$hotel)
{
    $hotel['classes'] = array();

    //add rating
    $star_identifier = drupal_clean_css_identifier(strtolower('star-rating-' . $hotel['rating']));
    $filters['rating'][$star_identifier] = $hotel['rating'];
    $hotel['classes'][$star_identifier] = $star_identifier;

    foreach ($hotel['packages'] as &$package) {

        $package['classes'] = array();
        if (!empty($package['supplier_name'])) {
            $supplier_identifier = drupal_clean_css_identifier(strtolower('supplier-' . $package['supplier_name']));
            $filters['availability'][$supplier_identifier] = $package['supplier_name'];
            $hotel['classes'][$supplier_identifier] = $supplier_identifier;
            $package['classes'][$supplier_identifier] = $supplier_identifier;
        }

        if (!empty($package['refund'])) {
            $refund_identifier = drupal_clean_css_identifier(strtolower($package['refund']));
            $filters['refund'][$refund_identifier] = $package['refund'];
            $hotel['classes'][$refund_identifier] = $refund_identifier;
            $package['classes'][$refund_identifier] = $refund_identifier;
        }

        foreach ($package['rooms'] as &$room) {
            $room['classes'] = array();
            /*ADD ROOM BASIS, CLASS, TYPE TO FILTERS ARRAY*/
            if (!empty($room['basis'])) {
                $basis_identifier = drupal_clean_css_identifier(strtolower($room['basis']));
                $filters['basis'][$basis_identifier] = $room['basis'];
                $hotel['classes'][$basis_identifier] = $basis_identifier;
                $room['classes'][$basis_identifier] = $basis_identifier;
                $package['classes'][$basis_identifier] = $basis_identifier;
            }

            if (!empty($room['class'])) {
                $class_identifier = drupal_clean_css_identifier(strtolower($room['class']));
                $filters['class'][$class_identifier] = $room['class'];
                $hotel['classes'][$class_identifier] = $class_identifier;
                $room['classes'][$class_identifier] = $class_identifier;
                $package['classes'][$class_identifier] = $class_identifier;
            }

            if (!empty($room['type'])) {
                $type_identifier = drupal_clean_css_identifier(strtolower($room['type']));
                $filters['type'][$type_identifier] = $room['type'];
                $hotel['classes'][$type_identifier] = $type_identifier;
                $room['classes'][$type_identifier] = $type_identifier;
                $package['classes'][$type_identifier] = $type_identifier;
            }

            if (!empty($room['availability'])) {
                $availability_identifier = drupal_clean_css_identifier(strtolower($room['availability']));
                $filters['availability'][$availability_identifier] = $room['availability'];
                $hotel['classes'][$availability_identifier] = $availability_identifier;
                $room['classes'][$availability_identifier] = $availability_identifier;
                $package['classes'][$availability_identifier] = $availability_identifier;
            }
        }
    }
    $hotel['classes'] = implode(' ', $hotel['classes']);
}

function search_hotels_hotel_detail($location_id, $dates, $rooms, $nationality_id, $hotel_id)
{
    $sh_request_params = array('l' => $location_id, 'd' => $dates, 'r' => $rooms, 'n' => $nationality_id);
    $args = array('location_id' => $location_id, 'dates' => $dates, 'rooms' => $rooms, 'hotel_id' => $hotel_id, 'nationality_id' => $nationality_id);

    /*RETURN ERROR_VALIDATING: IF INVALID REQUEST PARAMS*/
    $sh_request_params = hrk_sh_validate_request_param(hrk_sh_uncompress_request_param($sh_request_params));
    if (!$sh_request_params) return hrk_sh_popup('validation');

    /*CREATE HASH IDENTIFIER*/
    $sh_request_params['currency'] = currency_get_active_currency();

    $hash = hash('sha256', drupal_http_build_query($sh_request_params));

    /*GET SESSION HASH*/
    $session = hrk_system_session('search_hotels', 'result_sessions');
    $session_hash = $session->getSession($hash);

    /*GET ADDITIONAL INFORMATION*/
    $addition_info = $sh_request_params;
    $addition_info['nights'] = __sh_get_nights($sh_request_params['check_in'], $sh_request_params['check_out']);
    $addition_info['check_in'] = strtotime($sh_request_params['check_in']);
    $addition_info['check_out'] = strtotime($sh_request_params['check_out']);

    /*BACK TO SEARCH RESULTS PAGE*/
    $back_link = array(
        'link' => array(
            'title' => t('Try again'),
            'path' => hrk_sh_make_results_page_link($sh_request_params)
        )
    );

    /*RETURN ERROR_SESSION_EXPIRE: IF SESSION HASH EMPTY*/
    if (!$session_hash) return cl_popup('session_expired', $back_link);

    /*RETURN ERROR_SESSION_EXPIRE: IF DB_SESSION EXPIRED*/
    $db_session = hrk_cl_get_session($session_hash['sid']);
    if (!$db_session && cl_check_db_session_expire($db_session)) return cl_popup('session_expired', $back_link);

    /*RETURN DB RESULT:IF WE HAVE ACTIVE EP_SESSION AND SAVED DB DETAIL RESULT*/
    if (!empty($session_hash['sh_hotel_detail']) && in_array($hotel_id, $session_hash['sh_hotel_detail'])) {

        /*GET RESULT FROM DB*/
        $db_result = hrk_sh_results($session_hash['rid']);



        /*RETURN DB_RESULT HOTEL DETAIL IF EXIST:IF NOT DO NEW REQUESTS*/
        if ($db_result && !empty($db_result['sh_hotel_detail'][$hotel_id])) {
            $result = $db_result['sh_hotel_detail'][$hotel_id];
            __sh_results_hotel_detail_add_scripts();
            drupal_add_js(array('sh' => array('map' => $sh_request_params)), 'setting');

            /*ADD FILTERS*/
            $result['filters'] = array();
            __sh_add_hotel_filters($result['filters'], $result);

            return theme('sh_result_hotel', array('hotel' => $result, 'back_path' => hrk_sh_make_results_page_link($sh_request_params), 'addition_info' => $addition_info, 'args' => $args));
        }
    }

    /* IF WE REACHED HERE THAT WE HAVEN'T DB DETAIL RESULT */


    $cl = hrk_cl_engine();

    /*RETURN ERROR_CONNECTION:IF WE CAN'T GET CL_SESSION OR CONNECTION FAIL*/
    if (empty($db_session) || !$cl->connect()) {
        return hrk_sh_popup('connection_failed', $back_link);
    }

    /* CREATE SEARCH HOTEL DETAILS WITH PACKAGES REQUEST*/
    $request = hrk_cl_search_hotel_details_request($db_session['session'], TRUE)->setHotelID($hotel_id);
    $request_xml = $request->getRequest();

    /*DO SEARCH HOTEL DETAILS REQUEST*/
    $response = $cl->doRequest($request_xml, $request::SOAP_ACTION);

    /*RETURN ERROR "CONNECTION_FAILED": IF RESPONSE IS EMPTY*/
    if (!$response) {
        return hrk_sh_popup('connection_failed', $back_link);
    }

    /*GET PACKAGE DETAILS*/
    $package_result = hrk_sh_parse_hotel_package_response($response);

    /*RETURN ERROR "NO MATCHING ITEM FOUND.": IF RESPONSE PACKAGE DETAILS IS EMPTY*/
    if (!empty($package_result['error']['code']) && $package_result['error']['code'] == 'E4301') return hrk_sh_popup('show_error', array('text' => $package_result['error']['text']));

    /*RETURN ERROR "SERVER_ERROR" AND SAVE ERRORS TO DB: IF HAVE ERRORS*/
    if (!empty($package_result['error'])) {
        if ($package_result['error']['code'] == 'E0300') {
            hrk_cl_delete_session($db_session['sid']);
            $session->destroy($hash);
        } else {
            hrk_cl_errors()->save($db_session['session'], array($package_result['error']), \includes\CL_Errors::ERROR_SEARCH);
        }

        return hrk_sh_popup('show_error', array('text' => $package_result['error']['text']));
    }

    /* CREATE SEARCH HOTEL DETAILS WITH NO PACKAGES REQUEST*/
    $request = hrk_cl_search_hotel_details_request($db_session['session'], FALSE)->setHotelID($hotel_id);
    $request_xml = $request->getRequest();

    /*DO SEARCH HOTEL DETAILS REQUEST*/
    $response = $cl->doRequest($request_xml, $request::SOAP_ACTION);

    /*RETURN ERROR "CONNECTION_FAILED": IF RESPONSE IS EMPTY*/
    if (!$response) {
        return hrk_sh_popup('connection_failed', $back_link);
    }

    /*GET HOTEL DETAILS*/
    $hotel_result = hrk_sh_parse_hotel_info_response($response);

    /*RETURN ERROR "NO MATCHING ITEM FOUND.": IF RESPONSE HOTEL DETAILS IS EMPTY*/
    if (!empty($hotel_result['error']['code']) && $hotel_result['error']['code'] == 'E4301') return hrk_sh_popup('show_error', array('text' => $hotel_result['error']['text']));

    /*RETURN ERROR "SERVER_ERROR" AND SAVE ERRORS TO DB: IF HAVE ERRORS*/
    if (!empty($hotel_result['error'])) {

        if ($hotel_result['error']['code'] == 'E0300') {
            hrk_cl_delete_session($db_session['sid']);
            $session->destroy($hash);
        } else {
            hrk_cl_errors()->save($db_session['session'], array($hotel_result['error']), \includes\CL_Errors::ERROR_SEARCH);
        }

        return hrk_sh_popup('show_error', array('text' => $hotel_result['error']['text']));
    }

    $result = array_merge($hotel_result, $package_result);
    $result['id'] = $hotel_id;

    /*UPDATE DB RESULT*/
    $db_result = hrk_sh_results($session_hash['rid']);
    $db_result['sh_hotel_detail'][$hotel_id] = $result;

    db_update('hrk_sh_results')->fields(array(
        'result' => hrk_helper_result_encode($db_result)
    ))->condition('rid', $session_hash['rid'])->execute();

    $session_hash['sh_hotel_detail'][$hotel_id] = $hotel_id;

    /*UPDATE LOCAL SESSION*/
    $session->setSession(array($hash => $session_hash));
    __sh_results_hotel_detail_add_scripts();
    drupal_add_js(array('sh' => array('map' => $sh_request_params)), 'setting');

    /*ADD FILTERS*/
    $result['filters'] = array();
    __sh_add_hotel_filters($result['filters'], $result);

    return theme(
      'sh_result_hotel',
      array(
        'hotel' => $result,
        'back_path' => hrk_sh_make_results_page_link($sh_request_params),
        'addition_info' => $addition_info,
        'args' => $args));
}


function __sh_get_nights($check_in, $check_out)
{
    $date_check_in = new \DateTime($check_in);
    $date_check_out = new \DateTime($check_out);

    return $date_check_out->diff($date_check_in)->format("%a");
}


//filters forms

function search_hotels_result_filter($form, &$form_state, $filters)
{
  //$form['#attributes'] = array('class' => array('search-hotels-filter-form'));
  $form['#theme'] = array('search_hotels_result_filter');

    if (!empty($filters['rating'])) {
        $filters_rating_values = array_reverse($filters['rating']);

        $form['rating'] = array(
            '#type' => 'select',
            '#empty_value' => '_none',
            '#empty_option' => t('All'),
            '#options' => $filters['rating'],
            '#title' => t('Rating'),
            '#default_value' => !empty($filters_rating_values[$filters['default']['rating']]) ? $filters_rating_values[$filters['default']['rating']] : '_none'
        );
    }

    if (!empty($filters['basis'])) {
        $filters_basis_values = array_reverse($filters['basis']);
//      foreach($filters['basis'] as $key => $text) {
//        $filters['basis'][$key] = t($text, array(), array('context' => 'hotels'));
//      }

        $form['basis'] = array(
            '#type' => 'select',
            '#empty_value' => '_none',
            '#empty_option' => t('All'),
            '#options' => $filters['basis'],
          '#attributes' => array('autocomplete' => 'off', 'class' => array('off-styler')),
            '#title' => t('Service'),
            '#default_value' => !empty($filters_basis_values[$filters['default']['basis']]) ? $filters_basis_values[$filters['default']['basis']] : '_none'
        );
    }

    if (!empty($filters['class'])) {
        $filters_class_values = array_reverse($filters['class']);
//      foreach($filters['class'] as $key => $text) {
//        $filters['class'][$key] = t($text, array(), array('context' => 'hotels'));
//      }

        $form['class'] = array(
            '#type' => 'select',
            '#empty_value' => '_none',
            '#empty_option' => t('All'),
          '#attributes' => array('autocomplete' => 'off', 'class' => array('off-styler')),
            '#options' => $filters['class'],
            '#title' => t('Room Class'),
            '#default_value' => !empty($filters_class_values[$filters['default']['class']]) ? $filters_class_values[$filters['default']['class']] : '_none'
        );
    }

    if (!empty($filters['type'])) {
        $filters_type_values = array_reverse($filters['type']);
//      foreach($filters['type'] as $key => $text) {
//        $filters['type'][$key] = t($text, array(), array('context' => 'hotels'));
//      }

        $form['type'] = array(
            '#type' => 'select',
            '#empty_value' => '_none',
            '#empty_option' => t('All'),
            '#options' => $filters['type'],
          '#attributes' => array('autocomplete' => 'off', 'class' => array('off-styler')),
            '#title' => t('Room Type'),
            '#default_value' => !empty($filters_type_values[$filters['default']['type']]) ? $filters_type_values[$filters['default']['type']] : '_none'
        );
    }


    $form['search_hotels_js_live'] = array(
        '#type' => 'textfield',
        '#attributes' => array('id' => 'search_hotels_js_live', 'data-search-text' => t('Search Hotels...'), 'style' => array('margin-left' => '15px'))
    );


    return $form;
}


function search_hotels_details_result_filter($form, &$form_state,$filters){


    $form['#attributes'] = array('class' => array('search-hotels-details-filter-form'));

    $form['filters_left'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('filters-left'))
    );

    $form['filters_left']['price'] = array(
        '#type' => 'textfield',
        '#title' => t('Price'),
    );

    if (!empty($filters['basis'])) {
        $filters_basis_values = array_reverse($filters['basis']);

        $form['filters_left']['basis'] = array(
            '#type' => 'select',
            '#empty_value' => '_none',
            '#empty_option' => t('All'),
            '#options' => $filters['basis'],
            '#title' => t('Service'),
            '#default_value' => !empty($filters_basis_values[$filters['default']['basis']]) ? $filters_basis_values[$filters['default']['basis']] : '_none'
        );
    }

    if (!empty($filters['class'])) {
        $filters_class_values = array_reverse($filters['class']);

        $form['filters_left']['class'] = array(
            '#type' => 'select',
            '#empty_value' => '_none',
            '#empty_option' => t('All'),
            '#options' => $filters['class'],
            '#title' => t('Room Class'),
            '#default_value' => !empty($filters_class_values[$filters['default']['class']]) ? $filters_class_values[$filters['default']['class']] : '_none'
        );
    }

    if (!empty($filters['type'])) {
        $filters_type_values = array_reverse($filters['type']);

        $form['filters_left']['type'] = array(
            '#type' => 'select',
            '#empty_value' => '_none',
            '#empty_option' => t('All'),
            '#options' => $filters['type'],
            '#title' => t('Room Type'),
            '#default_value' => !empty($filters_type_values[$filters['default']['type']]) ? $filters_type_values[$filters['default']['type']] : '_none'
        );
    }

    $form['filters_right'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('filters-right'))
    );

    $sort = array(
        'price:asc' => t('cheapest'),
        'price:desc' => t('expensive')
    );

    $form['filters_right']['sort'] = array(
        '#type' => 'select',
        '#options' => $sort,
        '#title' => t('Sort (start with)'),
        '#default_value' => 'price:asc'
    );
//
//    $form['filters_left']['submit'] = array(
//        '#type' => 'submit',
//        '#value' => t('Choose room'),
//        '#attributes' => array('class' => array('default-bb'))
//    );

    return $form;
}