<?php

function ep_configuration_form($form, $form_state)
{
    $configuration = (object)variable_get('e_power', array());

    $form['e_power'] = array(
        '#type' => 'fieldset',
        '#title' => t('Connection'),
        '#tree' => TRUE
    );

    $form['e_power']['mode'] = array(
        '#type' => 'radios',
        '#title' => t('Mode'),
        '#options' => array('test' => t('TEST'), 'real' => t('REAL')),
        '#default_value' => isset($configuration->mode) ? $configuration->mode : 'test',
        '#attributes' => array('class' => array('container-inline'))
    );

    $form['e_power']['test'] = array(
        '#type' => 'fieldset',
        '#title' => t('TEST mode Connection info'),
        '#collapsible' => TRUE,
    );

    $form['e_power']['test']['request_url'] = array(
        '#type' => 'textfield',
        '#title' => 'TEST Request URL',
        '#size'=>90,
        '#required'=>TRUE,
        '#description' => t('Enter full url with http://'),
        '#default_value' => isset($configuration->test['request_url']) ? $configuration->test['request_url'] : ''
    );

    $form['e_power']['test']['client_url'] = array(
        '#type' => 'textfield',
        '#title' => 'TEST Client URL',
        '#size'=>90,
        '#required'=>TRUE,
        '#description' => t('Enter full url with http:// and ?WSDL'),
        '#default_value' => isset($configuration->test['client_url']) ? $configuration->test['client_url'] : ''
    );

    $form['e_power']['test']['login'] = array(
        '#type' => 'textfield',
        '#title' => 'TEST login',
        '#required'=>TRUE,
        '#default_value' => isset($configuration->test['login']) ? $configuration->test['login'] : ''
    );

    $form['e_power']['test']['password'] = array(
        '#type' => 'textfield',
        '#title' => 'TEST password',
        '#required'=>TRUE,
        '#default_value' => isset($configuration->test['password']) ? $configuration->test['password'] : ''
    );

    $form['e_power']['test']['secure_code'] = array(
        '#type' => 'textfield',
        '#title' => 'Booking secure code',
        '#required'=>TRUE,
        '#default_value' => isset($configuration->test['secure_code']) ? $configuration->test['secure_code'] : ''
    );

    $form['e_power']['real'] = array(
        '#type' => 'fieldset',
        '#title' => t('REAL mode Connection info'),
        '#collapsible' => TRUE,
    );

    $form['e_power']['real']['request_url'] = array(
        '#type' => 'textfield',
        '#title' => 'Request URL',
        '#size'=>90,
        '#required'=>TRUE,
        '#description' => t('Enter full url with http://'),
        '#default_value' => isset($configuration->real['request_url']) ? $configuration->real['request_url'] : ''
    );

    $form['e_power']['real']['client_url'] = array(
        '#type' => 'textfield',
        '#title' => 'Client URL',
        '#size'=>90,
        '#required'=>TRUE,
        '#description' => t('Enter full url with http:// and ?WSDL'),
        '#default_value' => isset($configuration->real['client_url']) ? $configuration->real['client_url'] : ''
    );

    $form['e_power']['real']['login'] = array(
        '#type' => 'textfield',
        '#title' => 'REAL login',
        '#required'=>TRUE,
        '#default_value' => isset($configuration->real['login']) ? $configuration->real['login'] : ''
    );

    $form['e_power']['real']['password'] = array(
        '#type' => 'textfield',
        '#title' => 'REAL password',
        '#required'=>TRUE,
        '#default_value' => isset($configuration->real['password']) ? $configuration->real['password'] : ''
    );

    $form['e_power']['real']['secure_code'] = array(
        '#type' => 'textfield',
        '#title' => 'Booking secure code',
        '#required'=>TRUE,
        '#default_value' => isset($configuration->real['secure_code']) ? $configuration->real['secure_code'] : ''
    );

    $form['test_request_xml_log'] = array(
      '#type' => 'radios',
      '#title' => 'TESTING: XML log file save',
      '#default_value' => variable_get('test_request_xml_log'),
      '#options' => array(TRUE => 'on', FALSE => 'off'),
    );

    return system_settings_form($form);
}