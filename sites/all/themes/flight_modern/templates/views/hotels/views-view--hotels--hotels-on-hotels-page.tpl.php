<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
?>
<div id="content" class="pb-30">
  <div class="container">

    <?php $settings = variable_get('avis_hotels'); if (!empty($settings['help'][0])): ?>
<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 better-hotel">
  <h1 class="main_header"><?php print t($settings['title_help']) ?></h1>
  <?php for ($i = 0; $i < 3; $i++) : ?>
  <div class="col-lg-4 col-md-4 col-sm-4 col-xs-12 better_hotel_adv">
    <?php
    $img = file_load($settings['help'][$i]['img']);
    print theme('image', array('path' => $img->uri));
    ?>
    <h1><?php print t($settings['help'][$i]['title']) ?></h1>
    <p><?php print t($settings['help'][$i]['desc']) ?></p>
  </div>
  <?php endfor; ?>
</div>
    <?php endif; ?>

<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12 popular-hotel">
<div class="<?php print $classes; ?>">
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($header): ?>
    <div class="view-header">
      <h1 class="main_header">
      <?php print t($header); ?>
      </h1>
    </div>
  <?php endif; ?>

  <?php if ($exposed): ?>
    <div class="view-filters">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="view-content">
      <div class="row">
      <?php print $rows; ?>
      </div>
    </div>
  <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <?php print $pager; ?>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div><?php /* class view */ ?>
</div>
</div>
</div>