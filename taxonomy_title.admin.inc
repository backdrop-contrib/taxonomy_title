<?php

/**
 * @file
 * Settings form for taxonomy title.
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
    $heading_options[$vid] = $vocab->name;
    $page_title_options[$vid] = $vocab->name;
    if (!isset($heading_defaults[$vid])) {
      $heading_defaults[$vid] = $vid;
    }
    if (!isset($page_title_defaults[$vid])) {
      $page_title_defaults[$vid] = $vid;
    }
  }

  $form['settings'] = array(
    '#theme' => 'taxonomy_title_admin_settings',
  );
  
  $form['settings']['taxonomy_title_headings'] = array(
    '#type' => 'checkboxes',
    '#options' => $heading_options,
    '#default_value' => $heading_defaults,
  );
  
  if (!module_exists('page_title')) {
    $form['settings']['taxonomy_title_page_titles'] = array(
      '#type' => 'checkboxes',
      '#options' => $page_title_options,
      '#default_value' => $page_title_defaults,
    ); 
  }
  else {
    $form['settings']['taxonomy_title_page_titles'] = array(
      '#type' => 'checkboxes',
      '#options' => $page_title_options,
      '#default_value' => array(),
      '#disabled' => TRUE,
    );
    $form['settings']['notice'] = array(
      '#weight' => 2,
      '#value' => '<p>' . t('* Since you have the page title module enabled, this module will be unable 
      to affect the title tags of your pages.  If you would like taxonomy titles to appear in your
      title tags, please configure the page title module using the provided tokens.  Example: [term-title]') . '</p>',
    );
  }
  
  return system_settings_form($form);
}