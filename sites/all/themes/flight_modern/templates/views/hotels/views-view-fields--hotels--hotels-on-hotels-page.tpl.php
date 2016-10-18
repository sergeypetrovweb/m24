<?php

/**
 * @file
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>

<div class="col-lg-4 col-md-4 col-sm-4 col-xs-12 better_hotel_product">
  <a href="<?php print $fields['field_hotel_link']->content ?>" class="col-lg-12 col-md-12 col-sm-12 col-xs-12 content_hotel_product">
    <?php print $fields['field_hotel_preview']->content ?>
    <div class="overlay_hotel_product">
      <div class="col-lg-9 col-md-9 col-sm-9 col-xs-9">
                                        <span class="name"><?php print $fields['title']->content ?></span>
        <span class="category">KURDEMIR Turu</span>
      </div>
      <div class="col-lg-3 col-md-3 col-sm-3 col-xs-3 raiting">
        <?php print $fields['field_hotel_stars']->content ?>
        <span class="price">
          <?php print Currency::init()->price_html($fields['field_hotel_price']->content); ?>
        </span>
      </div>
    </div>
  </a>
</div>