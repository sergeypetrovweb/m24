<?php if (!empty($popup) && $popup == 'session_expired'): ?>
    <div class="popup-bg popup-errors error-session ep-popup">
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
                <?php print t('Your search session ended. Please search again.'); ?>
            </div>
            <?php if (isset($link)): ?>
                <?php print l($link['title'], $link['path'], array('attributes' => array('class' => array('popup-search', 'popup-button-error')))); ?>
            <?php endif; ?>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'server_error'): ?>
    <div class="popup-bg popup-errors error-unexpected ep-popup">
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
                <?php print t('Unfortunately, an error occurred. Please search again.'); ?>
            </div>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'connection_failed'): ?>
    <div class="popup-bg popup-errors error-server ep-popup">
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
                <?php print t('Search service is temporarily unavailable. Please try again after several minutes.'); ?>
            </div>
            <?php if (isset($link)): ?>
                <?php print l($link['title'], $link['path'], array('attributes' => array('class' => array('popup-search', 'popup-button-error')))); ?>
            <?php endif; ?>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>


