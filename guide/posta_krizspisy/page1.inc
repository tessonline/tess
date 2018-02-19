<?php
//echo "smer je $SMER_KRIZ hodnota je ".$GLOBALS['IDPK'];

  if ($GLOBALS['IDPK']>0):
    SetCookie("IDP_KRIZ",0);
//  echo "nastavime".$GLOBALS['IDPK']." x";
    SetCookie("IDP_KRIZ",$GLOBALS['IDPK']);
  endif;  
  
if ($GLOBALS['smer_krize']<>"") {
  SetCookie("SMER_KRIZ",0);
//  echo "nastavime".$GLOBALS['smer_krize']." x";
  SetCookie("SMER_KRIZ",$GLOBALS['smer_krize']);
  }

Form_(array("agenda" => "POSTA","showselect"=>true, "showedit"=>false, "showdelete"=>false, "showguide"=>true));
?>
