(function ($) {
    Drupal.behaviors.repeat_search = {
        attach: function (context, settings) {

            var path = Drupal.settings.basePath + Drupal.settings.pathPrefix;

            $('.rs-cross-icon').once(function () {
                $(this).on('click', function () {
                    var index = $(this).data('index');
                    $(this).closest('.rs-unit-wrapper').remove();
                    var ajax = new Drupal.ajax(false, false, {url: path + 'ajax/repeat_search/delete/' + index});
                    ajax.eventResponse(ajax, {})
                });
            });
        }
    };
})(jQuery);
