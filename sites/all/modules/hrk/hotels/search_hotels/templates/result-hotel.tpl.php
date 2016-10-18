<?php if (!empty($hotel)): ?>
    <?php $hotel = (object)$hotel; ?>

    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 sort_hotel_result details <?php print $classes;?>">
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 buy_hotel_block">

            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 block_name">
                <div class="col-lg-6 col-md-6 col-sm-6 col-xs-12">
                    <span class="buy_name"><?php print $hotel->name ?></span>
                    <?php for ($i = 1; $i <= $hotel->rating; $i++): ?>
                        <img src="/sites/all/themes/flight_modern/images/big_star_active.png">
                    <?php endfor; ?>
                    <?php for ($i = 5; $i > $hotel->rating; $i--): ?>
                        <img src="/sites/all/themes/flight_modern/images/big_star.png">
                    <?php endfor; ?>

                </div>
                <div class="col-lg-6 col-md-6 col-sm-6 col-xs-12 value_users">
                    <?php if (isset ($hotel->trip_adv)) : ?>
                        <?php print t('Visitors rating') ?> <span class="value"><?php print $hotel->trip_adv['rating'] ?></span>
                    <?php endif; ?>
                </div>
                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 map_block">
                    <img src="/sites/all/themes/flight_modern/images/map_orange.png"> <span><?php print $hotel->address ?></span>
                    <?php if (!empty($addition_info)): ?>
                        <?php $addition_info = (object)$addition_info; ?>
<!--                        <div class="hotel_length">
                        <span>
                            <?php /*print $addition_info->nights . ' '; */?><?php /*print format_plural(($addition_info->nights % 2), t('night'), t('nights')); */?>
                        </span>
                            <?php /*$format_check_in = format_date($addition_info->check_in, 'medium', 'j F'); */?>
                            <?php /*$format_check_out = format_date($addition_info->check_out, 'medium', 'j F'); */?>
                            <?php /*print t('during the period from @check_in to @check_out', array('@check_in' => $format_check_in, '@check_out' => $format_check_out)); */?>
                        </div>-->
                    <?php endif; ?>
                    <a class="hotel-show-on-map"><?php print t('show on map') ?></a>
                    <a class="hotel-hide-map hidden"><?php print t('hide map') ?></a>
                    <?php if (!empty($back_path)): ?>
