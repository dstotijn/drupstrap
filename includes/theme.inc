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

/**
 * Implements template_preprocess_region().
 */
function drupstrap_preprocess_region(&$variables, $hook) {
  if (strpos($variables['region'], 'sidebar_') === 0) {
    $variables['classes_array'][] = 'col-sm-4';
    $variables['classes_array'][] = 'col-md-offset-1';
    $variables['classes_array'] = array_diff($variables['classes_array'],
      array('column', 'sidebar'));
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function drupstrap_preprocess_breadcrumb(&$variables, $hook) {
  $variables['title_attributes_array']['class'][] = 'sr-only';
}

/**
 * Implements theme_breadcrumb().
 */
function drupstrap_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  // Prepare for list output
  foreach ($breadcrumb as &$breadcrumb_item) {
    $breadcrumb_item = '<li>' . $breadcrumb_item . '</li>'; 
  }
  $output = '';

  // Determine if we are to display the breadcrumb.
  $show_breadcrumb = theme_get_setting('zen_breadcrumb');
  if ($show_breadcrumb == 'yes' || $show_breadcrumb == 'admin' && arg(0) == 'admin') {

    // Optionally get rid of the homepage link.
    $show_breadcrumb_home = theme_get_setting('zen_breadcrumb_home');
    if (!$show_breadcrumb_home) {
      array_shift($breadcrumb);
    }

    // Return the breadcrumb with separators.
    if (!empty($breadcrumb)) {
      $breadcrumb_separator = theme_get_setting('zen_breadcrumb_separator');
      $trailing_separator = $title = '';
      if (theme_get_setting('zen_breadcrumb_title')) {
        $item = menu_get_item();
        if (!empty($item['tab_parent'])) {
          // If we are on a non-default tab, use the tab's title.
          $breadcrumb[] = check_plain($item['title']);
        }
        else {
          $breadcrumb[] = drupal_get_title();
        }
      }
      elseif (theme_get_setting('zen_breadcrumb_trailing')) {
        $trailing_separator = $breadcrumb_separator;
      }

      // Provide a navigational heading to give context for breadcrumb links to
      // screen-reader users.
      if (empty($variables['title'])) {
        $variables['title'] = t('You are here');
      }
      // Unless overridden by a preprocess function, make the heading invisible.
      if (!isset($variables['title_attributes_array']['class'])) {
        $variables['title_attributes_array']['class'][] = 'element-invisible';
      }

      // Add 'active' class to last list item
      if (theme_get_setting('zen_breadcrumb_title')) {
        end($breadcrumb);
        $breadcrumb[key($breadcrumb)] = '<li class="active">' . $breadcrumb[key($breadcrumb)] . '</li>';
      }
      $output = '<nav role="navigation">';
      $output .= '<h2' . drupal_attributes($variables['title_attributes_array']) . '>' . $variables['title'] . '</h2>';
      $output .= '<ol class="breadcrumb">' . implode(' ', $breadcrumb) . '</ol>';
      $output .= '</nav>';
    }
  }

  return $output;
}
