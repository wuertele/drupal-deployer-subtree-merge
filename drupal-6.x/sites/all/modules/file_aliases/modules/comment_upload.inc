<?php
// $Id$
/**
 * @file
 * Contains Comment Upload module integration for the File Aliases module.
 */

/**
 * Implements hook_comment().
 */
function file_aliases_comment($a1, $op) {
  if ($op == 'view') {
    $node = node_load($a1->nid);
    $a1->type = $node->type;

    if (($ffp = filefield_paths_get_fields($a1, $op)) == FALSE) {
      break;
    }

    foreach ($ffp['#files'] as &$file) {
      if ($ffp['#settings'][$file['name']]['filealias']['display'] == TRUE) {
        $filefield_paths_alias = 'filefield_paths/alias/' . $file['field']['fid'];
        if (($alias = drupal_get_path_alias($filefield_paths_alias)) != $filefield_paths_alias) {
          $a1->comment = str_replace($file['field']['filepath'], $alias, $a1->comment);
        }
      }
    }
  }
}
