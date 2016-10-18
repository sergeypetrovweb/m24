(function ($) {
    // Parameter - form id (html attr id)
    function makePopupAjaxed(formId) {
        var ajax_element_settings_defaults = {
            url: '/ajax_forms_ajax',
            event: 'mousedown',
            prevent: 'click',
            keypress: false,
            selector: '#' + formId + ' .form-submit',
            effect: 'none',
            speed: 'none',
            method: 'replaceWith',
            /*wrapper: '',*/
            progress: {
                type: 'throbber',
                message: ''
            },
            submit: {
                'js': true
            }
        };

        var element_settings = ajax_element_settings_defaults;

        if (typeof(Drupal.settings.ajax) != 'object') {
            Drupal.settings.ajax = new Object();
        }

        Drupal.settings.ajax[formId + ' .form-submit'] = element_settings;
        Drupal.behaviors.AJAX.attach(null, Drupal.settings);
    }

    $(document).ready(function () {
        if ($.fancybox) {
            $('a.modal').fancybox({
                'padding': 44,
//                'wrapCSS': 'modal-webform-fancy',
                afterShow: function () {
                    makePopupAjaxed($('.fancybox-inner form').attr('id'));
                }
            });
        }
    });
}(jQuery));