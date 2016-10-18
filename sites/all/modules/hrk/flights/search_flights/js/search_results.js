(function ($) {
  //Реализация фильтра для ползунков
  var filter = function (op, data) {
    $('.content-row').each(function(k, e){
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

  Drupal.behaviors.search_flights = {
    attach: function (context, settings) {
      //console.log(settings);

      $('body').once(function() {
        /* Ползунок кол-ва пересадок */
        $("#transplant").ionRangeSlider({
          onFinish: function (data) {
            filter('wait', data);
          },
          hide_min_max: true,
          keyboard: true,
          min: settings.search_flights.min_transfer,
          max: settings.search_flights.max_transfer,
          from: settings.search_flights.min_transfer,
          to: settings.search_flights.max_transfer,
          type: 'double',
          step: 1,
          prefix: "",
          postfix: "",
          grid: false
        });
        /* Ползунок времени в пути */
        $("#travel_time").ionRangeSlider({
          onFinish: function (data) {
            filter('time', data);
          },
          hide_min_max: true,
          keyboard: true,
          min: settings.search_flights.min_time,
          max: settings.search_flights.max_time,
          from: settings.search_flights.min_time,
          to: settings.search_flights.max_time,
          type: 'double',
          step: 1,
          postfix: " " + Drupal.t("min"),
          grid: false
        });
        /* Ползунок цен */
        $("#price").ionRangeSlider({
          onFinish: function (data) {
            filter('price', data);
          },
          hide_min_max: true,
          keyboard: true,
          min: settings.search_flights.min_price,
          max: settings.search_flights.max_price,
          from: settings.search_flights.min_price,
          to: settings.search_flights.max_price,
          type: 'double',
          step: 1,
          postfix: settings.search_flights.currency_prefix,
          prefix: "",
          grid: false
        });




      });
    }


  };




  $(document).ready(function(){

    $('.open_search').click(function(){
      $('#breadcrumbs').toggleClass('open');
    });


    $('#flights-calendar-button').click(function(){
      var $popup_wr = $('.flights-calendar-popup');
                var $popup = $popup_wr.find('.popup-bg');
                $popup_wr.show();
                $popup.show();
              	var topPos = ($(window).height() - $("#flights-calendar-content").height())/2;
              	$popup.find(".popup-window").css("margin-top", topPos + 'px');
                console.log($("#flights-calendar-content").height());
                return false;
    });

    $('.flights-calendar-popup .cross-icon').click(function(){
    	$(this).closest('.popup-bg').hide();
    });

    $('.page-flights-results .content_table td.info').click(function() {
      //$('.content_table_details').hide();
      $(this).parents('.content_table').next('.content_table_details').toggleClass('open');
    });

    $('#select_air').change(function(){
        if ($(this).val() == 'none') {
            $('.content-row').removeClass('filter-hide-air');
        } else {
            $('.content-row').removeClass('filter-hide-air').filter("[data-airline!=" + $(this).val() + "]").addClass('filter-hide-air');
        }
    });


    $('#sort_container').mixItUp();

    $('.sort-link').click(function(){
      var e = $(this);
      var sort_type = e.data('type');
      var sort_order = 'asc';

      if (e.data('order') == 'asc') {
        sort_order = 'desc';
        e.data('order', 'desc');
      } else {
        e.data('order', 'asc');
      }

      $('#sort_container').mixItUp('multiMix', {sort: sort_type + ':' + sort_order});
      //console.log(sort_type, 'sort_type');
    });
  });


  $(window).resize(function(){
  	if ($('.flights-calendar-popup')){
  		var topPos = ($(window).height() - $("#flights-calendar-content").height())/2;
  		$('.flights-calendar-popup').find(".popup-window").css("margin-top", topPos + 'px');
  	}
  });


    Drupal.behaviors.sf_results = {
        attach: function (context, settings) {
            //transfers open
            $('.transfer-active').on('click', function () {
                $(this).next().find('.transition-message').show();
            });
            //transfers close
            $('.transition-message .cross-icon').on('click', function () {
                var $popup = $(this).closest('.transition-message');
                $popup.hide();
            });
            //make livew tooltips
            $('.tooltiper').on('hover', function () {
                $(this).once(function () {
                    $(this).tooltipster({position: 'bottom-left', theme: 'tooltipster-shadow', offsetY: 0});
                });
                $(this).tooltipster('show');
            });

            //mixup
            var $table_body = $('.result-container-table-body');
            var $all_rows = $('.result-flight-wrapper');

            var mix_up_filters = sf_get_filter_object();

            $all_rows.mixItUp({
                animation: {
                    enable: false
                },
                selectors: {
                    target: '.mix-combination'
                },
                load: {
                    sort: mix_up_filters.sort,
                    filter:mix_up_filters.filter
                },
                callbacks: {
                    onMixEnd: function (state) {
                        //console.log(state);
                        var $show = $(state.$show);

                        var first = $show.first();
                        var airline = first.closest('.result-container-table-flight');

                        //add attributes to parent row
                        airline
                            .attr('data-price', first.data('price'))
                            .attr('data-time', first.data('time'));

                        if (first.hasClass('direct')) {
                            airline.addClass('direct');
                        } else {
                            airline.removeClass('direct');
                        }

                        if (!$('.results-container').hasClass('result-without-airlines')) {
                            $show.not(first).hide();
                        }
                    }
                }
            });

            $table_body.mixItUp({
                selectors: {
                    target: '.mix-airlines'
                },
                load: {
                    sort: mix_up_filters.sort,
                    filter:mix_up_filters.filter
                },
                animation: {
                    enable: false
                },
                callbacks: {
                    onMixLoad: function () {
                        $(this).mixItUp('setOptions', {
                            animation: {
                                enable: true
                            }
                        });
                    },
                    onMixStart: function (state, futureState) {
                        var $targets = $(futureState.$targets);

                        var $fastest = null;
                        var $cheapest = null;
                        var price = 0;
                        var time = 0;
                        $targets.each(function () {

                            if (!price) price = $(this).data('price');
                            if (!time) time = $(this).data('time');
                            if (!$cheapest)  $cheapest = $(this);
                            if (!$fastest)  $fastest = $(this);

                            if (price > $(this).data('price')) $cheapest = $(this);
                            if (time > $(this).data('time'))$fastest = $(this);
                        });

                        $('.result-container-table-flight').removeClass('the-cheapest').removeClass('the-fastest');
                        $('.the-cheapest-icon,.the-fastest-icon').hide();
                        $cheapest.addClass('the-cheapest').find('.the-cheapest-icon').show();
                        $fastest.addClass('the-fastest').find('.the-fastest-icon').show();
                    }
                }
            });

            //make live sorting

            $('.filter-airlines').on('click', function () {
                var data = $(this).data('filter');

                $('.filter-airlines').removeClass('active');
                $(this).addClass('active');

                $('input[name=direction]').val(data);

                var mix_up_filters = sf_get_filter_object();
                sf_mix_it_up(mix_up_filters.sort,mix_up_filters.filter);
            });

            $('.search-flights-filter-form select').on('change', function () {

                var mix_up_filters = sf_get_filter_object();
                sf_mix_it_up(mix_up_filters.sort,mix_up_filters.filter);
                sf_mix_it_up(mix_up_filters.sort,mix_up_filters.filter);

            });

            //make live more variants
            $('.more-variants,.results-arrow').on('click', function () {
                var $airline_more = $(this).closest('.result-container-table-flight');

                //change class
                $('.results-container')
                    .addClass('result-without-airlines')
                    .removeClass('results-container-airlines')
                    .find('.result-container-table-flight').not($airline_more).hide();

                //add airline name to filter header
                $('.result-container-left .airline-name')
                    .html($airline_more.find('.company-name').html());

                //find active filters
                var mix_up_filters = sf_get_filter_object();

                var $mixUp = $airline_more.find('.result-flight-wrapper');

                $('input[name=direction]').attr('data-current-mix', $mixUp.attr('id'));

                $mixUp.mixItUp(
                    'multiMix', {
                        sort: mix_up_filters.sort,
                        filter: mix_up_filters.filter
                    });

                return false;
            });
//
            $('.result-container-filter .cross-icon').on('click', function () {
                $('.results-container')
                    .addClass('results-container-airlines')
                    .removeClass('result-without-airlines')
                    .find('.result-container-table-flight').show();

                var mix_up_filters = sf_get_filter_object();

                $all_rows.mixItUp('multiMix', {
                    sort: mix_up_filters.sort,
                    filter: mix_up_filters.filter
                });

                $table_body.mixItUp('multiMix', {
                    sort: mix_up_filters.sort,
                    filter: mix_up_filters.filter,
                    selectors: {
                        target: mix_up_filters.filter
                    }
                });

            });

            $('.results-booking-link').on('click', function () {
                $('.loading').show();
            });
        }
    };


    function sf_mix_it_up(sort, filter) {
        var $table_body = $('.result-container-table-body');
        var $all_rows = $('.result-flight-wrapper');

        if ($('.results-container').hasClass('result-without-airlines')) {
            $all_rows.filter('[id=' + $('input[name=direction]').data('current-mix') + ']').mixItUp('multiMix', {
                sort: sort,
                filter: filter
            });
        } else {
            $all_rows.mixItUp('multiMix', {
                sort: sort,
                filter: filter
            });

            $table_body.mixItUp('multiMix', {
                sort: sort,
                filter: filter,
                selectors: {
                    target: filter
                }
            });
        }
    }

    function sf_get_filter_object() {

        var filter_form = $('form.search-flights-filter-form').serializeArray();

        var mix_up = {
            filter: '',
            sort: ''
        };

        $.each(filter_form, function (k, v) {
            switch (v.name) {
                case'direction':
                    mix_up.filter = v.value;
                    break;
                case 'sort':
                    mix_up.sort = v.value;
                    break;
            }
        });

        return mix_up;
    }

})(jQuery);
