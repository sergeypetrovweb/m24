(function ($) {


    $(document).ready(function(){
        // executes when HTML-Document is loaded and DOM is ready

        $('.headroom').headroom();

        $("#off-menu").mmenu({
            "extensions": [
                "border-full"
            ],
            "offCanvas": {
                "zposition": "front",
                "position": "right"
            },
            "navbar": {
                add: false,
                title: ""
            }
        });

        var mmenu_api = $("#off-menu").data( "mmenu" );

        $("#mm-close-button").click(function() {
            mmenu_api.close();
        });

    });

    $(window).load(function() {
        // executes when complete page is fully loaded, including all frames, objects and images

    });

    $(window).on('resize', function() {

    });
})(jQuery);