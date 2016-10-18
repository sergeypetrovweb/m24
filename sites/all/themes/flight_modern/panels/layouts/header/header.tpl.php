<nav id="off-menu" class="mm-hidden">
    <a id="mm-close-button"></a>

    <div class="top-mob">
        <div class="currency-mob">
            <?php print $content['currency']; ?>
        </div>
        <div class="language-mob">
            <?php print $content['language']; ?>
        </div>
        <?php if (user_is_logged_in()) : ?>
        <div class="user-mob">
            <?php
            global $user;
            $user = user_load($user->uid);

            if (empty($user->picture)) {
                $picture = variable_get('user_picture_default', '');
            } else {
                $picture = file_load($user->picture->fid);
                $picture = file_create_url($picture->uri);
            }
            $output = '<div class="user-pic">'.theme_image(array('path' => $picture, 'width' => 36, 'height' => 36)).'</div>';

            print $output;
            ?>
        </div>
        <?php endif; ?>
    </div>

    <?php print $content['menu']; ?>

    <ul class="user-menu">
    <?php
    $links = array();
    $links[] = array(
        'title' => t('My orders'),
        'href' => $GLOBALS['base_url'].'/' . $GLOBALS['language']->language . '/user-book-management',
        'active' => arg(0) == 'user-book-management' ? 'active': null,
    );
    $links[] = array(
        'title' => t('My data'),
        'href' => $GLOBALS['base_url'].'/' . $GLOBALS['language']->language . '/user/' . $user->uid .'/edit',
        'active' => arg(2) == 'edit' ? 'active': null,
    );
    $links[] = array(
        'title' => t('Help'),
        'href' => $GLOBALS['base_url'].'/' . $GLOBALS['language']->language . '/tickets',
        'active' => arg(0) == 'tickets' || arg(0) == 'faq' || (arg(0) == 'node' && node_load(arg(1))->type == 'ticket') || (arg(0) == 'node' && node_load(arg(1))->type == 'faq') ? 'active': null,
    );
    $links[] = array(
        'title' => t('Logout'),
        'href' => $GLOBALS['base_url'].'/' . $GLOBALS['language']->language . '/user/logout',
        'active' => null,
    );
    $link_anonymous = array(
        'title' => t('Log in'),
        'href' => $GLOBALS['base_url'].'/' . $GLOBALS['language']->language . '/user/login',
        'active' => arg(1) == 'login' ? 'active': null,
    );

    if (user_is_logged_in()) {
        foreach ($links as $id => $link) {
            print '<li class="'.$link['active'].'">' .l($link['title'], $link['href'], array('attributes' => array('class' => $link['active']))). '</li>';
        }
    } else {
        print '<li class="'.$link['active'].'">' .
          l($link_anonymous['title'], $link_anonymous['href'], array('attributes' => array('class' => $link_anonymous['active'])))
          . '</li>';
    }
    ?>
    </ul>


</nav>

<header class="headroom">
    <div class="container">
        <nav class="navbar navbar-default">
            <div class="container-fluid">

                <div class="col-lg-3 col-md-3 col-sm-12 col-xs-12 navbar-header">
                    <a href="#off-menu" class="navbar-toggle collapsed">
                        <span class="sr-only">Toggle navigation</span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                    </a>

                    <a class="navbar-brand" href="/<?php print $GLOBALS['language'] -> language; ?>/"><img src="<?php print theme_get_setting('logo') ?>"></a>
                </div>


                <div class="col-lg-9 col-md-9 col-sm-12 col-xs-12 collapse navbar-collapse" id="bs-example-navbar-collapse-1">
                    <?php print $content['menu']; ?>
                    <ul class="nav navbar-nav right login hidden-xs">
                        <li class="dropdown currency">
                            <?php print $content['currency']; ?>
                        </li>
                        <li class="dropdown languages">
                            <?php print $content['language']; ?>
                        </li>
                        <li class="dropdown user">
                            <?php print $content['user']; ?>
                        </li>
                    </ul>
                </div>
            </div>
        </nav>
    </div>
</header>