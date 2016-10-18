<?php
//TODO remove phpcode from template
if (isset($variables['data'])) {
  $data = $variables['data'];
}
else {
  $data = array(
    1 => array(
      'img_src' => 'https://az712897.vo.msecnd.net/images/full/734AEB55-FFCE-4580-842B-11551A34957B.jpeg',
      'name' => 'Test1',
      'rating' => 4,
      'address' => 'Москва, Ленина 3б',
      'lower_price' => 299,
    ),
    2 => array(
      'img_src' => 'https://az712897.vo.msecnd.net/images/full/734AEB55-FFCE-4580-842B-11551A34957B.jpeg',
      'name' => 'Test2',
      'rating' => 5,
      'address' => 'Москва, Ленина 13б',
      'lower_price' => 29,
    ),
    3 => array(
      'img_src' => 'https://az712897.vo.msecnd.net/images/full/734AEB55-FFCE-4580-842B-11551A34957B.jpeg',
      'name' => 'Test3',
      'rating' => 5,
      'address' => 'Москва, Ленина 13б',
      'lower_price' => 229,
    ),
    4 => array(
      'img_src' => 'https://az712897.vo.msecnd.net/images/full/734AEB55-FFCE-4580-842B-11551A34957B.jpeg',
      'name' => 'Test4',
      'rating' => 3,
      'address' => 'Москва, Ленина 13б',
      'lower_price' => 29429,
    ),
    5 => array(
      'img_src' => 'https://az712897.vo.msecnd.net/images/full/734AEB55-FFCE-4580-842B-11551A34957B.jpeg',
      'name' => 'Test5',
      'rating' => 1,
      'address' => 'Москва, Ленина 13б',
      'lower_price' => 9,
    ),
  );
}

$path = 'sites/all/themes/flight_modern';
?>

<div
  class="col-lg-12 col-md-12 col-sm-12 col-xs-12 sort_hotel_result hotel-found"
  style="margin-top: 0;">
  <?php $hotel_index = 0; ?>
  <?php foreach ($data as $id => $hotel): ?>
    <?php $hotel = (object) $hotel; ?>

    <div
      class="col-lg-12 col-md-12 col-sm-12 col-xs-12 buy_hotel_block mix hotel-item hotel-item-<?php print $hotel_index; ?>">
      <div class="col-lg-2 col-md-3 col-sm-12 col-xs-12 thumb_hotel_buy">
        <?php $image = theme('imagecache_external', array(
          'path' => $hotel->img_src,
          'style_name' => 'hotels_thumbnails143x134',
          'alt' => $hotel->name,
          'title' => $hotel->name
        )); ?>
        <?php if ($image): ?>
          <?php print $image; ?>
        <?php else: ?>
          <?php print theme('image_style', array(
            'style_name' => 'hotels_thumbnails143x134',
            'path' => 'public://404.jpg',
            'width' => 298,
            'height' => 233
          )); ?>
        <?php endif; ?>
      </div>
      <div class="col-lg-10 col-md-9 col-sm-12 col-xs-12 content_hotel_buy">
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 block_name">
          <div class="col-lg-8 col-md-8 col-sm-8 col-xs-12 name-hotel">
            <span class="buy_name"><?php print $hotel->name; ?></span>
            <!--Рейтинг-->
            <?php for ($i = 1; $i <= 5; $i++): ?>
              <?php if ($i <= $hotel->rating): ?>
                <img src="/<?php print $path; ?>/images/big_star_active.png">
              <?php else: ?>
                <img src="/<?php print $path; ?>/images/big_star.png">
              <?php endif; ?>
            <?php endfor; ?>
            <!-- (конец) Рейтинг-->
          </div>
          <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12 price_sort">
            <?php print t('from') . ' ' ?><?php print Currency::init()
              ->price_html($hotel->lower_price); ?>
          </div>
        </div>
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 map_block">
          <div class="col-lg-6 col-md-6 col-sm-6 col-xs-6 geo-hotel"><img
              src="/<?php print $path; ?>/images/map_orange.png"> <?php print $hotel->address; ?>
          </div>
          <div
            class="col-lg-6 col-md-6 col-sm-6 col-xs-6 text-right choice_hotel">
            <a class="default-bb" href="#"><?php print t('Find'); ?></a>
          </div>
        </div>
      </div>
    </div>
    <?php $hotel_index++; ?>
  <?php endforeach; ?>
  <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 btn-blue-wrap">
    <a href="#" class="button-blue"><?php print t('All hotels'); ?></a>
  </div>
</div>