<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _amazon_examples_node_info() {
  $items = array(
    'amazon_example' => array(
      'name' => t('Amazon Example'),
      'module' => 'features',
      'description' => t('This is just an example content type to show how Amazon module can be used with CCK fields. A single CCK field is provided. You can populate a few nodes and then see how views work and how these are displayed.  A sample view that uses this CCK type is provided.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
