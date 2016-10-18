<?php if(!empty($room)):?>
    <?php $room = (object)$room;?>

    <div class="hotel-info">
        <div class="hotel-image">
            <?php if(!empty($room->image['src'])):?>
                <?php $html_img = theme('imagecache_external', array('path' => $room->image['src'], 'style_name' => 'bh_room_image')); ?>
                <?php if ($html_img): ?>
                    <?php print $html_img; ?>
                <?php endif;?>
            <?php endif;?>
        </div>
        <div class="single-hotel">
            <h3><?php print $room->class; ?> <?php print $room->type; ?></h3>
            <div class="short-descr">
                <div><span class="highlight"><?php print $room->basis; ?></span></div>
                <div><span class="highlight"><?php print $room->class; ?></span></div>
                <div><span class="highlight"><?php print $room->type; ?></span></div>
            </div>
            <div class="hotel-cancel">
                <?php if(hrk_bh_is_expire($room->free_cancellation)):?>
                        <div class="highlight-warning"><?php print t('No free cancellation');?></div>
                    <?php else:?>
                        <?php print t('Free cancellation up to @date', array('@date'=>format_date($room->free_cancellation,'medium','j F')));?>
                <?php endif;?>
                <?php if($room->cancellation_remarks):?>
                    <?php foreach ($room->cancellation_remarks as $remark):?>
                        <div><?php print $remark;?></div>
                    <?php endforeach;?>
                <?php endif;?>
            </div>
        </div>
        <div class="hrk-clearfix"></div>
        <?php if($room->description):?>
            <div class="single-hotel-description">
                <div class="hotel-article">
                    <h2><?php print t('room description');?></h2>
                    <div>
                        <?php foreach ($room->description as $description):?>
                            <p><?php print $description; ?></p>
                        <?php endforeach;?>
                    </div>
                </div>
            </div>
        <?php endif;?>
    </div>
<?php endif;?>
