<?php

function booking_hotels_check_expire()
{

    $query = db_select('hrk_bh_book', 'b')->fields('b', array())
        ->condition('expire', REQUEST_TIME, '<=')
        ->condition('is_cancel', 0)
        ->condition('is_paid',0);

    $result = $query->execute();

    foreach ($result as $row) {

        $db_session = hrk_cl_create_session();

        $request = hrk_cl_cancel_book($db_session['session'], $row->seid);

        $cl = hrk_cl_engine();
        $response = $cl->doRequest($request->getRequest(), $request::SOAP_ACTION);

        if(!$response) {
            hrk_cl_delete_session($db_session['sid']);
            continue;
        };

        bh_include('BH_Helper');
        $result = \includes\BH_Helper::parseCancelResponse($response);

        if ($result['error']) {
            hrk_cl_errors()->save($db_session['session'], array($result['error']), \includes\CL_Errors::ERROR_BOOKING);
            continue;
        }

        if(empty($result['cancel_id'])){
            hrk_cl_delete_session($db_session['sid']);
            continue;
        }

        db_update('hrk_bh_book')->fields(array('is_cancel' => 1, 'cancel_id' => $result['cancel_id']))->condition('bid', $row->bid)->execute();
        hrk_cl_delete_session($db_session['sid']);


        $to = '';
        if ($row->uid) {
            $user = user_load($row->uid);
            if ($user->mail != $row->email) {
                $to .= $user->mail . ',';
            }
        }
        $to .= $row->email;

        bh_mail_book($to, $row->bid);
    }

}