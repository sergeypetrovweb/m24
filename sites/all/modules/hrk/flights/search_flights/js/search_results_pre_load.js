(function ($) {
    Drupal.behaviors.sf_results_pre_loader = {
        attach: function (context, settings) {
          $('#loader_block').addClass('open').addClass('sky');
          setTimeout(
            function() {
              window.location.reload();
            },
            500
          )

        }
    };
})(jQuery);
