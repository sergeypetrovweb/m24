<div id="social">
    <div class="container">
        <div class="menu_seacrh">
            <?php
            $menu = menu_tree('menu-search-menu');
            $menu = drupal_render($menu);
            print $menu;
            ?>
        </div>
        <div class="social">
            <?php print t($settings['title']) ?>
            <?php for ($i = 0; $i < $settings['items']['count_items']; $i++) : ?>
                <?php
                $img = file_load($settings['items'][$i]['img']);
                $img = theme_image(array('path' => $img->uri));
                print l($img, $settings['items'][$i]['url'], array('html' => true));
                ?>
            <?php endfor; ?>
        </div>
    </div>
</div>