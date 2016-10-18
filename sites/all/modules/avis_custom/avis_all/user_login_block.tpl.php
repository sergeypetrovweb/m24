<?php
//TODO remove phpcode from template
$path = 'sites/all/themes/flight_modern';
global $user;
$user = user_load($user->uid);

if (empty($user->picture)) {
  $picture = variable_get('user_picture_default', '');
}
else {
  $picture = file_load($user->picture->fid);
  $picture = file_create_url($picture->uri);
}
$link_output = '<div class="user-name">' . $user->name . '<span class="user-pic"><img src="' . $picture
  . '"></span><span class="glyphicon glyphicon-triangle-bottom"></span></div>';

$links = array();
$links[] = array(
  'title' => '<span class="glyphicon glyphicon-shopping-cart"></span>' . t('My orders'),
  'href' => $GLOBALS['base_url'] . '/' . $GLOBALS['language']->language . '/user-book-management',
  'html' => TRUE,
);
$links[] = array(
  'title' => '<span class="glyphicon glyphicon-user"></span>' . t('My data'),
  'href' => $GLOBALS['base_url'] . '/' . $GLOBALS['language']->language . '/user/' . $user->uid . '/edit',
  'html' => TRUE,
);
$links[] = array(
  'title' => '<span class="glyphicon glyphicon-question-sign"></span>' . t('Help'),
  'href' => $GLOBALS['base_url'] . '/' . $GLOBALS['language']->language . '/tickets',
  'html' => TRUE,
);
$links[] = array(
  'title' => '<span class="glyphicon glyphicon-off"></span>' . t('Logout'),
  'href' => $GLOBALS['base_url'] . '/' . $GLOBALS['language']->language . '/user/logout',
  'html' => TRUE,
);
$output = theme('ctools_dropdown', array(
  'title' => $link_output,
  'links' => $links,
  'image' => TRUE
));

print $output;
?>