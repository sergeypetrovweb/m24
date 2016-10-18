<?php
$img = file_load($settings['img']);
$img = file_create_url($img->uri);
?>

<div class="p90">
    <div class="container">
        <div class="row">
            <div class="grid_6 wrap">
                <div class="block">
                    <h2 class="col2"><?php print $settings['title'] ?></h2>
                    <div class="image"><img src="<?php print $img ?>" alt=""></div>
                    <h4><span class="not-a-link"><?php print $settings['description'] ?></span></h4>
                    <p><?php print $settings['content'] ?></p>
                    <a href="<?php print $settings['link'] ?>" class="link1 col1">more</a>
                </div>
            </div>
            <div class="grid_6">
                <h2 class="col2">News</h2>

                <?php print views_embed_view('news', 'news_front'); ?>

                <a href="#" class="link1 col1">more news</a>
            </div>
        </div>
    </div>
</div>