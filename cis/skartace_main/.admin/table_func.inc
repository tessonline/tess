<?php

function JIDPlan($id) {
	$res = $GLOBALS['CONFIG']['ID_PREFIX'] . 'SPISPLAN' . $id;
	return $res;
}
function ExportXML($id) {
  $res = "<a href=\"generate.php?ID=0&MAIN_ID=".$id."\"><img src=\"".FileUpImage('images/export')."\" border=\"0\" target=\"ifrm_get_value2\" title=\"Exportovat spisový plán do XML\"></a>";
  return $res;
}

function ImportXML($id) {
	$res = "<a href=\"#\" onclick=\"NewWindow('edit.php?insert&app=import&ID=".$id."');\"><img src=\"".FileUpImage('images/import')."\" border=\"0\" target=\"ifrm_get_value2\" title=\"Importovat spisový plán z XML\"></a>";
	return $res;
}

function ShowStrom($id) {
	$res = "<a href=\"strom.php?ID=".$id."\"><img src=\"".FileUpImage('images/move')."\" border=\"0\" target=\"ifrm_get_value2\" title=\"Zobrazit stromovou strukturu\"></a>";
	return $res;
}

NewWindow(array("fname"=>"", "name"=>"pf_parc_new", "header"=>true, "cache"=>false, "window"=>"edit"));


?>
<iframe id="ifrm_get_value2" name="ifrm_get_value2" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden"></iframe>
