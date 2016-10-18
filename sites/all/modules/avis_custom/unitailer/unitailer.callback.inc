<?php
/**
 * Implements payment success page.
 */
function unitailer_payment_success_page() {
  if (count($_POST) && isset($_POST["Order_ID"]) && isset($_POST["Status"]) && isset($_POST["Signature"])) {
    if (checkSignature($_POST["Order_ID"], $_POST["Status"], $_POST["Signature"])) {
      if ($payment = unitailer_get_payment_by_id($_POST["Order_ID"])) {
        module_invoke_all('unitailer_payment', 'success', $payment, $_POST["Status"]);
      }
    }
    else {
    }
  }
  return "<h2>" . t('Thanks. Your payment is successfully!') . "</h2><a href='/" . $GLOBALS['language']->language . "/user' class='form-submit'>" . t('Go to your personal cabinet') . "</a>";
}

/**
 * Implements payment fail page.
 */
function unitailer_payment_fail_page() {
  return t('Payment fail');
}

/**
 * Function for checking signature.
 */
function checkSignature($Order_ID, $Status, $Signature) {
  $password = variable_get('unitailer_pass', '');
  return ($Signature == strtoupper(md5($Order_ID . $Status . $password)));
}
