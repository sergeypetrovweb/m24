(function ($) {
    Drupal.behaviors.booking_lcc = {
        attach: function (context, settings) {
            var last_price = 0;
            $('input.lcc-bags').on('change', function () {
                var bag_price = $(this).val();
//                var price = $('.hidden-price').val();
//                var commission = $('.hidden-commission').val();
                var $bags = $('.hidden-bags');
                $bags.val(bag_price);

                var total_price = $('.total-price span.currency__price');
                total_price.html(parseInt(total_price.text().replace(/ /g, ""))/* + parseInt(commission)*/ + parseInt(bag_price) + parseInt(-1 * last_price));
                last_price = bag_price;
            });
        }
    };
})(jQuery);
