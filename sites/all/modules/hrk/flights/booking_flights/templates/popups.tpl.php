<?php if (!empty($popup) && $popup == 'bad_request'): ?>
    <div class="popup-bg popup-errors error-request bf-popup">
        <div class="popup-window">
            <?php if (!empty($close)): ?>
                <div class="popup-cross">
                    <div class="cross-icon"></div>
                </div>
            <?php endif; ?>
            <div class="popup-error-title">
                <?php print t('Nothing has been found'); ?>
            </div>
            <div class="popup-error-description">
                <?php print t('Sorry, but we could not find suitable options for you flights. Try to change search conditions.'); ?>
            </div>
            <?php if (isset($link)): ?>
                <?php print l($link['title'], $link['path'], array('attributes' => array('class' => array('popup-search', 'popup-button-error')))); ?>
            <?php endif; ?>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'disable_booking'): ?>
    <div class="popup-bg popup-errors error-request bf-popup">
        <div class="popup-window">
            <?php if (!empty($close)): ?>
                <div class="popup-cross">
                    <div class="cross-icon"></div>
                </div>
            <?php endif; ?>
            <div class="popup-error-title">
                <?php print t('Error'); ?>
            </div>
            <div class="popup-error-description">
                <?php print t('Unfortunately, the booking is not available now. Please, try again in'); ?> <?php print $left_time; ?>
            </div>
            <?php if (isset($link)): ?>
                <?php print l($link['title'], $link['path'], array('query' => $link['query'], 'attributes' => array('class' => array('popup-search', 'popup-button-error')))); ?>
            <?php endif; ?>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'connection_failed'): ?>
    <div class="popup-bg popup-errors error-server sf-popup">
        <div class="popup-window">
            <div class="popup-error-title">
                <?php print t('Error'); ?>
            </div>
            <div class="popup-error-description">
                <?php print t('Booking service is temporarily unavailable. Please try again later several minutes.'); ?>
            </div>
            <?php print l(t('Try again'), current_path(), array('attributes' => array('class' => array('popup-search', 'popup-button-error')))); ?>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'flight_rules'): ?>
    <div class="popup-bg popup-errors flight-rules bf-popup">
        <div class="popup-window">
            <?php if (!empty($close)): ?>
                <div class="popup-cross">
                    <div class="cross-icon">x</div>
                </div>
            <?php endif; ?>
            <?php if (!empty($title)): ?>
                <div class="popup-error-title"><?php print t($title); ?></div>
            <?php endif; ?>
            <?php if (!empty($rules)): ?>
                <div class="popup-error-description">
                    <?php foreach ($rules as $rule): ?>
                        <?php if ($rule['type'] == 'title'): ?>
                            <div class="title">
                                <h2><?php print $rule['text']; ?></h2>
                            </div>
                        <?php else: ?>
                            <div class="description">
                                <?php print $rule['text']; ?>
                            </div>

                        <?php endif; ?>
                    <?php endforeach; ?>
                </div>
            <?php endif; ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'rules_empty'): ?>
    <div class="popup-bg popup-errors flight-rules-empty bf-popup">
        <div class="popup-window">
            <?php if (!empty($close)): ?>
                <div class="popup-cross">
                    <div class="cross-icon"></div>
                </div>
            <?php endif; ?>
            <div class="popup-error-title"><?php print t('Error'); ?></div>
            <div class="popup-error-description">
                <?php print t('Flight rule not found'); ?>
            </div>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'amadeus_error'): ?>
    <div class="popup-bg popup-errors flight-rules-empty bf-popup">
        <div class="popup-window">
            <?php if (!empty($close)): ?>
                <div class="popup-cross">
                    <div class="cross-icon"></div>
                </div>
            <?php endif; ?>
            <div class="popup-error-title"><?php print t('Error'); ?></div>
            <div class="popup-error-description">
                <?php if (!empty($errors)): ?>
                    <?php foreach ($errors as $error): ?>
                        <div class="description"><?php print $error['text'];?></div>
                    <?php endforeach; ?>
                    <div class="description"><?php print t('Please contact the manager "@site_name"',array('@site_name'=>variable_get('site_name')));?></div>
                <?php endif; ?>
            </div>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>