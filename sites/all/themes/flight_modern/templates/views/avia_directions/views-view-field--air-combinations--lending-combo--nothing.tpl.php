<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */

$field_name = 'name_'.$GLOBALS['language']->language;
$data = db_select('hrk_sf_cities', 'c')
  ->fields('c', array('code', $field_name))
  ->condition('c.code', array($row->air_combinations_city_arrival, $row->air_combinations_city_departure), 'IN')
  ->execute()
  ->fetchAllKeyed(0, 1);

$departure = $data[$row->air_combinations_city_departure];
$arrival = $data[$row->air_combinations_city_arrival];
?>
<a href="/<?php print $GLOBALS['language']->language ?>/flights/results/c_<?php print $row->air_combinations_city_departure; ?>-c_<?php print $row->air_combinations_city_arrival; ?>/<?php print date('ymd', strtotime('+1 day')) ?>/100/E/0"><?php print $departure . ' - ' . $arrival ?></a>