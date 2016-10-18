<?php
/**
 * Created by Avis.
 * User: Dima Evseev
 * Date: 26.08.2015
 * Time: 12:52
 */

class Currency
{
  private static $_instance;

  //Базовые настройки модуля.
  //TODO: Рассмотреть возможность вынести в админку.
  private $base_currency = 'EUR';
  public $currency_list = array('EUR', 'RUB', 'USD', 'AZN');
  private $currency_rates;
  private $active_currency;
  private $session;

  public function get_base_currency () {
    return $this->base_currency;
  }

  public static function init()
  {
    if (empty(self::$_instance))
    {
      self::$_instance = new Currency;
    }
    return self::$_instance;
  }

  function __construct()
  {
    session_api_include('system');
    $this->session = SystemSessionApi::init('currency','active');
    $active = $this->session->getSession('currency');

    $this->active_currency = !empty($active) ? $active : strtolower($this->base_currency);




    $this->currency_rates = variable_get('currency_rates', array());
    unset($this->currency_rates['created']);
    drupal_add_js(array('currency' => array(
      'rates' => $this->currency_rates,
      'active_currency' => $this->active_currency,
    )), 'setting');

    ctools_class_add ('currency-' . $this->active_currency);
  }



  public function get_price ($base_price) {
    //получаю конвертированную цену в сыром виде. Нужно для range фильтра по цене в результатах поиска по отелям.
    $price = round($this->convert($base_price, $this->base_currency, $this->active_currency));
    return $price;
  }

  public function get_currency () {
    return $this->active_currency;
  }

  public function price_html ($base_price) {
    $price = $base_price;
    if ($this->base_currency !== $this->active_currency) {
      $price = $this->convert($base_price, $this->base_currency, $this->active_currency);
    }

    return '<span class="currency"><span class="currency__price ' . $this->active_currency . '" data-base-price="' . $base_price . '">'
    . number_format($price, 0, ',', ' ')
    . '</span></span>';
  }

  public function change ($currency)
  {
    if (in_array($currency, $this->currency_list)) {
      $this->session->setSession(array('currency' => strtolower($currency)));
      return $currency;
    }
    return false;
  }

  public function convert($amount, $from, $to = null)
  {
    $converting = $amount;

    $currency_rates = variable_get('currency_rates', array());

    //dsm($currency_rates);

    if ($currency_rates) {
      $from_cur_code = strtolower($from);
      $to_cur_code = strtolower($to);

      $from_rate = isset($currency_rates[$from_cur_code]['rate']) ? $currency_rates[$from_cur_code]['rate'] : 1;
      $to_rate = isset($currency_rates[$to_cur_code]['rate']) ? $currency_rates[$to_cur_code]['rate'] : 1;

      //at first convert to EUR
      $eur = $amount / $from_rate;
      $converting = $eur * $to_rate;
    }
    return $converting;
  }
}