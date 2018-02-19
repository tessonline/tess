<?php
$hod=$hodnota;
require("tmapy_config.inc");
include_once(FileUp2(".admin/oth_funkce_2D.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2("html_header_full.inc"));

$agenda = VratAgenduDokumentu($TYP_POSTY);
?>

<script language="JavaScript" type="text/javascript">
if ("<?php echo $agenda; ?>" != "") 
	$("[name='<?php echo $vysledek; ?>']",parent.document).val(<?php echo $agenda; ?>).attr("selected", "selected"); 
	else 
	$("[name='<?php echo $vysledek; ?>']",parent.document).prop("selectedIndex", 0);

var text = $("#<?php echo $vysledek; ?> option[value='<?php echo $agenda ?>']", parent.document).text();
$('.select2-selection__rendered', parent.document).prop("title",text);
$('.select2-selection__rendered', parent.document).text(text);

</script>

<?php 

require(FileUp2("html_footer.inc"));
?>

