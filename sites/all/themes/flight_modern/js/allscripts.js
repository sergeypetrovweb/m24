(function($) {

    jQuery.validator.addMethod('selectcheck', function (value) {
        return (value != '_none');
    });

    function people_cnt_show() {
        $("input.people_count").click(function () {
            $(".people_count_overlay").show();
        });
        $(".number").stylerNumber();

        if ($('#edit-rooms').length) {
            $(this).find('.child_age').hide();
            $('.room-guest-type-chd').siblings('.ui-spinner-button').click(function (){
                if ($('.room-guest-type-chd').attr('aria-valuenow') > 0) {
                    $(this).parent().parent().parent().parent().find('.child_age').show();
                } else {
                    $(this).parent().parent().parent().parent().find('.child_age').hide();
                }
            });
        }
    }

    //Кнопки добавления/удаления строк для сложной формы на главной странице
    function add_count_buttons(block) {
        if(block.length) {
            block.find(".container_search.multi_stop").append('<div class="count_control"><p class="count_del"></p></div>');

            $('.count_control .count_add').on('click', function() {
                block.find(".container_search.multi_stop:hidden").eq(0).show();
                /*console.log(block.find(".container_search.multi_stop:hidden").eq(0));*/
                var $trip_count = $('.search-fly-block input[name=trips_count]');
                if ($trip_count.val() < 5) {
                    $trip_count.val(parseInt($trip_count.val()) + 1).keyup();
                }
            });

            $('.container_search.multi_stop .count_control .count_del').on('click', function() {
                if ($(this).parent().parent().is(':visible') && $(".container_search.multi_stop:visible").length > 1) {
                    $(this).parent().parent().hide();
                    $(this).parent().parent().find('input').each(function(e, elem){
                        $(elem).val('');
                    });
                }
            });
        }
    }

    function validateSeachForm(form, selectclass) {
        if ($('.data_type_name').length) {
            $('.data_type_name').keydown(function(event){
                if ((event.keyCode > 47 && event.keyCode < 58) || (event.keyCode > 95 && event.keyCode < 106 )) {
                    event.preventDefault();
                }
            });
        }

        form.find('input.form-submit').click(function() {
            var unvalid = false;

            form.validate();
            if (form.find('.picker__input').length) {
                form.find('.picker__input').rules("add", {
                    required: false
                });
            }


            form.find('input').each(function(i,elem) {
                if ($(elem).is(':visible') && $(elem).attr('data-requiur')== 1) {
                    $(elem).rules( "add", {
                        required: true,
                        messages: {
                            required: $(elem).attr('data-error-title')
                        }
                    });

                    switch ($(elem).attr('type')) {
                        case 'checkbox':
                        case 'radio':
                            if ($(elem).valid() == false) {
                                $(elem).parent().css('border-color','#E94E38');
                                unvalid = true;
                            } else {
                                $(elem).parent().css('border-color','#D3D3D3');
                            }
                            break;
                    }
                }
//

            });

            form.find('select').each(function(i,elem) {
                if ($(elem).is(':visible') && $(elem).attr('data-requiur')== 1) {
                    $(elem).rules( "add", {
                        required: true,
                        messages: {
                            required: $(elem).attr('data-error-title')
                        }
                    });

                    if ($(elem).context.value == '_none') {
                        $(elem).css('border-color','#E94E38');
                        unvalid = true;
                    } else {
                        $(elem).css('border-color','#D3D3D3');
                    }

                    if ($(elem).hasClass('error')) {
                        $(elem).parent().find(selectclass).addClass('error');
                        $(elem).parent().find(selectclass).css('border-color','#E94E38');
                    }
                }
            });

            if (!form.valid() && !unvalid) {
                return false;
            }
        });
    }

    function people_count(form) {
        $string = form.find('.people_count').attr('placeholder').split(' ');

        if ( typeof($count) != "undefined" && $count != null ) {
            form.find('.people_count').attr('placeholder', $count + ' ' + $string[1]);
        } else {
            $count = 0;

            form.find('.number').each(function(i,elem) {
                if (!elem.value) {
                    elem.value = 0;
                } else {
                    $count += parseInt(elem.value);
                }
            });
            form.find('.people_count').attr('placeholder', $count + ' ' + $string[1]);
        }

        if (form.find('.number').attr('aria-valuenow')) {
            form.find('.people_count').attr('placeholder', '1 ' + $string[1]);
            form.find('.people_count_block .ui-icon').click(function (){
                $count = 0;

                form.find('.number').each(function(i,elem) {
                    if ($(elem).is(':visible')) {
                        $count += parseInt($(elem).attr('aria-valuenow'));
                    }
                });

                if ($count == 1) {
                    form.find('.people_count').attr('placeholder', Drupal.t('@count person', {'@count' : $count}));
                } else if ($count > 4) {
                    form.find('.people_count').attr('placeholder', Drupal.t('@count people', {'@count' : $count}));
                } else {
                    form.find('.people_count').attr('placeholder', Drupal.t('@count[2] people', {'@count[2]' : $count}));
                }
            });

        } else {
            form.find('.number').change(function (){
                if (this.value < 1) {
                    this.value = 0;

                    if($(this).attr('id') == 'adults') {
                        this.value = 1;
                    }

                } else if (this.value > 5) {
                    this.value = 6;
                }
                checkInputs($(this),this.value);
//                teens
//                children
                $count = 0;

                form.find('.number').each(function(i,elem) {
                    if (!elem.value) {
                        elem.value = 0;
                    } else {
                        $count += parseInt(elem.value);
                    }
                });


                if ($count == 1) {
                    form.find('.people_count').attr('placeholder', Drupal.t('@count person', {'@count' : $count}));
                } else if ($count > 4) {
                    form.find('.people_count').attr('placeholder', Drupal.t('@count people', {'@count' : $count}));
                } else {
                    form.find('.people_count').attr('placeholder', Drupal.t('@count[2] people', {'@count[2]' : $count}));
                }
            });

        }
    }

    function checkInputs(self, newvalue){
        var valid = Number(newvalue);
        self.parents('.people_count_overlay').find('.counts_people input').each(function(i, item){
            if ($(item).attr('id') != self.attr('id')) {
                var input = Number($(item).val());
                valid = valid + input;
                while (valid > 6) {
                    if($(item).attr('id') == 'adults' && $(item).val() == 1) {
                        self.val( self.val() - 1 );
                    } else {
                        $(item).val( input - 1 );
                    }
                    valid--;
                }
            }
        });
    }

    //Реализация фильтра для ползунков
    var filter = function (op, data) {
        $('.hotel-item, .reservation').each(function(k, e){
            var e = $(this);
            var filter_class = 'filter-hide-' + op;
            var val = e.data(op);
            if (data.from > val || val > data.to) {
                e.addClass(filter_class);
            } else {
                e.removeClass(filter_class);
            }
        });
    };

    var price_range_hotel = function() {
        var price_cheap = $(".sort_content .price-range .cheap").text() + ' ';
        var price_expensive = $(".sort_content .price-range .expensive").text();
        var price_prefix = $(".sort_content .price-range .prefix").text();
        $(".price #edit-price").ionRangeSlider({
            onFinish: function (data) {
                filter('price', data);
            },
            hide_min_max: true,
            keyboard: true,
            min: price_cheap,
            max: price_expensive,
            from: price_cheap,
            to: price_expensive,
            type: 'double',
            step: 10,
            prefix: price_prefix,
            grid: false
        });
    };

    var price_range_hotel_results = function() {
        var price_cheap = $(".hotel-container .price-range .cheap .currency__price").text().replace(/ /g,'');
        var price_expensive = $(".hotel-container .price-range .expensive .currency__price").text().replace(/ /g,'');
        //var price_prefix = $(".hotel-container .price-range .prefix").text();

        $(".price #price_sort").ionRangeSlider({
            onFinish: function (data) {
                filter('price', data);
            },
            hide_min_max: true,
            keyboard: true,
            min: price_cheap,
            max: price_expensive,
            from: price_cheap,
            to: price_expensive,
            type: 'double',
            step: 10,
            //prefix: price_prefix,
            grid: false
        });
    };

    var show_popup_load = function() {
        $('#loader_block').addClass('open loader_hotel');
    };

    $(document).mouseup(function (e) {
      if ($(".people_count_overlay").has(e.target).length === 0){
        $(".people_count_overlay").hide();
      }
    });

    $(document).ajaxComplete(function(event, xhr, settings) {
        if(settings.url.search('/system/ajax') > 0) {
            people_cnt_show();
            if($('.search-fly-block').length) {
                add_count_buttons($('.search-fly-block'));
            }
            if($('.adv_seacrh_block').length) {
                add_count_buttons($('.adv_seacrh_block'));
            }
        }

        if ($('form').length) {
            $('form').each(function(i,form) {
                if ($(form).attr('data-typeform') == 'search') {
                        validateSeachForm($(form),'.jq-selectbox__select');
                        people_count($(form));
                }
            });
        }

    });

    $(document).ready(function() {
        people_cnt_show();

        if($('#edit-passengers .select2-chosen').length) {
            $('#edit-passengers .select2-chosen').text('');
        }

        if($('.search-fly-block').length) {
            add_count_buttons($('.search-fly-block'));
        }
        if($('.adv_seacrh_block').length) {
            add_count_buttons($('.adv_seacrh_block'));
        }

        $('#open_comments').on('mousedown',function() {
            if ($('.comment-form').is(":hidden")) {
                $('.comment-form').slideDown("slow");
                $(this).css('opacity','0');
                $(this).css('z-index','-10');
            }
        });


        if ($('form').length) {
            $('form').each(function(i,form) {
                if ($(form).attr('data-typeform') == 'search') {
                    validateSeachForm($(form),'.jq-selectbox__select');
                    people_count($(form));
                } else if ($(form).attr('data-typeform') == 'book') {
                    validateSeachForm($(form),'.select2-container');
                }
            });
        }

        //Фильтр для option'ов на странице отелей
        $('#search-hotels-result-filter select, .search-hotels-details-filter-form select').on('change', function() {
            var filter_class = 'filter-hide-' + $(this).attr('name');
            var filter_val = $(this).val();
//            console.log(filter_class);
//            console.log(filter_val);

            $('.hotel-item, .reservation').each(function(k, e){
                var e = $(this);
                if (!e.hasClass(filter_val) && (filter_val != '_none')) {
                    e.addClass(filter_class);
                } else {
                    e.removeClass(filter_class);
                }
            });
        });


        price_range_hotel();
        price_range_hotel_results();

        //show preloader on simple link
        $('.choice_hotel a.default-bb, .reserv a.default-bb').on('click', function () {
            show_popup_load();
        });

        $('#search-hotels-search-form').submit(function (event) {
            show_popup_load();
        });

        //$('#search-result-rooms').mixItUp();

        //$('.sort-link').click(function(){
        //    var e = $(this);
        //    var sort_type = e.data('type');
        //    var sort_order = 'asc';
        //
        //    if (e.data('order') == 'asc') {
        //        sort_order = 'desc';
        //        e.data('order', 'desc');
        //    } else {
        //        e.data('order', 'asc');
        //    }
        //
        //    console.log(sort_order);
        //
        //    $('#search-result-rooms').mixItUp({sort: sort_type + ':' + sort_order});
        //
        //    //$('#search-result-rooms').mixItUp({
        //    //
        //    //    selectors: {
        //    //        target: '.mix',
        //    //        sort: '.mix'
        //    //    },
        //    //    callbacks: {
        //    //        onMixEnd: function(state){
        //    //            console.log(state)
        //    //        }
        //    //    }
        //    //});
        //
        //});

      $("input.people_count").click(function () {
        $(".people_count_overlay").show();
          return false;
      });

        $("#switcher input").click(function () {
            var e = $(this);
            if (e.is('.no_active')) {
              var action = e.data('action');
              if (action == 'departure') {
                $('#table_air').removeClass('table-time-arrival').addClass('table-time-departure');
              } else {
                $('#table_air').removeClass('table-time-departure').addClass('table-time-arrival');
              }
              e.removeClass('no_active').addClass('active').siblings('input').removeClass('active').addClass('no_active');

            } else {
                //$(this).removeClass('no_active');
                //$(this).addClass('active');
            }
        });

        $("#close").click(function () {
            $('.info_block').hide();
        });


        $(".gender input").click(function () {
            if ($(this).is('#gender_one .male.active')) {
                $("#gender_one .female").removeClass('no_active');
                $("#gender_one .female").addClass('active');
                $("#gender_one .male").removeClass('active');
                $("#gender_one .male").addClass('no_active');
            }
            if ($(this).is('#gender_one .female.active')) {
                $("#gender_one .female").removeClass('active');
                $("#gender_one .female").addClass('no_active');
                $("#gender_one .male").removeClass('no_active');
                $("#gender_one .male").addClass('active');
            }
        });

        $(".gender input").click(function () {
            if ($(this).is('#gender_two .male.active')) {
                $("#gender_two .female").removeClass('no_active');
                $("#gender_two .female").addClass('active');
                $("#gender_two .male").removeClass('active');
                $("#gender_two .male").addClass('no_active');
            }
            if ($(this).is('#gender_two .female.active')) {
                $("#gender_two .female").removeClass('active');
                $("#gender_two .female").addClass('no_active');
                $("#gender_two .male").removeClass('no_active');
                $("#gender_two .male").addClass('active');
            }
        });

        $(".gender input").click(function () {
            if ($(this).is('#gender_three .male.active')) {
                $("#gender_three .female").removeClass('no_active');
                $("#gender_three .female").addClass('active');
                $("#gender_three .male").removeClass('active');
                $("#gender_three .male").addClass('no_active');
            }
            if ($(this).is('#gender_three .female.active')) {
                $("#gender_three .female").removeClass('active');
                $("#gender_three .female").addClass('no_active');
                $("#gender_three .male").removeClass('no_active');
                $("#gender_three .male").addClass('active');
            }
        });

/*        if ($('.timeago').length) {
            $(".timeago").timeago();
        }*/
    });

    $(window).load(function() {
        $('.flexslider').flexslider({
            animation: "slide",
            controlNav: "thumbnails"
        });
    });

})	(jQuery);