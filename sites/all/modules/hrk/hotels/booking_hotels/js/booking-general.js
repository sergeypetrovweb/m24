(function ($) {
    Drupal.behaviors.bh_general = {
        attach: function (context, settings) {
            $('.form-submit').once(function(){
                $(this).on('click',function(){
                    var $form = $(this).closest('form');
                    if($form.valid()){
                        $('.loading').show();
                    }
                });
            });

            $('.hotel-back').on('click',function(){
                $('.loading').show();
            });
        }
    }


})(jQuery);
