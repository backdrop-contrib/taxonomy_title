<?php
/**
 * @file
 * Theme functions for the taxonomy title module.
 */

/**
 * Theme function for admin form, turns it into a table.
 */
function theme_taxonomy_title_admin_settings($variables) {
  $form = $variables['form'];

  if (!module_exists('page_title') && !module_exists('metatag')) {
    $title_head = t('Affect title tag');
  }
  else {
    $title_head = t('Affect title tag *');
  }

  $header = array(
    t('Vocabulary for terms'),
    t('Global default value'),
    array('data' => t('Affect Heading tag'), 'class' => 'checkbox'),
    array('data' => $title_head, 'class' => 'checkbox'),
  );

  $rows = array();

  foreach($form['taxonomy_title_page_titles']['#options'] as $key => $name) {
    $row = array();
    $row[] = check_plain($name);
    $row[] = backdrop_render($form['taxonomy_title_default_' . $key]);
    unset($form['taxonomy_title_headings'][$key]['#title']);
    $row[] = array('data' => backdrop_render($form['taxonomy_title_headings'][$key]), 'class' => 'checkbox');
    unset($form['taxonomy_title_page_titles'][$key]['#title']);
    $row[] = array('data' => backdrop_render($form['taxonomy_title_page_titles'][$key]), 'class' => 'checkbox');

    $rows[] = $row;
  }

  // Add a row with screenshots.
  $heading_path = backdrop_get_path('module', 'taxonomy_title') . '/images/' . 'heading.png';
  $heading_example = theme('image', array('uri' => $heading_path));

  $title_path = backdrop_get_path('module', 'taxonomy_title') . '/images/' . 'title.png';
  $title_example = theme('image', array('uri' => $title_path));

  $rows[] = array(
    t('Example'),
    array('data' => ''),
    array('data' => $heading_example, 'class' => 'checkbox'),
    array('data' => $title_example, 'class' => 'checkbox'),
  );

  // Create the table inside the form.
  $form['settings'] = array(
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows)),
    '#weight' => -1,
  );

  $form['#sorted'] = FALSE;

  return backdrop_render_children($form);
}
