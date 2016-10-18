<?php $path = drupal_get_path('theme', 'flight_modern') ?>
<?php currency_include('convert'); ?>

<?php
$price_high = 0;
$price_low = 0;

foreach ($hotels as $id => $hotel) {
    if ($hotel['lower_price'] > $price_high) {
        $price_high = $hotel['lower_price'];
        //dsm($price_high);
    }

    if (!empty($price_low) && $hotel['lower_price'] < $price_low || empty($price_low)) {
        $price_low = $hotel['lower_price'];
        //dsm($price_low);
    }
}
?>

    <!--  <div id="simple_mini_filter">
    <div class="container">
      <?php /*print render(drupal_get_form('search_hotels_search_form', 'mini')); */?>
    </div>
  </div>-->

    <div id="sort">
        <div class="container">
            <span><?php print t('Sorting') ?>: </span>
            <ul>
                <li><a class="sort-link" data-order="desc" data-type="price"><?php print t('price') ?></a></li>
                <li><a class="sort-link" data-order="desc" data-type="rating"><?php print t('stars') ?></a></li>
                <li><a class="sort-link" data-order="desc" data-type="name"><?php print t('title') ?></a></li>
<!--                <li><a class="sort-link" data-order="desc" data-type="popularity">--><?php //print t('popularity') ?><!--</a></li>-->
<!--                <li><a class="sort-link" data-order="desc" data-type="reviews">--><?php //print t('reviews') ?><!--</a></li>-->
            </ul>
        </div>
    </div>

    <div id="content">
        <div class="container hotel-container">
            <div class="price-range">
                <span class="cheap">
                    <?php
                      $price_low = Currency::init()->convert($price_low, 'RUB', Currency::init()->get_base_currency());
                       print Currency::init()->price_html($price_low)
                    ?>
                </span>
                <span class="expensive">
                    <?php
                    $price_high = Currency::init()->convert($price_high, 'RUB', Currency::init()->get_base_currency());
                    print Currency::init()->price_html($price_high)
                    ?>
                </span>
                <span class="cheap_native"><?php print $price_low ?></span>
                <span class="expensive_native"><?php print $price_high ?></span>
            </div>

            <?php print render(drupal_get_form('search_hotels_result_filter',$filters));?>

            <div class="hotels-map-container">
                <div id="hotels-main-map" class="map"></div>
            </div>

            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 sort_hotel_result hotel-found">

                <?php $result_link = hrk_sh_make_results_page_link($request_params);?>
                <?php $hotel_index = 0;?>
                <?php foreach ($hotels as $id => $hotel): ?>
                    <?php $hotel = (object)$hotel; ?>
                    <?php
                    $hotel_data = array();
                    $hotel_data[] = 'data-price="' . Currency::init()->get_price($hotel->lower_price) . '"';
                    $hotel_data[] = 'data-rating="' . $hotel->rating . '"';
                    $hotel_data[] = 'data-lat="' . $hotel->location['latitude'] . '"';
                    $hotel_data[] = 'data-lng="' . $hotel->location['longitude'] . '"';
                    $hotel_data[] = 'data-name="' . strtolower($hotel->name) . '"';
                    $hotel_data[] = 'data-hotel-item="' . $hotel_index . '"';
                    ?>

                    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 buy_hotel_block mix hotel-item hotel-item-<?php print $hotel_index;?>  <?php print $hotel->classes; ?>" <?php print implode(' ', $hotel_data); ?>>
                        <div class="col-lg-2 col-md-3 col-sm-12 col-xs-12 thumb_hotel_buy">
                            <?php $image = theme('imagecache_external', array('path' => $hotel->img_src, 'style_name' => 'hotels_thumbnails143x134', 'alt' => $hotel->name, 'title' => $hotel->name)); ?>
                            <?php if ($image): ?>
                                <?php print $image; ?>
                            <?php else: ?>
                                <?php print theme('image_style', array('style_name' => 'hotels_thumbnails143x134', 'path' => 'public://404.jpg', 'width' => 298, 'height' => 233)); ?>
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
                                    <?php print t('from').' ' ?>
                                    <?php
                                        $price_base = Currency::init()->convert($hotel->lower_price, 'RUB', Currency::init()->get_base_currency());
                                        print Currency::init()->price_html($price_base);
                                    ?>
                                </div>
                            </div>
                            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 map_block">
                                <div class="col-lg-6 col-md-6 col-sm-6 col-xs-6 geo-hotel"><img src="/<?php print $path; ?>/images/map_orange.png"> <?php print $hotel->address; ?></div>
                                <div class="col-lg-6 col-md-6 col-sm-6 col-xs-6 text-right choice_hotel">
                                    <a class="default-bb" href="<?php print url($result_link . '/' . $hotel->id); ?>"><?php print t('Select Room'); ?></a>
                                    <a class="default-bb more-bb" href="<?php print url($result_link . '/' . $hotel->id); ?>"><?php print t('Read more'); ?></a>
                                </div>
                            </div>
                        </div>
                    </div>
                    <?php $hotel_index++;?>
                <?php endforeach; ?>
            </div>
            <div id="pagination" class="pagination"></div>
        </div>
    </div>


