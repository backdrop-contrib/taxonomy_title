<?php

/**
 * @file
 * Settings form for taxonomy title
 */

function taxonomy_title_admin_settings(){
  $form = array();
  
  // Get all taxonomy vocabularies.
  $vocabs = taxonomy_get_vocabularies();
    
  // Set up place holders for options.
  $heading_options = array();
  $page_title_options = array();
  
  // Set up holders for default values.
  $heading_defaults = variable_get('taxonomy_title_headings', array());
  $page_title_defaults = variable_get('taxonomy_title_page_titles', array());
  
  foreach ($vocabs as $vid => $vocab) {
    $heading_options[$vid] = t($vocab->name . ' heading');
    $page_title_options[$vid] = t($vocab->name . ' page title');
    if (!isset($heading_defaults[$vid])) {
      $heading_defaults[$vid] = $vid;
    }
    if (!isset($page_title_defaults[$vid])) {
      $page_title_defaults[$vid] = $vid;
    }
  }
  
  $form['heading_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Please indicate where you would like taxonomy title to affect headings.'),
  );
  
  $form['heading_settings']['taxonomy_title_headings'] = array(
    '#type' => 'checkboxes',
    '#options' => $heading_options,
    '#default_value' => $heading_defaults,
  );
  
  $form['page_title_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Please indicate where you would like taxonomy title to affect page titles.'),
  );
  
  $form['page_title_settings']['taxonomy_title_page_titles'] = array(
    '#type' => 'checkboxes',
    '#options' => $page_title_options,
    '#default_value' => $page_title_defaults,
  );
  
  // Set up a table to gather settings.
  $header = array(t('Vocabulary'), t('Heading tag'), t('Title tag'));
  
  return system_settings_form($form);
}