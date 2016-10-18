<?php if (!empty($hotel)): ?>
    <?php
    switch($type){
        case 'book':
            $title = t('Your rooms successfully booked!');
            $class = 'booking-message-wrapper-yellow';
            break;
        case 'paid':
            $title = t('Your rooms have successfully purchased!');
            $class = 'booking-message-wrapper-green';
            break;
        case 'cancel':
            $title = t('Your booking is canceled!');
            $class = 'booking-message-wrapper-red';
            break;
    }
    ?>
    <?php $hotel = (object)$hotel; ?>

    <div class="hotel-header">
        <div class="hotel-name"><?php print $hotel->name; ?></div>
        <a href="#" class="show_policy"><?php print t('cancellation policy'); ?></a>
        <div class="book-policy-popup" style="display:none">
            <?php print bh_popup('hotel_policy', array('polices' => $hotel->cancellation_policy, 'title' => t('Penalties'), 'close' => TRUE)); ?>
        </div>
    </div>
    <div class="hrk-clearfix"></div>
<div class="hotel-common <?php print $class;?>">
    <div class="hotel-address">
    <div><?php print $title; ?></div>
    <?php if($type == 'book'):?>
        <?php if (!empty($addition_info)): ?>
            <?php $addition_info = (object)$addition_info; ?>
            <div>
                <span></span>
            </div>
            </div>
            </div>
        <?php endif; ?>
    <?php endif; ?>
<?php endif; ?>