<div class="conditions-wrapper">
    <div>
        <h2 class="section_title"><?php print t('Terms, conditions and limitations'); ?></h2>
        <div>
            <div class="condition-item">
                <div class="booking-rules">
                    <a href="#" class="show-rules"><?php print t('Rules of exchange and return the selected tickets');?></a>
                </div>
                <div class="booking-rules-popup" style="display:none">
                    <?php print $penalties;?>
                </div>
            </div>
        </div>
    </div>
</div>


<?php if (1 == 2): ?>
<!--    hide some useful code-->
    <!--                <div class="blue-dot"></div>-->
    <!--                <div class="condition-text">-->
    <!--                    --><?php //print t('Please read the '); ?>
    <!--                    <a href="--><?php //url('/agreement'); ?><!--">--><?php //print t('agreement with Flight.az'); ?><!--</a>-->
    <!--                    --><?php //print t('and conditions'); ?>
    <!--                    <a href="#" class="show-rules">--><?php //print t('refund / exchange');?><!--</a>-->
    <!--                    --><?php //print t(' tickets') . '.'; ?>
    <!--                </div>-->
    <!--                <div class="condition-item">-->
    <!--                    <div class="blue-dot"></div>-->
    <!--                    <div class="condition-text">-->
    <!--                        --><?php //print t('Please read the '); ?>
    <!--                        <a target="_blank" href="--><?php //print $rule_link['path']; ?><!--">--><?php //print t('rules of the carrier @airline.', array('@airline' => $rule_link['title'])); ?><!--</a>-->
    <!--                    </div>-->
    <!--                </div>-->
<?php endif; ?>