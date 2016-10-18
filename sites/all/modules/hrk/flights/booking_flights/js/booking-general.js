(function ($) {
    Drupal.behaviors.booking_general = {
        attach: function (context, settings) {
            $('.form-submit').once(function(){
                $(this).on('click',function(){
                    var $form = $(this).closest('form');
                    if($form.valid()){
                        $('.loading').show();
                    } else {
                        $('.error.tooltipstered').tooltipster('show');
                    }
                });
            });

            $('.show-rules').on('click', function () {
                var $popup_wr = $('.booking-rules-popup');
                var $popup = $popup_wr.find('.popup-bg');
                $popup_wr.show();
                $popup.show();
                return false;
            });
        }
    };


})(jQuery);
