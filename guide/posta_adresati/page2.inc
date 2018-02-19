<?php

If ($GLOBALS["ODESL_PRIJMENI"]) {$GLOBALS["ODESL_PRIJMENI"]='*'.$GLOBALS["ODESL_PRIJMENI"].'*';}
//echo "Prijemci ".$PRIJEMCI2;
$where="AND odesl_adresat='a' and odes_typ<>'X'"; // jde o prijemce


Table(array("agenda" => "POSTA_PRIJEMCI",
  "showedit"=>"edit='1'",
  "showdelete"=>false,
  "showselect"=>true,
  "multipleselect"=>true,
  "multipleselectsupport"=>true,
  "nopaging"=>true,
  "nocaption"=>true,
  "setvars"=>true,
  "appendwhere"=>$where,
   "action"=>"guide/posta_adresati/page3.inc",
));
  /*
Table(array("agenda" => "POSTA_PRIJEMCI", "showedit"=>true, 
"showdelete"=>false, "showguide"=>true,"multipleselect"=>true,"showselect"=>true,
"multipleselectsupport"=>true,"nomultipleselectbuttons"=>false,
"nopaging"=>true,"action"=>"guide/posta_prijemci/page3.inc"));
//, "showselect"=>true
*/
echo "<script>
<!--
  function NewWindowX(script) {
    newwindow = window.open(script, 'Edit','height=400,width=790,left=0,top=0,scrollbars,resizable');
    newwindow.focus();  }
//-->
</script>";
echo "<input class='button btn' type='button' onclick=\"javascript:NewWindowX('./services/spisovka/prijemci/edit.php?insert&cacheid=&ODESL_ADRESAT=a');\" value='Přidat adresáta do seznamu'><br/>";

?>
