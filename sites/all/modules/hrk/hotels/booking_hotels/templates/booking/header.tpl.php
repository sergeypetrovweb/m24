<?php if(!empty($hotel)):?>
        <?php $hotel = (object)$hotel; ?>
        <div class="hotel-header">
            <div class="hotel-name"><?php print $hotel->name;?></div>
            <?php if (!empty($back_path)): ?>
                <a class="hotel-back" href="<?php print url($back_path); ?>"><?php print t('other rooms'); ?></a>
            <?php endif; ?>
        </div>
        <div class="hrk-clearfix"></div>
        <div class="hotel-common">
            <div class="hotel-address">
                <div><?php print $hotel->address; ?></div>
                <?php if (isset($time) || isset($left_time)): ?>
                    <div>
                        <?php if(!empty($time)):?>
                            <?php print t('Rooms must be paid to').' ';?>
                            <span>
                                <?php print $time;?>
                            </span>
                        <?php endif;?>
                        <?php if(!empty($left_time)):?>
                            <?php print t(', left to').' ';?>
                            <span>
                                <?php print $left_time;?>
                            </span>
                        <?php endif;?>
                    </div>
                <?php endif; ?>

                <?php if (!empty($addition_info)): ?>
                    <?php $addition_info = (object)$addition_info; ?>
                    <div>
                            <span>
                                <?php print $addition_info->nights . ' '; ?><?php print format_plural(($addition_info->nights % 2), t('night'), t('nights')); ?>
                            </span>
                        <?php $format_check_in = format_date($addition_info->check_in, 'medium', 'j F'); ?>
                        <?php $format_check_out = format_date($addition_info->check_out, 'medium', 'j F'); ?>
                        <?php print t('during the period from @check_in to @check_out', array('@check_in' => $format_check_in, '@check_out' => $format_check_out)); ?>
                    </div>
                <?php endif; ?>
            </div>
            <div class="hotel-rating">
                <div class="hotel-stars">
                    <?php for ($i = 1; $i <= $hotel->rating; $i++): ?>
                        <div class="star"></div>
                    <?php endfor; ?>
                </div>
                <div class="tripadvisor">
                    <?php if (!empty($hotel->trip_adv)): ?>
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
            </div>
        </div>
        <div class="hrk-clearfix"></div>
        <div class="horiz"></div>
<?php endif;?>