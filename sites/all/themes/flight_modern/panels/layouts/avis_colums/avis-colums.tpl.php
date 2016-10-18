<?php if (!empty($content['right'])) {
  $cols = ' twocol';
} else {
  $cols = '';
}
?>

<section id="panelpage" class="clearfix<?php print $cols; ?>">
  <div class="left-column">
    <?php print $content['left']; ?>
  </div>
  <div class="right-column">
    <?php print $content['right']; ?>
  </div>
</section>


