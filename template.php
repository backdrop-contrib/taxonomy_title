<?php
/**
 * Override or insert PHPTemplate variables into the templates.
 */
function _phptemplate_variables($hook, $vars) {
  if ($hook == 'page') {
    
    // USE BELOW: FOR TAXONOMY TITLE
    if (arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2)) && arg(2) > 0){
      // taxonomy term page - check for custom page title
      $title = _taxonomy_title_get_title(arg(2));
      if ($title != ''){
         $vars['title'] = $title;
      }
    }
    // USE ABOVE: FOR TAXONOMY TITLE
    
  }
}