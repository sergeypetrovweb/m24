<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 sort_content">
  <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12">
    <label><?php print t('Price') ?></label>
    <div class="default_range" style="position: relative;">
      <span class="bg_irs"></span>
      <div class="price">
        <input type="text" id="price_sort" value="" name="range" />
        <span class="price-currency"><?php print currency_get_prefix() ?></span>
      </div>
    </div>
  </div>
  <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12">
    <?php print render($form['basis']); ?>
  </div>
  <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12">
    <?php print render($form['class']); ?>
  </div>
  <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12">
    <?php print render($form['type']); ?>
  </div>
  <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12">
    <a class="show-map-link"><?php print t('show on map') ?></a>
    <a class="hide-map-link hidden"><?php print t('hide map') ?></a>
  </div>
</div>