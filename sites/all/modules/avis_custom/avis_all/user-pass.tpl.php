<div class="login_form">
  <h2><?php print t('Reset password'); ?></h2>
  <a href="/<?php print $GLOBALS['language']->language ?>/user/register"
     class="btnReg" title="Регистрация"><?php print t('Registration'); ?></a>
  <?php print theme_status_messages(array('display' => 'error')); ?>
  <?php print drupal_render_children($form); ?>
  <a href="/<?php print $GLOBALS['language']->language ?>/user/login"
     class="btnPass"><?php print t('Back to login'); ?></a>
</div>
