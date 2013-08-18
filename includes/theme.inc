<?php
/*
 * Custom theme functions
 *
 */

/**
 * Implements hook_css_alter().
 */
function drupstrap_css_alter(&$css) {
  $cdn = '//netdna.bootstrapcdn.com/bootstrap/3.0.0-rc2/css/bootstrap.min.css';
  $css[$cdn] = array(
    'data' => $cdn,
    'type' => 'external',
    'every_page' => TRUE,
    'media' => 'all',
    'group' => CSS_THEME,
  );
}
