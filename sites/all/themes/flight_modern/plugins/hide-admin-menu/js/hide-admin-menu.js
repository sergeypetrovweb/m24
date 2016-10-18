(function($) {
    $.fn.hideAdminMenu = function() {
        var selectedObject = this;

        selectedObject.prepend('<div id="admin-switch" class="plus">+</div>');
        selectedObject.find('#admin-switch').click(function() {
            var state = $(this).attr('class');

            if (state == 'plus') {
                $(this).text('-');
                $('#admin-menu').show();

                $(this).removeClass(state);
                $(this).addClass('minus');
            } else {
                $(this).text('+');
                $('#admin-menu').hide();

                $(this).removeClass(state);
                $(this).addClass('plus');
            }
        });

        return selectedObject;
    };
    $(document).ready(function(){
        $('body.admin-menu').hideAdminMenu();
    });
})(jQuery);