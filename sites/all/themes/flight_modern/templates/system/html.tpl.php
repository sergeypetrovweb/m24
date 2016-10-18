<!DOCTYPE html>
<html>
<head>
	<?php print $head; ?>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title><?php print $head_title; ?></title>
	<?php print $styles; ?>
    <?php print $scripts; ?>
    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
    <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
    <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
</head>

<body class="<?php print $classes; ?>" <?php print $attributes;?>>
<?php print $page_top; ?>
<?php print $page; ?>
<?php print $page_bottom; ?>
<div id="loader_block" class="sky new_load">
    <div class="loader-message">
        <h2><?php print t('We are looking for the best flights, at competitive prices.'); ?></h2>
        <p><?php print t('It takes less than a minute!'); ?></p>
    </div>
    <div class="loader_container">
        <img class="loader-throbber" src="/sites/all/themes/flight_modern/images/loader/new_load_throbber.gif">
    </div>
</div>
<?php if (1==2):?>
<!--    Временно отключённый блок-->
<div id="loader_block" class="sky">
    <div class="loader_container">
        <div class="loader-title"><?php print t('Please, wait') . '...'; ?></div>
        <div class="loader-animate"></div>
    </div>
</div>
<?php endif; ?>
</body>
</html>
