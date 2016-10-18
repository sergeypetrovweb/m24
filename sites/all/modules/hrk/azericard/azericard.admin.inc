<?php

function azericard_configuration_form($form, &$form_state)
{
    global $base_url;
    global $language;
    $l_prefix = ($language->language == 'en') ? 'en' : 'ru';

    $configuration = (object)variable_get('azericard', array());

    $form['azericard'] = array(
        '#type' => 'fieldset',
        '#title' => t('Connection'),
        '#tree' => TRUE
    );

    $form['azericard']['merchant_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Merchant URL'),
        '#size' => 90,
        '#required' => TRUE,
        '#default_value' => isset($configuration->merchant_url) ? $configuration->merchant_url : $base_url
    );

    $form['azericard']['merchant_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Merchant Name'),
        '#size' => 90,
        '#required' => TRUE,
        '#default_value' => isset($configuration->merchant_name) ? $configuration->merchant_name : variable_get('site_name')
    );

    $form['azericard']['merchant_gmt'] = array(
        '#type' => 'textfield',
        '#title' => t('Merchant GTM'),
        '#size' => 90,
        '#required' => TRUE,
        '#default_value' => isset($configuration->merchant_gmt) ? $configuration->merchant_gmt : 0
    );

    $query = db_select('hrk_sf_countries', 'c')->fields('c', array()); //get countries phone codes
    $result = $query->execute();
    $countries = array();
    foreach ($result as $row) {
        $name = 'name_' . $l_prefix;
        $countries[$row->code] = $row->$name;
    }

    $form['azericard']['country'] = array(
        '#type' => 'select',
        '#title' => t('Country'),
        '#options' => $countries,
        '#required' => TRUE,
        '#empty_option' => t('Select a country'),
        '#default_value' => isset($configuration->country) ? $configuration->country : '',
        '#select2' => array(
            'placeholder' => t('Select a country'),
            'allowClear' => FALSE,
            'minimumResultsForSearch' => 1
        ),
    );

    $form['azericard']['mode'] = array(
        '#type' => 'radios',
        '#title' => t('Mode'),
        '#required' => TRUE,
        '#options' => array('test' => t('TEST'), 'real' => t('REAL')),
        '#default_value' => isset($configuration->mode) ? $configuration->mode : 'dev',
        '#attributes' => array('class' => array('container-inline'))
    );

    $form['azericard']['test'] = array(
        '#type' => 'fieldset',
        '#title' => t('TEST mode Connection info'),
        '#collapsible' => TRUE,
    );

    $form['azericard']['test']['url'] = array(
        '#type' => 'textfield',
        '#title' => 'TEST Portal URL',
        '#size' => 90,
        '#required' => TRUE,
        '#description' => t('Enter full url with http://'),
        '#default_value' => isset($configuration->test['url']) ? $configuration->test['url'] : ''
    );

    $form['azericard']['test']['key_for_sign'] = array(
        '#type' => 'textfield',
        '#title' => t('KEY For SignIn'),
        '#size' => 90,
        '#required' => TRUE,
        '#default_value' => isset($configuration->test['key_for_sign']) ? $configuration->test['key_for_sign'] : ''
    );

    $form['azericard']['test']['terminal'] = array(
        '#type' => 'textfield',
        '#title' => t('Terminal'),
        '#size' => 90,
        '#required' => TRUE,
        '#default_value' => isset($configuration->test['terminal']) ? $configuration->test['terminal'] : ''
    );

    $form['azericard']['real'] = array(
        '#type' => 'fieldset',
        '#title' => t('REAL mode Connection info'),
        '#collapsible' => TRUE,
    );

    $form['azericard']['real']['url'] = array(
        '#type' => 'textfield',
        '#title' => 'REAL Portal URL',
        '#size' => 90,
        '#required' => TRUE,
        '#description' => t('Enter full url with http://'),
        '#default_value' => isset($configuration->real['url']) ? $configuration->real['url'] : ''
    );

    $form['azericard']['real']['key_for_sign'] = array(
        '#type' => 'textfield',
        '#title' => t('KEY For SignIn'),
        '#size' => 90,
        '#required' => TRUE,
        '#default_value' => isset($configuration->real['key_for_sign']) ? $configuration->real['key_for_sign'] : ''
    );

    $form['azericard']['real']['terminal'] = array(
        '#type' => 'textfield',
        '#title' => t('Terminal'),
        '#size' => 90,
        '#required' => TRUE,
        '#default_value' => isset($configuration->real['terminal']) ? $configuration->real['terminal'] : ''
    );

    return system_settings_form($form);
}