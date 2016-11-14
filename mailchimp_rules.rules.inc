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
