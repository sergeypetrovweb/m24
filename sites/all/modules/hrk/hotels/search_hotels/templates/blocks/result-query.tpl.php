<?php
global $language;
$l_prefix = ($language->language == 'en') ? 'en' : 'ru';
?>
<?php if ($location): ?>
    <?php $location = (object)$location; ?>
    <div class="result-top-panel">
        <div class="parameters-wrapper">
            <div class="parameters-left">
                <div class="hotelss-icon"></div>
                <div class="parameters-root">
                    <div class="parameters-block">
                        <div class="parameters-top">
                            <div class="parameters-check-in">
                                <?php print ($location->check_in) ? date('d.m.y', $location->check_in) : ''; ?>
                            </div>
                            <div class="parameters-check-out"> &mdash;
                                <?php print ($location->check_out) ? date('d.m.y', $location->check_out) : ''; ?>
                            </div>
                        </div>
                        <div class="parameters-city">
                            <?php if (empty($location->info['name_ru'])): ?>
                                <?php $city_name = $location->info['name_en'];?>
                            <?php else:?>
                                <?php $city_name = $location->info['name_'.$l_prefix];?>
                            <?php endif; ?>

                            <?php $popup_content = $location->info['country']['name_' . $l_prefix]; ?>

                            <a onclick="return false;" title="<?php print $popup_content; ?>" class="tooltiper" href="#">
                                <?php print $city_name; ?>
                            </a>
                        </div>
                    </div>
                </div>
            </div>
            <div class="parameters-right">
                <div class="change-parameters">
                    <a class="change-parameters-link"
                       href="<?php print $location->change_params_link; ?>"><?php print t('Change settings'); ?></a>
                </div>
            </div>
        </div>
    </div>
<?php endif; ?>