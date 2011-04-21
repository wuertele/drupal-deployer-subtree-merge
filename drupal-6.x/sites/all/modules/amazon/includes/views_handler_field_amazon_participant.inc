<?php
// $Id$

class views_handler_field_amazon_participant extends views_handler_field_prerender_list {
  function construct() {
    parent::construct();
    $this->additional_fields['asin'] = array('table' => 'amazon_item', 'field' => 'asin');
  }

  /**
   * Provide meaningful defaults
   */
  function options(&$options) {
    parent::options($options);
    $options['participant_type'] = '**ALL**';
  }

  /**
   * Provide "link to term" option.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['participant_type'] = array(
      '#type' => 'select',
      '#title' => t('Participant restriction'),
      '#options' => array(
        '**ALL**' => t('Show all particpants'),
        'author' => 'Author',
        'artist' => 'Artist',
        'actor' => 'Actor',
        'director' => 'Director',
        'creator' => 'Creator'
      ),
      '#default_value' => $this->options['participant_type'],
    );
  }

  function query() {
    $this->add_additional_fields();
  }

  function pre_render($values) {
    $this->field_alias = $this->aliases['asin'];
    $this->items = array();

    $asins = array();
    foreach ($values as $result) {
      if (!empty($result->{$this->aliases['asin']})) {
        $asins[] = $result->{$this->aliases['asin']};
      }
    }

    $sql = "SELECT aip.participant, aip.asin FROM {amazon_item_participant} aip WHERE aip.asin IN ('" . implode("', '", $asins) . "') ";
    if ($this->options['participant_type'] != '**ALL**') {
      $sql .= " AND aip.type = '%s'";
    }
    $results = db_query($sql, $this->options['participant_type']);

    while ($result = db_fetch_array($results)) {
      $this->items[$result['asin']][] = check_plain($result['participant']);
    }
  }
}
