<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
//require(FileUp2("html_header_full.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2("html_header_title.inc"));

include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/security_name.inc"));
//Die(Jsme tam);
    $q = new DB_POSTA;
    If (!$ODBOR) $ODBOR=1;
    $sql="SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=".UkazOdbor($ODBOR,0,0,1)." ORDER BY g.name";
    echo $sql;
      $q->query($sql); //<option value=\"\"></option>
    $subzak = "<select name=\"ODBOR2\" onChange=\"ChangeZakazka(this)\">";
    $opt = ""; 
		while ($q->next_record()) {
      $opt .= "<option value=\"".$q->Record["ID"]."\">".$q->Record["NAME"]."</option>";
    }
    if ($opt) 
      $subzak .= $opt."</select>";
//    Die($subzak);
//    $subzak="BLABLABLABLA";
    
    ?>
    <script language="JavaScript" type="text/javascript">
    <!--
//       window.opener.document.frm_edit.ODBOR2.value = '<?php echo $subzak;?>';

       var spn = window.parent.document.getElementById("ODBOR2_span");
       spn.innerHTML = '<?php echo $subzak;?>';
    //-->
    </script>
    <?php

require(FileUp2("html_footer.inc"));
?>

