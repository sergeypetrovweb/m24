(function ($) {
    Drupal.behaviors.book_flight = {
        attach: function (context, settings) {

            if($('#clock').length) {
                var clock = new FlipClock($('#clock'), $('#clock').attr('data-left'), {
                    clockFace: 'MinuteCounter',
                    autoStart: true,
                    countdown: true,
                    callbacks: {
                        stop: function() {
                            location.reload();
                        }
                    }
                });
            }

            $('.form-submit').once(function(){
                $(this).on('click',function(){
                    $('.loading').show();
                });
            });

            $('.show_rules').once(function(){
                $('.show_rules').on('click',function(){
                    $('.book-rules-popup, .flight-rules').show();
                });
            });
        }
    };
})(jQuery);
