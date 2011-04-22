<?php 
// $Id$

/**
 * @file
 * Filter handler for "between" and "overlap" operators of MVF.
 */
class mvf_filter_handler extends content_handler_filter_float {
  
  function operators() {
    $operators = parent::operators();
    $operators += array(
      'overlaps' => array(
        'title' => t('Overlaps with'),
        'method' => 'op_overlaps',
        'short' => t('overlap'),
        'values' => 2,
      ),
      'not overlaps' => array(
        'title' => t('Does not overlap with'),
        'method' => 'op_overlaps',
        'short' => t('no overlap'),
        'values' => 2,
      ),
    );
    return $operators;
  }
  
  function op_between($field1) {
    $field2 = $field1 .'2';
    if ($this->operator == 'between') {
      $this->query->add_where($this->options['group'], "$field1 >= %f", $this->value['min']);
      $this->query->add_where($this->options['group'], "$field2 <= %f", $this->value['max']);
    }
    else {
      $this->query->add_where($this->options['group'], "$field1 <= %f OR $field2 >= %f", $this->value['min'], $this->value['max']);
    }
  }
  
  /**
   * "Range overlap" operator for MVF.
   * 
   * Overlapping consists of 2 cases:
   *   1) full overlap: search range fully contains target range 
   *      (range of target node field) , i.e. it's "in between" case
   *   2) partial overlap: atleast one of search edges is within
   *      target range.   
   */
  function op_overlaps($field1) {
    $field2 = $field1 .'2';
    $min = $this->value['min'];
    $max = $this->value['max'];
    $group = $this->options['group'];
    if ($this->operator == 'overlaps') {
      $overlap  = "($field1 >= %f AND $field2 <= %f)"; // Full overlap.
      $overlap .= "OR ($field1 <= %f AND $field2 >= %f)"; // Left edge within.
      $overlap .= "OR ($field1 <= %f AND $field2 >= %f)"; // Right edge within.
      $this->query->add_where($group, $overlap, $min, $max, $min, $min, $max, $max);
    }
    else {
      // "no overlap" is simple case
      $this->query->add_where($group, "$field2 <= %f OR $field1 >= %f", $min, $max);
    }
  }  
}
