(function ($) {
    Drupal.behaviors.hrk_dump = {
        attach: function (context, settings) {

        }
    };


})(jQuery);

function _dump_close_click(that){
    var p=that.parentNode;
    p.className=p.className+" _dump__closed";
}

function _dump_pin_click(that){
    var p = that.parentNode;
    if(/_dump__pin/.test(p.className)){
        p.className=p.className.replace("_dump__pin","");
    }else{
        p.className=p.className+" _dump__pin";
    }
}