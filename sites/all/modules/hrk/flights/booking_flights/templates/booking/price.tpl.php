<div class="price-wrapper">
    <div class="price-inner">
        <h2 class="section_title"><?php print t('Payment'); ?></h2>
        <div class="price-text">
            <?php print t('Tickets must be paid to ') . ' ' . $time . ',' . t('left ') . ' <span>' . $left_time . '</span>'; ?>
        </div>
<!--        <div class="price-text">
            <?php /*print t('Commission for the financial transaction will be'); */?>
            <span><?php /*print Currency::init()->price_html($commission); */?></span>.
        </div>-->
        <div class="price-text">
            <?php print t('Price:'); ?>
            <span>
                <span class="total-price">
                    <?php print Currency::init()->price_html(round($price + $commission)); ?>
                </span>
                <span class="after-price"><?php print t('(including taxes and fees)'); ?></span>
                <span class="after-price-bonus">( <?php print Currency::init()->price_html(round($price + $commission)); ?> )</span>
            </span>

        </div>
    </div>
</div>