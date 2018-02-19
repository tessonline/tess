<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
$IDx=$IDP2;
$ID=$GLOBALS["SELECT_ID"];


  $q = new DB_POSTA;

 $sql='SELECT dalsi_prijemci FROM posta WHERE id='.$IDx;
 
 $q->query($sql);
 $q->next_record();
 $prijemci=$q->Record["DALSI_PRIJEMCI"];
 If ($prijemci=="") {$prijemci=",";}
 $retezec=','.$ID.','; 
 
 If (!strstr($prijemci,$retezec)) 
 { $prijemci.=$GLOBALS["SELECT_ID"].",";
   $q = new DB_POSTA;
   $sql="UPDATE posta SET dalsi_prijemci = '".$prijemci."' WHERE id=".$IDx;
   $q->query($sql);
 }

// die($sql);

?>


<script language="JavaScript" type="text/javascript">
<!--
  window.opener.location.reload();
  window.close();
//-->
</script>
<?php
?>
