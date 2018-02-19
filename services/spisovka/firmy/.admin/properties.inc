<?php
include_once(FileUp2(".config/settings/agenda_path.inc"));
include_once(FileUp2(".admin/db/db_default.inc"));

//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_SQL"] = true;
//$GLOBALS["PROPERTIES_DEBUG"]["SHOW_DEBUG"] = true;
include_once(FileUp2(".admin/db/db_posta.inc"));

$GLOBALS["CONFIG_POSTA"]["ADRESATI"]["TABULKA"]=$GLOBALS["CONFIG_POSTA"]["ADRESATI"]["TABULKA"]?$GLOBALS["CONFIG_POSTA"]["ADRESATI"]["TABULKA"]:'posta';
$PROPERTIES = array(
  "AGENDA_NAME" => "Seznam odesílatelů",
  "AGENDA_TABLE" => "POSTA",
  "AGENDA_ID" => "ID",
  "AGENDA_IDENT" => "POSTA_SEZNAMY_FIRMY",
  "DEFAULT_LANG"=>"cz_utf-8",

  "DB_NAME"=>"db_posta",

  "BROW_PAGE_SIZE" => 100,
    
  "HISTORY_SHOW"=>false,



//  "BROW_SELECT" => "SELECT DISTINCT p.*,s.lname from posta p LEFT JOIN security_user s ON p.referent=s.id WHERE p.CISLO_SPISU1<>'' ",
"BROW_SELECT" => "SELECT DISTINCT ON (p.odesl_prijmeni,p.odes_typ,p.odesl_jmeno,odesl_posta) p.* FROM ".$GLOBALS["CONFIG_POSTA"]["ADRESATI"]["TABULKA"]." p ",

"BROW_SELECT" => "SELECT * FROM
    (SELECT DISTINCT ON (odesl_prijmeni,odes_typ,odesl_jmeno,odesl_ulice,odesl_cp,odesl_posta,frozen,odbor) id,odes_typ,odesl_adrkod,odesl_titul,odesl_prijmeni,odesl_jmeno,odesl_odd,odesl_osoba,odesl_ulice,odesl_cp,odesl_cor,odesl_ico,odesl_psc,odesl_posta,odesl_rc,odesl_email,odesl_datschranka,odesl_datnar from posta WHERE (frozen like 'N' or frozen IS NULL)
    UNION
    SELECT id,odes_typ,odesl_adrkod,odesl_titul,odesl_prijmeni,odesl_jmeno,odesl_odd,odesl_osoba,odesl_ulice,odesl_cp,odesl_cor,odesl_ico,odesl_psc,odesl_posta,odesl_rc,odesl_email,odesl_datschranka,odesl_datnar, 'N' as frozen from posta_adresati) as foo
",
//  "LEFT JOIN  cis_posta_odbory o ON p.odbor=o.id ". 
//  "LEFT JOIN  security_group g ON o.id_odbor=g.id", 

//"BROW_SELECT" => "SELECT * FROM posta  ", 
//  "BROW_FIELD_PREFIX" => "p.",
  "BROW_FIELD_PREFIX" => "",
//  "BROW_ORDER_BY"=>"p.odesl_prijmeni,p.odes_typ,p.odesl_jmeno,odesl_posta DESC",
  "BROW_ORDER_BY"=>"odesl_prijmeni,odes_typ,odesl_jmeno,odesl_posta DESC",

  //po insertu se refreshne okno main
  "INSERT_REFRESH" => true,

  "EDIT_WIDTH" => 790,
  "EDIT_HEIGHT" => 420,
  "EDIT_LEFT" => 10,
  "EDIT_TOP" => 50,

  "DELETE_WIDTH" => 700,
  "DELETE_HEIGHT" => 250,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50

  
  
//  "ACCESS_BY_BROW_SELECT"=>true
);

if ($GLOBALS["CONFIG"]["DB"]=="mssql")
  $PROPERTIES["BROW_SELECT"] = "SELECT p.frozen,p.odesl_prijmeni,p.odesl_adrkod,p.odes_typ,p.odesl_jmeno,odesl_posta,p.odesl_cp,p.odesl_cor,p.odesl_ulice,p.odesl_odd,p.odesl_osoba FROM ".$PROPERTIES["TABULKA"]." p ";
