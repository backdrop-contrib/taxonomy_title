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

    $problematic_modules_known = array('metatag', 'page_title');
    $problematic_modules_found = array();
    // Go through the list of the known problematic modules...
    foreach ($problematic_modules_known as $module) {
      // ...and check if they are enabled.
      if (module_exists($module)) {
        // If found, get their human-readable name...
        $module_info = system_get_info('module', $module);
        // ...and store it in a list of found enabled problematic modules.
        $problematic_modules_found[] = $module_info['name'];
      }
    }

    $problematic_modules_count = count($problematic_modules_found);

    if ($problematic_modules_count != 0) {

      if ($problematic_modules_count == 1) {
        $problematic_modules = $problematic_modules_found[0];
      }
      else {
        $all_but_last_module = array_slice($problematic_modules_found, 0, $problematic_modules_count - 1);
        $problematic_modules = implode(', ', $all_but_last_module) . t('and') . end($problematic_modules_found);
      }

      $module_text = format_plural($problematic_modules_count, 'module', 'modules');

      $message = t('* Since you have the !modules !module_text enabled, Taxonomy Title will be unable to affect the title tags for your pages. If you would like term titles to appear in your title tags instead of term names, please configure !modules to use the <code>[term-title]</code> token.',
        array('!modules' => $problematic_modules, '!module_text' => $module_text));

      backdrop_set_message($message, 'warning');

    }
  }

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));

  return system_settings_form($form);
}

function taxonomy_title_settings_form_submit() {
}
