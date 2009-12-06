<?php
// $Id$

/**
 * @file
 * API documentation for Mollom module.
 */

/**
 * Return information about forms that can be protected by Mollom.
 *
 * Mollom invokes this hook for all modules to gather information about forms
 * that can be protected. Only forms that have been registered via this hook are
 * configurable in Mollom's administration interface.
 *
 * @return
 *   An associative array containing information about forms that can be
 *   protected. Each key is a $form_id whose value is an associative array:
 *   - title: The human-readable name of the form.
 *   - mode: (optional) The default protection mode for the form, which can be
 *     one of:
 *     - MOLLOM_MODE_DISABLED: No protection.
 *     - MOLLOM_MODE_CAPTCHA: CAPTCHA-only protection.
 *     - MOLLOM_MODE_ANALYSIS: Text analysis of submitted form values with
 *       fallback to CAPTCHA.
 *     If omitted, the form will not be configured upon installation of Mollom
 *     module.
 *   - bypass access: (optional) A list of user permissions to check for the
 *     current user to determine whether to protect the form with Mollom or do
 *     not validate submitted form values. If the current user has at least one
 *     of the listed permissions, the form will not be protected.
 *   - entity: (optional) The internal name of the entity type the form is for,
 *     e.g. 'node' or 'comment'. This is required for all forms that will store
 *     the submitted content persistently. It is only optional for forms that do
 *     not permanently store the submitted form values, such as contact forms
 *     that only send an e-mail, but do not store it in the database.
 *     Note that forms that specify 'entity' also need to specify 'post_id' in
 *     the 'mapping' (see below).
 *   - elements: (optional) An associative array of elements in the form that
 *     can be configured for Mollom's text analysis. The site administrator can
 *     only select the form elements to process (and exclude certain elements)
 *     when a form registers elements. Each key is a form API element #parents
 *     string representation of the location of an element in the form. For
 *     example, a key of "myelement" denotes a form element value on the
 *     top-level of submitted form values. For nested elements, a key of
 *     "parent][child" denotes that the value of 'child' is found below 'parent'
 *     in the submitted form values. Each value contains the form element label.
 *     If omitted, Mollom can only provide a CAPTCHA protection for the form.
 *   - mapping: (optional) An associative array to explicitly map form elements
 *     (that have been specified in 'elements') to the data structure that is
 *     sent to Mollom for validation. The submitted form values of all mapped
 *     elements are not used for the post's body, so Mollom can validate certain
 *     values individually (such as the author's e-mail address). None of the
 *     mappings are required, but most implementations most likely want to at
 *     least denote the form element that contains the title of a post.
 *     The following mappings are possible:
 *     - post_id: The form element value that denotes the ID of the content
 *       stored in the database.
 *     - post_title: The form element value that should be used as title.
 *     - post_body: Mollom automatically assigns this property based on all
 *       elements that have been selected for textual analysis in Mollom's
 *       administrative form configuration.
 *     - author_name: The form element value that should be used as author name.
 *     - author_mail: The form element value that should be used as the author's
 *       e-mail address.
 *     - author_url: The form element value that should be used as the author's
 *       homepage.
 *     - author_id: The form element value that should be used as the author's
 *       user uid.
 *     - author_openid: Mollom automatically assigns this property based on
 *       'author_id', if no explicit form element value mapping was specified.
 *     - author_ip: Mollom automatically assigns the user's IP address if no
 *       explicit form element value mapping was specified.
 */
function hook_mollom_form_info() {
  // Mymodule's comment form.
  $forms['mymodule_comment_form'] = array(
    'title' => t('Comment form'),
    'mode' => MOLLOM_MODE_ANALYSIS,
    'bypass access' => array('administer comments'),
    'entity' => 'comment',
    'elements' => array(
      'subject' => t('Subject'),
      'body' => t('Body'),
    ),
    'mapping' => array(
      'post_id' => 'cid',
      'post_title' => 'subject',
      'author_name' => 'name',
      'author_mail' => 'mail',
      'author_url' => 'homepage',
    ),
  );
  // Mymodule's user registration form.
  $forms['mymodule_user_register'] = array(
    'title' => t('User registration form'),
    'mode' => MOLLOM_MODE_CAPTCHA,
    'entity' => 'user',
    'mapping' => array(
      'post_id' => 'uid',
      'author_name' => 'name',
      'author_mail' => 'mail',
    ),
  );

  return $forms;
}

/**
 * Alter registered information about forms that can be protected by Mollom.
 *
 * @param &$form_info
 *   An associative array containing protectable forms. See
 *   hook_mollom_form_info() for details.
 */
function hook_mollom_form_info_alter(&$form_info) {
  if (isset($form_info['comment_form'])) {
    $form_info['comment_form']['elements']['mymodule_field'] = t('My additional field');
  }
}

