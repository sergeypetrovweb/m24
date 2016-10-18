<?php
global $language;
$l_prefix = ($language->language == 'en') ? 'en' : 'ru';
$path = drupal_get_path('theme', 'flight_modern');

//$inline_form = drupal_get_form('search_flights_search_inline_form');
$inline_form = drupal_get_form('simple_air_search','inline');
$inline_form = render($inline_form);
?>
<?php if (!empty($trips)): ?>

<div id="breadcrumbs">
  <div class="container">
    <img class="breadcrumbs-icon" src="/<?php print $path ?>/images/breadcrumbs_home.png">
    <div class="breadcrumbs-flights">

        <?php foreach ($trips as $trip): ?>
            <?php $trip = (object)$trip;?>
            <?php $airport_name = !empty($trip->info['name_'.$l_prefix])?$trip->info['name_'.$l_prefix]:'';?>
            <?php $city_name = !empty($trip->info['city']['name_'.$l_prefix])?$trip->info['city']['name_'.$l_prefix]:'';?>
            <?php $country_name = !empty($trip->info['country']['name_'.$l_prefix])?$trip->info['country']['name_'.$l_prefix]:'';?>
            <?php $popup_content = !empty($city_name)?$city_name.', '.$country_name:$country_name;?>
            <a title="<?php print $popup_content;?>" class="tooltiper open_search"><?php print $airport_name;?></a>
            <?php if (!empty($trip->transit)): ?>
                <span class="parameters-transit"><span><?php print date('d.m.y', $trip->transit) ?></span> — </span>
            <?php endif; ?>
        <?php endforeach; ?>
    </div>
    <?php print $inline_form ?>
  </div>
</div>

<?php endif; ?>