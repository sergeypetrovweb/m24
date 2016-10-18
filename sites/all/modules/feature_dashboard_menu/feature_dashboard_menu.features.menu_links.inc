<?php
/**
 * @file
 * feature_dashboard_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function feature_dashboard_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_--:admin/config/payment.
  $menu_links['management_--:admin/config/payment'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/payment',
    'router_path' => 'admin/config/payment',
    'link_title' => 'Информация о заказах',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'identifier' => 'management_--:admin/config/payment',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'management_dashboard:user',
  );
  // Exported menu link: management_--:control/ourteam.
  $menu_links['management_--:control/ourteam'] = array(
    'menu_name' => 'management',
    'link_path' => 'control/ourteam',
    'router_path' => 'control/ourteam',
    'link_title' => 'Блок "Наша команда"',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'identifier' => 'management_--:control/ourteam',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'management_dashboard:user',
  );
  // Exported menu link: management_-:control/brands.
  $menu_links['management_-:control/brands'] = array(
    'menu_name' => 'management',
    'link_path' => 'control/brands',
    'router_path' => 'control/brands',
    'link_title' => 'Список партнёров',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'identifier' => 'management_-:control/brands',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'management_dashboard:user',
  );
  // Exported menu link: management_-:control/social.
  $menu_links['management_-:control/social'] = array(
    'menu_name' => 'management',
    'link_path' => 'control/social',
    'router_path' => 'control/social',
    'link_title' => 'Социальные сети',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'identifier' => 'management_-:control/social',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'management_dashboard:user',
  );
  // Exported menu link: management_:control/contacts.
  $menu_links['management_:control/contacts'] = array(
    'menu_name' => 'management',
    'link_path' => 'control/contacts',
    'router_path' => 'control/contacts',
    'link_title' => 'Контакты',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'identifier' => 'management_:control/contacts',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'management_dashboard:user',
  );
  // Exported menu link: management_:control/footer.
  $menu_links['management_:control/footer'] = array(
    'menu_name' => 'management',
    'link_path' => 'control/footer',
    'router_path' => 'control/footer',
    'link_title' => 'Футер',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'identifier' => 'management_:control/footer',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'management_dashboard:user',
  );
  // Exported menu link: management_:control/hotels.
  $menu_links['management_:control/hotels'] = array(
    'menu_name' => 'management',
    'link_path' => 'control/hotels',
    'router_path' => 'control/hotels',
    'link_title' => 'Отели',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'identifier' => 'management_:control/hotels',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'management_dashboard:user',
  );
  // Exported menu link: management_:control/spec_city.
  $menu_links['management_:control/spec_city'] = array(
    'menu_name' => 'management',
    'link_path' => 'control/spec_city',
    'router_path' => 'control/spec_city',
    'link_title' => 'Города',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'identifier' => 'management_:control/spec_city',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'management_dashboard:user',
  );
  // Exported menu link: management_:control/spec_flight.
  $menu_links['management_:control/spec_flight'] = array(
    'menu_name' => 'management',
    'link_path' => 'control/spec_flight',
    'router_path' => 'control/spec_flight',
    'link_title' => 'Перелёты',
    'options' => array(
      'attributes' => array(),
      'alter' => TRUE,
      'identifier' => 'management_:control/spec_flight',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'management_dashboard:user',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Блок "Наша команда"');
  t('Города');
  t('Информация о заказах');
  t('Контакты');
  t('Отели');
  t('Перелёты');
  t('Социальные сети');
  t('Список партнёров');
  t('Футер');

  return $menu_links;
}
