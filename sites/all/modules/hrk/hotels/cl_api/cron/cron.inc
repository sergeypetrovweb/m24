<?php

function cl_api_close_sessions()
{
    db_delete('hrk_cl_sessions')->condition('created', strtotime('- 40 minutes', REQUEST_TIME), '<=')->execute();
}
