<?php global $language;
$l_prefix = ($language->language == 'ru') ? $language->language : 'en';
?>
<?php if ($variants): ?>
    <div class="rs-wrapper">
        <?php foreach ($variants as $index => $variant): ?>
            <?php $variant = (object)$variant; ?>
            <div class="rs-<?php print $variant->type; ?> rs-unit-wrapper">
                <div class="rs-icon"></div>
                <div class="rs-body">
                    <?php if ($variant->type == 'flight'): ?>
                        <?php print theme('rs_flight_unit', array('flight' => $variant)); ?>
                    <?php else:?>
                         <?php print theme('rs_hotel_unit', array('hotel' => $variant));?>
                    <?php endif; ?>
                </div>
                <div class="rs-cross-icon" data-index="<?php print $index; ?>">+</div>
            </div>
        <?php endforeach; ?>
    </div>
<?php endif; ?>