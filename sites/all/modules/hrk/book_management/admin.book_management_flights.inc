<?php

function admin_book_management_flights_list_form($form, &$form_state)
{
    //filter elements
    $session_filters = hrk_system_session('book_management', 'flights_filters');
    $filters_values = $session_filters->getSession();
    $form['filters'] = __admin_book_management_flights_get_filters($form_state);

    $header = array(
        'book_id' => array('data' => t('Book ID'), 'field' => 'cid'),
        'ticket_id' => array('data' => t('Ticket ID'), 'field' => 'tid'),
        'email' => array('data' => t('Email'), 'field' => 'email'),
        'phone' => array('data' => t('Phone'), 'field' => 'phone'),
        'user' => array('data' => t('User')),
        'sessions' => array('data' => t('Sessions')),
        'created' => array('data' => t('Created'), 'field' => 'created', 'sort' => 'desc'),
        'expire' => array('data' => t('Expire'), 'field' => 'expire'),
        'status' => array('data' => t('Status')),
        'operations' => array('data' => t('Operation')),
    );

    $query = db_select('hrk_bf_book', 'bf');
    $query->leftJoin('users', 'u', 'u.uid = bf.uid');

    if (!empty($filters_values['search'])) {
        $condition_or = db_or();
        $condition_or->condition('cid', $filters_values['search'], 'IN');
        $condition_or->condition('tid', $filters_values['search'], 'IN');
        $query->condition($condition_or);
    }

    if (!empty($filters_values['filters'])) {

        switch ($filters_values['filters']['state']) {
            case 'book':
                $query->condition('is_ticket', 0);
                $query->condition('is_cancel', 0);
                break;
            case 'ticket':
                $query->condition('is_ticket', 1);
                $query->condition('is_cancel', 0);
                break;
            case 'cancel':
                $query->condition('is_cancel', 1);
                break;
        }

        switch ($filters_values['filters']['period']) {
            case 'current_month':
                $query->condition('bf.created', strtotime(date('Y-m-1')), '>');
                break;
            case 'previous_month':
                $query->condition('bf.created', strtotime('first day of -1 month'), '>');
                break;
            case 'three_month':
                $query->condition('bf.created', strtotime('first day of -3 month'), '>');
                break;
            case 'six_month':
                $query->condition('bf.created', strtotime('first day of -6 month'), '>');
                break;
            case 'your_period':
                if (!empty($filters_values['filters']['from'])) {
                    $query->condition('bf.created', strtotime($filters_values['filters']['from']), '>');
                }
                if (!empty($filters_values['filters']['to'])) {
                    $query->condition('bf.created', strtotime($filters_values['filters']['from']), '<');
                }
                break;

        }
    }


    $query->groupBy('bf.created');

    $count_query = clone $query;
    $count_query->addExpression('COUNT(bf.bid)');

    $query = $count_query->extend('PagerDefault')->extend('TableSort');

    $query->fields('bf', array())
        ->fields('u', array('name'))
        ->limit(50)
        ->orderByHeader($header)
        ->setCountQuery($count_query);

    $result = $query->execute();

    //get books
    $books = array();
    $options = array();

    foreach ($result as $row) {
        $books[$row->bid] = $row;
        $books[$row->bid]->session = unserialize($row->sessions);
        $books[$row->bid]->data = hrk_helper_result_decode($row->data);
    }

    $destination = drupal_get_destination();
    if ($books) {
        foreach ($books as $book) {
            if ($book->bid) {
                $operations = array();

                $operations['show'] = array(
                    'title' => t('Show more'),
                    'href' => 'flights/book/' . $book->bid,
                    'attributes' => array('target' => '_blank'),
                    'query' => $destination,
                );

                if (!$book->is_cancel && !$book->is_ticket) {
/*                    if (!$book->is_ticket) {
                        $operations['checkout'] = array(
                            'title' => t('Checkout'),
                            'href' => 'admin/book_management/flights/' . $book->bid . '/checkout',
                            'query' => $destination,
                        );
                    }*/

                    $operations['cancel'] = array(
                        'title' => t('Cancel'),
                        'href' => 'admin/book_management/flights/' . $book->bid . '/cancel',
                        'query' => $destination,
                    );
                }

                if ($book->is_cancel || $book->is_ticket) {
                    $operations['delete'] = array(
                        'title' => t('delete'),
                        'href' => 'admin/book_management/flights/' . $book->bid . '/delete',
                        'query' => $destination,
                    );
                }

                $options[$book->bid] = array(
                    'book_id' => array(
                        'data' => array(
                            '#type' => 'item',
                            '#markup' => $book->cid,
                        )
                    ),
                    'ticket_id' => array(
                        'data' => array(
                            '#type' => 'item',
                            '#markup' => $book->tid,
                        )
                    ),
                    'email' => array(
                        'data' => array(
                            '#type' => 'link',
                            '#title' => $book->email,
                            '#href' => 'mailto:' . $book->email
                        )
                    ),
                    'phone' => array(
                        'data' => array(
                            '#type' => 'link',
                            '#title' => $book->phone,
                            '#href' => 'tel:+' . $book->phone
                        )
                    ),
                    'user' => array('data' => ($book->uid)
                            ? array('#type' => 'link', '#title' => $book->name, '#href' => 'user/' . $book->uid)
                            : array('#type' => 'item', '#markup' => t('Unregistered user'))),
                    'sessions' => array(
                        'data' => array(
                            '#type' => 'item',
                            '#markup' => __admin_book_management_get_flight_sessions($book->session)
                        )
                    ),
                    'created' => array(
                        'data' => array(
                            '#type' => 'item',
                            '#markup' => date('d.m.Y', $book->created),
                        )
                    ),
                    'expire' => array(
                        'data' => array(
                            '#type' => 'item',
                            '#markup' => date('d.m.Y', $book->expire),
                        )
                    ),
                    'status' => array(
                        'data' => array(
                            '#type' => 'item',
                            '#markup' => __admin_book_management_get_flight_status($book),
                        )
                    ),
                    'operations' => array(
                        'data' => array(
                            '#theme' => 'links__node_operations',
                            '#links' => $operations,
                            '#attributes' => array('class' => array('links', 'inline')),
                        )
                    ),
                );
            }
        }
    }

    $form['book_flights'] = array(
        '#tree' => TRUE,
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $options,
        '#empty' => t('No book.'),
    );

    $form['pager']['#markup'] = theme('pager');

    return $form;
}


