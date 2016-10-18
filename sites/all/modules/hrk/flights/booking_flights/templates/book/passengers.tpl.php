<?php if (!empty($passengers)) : ?>
    <div class="passenger-wrapper">
        <h2><?php print t('passengers');?></h2>
        <div class="passenger-table">
            <div class="passenger-table-header">
                <div class="surname"><?php print t('Last name');?></div>
                <div class="passenger-name"><?php print t('First name');?></div>
                <div class="passenger-birth"><?php print t('Date of birth');?></div>
                <div class="passenger-passport"><?php print t('Passport number');?></div>
            </div>
            <div class="transition-hr"></div>

            <?php foreach ($passengers as $type => $passengers_by_type): ?>
                <?php foreach ($passengers_by_type as $index => $passenger): ?>
                    <div class="passenger-unit-wrapper passenger-adt-row">
                        <?php $passenger = (object)$passenger; ?>
                        <div class="passenger-number">
                            <?php print $index + 1; ?>
                        </div>
                        <div class="passenger-sex">
                            <?php print $passenger->sex; ?>
                        </div>
                        <div class="surname">
                            <?php print $passenger->last_name; ?>
                        </div>
                        <div class="passenger-name">
                            <?php print $passenger->first_name; ?>
                        </div>
                        <div class="passenger-birth">
                            <?php print format_date(strtotime($passenger->birthday), 'medium', 'd.m.Y'); ?>
                        </div>
                        <div class="passenger-passport">
                            <?php print $passenger->document['id']; ?>
                        </div>
                    </div>
                <?php endforeach; ?>
            <?php endforeach; ?>
        </div>
    </div>
<?php endif; ?>