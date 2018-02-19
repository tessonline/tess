<?php
$hod=$hodnota;
require("tmapy_config.inc");
include_once(FileUp2(".admin/brow_.inc"));
include_once(FileUp2("security/.admin/security_func.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2(".admin/el/of_odbory_.inc"));
require(FileUp2("html_header_full.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';


include_once(FileUp2(".admin/db/db_posta.inc"));

$hodnota=$hod;
    $q = new DB_POSTA;
    If (!$ODBOR) $ODBOR=1;
//    $sql='SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id='.$ODBOR.' ORDER BY g.name';
    $hodnoty=VratSpisUzly($ODBOR);

    if ($vysledek=='ODBOR' or $vysledek=='ODBOR2') 
      $add2="onchange=UkazPracovnika(this,\"REFERENT\")";
    else    
      $add2="onchange=UkazPracovnika(this,\"ODESL_PRAC2\")";    

    $subzak = "<select name=\"$vysledek\" $add2><option value=\"\"></option>";
    $opt = ""; 

echo " hodnota je ".$hodnota;
		while (list($key,$val)=each($hodnoty)) {
      $key=VratOdbor($key);
      if ($hodnota==$key) $add_text=' SELECTED'; else $add_text=''; //id<20 aby se nenastavoval odbor
      $opt .= "<option value=\"".$key."\"$add_text>".$val."</option>";
    }
    if ($opt) 
      $subzak .= $opt."</select>";


echo '
    <script language="JavaScript" type="text/javascript">
    <!--
     // var spn = window.parent.document.getElementById("'.$vysledek.'");
      var spn = window.parent.document.getElementsByName("'.$vysledek.'")[0];
      if (spn) {
         spn.innerHTML = \''.$subzak.'\';
      } 
      //var spn = window.parent.document.getElementById("'.$vysledek.'2");
      var spn = window.parent.document.getElementsByName("'.$vysledek.'2")[0];
      if (spn) {
         spn.innerHTML = \''.$subzak.'\';
      } 
    //-->
    </script>
';
require(FileUp2("html_footer.inc"));
?>

