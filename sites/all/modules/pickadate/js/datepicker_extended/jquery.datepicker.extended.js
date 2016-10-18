(function ( $ ) {

  $.fn.datepickerExtended = function( options ) {

    var settings = $.extend({
      //datepicker options
      monthsToShow: 12,
      rangeSelect: true,
      firstDay: 1,
      minDate: 0,
      maxDate: '+1y',
      dateFormat: 'dd M',
      showAnim: 'show',
      altField: "#" + $(this).attr('target-id'),
      //mcustomscrollbar options
      theme: 'minimal-dark',
      scrollInertia: 500,
      scrollAmount: 150,
      //load all additional libraries
      cssPath: [],
      jsPath: []
    }, options );

    $.each(settings.cssPath, function(i, val) {
      $("<link/>", {
        rel: "stylesheet",
        type: "text/css",
        href: val
      }).appendTo("head");
    });

    $.each(settings.jsPath, function(i, val) {
      var s = document.createElement("script");
      s.type = "text/javascript";
      s.src = val;
      $("head").append(s);
    });

    this.datepick({
      changeMonth: false,
      useMouseWheel: false,
      alignment: 'bottomLeft',
      rangeSelect: settings.rangeSelect,
      altField: settings.altField,
      altFormat: 'yyyy-mm-dd',
      //multiSelect: 2,
      monthsToShow: settings.monthsToShow,
      firstDay: settings.firstDay,
      showAnim: settings.showAnim,
      minDate: settings.minDate,
      maxDate: settings.maxDate,
      dateFormat: settings.dateFormat,
      onShow: onShowDatepick,
      onSelect: onSelectDatepick,
      onClose: onCloseDatepick
    });

    this.attr('readonly', 'readonly');
    //$('.datepicker_labels').remove();

    if (settings.rangeSelect) {

      $(this).parent().append('<div class="datepicker_labels">' +
          '<span class="datepicker_label datepicker_from"></span>' +
          '<span class="datepicker_label datepicker_del"></span>' +
          '<span class="datepicker_label datepicker_to"></span></div>');
    } else {
      $(this).css('color', '#222');
    }

    function onCloseDatepick(date) {
      var next_elem = $(this).parent().parent().parent().parent().nextAll('.container_search');

      next_elem.each(function (key, val) {
        var next_elem_picker = $(val).find('.datepicker_date');
        var next_min_date = Date.parse(date);

        next_elem_picker.datepick('clear');
        next_elem_picker.datepick('option', 'minDate', new Date(next_min_date));

        next_elem_picker.parent().find('.datepicker_clear').remove();
      })
    }

    function onSelectDatepick(date) {
      if (date.length && settings.rangeSelect) {
        var date_value = $(this).val();
        var date_split = date_value.split(' - ');
        if (date_split[0] == date_split[1]) {
          $(this).parent().find('.datepicker_labels .datepicker_from').text(date_split[0]).removeClass('datepicker_current');
          $(this).parent().find('.datepicker_labels .datepicker_del').text(' — ');
          $(this).parent().find('.datepicker_labels .datepicker_to').text(Drupal.t('Backward')).addClass('datepicker_current');
        } else {
          $(this).parent().find('.datepicker_labels .datepicker_from').text(date_split[0]).removeClass('datepicker_current');
          $(this).parent().find('.datepicker_labels .datepicker_del').text(' — ');
          $(this).parent().find('.datepicker_labels .datepicker_to').text(date_split[1]).removeClass('datepicker_current');
        }


        //add clear button
        if (!$(this).parent().find('.datepicker_clear').length) {
          $(this).parent().append('<span class="datepicker_clear"></span>');

          $('.datepicker_clear').on('click', function() {
            $(this).parent().find('.datepicker_date').datepick('clear');
            $(this).parent().find('.datepicker_date').attr('placeholder', Drupal.t('Date'));
            $(this).parent().find('.datepicker_labels span').text('').removeClass('datepicker_current');

            $(this).remove();
          })
        }
      } else if (date.length) {
        var date_value = $(this).val();
        var date_split = date_value.split(' - ');
        setCookie('tempDate', date_split);
        setCookie('round_trip', 1);

        //add clear button to one-way and advanced form
        if (!$(this).parent().find('.datepicker_clear').length) {
          $(this).parent().append('<span class="datepicker_clear"></span>');

          $('.datepicker_clear').on('click', function() {
            $(this).parent().find('.datepicker_date').datepick('clear');
            setCookie('round_trip', '', -1);
            $(this).remove();
          })
        }
      }
    }

    function onShowDatepick(wrap, instance) {
      if (settings.rangeSelect) {
        $(this).attr('placeholder', '');
        if (!$(this).parent().find('.datepicker_labels .datepicker_from').text().length) {
          $(this).parent().find('.datepicker_labels .datepicker_from').text(Drupal.t('There')).addClass('datepicker_current');
          $(this).parent().find('.datepicker_labels .datepicker_del').text(' — ');
          $(this).parent().find('.datepicker_labels .datepicker_to').text(Drupal.t('Backward'));
        }
      }

      $(".datepick-multi").mCustomScrollbar({
        theme: settings.theme,
        scrollInertia: settings.scrollInertia,
        mouseWheel: {
          scrollAmount: settings.scrollAmount
        },
        callbacks: {
          onScroll: onScrollbarScroll
        }
      });

      $('.datepick-month-list').remove();

      $('.datepick-multi').append('<div class="datepick-month-list"></div>');
      var size = $('.datepick-month-row .datepick-month').length;
      $('.datepick-month-row .datepick-month').each(function(i, val) {
        var string = $('.datepick-month-header',val).text();
        var month = $.trim(string.replace(/\d+/g, ''));
        var year = $.trim(string.replace(/\D/g, ''));
        string = month + ' <span class="datepick-year">'+year+'</span>';

        $('.datepick-month-header',val).text('').append(string);

        if (i<=11 && size == 12) {
          $('.datepick-month-header', val).clone().addClass('month-tall').appendTo('.datepick-month-list');
        }

        if (i>11 && size == 24) {
          $('.datepick-month-header', val).clone().addClass('month-tall').appendTo('.datepick-month-list');
        }
      });

      $('.datepick-month-header.month-tall:first-child').addClass('selected');

      $('.datepick-month-header.month-tall').on('click', function() {
        var month_index = $(this).index();
        var month_selector = $('.datepick-multi').find('.mCSB_container').find('.datepick-month-row .datepick-month:eq(' + month_index + ')');
        $('.datepick-month-header.month-tall').removeClass('selected');
        $(this).addClass('selected');
        $('.datepick-multi').mCustomScrollbar('scrollTo', month_selector);
      });
    }

    function onScrollbarScroll() {
      var container_height = $('.datepick-month-row').height();
      var month_height = $('.datepick-month-row .datepick-month.first').height();
      var picker_height = $('.mCustomScrollBox').height();
      var scrollTop = $('.datepick-multi').find(".mCSB_container").position().top;
      var curr_element = scrollTop/month_height;

      curr_element = Math.floor(curr_element);
      curr_element = Math.abs(curr_element);

      if ((Math.abs(scrollTop) + picker_height) == container_height) {
        curr_element = container_height / month_height - 1;

        curr_element = Math.ceil(curr_element);
        curr_element = Math.abs(curr_element);
      }

      $('.datepick-month-header.month-tall').removeClass('selected');
      $('.datepick-multi').find('.datepick-month-header.month-tall:eq(' + curr_element + ')').addClass('selected');
    }

    // Set Cookie.
    function setCookie(cname, cvalue, exdays) {
      var d = new Date();
      d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
      var expires = "expires=" + d.toUTCString();
      document.cookie = cname + "=" + cvalue + "; " + expires;
    }

    return this;
  };

}( jQuery ));
