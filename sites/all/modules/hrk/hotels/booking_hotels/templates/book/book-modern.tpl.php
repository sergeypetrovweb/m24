<?php
$path = drupal_get_path('theme', 'flight_modern');

foreach ($hotel->package['rooms'] as $room) {
    $room = (object)$room;
}

$class = '';

switch($type){
    case 'book':
        $status_title = t('Your rooms successfully booked!');
        $class = ' booking-message-wrapper-yellow';
        break;
    case 'paid':
        $status_title = t('Your rooms have successfully purchased!');
        $class = ' booking-message-wrapper-green';
        break;
    case 'cancel':
        $status_title = t('Your booking is canceled!');
        $class = ' booking-message-wrapper-red';
        break;
}

$currency = Currency::init()->get_base_currency();

$price_base = Currency::init()->convert($hotel->price['original_price'], 'RUB', Currency::init()->get_base_currency());

$price = Currency::init()->price_html($price_base);
if (empty($bonus)) {
  $bonus = 0;
}
?>

<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 information_block<?php print $class; ?>">
    <div class="col-lg-10 col-md-10 col-sm-10 col-xs-10">
        <p><?php print $status_title ?></p>

        <p><?php print t('Reservation number:') ?> <strong><?php print $book->orid . '.' . $book->seid ?></strong></p>

    </div>
    <div class="col-lg-2 col-md-2 col-sm-2 col-xs-2">
        <?php if ($type == 'book'): ?>
            <?php print $buy;?>
        <?php endif; ?>
    </div>
</div>

<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 buy_hotel_block">
    <div class="col-lg-4 col-md-4 col-sm-12 col-xs-12 thumb_hotel_buy">
        <?php if (!empty($hotel->images)) : ?>
            <?php
            print theme('imagecache_external', array(
                'path' => $hotel->images[0]['src'],
                'style_name'=> '360x330',
            ));
            ?>
        <?php endif; ?>

    </div>
    <div class="col-lg-8 col-md-8 col-sm-12 col-xs-12 content_hotel_buy">
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 block_name">
            <div class="col-lg-8 col-md-8 col-sm-8 col-xs-12">
                <span class="buy_name"><?php print $hotel->name; ?></span>
                <span class="raiting_block">
                    <?php for ($i = 1; $i <= 5; $i++): ?>
                        <?php if ($i <= $hotel->rating): ?>
                            <img src="/<?php print $path; ?>/images/big_star_active.png">
                        <?php else: ?>
                            <img src="/<?php print $path; ?>/images/big_star.png">
                        <?php endif; ?>
                    <?php endfor; ?>
                </span>
            </div>
            <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12 value_users">
                <?php if (!empty($hotel->trip_adv) &&!empty($hotel->trip_adv['rating'])): ?>
                    <?php print t('Visitors rating') ?> <span class="value"><?php print $hotel->trip_adv['rating']; ?></span>
                <?php endif; ?>
            </div>
        </div>
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 map_block">
            <img src="/<?php print $path; ?>/images/map_orange.png"> <?php print $hotel->address; ?>
        </div>
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 room_info"><a><?php print $room->class; ?> <?php print $room->type; ?></a></div>
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 buy_hotel_table">
            <table>
                <tr class="head_links">
                    <td><a class="show_policy red_a"><?php print t('cancellation policy'); ?></a></td>
                    <td></td>
                    <td></td>
                    <td></td>
                </tr>
                <tr class="book-policy-popup" style="display:none">
                    <td colspan="4">
                        <?php print bh_popup('hotel_policy', array('polices' => $hotel->cancellation_policy, 'title' => t('Penalties'), 'close' => TRUE)); ?>
                    </td>
                </tr>
                <tr class="header">
                    <td class="guest_name"><?php print t('Guests');?></td>
                    <td><?php print t('Reservation time');?></td>
                    <td><?php print t('Reservation number');?></td>
                    <td><?php print t('Order number');?></td>
                </tr>
                <?php foreach ($room->guests as $guest_age): ?>
                    <?php foreach ($guest_age as $people): ?>
                        <tr>
                            <td class="guest_name"><?php print $people['last_name'] . ' ' . $people['first_name'] ?></td>
                            <td><?php print
                                    format_date($hotel->_sh_params['check_in'], 'custom', 'd.m') . ' - ' .
                                    format_date($hotel->_sh_params['check_out'], 'custom', 'd.m') .
                                    ' ('. $hotel->_sh_params['nights'] . ' ' . t('nights') . ')'
                                ?></td>
                            <td><?php print $book->orid . '.' . $book->seid ?></td>
                            <td><?php print $book->bid ?></td>
                        </tr>
                    <?php endforeach; ?>
                <?php endforeach; ?>
                <tr class="price_summary">
                    <td colspan="4">
                        <?php




                        print t('Total price') ?>: <?php print Currency::init()->price_html($price_base-$bonus); ?>
                        <?php if ($bonus != 0): ?>
                        <span class="after-price-bonus">( <?php print $price; ?> )</span>
                        <?php endif; ?>
                    </td>
                </tr>
            </table>
        </div>
    </div>
</div>
