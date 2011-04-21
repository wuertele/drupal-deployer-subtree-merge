<?php

function amazon_settings_form($form_state) {
  $cache = amazon_data_cache();
  $options = array();
  foreach ($cache['locales'] as $locale => $data) {
    $options[$locale] = $data['name'];
  }
  $form['amazon_locale'] = array(
    '#type' => 'select',
    '#title' => t('Amazon locale'),
    '#default_value' => variable_get('amazon_locale', 'US'),
    '#options' => $options,
    '#description' => t('Amazon.com uses separate product databases and Ecommerce features in different locales; pricing and availability information, as well as product categorization, differs from one locale to the next. Be sure to select the locale your site will be running in.'),
  );

  $form['amazon_associate_setting'] = array(
    '#type' => 'select',
    '#title' => t('Amazon referral settings'),
    '#default_value' => variable_get('amazon_associate_setting', 'association'),
    '#options' => array(
      'association' => t('Use the Drupal Association\'s associate ID'),
      'custom' => t('Use your own associate ID'),
      'none' => t('Do not use any associate ID')
    ),
    '#description' => t('Outgoing links to Amazon.com can include an associate ID code. When shoppers purchase Amazon products via one of those links, the associate ID is used to determine who should receive a referral bonus from Amazon.com.'),
  );

  $form['amazon_custom_associate_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Your associate ID'),
    '#description' => t('Enter your own associate ID to receive referral bonuses when shoppers purchase Amazon products via your site.'),
    '#default_value' => variable_get('amazon_custom_associate_id', ''),
    '#prefix' => '<div id="amazon-associate-id-wrapper">',
    '#suffix' => '</div>',
  );
  if (variable_get('amazon_associate_setting', 'association') != 'custom') {
    $form['amazon_custom_associate_id']['#prefix'] = '<div id="amazon-associate-id-wrapper" class="js-hide">';
  }

  $form['amazon_aws_access_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Amazon AWS Access Key ID'),
    '#description' => t('You must sign up for an Amazon AWS account to use the Product Advertising Service. See !more_info for information and a registration form.',array('!more_info'=>l(t('the AWS home page'),'https://aws-portal.amazon.com/gp/aws/developer/account/index.html?ie=UTF8&action=access-key',array('html'=>TRUE)))),
    '#default_value' => variable_get('amazon_aws_access_key', ''),
    '#required' => TRUE,
  );

  $form['amazon_aws_secret_access_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Amazon AWS Secret Access Key'),
    '#description' => t('You must sign up for an Amazon AWS account to use the Product Advertising Service. See !more_info for information and a registration form.',array('!more_info'=>l(t('the AWS home page'),'https://aws-portal.amazon.com/gp/aws/developer/account/index.html?ie=UTF8&action=access-key',array('html'=>TRUE)))),
    '#default_value' => variable_get('amazon_aws_secret_access_key',""),
    '#required' => TRUE,
  );
  $form['default_image'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default image to use when Amazon does not provide an image'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  if (module_exists('imagecache')) {
    $form['#attributes'] = array('enctype' => "multipart/form-data");
    $default_image = variable_get('amazon_default_image', '');
    if (!empty($default_image)) {
      $preset = variable_get('amazon_default_image_small_preset', '');
      if (!empty($preset)) {
        $themed_image = theme('imagecache', $preset, $default_image, t('Amazon default image'));
      }
      else {
        $themed_image = theme('image', $default_image);
      }
      $form['default_image']['existing_image'] = array(
        '#type' => 'markup',
        '#value' => $themed_image,
      );
    }
    $form['default_image']['amazon_default_image'] = array(
      '#type' => 'file',
      '#title' => t('Default image to be used when no image is available'),
      '#size' => 20,
      '#default_value' => $default_image,
    );

    $imagecache_presets = array('' => t('Select a preset'));
    foreach(imagecache_presets() as $preset) {
      $imagecache_presets[$preset['presetname']] = $preset['presetname'];
    };
    $form['default_image']['amazon_default_image_large_preset'] = array(
      '#title' => 'Imagecache preset for "large" size',
      '#type' => 'select',
      '#options' => $imagecache_presets,
      '#default_value' => variable_get('amazon_default_image_large_preset', ''),
    );
    $form['default_image']['amazon_default_image_medium_preset'] = array(
      '#title' => 'Imagecache preset for "medium" size',
      '#type' => 'select',
      '#options' => $imagecache_presets,
      '#default_value' => variable_get('amazon_default_image_medium_preset', ''),
    );
    $form['default_image']['amazon_default_image_small_preset'] = array(
      '#title' => 'Imagecache preset for "small" size',
      '#type' => 'select',
      '#options' => $imagecache_presets,
      '#default_value' => variable_get('amazon_default_image_small_preset', ''),
    );

  }
  else {
    $form['default_image']['if_imagecache'] = array(
      '#type' => 'markup',
      '#value' => t('If imagecache were installed you could set a default image'),
    );
  }

  // Now add the Javascript that does the fancy hide/show effects.
  drupal_add_js(drupal_get_path('module', 'amazon') .'/amazon.admin.js');

  return system_settings_form($form);
}

