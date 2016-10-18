<?php if (!empty($popup) && $popup == 'validation'): ?>
    <div class="popup-bg popup-errors error-request">
        <div class="popup-window">
            <div class="popup-error-title">
                <?php print t('Error'); ?>
            </div>
            <div class="popup-error-description">
                <?php print t('Invalid search query. Please start a new search.'); ?>
            </div>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'no_available_hotels'): ?>
    <div class="popup-bg popup-errors error-not-found sh-popup">
        <div class="popup-window">
            <div class="popup-cross">
                <div class="cross-icon"></div>
            </div>
            <div class="popup-error-title">
                <?php print t('unfortunately, nothing has been found'); ?>
            </div>
            <div class="popup-error-description">
                <?php print t('Given search criterias are no hotels. Try change the check-in and check-out dates.'); ?>
            </div>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'connection_failed'): ?>
    <div class="popup-bg popup-errors error-server sh-popup">
        <div class="popup-window">
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

<?php if (!empty($popup) && $popup == 'server_error'): ?>
    <div class="popup-bg popup-errors error-unexpected sh-popup">
        <div class="popup-window">
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

<?php if (!empty($popup) && $popup == 'show_error'): ?>
    <div class="popup-bg popup-errors error-unexpected sh-popup">
        <div class="popup-window">
            <div class="popup-error-title">
                <?php print t('Error'); ?>
            </div>
            <div class="popup-error-description">
                <?php print t($text); ?>
            </div>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>