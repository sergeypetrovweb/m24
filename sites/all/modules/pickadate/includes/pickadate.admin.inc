<?php

function pickadate_admin_settings($form, $form_state)
{

    $form['pickadate_variant'] = array(
        '#title' => t('Pickadate variant'),
        '#description' => t('Select the variant for Pickadate. Default presents full version library with classic.css and default.css.'),
        '#type' => 'select',
        '#options' => array(
            'full' => t('Full with classic.css and default.css'),
            'min_all_themes' => t('Min with compressed classic.css and default.css'),
            'min_default' => t('Min with compressed default.css'),
            'min_classic' => t('Min with compressed classic.css'),
        ),
        '#default_value' => variable_get('pickadate_variant', 'full')
    );

    return system_settings_form($form);
}