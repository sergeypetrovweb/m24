/*
*	Styler number
*/

(function($) {

	$.fn.stylerNumber = function() {
		
		var styler = function() {
			
			var id;
			var min = false;
			var max = false;
			var step = 1;
			var self = $(this);
			
			if (self.attr('id')) {
				id = self.attr('id');
			}
			else {
				return;
			}
			if (self.attr('min')) {
				min = self.attr('min');
			}
			if (self.attr('max')) {
				max = self.attr('max');
			}
			if (self.attr('step')) {
				if (getLengthDecimal(self.attr('step')) >= 0 && getLengthDecimal(self.attr('step')) <= 20) 
				step = Number(self.attr('step'));
				else return;
			}

			function getLengthDecimal(number) {
			    var number = new String(number);
			    var pos = number.indexOf(".");
			    if (pos == -1) return 0;
			    number = number.substr(pos + 1);
			    number = Number(number.length);
			    return number;
			}

			$("[data-for='" + id + "']").on("selectstart", function(even) {
				return false;
			});
			
			$("[data-for='" + id + "']").on("click", function(event) {
				var e = $(this).attr("data-event");
				var f = $(this).attr("data-for");
				if (!f || !e) return false;
				if (e == "sub") {
					var value = Number(self.val());
					var newvalue = Number((value - step).toFixed(getLengthDecimal(step)));
					if (!min) {
						self.val(newvalue);
						self.change();
					}
					else if (newvalue >= min) {
						self.val(newvalue);
						self.change();
					}
				} else if (e == "add") {
					var value = Number(self.val());
					var newvalue = Number((value + step).toFixed(getLengthDecimal(step)));
					if (!max) {
						self.val(newvalue);
						self.change();
					}
					else if (newvalue <= max) {
						self.val(newvalue);
						self.change();
					}
				}
				return false;
			});
		};
		return this.each(styler);
	};
	
})	(jQuery);