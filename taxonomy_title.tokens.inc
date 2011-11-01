<?php

/**
 * Implementation of hook_token_list().
 */
function taxonomy_title_token_list($type = 'all') {
  if ($type == 'taxonomy' || $type == 'all') {
    $tokens['taxonomy']['term-title'] = t("The term's title, defaults to term name (same as [term]).");
    $tokens['taxonomy']['term-title-raw'] = t("The raw component of the term's title, WARNING - raw user input.");
    return $tokens;
  }
}

/**
 * Implementation of hook_token_values().
 */
function taxonomy_title_token_values($type, $object = NULL, $options = array()) {
  $values = array();
  if ($type == 'taxonomy') {
      $category = $object;
      // Use taxonomy title if it exists, else the category name.
      $title = _taxonomy_title_get($category->tid);
      $values['term-title'] = ($title) ? check_plain($title) : check_plain($category->name);
      $values['term-title-raw'] = ($title) ? $title : $category->name;
  }
  return $values;
}