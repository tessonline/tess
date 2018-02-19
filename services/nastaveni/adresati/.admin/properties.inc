<?php
include_once(FileUp2('.admin/config.inc'));

$PROPERTIES = array(
  "AGENDA_NAME" => "Nastavení adresátů",
  'AGENDA_TABLE' => 'posta_adresati',
  'AGENDA_ID' => 'ID',
  'AGENDA_IDENT' => 'POSTA_NASTAVENI_ADRESATI',//'POSTA_NASTAVENI_ADRESATI',   "DB_NAME" => "db_posta",
  "DEFAULT_LANG"=>"cz_utf-8",

  "INSERT_REFRESH"=>true,
  /*
  "BROW_SELECT" =>"
    select odes_typ,odesl_adrkod,odesl_prijmeni,odesl_jmeno,odesl_odd,odesl_osoba,
    odesl_titul,odesl_ulice,odesl_cp,odesl_cor,odesl_ico,odesl_psc,odesl_posta,
    count(*) as pocet  
    from posta
    where odesl_prijmeni ilike 'ČESKÝ RYBÁŘSKÝ SVAZ výbor územního svazu pro SMaS%'
  ",
  */
  "ACCESS_IDENT" => "POSTA_CISELNIKY",

  "BROW_SELECT" =>"
    select 
    p.odes_typ, p.odesl_adrkod,
    coalesce(p.odesl_prijmeni,'') as odesl_prijmeni,
    coalesce(p.odesl_jmeno,'') as odesl_jmeno, coalesce(p.odesl_odd,'') as odesl_odd,
    coalesce(p.odesl_osoba,'') as odesl_osoba, coalesce(p.odesl_titul,'') as odesl_titul,
    coalesce(p.odesl_ulice,'') as odesl_ulice, coalesce(p.odesl_cp,'') as odesl_cp,
    coalesce(p.odesl_cor,'') as odesl_cor, coalesce(p.odesl_ico,'') as odesl_ico,
    coalesce(p.odesl_psc,'') as odesl_psc, coalesce(p.odesl_posta,'') as odesl_posta,
    coalesce(p.odesl_datschranka,'') as odesl_datschranka,
    count(p.*) as pocet, p.frozen, count(*) as pocet
    from posta p
    where p.odes_typ<>'A' and p.odes_typ<>'V' and p.odes_typ<>'Z' 
  ",
//    p.referent, 

//    su.lname||' '||su.fname as n_referent,
//    left join security_user su on su.id = p.referent
  
  "BROW_SELECT" => "
    SELECT DISTINCT ON (p.odesl_prijmeni,p.odes_typ,p.odesl_jmeno,p.odesl_ulice,p.odesl_cp,odesl_posta,frozen) p.* FROM posta p WHERE p.odes_typ<>'A' AND p.odes_typ<>'X' and p.odes_typ<>'V' and p.odes_typ<>'Z' AND p.odes_typ<>'S' 
   ",

//   "BROW_SELECT" => "
//     SELECT DISTINCT ON (odesl_prijmeni,odes_typ,odesl_jmeno,odesl_ulice,odesl_cp,odesl_posta,frozen,odbor) id,odes_typ,odesl_adrkod,odesl_titul,odesl_prijmeni,odesl_jmeno,odesl_odd,odesl_osoba,odesl_ulice,odesl_cp,odesl_cor,odesl_ico,odesl_psc,odesl_posta,odesl_rc,odesl_email,odesl_datschranka,odesl_datnar,'0' as adresar from posta
//     UNION
//     SELECT id,odes_typ,odesl_adrkod,odesl_titul,odesl_prijmeni,odesl_jmeno,odesl_odd,odesl_osoba,odesl_ulice,odesl_cp,odesl_cor,odesl_ico,odesl_psc,odesl_posta,odesl_rc,odesl_email,odesl_datschranka,odesl_datnar,'1' as adresar from posta_adresati
//
//     WHERE odes_typ<>'A' AND odes_typ<>'X' and odes_typ<>'V' and odes_typ<>'Z' AND odes_typ<>'S'
//
//   ",
  
  "BROW_FIELD_PREFIX" => "",
  "BROW_ORDER_BY"=>"odesl_prijmeni,odes_typ,odesl_jmeno,odesl_posta DESC",


//  "BROW_ORDER_BY"=>"count(p.*) desc",
//  "BROW_GROUP_BY"=>"odes_typ,odesl_adrkod,odesl_prijmeni,odesl_jmeno,odesl_odd,odesl_osoba,odesl_titul,odesl_ulice,odesl_cp,odesl_cor,odesl_ico,odesl_psc,odesl_posta having count(*)=30",
//  "BROW_GROUP_BY"=>"odes_typ,odesl_adrkod,odesl_prijmeni,odesl_jmeno,odesl_odd,odesl_osoba,odesl_titul,odesl_ulice,odesl_cp,odesl_cor,odesl_ico,odesl_psc,odesl_posta",
/*
  "BROW_GROUP_BY"=>"
    p.odes_typ, p.odesl_adrkod,
    coalesce(p.odesl_prijmeni,''),
    coalesce(p.odesl_jmeno,''), coalesce(p.odesl_odd,''),
    coalesce(p.odesl_osoba,''), coalesce(p.odesl_titul,''),
    coalesce(p.odesl_ulice,''), coalesce(p.odesl_cp,''),
    coalesce(p.odesl_cor,''), coalesce(p.odesl_ico,''),
    coalesce(p.odesl_psc,''), coalesce(p.odesl_posta,''),
    coalesce(p.odesl_datschranka,''),
    p.frozen
  ",
//    p.referent, 
*/
/*
  "BROW_GROUP_BY"=>"
    p.odes_typ,
    coalesce(p.odesl_prijmeni,''),
    coalesce(p.odesl_jmeno,''),
    coalesce(p.odesl_psc,''), 
    p.referent, 
    p.frozen
  ",
*/
//SELECT DISTINCT ON (p.odesl_prijmeni,p.odes_typ,p.odesl_jmeno,odesl_posta)
//    su.lname||' '||su.fname, 

  "EDIT_LEFT"=>20,
  "EDIT_TOP"=>20,
  "EDIT_HEIGHT"=>200,
  "EDIT_WIDTH"=>750,

  "DELETE_HEIGHT" => 300,
  "DELETE_WIDTH" => 600,
  "DELETE_LEFT" => 50,
  "DELETE_TOP" => 50
);
if (!$GLOBALS["QUERY_STRING"] || $GLOBALS["QUERY_STRING"]=="frame")
  $PROPERTIES["MAIN_WINDOW"] = "edit.php?filter";

if ($GLOBALS['FROZEN']<>'D')
  $PROPERTIES['BROW_SELECT'] .= "AND p.frozen<>'D'";
