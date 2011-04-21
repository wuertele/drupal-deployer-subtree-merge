<?php

/**
 * Implementation of hook_content_default_fields().
 */
function amazon_examples_content_default_fields() {
  module_load_include('inc', 'amazon_examples', 'amazon_examples.defaults');
  $args = func_get_args();
  return call_user_func_array('_amazon_examples_content_default_fields', $args);
}

/**
 * Implementation of hook_node_info().
 */
function amazon_examples_node_info() {
  module_load_include('inc', 'amazon_examples', 'amazon_examples.features.node');
  $args = func_get_args();
  return call_user_func_array('_amazon_examples_node_info', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function amazon_examples_views_default_views() {
  module_load_include('inc', 'amazon_examples', 'amazon_examples.features.views');
  $args = func_get_args();
  return call_user_func_array('_amazon_examples_views_default_views', $args);
}