function __admin_book_management_get_flight_status($book)
{
    $status = ($book->tid) ? '<span style="color:green">' . t('Booked and paid') . '</span>' : '<span style="color:blue">' . t('Booked') . '</span>';

    if ($book->is_cancel) {
        $status = '<span style="color:red">' . t('Canceled') . '</span>';
    }

    return $status;
}

function __admin_book_management_get_flight_sessions($sessions)
{
    $sessions_id = array();
    foreach ($sessions as $session) {
        $sessions_id[] = '<li>' . $session['ASP.NET_SessionId'][0] . '</li>';
    }
    return '<ul>' . implode('', $sessions_id) . '</ul>';
}

function __admin_book_management_flights_get_filters($form_state)
{
    $session_filters = hrk_system_session('book_management', 'flights_filters');
    $filters_values = $session_filters->getSession();

    $filters = array();

    $filters['search'] = array(
        '#type' => 'fieldset',
        '#title' => t('Search'),
        '#tree' => TRUE,
        '#attributes' => array('class' => array('exposed-filters')),
        '#description' => t('Search Book ID and Ticket ID, to find more values separate them with commas.')
    );

    $filters['search']['term'] = array(
        '#type' => 'textfield',
        '#attributes' => array('placeholder' => t('Search'), 'autocomplete' => 'off'),
        '#default_value' => !empty($filters_values['search']) ? implode(',', $filters_values['search']) : ''
    );

    $filters['search']['button'] = array(
        '#type' => 'submit',
        '#value' => t('Search'),
        '#submit' => array('__book_management_add_flights_args_to_filter'),
    );

    if (!empty($filters_values['search'])) {
        $filters['search']['clear_button'] = array(
            '#type' => 'submit',
            '#value' => t('Clear'),
            '#submit' => array('__book_management_add_flights_args_to_filter'),
        );
    }

    $filters['filters'] = array(
        '#type' => 'fieldset',
        '#title' => t('Filters'),
        '#tree' => TRUE,
        '#attributes' => array('class' => array('exposed-filters'))
    );

    $filters['filters']['state'] = array(
        '#type' => 'select',
        '#title' => t('Status'),
        '#options' => array('all' => t('All'), 'cancel' => t('Canceled'), 'book' => t('Booked'), 'ticket' => t('Booked and paid')),
        '#default_value' => isset($filters_values['filters']['state']) ? $filters_values['filters']['state'] : 'all'
    );

    $filters['filters']['period'] = array(
        '#type' => 'select',
        '#title' => t('Time'),
        '#options' => array(
            'all' => t('For all time'),
            'current_month' => t('Current month'),
            'previous_month' => t('Previous Month'),
            'three_month' => t('3 months'),
            'six_month' => t('6 months'),
            'your_period' => t('Your time period')),
        '#default_value' => isset($filters_values['filters']['period']) ? $filters_values['filters']['period'] : 'all'
    );

    $filters['filters']['from'] = array(
        '#type' => 'pickadate_date',
        '#attributes' => array('placeholder' => t('From date'), 'autocomplete' => 'off'),
        '#states' => array('visible' => array(':input[name="filters[period]"]' => array('value' => 'your_period'))),
        '#default_value' => isset($filters_values['filters']['from']) ? $filters_values['filters']['from'] : '',
        '#settings' => pickadate_date_default_settings(array(
            'formatSubmit' => 'yyyy-mm-dd',
            'firstDay' => 1,
            'hiddenName' => false,
            'max' => date('[Y,n,j]', strtotime('-1 month', REQUEST_TIME)),
            'today' => '',
            'close' => '',
            'clear' => ''))
    );

    $filters['filters']['to'] = array(
        '#type' => 'pickadate_date',
        '#attributes' => array('placeholder' => t('To date'), 'autocomplete' => 'off'),
        '#states' => array('visible' => array(':input[name="filters[period]"]' => array('value' => 'your_period'))),
        '#default_value' => isset($filters_values['filters']['to']) ? $filters_values['filters']['to'] : '',
        '#settings' => pickadate_date_default_settings(array(
            'formatSubmit' => 'yyyy-mm-dd',
            'firstDay' => 1,
            'hiddenName' => false,
            'max' => date('[Y,n,j]', strtotime('-1 month', REQUEST_TIME)),
            'today' => '',
            'close' => '',
            'clear' => ''))
    );

    $filters['filters']['button'] = array(
        '#type' => 'submit',
        '#value' => t('Filter'),
        '#submit' => array('__book_management_add_flights_args_to_filter'),
    );

    if (!empty($filters_values['filters'])) {
        $filters['filters']['clear_button'] = array(
            '#type' => 'submit',
            '#value' => t('Clear'),
            '#submit' => array('__book_management_add_flights_args_to_filter'),
        );
    }


    return $filters;
}

