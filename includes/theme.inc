<?php

/**
 * Implements hook_css_alter().
 */
function drupstrap_css_alter(&$css) {
  $cdn = '//netdna.bootstrapcdn.com/bootstrap/3.0.0/css/bootstrap.min.css';
  $css[$cdn] = array(
    'data' => $cdn,
    'type' => 'external',
    'every_page' => TRUE,
    'media' => 'all',
    'preprocess' => TRUE,
    'group' => CSS_THEME,
    'browsers' => array('IE' => TRUE, '!IE' => TRUE),
    'weight' => -2,
  );
}

/**
 * Implements template_preprocess_html().
 */
function drupstrap_preprocess_html(&$variables, $hook) {
  $viewport = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width, initial-scale=1.0'
    ),
  );
  drupal_add_html_head($viewport, 'bootstrap_viewport');
}