<?php if(0): ?>


    <div class="hotel-item hotel-item-<?php print $hotel_index;?>  <?php print $hotel->classes; ?>" <?php print implode(' ', $hotel_data); ?>>

        <?php $image = theme('imagecache_external', array('path' => $hotel->img_src, 'style_name' => 'hotels_thumbnails', 'alt' => $hotel->name, 'title' => $hotel->name)); ?>
        <?php if ($image): ?>
            <?php print $image; ?>
        <?php else: ?>
            <?php print theme('image_style', array('style_name' => 'hotels_thumbnails', 'path' => 'public://404.jpg', 'width' => 298, 'height' => 233)); ?>
        <?php endif; ?>
        <div class="hotel-top">
            <div class="hotel-stars">
                <?php for ($i = 1; $i <= $hotel->rating; $i++): ?>
                    <div class="star"></div>
                <?php endfor; ?>
            </div>
            <div class="hotel-detector"></div>
        </div>
        <div class="hotel-middle">
            <?php if (!empty($hotel->trip_adv) &&!empty($hotel->trip_adv['rating'])): ?>
                <?php $rating = intval($hotel->trip_adv['rating']); ?>
                <div class="owl"></div>
                <?php for ($i = 1; $i <= 5; $i++): ?>
                    <?php if ($i <= $rating): ?>
                        <div class="owl-dot active"></div>
                    <?php elseif ($i == $rating): ?>
                        <div class="owl-dot active"></div>
                        <?php if ($hotel->trip_adv['rating'] - $rating): $i++ ?>
                            <div class="owl-dot half"></div>
                        <?php endif; ?>
                        <?php
                    else: ?>
                        <div class="owl-dot"></div>
                    <?php endif; ?>
                <?php endfor; ?>
            <?php endif; ?>
        </div>
        <div class="hotel-bottom">
            <h3><?php print $hotel->name; ?></h3>

            <div>
                <div class="hotel-price">
                    <?php currency_include('convert'); ?>
                    <?php print t('from'); ?>
                    <span><?php print ceil($hotel->lower_price) . currency_get_prefix(); ?></span>
                </div>
                <a href="<?php print url($result_link . '/' . $hotel->id); ?>"><?php print t('Select Room'); ?></a>
            </div>
        </div>
        <div class="map-hotel-info">
            <div class="map-hotel-name"><h3><?php print $hotel->name; ?></h3></div>
            <div class="map-hotel-body">
                <div class="map-hotels-image">
                    <?php $image = theme('imagecache_external', array('path' => $hotel->img_src, 'style_name' => 'hotels_thumbnails_map', 'alt' => $hotel->name, 'title' => $hotel->name)); ?>
                    <?php if ($image): ?>
                        <?php print $image; ?>
                    <?php else: ?>
                        <?php print theme('image_style', array('style_name' => 'hotels_thumbnails_map', 'path' => 'public://404.jpg','alt' => $hotel->name, 'title' => $hotel->name)); ?>
                    <?php endif; ?>
                </div>
                <div class="map-hotel-right">
                    <div class="map-hotel-stars">
                        <?php for ($i = 1; $i <= $hotel->rating; $i++): ?>
                            <div class="star"></div>
                        <?php endfor; ?>
                    </div>
                    <div class="hotel-address"><?php print $hotel->address; ?></div>
                </div>
            </div>
            <div class="map-hotel-description">
                <div class="hotel-area"><?php print trim($hotel->area); ?></div>
                <div class="hotel-district"><?php print trim($hotel->district); ?></div>
            </div>
        </div>
    </div>




    <div class="hotel-container">
        <div class="hotel-filters">
            <?php print render(drupal_get_form('search_hotels_result_filter',$filters));?>
        </div>

        <div class="hrk-clearfix"></div>

        <div class="hotel-access-line">
            <div class="access">
                <?php print t('Hotels found: '); ?><span><?php print count($hotels); ?></span>
            </div>
            <div class="hide-map">
                <a class="hide-map-link" href="#"><?php print t('Hide map'); ?></a>
                <a class="show-map-link" style="display: none" href="#"><?php print t('Show map'); ?></a>
            </div>
        </div>

        <div class="hrk-clearfix"></div>

        <div class="hotels-map-container">
            <div id="hotels-main-map" class="map"></div>
        </div>

        <div class="hotel-found">
            <?php $result_link = hrk_sh_make_results_page_link($request_params);?>
            <?php $hotel_index = 0;?>
            <?php foreach ($hotels as $id => $hotel): ?>
                <?php $hotel = (object)$hotel; ?>
                <?php
                $hotel_data = array();
                $hotel_data[] = 'data-price="' . ceil($hotel->lower_price) . '"';
                $hotel_data[] = 'data-rating="' . $hotel->rating . '"';
                $hotel_data[] = 'data-lat="' . $hotel->location['latitude'] . '"';
                $hotel_data[] = 'data-lng="' . $hotel->location['longitude'] . '"';
                $hotel_data[] = 'data-name="' . strtolower($hotel->name) . '"';
                $hotel_data[] = 'data-hotel-item="' . $hotel_index . '"';
                ?>


                <div class="hotel-item hotel-item-<?php print $hotel_index;?>  <?php print $hotel->classes; ?>" <?php print implode(' ', $hotel_data); ?>>

                    <?php $image = theme('imagecache_external', array('path' => $hotel->img_src, 'style_name' => 'hotels_thumbnails', 'alt' => $hotel->name, 'title' => $hotel->name)); ?>
                    <?php if ($image): ?>
                        <?php print $image; ?>
                    <?php else: ?>
                        <?php print theme('image_style', array('style_name' => 'hotels_thumbnails', 'path' => 'public://404.jpg', 'width' => 298, 'height' => 233)); ?>
                    <?php endif; ?>
                    <div class="hotel-top">
                        <div class="hotel-stars">
                            <?php for ($i = 1; $i <= $hotel->rating; $i++): ?>
                                <div class="star"></div>
                            <?php endfor; ?>
                        </div>
                        <div class="hotel-detector"></div>
                    </div>
                    <div class="hotel-middle">
                        <?php if (!empty($hotel->trip_adv) &&!empty($hotel->trip_adv['rating'])): ?>
                            <?php $rating = intval($hotel->trip_adv['rating']); ?>
                            <div class="owl"></div>
                            <?php for ($i = 1; $i <= 5; $i++): ?>
                                <?php if ($i <= $rating): ?>
                                    <div class="owl-dot active"></div>
                                <?php elseif ($i == $rating): ?>
                                    <div class="owl-dot active"></div>
                                    <?php if ($hotel->trip_adv['rating'] - $rating): $i++ ?>
                                        <div class="owl-dot half"></div>
                                    <?php endif; ?>
                                    <?php
                                else: ?>
                                    <div class="owl-dot"></div>
                                <?php endif; ?>
                            <?php endfor; ?>
                        <?php endif; ?>
                    </div>
                    <div class="hotel-bottom">
                        <h3><?php print $hotel->name; ?></h3>

                        <div>
                            <div class="hotel-price">
                                <?php currency_include('convert'); ?>
                                <?php print t('from'); ?>
                                <span><?php print ceil($hotel->lower_price) . currency_get_prefix(); ?></span>
                            </div>
                            <a href="<?php print url($result_link . '/' . $hotel->id); ?>"><?php print t('Select Room'); ?></a>
                        </div>
                    </div>
                    <div class="map-hotel-info">
                        <div class="map-hotel-name"><h3><?php print $hotel->name; ?></h3></div>
                        <div class="map-hotel-body">
                            <div class="map-hotels-image">
                                <?php $image = theme('imagecache_external', array('path' => $hotel->img_src, 'style_name' => 'hotels_thumbnails_map', 'alt' => $hotel->name, 'title' => $hotel->name)); ?>
                                <?php if ($image): ?>
                                    <?php print $image; ?>
                                <?php else: ?>
                                    <?php print theme('image_style', array('style_name' => 'hotels_thumbnails_map', 'path' => 'public://404.jpg','alt' => $hotel->name, 'title' => $hotel->name)); ?>
                                <?php endif; ?>
                            </div>
                            <div class="map-hotel-right">
                                <div class="map-hotel-stars">
                                    <?php for ($i = 1; $i <= $hotel->rating; $i++): ?>
                                        <div class="star"></div>
                                    <?php endfor; ?>
                                </div>
                                <div class="hotel-address"><?php print $hotel->address; ?></div>
                            </div>
                        </div>
                        <div class="map-hotel-description">
                            <div class="hotel-area"><?php print trim($hotel->area); ?></div>
                            <div class="hotel-district"><?php print trim($hotel->district); ?></div>
                        </div>
                    </div>
                </div>
                <?php $hotel_index++;?>
            <?php endforeach; ?>
        </div>
        <div id="pagination" class="pagination"></div>
    </div>

<?php endif; ?>