(function ($) {
    Drupal.behaviors.bh_form = {
        attach: function (context, settings) {
            var form_id = '#' + settings.booking_hotels.forms.booking_hotels_form + ' ';

            /* TRANSLITERATION FIELDS*/
            $('.li-translit').each(function () {
                $(this).once(function () {
                    $(this).liTranslit({eventType: 'keyup', caseType: 'upper'});
                });
            });

            //Drupal.clientsideValidation.prototype.bh_form_validate = function (error, element) {
            //    $(element).once(function () {
            //        $(this).tooltipster({
            //            theme: 'tooltipster-shadow',
            //            animation: 'grow',
            //            timer: 2000,
            //            content:$(error),
            //            trigger: 'custom'
            //        });
            //
            //        $(this).on('click', function () {
            //            $('.error.tooltipstered').tooltipster('hide');
            //        });
            //    });
            //};

            $(form_id).submit(function (event) {
                if ($(this).valid()) {
                    $('.loading').show();
                } else {
                    $(form_id + '.error.tooltipstered').tooltipster('show');
                }
            });
        }
    };
})(jQuery);
