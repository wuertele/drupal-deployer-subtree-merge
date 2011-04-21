<?php
// $Id$

/**
 Filter node-linked amazom products by source module
 */
class views_handler_filter_amazon_node_module extends views_handler_filter_in_operator {
  function construct() {
    parent::construct();
    $this->value_title = t('Source module');
    $options = array();
    $result = db_query("SELECT DISTINCT ain.module FROM {amazon_item_node} ain");
    while ($module = db_fetch_array($result)) {
      $options[$module['module']] = $module['module'];
    }
    $this->value_options = $options;
  }

  function options(&$options) {
    parent::options($options);
    $result = db_query("SELECT DISTINCT ain.module FROM {amazon_item_node} ain");
    $module = db_fetch_array($result);
    $options['value'] = array($module['module']);
  }
}

class views_handler_field_amazon_title extends views_handler_field {
  function options(&$options) {
    parent::options($options);
    $options['link_format'] = 'amazon';
  }

  /**
   * Override init function to provide generic option to link to node.
   */
  function init(&$view, &$data) {
    parent::init($view, $data);
    if (!empty($data['link_format']) && $data['link_format'] == 'amazon') {
      $this->additional_fields[] = 'detailpageurl';
    }
  }

  /**
   * Provide link to node option
   */
  function options_form(&$form, &$form_state) {
    $form['link_format'] = array(
      '#title' => t('Link behavior'),
      '#type' => 'radios',
      '#options' => array(
        'plain' => t('No link'),
        'amazon' => t("A link to the product's Amazon page"),
      ),
      '#default_value' => !empty($this->options['link_format']) ? $this->options['link_format'] : 'plain',
    );
    if ($this->view->base_table == 'node') {
      $form['link_format']['#options']['node'] = t('A link to the node the product is associated with');
    }
  }

  function render($values) {
    $title = check_plain($values->{$this->field_alias});
    switch($this->options['link_format']) {
      case 'plain':
        return $title;
        break;
      case 'node':
        return l($title, 'node/'. $values->nid, array('html' => TRUE));
        break;
      case 'amazon':
        return l($title, check_url($values->{$this->table_alias . '_detailpageurl'}), array('html' => TRUE, 'attributes' => array('rel' => 'nofollow')));
        break;
    }
  }
}
