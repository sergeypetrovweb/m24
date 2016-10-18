(function ($) {
    $(document).ready(function () {
        if ($('.form-item-pay-from-bonus').length) {
            var bonusfield = $('.form-item-summ-pay-from-bonus');
            var pricefield = $('.price-wrapper .total-price .currency__price');
            var afterprice = $('.price-wrapper .after-price');
            var afterpricebonus = $('.price-wrapper .after-price-bonus');
            var oldprice = parseInt(pricefield.text().replace(' ', ''));
            bonusfield.find('input').numeric(",");

            $('#edit-pay-from-bonus').on('change', function () {
                if ($(this).prop('checked') == true) {
                    bonusfield.slideDown("slow");
                    var bonusvalue = parseFloat(bonusfield.find('input').val()).toFixed(2);
                    if (isNaN(bonusvalue)) {
                        bonusvalue = 0;
                    }
                    pricefield.text(oldprice - bonusvalue);
                    afterprice.hide();
                    afterpricebonus.show();
                } else {
                    bonusfield.slideUp("slow");
                    pricefield.text(Math.ceil(pricefield.attr('data-base-price')));
                    afterprice.show();
                    afterpricebonus.hide();
                }
            });

            bonusfield.find('input').on('input', function () {
                if (parseFloat($(this).val()) > parseFloat($(this).attr('data-max-val'))) {
                    $(this).val($(this).attr('data-max-val'));
                }
                var bonusvalue = parseFloat($(this).val()).toFixed(2);
                if (isNaN(bonusvalue)) {
                    bonusvalue = 0;
                }
                pricefield.text(oldprice - bonusvalue);
            });
        }

        if ($('.page-control-bonus').length) {
            $('input[data-type="numeric"]').numeric();
        }
    });
})(jQuery);