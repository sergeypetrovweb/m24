<?php
global $language;
$l_prefix = ($language->language == 'en') ? 'en' : 'ru';
$path = drupal_get_path('theme', 'flight_modern');
currency_include('convert');
if (empty($bonus)) {
  $bonus = 0;
}
$price = round($book->price['fare'][Currency::init()->get_base_currency()] + $book->price['commission'][Currency::init()->get_base_currency()]);
//�������� ������ � ������� ����, ��� ��������� ���������� �������
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
$passengers = $book->passenger;
?>
<div class="filter_table">
<?php if (isset($flights[0][0][0]) && is_array($flights)): ?>
    <?php $flight = $flights[0][0][0]; ?>
    <?php $depart_info = $codes['airports'][$flight['departure_airport']]; ?>
    <?php $arrival_info = $codes['airports'][$flight['arrival_airport']]; ?>
    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 content_table">
        <table>
            <tr>
                <?php $logo = avis_all_get_logo($flight['marketing_airline']); ?>
                <td><img class="air-logo" src="<?php print $logo ?>"></td>
                <td><i class="glyphicon glyphicon-plane"></i><?php print $flight['marketing_airline'] . ' ' . $flight['flight_number']; ?></td>
                <td><i class="glyphicon glyphicon-time"></i><?php print format_date($flight['departure'], 'custom', 'd F Y | H:i') ?></td>
                <td>1 <i class="glyphicon glyphicon-triangle-bottom"></i></td>
                <td><img src="/<?php print $path ?>/images/places_table.png"> <?php print $flight['design_quantity'] ?></td>
                <td><?php print $depart_info['city']['name_' . $l_prefix]; ?> - <?php print $arrival_info['city']['name_' . $l_prefix]; ?></td>
                <td><?php print Currency::init()->price_html($price-$bonus);?>
                  <?php if ($bonus != 0): ?>
                  <span class="after-price-bonus">( <?php print Currency::init()->price_html($price); ?> )</span>
                  <?php endif; ?>
                </td>
            </tr>
        </table>
    </div>

    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 content_table_details">
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 details_avia">
            <?php if (isset($passengers) && is_array($passengers)): ?>

                        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 details_avia_row">
                            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                                <div><?php print t('Last Name') ?></div>
                                <?php foreach ($passengers as $passengers_group): ?>
                                    <?php foreach ($passengers_group as $passenger): ?>
                                        <div class="detail_bold"><?php print $passenger['last_name']; ?></div>
                                    <?php endforeach; ?>
                                <?php endforeach; ?>
                            </div>
                            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                                <div><?php print t('First Name') ?></div>
                                <?php foreach ($passengers as $passengers_group): ?>
                                    <?php foreach ($passengers_group as $passenger): ?>
                                        <div class="detail_bold"><?php print $passenger['first_name']; ?></div>
                                    <?php endforeach; ?>
                                <?php endforeach; ?>
                            </div>
                            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                                <div><?php print t('Birthday') ?></div>
                                <?php foreach ($passengers as $passengers_group): ?>
                                    <?php foreach ($passengers_group as $passenger): ?>
                                        <div class="detail_bold"><?php print $passenger['birthday']; ?></div>
                                    <?php endforeach; ?>
                                <?php endforeach; ?>
                            </div>
                            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
                                <div><?php print t('Passport number') ?></div>
                                <?php foreach ($passengers as $passengers_group): ?>
                                    <?php foreach ($passengers_group as $passenger): ?>
                                        <div class="detail_bold"><?php print $passenger['document']['id']; ?></div>
                                    <?php endforeach; ?>
                                <?php endforeach; ?>
                            </div>
                        </div>

            <?php endif; ?>

            <?php if (isset($flights) && is_array($flights)): ?>
                <?php foreach ($flights as $ref_num => $direction_flights): ?>
                    <?php foreach ($direction_flights as $dir => $unit_flights) : ?>
                            <?php foreach ($unit_flights as $index => $flight) : ?>
                                <?php $depart_info = $codes['airports'][$flight['departure_airport']]; ?>
                                <?php $arrival_info = $codes['airports'][$flight['arrival_airport']]; ?>
                            <?php
                            if(isset($timez[$depart_info['city']['code']]) && isset($timez[$arrival_info['city']['code']])) {
                                $dep_tz = new DateTimeZone($timez[$depart_info['city']['code']]);
                                $ar_tz = new DateTimeZone($timez[$arrival_info['city']['code']]);
                                $dep_time = new DateTime(date('Y-m-d H:i:s',$flight['departure']), $dep_tz);
//                                   $flight->departure = strtotime();
                                $ar_time = new DateTime(date('Y-m-d H:i:s',$flight['arrival']), $ar_tz);
                                $diff_time = date_diff($dep_time, $ar_time);
                                $in_air = format_interval(($diff_time->h * 3600) + ($diff_time->i * 60) + $diff_time->s);
                            }
                            ?>

                                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 details_avia_row">
                                    <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 avia_to"><i class="glyphicon glyphicon-plane to"></i><?php print $depart_info['city']['name_' . $l_prefix]; ?><br><span><?php print format_date($flight['departure'], 'custom', 'd F Y | H:i') ?></span></div>
                                    <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12"><?php print $flight['marketing_airline'] . ' ' . $flight['flight_number']; ?></div>
                                    <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12"><?php print $in_air?$in_air:''; ?></div>
                                    <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12"><?php print $arrival_info['city']['name_' . $l_prefix]; ?><br><?php print format_date($flight['arrival'], 'custom', 'd F Y | H:i') ?></div>
                                </div>
                            <?php endforeach; ?>
                    <?php endforeach; ?>
                <?php endforeach; ?>
            <?php endif; ?>
        </div>
    </div>

<?php endif; ?>

</div>
