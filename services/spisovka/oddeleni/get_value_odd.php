<?php
require("tmapy_config.inc");
include_once(FileUp2(".admin/brow_.inc"));
include_once(FileUp2("security/.admin/security_func.inc"));
include_once(FileUp2(".admin/security_name.inc"));
require(FileUp2("html_header_full.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';


include_once(FileUp2(".admin/db/db_posta.inc"));
//Die(Jsme tam);

    $q = new DB_POSTA;
    If (!$ODBOR) $ODBOR=1;
    $hodnoty=VratOddeleni($ODBOR);
//    $hodnoty=VratOddeleni(UkazOdbor($ODBOR,0,0,1));
    if ($vysledek=='ODDELENI') 
      $add2="onchange=UkazPracovnika(this,\"REFERENT\")";
    else    
      $add2="onchange=UkazPracovnika(this,\"ODESL_PRAC2\")";    
    $subzak = "<select name=\"$vysledek\" $add2><option value=\"\"></option>";
    $opt = ""; 
		while (list($key,$val)=each($hodnoty)) {
      if ($hodnota==$key) $add_text=' SELECTED'; else $add_text='';
      $opt .= "<option value=\"".$key."\"$add_text>".$val."</option>";
    }
    if ($opt) 
      $subzak .= $opt."</select>";
//    Die($subzak);
//    $subzak="BLABLABLABLA";

echo '
    <script language="JavaScript" type="text/javascript">
    <!--
      var spn = window.parent.document.getElementById("'.$vysledek.'");
       if (spn)
      {
         spn.innerHTML = \''.$subzak.'\';
      }

    //-->
    </script>
';
require(FileUp2("html_footer.inc"));
?>

