<?php
// $Id$
/**
 * @file
 * Contains FileField module integration for the File Aliases module.
 */

/**
 * Implements file_aliases_hook_process().
 */
function file_aliases_filefield_process(&$node, &$file, &$path, &$alias, &$count) {
  $count[$file['name']] = isset($count[$file['name']]) ? $count[$file['name']] + 1 : 1;
  $target = &$node->content[$file['name']]['field']['items'][$count[$file['name']] - 1]['#item'];

  $target['origpath'] = $file['field']['filepath'];
  $target['filepath'] = $path . $alias;
  $target['filename'] = array_pop(explode('/', $alias));
}

/**
 * Implements file_aliases_hook_views_handlers().
 */
function file_aliases_filefield_views_handlers(&$handlers) {
  $handlers['file_aliases_content_handler_field_multiple'] = array(
    'parent' => 'file_aliases_content_handler_field',
  );
  $handlers['file_aliases_content_handler_field'] = array(
    'parent' => 'content_handler_field',
  );
}

/**
 * Implements file_aliases_hook_views_data_alter().
 */
function file_aliases_filefield_views_data_alter(&$data) {
  foreach (content_fields() as $field) {
    if ($field['module'] == 'filefield' && isset($data['node_data_' . $field['field_name']])) {
      $data['node_data_' . $field['field_name']][$field['field_name'] . '_fid']['field']['handler'] = 'file_aliases_content_handler_field_multiple';
    }
  }
}

/**
 * Implements hook_theme_registry_alter().
 */
function file_aliases_theme_registry_alter(&$theme_registry) {
  $theme_registry['imagefield_image']['theme path'] = drupal_get_path('module', 'file_aliases');
  $theme_registry['imagefield_image']['function'] = 'theme_file_aliases_imagefield_image';
  $theme_registry['imagefield_image']['theme paths'][0] = drupal_get_path('module', 'file_aliases');
}

/**
 * Modified version of theme_imagefield_image().
 */
function theme_file_aliases_imagefield_image($file, $alt = '', $title = '', $attributes = NULL, $getsize = TRUE) {
  $file = (array)$file;

  if (isset($file['origpath'])) {
    $file['alias'] = $file['filepath'];
    $file['filepath'] = $file['origpath'];
  }

  if (!file_exists($file['filepath'])) {
    return '<!-- File not found: ' . $file['filepath'] . ' -->';
  }

  if ($getsize && (list($width, $height, $type, $image_attributes) = @getimagesize($file['filepath']))) {
    $attributes['width'] = $width;
    $attributes['height'] = $height;
  }

  if (!empty($title)) {
    $attributes['title'] = $title;
  }

  // Alt text should be added even if it is an empty string.
  $attributes['alt'] = $alt;

  // Add a timestamp to the URL to ensure it is immediately updated after editing.
  $query_string = '';
  if (isset($file['timestamp'])) {
    $query_character = (variable_get('file_downloads', FILE_DOWNLOADS_PUBLIC) == FILE_DOWNLOADS_PRIVATE && variable_get('clean_url', '0') == '0') ? '&' : '?';
    $query_string = $query_character . $file['timestamp'];
  }

  $url = file_create_url(isset($file['alias']) ? $file['alias'] : $file['filepath']) . $query_string;
  $attributes['src'] = $url;
  $attributes = drupal_attributes($attributes);
  return '<img ' . $attributes . ' />';
}

/**
 * Implements CCK's hook_field($op = 'sanitize').
 */
function file_aliases_filefield_field($op, $node, $field, &$items, $teaser, $page) {
  if ($op == 'sanitize') {
    foreach ($items as $delta => $item) {
      // Cleanup $items during node preview.
      if (empty($item['fid']) || !empty($item['delete'])) {
        // Check for default images at the widget level.
        // TODO: Provide an API to ImageField to do this itself?
        if (!empty($field['widget']['use_default_image']) && !empty($field['widget']['default_image']['filepath'])) {
          $items[$delta] = $field['widget']['default_image'];
          $items[$delta]['default'] = TRUE;
        }
        else {
          $items[$delta] = NULL;
          continue;
        }
      }
      // Load the complete file if a filepath is not available.
      if (!empty($item['fid']) && empty($item['filepath'])) {
        $items[$delta] = array_merge($item, field_file_load($item['fid']));
      }
      // Add nid so formatters can create a link to the node.
      $items[$delta]['nid'] = $node->nid;

      // Calculate relative path.
      $path = (variable_get('file_downloads', FILE_DOWNLOADS_PUBLIC) == FILE_DOWNLOADS_PUBLIC) ? '' : base_path();
      foreach (explode('/', file_directory_path()) as $dir) {
        $path .= '../';
      }

      if (($alias = drupal_get_path_alias('filefield_paths/alias/' . $items[$delta]['fid'])) !== 'filefield_paths/alias/' . $items[$delta]['fid'] && _file_aliases_display_alias($field['type_name'], $field['field_name'])) {
        $items[$delta]['origpath'] = $items[$delta]['filepath'];
        $items[$delta]['filepath'] = file_directory_path() . '/' . $path . $alias;
      }

      // TODO: This is only necessary for Views, which doesn't call the "load"
      // $op. It might be preferable to move this to Views integration somehow.
      if (!empty($items['data']) && is_string($items[$delta]['data'])) {
        $item['data'] = unserialize($item['data']);
      }
      // Temporary fix to unserialize data serialized multiple times.
      // See the FileField issue http://drupal.org/node/402860.
      // And the CCK issue http://drupal.org/node/407446.
      while (!empty($items[$delta]['data']) && is_string($items[$delta]['data'])) {
        $items[$delta]['data'] = unserialize($items[$delta]['data']);
      }

      // Verify the file exists on the server.
      if (!empty($item['filepath']) && !file_exists($item['filepath'])) {
        watchdog('filefield', 'FileField was trying to display the file %file, but it does not exist.', array('%file' => $item['filepath']));
      }
    }
  }
}
