<?php if(!empty($package) && !empty($addition_info)):?>
        <?php $package = (object)$package;?>
        <?php $addition_info = (object)$addition_info;?>
        <h2><?php print t('payment');?></h2>
        <div class="booking-table">
            <div class="tariff"></div>
            <div class="average"><?php print t('Average price per night');?></div>
            <div class="night"><?php print t('Nights');?></div>
            <div class="period"><?php print t('For the period');?></div>
        </div>
        <div class="horiz"></div>
        <div class="booking-table">
            <div class="tariff"><?php print t('Rate');?></div>
            <div class="average">
                <?php print Currency::init()->price_html($package->package_price['final_price']/$addition_info->nights);?>
            </div>
            <div class="night">
                <?php print $addition_info->nights;?>
            </div>
            <div class="period">
                <?php print Currency::init()->price_html($package->package_price['final_price']);?>
            </div>
        </div>
        <div class="booking-table">
            <div class="tariff"><?php print t('Total');?></div>
            <div class="average"></div>
            <div class="night"></div>
            <div class="period">
              <?php
              $price_base = Currency::init()->convert($package->package_price['final_price'], 'RUB', Currency::init()->get_base_currency());
              print Currency::init()->price_html($price_base);?>
            </div>
        </div>
<?php endif;?>