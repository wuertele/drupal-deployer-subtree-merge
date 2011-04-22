<?php
// $Id$
/**
 * @file
 * Contains Drupal core Upload module integration for the File Aliases module.
 */

/**
 * Implements file_aliases_hook_process().
 */
function file_aliases_upload_process(&$node, &$file, &$path, &$alias, &$count) {
  $node->content['files']['#value'] = str_replace($file['field']['filepath'], $alias, $node->content['files']['#value']);
}

/**
 * Implements file_aliases_hook_views_handlers().
 */
function file_aliases_upload_views_handlers(&$handlers) {
  $handlers['file_aliases_views_handler_field_upload_fid'] = array(
    'parent' => 'views_handler_field_upload_fid',
  );
}

/**
 * Implements file_aliases_hook_views_data_alter().
 */
function file_aliases_upload_views_data_alter(&$data) {
  $data['node']['upload_fid']['field']['handler'] = 'file_aliases_views_handler_field_upload_fid';
}
