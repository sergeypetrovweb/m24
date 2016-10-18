<?php
//TODO Remove phpcode from template
$scl = Sklonyator::init();
$lang = $GLOBALS['language']->language;
?>

<div id="advanced_search" class="variant_one">
  <div class="container">
    <div class="title_adv_seacrh">
      <h1>Дешевые авиабилеты
        из <?php print $scl->get_fixed_name('city', $from, 'roditelniy'); ?>
        в <?php print $scl->get_fixed_name('city', $to, 'imenitelniy'); ?>
        от <?php print $price . ' руб.'; ?></h1>
    </div>
    <?php

    $from_arr = array(
      'q' => $scl->get_fixed_name('city', $from, 'imenitelniy'),
      'code' => $from,
    );

    $to_arr = array(
      'q' => $scl->get_fixed_name('city', $to, 'imenitelniy'),
      'code' => $to,
    );
    print render(drupal_get_form('simple_air_search', array(
      'from' => $from_arr,
      'to' => $to_arr
    )));
    ?>
  </div>
</div>

<div class="container landing_air">
  <h2>Сравнить цены на авиабилеты
    из <?php print $scl->get_fixed_name('city', $from, 'roditelniy'); ?>
    в <?php print $scl->get_fixed_name('city', $to, 'imenitelniy'); ?></h2>
  <?php
  $combinations = db_select('air_combinations', 'c')
    ->fields('c')
    ->condition('c.city_departure', $from)
    ->condition('c.city_arrival', $to)
    ->execute()
    ->fetchAll();

  if (!empty($combinations)) {
    print '<h3>Авиабилеты из ' . $scl->get_fixed_name('city', $from, 'roditelniy') . ' в ' . $scl->get_fixed_name('city', $to, 'imenitelniy') . '</h3>';
    print views_embed_view('air_combinations', 'lending_combo', arg(1), arg(2));
  }
  ?>

  <?php
  $calend = db_select('air_calendar', 'ac')
    ->fields('ac', array('month', 'price'))
    ->condition('ac.did', $id_route)
    ->condition('ac.price', 0, '>')
    ->condition('ac.time', '', '<>')
    ->execute()
    ->fetchAllKeyed(0, 1);

  ?>

  <?php if ($calend): ?>
    <h3>Динамика цен на
      авиабилеты <?php print $scl->get_fixed_name('city', $from, 'imenitelniy'); ?>
      – <?php print $scl->get_fixed_name('city', $to, 'imenitelniy'); ?></h3>
    <?php
    $max = max($calend);
    $top = '';
    $bottom = '';

    $count = db_select('air_calendar', 'ac')
      ->fields('ac', array('time', 'id'))
      ->condition('ac.id', 6500, '<=')
      ->condition('ac.time', '')
      ->execute()
      ->fetchAllKeyed(1, 0);

    //dsm($count);

    $calend_sort = $calend;

    asort($calend_sort);
    ///dsm($id_route);

    //dsm($calend_sort, '$calend_sort');
    $mon_m = array_keys($calend_sort);
    //dsm($mon_m, '$mon_m');

    $min_m = $mon_m[0];
    $max_m = $mon_m[count($mon_m) - 1];

    //$min_m = format_date(strtotime($m . '-15'), 'custom', 'M', NULL, 'ru');

    $min_price = min($calend);
    foreach ($calend as $m => $price) {
      $min = '';
      if ($price == $min_price) {
        $min = 'background:#E94E38; ';
      }
      $top .= '<div class="graf-col-wp"><div class="graf-col graf-col-1" style="' . $min . 'height: ' . ($price / ($max / 100)) . '%">' . Currency::init()
          ->price_html($price) . '</div></div>';
      $bottom .= '<div class="graf-col-wp"><div class="graf-col">' . format_date(strtotime($m . '-15'), 'custom', 'M', NULL, 'ru') . '</div></div>';
    }
    ?>

    <div class="graf lang">
      <?php print $top; ?>
    </div>
    <div class="graf mon">
      <?php print $bottom; ?>
    </div>
    <?php
    foreach ($combinations as $key => $variant) {
      if ($variant->price < $min_price || $key == 0) {
        $min_price = $variant->price;
        $low_cost_code = $variant->airline_code;
      }
    }

    $low_cost_airline = db_select('hrk_sf_airlines', 'a')
      ->fields('a', array('name'))
      ->condition('a.code', $low_cost_code)
      ->execute()
      ->fetchField();
    ?>
    <p class="land_p">По нашим данным <?php print $low_cost_airline; ?> самая
      дешевая авиакомпания, летающая по
      направлению <?php print $scl->get_fixed_name('city', $from, 'imenitelniy'); ?>
      – <?php print $scl->get_fixed_name('city', $to, 'imenitelniy'); ?>.</p>
    <p class="land_p">В нашей поисковой базе 12 авиакомпаний предлагают билеты
      на данный и альтернативные маршруты.</p>
    <p class="land_p">Самое дешевое время года для покупки авиабилетов
      из <?php print $scl->get_fixed_name('city', $from, 'roditelniy'); ?>
      в <?php print $scl->get_fixed_name('city', $to, 'imenitelniy'); ?>
      - <?php print t(date('F', strtotime($min_m . '-15')), array(), array('context' => 'im_pad_month')); ?>
      . Самое дорогое
      - <?php print t(date('F', strtotime($max_m . '-15')), array(), array('context' => 'im_pad_month')); ?>
      . </p>
  <?php endif; ?>

  <?php
  //TODO uncomment block when hotels functionality has been fixed
  //  $data = db_select('air_hotels', 'a')
  //    ->fields('a')
  //    ->condition('a.location_code', $to)
  //    ->execute()
  //    ->fetchAll();
  //if ($data):
  ?>
  <!--  <section id="top-hotels" class="clearfix">-->
  <!--    <h3>-->
  <?php //print 'Отели '.$scl->get_fixed_name('city', $to, 'roditelniy'); ?><!-- </h3>-->
  <!--    --><?php //print theme('five_hotels_block', array('data'=> $data)) ?>
  <!--  </section>-->
  <?php //endif; ?>

  <?php
  print theme('avis_weather_block', array('code' => $to));
  ?>
  <?php
  $info_nid = db_select('field_data_field_city_code', 'c')
    ->fields('c', array('entity_id'))
    ->condition('c.field_city_code_value', $to)
    ->execute()
    ->fetchField();

  if (!empty($info_nid)):
    $info = node_load($info_nid);
    ?>

    <section id="city-info">
      <h3><?php print t('Basic information about') . ' ' . $scl->get_fixed_name('city', $to, 'predlojniy');
        if ($user->uid == 1) {
          print ' ' . l('(редактировать)', 'node/' . $info->nid . '/edit', array('attributes' => array('style' => 'font-size:18px; color:#444444;')));
        } ?></h3>

      <div class="city-text">
        <?php print $info->body[LANGUAGE_NONE][0]['safe_value']; ?>
      </div>
      <div class="city-imgs">
        <?php
        foreach ($info->field_city_photos[LANGUAGE_NONE] as $img) {
          print '<div class="city-img-wrap">' . theme('image_style', array(
              'style_name' => 'landing_photos',
              'path' => $img['uri']
            )) . '</div>';
        }
        ?>
      </div>
    </section>
  <?php endif; ?>

  <?php
  $getnames = db_select('hrk_sf_cities', 'p');
  $getnames->innerJoin('hrk_sf_airports', 'u', 'u.ctid = p.ctid');
  $getnames->fields('u', array('ctid', 'code', 'name_en', 'name_ru'));
  $getnames->condition('p.code', $to);
  $getnames = $getnames->execute()->fetchAll();
  ?>

  <section id="airports-list">
    <h3><?php print t('Airports') . ' ' . $scl->get_fixed_name('city', $to, 'roditelniy'); ?></h3>
    <ul>
      <?php
      $name = 'name_' . $lang;
      foreach ($getnames as $airport) {
        print '<li>' . $scl->get_fixed_name('city', $to, 'imenitelniy') . ', ' . $airport->$name . ' (' . $airport->code . ')</li>';
      }
      ?>
    </ul>
  </section>

  <section id="come-form-list">
    <h3><?php print t('Airtickets') . ' ' . t('from', array(), array('context' => 'from_city')) . ' ' . $scl->get_fixed_name('city', $to, 'vinitelniy'); ?></h3>
    <ul class="clearfix">
      <?php
      $directions = db_select('avis_parsing_directions', 'd')
        ->fields('d')
        ->condition('d.code_to', $to)
        ->execute()
        ->fetchAll();

      foreach ($directions as $direct) {
        $name = $scl->get_fixed_name('city', $direct->code_from, 'vinitelniy');
        if (mb_substr($name, -1) != 'у') {
          $name = $scl->get_fixed_name('city', $direct->code_from, 'imenitelniy');
        }
        print '<li><a href="/' . $lang . '/route/' . $to . '/' . $direct->code_from . '">' . t('Airtickets') . ' ' . t('to') . ' ' . $name . '</a></li>';
      }
      ?>
    </ul>
  </section>
</div>
