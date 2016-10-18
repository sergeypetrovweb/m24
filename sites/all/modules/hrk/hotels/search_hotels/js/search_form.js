(function ($) {
    var cache = {};
    var ajax_process = false;
    Drupal.behaviors.search_hotels_search_form = {
        attach: function (context, settings) {
            var form_id = '#' + settings.search_hotels.forms.search_hotels_search_form + ' ';

            /*CLIENTSIDE VALIDATION*/
/*            Drupal.clientsideValidation.prototype.search_form_hotels_validate = function (error, element) {
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
            };*/
            /*FORM*/

            //make live button add room
            $(form_id +'.search-hotels-form-add-room').on('click',function(){
                var $rooms_count = $(form_id + 'input[name=rooms_count]');
                if ($rooms_count.val() < 4) {
                    $rooms_count.val(parseInt($rooms_count.val()) + 1).keyup();
                }
            });

            //make live delete room
            $(form_id+'.search-hotels-form-remove-room-icon').on('click',function(){
                var $rooms_count = $(form_id + 'input[name=rooms_count]');
                if ($rooms_count.val() > 1) {
                    $rooms_count.val(parseInt($rooms_count.val()) - 1).keyup();
                }
            });

            //validate datepikers
            $(form_id + '.picker__input').each(function (k, v) {
                var $piker = $(this).pickadate('picker');
                $piker.on('set', function (data) {
                    var $next = $(form_id+'.picker__input').eq(k + 1);
                    if (data && $next.length > 0) {
                        var next_picker = $next.pickadate('picker');
                        var date = new Date(data.select);
                        next_picker.set('min', date);

                        var next_val = next_picker.get('select', 'yyyy/mm/dd');
                        if (next_val) {
                            var next_date = new Date(next_val);
                            if (date.getTime() > next_date.getTime()) {
                                next_picker.clear();
                            }
                        }
                    }
                });
            });

            //autocomplete for from and to fields
            $(form_id + ".ui-autocomplete-fields").once(function () {
                $(this).HRK_Complete({
                    minLength: 0,
                    delay: 190,
                    autoFocus: false,
                    source: function (request, response) {
                        var term = request.term;
                        if (term in cache) {
                            response(cache[term]);
                            return;
                        }

                        if (!term) {
                            request.term = term = 'getItemsWithoutSearch';
                        }

                        if (!ajax_process && term) {
                            $.ajax({
                                type: 'GET',
                                url: Drupal.settings.basePath + Drupal.settings.pathPrefix + 'search/hotels/cities/autocomplete',
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
                        var $code = $(event.target).parent().parent().find('.hidden-location-id');
                        if (!$code.val()) {
                            $(event.target).val('').HRK_Complete('search', '');
                            $code.val('');
                        }
                        if (!ui.item) {
                            $(this).blur();
                        }
                    },
                    focus: function (event, ui) {
                        $(event.target).val(ui.item.name);
                        $(event.target).parent().parent().find('.hidden-location-id').val('');
                        return false;
                    },
                    select: function (event, ui) {
                        $(event.target).parent().parent().find('.hidden-location-id').val(ui.item.lid);
                        $(event.target).val(ui.item.name);
                        return false;
                    }
                }).focus(function() {
                    $(this).HRK_Complete('search', 'getItemsWithoutSearch');
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