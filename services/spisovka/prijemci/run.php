<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/security_name.inc"));
//require(FileUp2(".admin/security_.inc"));
require_once(Fileup2("html_header_title.inc"));

if ($GLOBALS["ODES_TYP"]=='A' ||$GLOBALS["ODES_TYP"]=='V' ||$GLOBALS["ODES_TYP"]=='Z') $GLOBALS["ODESL_PRIJMENI"]=$GLOBALS["ODESL_PRIJMENI_NAZEV"];
if ($GLOBALS["ODES_TYP"]=='P' ||$GLOBALS["ODES_TYP"]=='U') $GLOBALS["ODESL_PRIJMENI"]=$GLOBALS["ODESL_PRIJMENI_FIRMA"];

if ($GLOBALS["ODES_TYP"]=='S')
{
  $add_text=$GLOBALS["ODESL_TITUL"]==1?"Město ".$GLOBALS["CONFIG"]["MESTO"]:$GLOBALS["CONFIG"]["URAD"]." ".$GLOBALS["CONFIG"]["MESTO"];
  $GLOBALS["ODESL_PRIJMENI"]=UkazOdbor($GLOBALS["ODESL_ODBOR"]);
  $GLOBALS["ODESL_JMENO"]=UkazUsera($GLOBALS["ODESL_PRAC2"]);
  $GLOBALS["ODESL_TITUL"]=$GLOBALS["ODESL_URAD"];
  $GLOBALS["ODESL_ULICE"]=$GLOBALS["ODESL_ODBOR"];
  $GLOBALS["ODESL_ODD"]=$GLOBALS["ODESL_ODD2"];
  $GLOBALS["ODESL_OSOBA"]=$GLOBALS["ODESL_PRAC2"];
}

Run_(array("showaccess"=>true,"outputtype"=>3));
require_once(Fileup2("html_footer.inc"));  

?>
  
