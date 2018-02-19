<?php
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

$PROPERTIES = array(
  "AGENDA_NAME" => "Adresy",
  "AGENDA_TABLE" => "CIS_POSTA_PRIJEMCI",
//  "AGENDA_TABLE" => "VIEW_POSTA_PRIJEMCI",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_PRIJEMCI",
  "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

 
  "SECURITY_SELECT"=>"SELECT * from VIEW_POSTA_PRIJEMCI",
  "BROW_SELECT"=>"SELECT * from VIEW_POSTA_PRIJEMCI",
  "BROW_ORDER_BY"=>"ODESL_PRIJMENI",

  "INSERT_REFRESH"=>true,
  "DELETE_REFRESH"=>true,
  "EDIT_WIDTH" => 730,
  "EDIT_HEIGHT" => 420,
  "EDIT_LEFT" => 10,
  "EDIT_TOP" => 50,

  "DELETE_WIDTH" => 700,
  "DELETE_HEIGHT" => 250,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50,

  //ARES CONFIG	
	"CONFIG_ARES"=>array(
    "PROXY_HOSTNAME"=>"", //pouzit proxy server
    "PROXY_HOSTNAME_PORT"=>"",
    "FRM_NAME"=>"frm_edit_prijemce", //nazev formu, default je frm_edit
    "TEXT_PRED"=>"TEXT_ARES", //ukecany skript, vraci pres innerhtml text, co dela...
    "OBCHODNI_NAZEV"=>"ODESL_PRIJMENI_FIRMA",  //nazvy poli, ktere se budou vyplnovat.Pokud nechcete vyplnovat nektere udaje, nechte hodnotu prazdnou.
    "ICO"=>"ODESL_ICO",
    "ULICE"=>"ODESL_ULICE",
    "CP"=>"ODESL_CP",
    "COR_CISLO"=>"ODESL_COR",
    "COR_PISMENO"=>"",
    "MESTO"=>"ODESL_POSTA",
    "PSC"=>"ODESL_PSC",
    "ADRESA_KOD"=>"ODESL_ADRKOD",
    "OBEC_KOD"=>"",
    "REJSTRIK"=>"", //z ktereho rejstriku jsou data
  ),

);
?>
