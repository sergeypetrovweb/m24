<?php
/**
 * Шаблон вывода блока с погодой.
 */
$data = avis_weather_get($variables['code']);
$lang = $GLOBALS['language']->language;
$date = NULL;
$output = NULL;
$temp = NULL;
$picture = NULL;
$weather = $data['weather'];
$from = strtotime($weather[0]->date);
foreach ($weather as $key => $day) {
  $timestamp = strtotime($day->date);
  $date = format_date($timestamp, 'custom', 'D, d.m');
  $high = round(5 / 9 * ($day->high - 32));
  $low = round(5 / 9 * ($day->low - 32));
  $picture = '<img src="http://l.yimg.com/a/i/us/we/52/' . $day->code . '.gif">';
  $temp = ($high > 0 ? '+' . $high : $high) . '/' . ($low > 0 ? '+' . $low : $low);

  $output .= '
        <li>
           <div class="weather-date">' . $date . '</div>
           <div class="weather-pic">' . $picture . '</div>
           <div class="weather-temp">' . $temp . '</div>
        </li>
        ';
}

drupal_add_css(drupal_get_path('module', 'avis_weather') . '/avis_weather.css');
?>

<section id="weather-city">
  <h3><?php print t("Weather") . ' ' . $data['city'][$lang] . ' ' . t('from') . ' ' . format_date($from, 'custom', 'd F Y'); ?></h3>
  <ul class="weather-data">
    <?php print $output; ?>
  </ul>
</section>