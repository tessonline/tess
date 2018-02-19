<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/config.inc"));
require_once(Fileup2("html_header_title.inc"));
Flush();
include_once(FileUp2(".admin/security_obj.inc")); 
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];

if (!$EDIT_ID && !$DELETE_ID) $is_insert = true;
if ($EDIT_ID) $is_edit = $EDIT_ID;
if ($DELETE_ID) $is_delete = $DELETE_ID;
//die($NAZEV_SPISU);
/*
if ($is_insert)
$DATUM_PODATELNA_PRIJETI = Date('d.m.Y')." ".Date('H:m:s');
*/

if ($GLOBALS["ODES_TYP"] == 'A' ||$GLOBALS["ODES_TYP"] == 'V' ||$GLOBALS["ODES_TYP"] == 'Z') $GLOBALS["ODESL_PRIJMENI"] = $GLOBALS["ODESL_PRIJMENI_NAZEV"];
if ($GLOBALS["ODES_TYP"] == 'P' ||$GLOBALS["ODES_TYP"] == 'U')
{
  $GLOBALS["ODESL_PRIJMENI"] = $GLOBALS["ODESL_PRIJMENI_FIRMA"];
  $GLOBALS["ODESL_JMENO"] = ""; $GLOBALS["ODESL_DATNAR"] = "";
}
  if (strlen($GLOBALS[VEC])>254) $GLOBALS[VEC] = substr($GLOBALS[VEC],0,254);
  if (strlen($GLOBALS[ODESL_PRIJMENI])>99) $GLOBALS[ODESL_PRIJMENI] = substr($GLOBALS[ODESL_PRIJMENI],0,99);


if ($GLOBALS['OLD_REFERENT']>0 && $GLOBALS['REFERENT']>0 && $GLOBALS['OLD_REFERENT']<>$GLOBALS['REFERENT'])
{
  $pole = OdborPrac($GLOBALS['REFERENT']);
  $GLOBALS['ODBOR'] = $pole['odbor'];
  $GLOBALS['ODDELENI'] = $pole['oddeleni'];

}



Run_(array("outputtype"=>3));

require_once(Fileup2("html_footer.inc"));  

?>

