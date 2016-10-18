<?php
global $language;
$l_prefix = ($language->language == 'en') ? 'en' : 'ru';
$path = drupal_get_path('theme', 'flight_modern');

//Приведем данные к нужному виду, для упрощения читаемости шаблона
if(isset($codes['airports']) && !empty($codes['airports'])) {
    $need_timez = array();
    foreach($codes['airports'] as $some_airport) {
        $need_timez[] = $some_airport['city']['code'];
    }
    $timez = db_select('hrk_sf_cities', 'n')
        ->fields('n', array('code', 'tz'))
        ->condition('n.code', $need_timez, 'IN')
        ->execute()
        ->fetchAllKeyed(0,1);

    foreach($timez as $i => $tz) {
      if ($tz == 'Not found') {
        $timez[$i] = 'Europe/Moscow';
      }
    }
}
?>

<div id="filter">
    <div class="container">
        <?php if (isset($combination['index_list']) && isset($flights) && isset($search_params) && isset($codes)): ?>

            <?php foreach ($combination['index_list'] as $dir => $ref): ?>
                <?php $com_flights = $flights[$ref][$dir]; ?>
                <?php $direction_class = (isset($search_params['direction_type']) && $search_params['direction_type'] == 'round_trip' && $dir == 1) ? 'from' : 'to' ?>


                    <?php foreach ($com_flights as $index => $flight): ?>
                        <?php $flight = (object)$flight; ?>
                        <?php $next_flight = isset($comb_flights[$index + 1]) ? (object)$comb_flights[$index + 1] : array(); ?>
                        <?php $depart_info = $codes['airports'][$flight->departure_airport]; ?>
                        <?php $arrival_info = $codes['airports'][$flight->arrival_airport]; ?>

                        <?php $logo = avis_all_get_logo($flight->marketing_airline); ?>

                        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 company_details">
                            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 company_logo">
                                <img src="<?php print $logo ?>" class="air-logo">
                                <a href="#"><?php print $depart_info['city']['name_' . $l_prefix]; ?> - <?php print $arrival_info['city']['name_' . $l_prefix]; ?></a>
                                <span><i class="glyphicon glyphicon-plane"></i> <?php print $flight->marketing_airline . ' ' . $flight->flight_number ?></span>
                            </div>

                            <?php
                            if(isset($timez[$depart_info['city']['code']]) && isset($timez[$arrival_info['city']['code']])) {
                                    $dep_tz = new DateTimeZone($timez[$depart_info['city']['code']]);
                                   $ar_tz = new DateTimeZone($timez[$arrival_info['city']['code']]);
                                   $dep_time = new DateTime(date('Y-m-d H:i:s',$flight->departure), $dep_tz);
//                                   $flight->departure = strtotime();
                                   $ar_time = new DateTime(date('Y-m-d H:i:s',$flight->arrival), $ar_tz);
                                   $diff_time = date_diff($dep_time, $ar_time);
                                   $in_air = format_interval(($diff_time->h * 3600) + ($diff_time->i * 60) + $diff_time->s);
                                }
                            ?>
                            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                                <p><?php print t('Departure', array(), array('context' => 'flights_results')); ?>: <span class="red_time"><?php print format_date($flight->departure, 'medium', 'H:i'); ?></span><br>
                                    <?php print format_date($flight->departure, 'medium', 'j F Y'); ?><br>
                                    <?php print $depart_info['name_' . $l_prefix].' ('.$flight->departure_airport.')'; ?></p>
                            </div>
                            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                                <p><?php print t('Flight duration') . ': ' . ($in_air? $in_air:'');?><br>
                                    </p>
                            </div>
                            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                                    <p><?php print t('Arrival', array(), array('context' => 'flights_results')); ?>: <span class="red_time"><?php print format_date($flight->arrival, 'medium', 'H:i'); ?></span><br>
                                    <?php print format_date($flight->arrival, 'medium', 'j F Y'); ?><br>
                                    <?php print $arrival_info['name_' . $l_prefix].' ('.$flight->arrival_airport.')'; ?></p>
                            </div>
                        </div>
                    <?php endforeach; ?>
            <?php endforeach; ?>
        <?php endif; ?>
    </div>
</div>