<!--                        <a class="hotel-back" href="--><?php //print url($back_path); ?><!--">--><?php //print t('other hotels'); ?><!--</a>-->
                    <?php endif; ?>
                    <div class="hotel-map-container">
                        <div id="hotel-main-map" class="map" data-lng="<?php print $hotel->longitude; ?>" data-lat="<?php print $hotel->latitude; ?>"></div>
                    </div>
                </div>
            </div>

            <div class="col-lg-4 col-md-4 col-sm-12 col-xs-12 thumb_hotel_buy">
                <div class="hotel-slider-slides flexslider">
                    <ul class="slides">
                        <?php foreach ($hotel->images as $image): ?>
                            <?php $html_img = theme('imagecache_external', array('path' => $image['src'], 'style_name' => 'hotel_detail_slider', 'alt' => $hotel->name, 'title' => $hotel->name)); ?>
                            <?php if ($html_img): ?>
                                <li>
                                    <?php print $html_img; ?>
                                </li>
                            <?php endif; ?>
                        <?php endforeach; ?>
                    </ul>
                </div>
                <div class="hotel-slider-carousel flexslider">
                    <ul class="slides">
                        <?php foreach ($hotel->images as $image): ?>
                            <?php $html_img_thumb = theme('imagecache_external', array('path' => $image['src'], 'style_name' => 'hotel_detail_slider_thumb', 'alt' => $hotel->name, 'title' => $hotel->name)); ?>
                            <?php if ($html_img_thumb): ?>
                                <li>
                                    <?php print $html_img_thumb; ?>
                                </li>
                            <?php endif; ?>
                        <?php endforeach; ?>
                    </ul>
                </div>
            </div>

            <div class="col-lg-8 col-md-8 col-sm-12 col-xs-12 content_hotel_buy">

                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 descrip">
                    <?php if(!empty($hotel->description)):?>
                        <?php foreach ($hotel->description as $description):?>
                            <p><?php print $description; ?></p>
                        <?php endforeach;?>
                    <?php endif;?>
                </div>
                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 in-hotel">
                    <h3><?php print t('Facilities') . ':' ?></h3>

                    <?php
                    $facilities = null;
                    if (!empty($hotel->facilities)) {
                        $count = round(count($hotel->facilities)/3);
                        $facilities = array_chunk($hotel->facilities, $count);
                    }
                    ?>
                    <?php if(!empty($facilities)): ?>
                        <?php foreach ($facilities as $column): ?>
                            <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12">
                                <ul class="style">
                                    <?php foreach ($column as $value): ?>
                                        <li><?php print $value ?></li>
                                    <?php endforeach; ?>
                                </ul>
                            </div>
                        <?php endforeach; ?>
                    <?php endif; ?>
                </div>
                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 price_block">
                    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 price_sort text-right">
                        <?php print t('from') ?>
                        <?php
                        $cheap_room = array_shift(array_values($hotel->packages));
                        $expensive_room = array_pop(array_values($hotel->packages));
                        ?>
                        <span>
                            <?php
                                $cheap_room_price = Currency::init()->convert($cheap_room['price'], 'RUB', Currency::init()->get_base_currency());
                                print Currency::init()->price_html($cheap_room_price);
                            ?>
                        </span>
                    </div>
                </div>
            </div>

            <div id="sort" class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
                <span><?php print t('Sorting') ?>: </span>
                <ul>
                    <li><a class="sort-link" data-order="desc" data-type="price"><?php print t('price') ?></a></li>
                </ul>
            </div>

            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 sort_content">
                <span class="price-range">
                    <span class="cheap"><?php

                        print round($cheap_room_price);?></span>
                    <span class="expensive"><?php
                        $expensive_room_price = Currency::init()->convert($expensive_room['price'], 'RUB', Currency::init()->get_base_currency());
                        print round($expensive_room_price); ?></span>
                    <span class="prefix"><?php /*print Currency::init()->get_currency() */?> </span>
                </span>
                <?php print render(drupal_get_form('search_hotels_details_result_filter', $hotel->filters));?>
            </div>

            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
                <div class="title_line">
                    <p class="title_services"><?php print t('Free rooms') ?></p>
                    <span class="line"></span>
                </div>
            </div>

            <div id="search-result-rooms">
                <?php foreach ($hotel->packages as $package): ?>

                    <?php
                    $package = (object)$package;
                    $package_data = array();
                    $package_data[] = 'data-price="' . ceil($package->price) . '"';
                    $availability = TRUE;
                    ?>

                    <div class="mix col-lg-12 col-md-12 col-sm-12 col-xs-12 reservation <?php print implode(' ',$package->classes);?>" <?php print implode(' ',$package_data);?>>
                        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
                            <?php foreach ($package->rooms as $room): ?>
                                <?php $room = (object)$room; ?>

                                <div class="col-lg-6 col-md-6 col-sm-6 col-xs-12 room-title"><?php print $room->class; ?> <?php print $room->type; ?></div>
                                <div class="col-lg-3 col-md-3 col-sm-3 col-xs-6 price_for_night">
                                  <?php
                                  $package_price = Currency::init()->convert($package->price, 'RUB', Currency::init()->get_base_currency());
                                  print Currency::init()->price_html($package_price) . ' ' . t('per 1 night'); ?>
                                </div>
                            <?php endforeach; ?>
                            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-6 reserv">
                                <?php if($availability && !empty($args)):?>
                                    <?php $args = (object)$args;?>
                                    <a class="price-booking-link default-bb"
                                       href="<?php print url(hrk_bh_make_results_page_link($args->location_id, $args->dates, $args->rooms, $args->nationality_id, $args->hotel_id, $package->id)); ?>">
                                        Забронировать
                                    </a>
                                <?php else:?>
                                    <a class="price-booking-link default-bb sell"><?php print t('Sell'); ?></a>
                                <?php endif;?>
                            </div>
                        </div>
                        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 adv">
                            <?php foreach ($package->rooms as $room): ?>
                                <div class="col-lg-4 col-md-4 col-sm-6 col-xs-12">
                                    <?php $room = (object)$room; ?>
                                    <ul class="style">
                                        <li><span><?php print t('Room basis:').' ';?></span><?php print $room->basis; ?></li>
                                        <li><span><?php print t('Room class:').' ';?></span><?php print $room->class; ?></li>
                                    </ul>
                                </div>
                                <div class="col-lg-4 col-md-4 col-sm-6 col-xs-12">
                                    <?php $room = (object)$room; ?>
                                    <ul class="style">
                                        <li><span><?php print t('Room type:').' ';?></span><?php print $room->type; ?></li>
                                        <li><span><?php print t('Refundability:').' ';?></span><?php $package->refund ? print $package->refund : print t('No'); ?></li>
                                    </ul>
                                </div>
                            <?php endforeach; ?>
                        </div>
                    </div>
                <?php endforeach; ?>
            </div>
        </div>
    </div>
<?php endif; ?>