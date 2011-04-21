<?php
// $Id$

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
    $this->additional_fields[] = 'asin';
  }

  /**
   * Provide link to node option
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
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
    if (module_exists('amazon_store')) {
      $form['link_format']['#options']['amazon_store'] = t("A link to the product's Amazon Store page (Amazon Store Module)");
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
        return l($title, check_url($values->{$this->table_alias . '_detailpageurl'}), array('html' => TRUE));
        break;
      case 'amazon_store':
        $path = function_exists('amazon_store_get_amazon_store_path') ? amazon_store_get_amazon_store_path() : 'amazon_store';
        $asin = $values->{$this->aliases['asin']};
        return l($title, "$path/item/$asin", array('html' => TRUE));
        break;

    }
  }
}
