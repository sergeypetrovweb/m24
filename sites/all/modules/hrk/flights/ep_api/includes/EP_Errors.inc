<?php
/**
 * Created by PhpStorm.
 * User: Droid
 * Date: 10.09.14
 * Time: 20:01
 */

namespace includes;


class EP_Errors
{
    const ERROR_SEARCH = 1;
    const ERROR_BOOKING = 2;
    const ERROR_RULES = 3;

    public function save($session, $error_body, $type)
    {
        $query = db_insert('hrk_ep_errors');
        $query->fields(array(
            'created' => REQUEST_TIME,
            'session' => serialize($session),
            'error' => serialize($error_body),
            'type' => $type
        ));

        $eid = $query->execute();

        return $eid;
    }

} 