<?php

function ep_api_close_sessions()
{
    $query = db_select('hrk_ep_sessions', 's');
    $query->fields('s', array('sid', 'session'));
    $query->condition('created', strtotime('- 15 minutes', REQUEST_TIME), '<=');

    $result = $query->execute();

    foreach ($result as $row) {
        $db_session[$row->sid] = (object)array(
            'sid' => $row->sid,
            'session' => unserialize($row->session)
        );
    }

    if (!empty($db_session)) {
        ep_api_include('EPower');

        $ep = new \includes\EPower();

        foreach ($db_session as $session) {
            if ($ep->connect($session->session)) {
                $ep->disconnect();
                \includes\EPower::deleteSession($session->sid);
            }
        }
    }
}
