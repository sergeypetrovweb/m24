<?php

function search_hotels_delete_results()
{
    db_delete('hrk_sh_results')->condition('created', strtotime('- 40 minutes', REQUEST_TIME), '<=')->execute();
}
