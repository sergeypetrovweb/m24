<?php
global $language;
$name = 'name_' . $language->language;


?>

<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 popular-hotel popular-cities">
  <div class="container">
    <div class="view view-hotels view-id-hotels view-display-id-pop_city_on_hotels_page view-dom-id-f4f68df6c7325ca135e151342896e53f">
      <div class="view-header">
        <h1 class="main_header"><?php print t('Most popular cities') ?></h1>
      </div>
      <div class="view-content">
        <div class="row">
          <?php foreach($data['flight'] as $flight): ?>
              <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 product">
                <a href="/<?php print $language->language ?>/hotels/results/<?php print $flight['lid'] ?>/<?php print $data['date_start'] ?>-<?php print $data['date_end'] ?>/100/161"  class="col-lg-12 col-md-12 col-sm-12 col-xs-12 content_hotel_product">
                  <div class="content_product">
                    <div class="miniature">
                      <?php print $flight['img'] ?>
                      <i class="date"><?php print date('d.m', $data['date']) ?></i>
                    </div>
                    <div class="description">
                      <p><?php print $data['cyties'][ $flight['lid'] ]->$name; ?></p>
                    </div>
                  </div>
                </a>

            </div>
          <?php endforeach; ?>
        </div>
      </div>
    </div>
  </div>
</div>