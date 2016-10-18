<?php
    switch($type){
        case 'book':
            $title = t('Your tickets successfully booked!');
            $class = ' booking-message-wrapper-yellow';
            break;
        case 'ticket':
            $title = t('Your tickets have successfully purchased!');
            $class = ' booking-message-wrapper-green';
            break;
        case 'cancel':
            $title = t('Your booking is canceled!');
            $class = ' booking-message-wrapper-red';
            break;
    }
?>


<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 information_block<?php print $class;?>">
    <div class="col-lg-10 col-md-10 col-sm-10 col-xs-10">
        <p><?php print $title; ?><br>
            <?php if(isset($time)):?>
                <?php print t('Tickets must be paid to').' '. $time;?>
            <?php endif;?>
            <?php if(isset($left_time)):?>
                <?php if(isset($left_seconds) && $left_seconds < 1201):?>
                    <?php print t(', left to').':  <span id="clock" data-left="' . $left_seconds . '"></span>';?>
                <?php else: ?>
                    <?php print t(', left to').' '.$left_time;?>
                <?php endif;?>
            <?php endif;?>
        </p>
        <?php if($type == 'book' && isset($context_id)):?>

            <p><?php print t('Reservation number:');?> <strong><?php print $context_id;?></strong></p>
        <?php endif;?>

        <?php if($type == 'ticket' && isset($context_id)):?>
            <p><?php print t('Tickets number:');?> <strong><?php print $context_id;?></strong></p>
        <?php endif;?>
    </div>
    <?php if (isset($time) || isset($left_time)): ?>
        <div class="col-lg-2 col-md-2 col-sm-2 col-xs-2">
        <?php if($buy) print $buy; ?>
        </div>
    <?php endif; ?>
</div>