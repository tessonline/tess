<?php
require("tmapy_config.inc");
include_once(FileUp2(".admin/brow_.inc"));
include_once(FileUp2("security/.admin/security_func.inc"));
include_once(FileUp2(".admin/el/of_odbory_.inc"));
include_once(FileUp2(".admin/security_name.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2("html_header_title.inc"));

include_once(FileUp2(".admin/db/db_posta.inc"));
//Die(Jsme tam);
    $q = new DB_POSTA;
    If (!$ODBOR) $ODBOR=1;
//    $sql="select u.* FROM security_user u,security_group g,cis_posta_odbory o WHERE g.id=o.id_odbor AND u.group_id=g.id AND o.id=".$ODBOR." ORDER BY lname";
//      $q->query($sql);
    $hodnoty=VratPracovniky(0,1,$ODBOR); //vcetne podrizenych
//    if ($cislo>0)
      $subzak = "<select name=\"VNITRNI_POSTA_REFERENT[".$cislo."]\">";
//    else
//      $subzak = "<select name=\"REFERENT2\">";
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

       var spn = window.parent.document.getElementById("REF2_<?php echo $cislo?>_span");
       if (spn) { spn.innerHTML = '<?php echo $subzak;?>'; }
    //-->
    </script>
    <?php

require(FileUp2("html_footer.inc"));
?>

