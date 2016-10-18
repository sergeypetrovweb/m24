(function ($) {
    Drupal.behaviors.sf_plus_minus = {
        attach: function (context, settings) {
            var form_id = '#' + settings.search_flights.forms.search_flights_search_form + ' ';

            var pass_options = {
                'adt': {min: 1, max: 6},
                'chd': {min: 0, max: 5},
                'inf': {min: 0, max: 6}
            };

            $(form_id + 'input.passenger-type', context).each(function () {
                var pass_type = $(this).data('passenger-type');

                $(this).HRK_Spinner({
                    min: pass_options[pass_type].min,
                    max: pass_options[pass_type].max,
                    change: function (event, ui) {
                        var self = $(event.target);
                        var pass_type = self.data('passenger-type');

                        if (self.val() >= pass_options[pass_type].max) {
                            self.parent().find('.ui-spinner-up').addClass('disabled');
                        } else if (self.val() <= pass_options[pass_type].min) {
                            self.parent().find('.ui-spinner-down').addClass('disabled');
                        } else {
                            self.parent().find('.ui-spinner-button').removeClass('disabled');
                        }
                    },
                    spin: function (event, ui) {
                        var target = $(event.target);
                        var pass_type = target.data('passenger-type');

                        var $adt = $(form_id + 'input[data-passenger-type=adt]');
                        var $chd = $(form_id + 'input[data-passenger-type=chd]');
                        var $inf = $(form_id + 'input[data-passenger-type=inf]');

                        switch (pass_type) {
                            case 'adt':
                                var pass_dif = pass_options.adt.max - ui.value;
                                if ($chd.HRK_Spinner('value') > pass_options.adt.max - ui.value) $chd.HRK_Spinner('value', pass_options.adt.max - ui.value);
                                if ($inf.HRK_Spinner('value') > ui.value)  $inf.HRK_Spinner('value', ui.value);
                                break;
                            case 'chd':
                                if (ui.value > pass_options.adt.max - $adt.HRK_Spinner('value')) $adt.HRK_Spinner('value', pass_options.adt.max - ui.value);
                                break;
                            case 'inf':
                                if (ui.value > $adt.HRK_Spinner('value')) $adt.HRK_Spinner('value', ui.value);
                                if ($chd.HRK_Spinner('value') > pass_options.adt.max - $adt.HRK_Spinner('value')) $chd.HRK_Spinner('value', pass_options.adt.max - $adt.HRK_Spinner('value'));
                                break;
                        }
                        //add class disabled if spinner value beyond the limits of permitted values
                        if (ui.value >= pass_options[pass_type].max) {
                            $(event.currentTarget).addClass('disabled');
                        } else if (ui.value <= pass_options[pass_type].min) {
                            $(event.currentTarget).addClass('disabled');
                        } else {
                            target.parent().find('.ui-spinner-button').removeClass('disabled');
                        }
                    }
                });
            });
        }
    };
})(jQuery);