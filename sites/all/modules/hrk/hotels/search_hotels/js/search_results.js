(function ($) {
    Drupal.behaviors.sh_results = {
        attach: function (context, settings) {

            var $hotels_wr = $('.hotel-found');

            $('.hotel-bottom a').on('click', function () {
                $('.loading').show();
            });
            //make livew tooltips
            $('.tooltiper').on('hover', function () {
                $(this).once(function () {
                    $(this).tooltipster({position: 'bottom-left', theme: 'tooltipster-shadow', offsetY: 0});
                });
                $(this).tooltipster('show');
            });

            //map
            $('#search-hotels-result-filter a.show-map-link').on('click', function() {
                if (!$('#hotels-main-map .gm-style').length) {
                    var map_settings = settings.sh.map;
                    var hotel_google_map = new GMaps({
                        div: '#hotels-main-map',
                        lat: map_settings.latitude,
                        lng: map_settings.longitude,
                        zoom: 11,
                        height: '300px',
                        width: '100%'
                    });

                    var markers = sh_created_markers($('.hotel-item'), hotel_google_map, map_settings);//CREATE MAP

                    var cluster_image = settings.basePath + 'sites/all/themes/flight_modern/images/marker-hotel-cluster-new.png';
                    var cluster_options = {
                        styles: [
                            {url: cluster_image, width: 37, height: 52, textSize: 16, textColor: '#ffffff'}
                        ]
                    };

                    var cluster = sh_create_marker_cluster(hotel_google_map.map, markers, cluster_options);

                    //height magic on map init
                    $('.hotels-map-container').css('height', '0px').animate({height: '300px'}, 400, function() {
                        $('.hotels-map-container').css('height', 'auto');
                    });
                } else {
                    $('#hotels-main-map').slideDown(400);
                }

                $(this).addClass('hidden').siblings('.hide-map-link').removeClass('hidden');
            });

            //hide map link
            $('#search-hotels-result-filter a.hide-map-link').on('click', function () {
                $('#hotels-main-map').slideUp(400);
                $(this).addClass('hidden').siblings('.show-map-link').removeClass('hidden');
            });

            //SEARCH HOTELS
            var search = $('#search_hotels_js_live');
            var searchMeme = search.searchMeme({
                onSearch: function (searchText) {
                    var filter_form = $('form.search-hotels-filter-form');
                    var search_default_text = search.data('search-text');

                    var sort = filter_form.find('select[name=sort]').val();

                    var mix_up = {filter: [], sort: sort};

                    filter_form[0].reset();

                    search.val(searchText);
                    filter_form.find('select[name=sort]').val(sort);


                    if (searchText && searchText != search_default_text) {
                        var $hotels_by_search = $('.hotel-item[data-name*="' + searchText.toLowerCase() + '"]');

                        $hotels_by_search.each(function () {
                            mix_up.filter.push('.hotel-item-' + $(this).attr('data-hotel-item'));
                        });
                    }

                    mix_up.filter = (mix_up.filter.join(',')) ? mix_up.filter.join(',') : '.hotel-item';

                    //$hotels_wr.mixItUp('multiMix', mix_up);
                    search.searchMeme({searchComplete: true});
                },
                animate: false,
                buttonPlacement: 'left',
                button: 'flight',
                defaultText: search.data('search-text')
            });

            //search.on('change', function () {
            //    setTimeout(function () {
            //        if (search.val() == '') {
            //            searchMeme.onSearch('');
            //        }
            //    }, 300);
            //});

            $('.jq-selectbox__dropdown').hover(
                function() {
                }, function() {
                    $(this).hide();
                }
            );

            //make live filters

            $('.search-hotels-filter-form select').on('change', function () {
                search.val(search.data('search-text'));
                //var mix_up_filters = sh_get_filter_object();
                //console.log(mix_up_filters);
                //$hotels_wr.mixItUp('multiMix', mix_up_filters);
            });

            //mixup
            var mix_up_filters = sh_get_filter_object();

            $hotels_wr.mixItUp({
                selectors: {
                    target: '.mix'
                },
                load: {
                    sort: 'price:asc'
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

            //$hotels_wr.mixItUp({
            //    selectors: {
            //        target: '.hotel-item'
            //    },
            //    load: {
            //        filter: mix_up_filters.filter,
            //        sort: mix_up_filters.sort
            //    },
            //    animation: {
            //        enable: false
            //    },
            //    callbacks: {
            //        onMixLoad: function () {
            //            $(this).mixItUp('setOptions', {
            //                animation: {
            //                    enable: true,
            //                    animateResizeContainer: false
            //                }
            //            });
            //        },
            //        onMixStart: function (state, futureState) {
            //            var updated_markers = sh_update_markers($(futureState.$show), markers);
            //            sh_update_marker_cluster(cluster, updated_markers);
            //        },
            //        onMixEnd: function (state) {
            //            $('.hotel-access-line .access span').html($('.hotel-item:visible').size());
            //            sh_pagination(settings);
            //
            //        }
            //    }
            //});
        }
    };

    function sh_get_filter_object() {

        var filter_form = $('form.search-hotels-filter-form').serializeArray();

        var mix_up = {
            filter: [],
            sort: ''
        };

        $.each(filter_form, function (k, v) {
            if (v.name == 'rating' || v.name == 'basis' || v.name == 'class' || v.name == 'type') {
                if (v.value != '_none') {
                    mix_up.filter.push('.' + v.value);
                }
            }

            if (v.name == 'sort') {
                mix_up.sort = v.value;
            }
        });

        mix_up.filter = (mix_up.filter.join(',')) ? mix_up.filter.join(',') : '.hotel-item';

        return mix_up;
    }

    function sh_pagination(settings) {

        var $hotels = $('.hotel-item:visible');
        var total_pages = Math.ceil($hotels.size() / 9);
        for (var page = 1; page <= total_pages; page++) {
            $hotels.slice((page - 1) * 9, page * 9).attr('data-page', page);
        }

        var $pagination = $('#pagination');

        if ($('ul.pagination').length) {
            $pagination.twbsPagination('destroy');
        }

        $hotels.hide().filter('[data-page=1]').css('display', 'inline-block');
        var sh_settings = settings.sh;

        if (total_pages) {
            $pagination.twbsPagination({
                totalPages: total_pages,
                visiblePages: 4,
                first: sh_settings.pager_first,
                prev: sh_settings.pager_prev,
                next: sh_settings.pager_next,
                last: sh_settings.pager_last,
                href: 'javascript:void(0);',
                onPageClick: function (event, page) {
                    $hotels.hide().filter('[data-page=' + page + ']').fadeIn(600, function () {
                        $('html, body').animate({
                            scrollTop: $("#pagination").offset().top
                        }, 1000, function () {
                            $(this).stop(true, true);
                        });
                    }).css('display', 'inline-block');
                }
            });
        }
    }

    function sh_created_markers($targets, hotel_google_map, map_settings) {
        var markers = [];
        $targets.each(function () {
            var lat = $(this).data('lat');
            var lng = $(this).data('lng');
            var marker = hotel_google_map.addMarker({
                lat: lat,
                lng: lng,
                infoWindow: {
                    content: $(this).find('.map-hotel-info').html(),
                    maxWidth: 500
                }
            });
            $(this).find('.hotel-detector').on('click', function () {
                if ($(this).hasClass('active')) {
                    hotel_google_map.setCenter(map_settings.latitude, map_settings.longitude);
                    hotel_google_map.setZoom(11);
                    marker.infoWindow.close();
                    $(this).removeClass('active');
                } else {
                    $(this).addClass('active');
                    var marker_lat = marker.position.lat();
                    var marker_lng = marker.position.lng();

                    hotel_google_map.setCenter(marker_lat, marker_lng);
                    hotel_google_map.setZoom(16);

                    $('html, body').animate({
                        scrollTop: $("#page").offset().top
                    }, 1000, function () {
                        $(this).stop(true, true);
                    });

                    setTimeout(function () {
                        marker.infoWindow.open(hotel_google_map.map, marker);
                    }, 1000);
                }
            });
            markers.push(marker);
            $(this).attr('data-marker-index', markers.length - 1);
        });

        return markers;
    }

    function sh_update_markers($targets, markers) {
        var updated_markers = [];
        $targets.each(function () {
            var marker_index = $(this).data('marker-index');
            updated_markers.push(markers[marker_index]);
        });
        return updated_markers;
    }

    function sh_create_marker_cluster(map, markers, options) {
        return new MarkerClusterer(map, markers, options);
    }

    function sh_update_marker_cluster(marker_cl, markers) {
        marker_cl.clearMarkers();
        marker_cl.addMarkers(markers);
    }

})(jQuery);
