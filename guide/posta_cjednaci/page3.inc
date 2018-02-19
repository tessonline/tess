<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
require(FileUp2("html_header_full.inc"));



$ID=$GLOBALS["SELECT_ID"];
//echo "IPD".$IDPcko;

$q = new DB_POSTA;

$sql='SELECT odbor,ev_cislo,rok,cislo_jednaci1,cislo_jednaci2,znacka,cislo_spisu1,cislo_spisu2,nazev_spisu,skartace FROM posta WHERE id='.$ID;


Table(array(
  "sql"=>"select * from posta where id=".$ID,
  "agenda"=>"POSTA_C_JEDNACI",
  "caption"=>"Vybraná písmenost",
  "showaccess"=>false, 
  "showinfo"=>false,
  "showedit"=>false,
  "showdelete"=>false,
  "showhistory"=>false,
//  "setvars"=>true,
   ));
$q->query($sql);
$q->next_record();
$EV_CISLO=$q->Record["EV_CISLO"];
$ROK=$q->Record["ROK"];
$ODBOR=$q->Record["ODBOR"];
$CISLO_JEDNACI1=$q->Record["CISLO_JEDNACI1"];
$CISLO_JEDNACI2=$q->Record["CISLO_JEDNACI2"];
$CISLO_SPISU1=$q->Record["CISLO_SPISU1"];
$CISLO_SPISU2=$q->Record["CISLO_SPISU2"];
$ZNACKA=$q->Record["ZNACKA"];
$SKARTACE=$q->Record["SKARTACE"];
$NAZEV_SPISU=$q->Record["NAZEV_SPISU"];
$ID_PUVODNI=$ID;

$text_spisu=$CISLO_SPISU1."/".$CISLO_SPISU2;
If ($NAZEV_SPISU) $text_spisu.=" - ".$NAZEV_SPISU;
$text_spisu.=" ";

include_once(FileUp2(".admin/security_name.inc"));
$zkratka=UkazOdbor($ODBOR,true);


//echo "$CISLO_SPISU1 $CISLO_SPISU2";

$adresa='aaaaa';
//die("aa".$ID_PUVODNI."aa");
$OBJEKT_KOD=$ID;

$add_checkbox="<input type=\"checkbox\" name=\"KOPIE_SOUBORU\" value=\"$ID\" CHECKED>&nbsp;Zkopírovat přiložené soubory<br/>";

?>
<script language="JavaScript" type="text/javascript">
<!--
  window.opener.document.frm_edit.ZNACKA.value = '<?php echo $ZNACKA;?>';
  window.opener.document.frm_edit.CISLO_JEDNACI1.value = '<?php echo $CISLO_JEDNACI1;?>';
  window.opener.document.frm_edit.CISLO_JEDNACI2.value = '<?php echo $CISLO_JEDNACI2;?>';
  if (!window.opener.document.frm_edit.CISLO_SPISU1.value)
  {
//    alert(window.opener.document.frm_edit.CISLO_SPISU1.value);
    window.opener.document.frm_edit.CISLO_SPISU1.value = '<?php echo $CISLO_SPISU1;?>';
    window.opener.document.frm_edit.CISLO_SPISU2.value = '<?php echo $CISLO_SPISU2;?>';
    window.opener.document.frm_edit.NAZEV_SPISU.value = '<?php echo $NAZEV_SPISU;?>';
    window.opener.document.frm_edit.SKARTACE.value = '<?php echo $SKARTACE;?>';
    window.opener.document.getElementById('OBJEKT_KOD_SPAN').innerHTML = '<?php echo $text_spisu ?>';
  }
  window.opener.document.getElementById('CJEDNACI_KOD_SPAN').innerHTML = '<?php echo $add_checkbox."ČJ: ".$CISLO_JEDNACI1."/".$CISLO_JEDNACI2;?>';
  window.close();
//-->
</script>


