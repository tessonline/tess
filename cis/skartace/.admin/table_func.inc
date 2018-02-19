<?php
Function ChangeClassBarva_skartace($t)
// staci pustit to zaremovany a barvi se cely radek....
{
	If (!$GLOBALS["AKTIVNI"]==1) $t->classname="gray_line";
	else
	{
		static $i=1;
		if ($i):
		$t->classname = "brow".$color;
		$i = 0;
		else:
		$t->classname = "browdark".$color;
		$i = 1;
		endif;

	}
}

function JIDVS($id) {
	$res = $GLOBALS['CONFIG']['ID_PREFIX'] . 'VS' . $id;
	return $res;
}

function ExportXMLVS($id, $typ) {
		if ($typ == 1)
     		$res = "<a href=\"generate.php?ID=".$id."\"><img src=\"".FileUpImage('images/export')."\" border=\"0\" target=\"ifrm_get_value2\" title=\"Exportovat věcnou skupinu do XML\"></a>";
	    else 
	    	$res = ""; 
     	return $res;
	}

	
	function ShowSkartaceVS($znak, $lhuta, $typ) {
	  if ($typ == 1) $res = '';
	  else  
	  	$res = $znak . '/' . $lhuta;
	  return $res;
	}
  
