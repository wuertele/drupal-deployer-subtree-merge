<?php
// $Id$
/**
 * @file
 * Migration for the amazonnode and related item links from D5 amazontools.
 */

/**
 * Batch Operation Callback
 */
function _aat_legacy_migrate_field_from_d5($item, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;

    if ($node = _aat_legacy_migrate_from_d5($item['nid'], $item['ntype'])) {
      $context['results'][$node->nid] = $node->title;

      $context['sandbox']['progress']++;
      $context['sandbox']['current_node'] = $node->nid;
      $context['message'] = t('Processing nid <a href="!url">%nid</a>, %title', array('!url' => url("node/$node->nid"), '%nid' => $node->nid, '%title' => $node->title));
    }
  }
}
/**
 * Batch 'finished' callback
 */
function _aat_legacy_migrate_fields_finished($success, $results, $operations) {
  if ($success) {
    $message = t('%count legacy fields (amazonnodes and links) were imported.', array('%count' => count($results)));
    $message .= theme('item_list', $results);
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %op.  with arguments = %args.', array('%op' => $error_operation[0], '%args' => print_r($error_operation[0], TRUE)));
  }
  drupal_set_message($message);
}

/**
 * Process one node.
 * @param $nid
 *   The nid to which we are to add values.
 * @param $type
 *   The ntype field from amazonnode table: the content type we're working with.
 * @return
 *   the updated node.
 */
function _aat_legacy_migrate_from_d5($nid, $type) {
  $results = db_query("SELECT asin, ntype FROM {amazonnode} an WHERE an.nid = %d and an.ntype = '%s'", $nid, $type);
  $dirty = FALSE;
  $node = node_load($nid);

  while ($asin = db_fetch_object($results)) {
    // if (!in_array($asin->asin, array_keys(array_values($node->field_legacy_asin)))) {
    $node->field_legacy_asin[]['asin'] = $asin->asin;
    // }
  }
  node_save($node);
  $sql = "DELETE FROM {amazonnode} WHERE nid = %d AND ntype = '%s'";
  db_query($sql, $nid, $type);

  return $node;
}