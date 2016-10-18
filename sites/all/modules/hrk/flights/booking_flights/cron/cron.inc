<?php

function booking_flights_check_expire()
{

    $query = db_select('hrk_bf_book', 'b')->fields('b', array())
        ->condition('expire', REQUEST_TIME, '<=')
        ->condition('is_cancel', 0)
        ->condition('is_deleted', 0)
        ->condition('is_ticket', 0);

    $result = $query->execute();

    foreach ($result as $row) {
        hrk_bf_update_book($row->bid, array('is_cancel' => 1));

        $to = '';
        if ($row->uid) {
            $user = user_load($row->uid);
            if ($user->mail != $row->email) {
                $to .= $user->mail . ',';
            }
        }

        $to .= $row->email;

        bf_mail_book($to, $row->bid);
    }

}