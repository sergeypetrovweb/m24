(function ($) {
    Drupal.behaviors.pickadate = {
        attach: function (context, settings) {

            // Set Cookie.
            function setCookie(cname, cvalue, exdays) {
                var d = new Date();
                d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
                var expires = "expires=" + d.toUTCString();
                document.cookie = cname + "=" + cvalue + "; " + expires;
            }

            // Get Cookie.
            function getCookie(cname) {
                var name = cname + "=";
                var ca = document.cookie.split(';');
                for (var i = 0; i < ca.length; i++) {
                    var c = ca[i];
                    while (c.charAt(0) == ' ') {
                        c = c.substring(1);
                    }
                    if (c.indexOf(name) == 0) {
                        var tData = c.substring(name.length, c.length);
                        return tData;
                    }
                }
                return "";
            }

            // Cleaning Cookie.
            $(window).bind('beforeunload', function () {
                setCookie('round_trip', '', -1);
                setCookie('tempDate', '', -1);
            });

            //TODO remove on hotels search form update
            if (typeof settings.pickadate != 'undefined' && (!($('#flight_search').length)) && (!($('#search-hotels-search-form').length))) {
                if (typeof settings.pickadate.dateSettings != 'undefined') {
                    $.each(settings.pickadate.dateSettings, function (index, value) {
                        var options = JSON.parse(value);
                        var eval_values = {
                            min: 1,
                            max: 1
                        };
                        $.each(options, function (name, val) {
                            if (eval_values[name]) {
                                options[name] = eval(val);
                                options[name][1] += -1;
                            }
                        });
                        var el = $('#' + index);

                        el.pickadate(options);

                        var picker = el.pickadate('picker');

                        if (el.hasClass('birthday_input') || el.hasClass('expire_input')) {
                            if (el.val() && el.val().length == 10) {
                                picker.set('select',  el.val(), { format: 'yyyy-mm-dd' });
                            } else {
                                picker.set('select',  el.siblings('input[type=hidden]').val(), { format: 'yyyy-mm-dd' });
                            }
                        }




                        var select = el.attr('data-select');
                        if (select) {
                            var date = new Date(select * 1000);
                            date.setHours(23);
                            picker.set('highlight', date);
                        }
                    });
                }

                if (typeof settings.pickadate.timeSettings != 'undefined') {
                    $.each(settings.pickadate.timeSettings, function (index, value) {
                        var el = $('#' + index);
                        el.pickatime(eval(JSON.parse(value)));
                        var picker = el.pickadate('picker');
                        picker.set('select', select * 1000);
                        var select = el.attr('data-select');
                        if (select) {
                            var date = new Date(select * 1000);
                            date.setHours(23);
                            picker.set('highlight', date);
                        }
                    });
                }
            }

            //--remove on hotels search form update



            //added with new datepicker

            //flights form
            $('.search-fly-block .container_search').each(function() {
                var tempDate = getCookie('tempDate');
                var roundSelect = getCookie('round_trip');
                var searchDate = '';
                if (tempDate != '') {
                    tempDate = tempDate.split(" ");
                    if (tempDate[0].charAt(0) == 0) {
                        tempDate[0] = tempDate[0].substring(1);
                    }
                    searchDate = tempDate[1] + ' ' + tempDate[0];
                }

                var isRange = true;

                if ($(this).hasClass('multi_stop') || $(this).hasClass('one_way')) {
                    isRange = false;
                    $(this).find('.datepicker_date').datepick('clear');
                }

                if ($('#flight_search').length || $('#flight_search_inline').length) {

                    $(this).find('.datepicker_date').datepickerExtended({
                        rangeSelect: isRange
                    });

                }
                if ($(this).hasClass('round_trip')) {
                    if (roundSelect == 1) {
                        setCookie('round_trip', '', -1);
                        $(this).find('.datepicker_date').datepick('show');
                        $('.datepick-popup a[title*="' + searchDate + '"]').trigger('click');
                    }
                }

            });

            $('.adv_seacrh_block .container_search').each(function() {
                var tempDate = getCookie('tempDate');
                var roundSelect = getCookie('round_trip');
                var searchDate = '';
                if (tempDate != '') {
                    tempDate = tempDate.split(" ");
                    if (tempDate[0].charAt(0) == 0) {
                        tempDate[0] = tempDate[0].substring(1);
                    }
                    searchDate = tempDate[1] + ' ' + tempDate[0];
                }

                var isRange = true;

                if ($(this).hasClass('multi_stop') || $(this).hasClass('one_way')) {
                    isRange = false;
                    $(this).find('.datepicker_date').datepick('clear');
                }

                if ($('#flight_search').length) {

                    $(this).find('.datepicker_date').datepickerExtended({
                        rangeSelect: isRange
                    });

                }
                if ($(this).hasClass('round_trip')) {
                    if (roundSelect == 1) {
                        setCookie('round_trip', '', -1);
                        $(this).find('.datepicker_date').datepick('show');
                        $('.datepick-popup a[title*="' + searchDate + '"]').trigger('click');
                    }
                }

            });

            //hotels form
            if ($('#search-hotels-search-form').length) {
                $('#search-hotels-search-form').find('.datepicker_date').datepickerExtended();
            }


            //common
            $("#advanced_search .bottom-white span").on("select2-open", function() {
                $('.datepicker_date').datepick('hide');
            });

            $(window).scroll(function() {
                if($('.datepicker_date').length) {
                    $('.datepicker_date').blur();
                }
            })
        }
    };
})(jQuery);
