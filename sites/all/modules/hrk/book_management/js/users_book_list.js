(function ($) {
    Drupal.behaviors.user_book_list = {
        attach: function (context, settings) {
            var hash = user_book_list_get_table();

            if(hash == '.flight-row')  $('.user-table.user-hotels').hide();
            if(hash == '.hotel-row')  $('.user-table.user-flights').hide();

            /*Hotels and flights mixItUp*/
            var $mix_wr = $('.user-table-body-hotels, .user-table-body-flights');
            $mix_wr.mixItUp({
                selectors: {
                    target: '.mix'
                },
                load: {
                    sort: 'created:desc',
                    filter: hash
                },
                layout: {
                    display: 'block'
                }
            });

            /*FILTERS*/
            $('#switcher input').on('click', function() {
                var show = $(this).data('type');
                var mix_up = {};
                mix_up.filter = show;
                $('.select_style.filtering select').val('all');
                $('.select_style.ordering select').val('default');

                if (show == '.flight-row') {
                    $('.user-table.user-hotels').hide();
                    $('.user-table.user-flights').show();
                }
                if (show == '.hotel-row') {
                    $('.user-table.user-hotels').show();
                    $('.user-table.user-flights').hide();
                }

                $mix_wr.mixItUp('multiMix', mix_up);
            });

            $('.filter_account .select_style select').on('change', function () {
                var data_filter = $('.select_style.filtering select').find(':selected').data('filter');
                var data_sort = $('.select_style.ordering select').find(':selected').data('sort');
                var mix_up = {};

                //GET FILTERS
                mix_up.filter = data_filter;
                if (mix_up.filter == 'all') {
                    mix_up.filter = user_book_list_get_table();
                } else {
                    mix_up.filter += user_book_list_get_table();
                }

                //GET SORT
                mix_up.sort = data_sort;
                $mix_wr.mixItUp('multiMix', mix_up);
            });
        }
    };

    function user_book_list_get_table() {
        return $('#switcher input.active').data('type');
    }
})(jQuery);
