<?php
$row_count = null;

switch ($form['direction_type']['#value']) {
  case 'multi_stop':
    $row_count = SEARCH_FLIGHTS_MODULE_MAX_TRIPS_COUNT;
    break;
  case 'round_trip':
    $row_count = 1;
    break;
  case 'one_way':
    $row_count = 1;
    break;
}
?>


<div class="search-fly">
<!--   ex adv_seacrh_block-->
    <div class="search-fly-block <?php print 'type-'.$form['direction_type']['#value']; ?>">

  <?php if ($form['direction_type']['#value'] == 'round_trip'): ?>
  <?php endif; ?>


  <?php if ($form['direction_type']['#value'] == 'one_way'): ?>
  <?php endif; ?>



  <?php for ($i = 1; $i <= $row_count; $i++) : ?>
    <?php
    if (!empty($form['trip'][$i]['direction_from']['q']['#default_value'])) {
      $visible = ' visible-item';
    } else {
      $visible = '';
    }
    ?>


    <div id="edit-trip-<?php print $i; ?>" class="container_search <?php print $form['direction_type']['#value'].$visible; ?> clearfix">
      <div class="points_air direction-departure">
          <?php print render($form['trip'][$i]['direction_from']); ?>
          <input value="" class="reset choice_cities_filter" id="flight_from_reset" type="reset">
      </div>
      <i class="search-flights-form-trip-revert glyphicon glyphicon-sort"></i>
      <div class="points_air direction-return">
          <?php print render($form['trip'][$i]['direction_to']); ?>
          <input value="" class="reset choice_cities_filter" id="flight_from_reset" type="reset">
      </div>
      <div class="calendar_block">
        <div class="col-datepicker_date">
          <?php print render($form['trip'][$i]['datepicker_date']); ?>
          <?php print render($form['trip'][$i]['datepicker_date_value']); ?>

          <div class="real-inputs">
            <div class="form-type-pickadate-date col-departure">
              <?php print render($form['trip'][$i]['departure']); ?>
            </div>
            <div class="form-type-pickadate-date col-return">
              <?php print render($form['trip'][$i]['return']);?>
            </div>
          </div>
        </div>
      </div>

      <?php if ($row_count == 1): ?>

        <div class="people_count_block">
          <input type="text" placeholder="1 <?php print t('person'); ?>" class="people_count">
          <div class="people_count_overlay">
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 people adults">
              <div class="col-lg-7 col-md-7 col-sm-7 col-xs-12 text"><?php print t('Adults'); ?></div>
              <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 counts_people">
                <?php print render($form['passengers']['adt']); ?>
                <a href="#" data-for="adults" data-event="add"></a>
                <a href="#" data-for="adults" data-event="sub"></a>
              </div>
            </div>
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 people children">
              <div class="col-lg-7 col-md-7 col-sm-7 col-xs-12 text"><?php print t('Children (%age)', array('%age' => '<12')); ?></div>
              <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 counts_people">
                <?php print render($form['passengers']['chd']); ?>
                <a href="#" data-for="teens" data-event="add"></a>
                <a href="#" data-for="teens" data-event="sub"></a>
              </div>
            </div>
            <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 people children">
              <div class="col-lg-7 col-md-7 col-sm-7 col-xs-12 text"><?php print t('Infants (%age)', array('%age' => '<2')); ?></div>
              <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 counts_people">
                <?php print render($form['passengers']['inf']); ?>
                <a href="#" data-for="children" data-event="add"></a>
                <a href="#" data-for="children" data-event="sub"></a>
              </div>
            </div>
          </div>
        </div>

        <div class="bottom-white">
          <span>
            <label>
              <?php print t('Flight', array(), array('context' => 'search_form')); ?>:
            </label>
              <?php print render($form['direction_type']); ?>
          </span>
          <span>
            <label>
              <?php print t('Ticket option'); ?>:
            </label>
              <?php print render($form['cabin_type']); ?>
          </span>
        </div>

        <div class="search-btn">
          <?php print render($form['submit']); ?>
        </div>

      <?php endif; ?>

    </div>

  <?php endfor; ?>

  <?php if ($row_count > 1) : ?>
    <div class="bottom-white">
      <span>
        <label>
          <?php print t('Flight', array(), array('context' => 'search_form')); ?>:
        </label>
          <?php print render($form['direction_type']); ?>
      </span>
      <span>
        <label>
          <?php print t('Ticket option'); ?>:
        </label>
          <?php print render($form['cabin_type']); ?>
      </span>
          <div class="count_control"><span class="count_add">+ <?php print t('Add flight') ?></span></div>
    </div>

    <div class="bottom_options_block clearfix">
        <div class="people_count_block">
            <input type="text" placeholder="1 <?php print t('person'); ?>" class="people_count" readonly>
            <div class="people_count_overlay">
                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 people adults">
                    <div class="col-lg-7 col-md-7 col-sm-7 col-xs-12 text"><?php print t('Adults'); ?></div>
                    <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 counts_people">
                        <?php print render($form['passengers']['adt']); ?>
                        <a href="#" data-for="adults" data-event="add"></a>
                        <a href="#" data-for="adults" data-event="sub"></a>
                    </div>
                </div>
                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 people children">
                    <div class="col-lg-7 col-md-7 col-sm-7 col-xs-12 text"><?php print t('Children (%age)', array('%age' => '<12')); ?></div>
                    <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 counts_people">
                        <?php print render($form['passengers']['chd']); ?>
                        <a href="#" data-for="teens" data-event="add"></a>
                        <a href="#" data-for="teens" data-event="sub"></a>
                    </div>
                </div>
                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 people children">
                    <div class="col-lg-7 col-md-7 col-sm-7 col-xs-12 text"><?php print t('Infants (%age)', array('%age' => '<2')); ?></div>
                    <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 counts_people">
                        <?php print render($form['passengers']['inf']); ?>
                        <a href="#" data-for="children" data-event="add"></a>
                        <a href="#" data-for="children" data-event="sub"></a>
                    </div>
                </div>
            </div>
        </div>

        <div class="search-btn">
            <?php print render($form['submit']); ?>
        </div>
    </div>

  <?php endif; ?>

  <?php print drupal_render_children($form); ?>
</div>
</div>