(function ($) {
    Drupal.behaviors.search_hotels_plus_minus = {
        attach: function (context, settings) {
            var form_id = '#' + settings.search_hotels.forms.search_hotels_search_form + ' ';

            var guest_options = {
                'adt': {min: 1, max: 4},
                'chd': {min: 0, max: 2},
                'age': {min: 0, max: 12}
            };

            $(form_id + 'input.guest-type', context).each(function () {
                var guest_type = $(this).data('room-guest-type');

                $(this).HRK_Spinner({
                    min: guest_options[guest_type].min,
                    max: guest_options[guest_type].max,
                    change: function (event, ui) {
                        var self = $(event.target);
                        var guest_type = self.data('room-guest-type');

                        if (self.val() >= guest_options[guest_type].max) {
                            self.parent().find('.ui-spinner-up').addClass('disabled');
                        } else if (self.val() <= guest_options[guest_type].min) {
                            self.parent().find('.ui-spinner-down').addClass('disabled');
                        } else {
                            self.parent().find('.ui-spinner-button').removeClass('disabled');
                        }
                    },
                    spin: function (event, ui) {
                        var target = $(event.target);
                        var guest_type = target.data('room-guest-type');

                        if(guest_type == 'chd'){
                            target.closest('.fieldset-wrapper').find('input[type=hidden]').val(ui.value).keyup();
                        }

                        //add class disabled if spinner value beyond the limits of permitted values
                        if (ui.value >= guest_options[guest_type].max) {
                            $(event.currentTarget).addClass('disabled');
                        } else if (ui.value <= guest_options[guest_type].min) {
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