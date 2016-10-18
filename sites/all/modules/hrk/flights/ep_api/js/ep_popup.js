(function ($) {
    Drupal.behaviors.ep_popup = {
        attach: function (context, settings) {

            var $close = $('.ep-popup .cross-icon');

            $close.once(function(){
                $(this).on('click',function(){
                    $(this).closest('.popup-bg').remove();
                });
            });
        }
    };
})(jQuery);
