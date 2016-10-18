(function ($) {
    jQuery.fn.equalHeights = function() {
        var currentTallest = 0;
        $(this).css({'min-height': 'inherit'});
        $(this).each(function(){
            if ($(this).outerHeight() > currentTallest) { currentTallest = $(this).outerHeight(); }
        });
        $(this).css({'min-height': currentTallest});
        return this;
    };
})(jQuery);