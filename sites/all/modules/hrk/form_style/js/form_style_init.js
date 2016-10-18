(function ($) {
    Drupal.behaviors.form_style = {
        attach: function (context) {

            Drupal.settings.form_style = Drupal.settings.form_style || {};

            if (Drupal.settings.form_style) {
                $.each(Drupal.settings.form_style, function (k, v) {
                    var selectors = v.selectors || [];
                    var html_form_id = '#' + v.html_form_id || '';
                    selectors = ' ' + selectors.join(',');

                    if ((html_form_id || selectors)/* && (k != 'booking_hotels_form')*/) {
                        $(html_form_id + selectors).once(function () {
                            $(html_form_id + selectors).styler();
                        });
                    }
                });

            }
        }
    };
})(jQuery);

