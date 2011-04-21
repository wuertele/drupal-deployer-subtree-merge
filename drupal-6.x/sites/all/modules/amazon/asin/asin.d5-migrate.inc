<?php
// $Id$

/**
 * Batch Operation Callback
 */
function _asin_migrate_field_from_d5($fields, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;
    
    $sql = "SELECT COUNT(DISTINCT nid) FROM {amazonnode} WHERE ntype IN ";
    $sql .= '(' . db_placeholders($fields, 'varchar') . ')';
    
    $context['sandbox']['max'] = db_result(db_query($sql, array_keys($fields)));
  }
  
  $sql = "SELECT DISTINCT(nid) FROM {amazonnode} WHERE ntype IN (" . db_placeholders($fields, 'varchar') . ") ORDER BY nid ASC";
  $params[] = $context['sandbox']['current_node'];
  $nid_results = db_query_range($sql, array_keys($fields), 0, 20);
  $nids = array();
  while ($nid = db_fetch_object($nid_results)) {
    $nids[] = $nid->nid;
  }

  foreach ($nids as $nid) {
    if ($node = _asin_migrate_from_d5($nid, $fields)) {
      $context['results'][$node->nid] = $node->title;
  
      $context['sandbox']['progress']++;
      $context['sandbox']['current_node'] = $node->nid;
      $context['message'] = t('Now processing %node', array('%node' => $node->title));
    }
  }
  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Batch 'finished' callback
 */
function _asin_migrate_fields_finished($success, $results, $operations) {
  if ($success) {
    // Here we do something meaningful with the results.
    $message = count($results) .' nodes migrated to new ASIN field structure.';
    $message .= theme('item_list', $results);
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = 'An error occurred while processing '. $error_operation[0] .' with arguments :'. print_r($error_operation[0], TRUE);
  }
  drupal_set_message($message);
}

function _asin_migrate_from_d5($nid, $fields) {
  $results = db_query("SELECT asin, ntype FROM {amazonnode} an WHERE an.nid = %d", $nid);
  $dirty = FALSE;
  $node = node_load($nid);

  while ($asin = db_fetch_object($results)) {
    if (array_key_exists($asin->ntype, $fields)) {
      $node->{$asin->ntype}[]['asin'] = $asin->asin;
    }
  }

  node_save($node);
  $sql = "DELETE FROM {amazonnode} WHERE nid = %d AND ntype IN (" . db_placeholders($fields, 'varchar') . ")";
  $params = array_keys($fields);
  array_unshift($params, $nid);
  db_query($sql, $params);

  return $node;
}