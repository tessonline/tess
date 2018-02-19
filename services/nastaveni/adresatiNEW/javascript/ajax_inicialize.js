	$(document).ready(function() {
		$(".active").click(function() { 
			$id = this.id;
			$.post("ajax.php", { id: $id}, function(data) {
				$('#'+$id).empty();
				$('#'+$id).append(data);
			});
		});
	});