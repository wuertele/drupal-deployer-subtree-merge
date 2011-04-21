<?php

/**
 * Helper to implementation of hook_content_default_fields().
 */
function _amazon_examples_content_default_fields() {
  $fields = array();

  // Exported field: field_asin
  $fields[] = array(
    'field_name' => 'field_asin',
    'type_name' => 'amazon_example',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'asin',
    'required' => '1',
    'multiple' => '0',
    'module' => 'asin',
    'active' => '1',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'asin' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'ASIN',
      'weight' => '-4',
      'description' => 'Enter a 10-digit ASIN that identifies an Amazon item. ',
      'type' => 'asin_text',
      'module' => 'asin',
    ),
  );

  // Translatables
  array(
    t('ASIN'),
  );

  return $fields;
}
