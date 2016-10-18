<div class="hotel-article hotel-policy">
    <h3><?php print t('terms, conditions and limitations'); ?></h3>
    <div>
        <ul class="style">
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
                               <?php print t("During the period from @date_from to @date_to, booking cancellation fees will be @price ". $policy->currency .". @description",
                                   array('@date_from' => $date_from, '@date_to' => $date_to, '@price' => ceil($policy->price), '@description' => $policy->description));?>
                            </span>
                        </li>
                        <?php else: ?>
                        <li>
                            <span>
                                <?php print t("From @date_from, cancellation fees will be @price ". $policy->currency .". @description",
                                    array('@date_from' => $date_from, '@price' => ceil($policy->price), '@description' => $policy->description));?>
                            </span>
                        </li>
                    <?php endif; ?>

                <?php endforeach; ?>
            <?php endif; ?>
        </ul>
    </div>
</div>

