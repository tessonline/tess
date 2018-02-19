$(document).ready(function() {
	/*přidání parametrů do url linků*/
	$(".stat_link").click( function() {
		$select=$("select#department option:selected").val();
		$yearfrom=$("input#yearfrom").val();
		$yearto=$("input#yearto").val();
		var _href=$(this).attr("href");	
		$("a.stat_link").attr("href", _href + '&department=' + $select + '&yearfrom=' + $yearfrom + '&yearto=' + $yearto);
		//alert($(".stat_link").attr("href"));
	});
	$('#links').show("slow");
	$('#select_odbor').show("slow");
})
	