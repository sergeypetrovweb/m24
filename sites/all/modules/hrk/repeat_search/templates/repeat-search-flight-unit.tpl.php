<?php global $language;
$l_prefix = ($language->language == 'ru') ? $language->language : 'en';
?>
<?php if (!empty($flight)): ?>
    <a href="<?php print url($flight->path); ?>">
        <div class="rs-cities">
            <?php if (!empty($flight->info['from']['trip'])): ?>
                <div class="rs-city">
                    <?php print $flight->info['from']['trip']['name_' . $l_prefix]; ?>
                </div>
            <?php endif; ?>

            <div class="rw-direction-arrows">
                    <?php if ($flight->direction == 'round_trip') print '↔'; ?>
                    <?php if ($flight->direction == 'one_way') print '→'; ?>
                    <?php if ($flight->direction == 'multi_stop') print '→ →'; ?>
            </div>

            <?php if (!empty($flight->info['to']['trip'])): ?>
                <div class="rs-city">
                    <?php print $flight->info['to']['trip']['name_' . $l_prefix]; ?>
                </div>
            <?php endif; ?>

        </div>
        <div class="rs-time">
            <?php if (!empty($flight->info['from']['time'])): ?>
                <div class="rs-from-time rs-time">
                    <?php print format_date($flight->info['from']['time'], 'medium', 'j M'); ?>
                </div>
            <?php endif; ?>
            <?php if (!empty($flight->info['to']['time'])): ?>
                <div class="rs-from-time rs-time">
                    - <?php print format_date($flight->info['to']['time'], 'medium', 'j M'); ?>
                </div>
            <?php endif; ?>
        </div>
    </a>
<?php endif; ?>