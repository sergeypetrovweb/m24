<?php global $language;
$l_prefix = ($language->language == 'ru') ? $language->language : 'en';
?>
<?php if (!empty($hotel)): ?>
    <a href="<?php print url($hotel->path); ?>">
        <div class="rs-cities">
            <?php if (!empty($hotel->info['location'])): ?>
                <div class="rs-city">
                    <?php if (empty($hotel->info['location']['name_ru'])): ?>
                        <?php print $hotel->info['location']['name_en']; ?>
                    <?php else: ?>
                        <?php print $hotel->info['location']['name_' . $l_prefix]; ?>
                    <?php endif; ?>
                </div>
            <?php endif; ?>
        </div>
        <div class="rs-time">
            <?php if (!empty($hotel->info['check_in'])): ?>
                <div class="rs-from-time rs-time">
                    <?php print format_date($hotel->info['check_in'], 'medium', 'j M'); ?>
                </div>
            <?php endif; ?>
            <?php if (!empty($hotel->info['check_out'])): ?>
                <div class="rs-from-time rs-time">
                    - <?php print format_date($hotel->info['check_out'], 'medium', 'j M'); ?>
                </div>
            <?php endif; ?>
        </div>
    </a>
<?php endif; ?>