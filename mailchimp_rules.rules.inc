<?php

/**
 * @file
 * Rules integration for the mailchimp_rules module.
 */

/**
 * Implements hook_rules_action_info().
 */
function mailchimp_rules_rules_action_info() {
  $items = array();

  $items['mailchimp_rules_mail_subscribe'] = array(
    'label' => t('Subscribe a mail to a MailChimp list'),
    'parameter' => array(
      'list' => array(
        'type' => 'text',
        'label' => t('MailChimp list'),
        'description' => t('Select an existing MailChimp list from your account'),
        'options list' => 'mailchimp_rules_list_names',
      ),
      'mail' => array(
        'type' => 'text',
        'label' => t('Mail address'),
        'description' => t('The mail address to subscribe to the list'),
        'default mode' => 'selector',
      ),
    ),
    'group' => t('MailChimp Rules'),
    'base' => 'mailchimp_rules_rules_action_mail_subscribe_list',
  );

  $items['mailchimp_rules_mail_unsubscribe'] = array(
    'label' => t('Unsubscribe a mail to a MailChimp list'),
    'parameter' => array(
      'list' => array(
        'type' => 'text',
        'label' => t('MailChimp list'),
        'description' => t('Select an existing MailChimp list from your account'),
        'options list' => 'mailchimp_rules_list_names',
      ),
      'mail' => array(
        'type' => 'text',
        'label' => t('Mail address'),
        'description' => t('The mail address to subscribe to the list'),
        'default mode' => 'selector',
      ),
    ),
    'group' => t('MailChimp Rules'),
    'base' => 'mailchimp_rules_rules_action_mail_unsubscribe_list',
  );

  $items['mailchimp_rules_user_subscribe'] = array(
    'label' => t('Subscribe a user to a MailChimp list'),
    'parameter' => array(
      'list' => array(
        'type' => 'text',
        'label' => t('MailChimp list'),
        'description' => t('Select an existing MailChimp list from your account'),
        'options list' => 'mailchimp_rules_list_names',
      ),
      'user' => array(
        'type' => 'user',
        'label' => t('User'),
        'description' => t('The user which should subscribe to the list'),
        'default mode' => 'selector',
      ),
      'merge_fields' => array(
        'type' => 'list<text>',
        'label' => t('Merge fields'),
        'description' => t("For each line you can enter a merge field in the form of 'merge_field': '[replacement_pattern]'. You can view the merge field tags in the settings for the selected list."),
        'restriction' => 'input',
      ),
    ),
    'optional' => TRUE,
    'group' => t('MailChimp Rules'),
    'base' => 'mailchimp_rules_rules_action_user_subscribe_list',
  );

  return $items;
}

/**
 * Returns all the available MailChimp lists for the rules.
 */
function mailchimp_rules_list_names(RulesPlugin $element, $param_name) {
  return mailchimp_rules_retrieve_lists();
}

/**
 * Callback to subscribe an email address to a MailChimp list.
 */
function mailchimp_rules_rules_action_mail_subscribe_list($list, $mail) {
  mailchimp_rules_subscribe_mail($list, $mail);
}

/**
 * Callback to unsubscribe an email address from a MailChimp list.
 */
function mailchimp_rules_rules_action_mail_unsubscribe_list($list, $mail) {
  mailchimp_rules_unsubscribe_mail($list, $mail);
}

/**
 * Callback to subscribe an user to a MailChimp list.
 */
function mailchimp_rules_rules_action_user_subscribe_list($list, $user, $merge_fields) {
  $fields = array();
  foreach ($merge_fields as $line) {
    if (!empty($line)) {
      $parts = array();
      // Fields should have to json like format 'key': 'value' where, the key is
      // the merge field tag/name and value is the value the should be used for
      // the merge key. Ignore any spaces around the apostrophes.
      preg_match("/^\s*'(.*)':\s*'(.*)'\s*$/", $line, $parts);

      // Save the merge field only if we have a key and a value.
      if (count($parts) == 3) {
        $fields[$parts[1]] = $parts[2];
      }
    }
  }

  mailchimp_rules_subscribe_mail($list, $user->mail, $fields, FALSE);
}
