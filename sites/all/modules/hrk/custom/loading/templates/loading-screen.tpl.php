<div class="loading popup-bg">
    <div class="popup-window">
        <div class="popup-header">
<!--            --><?php //print t('Fly with us - it is a pleasure!'); ?>
            <div class="popup-logo"></div>
            <div id="loader-wrapper">
                <div id="loader"></div>
            </div>
            <div class="popup-flight"></div>
        </div>

        <?php if ($advertisements): ?>
            <div class="popup-advertisement">
                <?php foreach ($advertisements as $key => $advertisement) : ?>
                    <?php $index = $key;?>
                    <?php $side = (($index + 1) % 2) ? 'float:left' : 'float:right'; ?>
                    <div class="popup-advertisement-block" style="background: url('  <?php print $advertisement->banner;?>')center no-repeat;<?php print $side;?>" >
                        <div class="popup-advertisement-head">
                            <div class="advertisement-title"><?php print ($advertisement->title);?></div>
                            <div class="advertisement-logo" style="background: url('<?php print $advertisement->logo;?>')right center no-repeat;>"></div>
                        </div>
                    </div>
                <?php endforeach; ?>
            </div>
        <?php endif; ?>
    </div>
</div>
