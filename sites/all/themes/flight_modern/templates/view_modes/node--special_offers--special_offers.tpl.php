<?php

$from_code = field_get_items('node', $node, 'field_special_offer_from');
$from_code = $from_code[0]['value'];
$to_code = field_get_items('node', $node, 'field_special_offer_to');
$to_code = $to_code[0]['value'];

$cities = db_select('hrk_sf_cities', 'c')
  ->fields('c',array('code','name_en','name_ru'))
  ->condition('c.code', array($from_code, $to_code), 'IN')
  ->execute()
  ->fetchAllAssoc('code');

$name = 'name_'.$node->language;
$price = field_get_items('node', $node, 'field_special_offer_price_modern');
$price = $price[0]['value'];

$cat = field_get_items('node', $node, 'field_special_offer_category');
$cat = taxonomy_term_load($cat[0]['tid']);

$img = field_get_items('node', $node, 'field_special_offer_image');
$img = $img[0]['uri'];

$img = theme(
    'image_style',
    array(
        'path' => $img,
        'style_name' => 'flight_modern__special_offers',
    )
);

$rating = field_view_field('node', $node, 'field_special_offer_rating');
$stars = round($rating['#items'][0]['average'] / 20);
//$rating = drupal_render($rating);
?>

<a href="/flights/results/c_<?php print $from_code ?>-c_<?php print $to_code ?>/150903/100/E/0">
<div class="content_product">
    <div class="miniature">
        <?php if (!empty($price)) : ?>
            <span class="time">
              <?php print Currency::init()->price_html($price) ?></span>
        <?php endif; ?>
        <?php print $img ?>
<!--        <i class="icon plane green"></i>-->
        <i class="date">04.05</i>
    </div>
    <div class="description">
      <p><?php print $cities[$from_code]->$name ?></p>
      <i class="planegreen"></i>
      <p><?php print $cities[$to_code]->$name ?></p>
<!--        <span class="name">--><?php ///*print l($node->title, getPathAlias($node->nid)) */?><!--</span>-->
<!--        <span class="category">--><?php ///*print $cat->name */?><!--</span>-->
<!--        <div class="raiting">
            <?php /*for ($i=1; $i<=5; $i++): */?>
                <span class="star <?php /*$i <= $stars ? print 'active' : null */?>"></span>
            <?php /*endfor; */?>

            (<?php /*print $rating['#items'][0]['count'] */?>)
        </div>-->
    </div>
</div>
</a>