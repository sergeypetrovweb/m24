<?php
//drupal_add_js('sites/all/themes/flight_modern/js/ion.rangeSlider.js', array('scope'=>'footer'));

/**
 * Обнулим системный css
 */
function  flight_modern_css_alter(&$css) {
  $exclude = array(
    'misc/vertical-tabs.css' => FALSE,
    'modules/aggregator/aggregator.css' => FALSE,
    'modules/block/block.css' => FALSE,
    'modules/book/book.css' => FALSE,
    'modules/comment/comment.css' => FALSE,
    'modules/dblog/dblog.css' => FALSE,
    'modules/file/file.css' => FALSE,
    'modules/filter/filter.css' => FALSE,
    'modules/forum/forum.css' => FALSE,
    'modules/help/help.css' => FALSE,
    'modules/menu/menu.css' => FALSE,
    'modules/node/node.css' => FALSE,
    'modules/openid/openid.css' => FALSE,
    'modules/poll/poll.css' => FALSE,
    'modules/profile/profile.css' => FALSE,
    'modules/search/search.css' => FALSE,
    'modules/statistics/statistics.css' => FALSE,
    'modules/syslog/syslog.css' => FALSE,
    'modules/system/admin.css' => FALSE,
    'modules/system/maintenance.css' => FALSE,
    'modules/system/system.css' => FALSE,
    'modules/system/system.admin.css' => FALSE,
    'modules/system/system.base.css' => FALSE,
    'modules/system/system.maintenance.css' => FALSE,
    'modules/system/system.menus.css' => FALSE,
    'modules/system/system.messages.css' => FALSE,
    'modules/system/system.theme.css' => FALSE,
    'modules/taxonomy/taxonomy.css' => FALSE,
    'modules/tracker/tracker.css' => FALSE,
    'modules/update/update.css' => FALSE,
    'modules/user/user.css' => FALSE,
  );
  $css = array_diff_key($css, $exclude);
}

/**
 * Implement HOOK_preprocess_panels_pane
 * Allow create tpl:
 * panels_pane__subtype__TYPE
 * panels_pane__pid__PID
 */
function flight_modern_preprocess_panels_pane(&$vars) {
	$vars['theme_hook_suggestions'][] = 'panels_pane__subtype__' . $vars['pane']->subtype;
	$vars['theme_hook_suggestions'][] = 'panels_pane__pid__' . $vars['pane']->pid;
	return $vars;
}

/**
 * Implements hook_preprocess_node().
 */
function flight_modern_preprocess_node(&$vars) {
//    dsm($vars);
    if($vars['view_mode'] == 'special_offers') {
        $vars['theme_hook_suggestions'][] = 'node__' . $vars['type'] . '__special_offers';
    }
}

function flight_modern_menu_tree__menu_top_menu($variables) {
    return '<ul class="nav navbar-nav main_menu">' . $variables['tree'] . '</ul>';
}

function flight_modern_menu_link(&$variables) {
    $element = $variables['element'];
    $sub_menu = '';

    if ($element['#below']) {
        $sub_menu = drupal_render($element['#below']);
    }
    $element['#localized_options']['html'] = TRUE;
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);

    // if link class is active, make li class as active too
    if(strpos($output,"active")>0){
        $element['#attributes']['class'][] = "active";
        $output = l($element['#title'] . ' <span class="sr-only">(current)</span>', $element['#href'], $element['#localized_options']);
    }
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

function flight_modern_item_list($variables) {
    $items = $variables ['items'];
    $title = $variables ['title'];
    $type = $variables ['type'];
    $attributes = $variables ['attributes'];

    // Only output the list container and title, if there are any list items.
    // Check to see whether the block title exists before adding a header.
    // Empty headers are not semantic and present accessibility challenges.
    $output = '';
    if (isset($title) && $title !== '') {
        $output .= '<h3>' . $title . '</h3>';
    }

    if (!empty($items)) {
        $output .= "<$type" . drupal_attributes($attributes) . '>';
        $num_items = count($items);
        $i = 0;
        foreach ($items as $item) {
            $attributes = array();
            $children = array();
            $data = '';
            $i++;
            if (is_array($item)) {
                foreach ($item as $key => $value) {
                    if ($key == 'data') {
                        $data = $value;
                    }
                    elseif ($key == 'children') {
                        $children = $value;
                    }
                    else {
                        $attributes [$key] = $value;
                    }
                }
            }
            else {
                $data = $item;
            }
            if (count($children) > 0) {
                // Render nested list.
                $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
            }
            if ($i == 1) {
                $attributes ['class'][] = 'first';
            }
            if ($i == $num_items) {
                $attributes ['class'][] = 'last';
            }
            $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
        }
        $output .= "</$type>";
    }
    $output .= '';
    return $output;
}

function flight_modern_links__locale_block(&$variables) {
    // the global $language variable tells you what the current language is
    global $language;

// an array of list items
    $items = array();
    foreach($variables['links'] as $lang => $info) {
        $name     = $info['language']->native;
        $href     = isset($info['href']) ? $info['href'] : '';
        $li_classes   = array('');
        // if the global language is that of this item's language, add the active class
        if($lang === $language->language){
            $li_classes[] = 'active';
        }
        $link_classes = array('');
        $options = array('attributes' => array('class'    => $link_classes),
            'language' => $info['language'],
            'html'     => true
        );
        $link = l(theme('image', array('path' => '/sites/all/themes/flight_modern/images/lang/' . $lang . '.png')) . ' ' . $name, $href, $options);

        // display only translated links
        if ($href) $items[] = array('data' => $link, 'class' => $li_classes);
    }

// output
    $attributes = array('class' => array('dropdown-menu'), 'role' => 'menu');
    $output = l(t('Language') . ': ' . '<span class="active_dropdown"><img src="/sites/all/themes/flight_modern/images/lang/'. $GLOBALS['language']->language . '.png"></span>', '#', array('html' => TRUE, 'external' => TRUE, 'attributes' => array('data-toggle' => 'dropdown', 'class' => 'dropdown-toggle', 'role' => 'button', 'aria-expanded' => 'false')));
    $output .= theme('item_list',array('items' => $items,
        'title' => '',
        'type'  => 'ul',
        'attributes' => $attributes
    ));

    return $output;
}

function flight_modern_ctools_dropdown($vars) {
    // Provide a unique identifier for every dropdown on the page.
    static $id = 0;
    $id++;

//    $class = 'ctools-dropdown-no-js ctools-dropdown' . ($vars['class'] ? (' ' . $vars['class']) : '');

    ctools_add_js('dropdown');
    ctools_add_css('dropdown');

    $output = '';

    if ($vars['image']) {
        $output .= '<a href="#" class="dropdown-toggle ctools-dropdown-link ctools-dropdown-image-link" data-toggle="dropdown" role="button" aria-expanded="false">' . $vars['title'] . '</a>';
    }
    else {
        $output .= '<a href="#" class="ctools-dropdown-link ctools-dropdown-text-link">' . check_plain($vars['title']) . '</a>';
    }

    $output .= theme_links(array('links' => $vars['links'], 'attributes' => array('class' => 'dropdown-menu', 'role' => 'menu'), 'heading' => ''));
    return $output;
}

/**
 * Implements hook_preprocess_page().
 */
function flight_modern_preprocess_page() {
    setcookie("round_trip", "", time()-3600);
}
