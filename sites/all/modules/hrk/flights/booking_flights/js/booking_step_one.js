(function ($) {
    Drupal.behaviors.booking_step_one = {
        attach: function (context, settings) {
            /* TRANSLITERATION FIELDS*/
            $('.li-translit').each(function () {
                $(this).once(function () {
                    $(this).liTranslit({eventType: 'keyup', caseType: 'upper'});
                });
            });

/*            Drupal.clientsideValidation.prototype.booking_form_validate = function (error, element) {

                $(element).tooltipster({
                    theme: 'tooltipster-shadow',
                    animation: 'grow',
                    timer: 2000,
                    content: $(error),
                    trigger: 'custom'
                });

                $(this).on('click', function () {
                    $('.error.tooltipstered').tooltipster('hide');
                });
            };*/
        }
    };
})(jQuery);
