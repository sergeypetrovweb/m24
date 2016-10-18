(function ($) {
    $.widget("custom.HRK_Complete", $.ui.autocomplete, {
        _create: function () {
            this._super();
            this.widget().menu("option", "items", "> :not(.ui-autocomplete-category)");
        },
        _renderMenu: function (ul, items) {
            var that = this;
            var current_category = "";

            $.each(items, function (index, item) {
                var $li;

                //create category
                if (item.category != current_category) {
                    var $li_category = $("<li>")
                        .addClass('hrk-autocomplete-category')
                        .html(item.category);
                    ul.append($li_category);
                    current_category = item.category;
                }

                $li = that._renderItemData(ul, item);
                if (item.category) {
                    $li.attr("aria-label", item.category);
                }
            });
        },
        _renderItem: function (ul, item) {
            var $li = $('<li>');
            var $container = $('<a>').addClass('hrk-select-container');

            var $left_child_container = $('<div>')
                .addClass('hrk-left-container')
                .addClass('hrk-left-container-' + item.type)
                .append($('<div>')
                    .addClass('hrk-select-title')
                    .append(item.name)
                    .append($('<span>')
                        .addClass('hrk-select-code')
                        .append('(' + item.code + ')')))
                .append($('<div>').addClass('hrk-select-city').html(item.city));

            var $right_child_container = $('<div>')
                .addClass('hrk-right-container')
                .addClass('hrk-right-container-' + item.type)
                .append($('<div>').addClass('hrk-select-country').html(item.country));

            ul.removeClass('ui-corner-all');

            return $li.attr('data-value', item.code)
                .append($container
                    .append($left_child_container)
                    .append($right_child_container))
                .appendTo(ul);
        }
    });
})(jQuery);