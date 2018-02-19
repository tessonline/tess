<?php
$hod=$hodnota;
require("tmapy_config.inc");
include_once(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/oth_funkce_2D.inc"));
require(FileUp2("html_header_full.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';


include_once(FileUp2(".admin/db/db_posta.inc"));

//$GLOBALS['agenda'] = getSelectDataEed(new of_select_agenda_dokumentu(array("superodbor"=>$SODBOR)));


/*function ukazTyp($typ_id) {
  $ret = $GLOBALS['agenda'][$typ_id];
  if (!$ret) $ret = $typ_id;
  return $ret;
}*/

    $q = new DB_POSTA;


    $hodnoty=vratFiltrovaneAgendy($SODBOR);
    $add2 = "";
    $add2="UkazTypPosty(this,\'TYP_POSTY\',\'\',\'\',1);";    

    $subzak = "<select name=\"$vysledek\" onChange=\"$add2\">";
    $opt = ""; 

		while (list($key,$val)=each($hodnoty)) {
      $opt .= "<option value=\"".$key."\">".$val."</option>";
    }
    if ($opt) 
    $subzak .= $opt."</select>";

echo '
    <script language="JavaScript" type="text/javascript">
    <!--
    var spn = window.parent.document.getElementsByName("'.$vysledek.'")[0];
      if (spn) {
         spn.innerHTML = \''.$subzak.'\';
      } 
    //-->
    </script>
';
require(FileUp2("html_footer.inc"));
?>

