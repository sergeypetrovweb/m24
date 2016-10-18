<?php
global $language;
$name = 'name_' . $language->language;

?>
<div id="special_offers">
    <h1 class="views-title"><?php print t('Special Offers') ?></h1>
  <div class="products">
    <div class="row">
      <?php foreach($data['flight'] as $flight) : ?>
        <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 product">
          <a href="/<?php print $language->language ?>/flights/results/c_<?php print $flight['from'] ?>-c_<?php print $flight['to'] ?>/<?php print date('ymd', $data['date']) ?>/100/E/0">
            <div class="content_product">
              <div class="miniature">
                <?php if (!empty($flight['price'])) : ?>
                  <span class="time">
                    <?php print Currency::init()->price_html($flight['price']) ?>
                  </span>
                <?php endif; ?>
                <?php print $flight['img'] ?>
                <i class="date"><?php print date('d.m', $data['date']) ?></i>
              </div>
              <div class="description">
                <p><?php print $data['cyties'][ $flight['from'] ]->$name; ?></p>
                <i class="planegreen"></i>
                <p><?php print $data['cyties'][ $flight['to'] ]->$name; ?></p>
              </div>
            </div>
          </a>
        </div>
      <?php endforeach; ?>
    </div>
  </div>
</div>



