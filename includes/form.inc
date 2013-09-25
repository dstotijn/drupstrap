<?php

/**
 * Implements hook_form_alter().
 */
function drupstrap_form_alter(&$form, &$form_state, $form_id) {
  $form['#attributes']['role'][] = 'form';
}

/**
 * Implements theme_form_element().
 */
function drupstrap_form_element($variables) {
  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-group');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="help-block">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * Implements hook_preprocess_HOOK().
 */
function drupstrap_preprocess_textfield(&$variables) {
  $element = &$variables['element'];
  $element['#attributes']['class'][] = 'form-control';
}

/**
 * Implements hook_preprocess_HOOK().
 */
function drupstrap_preprocess_textarea(&$variables) {
  $element = &$variables['element'];
  $element['#attributes']['class'][] = 'form-control';
}

/**
 * Implements hook_preprocess_HOOK().
 */
function drupstrap_preprocess_password(&$variables) {
  $element = &$variables['element'];
  $element['#attributes']['class'][] = 'form-control';
}

/**
 * Implements hook_preprocess_HOOK().
 */
function drupstrap_preprocess_button(&$variables) {
  $element = &$variables['element'];
  $el_style = t($element['#value']);

  $bs_type = array(
    t('Save') => 'btn-primary',
    t('Create') => 'btn-primary',
    t('Update') => 'btn-primary',
    t('Execute') => 'btn-primary',
    t('Switch') => 'btn-primary',
    t('Run') => 'btn-primary',
    t('Log in') => 'btn-primary',
    t('Filter') => 'btn-info',
    t('Add') => 'btn-info',
    t('Upload') => 'btn-info',
    t('Delete') => 'btn-danger',
  );

  if (strpos($el_style, t('Save')) !== false) $el_style = t('Save');
  if (strpos($el_style, t('Create')) !== false) $el_style = t('Create');
  if (strpos($el_style, t('Run')) !== false) $el_style = t('Run');

  if (array_key_exists($el_style, $bs_type)) {
    $button_style = $bs_type[$el_style];
  } else {
    $button_style = 'btn-default';
  }
  $element['#attributes']['class'][] = 'btn';
  $element['#attributes']['class'][] = $button_style;
}

/**
 * Implements theme_button().
 */
function drupstrap_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];

  return '<button' . drupal_attributes($element['#attributes']) . ' />' . check_plain($element['#value']) . '</button>' . "\n";
}
