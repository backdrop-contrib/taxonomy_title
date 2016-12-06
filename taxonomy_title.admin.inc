<?php
/**
 * @file
 * Admin pages and forms for the taxonomy title module.
 */

/**
 * Admin settings form.
 */
function taxonomy_title_settings_form($form, &$form_state) {
  $form = array();

  // Get all taxonomy vocabularies.
  $vocabs = taxonomy_get_vocabularies();

  // Set up place holders for options.
  $heading_options = array();
  $page_title_options = array();

  // Set up holders for default values.
  $heading_defaults = variable_get('taxonomy_title_headings', array());
  $page_title_defaults = variable_get('taxonomy_title_page_titles', array());

  $form['settings'] = array(
    '#theme' => 'taxonomy_title_admin_settings',
  );

  $link = theme('token_tree_link', array('text' => 'Browse available tokens', 'token_types' => array('term')));

  foreach ($vocabs as $vid => $vocab) {
    $heading_options[$vid] = $vocab->name;
    $page_title_options[$vid] = $vocab->name;
    if (!isset($heading_defaults[$vid])) {
      $heading_defaults[$vid] = $vid;
    }
    if (!isset($page_title_defaults[$vid])) {
      $page_title_defaults[$vid] = $vid;
    }

    $form['settings']['taxonomy_title_default_' . $vid] = array(
      '#type' => 'textfield',
      '#description' => t('Leave blank for none.') . ' ' . $link,
      '#default_value' => variable_get('taxonomy_title_default_' . $vid, ''),
    );
  }

  $form['settings']['taxonomy_title_headings'] = array(
    '#type' => 'checkboxes',
    '#options' => $heading_options,
    '#default_value' => $heading_defaults,
  );

  if (!module_exists('page_title') && !module_exists('metatag')) {
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

    $problem_module = FALSE;
    if (module_exists('metatag')) {
      $problem_module = 'Metatag';
    }
    elseif (module_exists('page_title')) {
      $problem_module = 'Page Title';
    }
    if ($problem_module) {
      $message = t('* Since you have the !module module enabled, Taxonomy Title will be unable to affect the title tags for your pages.  If you would like term titles to appear in your title tags instead of term names, please configure !module to use the [term-title] token.',
        array('!module' => $problem_module));
      backdrop_set_message($message, 'warning');
    }
  }

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));

  return system_settings_form($form);
}

function taxonomy_title_settings_form_submit() {
}
