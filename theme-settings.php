<?php
/**
 * Implements hook_form_system_theme_settings_alter() function.
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
function drupstrap_form_system_theme_settings_alter(&$form, $form_state, $form_id = NULL) {
  // Work-around for a core bug affecting admin themes. See issue #943212.
  if (isset($form_id)) {
    return;
  }

  // Create the form using Forms API
  $form['grid'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Bootstrap grid settings'),
  );
  $form['grid']['grid_options'] = array(
    '#type' => 'container',
    '#states' => array(
      'invisible' => array(
        ':input[name="drupstrap_grid"]' => array('value' => 'no'),
      ),
    ),
  );
  $form['grid']['grid_options']['drupstrap_sidebar_first_span'] = array(
    '#type'          => 'select',
    '#title'         => t('First sidebar column width'),
    '#description'   => t('Select the Bootstrap column width for the first sidebar.'),
    '#default_value' => theme_get_setting('drupstrap_sidebar_first_span'),
    '#options'       => array(
                          '1'   => 1,
                          '2'   => 2,
                          '3'   => 3,
                          '4'   => 4,
                          '5'   => 5,
                          '6'   => 6,
                          '7'   => 7,
                          '8'   => 8,
                          '9'   => 9,
                          '10'   => 10,
                          '11'   => 11,
                          '12'   => 12,
                        ),
  );
  $form['grid']['grid_options']['drupstrap_sidebar_second_span'] = array(
    '#type'          => 'select',
    '#title'         => t('Second sidebar column width'),
    '#description'   => t('Select the Bootstrap column width for the second sidebar.'),
    '#default_value' => theme_get_setting('drupstrap_sidebar_second_span'),
    '#options'       => array(
                          '1'   => 1,
                          '2'   => 2,
                          '3'   => 3,
                          '4'   => 4,
                          '5'   => 5,
                          '6'   => 6,
                          '7'   => 7,
                          '8'   => 8,
                          '9'   => 9,
                          '10'   => 10,
                          '11'   => 11,
                          '12'   => 12,
                        ),
  );
}
