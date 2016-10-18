<div class="booking-header">
    <div class="airline-name"><?php print $airline['name']; ?></div>
    <div class="booking-rules">
        <a href="#" class="show-rules"><?php print t('rules of exchange and return the selected tickets');?></a>
    </div>
    <div class="booking-rules-popup" style="display:none">
       <?php print $penalties;?>
    </div>
</div>