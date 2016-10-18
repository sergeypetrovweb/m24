<?php

function cl_configuration_form($form, $form_state)
{
    $configuration = (object)variable_get('carsolize', array());

    $form['carsolize'] = array(
        '#type' => 'fieldset',
        '#title' => t('Connection'),
        '#tree' => TRUE
    );

    $form['carsolize']['mode'] = array(
        '#type' => 'radios',
        '#title' => t('Mode'),
        '#options' => array('test' => t('TEST'), 'real' => t('REAL')),
        '#default_value' => isset($configuration->mode) ? $configuration->mode : 'test',
        '#attributes' => array('class' => array('container-inline'))
    );

    $form['carsolize']['test'] = array(
        '#type' => 'fieldset',
        '#title' => t('TEST mode Connection info'),
        '#collapsible' => TRUE,
    );

    $form['carsolize']['test']['request_url'] = array(
        '#type' => 'textfield',
        '#title' => 'TEST Request URL',
        '#size'=>90,
        '#required'=>TRUE,
        '#description' => t('Enter full url with http://'),
        '#default_value' => isset($configuration->test['request_url']) ? $configuration->test['request_url'] : ''
    );

    $form['carsolize']['test']['login'] = array(
        '#type' => 'textfield',
        '#title' => 'TEST login',
        '#required'=>TRUE,
        '#default_value' => isset($configuration->test['login']) ? $configuration->test['login'] : ''
    );

    $form['carsolize']['test']['password'] = array(
        '#type' => 'textfield',
        '#title' => 'TEST password',
        '#required'=>TRUE,
        '#default_value' => isset($configuration->test['password']) ? $configuration->test['password'] : ''
    );

    $form['carsolize']['real'] = array(
        '#type' => 'fieldset',
        '#title' => t('REAL mode Connection info'),
        '#collapsible' => TRUE,
    );

    $form['carsolize']['real']['request_url'] = array(
        '#type' => 'textfield',
        '#title' => 'Request URL',
        '#size'=>90,
        '#required'=>TRUE,
        '#description' => t('Enter full url with http://'),
        '#default_value' => isset($configuration->real['request_url']) ? $configuration->real['request_url'] : ''
    );

    $form['carsolize']['real']['login'] = array(
        '#type' => 'textfield',
        '#title' => 'REAL login',
        '#required'=>TRUE,
        '#default_value' => isset($configuration->real['login']) ? $configuration->real['login'] : ''
    );

    $form['carsolize']['real']['password'] = array(
        '#type' => 'textfield',
        '#title' => 'REAL password',
        '#required'=>TRUE,
        '#default_value' => isset($configuration->real['password']) ? $configuration->real['password'] : ''
    );


    return system_settings_form($form);
}