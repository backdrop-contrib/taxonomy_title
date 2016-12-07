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
  $config = config('taxonomy_title.settings');
  $heading_defaults = $config->get('headings', array());
  $page_title_defaults = $config->get('page_titles', array());

  $form['settings'] = array(
    '#theme' => 'taxonomy_title_admin_settings',
  );

  $link = theme('token_tree_link', array('text' => 'Browse available tokens', 'token_types' => array('term')));

  foreach ($vocabs as $key => $vocab) {
    $heading_options[$key] = $vocab->name;
    $page_title_options[$key] = $vocab->name;
    if (!isset($heading_defaults[$key])) {
      $heading_defaults[$key] = $key;
    }
    if (!isset($page_title_defaults[$key])) {
      $page_title_defaults[$key] = $key;
    }

    $form['settings']['taxonomy_title_default_' . $key] = array(
      '#type' => 'textfield',
      '#description' => t('Leave blank for none.') . ' ' . $link,
      '#default_value' => $config->get('default_' . $key, ''),
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

      $singular_text = '* Since you have the !modules module enabled, Taxonomy Title will be unable to affect the title tags for your term pages. If you would like term titles to appear in your title tags instead of term names, please configure !modules to use the <code>[term-title]</code> token.';
      $plural_text = '* Since you have the !modules modules enabled, Taxonomy Title will be unable to affect the title tags for your term pages. If you would like term titles to appear in your title tags instead of term names, please configure !modules to use the <code>[term-title]</code> token.';

      $message = format_plural($problematic_modules_count, $singular_text, $plural_text, array('!modules' => $problematic_modules));

      backdrop_set_message($message, 'warning');

    }
  }

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));

  return $form;
}

/**
 * Submit handler for taxonomy_title_settings_form().
 */
function taxonomy_title_settings_form_submit(&$form, &$form_state) {
  $config = config('taxonomy_title.settings');
  $vocabs = taxonomy_get_vocabularies();
  foreach ($vocabs as $key => $vocab) {
    $config->set('default_' . $key, $form_state['values']['taxonomy_title_default_' . $key]);
  }
  $config->set('headings', $form_state['values']['taxonomy_title_headings']);
  $config->set('page_titles', $form_state['values']['taxonomy_title_page_titles']);
  $config->save();
}
