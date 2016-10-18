(function ($) {
    Drupal.behaviors.sf_popup = {
        attach: function (context, settings) {

            var $close = $('.sf-popup .cross-icon');

            $close.once(function(){
                $(this).on('click',function(){
                    $(this).closest('.popup-bg').remove();
                });
            });
        }
    };
})(jQuery);
