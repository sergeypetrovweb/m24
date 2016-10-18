(function ($) {
    Drupal.behaviors.bf_popup = {
        attach: function (context, settings) {

            var $close = $('.bf-popup .cross-icon');

            $close.once(function(){
                $(this).on('click',function(){
                    $(this).closest('.popup-bg').hide();
                });
            });
        }
    };
})(jQuery);