(function ($) {
    Drupal.behaviors.sh_popup = {
        attach: function (context, settings) {

            var $close = $('.sh-popup .cross-icon');

            $close.once(function(){
                $(this).on('click',function(){
                    $(this).closest('.popup-bg').remove();
                });
            });
        }
    };
})(jQuery);
