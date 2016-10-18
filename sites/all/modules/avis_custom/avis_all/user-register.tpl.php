<div class="login_form">
  <h2><?php print t('Registration'); ?></h2>
  <?php print theme_status_messages(array('display' => 'error')); ?>
  <?php print drupal_render_children($form); ?>
  <a href="/<?php print $GLOBALS['language']->language ?>/user/login"
     class="btnPass"><?php print t('Back to login'); ?></a>
</div>
