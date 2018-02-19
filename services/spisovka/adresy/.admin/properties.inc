<?php
//include(GetAgendaPath('UIRADR_INDEX')."/.admin/config.inc");
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true; 

$PROPERTIES = array(
  "AGENDA_NAME" => "Adresa",
  "AGENDA_TABLE" => "adresa",
  "AGENDA_CHECK" => "ADRESA_KOD",
  "AGENDA_ID" => "ADRESA_KOD",
  "AGENDA_IDENT" => "POSTA_UIRADR",
  "DB_NAME"=>"DB_POSTA",

  "DEFAULT_LANG"=>$CONFIG["DEFAULT_LANG"],

  "INSERT_REFRESH" => true,

  "GUIDE_WIDTH" => 700,
  "GUIDE_HEIGHT" => 550,
  "GUIDE_LEFT" => 10,
  "GUIDE_TOP" => 30,

//  "BROW_SELECT" => "select a.STAV, a.ADRESA_KOD, a.OBJEKT_KOD, a.ULICE_KOD, a.CISOR_HOD, a.CISOR_PIS, a.PSC, u.NAZEV as ULICE, j.CISDOM_TYP, j.CISDOM_HOD, c.NAZEV as COBCE, c.COBCE_KOD, za.zatopa from ".$GLOBALS["CONFIG"]["TABLE_PREFIX"]."adresa a, ".$GLOBALS["CONFIG"]["TABLE_PREFIX"]."ulice u, ".$GLOBALS["CONFIG"]["TABLE_PREFIX"]."objekt j, ".$GLOBALS["CONFIG"]["TABLE_PREFIX"]."cobce c, ".$GLOBALS["CONFIG"]["TABLE_PREFIX"]."adr_kod_zatopa za WHERE (a.ulice_kod = u.ulice_kod ) and (a.objekt_kod = j.objekt_kod)and (j.cobce_kod = c.cobce_kod) and (a.adresa_kod=za.adresa_kod) and a.stav <> 3",
/*
  "BROW_SELECT" => "SELECT a.stav, a.adresa_kod, a.objekt_kod, a.ulice_kod, a.cisor_hod, a.cisor_pis, a.psc, u.nazev as ulice, j.cisdom_typ, j.cisdom_hod, c.nazev as cobce, c.cobce_kod, o.nazev as obec, o.obec_kod".
                   " FROM ui_adresa a ".
                   " LEFT JOIN ui_ulice u ON (a.ulice_kod = u.ulice_kod )".
                   " LEFT JOIN ui_objekt j ON (a.objekt_kod = j.objekt_kod)".
                   " LEFT JOIN ui_cobce c ON (j.cobce_kod = c.cobce_kod)".
                   " LEFT JOIN ui_obec o ON (o.obec_kod = c.obec_kod)".
                   " WHERE  j.cisdom_typ=1",
  */
//
  "BROW_SELECT" => "SELECT a.STAV, a.ADRESA_KOD, a.OBJEKT_KOD, a.ULICE_KOD, a.CISOR_HOD, a.CISOR_PIS, a.PSC, ". 
    "j.CISDOM_TYP, j.CISDOM_HOD, c.NAZEV as COBCE, c.COBCE_KOD FROM ui_adresa a, ui_objekt j,ui_cobce c,ui_obec o",

  "BROW_ORDER_BY"=>"ADRESA_KOD ",
  "BROW_FIELD_PREFIX" => "a.",

  "DELETE_LEFT"=>20,
  "DELETE_TOP"=>20,
  "DELETE_HEIGHT"=>250,
  "DELETE_WIDTH"=>600,

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>500,
  "EDIT_WIDTH"=>590,

//  "EDIT_BUTTONS_UP"=>true


);

If ($GLOBALS["ULICE"]<>"") 
{
  $PROPERTIES = array(
  "BROW_SELECT" => "SELECT a.STAV, a.ADRESA_KOD, a.OBJEKT_KOD, a.ULICE_KOD, a.CISOR_HOD, a.CISOR_PIS, a.PSC, u.NAZEV as ULICE, ". 
    "j.CISDOM_TYP, j.CISDOM_HOD, c.NAZEV as COBCE, c.COBCE_KOD FROM ui_adresa a, ui_objekt j,ui_cobce c,ui_obec o,ui_ulice u",
  "BROW_ORDER_BY"=>"ULICE ASC, CISOR_HOD ASC, CISOR_PIS ASC",
  "BROW_FIELD_PREFIX" => "a.",
    
    );
  }                   

?>
