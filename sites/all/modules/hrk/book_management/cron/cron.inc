<?php

function book_management_check_booking_status()
{

    $query = db_select('hrk_bh_book', 'b')->fields('b', array())
        ->condition('is_cancel', 0);

    $result = $query->execute();

    foreach ($result as $row) {

        $db_session = hrk_cl_create_session();

        $request = hrk_cl_check_book_status($db_session['session'], $row->seid);

        $cl = hrk_cl_engine();
        $response = $cl->doRequest($request->getRequest(), $request::SOAP_ACTION);

        if (!$response) {
            hrk_cl_delete_session($db_session['sid']);
            continue;
        };

        bh_include('BH_Helper');
        /*GET STATUS*/
        $result = \includes\BH_Helper::parseCheckBookingStatusResponse($response);

        if (!empty($result['error'])) {
            hrk_cl_errors()->save($db_session['session'], array($result['error']), \includes\CL_Errors::ERROR_BOOKING);
            continue;
        }

        if (empty($result['status'])) {
            hrk_cl_delete_session($db_session['sid']);
            continue;
        }

        if ($result['status'] == 'CX') {
            db_update('hrk_bh_book')->fields(array('is_cancel' => 1))->condition('bid', $row->bid)->execute();
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

        if ($result['status'] == 'OK') {
            db_update('hrk_bh_book')->fields(array('is_cancel' => 0))->condition('bid', $row->bid)->execute();
            hrk_cl_delete_session($db_session['sid']);
        }
    }

}