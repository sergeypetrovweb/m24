<?php if (!empty($settings['offers'][0])): ?>
<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 variety_offers">
  <div class="container">
    <h1 class="main_header"><?php print t($settings['title_offers']) ?></h1>
    <?php for ($i = 0; $i < 4; $i++) : ?>
    <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 variety_offer"><div class="content"><span class="big"><?php print t($settings['offers'][$i]['numb']) ?></span><span class="small"><?php print t($settings['offers'][$i]['desc']) ?></span></div></div>
    <?php endfor; ?>
  </div>
</div>
<?php endif; ?>