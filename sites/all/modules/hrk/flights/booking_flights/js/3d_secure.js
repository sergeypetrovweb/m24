(function ($) {
    Drupal.behaviors.three_d_secure = {
        attach: function (context, settings) {
            $('a.3d-secure-link').click(function(){
                window.open($(this).attr('href'));
                return false;
            });
        }
    };
})(jQuery);
