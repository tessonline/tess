<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/security_name.inc"));
require(FileUp2(".admin/status.inc"));
require_once(Fileup2("html_header_title.inc"));

$w=new DB_POSTA;
if (!$GLOBALS['REFERENT']) $GLOBALS['REFERENT'] = $GLOBALS['REFERENT2'];
if (!$GLOBALS['REFERENT']) $GLOBALS['REFERENT'] = "NULL";

$EedUser = LoadClass('EedUser', 0);
$EedCj = LoadClass('EedCj', $GLOBALS['SPIS_ID']);
$referent = $EedCj->referent_id ? $EedCj->referent_id : 0;
$referent_puv = $EedCj->referent_id ? $EedCj->referent_id : 0;
$odbor_puv = $EedCj->odbor ? $EedCj->odbor : 0;
$docIDS = $EedCj->GetDocsInCj($GLOBALS['SPIS_ID']);

$cj_info = $EedCj->GetCjInfo($GLOBALS['SPIS_ID']);
$ns = $cj_info['CELE_CISLO'];
if (!$GLOBALS['ODBOR']) $GLOBALS['ODBOR'] = $GLOBALS['ODBOR_PUV'];
//ZapisCJ($GLOBALS['SPIS_ID'], $EedCj->cislo_jednaci);

//$sql="update posta SET odbor=".$GLOBALS["ODBOR"].",referent=".$GLOBALS["REFERENT"].",datum_referent_prijeti=NULL WHERE id in (".$GLOBALS["SPIS_ID"].",".implode(',', $docIDS).") and referent=".$referent;
$sql="update posta SET odbor=".$GLOBALS["ODBOR"].",referent=".$GLOBALS["REFERENT"].",datum_referent_prijeti=NULL WHERE id in (".$GLOBALS["SPIS_ID"].",".implode(',', $docIDS).") and (kopie=0 or kopie is null)";
$w->query($sql);

$text = 'čj/spis <b>'.$ns.'</b> byl dne '.$GLOBALS['DATUM'].' předán na odbor <b>'.UkazOdbor($GLOBALS["ODBOR"]).'</b> (' . $GLOBALS["ODBOR"] . ')';
if ($GLOBALS['REFERENT']>0) $text .= ', zpracovatel <b>' . UkazUsera($GLOBALS['REFERENT']) .'</b> ('.$GLOBALS['REFERENT'].')';
if ($GLOBALS['POZNAMKA']) $text .= '. Pozn: '. $GLOBALS['POZNAMKA'];
EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'DOC', $id_user);
EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'SPIS', $id_user);


if ($referent_puv>0) {
  $sql = "insert into posta_pristupy (posta_id,access,spis,odbor,referent,last_date,last_time,last_user_id,owner_id)
  VALUES (".$GLOBALS['SPIS_ID'].", 'read',1,$odbor_puv,$referent_puv,'".Date('Y-m-d')."','".Date('H:i:s')."',$referent_puv,$referent_puv) ";

}
elseif ($odbor_puv>0) {
  $sql = "insert into posta_pristupy (posta_id,access,spis,odbor,last_date,last_time,last_user_id,owner_id)
  VALUES (".$GLOBALS['SPIS_ID'].", 'read',1,$odbor_puv,'".Date('Y-m-d')."','".Date('H:i:s')."',$referent_puv,$referent_puv) ";

}
$w->query($sql);
$opravneni = '<b>read</b> pro spis.uzel <b>'.UkazOdbor($odbor_puv).'</b> ('.$odbor_puv.'), zpracovatel <b>'.UkazUsera($referent_puv).'</b> ('.$referent_puv.')';
$text = $cj_info['CELY_NAZEV'] . ' - bylo přidáno oprávnění: ' . $opravneni;
EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'DOC');
EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'SPIS');


if ($GLOBALS["REFERENT"]>0) {
  $doc = LoadClass('EedDokument', $GLOBALS['SPIS_ID']);
  include_once(FileUp2('plugins/emaily/.admin/emaily_funkce.inc'));
  $USER_INFO_EMAIL = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($GLOBALS['REFERENT'],true,0,1);;
  $komu = $USER_INFO_EMAIL['EMAIL'];
  $login = getEnv("REMOTE_USER");
  $kdo_poslal = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($login,true);
  $kdo = $kdo_poslal['FNAME'] . ' ' . $kdo_poslal['LNAME'];

  $vec = '---předání čj. jinému zpracovateli ---';
  if (strlen($komu)>5   && EedTools::MuzemePoslatEmail($GLOBALS['REFERENT']) ) {
    OdesliEmail('nova_posta_precteni', $komu,$doc->datum_podatelna_prijeti,$vec.$doc->vec,$doc->id_dokument,$kdo,'Přiřazení nového dokumentu');
  }
}

$lastid = Run_(array("outputtype"=>3,"no_unsetvars"=>true ));


require_once(Fileup2("html_footer.inc"));  

