<?php if(!empty($package) && !empty($addition_info)):?>
    <?php $package = (object)$package;?>
    <?php $addition_info = (object)$addition_info;?>
    <?php
    $ppl_cnt = 0;
    foreach ($addition_info->rooms[0] as $value) {
        $ppl_cnt += $value;
    }
  $currency = Currency::init()->get_base_currency();
  $package_price_p = Currency::init()->convert($package->package_price['final_price'], 'RUB', Currency::init()->get_base_currency());
  $price = Currency::init()->price_html($package_price_p);
    ?>

    <div class="payment_table">
        <h3><?php print t('Payment');?></h3>
        <table class="desktop">
            <tr>
                <td class="first"><?php print t('Average price per night');?></td>
                <td><?php print t('Nights');?></td>
                <td><?php print t('Peoples');?></td>
                <td><?php print t('Total price');?></td>
            </tr>
            <tr>
                <td class="first"><?php
                  $package_price = Currency::init()->convert($package->package_price['final_price']/$addition_info->nights, 'RUB', Currency::init()->get_base_currency());
                  print Currency::init()->price_html($package_price); ?></td>
                <td><?php print $addition_info->nights;?></td>
                <td><?php print $ppl_cnt;?></td>
              <td class="price-wrapper">
                <span class="total-price">
                  <?php print $price; ?>
                </span>
                <span class="after-price-bonus">( <?php print $price; ?> )</span>
              </td>
<!--                <td>--><?php //print ceil($package->package_price['final_price']).' '.currency_get_prefix($package->package_price['currency']);?><!--</td>-->
            </tr>
        </table>
        <table class="mobile">
            <tr>
                <td><?php print t('Average price per night');?></td>
                <td><?php
                  $package_price_av = Currency::init()->convert($package->package_price['final_price']/$addition_info->nights, 'RUB', Currency::init()->get_base_currency());
                  print Currency::init()->price_html($package_price_av);?></td>
            </tr>
            <tr>
                <td><?php print t('Nights');?></td>
                <td><?php print $addition_info->nights;?></td>
            </tr>
            <tr>
                <td><?php print t('Peoples');?></td>
                <td><?php print $ppl_cnt;?></td>
            </tr>
            <tr>
                <td><?php print t('Total price');?></td>
              <td>
                <span class="total-price">
                  <?php print $price; ?>
                </span>
                <span class="after-price-bonus">( <?php print $price; ?> )</span>
              </td>
<!--                <td>--><?php //print ceil($package->package_price['final_price']).' '.currency_get_prefix($package->package_price['currency']);?><!--</td>-->
            </tr>
        </table>
    </div>
<?php endif;?>