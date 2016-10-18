<div id="advanced_search" class="variant_one">
    <div class="container">
        <div class="title_adv_seacrh">
            <?php if ($title): ?>
                <h1><?php print $title; ?></h1>
            <?php endif; ?>
        </div>
        <?php print render($content); ?>
    </div>
</div>

