<?php $path = 'sites/all/themes/flight_modern'; ?>

<div class="off-canvas">

    <div id="wraper">
        <?php print $content['top']; ?>

        <div id="content">
            <div class="container">
                <?php print $content['content']; ?>
            </div>
        </div>

        <div class="footer_info_two variant_two">
            <div class="container no-padding">
                <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 no-padding ">
                    <?php print $content['footer_pre_1']; ?>
                </div>
                <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 no-padding ">
                    <?php print $content['footer_pre_2']; ?>
                </div>
                <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 no-padding ">
                    <?php print $content['footer_pre_3']; ?>
                </div>
                <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 no-padding center social_footer_two">
                    <?php print $content['footer_pre_4']; ?>
                    <div class="border_footer_title"><?php print t('Follow Us') . ':'; ?></div>
                    <a href="https://www.facebook.com/mambo24" class="link_social"><img src="/<?php print $path; ?>/images/fb_icon.png" alt="Facebook"></a>
                    <a href="https://vk.com/mambo24" class="link_social"><img src="/<?php print $path; ?>/images/vk_icon.png" alt="VK"></a>
                    <a href="https://twitter.com/mambo24ru" class="link_social"><img src="/<?php print $path; ?>/images/twitter_icon.png" alt="Twiiter"></a>
                    <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 cards_icons">
                        <img src="/<?php print $path; ?>/images/mastercard_icon.png" alt="MasterCard">
                        <img src="/<?php print $path; ?>/images/visa_icon.png" alt="Visa">
                        <a href="http://uniteller.ru"><img class="uniteller_logo" src="/<?php print $path; ?>/images/uniteller.png" alt="Uniteller"><a>
                    </div>
                </div>

            </div>
        </div>
        <?php print $content['footer']; ?>
    </div>
</div>
<img class="inv_preload" width="0px" height="0px" src="/sites/all/themes/flight_modern/images/sky_back.jpg">