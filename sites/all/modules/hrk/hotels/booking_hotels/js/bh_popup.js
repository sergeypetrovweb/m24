(function ($) {
    Drupal.behaviors.bh_popup = {
        attach: function (context, settings) {
            var $close = $('.bh-popup .cross-icon');
            $close.once(function(){
                $(this).on('click',function(){
                    var $popup =  $(this).closest('.popup-bg');
                    if($close.hasClass('no-remove')){
                        $popup.hide();
                    }else{
                        $popup.remove();
                    }
                });
            });
        }
    };
})(jQuery);
