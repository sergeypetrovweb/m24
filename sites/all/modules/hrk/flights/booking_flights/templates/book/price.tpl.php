<div class="price-wrapper">
    <div class="price-inner">
        <h2><?php print t('payment'); ?></h2>

        <div class="price-text">
            <span><?php print t('Attention!'); ?> </span>
            <?php print t('If you do not want to pay a financial fee, you can pay the tickets at our office.'); ?>
        </div>

        <div class="price-text">
            <?php print t('Commission for the financial transaction will be'); ?>
            <span><?php print $commission; ?> <?php print $currency; ?></span>.
        </div>
        <div class="price-text">
            <?php print t('Price:'); ?>
            <span>
                <span class="total-price">
                    <?php print $price + $commission; ?>
                </span>
                <?php print $currency; ?>
            </span>
            <?php print t('(including taxes and fees).'); ?>
        </div>
    </div>
</div>
