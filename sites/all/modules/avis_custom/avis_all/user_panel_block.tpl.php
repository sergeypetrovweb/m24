<?php
//TODO remove phpcode from template
$path = 'sites/all/themes/flight_modern';
global $user;
$user = user_load($user->uid);
$bonus = field_get_items('user', $user, 'field_user_bonus');
?>

<div id="breadcrumbs">
  <div class="container">
    <p class="profile_logo glyphicon glyphicon-user">
      <span><?php print t('Personal Area') ?></span></p>

    <div class="breadcrumbs_nav usrmenu">
      <?php if (!empty($bonus)): ?>
        <p
          class="user-page-item user-bonus"><?php print t('Bonuses') . ': ' . $bonus[0]['value'] ?></p>
      <?php endif; ?>

      <a
        href="/<?php print $GLOBALS['language']->language; ?>/user-book-management"
        class="<?php arg(0) == 'user-book-management' ? print 'active' : NULL ?>">
        <i
          class="glyphicon glyphicon-shopping-cart"></i><?php print t('My orders'); ?>
      </a>
      <a
        href="/<?php print $GLOBALS['language']->language; ?>/user/<?php print $user->uid ?>/edit"
        class="<?php arg(2) == 'edit' ? print 'active' : NULL ?>">
        <i class="glyphicon  glyphicon-user"></i><?php print t('My data'); ?>
      </a>
      <a href="/<?php print $GLOBALS['language']->language; ?>/tickets"
         class="<?php arg(0) == 'tickets' || arg(0) == 'faq' || (arg(0) == 'node' && node_load(arg(1))->type == 'ticket') || (arg(0) == 'node' && node_load(arg(1))->type == 'faq') ? print 'active' : NULL ?>">
        <i
          class="glyphicon glyphicon-question-sign"></i><?php print t('Help'); ?>
      </a>
    </div>
  </div>
</div>