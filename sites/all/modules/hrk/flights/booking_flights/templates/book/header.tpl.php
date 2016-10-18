<div class="booking-header">
    <div class="airline-name"><?php /*print $airline['name'];*/ ?></div>
    <?php if (!empty($rules)): ?>
        <div class="booking-rules">
            <a href="#" class="show_rules"><?php print t('rules of exchange and return'); ?></a>
        </div>
        <div class="book-rules-popup" style="display:none">
            <?php print hrk_bf_popup('flight_rules', array('rules' => $rules, 'title' => t('Penalties'), 'close' => TRUE)); ?>
        </div>
    <?php endif; ?>
</div>