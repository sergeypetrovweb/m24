<?php if(!empty($room)):?>
    <?php $room = (object)$room;?>

    <div class="hotel-info">
        <div class="info-wrapper clearfix">
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 single-hotel">
                <h3><?php print $room->class; ?> <?php print $room->type; ?></h3>
                <ul class="short-descr style">
                    <li><span class="highlight"><?php print $room->basis; ?></span></li>
                    <li><span class="highlight"><?php print $room->class; ?></span></li>
                    <li><span class="highlight"><?php print $room->type; ?></span></li>
                </ul>
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
