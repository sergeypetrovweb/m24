(function ($) {
    $.widget("custom.HRK_Spinner", $.ui.spinner, {
        _buttonHtml: function () {
            var max = this.options.max,
                min = this.options.min,
                value = $(this.element).val();

            var up_button = $('<a>')
                .addClass('ui-spinner-button ui-spinner-up ui-corner-tr')
                .append($('<span>').addClass('ui-icon ' + this.options.icons.up).html('+'));

            if (max != null && value >= max) {
                up_button.addClass('disabled');
            }

            var down_button = $('<a>')
                .addClass('ui-spinner-button ui-spinner-down ui-corner-br')
                .append($('<span>').addClass('ui-icon ' + this.options.icons.down).html('-'));

            if (min != null && value <= min) {
                down_button.addClass('disabled');
            }

            return up_button.prop('outerHTML') + down_button.prop('outerHTML');
        }
    });
})(jQuery);

