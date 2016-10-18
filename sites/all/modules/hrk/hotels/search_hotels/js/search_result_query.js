(function ($) {
    Drupal.behaviors.sh_query = {
        attach: function (context, settings) {
            $('.change-parameters-link').on('click',function(){
                $('.loading').show();
            });
        }
    };
})(jQuery);
