<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/oth_funkce.inc"));
include(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/form_func.inc"));
require(FileUp2("html_header_full.inc"));


$VYMAZAT=','.$DEL_ID.',';
$novi=str_replace($VYMAZAT,',',$prijemci);
If ($novi==',') {$novi="";}

If ($zpusob=='p') {$textprijemci=UkazOdesilatele($novi,'a');}
If ($zpusob=='a') {$textprijemci=UkazAdresaty($novi,'a');}


echo "      <script language=\"JavaScript\" type=\"text/javascript\">
  window.parent.document.getElementById('PRIJEMCI_SPAN').innerHTML = '".$textprijemci."';
  window.parent.document.frm_edit.DALSI_PRIJEMCI.value = '".$novi."';
  window.close();
         
      //-->
      </script>
";

?>
