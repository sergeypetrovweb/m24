<?php

//dsm($hotel);
?>

<div class="booking-guests">
    <h2><?php print t('Guests');?></h2>
    <div class="passenger-table">
        <div class="passenger-table-header">
            <div class="surname"><?php print t('Last name');?></div>
            <div class="passenger-name"><?php print t('First name');?></div>
        </div>
        <div class="transition-hr"></div>

        <?php foreach ($guests as $type => $guest_by_type): ?>
            <?php foreach ($guest_by_type as $index => $guest): ?>
                <div class="passenger-unit-wrapper passenger-adt-row">
                    <?php $guest = (object)$guest; ?>
                    <div class="passenger-number">
                        <?php print $index; ?>
                    </div>
                    <div class="passenger-sex">
                        <?php print $guest->sex; ?>
                    </div>
                    <div class="surname">
                        <?php print $guest->last_name; ?>
                    </div>
                    <div class="passenger-name">
                        <?php print $guest->first_name; ?>
                    </div>
                </div>
            <?php endforeach; ?>
        <?php endforeach; ?>
    </div>
</div>