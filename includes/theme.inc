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

/**
 * Implements template_preprocess_node().
 */
function drupstrap_preprocess_node(&$variables) {
  if ($variables['display_submitted']) {
    $variables['submitted'] = t('!datetime', array(
      '!datetime' => $variables['date'],
    ));
  }
}

/**
 * Implements theme_menu_local_tasks().
 */
function drupstrap_menu_local_tasks(&$variables) {
  $output = '';

  if (!empty($variables['primary'])) {
    $variables['primary']['#prefix'] = '<h2 class="sr-only">' . t('Primary tabs') . '</h2>';
    $variables['primary']['#prefix'] .= '<ul class="nav nav-tabs">';
    $variables['primary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['primary']);
  }
  if (!empty($variables['secondary'])) {
    $variables['secondary']['#prefix'] = '<h2 class="sr-only">' . t('Secondary tabs') . '</h2>';
    $variables['secondary']['#prefix'] .= '<ul class="nav nav-pills">';
    $variables['secondary']['#suffix'] = '</ul>';
    $output .= drupal_render($variables['secondary']);
  }

  return $output;
}

/**
 * Implements theme_menu_local_task().
 */
function drupstrap_menu_local_task($variables) {
  $type = $class = FALSE;

  $link = $variables['element']['#link'];
  $link_text = $link['title'];

  // Check for tab type set in zen_menu_local_tasks().
  if (is_array($variables['element']['#theme'])) {
    $type = in_array('menu_local_task__secondary', $variables['element']['#theme']) ? 'tabs-secondary' : 'tabs-primary';
  }

  // Add SMACSS-style class names.
  if ($type) {
    $link['localized_options']['attributes']['class'][] = $type . '__tab-link';
    $class = $type . '__tab';
  }

  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = ' <span class="sr-only">' . t('(active tab)') . '</span>';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));

    if (!$type) {
      $class = 'active';
    }
    else {
      $link['localized_options']['attributes']['class'][] = 'is-active';
      $class .= ' is-active';
    }
  }

  return '<li' . ($class ? ' class="' . $class . '"' : '') . '>' . l($link_text, $link['href'], $link['localized_options']) . "</li>\n";
}

/**
 * Implements theme_status_messages().
 */
function drupstrap_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  // Match Drupal message types with Bootstrap message types
  $bs_type = array(
    'status' => 'info',
    'warning' => 'warning',
    'error' => 'danger',
  );

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    $output .= "<div class=\"alert alert-$bs_type[$type]\">\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="sr-only">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul class=\"messages__list\">\n";
      foreach ($messages as $message) {
        $output .= '  <li class=\"messages__item\">' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Implements hook_preprocess_HOOK().
 */
function drupstrap_preprocess_table(&$variables, $hook) {
  $variables['attributes']['class'][] = 'table';
}
