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
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'loading'): ?>
    <div class="popup-bg popup-errors popup-loading">
        <div class="popup-window">
            <?php if (!empty($close)): ?>
                <div class="popup-cross">
                    <div class="cross-icon"></div>
                </div>
            <?php endif; ?>
            <div class="popup-header">
                <div id="loader-wrapper">
                    <div id="loader"></div>
                </div>
                <div class="popup-flight"></div>
            </div>
        </div>
    </div>
<?php endif; ?>

<!--<div class="popup-bg popup-errors error-server">-->
<!--    <div class="popup-window">-->
<!--        <div class="popup-cross">-->
<!--            <div class="cross-icon">+</div>-->
<!--        </div>-->
<!--        <div class="popup-error-title">ошибка</div>-->
<!--        <div class="popup-error-description">Сервис поиска временно недоступен. Пожалуйста, повторите попытку через-->
<!--        несколько минут.</div>-->
<!--        <a href="#" class="popup-home">Вернуться на главную</a>-->
<!--    </div>-->
<!--</div>-->

<!--<div class="popup-bg popup-errors error-unexpected">-->
<!--    <div class="popup-window">-->
<!--        <div class="popup-cross">-->
<!--            <div class="cross-icon">+</div>-->
<!--        </div>-->
<!--        <div class="popup-error-title">ошибка</div>-->
<!--        <div class="popup-error-description">К сожалению, произошла ошибка. Пожалуйста, повторите поиск.</div>-->
<!--        <a href="#" class="popup-search popup-button-error">Повторить поиск</a>-->
<!--        <a href="#" class="popup-home popup-button-error">Вернуться на главную</a>-->
<!--    </div>-->
<!--</div>-->

<!--<div class="popup-bg popup-errors error-session">-->
<!--    <div class="popup-window">-->
<!--        <div class="popup-cross">-->
<!--            <div class="cross-icon">+</div>-->
<!--        </div>-->
<!--        <div class="popup-error-title">ошибка</div>-->
<!--        <div class="popup-error-description">Ваша поисковая сессия закончилась. Пожалуйста, повторите поиск.</div>-->
<!--        <a href="#" class="popup-search popup-button-error">Повторить поиск</a>-->
<!--        <a href="#" class="popup-home popup-button-error">Вернуться на главную</a>-->
<!--    </div>-->
<!--</div>-->