function __book_management_add_flights_args_to_filter($form, &$form_state)
{
    $values = (object)$form_state['values'];

    $session_filters = hrk_system_session('book_management', 'flights_filters');

    switch ($values->op) {
        case t('Search'):
            $session_filters->destroy();
            $session_filters->setSession(array('search' => explode(',', $values->search['term'])));
            break;
        case t('Clear'):
            $session_filters->destroy();
            break;
        case t('Filter'):
            $session_filters->setSession(array('filters' => $values->filters));
            break;
    }
}

function admin_book_management_flights_checkout_form($form, &$form_state, $bid)
{

    $book = hrk_bf_book($bid);

    if (!$book) drupal_not_found();

    $book = (object)$book;
    $book_info = $book->data['book'];
    $book_info = (object)$book_info;

    if ($book->is_cancel) return array('cancel' => array('#markup' => t('Unable to pay for the reservation, the reservation is canceled')));

    if (empty($book->azid)) {

        $price = $book_info->price;
        $user_active_currency = strtoupper(currency_get_active_currency($price['currency']));
        $amount = ceil($price['fare'][$user_active_currency] + $price['commission'][$user_active_currency]);
        $az = hrk_az_create_payment($amount, $user_active_currency);

        if ($az) {
            /*UPDATE BOOK RECORD*/
            db_update('hrk_bf_book')->fields(array('azid' => $az['azid']))->condition('bid', $book->bid)->execute();
        }
    } else {
        $az = hrk_az_get_payment($book->azid);
    }

    if ($az) {
        /*UPDATE AZ PAYMENT : IF CURRENCY CHANGED*/
        $form = array_merge($form, azericard_payment_form($form, $form_state, $az));
    }

    $confirm_question = t('Are you sure you want to pay booking with a Book ID: @booking_id?', array('@booking_id' => $book->cid));

    return confirm_form($form, $confirm_question, 'admin/book-management/flights', '', t('Pay'), t('Cancel'));
}

