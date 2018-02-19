<?php

If ($GLOBALS["ODESL_PRIJMENI"]) {$GLOBALS["ODESL_PRIJMENI"]='*'.$GLOBALS["ODESL_PRIJMENI"].'*';}
//echo "Prijemci ".$PRIJEMCI2;
$where="AND odesl_adresat='p'"; // jde o prijemce

Table(array("agenda" => "POSTA_PRIJEMCI",
  "showedit"=>true,
  "showdelete"=>false,
  "showselect"=>true,
  "multipleselect"=>true,
  "multipleselectsupport"=>true,
  "nopaging"=>true,
  "setvars"=>true,
  "nocaption"=>true,
  "appendwhere"=>$where,
   "action"=>"guide/posta_prijemci/page3.inc",
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
    newwindow = window.open(script, 'Edit2','height=400,width=790,left=0,top=0,scrollbars,resizable');
    newwindow.focus();
  }
//-->
</script>";
echo "<input class='button btn' type='button' onclick=\"javascript:NewWindowX('./services/spisovka/prijemci/edit.php?insert&cacheid=&ODESL_ADRESAT=p');\" value='Přidat odesílatele do seznamu'><br/>";

?>
