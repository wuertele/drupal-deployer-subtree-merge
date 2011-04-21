<?php

/**
 * Helper to implementation of hook_views_default_views().
 */
function _amazon_examples_views_default_views() {
  $views = array();

  // Exported view: amazon_example_view
  $view = new view;
  $view->name = 'amazon_example_view';
  $view->description = 'Amazon Example View';
  $view->tag = 'examples';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'field_asin_asin' => array(
      'label' => 'field_asin_asin',
      'required' => 1,
      'id' => 'field_asin_asin',
      'table' => 'node_data_field_asin',
      'field' => 'field_asin_asin',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'nid' => array(
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
    ),
    'asin' => array(
      'label' => 'ASIN',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'asin',
      'table' => 'amazon_item',
      'field' => 'asin',
      'relationship' => 'field_asin_asin',
    ),
    'title' => array(
      'label' => 'Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_format' => 'plain',
      'exclude' => 0,
      'id' => 'title',
      'table' => 'amazon_item',
      'field' => 'title',
      'relationship' => 'field_asin_asin',
    ),
    'detailpageurl' => array(
      'label' => 'Detail page URL',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'exclude' => 1,
      'id' => 'detailpageurl',
      'table' => 'amazon_item',
      'field' => 'detailpageurl',
      'relationship' => 'field_asin_asin',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'listpriceformattedprice' => array(
      'id' => 'listpriceformattedprice',
      'table' => 'amazon_item',
      'field' => 'listpriceformattedprice',
    ),
    'publisher' => array(
      'id' => 'publisher',
      'table' => 'amazon_item',
      'field' => 'publisher',
    ),
    'publicationdate' => array(
      'label' => 'Publication date',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'date_format' => 'default',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'publicationdate',
      'table' => 'amazon_book',
      'field' => 'publicationdate',
      'relationship' => 'field_asin_asin',
    ),
    'product_image' => array(
      'label' => 'Image URL',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'image_size' => 'mediumimage',
      'link_format' => 'plain',
      'exclude' => 1,
      'id' => 'product_image',
      'table' => 'amazon_item_image',
      'field' => 'product_image',
      'relationship' => 'field_asin_asin',
      'presentation_format' => 'plain_url',
    ),
    'nothing' => array(
      'label' => 'Custom: Example Link to Image',
      'alter' => array(
        'text' => 'Example link/image: <a href="[detailpageurl]"><img src="[product_image]"></a>',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'nothing',
      'table' => 'views',
      'field' => 'nothing',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'amazon_example' => 'amazon_example',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('header', 'This is an example view that you can experiment with. 

If you see no results, it\'s because you have to create some nodes first. Go to Create Content-&gt;Amazon Example and create a node or two. Try using these ASINs: 0596515804, 1430209895, 0470429038.');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 1);
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'asin' => 'asin',
      'nid' => 'nid',
    ),
    'info' => array(
      'asin' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'nid' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'amazon_example_view');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Amazon Example View',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));

  $views[$view->name] = $view;

  return $views;
}