/**
 * Validation handler for amazon_settings_form().
 * Handles the file upload and making sure it happens correctly.
 */
function amazon_settings_form_validate($form, &$form_state) {

  if ($file = file_save_upload('amazon_default_image')) {
    $orig_picture = variable_get('amazon_default_image', '');
    if (!empty($orig_picture) && file_exists($orig_picture)) {
      file_delete($orig_picture);
    }

    // The image was saved using file_save_upload() and was added to the
    // files table as a temporary file. We'll make a copy and let the garbage
    // collector delete the original upload.
    $info = image_get_info($file->filepath);
    if (file_copy($file, 0, FILE_EXISTS_REPLACE)) {
      $form_state['values']['amazon_default_image'] = $file->filepath;
    }
    else {
      form_set_error('amazon_default_image', t("Failed to upload the picture image."));
    }
  }
}

/**
 * Form to determine how often cache is refreshed, etc.
 */
function amazon_storage_settings_form() {

  $period = drupal_map_assoc(array(3600, 7200, 14400, 21600, 43200, 86400), 'format_interval');
  $form['details']['amazon_refresh_schedule'] = array(
    '#type' => 'select',
    '#title' => t('Amazon refresh schedule'),
    '#description' => t('Cached information on Amazon items must be refreshed regularly to keep pricing and stock information up to date. Cron must be enabled for this function to work properly.'),
    '#default_value' => variable_get('amazon_refresh_schedule', 86400),
    '#options' => $period
  );

  $form['details']['amazon_core_data'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Store extended product data'),
    '#default_value' => variable_get('amazon_core_data', array('creators', 'images', 'editorial_reviews')),
    '#options' => array(
      'creators' => t('Book authors, film actors, etc.'),
      'images' => t('Product images'),
      'editorial_reviews' => t('Editorial reviews'),
    ),
  );

  // Now add the Javascript that does the fancy hide/show effects.
  drupal_add_js(drupal_get_path('module', 'amazon') .'/amazon.admin.js');

  return system_settings_form($form);
}

/**
 * Form to allow debugging the actual retrieval from Amazon.
 */
function amazon_test_form($form_state) {
  $form = array();

  $form['asin'] = array(
    '#type' => 'textfield',
    '#title' => t('Amazon Product ID'),
    '#description' => t('The ASIN, ISBN-10, or ISBN-13 of a product listed on Amazon.'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Look Up Product'),
  );

  if (isset($form_state['amazon_item'])) {
    $markup = theme('amazon_item', $form_state['amazon_item'], 'details');
    $markup .= '<pre>'. print_r($form_state['amazon_item'], TRUE) .'</pre>';
    $form['item_data'] = array(
      '#type' => 'markup',
      '#value' => $markup,
      '#weight' => 10,
    );
  }
  return $form;
}

function amazon_test_form_submit($form, &$form_state) {
  $asin = $form_state['values']['asin'];
  $asin = amazon_convert_to_asin($asin); // Normalize to an asin. ISBN-13 OK.

  $items = amazon_item_lookup_from_web(array($asin));
  if (!empty($items) && is_array($items)) {
    $item = array_pop($items);
    amazon_item_delete($item['asin']);
    amazon_item_insert($item);

    // We could probably be sneaky and put the Amazon data in here directly,
    // but SimpleXML objects can't be serialized, and setting rebuild = TRUE
    // causes a serialization operation. Whoops.
    $form_state['amazon_item'] = $item;
    $form_state['rebuild'] = TRUE;
  } else {
    drupal_set_message(t("Test failed for this ASIN. Please check the !link for messages.", array('!link' => l(t("error log"), 'admin/reports/dblog'))));
  }
}
