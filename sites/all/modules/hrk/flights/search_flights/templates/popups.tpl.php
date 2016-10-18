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

<?php if (!empty($popup) && $popup == 'no_available_flights'): ?>
    <div class="popup-bg popup-errors error-not-found sf-popup">
        <div class="popup-window">
            <div class="popup-cross">
                <div class="cross-icon"></div>
            </div>
            <div class="popup-error-title">
                <?php print t('Nothing has been found'); ?>
            </div>
            <div class="popup-error-description">
                <?php print t('Sorry, but we could not find suitable options for you flights. Try to change search conditions.'); ?>
            </div>
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
                <?php print t('Search service is temporarily unavailable. Please try again after several minutes.'); ?>
            </div>
            <?php print l(t('Try again'), current_path(), array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'server_error'): ?>
    <div class="popup-bg popup-errors error-unexpected sf-popup">
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