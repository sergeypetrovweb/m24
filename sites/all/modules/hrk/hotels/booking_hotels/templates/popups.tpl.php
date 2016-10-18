<?php if (!empty($popup) && $popup == 'empty_hotel_detail'): ?>
    <div class="popup-bg popup-errors error-server bh-popup">
        <div class="popup-window">
            <div class="popup-error-title">
                <?php print t('Error'); ?>
            </div>
            <div class="popup-error-description">
                <?php print t('Hotel information not found.'); ?>
            </div>
            <?php if (isset($link)): ?>
                <?php print l($link['title'], $link['path'], array('attributes' => array('class' => array('popup-search', 'popup-button-error')))); ?>
            <?php endif; ?>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'connection_failed'): ?>
    <div class="popup-bg popup-errors error-server bh-popup">
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

<?php if (!empty($popup) && $popup == 'show_error'): ?>
    <div class="popup-bg popup-errors error-server bh-popup">
        <div class="popup-window">
            <div class="popup-error-title">
                <?php print t('Error'); ?>
            </div>
            <div class="popup-error-description">
                <?php print $text; ?>
            </div>
            <?php if (isset($link)): ?>
                <?php print l($link['title'], $link['path'], array('attributes' => array('class' => array('popup-search', 'popup-button-error')))); ?>
            <?php endif; ?>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'package_not_found'): ?>
    <div class="popup-bg popup-errors error-server bh-popup">
        <div class="popup-window">
            <div class="popup-error-title">
                <?php print t('Error'); ?>
            </div>
            <div class="popup-error-description">
                <?php print t('Information about the rooms not found.'); ?>
            </div>
            <?php if (isset($link)): ?>
                <?php print l($link['title'], $link['path'], array('attributes' => array('class' => array('popup-search', 'popup-button-error')))); ?>
            <?php endif; ?>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>


<?php if (!empty($popup) && $popup == 'booking_error'): ?>
    <div class="popup-bg popup-errors error-server bh-popup">
        <div class="popup-window">
            <div class="popup-error-title">
                <?php print t('Error'); ?>
            </div>
            <div class="popup-error-description">
                <?php print t('Sorry currently reservation is not possible.'); ?>
            </div>
            <?php if (isset($link)): ?>
                <?php print l($link['title'], $link['path'], array('attributes' => array('class' => array('popup-search', 'popup-button-error')))); ?>
            <?php endif; ?>
            <?php print l(t('Back to home'), '', array('attributes' => array('class' => array('popup-home', 'popup-button-error')))); ?>
        </div>
    </div>
<?php endif; ?>

<?php if (!empty($popup) && $popup == 'hotel_policy'): ?>
    <div class="popup-bg popup-errors hotel-rules bh-popup">
        <div class="popup-window">
            <?php if (!empty($close)): ?>
                <div class="popup-cross">
                    <div class="cross-icon no-remove"></div>
                </div>
            <?php endif; ?>
            <?php if (!empty($title)): ?>
                <div class="popup-error-title"><?php print t($title); ?></div>
            <?php endif; ?>
            <?php if (!empty($polices)): ?>
                <div class="popup-error-description">
                    <ul>
                        <?php if (!empty($polices)): ?>
                            <?php $free_cancellation_time = strtotime('-1 days', strtotime($polices[0]['date_from'])); ?>
                            <?php if ($free_cancellation_time > REQUEST_TIME): ?>
                                <?php $date_free_cancellation = format_date($free_cancellation_time, 'medium', 'j F'); ?>
                                <li>
                                    <span>
                                        <?php print t('In case of booking cancellation up until @date, no fee will be charged.', array('@date' => $date_free_cancellation)); ?>
                                    </span>
                                </li>
                            <?php else: ?>
                                <li>
                                    <span>
                                        <?php print t('No free cancellation.'); ?>
                                    </span>
                                </li>
                            <?php endif; ?>
                            <?php foreach ($polices as $policy): ?>
                                <?php $policy = (object)$policy; ?>
                                <?php $date_from_timestamp = strtotime($policy->date_from);?>
                                <?php $date_to_timestamp = strtotime($policy->date_to);?>
                                <?php $date_from = (!empty($date_from_timestamp)) ? format_date($date_from_timestamp, 'medium', 'j F'):FALSE; ?>
                                <?php $date_to = (!empty($date_to_timestamp)) ? format_date($date_to_timestamp, 'medium', 'j F') : FALSE; ?>
                                <?php if ($date_from && $date_to): ?>
                                    <li>
                                        <span>
                                            <?php print t('During the period from @date_from to @date_to, booking cancellation fees will be @price '.$policy->currency.'. @description',
                                                array('@date_from' => $date_from, '@date_to' => $date_to, '@price' => ceil($policy->price), '@description' => $policy->description));?>
                                        </span>
                                    </li>
                                <?php else: ?>
                                    <li>
                                        <span>
                                            <?php print t('From @date_from, cancellation fees will be @price '.$policy->currency.'. @description',
                                                array('@date_from' => $date_from, '@price' => ceil($policy->price), '@description' => $policy->description));?>
                                        </span>
                                    </li>
                                <?php endif; ?>
                            <?php endforeach; ?>
                        <?php endif; ?>
                    </ul>
                </div>
            <?php endif; ?>
        </div>
    </div>
<?php endif; ?>