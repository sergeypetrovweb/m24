(function ($) {
    Drupal.behaviors.bh = {
        attach: function (context, settings) {

            $('.form-submit').once(function(){
                $(this).on('click',function(){
                    $('.loading').show();
                });
            });

            $('.show_policy').once(function(){
                $('.show_policy').on('click',function(){
                    $('.book-policy-popup, .hotel-rules').show();
                });
            });
        }
    };
})(jQuery);
