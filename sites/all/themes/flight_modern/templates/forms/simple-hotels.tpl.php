<?php //if(!$form['#mini']): ?>
<div id="advanced_search">
  <div class="container">
  <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 title_adv_seacrh">
    <h1><?php print t('The best hotel deals here and now') ?></h1>
  </div>
<?php //endif; ?>
    <div class="col-lg-10 col-md-10 col-sm-10 hidden-xs adv_seacrh_block">
      <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">
        <div class="side-by-side clearfix">
          <?php print render($form['city']) . render($form['location_id']); ?>
        </div>
        <input value="" class="reset choice_cities_filter" id="flight_from_reset" type="reset">
      </div>
      <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12 calendar_block">
          <div class="col-datepicker_date">
              <?php print render($form['datepicker_date']); ?>
              <?php print render($form['datepicker_date_value']); ?>

              <div class="real-inputs">
                  <?php print render($form['check_in']); ?>
                  <?php print render($form['check_out']); ?>
              </div>
          </div>
      </div>
      <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 nationality_block">
        <?php print render($form['nationality']); ?>
      </div>
      <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12 people_count_block">
        <input type="text" placeholder="0 <?php print t('person') ?>" class="people_count">
        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 people_count_overlay">
          <?php print render($form['add_room']); ?>

          <?php print render($form['rooms']); ?>
        </div>
      </div>
      <div class="col-lg-2 col-md-2 col-sm-2 col-xs-12">
        <?php print render($form['actions']['submit']); ?>
      </div>
    </div>

<!--    <div class="hidden-lg hidden-md hidden-sm col-xs-12 adv_seacrh_block">-->
<!---->
<!--      <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 bg_seacch_block">-->
<!---->
<!-- Nav tabs -->
<!--        <ul class="nav nav-tabs" role="tablist">-->
<!--          <li role="presentation" class="active"><a href="#hotels_tab" aria-controls="hotels_tab" role="tab" data-toggle="tab">--><?php //print t('Hotels') ?><!--</a></li>-->
<!--          <li role="presentation"><a href="#tickets_tab" aria-controls="tickets_tab" role="tab" data-toggle="tab">--><?php //print t('Flights') ?><!--</a></li>-->
<!--        </ul>-->
<!-- Tab panes -->
<!--        <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 tab-content">-->
<!--          <div role="tabpanel" class="col-lg-12 col-md-12 col-sm-12 col-xs-12 tab-pane active" id="hotels_tab">-->
<!--            <div class="col-lg-3 col-md-3 col-sm-3 col-xs-12">-->
<!--              <div class="side-by-side clearfix">-->
<!--                <select data-placeholder="--><?php //print t('Choose city or hotel') ?><!--" style="width:100%;" class="select-city-and-hotel" tabindex="12" id="cities_filter">-->
<!--                  <option value=""></option>-->
<!--                  <option>--><?php //print t('Frejus') ?><!--, <span>--><?php //print t('France') ?><!--</span></option>-->
<!--                  <option>--><?php //print t('Fresno') ?><!--, <span>--><?php //print t('USA') ?><!--</span></option>-->
<!--                  <option>--><?php //print t('Freiburg') ?><!--, <span>--><?php //print t('Germany') ?><!--</span></option>-->
<!--                  <option>--><?php //print t('Frejus') ?><!--, <span>--><?php //print t('France') ?><!--</span></option>-->
<!--                  <option>--><?php //print t('Freiburg') ?><!--, <span>--><?php //print t('Germany') ?><!--</span></option>-->
<!--                </select>-->
<!--              </div>-->
<!--              <input value="" class="reset choice_cities_filter" id="flight_from_reset" type="reset">-->
<!--            </div>-->
<!--            <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 calendar_block">-->
<!--              <input type="text" placeholder="--><?php //print t('Arrival') ?><!--" class="calendar from" id="datepicker_from">-->
<!--              <input type="text" placeholder="--><?php //print t('Departure') ?><!--" class="calendar to" id="datepicker_to">-->
<!--            </div>-->
<!--            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-6 people_count_block">-->
<!--              <input type="text" placeholder="0 --><?php //print t('person') ?><!--" class="people_count">-->
<!--              <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 people_count_overlay">-->
<!--                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 people adults">-->
<!--                  <div class="col-lg-7 col-md-7 col-sm-7 col-xs-12 text">--><?php //print t('Adults') ?><!--</div>-->
<!--                  <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 counts_people">-->
<!--                    <input id='adults' type='number' value='1'>-->
<!--                    <a href="#" data-for='adults' data-event='add'></a>-->
<!--                    <a href="#" data-for='adults' data-event='sub'></a>-->
<!--                  </div>-->
<!--                </div>-->
<!--                <div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 people children">-->
<!--                  <div class="col-lg-7 col-md-7 col-sm-7 col-xs-12 text">--><?php //print t('Childrens') ?><!--</div>-->
<!--                  <div class="col-lg-5 col-md-5 col-sm-5 col-xs-12 counts_people">-->
<!--                    <input id='children' type='number' value='1'>-->
<!--                    <a href="#" data-for='children' data-event='add'></a>-->
<!--                    <a href="#" data-for='children' data-event='sub'></a>-->
<!--                  </div>-->
<!--                </div>-->
<!--              </div>-->
<!--            </div>-->
<!--            <div class="col-lg-2 col-md-2 col-sm-2 col-xs-6">-->
<!--              --><?php //print render($form['actions']['submit']); ?>
<!--            </div>-->
<!--          </div>-->
<!--          <div role="tabpanel" class="col-lg-12 col-md-12 col-sm-12 col-xs-12 tab-pane" id="tickets_tab">...</div>-->
<!--        </div>-->
<!--      </div>-->
<!--    </div>-->
<?php //if(!$form['#mini']): ?>
   </div>
  </div>
<?php //endif; ?>

<?php print drupal_render_children($form); ?>