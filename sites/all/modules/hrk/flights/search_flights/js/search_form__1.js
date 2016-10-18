(function ($) {
    var cache = {};
    var ajax_process = false;
    Drupal.behaviors.sf_search_form = {
        attach: function (context, settings) {
            var form_id = '#' + settings.search_flights.forms.search_flights_search_form + ' ';

            Drupal.clientsideValidation.prototype.search_form_validate = function (error, element) {
                $(element).once(function () {
                    $(this).tooltipster({
                        theme: 'tooltipster-shadow',
                        animation: 'grow',
                        timer: 2000,
                        content: $(error).html($(element).data('error-title')),
                        trigger: 'custom'
                    });

                    $(this).on('click', function () {
                        $(form_id + '.error.tooltipstered').tooltipster('hide');
                    });
                });
            };


            // make live button revert trip
            $(form_id + '.search-flights-form-trip-revert', context).click(function () {
                var $prev_trip_container = $(this).prev();
                var $prev_trip_name = $prev_trip_container.find('.form-type-textfield input');
                var $prev_trip_code = $prev_trip_container.find('.hide-code');
                var $prev_trip_type = $prev_trip_container.find('.hide-type');

                var $next_trip_container = $(this).next();
                var $next_trip_name = $next_trip_container.find('.form-type-textfield input');
                var $next_trip_code = $next_trip_container.find('.hide-code');
                var $next_trip_type = $next_trip_container.find('.hide-type');

                var prev_name = $prev_trip_name.val();
                var prev_code = $prev_trip_code.val();
                var prev_type = $prev_trip_type.val();

                var next_name = $next_trip_name.val();
                var next_code = $next_trip_code.val();
                var next_type = $next_trip_type.val();

                $prev_trip_name.val(next_name);
                $next_trip_name.val(prev_name);

                $prev_trip_code.val(next_code);
                $next_trip_code.val(prev_code);

                $prev_trip_type.val(next_type);
                $next_trip_type.val(prev_type);
            });

            //make live button add trip
            $(form_id + '.search-flights-form-add-trip', context).click(function () {
                var $trip_count = $(form_id + 'input[name=trips_count]');
                if ($trip_count.val() < 5) {
                    $trip_count.val(parseInt($trip_count.val()) + 1).keyup();
                }
            });

            //make live button remove trip
            $(form_id + '.search-flights-form-remove-trip', context).click(function () {
                $(this).parent().find('input').each(function () {
                    $(this).val('');
                });

                var $trip_count = $(form_id + 'input[name=trips_count]');

                if ($trip_count.val() != 1) {
                    $trip_count.val(parseInt($trip_count.val()) - 1).keyup();
                }
            });
            //add class to form when direction_type field change
            $(form_id + 'input[name=direction_type]').change(function () {
                $(form_id).removeClass().addClass($(this).val().replace('_', '-'));
            });
            //autocomplete for from and to fields
            $(form_id + ".ui-autocomplete-fields").once(function () {
                $(this).HRK_Complete({
                    minLength: 3,
                    delay: 500,
                    autoFocus: true,
                    source: function (request, response) {
                        var term = request.term;
                        if (term in cache) {
                            response(cache[term]);
                            return;
                        }
                        if (!ajax_process && term) {
                            $.ajax({
                                type: 'GET',
                                url: Drupal.settings.basePath + Drupal.settings.pathPrefix + 'search/flights/cities_and_airports/autocomplete',
                                dataType: 'json',
                                data: {term: request.term},
                                beforeSend: function () {
                                    ajax_process = true;
                                },
                                success: function (data) {
                                    cache[term] = data;
                                    response(data);
                                    ajax_process = false;
                                }
                            });
                        }
                    },
                    change: function (event, ui) {
                        var $code = $(event.target).parent().parent().find('.hide-code');
                        var $type = $(event.target).parent().parent().find('.hide-type');
                        if (!$code.val()) {
                            $(event.target).val('').HRK_Complete('search', '');
                            $code.val('');
                            $code.val('');
                        }
                    },
                    focus: function (event, ui) {
                        $(event.target).val(ui.item.name);
                        $(event.target).parent().parent().find('.hide-code').val('');
                        $(event.target).parent().parent().find('.hide-type').val('');
                        return false;
                    },
                    select: function (event, ui) {
                        $(event.target).parent().parent().find('.hide-code').val(ui.item.code);
                        $(event.target).val(ui.item.name);
                        $(event.target).parent().parent().find('.hide-type').val(ui.item.type);
                        return false;
                    }
                });
            });


            //validate datepikers
            $(form_id + '.picker__input').each(function (k, v) {
                var $piker = $(this).pickadate('picker');
                $piker.on('set', function (data) {
                    var $next = $(form_id + '.picker__input').eq(k + 1);
                    if (data && $next.length > 0) {
                        var next_picker = $next.pickadate('picker');
                        var date = new Date(data.select);
                        next_picker.set('min', date);

                        if ($next.attr('id') == 'edit-trip-1-return') $('.picker__input').eq(k + 2).pickadate('picker').set('min', date);

                        var next_val = next_picker.get('select', 'yyyy/mm/dd');
                        if (next_val) {
                            var next_date = new Date(next_val);
                            if (date.getTime() > next_date.getTime()) {
                                next_picker.clear();
                            }
                        }
                    }

                    if ($next.attr('id') == 'edit-trip-1-return') {
                        $next = $('.picker__input').eq(k + 2);
                        if (data && $next.length > 0) {
                            next_picker = $next.pickadate('picker');
                            date = new Date(data.select);
                            next_picker.set('min', date);
                            next_val = next_picker.get('select', 'yyyy/mm/dd');
                            if (next_val) {
                                next_date = new Date(next_val);
                                if (date.getTime() >= next_date.getTime()) {
                                    next_picker.clear();
                                }
                            }
                        }
                    }
                });
            });

            $('#edit-direction-type-multi-stop').on('change', function () {
                $('.picker__input').each(function () {
                    $(this).pickadate('picker').clear();
                });
            });

            //show preloader overlay if form submit
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


function updateQueryStringParameter(uri, key, value) {
    var re = new RegExp("([?&])" + key + "=.*?(&|$)", "i");
    var separator = uri.indexOf('?') !== -1 ? "&" : "?";
    if (uri.match(re)) {
        return uri.replace(re, '$1' + key + "=" + value + '$2');
    }
    else {
        return uri + separator + key + "=" + value;
    }
}