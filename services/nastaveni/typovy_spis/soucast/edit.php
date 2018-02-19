<?php
require("tmapy_config.inc");

require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));

echo '<iframe id="ifrm_get_value" name="ifrm_get_value" style="position:absolute;z-index:0;left:10;top:10;visibility:hidden"></iframe>';
  echo "<script>

  function UkazSkartacniRezim(skartace) {
    newwindow =   window.open('" . GetAgendaPath('POSTA',false,true). "/services/spisovka/oddeleni/get_value_rezim.php?SKARTACE_ID='+skartace.value+'','ifrm_get_value','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  }
  ";
  if ($GLOBALS['SKARTACE_ID']>0) {
    echo "UkazSkartacniRezim(document.frm_edit.SKARTACE_ID);";
  }

  echo "</script>";

Form_(array("showaccess"=>true, "nocaption"=>false));
require(FileUp2("html_footer.inc"));
