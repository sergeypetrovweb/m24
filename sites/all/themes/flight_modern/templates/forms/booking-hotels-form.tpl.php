<?php
$path = 'sites/all/themes/flight_modern';
$hotel = (object)$form['#hotel'];
?>
<div id="content">
  <div class="container">

    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 buy_hotel_block">
      <div class="col-lg-4 col-md-4 col-sm-12 col-xs-12 thumb_hotel_buy">
        <?php if (isset($hotel->images[0]['src'])): ?>
          <?php $image = theme('imagecache_external', array('path' => $hotel->images[0]['src'], 'style_name' => 'hotels_thumbnails', 'alt' => $hotel->name, 'title' => $hotel->name)); ?>
          <?php if ($image): ?>
            <?php print $image; ?>
          <?php else: ?>
            <?php print theme('image_style', array('style_name' => 'hotels_thumbnails', 'path' => 'public://404.jpg', 'width' => 298, 'height' => 233)); ?>
          <?php endif; ?>
        <?php endif; ?>
      </div>
      <div class="col-lg-8 col-md-8 col-sm-12 col-xs-12 content_hotel_buy">
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 block_name">
          <div class="col-lg-8 col-md-8 col-sm-8 col-xs-12">
            <span class="buy_name"><?php print $hotel->name; ?></span>
            <!--Рейтинг-->
            <?php for ($i = 1; $i <= 5; $i++): ?>
              <?php if ($i < $hotel->rating): ?>
                <img src="/<?php print $path; ?>/images/big_star_active.png">
              <?php else: ?>
                <img src="/<?php print $path; ?>/images/big_star.png">
              <?php endif; ?>
            <?php endfor; ?>
            <!-- (конец) Рейтинг-->
          </div>
          <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12 value_users">
            <?php if (!empty($hotel->trip_adv) &&!empty($hotel->trip_adv['rating'])): ?>
              <?php print t('Visitors rating') ?> <span class="value"><?php print $hotel->trip_adv['rating']; ?></span>
            <?php endif; ?>
          </div>
        </div>
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 map_block">
          <img src="/<?php print $path; ?>/images/map_orange.png"> <?php print $hotel->address; ?>
<!--          <a href="#">Показать на карте</a>-->
        </div>
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
          <div class="col-lg-6 col-md-6 col-sm-6 col-xs-12">

              <?php
              $apartment_name = '';
              foreach ($hotel->packages as $room) {

                  foreach ($room['rooms'] as $room_id) {
                      $apartment_name = $room_id['type_original'];
                  }
              }
              ?>
            <a class="apartment-name-header"><?php print $apartment_name ?></a>
          </div>
<!--          <div class="col-lg-6 col-md-6 col-sm-6 col-xs-12 text-right"><a href="#" class="other_rooms">другие номера</a></div>-->
        </div>
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 time">
          <?php print t('Residence time:') ?> <span><?php print format_date($hotel->_sh_params['check_in'], 'custom', 'd.m') ?> - <?php print format_date($hotel->_sh_params['check_out'], 'custom', 'd.m') ?> (<?php print $hotel->_sh_params['nights'] . ' ' . t('nights') ?>)</span>
        </div>
      </div>

        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 you_data">
            <div class="contact-form-wrapper">
                <?php print render($form['contact']) ?>

                <?php print render($form['credit_card']) ?>
            </div>
        </div>

        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 you_data you_rooms">
            <?php print render($form['rooms']) ?>
        </div>

        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 payment payment-price">
            <?php print render($form['price']) ?>
            <?php print render($form['payment_container']) ?>
        </div>

        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 payment">
            <?php
            $package_id = !empty($form['package_id']['#value']) ? $form['package_id']['#value'] : null;
            $room_id = !empty($form['rooms'][0]) ? $form['rooms'][0]['id']['#value'] : null;
            if ($package_id && $room_id) {
                print theme('bh_room_info', array('room' => $hotel->packages[$package_id]['rooms'][$room_id]));
            }
            ?>

            <?php print render($form['policy']); ?>
        </div>

        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 text-center accept">
            <?php print render($form['agree_to_the_rules']); ?>
            <?php print render($form['actions']['book']); ?>
        </div>
    </div>
  </div>
</div>

<?php unset($form['header']) ?>

<?php print drupal_render_children($form); ?>
