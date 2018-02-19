<?php
require("tmapy_config.inc");
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2(".admin/db/db_default.inc"));
require(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
require(FileUp2(".admin/security_obj.inc"));
require(FileUp2("security/.admin/security_func.inc"));
require(FileUp2(".admin/security_name.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2(".admin/config.inc"));
require(FileUp2("html_header_title.inc"));

//Die(Jsme tam);
    $q = new DB_DEFAULT;
    If (!$ODBOR) $ODBOR=1;
//    $ODBOR=UkazOdbor($ODBOR,0,0,1);
    $hodnoty=VratPracovniky(0,1,$ODBOR); //vcetne podrizenych
//    if ($cislo>0)
//      $subzak = "<select name=\"VNITRNI_POSTA_REFERENT[".$cislo."]\">";
//    else
      $subzak = "<select name=\"REFERENT2\">";
    $opt = "<option value=\"\"></option>"; 
		while (list($key,$val)=each($hodnoty)) {
    if ($GLOBALS["hodnota"]==$key) $add_text=' SELECTED'; else $add_text='';
    $opt .= "<option value=\"".$key."\"$add_text>".$val."</option>";
    }
    if ($opt) 
      $subzak .= $opt."</select>";
//    Die($subzak);
//    $subzak="BLABLABLABLA";
    
    ?>
    <script language="JavaScript" type="text/javascript">
    <!--
//       window.opener.document.frm_edit.REFERENT.value = '<?php echo $subzak;?>';

       var spn = window.parent.document.getElementById("REF_span");
       spn.innerHTML = '<?php echo $subzak;?>';
    //-->
    </script>
    <?php

require(FileUp2("html_footer.inc"));
?>