function admin_book_management_flights_delete_form($form, &$form_state, $bid)
{
    $book = hrk_bf_book($bid);

    if (!$book) drupal_not_found();

    $form['bid'] = array('#type' => 'value', '#value' => $bid);

    $book = (object)$book;
    $confirm_question = t('Are you sure you want to delete booking with a Book ID: @booking_id, Ticket ID: @ticket_id?', array(
        '@booking_id' => $book->cid,
        '@ticket_id' => ($book->tid) ? $book->tid : t('None'),
    ));

    return confirm_form($form, $confirm_question, 'admin/book-management/flights', t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

function admin_book_management_flights_delete_form_submit($form, &$form_state)
{
    $values = (object)$form_state['values'];
    $book = hrk_bf_book($values->bid);

    if ($book) {
        $book = (object)$book;

        db_delete('hrk_bf_book')->condition('bid', $values->bid)->execute();

        drupal_set_message(t('Booking with  with a Book ID: @booking_id, Ticket ID: @ticket_id successfully deleted.', array(
            '@booking_id' => $book->cid,
            '@ticket_id' => ($book->tid) ? $book->tid : t('None'),
        )));
    } else {
        drupal_set_message(t('Booking not found', 'warning'));
    }
}

function admin_book_management_flights_cancel_form($form, &$form_state, $bid)
{
    $book = hrk_bf_book($bid);

    if (!$book) drupal_not_found();

    $book = (object)$book;

    if ($book->is_cancel) return array('cancel' => array('#markup' => t('Unable to pay for the reservation, the reservation is canceled')));

    $form['bid'] = array('#type' => 'value', '#value' => $bid);

    $confirm_question = t('Are you sure you want to cancel booking with a Book ID: @booking_id, Ticket ID: @ticket_id?', array(
        '@booking_id' => $book->cid,
        '@ticket_id' => ($book->tid) ? $book->tid : t('None'),
    ));

    return confirm_form($form, $confirm_question, 'admin/book-management/flights', t('This action cannot be undone.'), t('Cancel'), t('Back'));
}

function admin_book_management_flights_cancel_form_submit($form, &$form_state)
{

    $values = (object)$form_state['values'];
    $book = hrk_bf_book($values->bid);


    if ($book) {
        $book = (object)$book;
        $book_info = (object)$book->data['book'];

        $db_session = hrk_ep_create_session();

        if (!$db_session) {
            drupal_set_message(t('Failed to create session'), 'error');
            return TRUE;
        }

        $passenger = (object)$book_info->passenger['ADT'][0];

        $request = hrk_ep_cancel_booking()->setContextID($book->cid)->setVerificationSurName($passenger->last_name);

        $ep = hrk_ep_engine();

        if (!$ep->connect($db_session['session'])) {
            hrk_ep_delete_session($db_session['sid']);
            drupal_set_message(t('Connection error'), 'error');
            return TRUE;
        }

        $response = $ep->doRequest($request->getRequest(), $request::SOAP_ACTION);

        if (!$response) {
            hrk_ep_delete_session($db_session['sid']);
            drupal_set_message(t('You can not cancel your reservation, Amadeus not answer!'), 'error');
            return TRUE;
        };

        $result = hrk_bf_parse($response)->cancel();
      //dsm($result);

        if ($result['error']) {
            hrk_ep_errors()->save($db_session['session'], array($result['error']), \includes\EP_Errors::ERROR_BOOKING);
            drupal_set_message($result['error']['text'], 'error');
            return TRUE;
        }

        if (empty($result['success'])) {
            hrk_ep_delete_session($db_session['sid']);
            drupal_set_message(t('You can not cancel your reservation, Amadeus return empty Cancel Status!'), 'error');
            return TRUE;
        }

        db_update('hrk_bf_book')->fields(array('is_cancel' => 1))->condition('bid', $book->bid)->execute();
        hrk_ep_delete_session($db_session['sid']);

        $to = '';
        if ($book->uid) {
            $user = user_load($book->uid);
            if ($user->mail != $book->email) {
                $to .= $user->mail . ',';
            }
        }
        $to .= $book->email;

        bf_mail_book($to, $book->bid);

//      if ($book->tid || $book->is_ticket) {
//        $rez = unitailer_cancel($book->uuid);
//        dsm($rez,'rez');
//      }

        drupal_set_message(t('Booking with a Book ID: @booking_id, Ticket ID: @ticket_id successfully canceled.', array(
            '@booking_id' => $book->cid,
            '@ticket_id' => ($book->tid) ? $book->tid : t('None'),
        )));
    } else {
        drupal_set_message(t('Booking not found', 'warning'));
    }
}