<?php
require("tmapy_config.inc");
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2("html_header_title.inc"));

include_once(FileUp2(".admin/db/db_posta.inc"));
//Die(Jsme tam);
    $q = new DB_POSTA;
    If (!$ODBOR) $ODBOR=1;
    $sql="select u.* FROM security_user u,security_group g,cis_posta_odbory o WHERE g.id=o.id_odbor AND u.group_id=g.id AND o.id=".$ODBOR." ORDER BY lname";
      $q->query($sql);
    $subzak = "<select name=\"REFERENT2\"><option value=\"\"></option>";
    $opt = ""; 
		while ($q->next_record()) {
      $opt .= "<option value=\"".$q->Record["ID"]."\">".$q->Record["LNAME"]." ".$q->Record["FNAME"]."</option>";
    }
    if ($opt) 
      $subzak .= $opt."</select>";
//    Die($subzak);
//    $subzak="BLABLABLABLA";
    
    ?>
    <script language="JavaScript" type="text/javascript">
    <!--
//       window.opener.document.frm_edit.REFERENT.value = '<?php echo $subzak;?>';

       var spn = window.parent.document.getElementById("REF2_span");
       spn.innerHTML = '<?php echo $subzak;?>';
    //-->
    </script>
    <?php

require(FileUp2("html_footer.inc"));
?>

