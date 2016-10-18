(function ($) {
    Drupal.behaviors.sh_results_hotel_detail = {
        attach: function (context, settings) {

            $('.room-block a.price-booking-link, .hotel-back').on('click',function(){
                $('.loading').show();
            });

            /*SLIDER*/
            $('.hotel-slider-carousel').flexslider({
                animation: "slide",
                controlNav: false,
                animationLoop: false,
                slideshow: false,
                itemWidth: 320,
                itemMargin: 5,
                minItems: 3,
                maxItems: 3,
                move:3,
                prevText: "",
                nextText: "",
                asNavFor: '.hotel-slider-slides'
            });

            $('.hotel-slider-slides').flexslider({
                animation: "slide",
                controlNav: false,
                directionNav: false,
                animationLoop: false,
                slideshow: false,
                sync: ".hotel-slider-carousel"
            });

            /*MAP*/
            $('.hotel-show-on-map').on('click', function() {
                if (!$('#hotel-main-map .gm-style').length) {
                    var $map_container = $('.map');
                    var lat = $map_container.data('lat');
                    var lng = $map_container.data('lng');
                    var hotel_google_map = new GMaps({div: '#hotel-main-map', lat: lat, lng: lng, zoom: 16, height: '300px', width: '100%'});
                    var marker = hotel_google_map.addMarker({
                        lat: lat,
                        lng: lng
                    });

                    //height magic on map init
                    $('.hotel-map-container').css('height', '0px').animate({height: '300px'}, 400, function() {
                        $('.hotel-map-container').css('height', 'auto');
                    });
                } else {
                    $('#hotel-main-map').slideDown(400);
                }

                $(this).addClass('hidden').siblings('.hotel-hide-map').removeClass('hidden');
            });

            $('.hotel-hide-map').on('click', function() {
                $('#hotel-main-map').slideUp(400);
                $(this).addClass('hidden').siblings('.hotel-show-on-map').removeClass('hidden');
            });

            /*MORE INFO*/
            $('.more-info-link').on('click', function () {
                $(this).next().toggle();
                if ($(this).hasClass('info-up')) {
                    $(this).removeClass('info-up').addClass('info-down');
                } else {
                    $(this).removeClass('info-down').addClass('info-up');
                }

                return false;
            });

            /*FILTERS*/
            var $hotels_wr = $('#search-result-rooms');

            $('.search-hotels-details-filter-form').on('change', function () {
                var mix_up_filters = sh_get_filter_object();
                $hotels_wr.mixItUp('multiMix', mix_up_filters);
            });

            //mixup
            var mix_up_filters = sh_get_filter_object();

            $hotels_wr.mixItUp({
                selectors: {
                    target: '.mix'
                },
                load: {
                    sort: 'price:desc'
                },
                layout: {
                    display: 'block'
                }
            });

            $('a.sort-link').on('click', function() {
                var data = $(this).attr('data-type');
                if (($(this).attr('data-order') == 'desc')) {
                    mix_up_filters.sort = data + ':asc';
                    $(this).attr('data-order', 'asc');
                } else if ($(this).attr('data-order') == 'asc') {
                    mix_up_filters.sort = data + ':desc';
                    $(this).attr('data-order', 'desc');
                }
                $hotels_wr.mixItUp('multiMix', mix_up_filters);
            });

            //var mix_up_filters = sh_get_filter_object();
            //
            ////mixup
            //$hotels_wr.mixItUp({
            //    selectors: {
            //        target: '.room-line'
            //    },
            //    load: {
            //        filter: mix_up_filters.filter,
            //        sort: mix_up_filters.sort
            //    },
            //    animation: {
            //        enable: false
            //    },
            //    layout: {
            //        display: 'block'
            //    },
            //    callbacks: {
            //        onMixLoad: function () {
            //            $(this).mixItUp('setOptions', {
            //                animation: {
            //                    enable: true,
            //                    animateResizeContainer: false
            //                }
            //            });
            //        }
            //    }
            //});
        }
    };

    function sh_get_filter_object() {

        var filter_form = $('form.search-hotels-details-filter-form').serializeArray();

        var mix_up = {
            filter:[],
            sort:''
        };

        $.each(filter_form, function (k, v) {
            if ( v.name == 'basis' || v.name == 'class' || v.name == 'type') {

                if (v.value != '_none') {
                    mix_up.filter.push('.' + v.value);
                }
            }
            if (v.name == 'sort') {
                mix_up.sort = v.value;
            }
        });

        mix_up.filter = (mix_up.filter.join(' ')) ? mix_up.filter.join(' ') : '.available';
        return mix_up;
    }

})(jQuery);
