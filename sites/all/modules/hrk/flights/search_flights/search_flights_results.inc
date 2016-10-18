<?php



function __get_flights_city_name ($codes, $airport, $lang) {
    return $codes['airports'][$airport]['city']['name_' . $lang];
}

function search_flights_results($des, $date, $pas, $cabin, $mode)
{

  $search_params = array('des' => $des, 'date' => $date, 'pas' => $pas, 'c' => $cabin, 'm' => $mode);

  /*RETURN ERROR_VALIDATING: IF INVALID REQUEST PARAMS*/
  $q_params = hrk_sf_validate_request_param(hrk_sf_uncompress_request_param($search_params));

  if (!$q_params) return hrk_sf_popup('validation');

  /*SAVE DESTINATION TO HISTORY*/
  hrk_rs_save_history(current_path(), 'flight');

  /*CREATE HASH IDENTIFIER*/
  $query = drupal_http_build_query(hrk_sf_compress_request_param($q_params));
  $hash = hash('sha256', $query);

  /*RETURN DB RESULT:IF WE HAVE ACTIVE EP_SESSION AND SAVED DB RESULT*/
  $session = hrk_system_session('search_flights', 'result_sessions');
  $preloader = hrk_system_session('preloader', 'search_flights');

  $session_hash = $session->getSession($hash);

  if ($session_hash) {
    $db_session = hrk_ep_get_session($session_hash['sid']);

    /*IF ACTIVE EP_SESSION*/
    if ($db_session && !ep_check_db_session_expire($db_session)) {
      $result = hrk_sf_results($session_hash['rid']);

      /*RETURN DB RESULT: IF IT IS*/
      if ($result) {
        libraries_load('tooltiper', 'shadow');
        libraries_load('mixup');
        drupal_add_js(drupal_get_path('module', 'search_flights') . '/js/search_results.js', array('scope' => 'footer'));

        $preloader->destroy($hash);
        $result['session'] = $session->getSession($hash);
        $result['q_params'] = $q_params;
        return theme('sf_results', $result);
      }
    }

    /*CLEAN UP IF WE CAN'T USE DB_RESULT*/
    db_delete('hrk_sf_results')->condition('rid', $session_hash['rid'])->execute();
    $session->destroy($hash);
  }

  /*
   * IF WE REACHED HERE THAT WE HAVE NO ACTIVE SESSION AND(OR)DB_RESULT IS EMPTY
   */

  /*RETURN PRELOADER:IF THE REQUEST WAS NOT SEND FROM THE SEARCH FORM*/
  if (!$preloader->getSession($hash, FALSE)) {
    drupal_add_js(drupal_get_path('module', 'search_flights') . '/js/search_results_pre_load.js', array('scope' => 'footer'));
    $preloader->setSession(array($hash => TRUE));

    return '';
  }

  /*CREATE NEW EP_SESSION*/
  $ep_session = hrk_ep_create_session();
  $ep = hrk_ep_engine();

  /*RETURN ERROR_CONNECTION:IF WE CAN'T GET NEW EP_SESSION*/
  if (empty($ep_session) || !$ep->connect($ep_session['session'])) {
    $ep->disconnect();
    return hrk_sf_popup('connection_failed');
  }

  //dsm($q_params);

  /* AI: FLIGHT CALENDAR REQUEST*/

	$calendar_parsed = '';
	if ($q_params['direction_type'] != 'multi_stop')
	{
  	$request = hrk_ep_make_search_request('flight_calendar')->setTrips($q_params['trip'])->setPassengers($q_params['passengers'])->setCabinType($q_params['cabin_type']);
  	$request_xml = $request->getRequest();
		$response = $ep->doRequest($request_xml,$request::SOAP_ACTION);
		$calendar_parsed = hrk_sf_parse_calendar($response, $q_params['direction_type']);
	}

	

  /* CREATE SEARCH FLIGHT REQUEST*/
  $request = hrk_ep_make_search_request('flight')->setTrips($q_params['trip'])->setPassengers($q_params['passengers'])->setCabinType($q_params['cabin_type']);
  $request_xml = $request->getRequest();

  if(module_exists('dump')) dump($request_xml,'Запрос на получение перелета к Amadeus');

  /*DO SEARCH FLIGHT REQUEST*/
  $response = $ep->doRequest($request_xml,$request::SOAP_ACTION);

  if(module_exists('dump')) dump($response,'Ответ Amadeus на запрос перелетаа');
  //dsm($response, 'Ответ Amadeus на запрос перелета');


  /*RETURN ERROR "CONNECTION_FAILED": IF RESPONSE IS EMPTY*/
  if (!$response) {
    if ($ep->disconnect()) {
      hrk_ep_delete_session($ep_session['sid']);
    }
    return hrk_sf_popup('connection_failed');
  }

  /*PARSE RESPONSE*/
  $result = hrk_sf_parse_response($response);

  /*RETURN ERROR "NO AVAILABLE FLIGHTS": IF RESPONSE FLIGHTS IS EMPTY*/
  if (!empty($result['empty'])) return hrk_sf_popup('no_available_flights');


  /*RETURN ERROR "SERVER_ERROR" AND SAVE ERRORS TO DB: IF HAVE ERRORS*/
  if (!empty($result['errors'])) {
    if ($ep->disconnect()) hrk_ep_delete_session($ep_session['sid']);
    if ($result['errors'][0]['text'] == 'EPowerException.EPowerException.No Available Flights') {

        return hrk_sf_popup('no_available_flights');
    }
    hrk_ep_errors()->save($ep_session['session'], $result['errors'], \includes\EP_Errors::ERROR_SEARCH);
    return hrk_sf_popup('server_error');
  }

  /*ADD MODE TO RESULT*/
  $result['mode'] = $q_params['direction_type'];

	$result['calendar'] = $calendar_parsed; // AI: INJECT CALENDAR TO RESULT

  /*SAVE SEARCH RESULT TO DB*/
  $rid = db_insert('hrk_sf_results')->fields(array(
    'hash' => $hash,
    'sid' => $ep_session['sid'],
    'created' => REQUEST_TIME,
    'result' => hrk_helper_result_encode($result)
  ))->execute();

  /*RETURN ERROR "SERVER_ERROR": IF RESULT DON'T SAVED TO DB*/
  if (!$rid) return hrk_sf_popup('server_error');

  /*SAVED INFO ABOUT RESULT IN LOCAL SESSION*/
  $session->setSession(array(
    $hash => array('sid' => $ep_session['sid'],
      'rid' => $rid,
      'hash' => $hash,
      'query' => $query,
      'created' => REQUEST_TIME)
  ));

  /*RETURN NEW RESULT:IF ALL OK*/
  libraries_load('tooltiper', 'shadow');
  libraries_load('mixup');
  drupal_add_js(drupal_get_path('module', 'search_flights') . '/js/search_results.js', array('scope' => 'footer'));

  $preloader->destroy($hash);
  $result['session'] = $session->getSession($hash);
  $result['q_params'] = $q_params;
  return theme('sf_results', $result);
}


function search_flights_result_filter($form,&$form_state){

    $form['#attributes'] = array('class' => array('search-flights-filter-form'));

    $form['direction'] = array(
        '#type'=>'hidden',
        '#default_value'=>'all'
    );

    $sort = array(
        'price:asc' => t('cheapest'),
        'time:asc' => t('fastest')
    );

    $form['sort'] = array(
        '#type' => 'select',
        '#options' => $sort,
        '#title' => t('Sort (start with)'),
        '#default_value' => 'price:asc'
    );


    return $form;
}