(function($) {

  Number.prototype.format = function(n, x, s, c) {
    var re = '\\d(?=(\\d{' + (x || 3) + '})+' + (n > 0 ? '\\D' : '$') + ')',
      num = this.toFixed(Math.max(0, ~~n));

    return (c ? num.replace('.', c) : num).replace(new RegExp(re, 'g'), '$&' + (s || ','));
  };

  Drupal.ajax.prototype.commands.currency_convert = function (ajax, response, status) {

    var rates = Drupal.settings.currency.rates;
    var active_currency = Drupal.settings.currency.active_currency;
    var new_currency = response.data;
    var rate = rates[new_currency].rate;

    $('.currency__price').each(function(k, e){
      var e = $(e);
      e.removeClass(active_currency).addClass(new_currency);
      var price = rate * e.data('base-price');
      e.text(price.format(0, 3, ' ', ''));
    });

    $('.currency-title-active').text(new_currency);
    $('body').removeClass('currency-' + active_currency).addClass('currency-' + new_currency);
    
  };
})(jQuery);
