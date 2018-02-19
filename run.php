<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/status.inc"));
require(FileUp2("interface/.admin/upload_funkce.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(Fileup2("html_header_title.inc"));
require_once(Fileup2(".admin/vnitrni_adresati.inc"));
require_once(Fileup2(".admin/vnejsi_adresati.inc"));

set_time_limit(180);

if (isset($GLOBALS['TYP_POSTY1'])) $GLOBALS['TYP_POSTY'] = $GLOBALS['TYP_POSTY1'];

$q = new DB_POSTA;

function replace_mail($editmail)
{
  $adresy = split("[;, ]",$editmail);
  foreach($adresy as $adresa){
    if($adresa){
      $adresa = strtolower($adresa);
      if($savemail)
        $savemail .= ', '.$adresa;
      else
        $savemail = $adresa;
    }
  }
  return $savemail;
}
reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/run_start.php');

		if (File_Exists($file)) include($file);
  }
}


//upravime pole adresatu
if ($GLOBALS['ODESL_EMAIL']) $GLOBALS['ODESL_EMAIL'] = replace_mail($GLOBALS['ODESL_EMAIL']);

if ($GLOBALS['ZALOZIT_ARCH'] == 2) //pozor, v dalsim vypraveni rekli, ze chteji zalozit jako novy soubor
{
  $GLOBALS['EXEMPLAR'] = 0; //dalsi vypraveni pridava exemplar
  $GLOBALS['PRIRAD_PODCISLO'] = 1; //nebudeme pridavat lomeni sberneho archu
}

if ($GLOBALS['ZALOZIT_ARCH'] == 1) //pozor, v dalsim vypraveni rekli, ze chteji zalozit jako novy soubor
{
  $GLOBALS['EXEMPLAR'] = -1; //dalsi vypraveni pridava exemplar
  if (!$GLOBALS['PRIRAD_PODCISLO']) $GLOBALS['PRIRAD_PODCISLO'] = 1; 
  if (!$GLOBALS['PODCISLO_SPISU']) $GLOBALS['PODCISLO_SPISU'] = 1;
}


if ($GLOBALS['KOPIE_SOUBORU_ANO']) {
  $GLOBALS['KOPIE_SOUBORU'] = $GLOBALS['KOPIE_SOUBORU_HODNOTA'];
}

if ($GLOBALS['MULTIEDIT'] && $GLOBALS['SUPERODBOR']) {
  //menime superodbor, musime vsechno ostatni vynulovat
  $GLOBALS['ODBOR'] = 0;
  $GLOBALS['ODDELENI'] = 0;
  $GLOBALS['REFERENT'] = 0;
//  Die('ok');
}

if ($GLOBALS['MULTIEDIT'] && $GLOBALS['REFERENT']) {
  $pole = OdborPrac($GLOBALS['REFERENT']);
//  print_r($pole);

  $GLOBALS['ODBOR'] = $pole['odbor'];
  $GLOBALS['ODDELENI'] = $pole['oddeleni'];
//  Die('ok');
}

if ($GLOBALS['REFERENT'] && !$GLOBALS['ODBOR']) {
  //vratil se nam referent a neni odbor, tak ho doplnime
  $userObj = LoadClass('EedUser', $GLOBALS['REFERENT']);
  $GLOBALS['ODBOR'] = $userObj->VratSpisovyUzelPracovnika($GLOBALS['REFERENT']);
}

//doslo ke zmene pracoviste, pro jisotut opet vymazeme potrebne veci
if ($GLOBALS['ODBOR_PUVODNI'] == -1) {
//  Die();
  $GLOBALS['ODBOR'] = 0;
  $GLOBALS['REFERENT'] = 0;
  $GLOBALS['STATUS'] = 7;
  $GLOBALS['DATUM_REFERENT_PRIJETI'] = '';
  $GLOBALS['DATUM_VYRIZENI'] = '';
  $GLOBALS['VYRIZENO'] = '';

}
if ($GLOBALS['DOPORUCENE'] == 1 && $GLOBALS['VLASTNICH_RUKOU'] == 1 && $GLOBALS['DATUM_VYPRAVENI'] == '' && $GLOBALS['CONFIG']['OBYCEJNA_POSTA_AUTOMATICKY_VYPRAVENA']) {
  $GLOBALS['DATUM_VYPRAVENI'] = Date('d.m.Y H:i:s');
}

//print_r($GLOBALS);
//print_r($VNITRNI_POSTA_REFERENT);
//Die();
if (!$GLOBALS['SUPERODBOR'])  {
  $GLOBALS['SUPERODBOR'] = EedTools::VratSuperOdbor();
}

echo "Ukládám...";
//Die($GLOBALS['SUPERODBOR']);
//print_r($GLOBALS['DALSI_PRIJEMCI']);
//Die();

$login = getEnv("REMOTE_USER");
$logged_user = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($login,true);
if ($logged_user[ID]>0)
{
  $GLOBALS[LAST_USER_ID] =  $logged_user[ID];
//  $GLOBALS[OWNER_ID] =  $logged_user[ID];
}

If ($GLOBALS["DELETE_ID"]) Die('STOP');
//Die($GLOBALS["PODCISLO_SPISU"]);
$GLOBALS["ODESL_ADRKOD"] = $GLOBALS["ODESL_ADRKOD"] ? $GLOBALS["ODESL_ADRKOD"]:0;
if (!$GLOBALS["ODESL_OTOCIT"]) $GLOBALS["ODESL_OTOCIT"] = 0;
if (!$GLOBALS["PRIVATE"]) $GLOBALS["PRIVATE"] = 0;
if (!$GLOBALS["OBALKA_NEVRACET"]) $GLOBALS["OBALKA_NEVRACET"] = 0;
if (!$GLOBALS["OBALKA_10DNI"]) $GLOBALS["OBALKA_10DNI"] = 0;
if ($GLOBALS["ODES_TYP"] == 'A' ||$GLOBALS["ODES_TYP"] == 'V' ||$GLOBALS["ODES_TYP"] == 'Z') $GLOBALS["ODESL_PRIJMENI"] = $GLOBALS["ODESL_PRIJMENI_NAZEV"];
if ($GLOBALS["ODES_TYP"] == 'P' ||$GLOBALS["ODES_TYP"] == 'U') 
{
  $GLOBALS["ODESL_PRIJMENI"] = $GLOBALS["ODESL_PRIJMENI_FIRMA"];
  $GLOBALS["ODESL_JMENO"] = ""; $GLOBALS["ODESL_DATNAR"] = "";
}
  if (strlen($GLOBALS[VEC])>254) $GLOBALS[VEC] = mb_substr($GLOBALS[VEC],0,254);
  if (strlen($GLOBALS[ODESL_PRIJMENI])>99) $GLOBALS[ODESL_PRIJMENI] = mb_substr($GLOBALS[ODESL_PRIJMENI],0,99);


if ($GLOBALS['OLD_REFERENT']>0 && $GLOBALS['REFERENT']>0 && $GLOBALS['OLD_REFERENT']<>$GLOBALS['REFERENT'])
{
  $pole = OdborPrac($GLOBALS['REFERENT']);
  $GLOBALS['ODBOR'] = $pole['odbor'];
  $GLOBALS['ODDELENI'] = $pole['oddeleni'];
   
}



// priradime podcislo k cislu jednacimu
Function PriradPodcislo($lastid) {
  if ($GLOBALS['PRIRAD_PODCISLO'] == 1) {
	EedTools::PriradPodcislo($lastid);
  }
}


// Pokud davam Vloz odchozi a je tam vice adresatu, vznika spis, dodelano 26.4.


// Priradime spisove cislo puvodni dosle poste!
// dali odpovedet, tak u puvodni posty musime napsat cislo spisu... asi ho jeste nema...    


//If ($GLOBALS["EDITOVANE_ID"]<>"" && $GLOBALS["CONFIG"]["VYTVOR_SPIS"]) 
/*
If ($GLOBALS["EDITOVANE_ID"]<>"")  {
  $idxxx = $GLOBALS["EDITOVANE_ID"];
  $q = new DB_POSTA;
  $CISLOSPISU1 = $GLOBALS["CISLO_SPISU1"] ? $GLOBALS["CISLO_SPISU1"]:0;
  $CISLOSPISU2 = $GLOBALS["CISLO_SPISU2"] ? $GLOBALS["CISLO_SPISU2"]:0;
  $DATUMVYRIZENI = $GLOBALS["DATUM_PODATELNA_PRIJETI"];
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $referent = $GLOBALS["REFERENT"]; 
  If ($referent == "") {$GLOBALS["REFERENT"] = $USER_INFO["ID"]; $referent = $USER_INFO["ID"];}
  $q->query ("update POSTA SET CISLO_SPISU1 = '$CISLOSPISU1' where id = $idxxx");
  $q->query ("update POSTA SET CISLO_SPISU2 = '$CISLOSPISU2' where id = $idxxx");
  $q->query ("update POSTA SET DATUM_VYRIZENI = '$DATUMVYRIZENI' where id = $idxxx");
  $q->query ("update POSTA SET REFERENT = $referent where id = $idxxx");
  NastavStatus($idxxx);
//    If ($GLOBALS["PODCISLO_SPISU"]"") { 
//    $q->query ("update POSTA SET PODCISLO_SPISU = '0' where id = $idxxx");
//    }
}
*/
$GLOBALS['ZAPIS_TEXT'] = '';

if ($GLOBALS['DOSBERNEHOARCHU'] == -9) {
//dochazi ke zmene cj;
  if ($GLOBALS['EDIT_ID']>0) {
    $cj_puv = LoadClass('EedCj', $GLOBALS['EDIT_ID']);
	  $text = 'U dokumentu <b>('.$GLOBALS['EDIT_ID'].')</b> '.$cj_puv->cislo_jednaci.' došlo ke změně čísla jednacího. ';
    $GLOBALS['ZAPIS_TEXT'] = $text;
  }
	$sql = 'select * from posta_h where id= ' . $GLOBALS['EDIT_ID'] . ' order by id_h asc';
	$novecj1 = 0;
	$novecj2 = 0;
  $exemplar = 0;
	$q->query($sql);
	while($q->Next_Record()) {
		$cj1temp = $q->Record['CISLO_SPISU1'];
		$cj2temp = $q->Record['CISLO_SPISU2'];
		// echo " $cj1temp / $cj2temp <br/>";
		if ($cj1temp>0 && (($cj1temp <> $GLOBALS['CISLO_SPISU1']) || ($cj2temp <> $GLOBALS['CISLO_SPISU2']))) {
			$novecj1 = $cj1temp;
			$novecj2 = $cj2temp;
			$main_doc = $q->Record['MAIN_DOC'];
      $exemplar = $q->Record['EXEMPLAR'];
			if ($main_doc>100 && $q->Record['TEXT_CJ']<>'') $text_cj = $q->Record['TEXT_CJ']; else $text_cj = '';
		}
	}
	$GLOBALS['CISLO_SPISU1'] = $novecj1;
	$GLOBALS['CISLO_SPISU2'] = $novecj2;
	$GLOBALS['EXEMPLAR'] = $exemplar;
	$GLOBALS['MAIN_DOC'] = $main_doc ? $main_doc : 1;

	if ($GLOBALS['CISLO_SPISU1'] == $GLOBALS['PUVODNI_CISLO_SPISU1']) {
		$GLOBALS['CISLO_SPISU1'] = 0;
		$GLOBALS['CISLO_SPISU2'] = Date('Y');
		$GLOBALS['CISLO_SPISU1'] = 0;
		$GLOBALS['CISLO_SPISU2'] = Date('Y');
	}

	if ($GLOBALS['CISLO_SPISU1'] == 0) {
		$GLOBALS['ROK'] = Date('Y');
		$GLOBALS['CISLO_SPISU1'] = 0;
		$GLOBALS['CISLO_SPISU2'] = Date('Y');
	}

	$GLOBALS['PODCISLO_SPISU'] = 0;
	$GLOBALS['TEXT_CJ'] = $text_cj;

}
//Die($GLOBALS['ZAPIS_TEXT']);
If ($EDIT_ID)  {

  If (($GLOBALS["OLD_CISLO_SPISU1"]<>$GLOBALS["CISLO_SPISU1"]) or ($GLOBALS["OLD_CISLO_SPISU2"]<>$GLOBALS["CISLO_SPISU2"]))
  {
    $cj_puv = LoadClass('EedCj', $GLOBALS['EDIT_ID']);
	  $text = 'U dokumentu <b>('.$GLOBALS['EDIT_ID'].')</b> '.$cj_puv->cislo_jednaci.' došlo ke změně čísla jednacího. ';
    $GLOBALS['ZAPIS_TEXT'] = $text;

    //doslo ke zmene cj.
  }
}

if ($GLOBALS["ODES_TYP"] == 'S') {
  $GLOBALS["ODESL_PRIJMENI"] = UkazOdbor($GLOBALS["ODESL_ODBOR"]);
  $GLOBALS["ODESL_JMENO"] = UkazUsera($GLOBALS["ODESL_PRAC2"]);
  $GLOBALS["ODESL_TITUL"] = $GLOBALS["ODESL_URAD"];
  $GLOBALS["ODESL_ULICE"] = $GLOBALS["ODESL_ODBOR"];
  $GLOBALS["ODESL_ODD"] = $GLOBALS["ODESL_ODD2"] ? $GLOBALS["ODESL_ODD2"] : 0;
  $GLOBALS["ODESL_OSOBA"] = $GLOBALS["ODESL_PRAC2"];
}

If (($GLOBALS["DATUM_REFERENT_PRIJETI2"] == 'vypnout')and($GLOBALS["EDIT_ID"])) {
  $q = new DB_POSTA;
  $sql = "update posta SET datum_referent_prijeti = null where id = ".$GLOBALS["EDIT_ID"];
  //echo $sql;
  $q->query($sql);
}

//automaticky označíme písemnosti, které by se měly otevírat ve Vitě.
If ($GLOBALS["STAV"] == '') $GLOBALS["STAV"] = 0;

If ($GLOBALS["STAV"] == 0 and $GLOBALS["ODBOR"] == $GLOBALS["CONFIG"]["ODBOR_VITA"])
  $GLOBALS["STAV"] = 1;

If ($GLOBALS["ODESIL_TYP"] == 'X' && $GLOBALS["ODBOR"] && !$GLOBALS["EDIT_ID"]) {
  //u vnitrni posty u ulozeni poupravime adresata pred ulozenim...
  $odesl_prijmeni_zal = $GLOBALS["ODESL_PRIJMENI"];
  $odesl_jmeno_zal = $GLOBALS["ODESL_JMENO"];
  $GLOBALS["ODESL_PRIJMENI"] = VratSNazevSkupiny($GLOBALS['SUPERODBOR2']).", ".UkazOdbor($GLOBALS["ODBOR2"]);

  $GLOBALS["ODESL_JMENO"] = UkazUsera($GLOBALS["REFERENT2"]);
}

$getOdesTyp = false;

$vnitrniAdresati = getVnitrniAdresatiFromForm(array_merge($_GET, $_POST));

$vnejsiAdresati = getVnejsiAdresatiFromForm(array_merge($_GET, $_POST));
if (count($vnejsiAdresati)>0) {
  $poleAdresatu = reset($vnejsiAdresati);
  if (count($poleAdresatu)>0) { 
    $GLOBALS['DALSI_PRIJEMCI'] = ',' . implode(',', $poleAdresatu) . ',';
    $getOdesTyp = true;
  }
}

if ($GLOBALS['ADRESAT_ID'] > 0) {
  $adresa = LoadClass('EedAdresa', $GLOBALS['ADRESAT_ID']);
  $GLOBALS['ODES_TYP'] = $adresa->typ; 
}
//print_r( $GLOBALS['DALSI_PRIJEMCI']); Die();

if ($DELETE_ID) {
  // Nedochazi k mazani zaznamu, ale pouze k jeho stornu.
   deleteVnitrniAdresati($DELETE_ID) ; 
}
else if ($EDIT_ID) {

  editVnitrniAdresati($EDIT_ID, $vnitrniAdresati);
}

$puvodni_status = $GLOBALS['STATUS'];

//pokud vloz prichozi se souboru nastavit datum predani
$path = $GLOBALS['PATH_CONTENT'];
if (strlen($path)>1) {
  $GLOBALS['DATUM_PREDANI'] = $GLOBALS['DATUM_PODATELNA_PRIJETI'];
}

$lastid = Run_(array("outputtype" => 1 ,"no_unsetvars" => true,"to_history" => false));

UNSET($GLOBALS['POSTA_OPT']['POSTA'][$lastid]);

//upload souboru - Vlož příchozí ze souboru
if (strlen($path)>1) {
  UNSET($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['ONLY_FILE_TYPES']);  
  $tc = $GLOBALS['TYPE_CONTENT'];  
   
  require_once(FileUp2(".admin/classes/dokument/Dokument.php"));
  $doc = new Dokument();
  $path_doc = $tc =="msg"? dirname($path).'/'.basename($path,".msg").".eml": $path;
  $doc->setDocumentPath($path_doc);
  $doc->upload($lastid);
  
  //upload příloh
  if ($tc=="eml"||$tc =="msg") {
    $tc = ucfirst($tc);
    require_once(FileUp2(".admin/classes/dokument/".$tc.".php"));
    $doc = new $tc();
    $doc->setDocumentPath($path);
    $doc->extractAttachments($lastid);
  }
  $doc->delTempDir();
  //$odesl_body = $GLOBALS['ODESL_BODY'];
  //unset($GLOBALS['ODESL_BODY']);
}


if (!$DELETE_ID && !$EDIT_ID) {
  insertVnitrniAdresati($lastid, $vnitrniAdresati);
}

$tran = LoadClass('EedTransakce');
//$tran->ZapisZHistorie($lastid);
if (is_array($lastid)) {
  foreach($lastid as $idcko)
//    $zmeny[$idcko] = $tran->CompareHistory($idcko);
    $zmeny[$idcko] = $tran->ZapisZHistorie($idcko);
    EedCeskaPosta::NastavCK($idcko);
}
else {
  $zmeny[$lastid] = $tran->ZapisZHistorie($lastid);
  EedCeskaPosta::NastavCK($lastid);
}



if ($GLOBALS['ID_PUVODNI']>0 && $GLOBALS['PRICHOZI_VYRIZEN']) {

  $lastid = $GLOBALS['EDIT_ID'];

  $GLOBALS['EDIT_ID'] = $GLOBALS['ID_PUVODNI'];
  $zpusob_vyrizeni = $GLOBALS[CONFIG_POSTA][HLAVNI][zpusob_vyrizeni_odpovedi];
  $LAST_TIME = Date('H:i:s');
  $LAST_DATE = Date('Y-m-d');

  $add_info = ",last_date = '$LAST_DATE',last_time = '$LAST_TIME',last_user_id = ".$GLOBALS[LAST_USER_ID];
  $sql = "update posta set datum_vyrizeni='" . Date('Y-m-d H:i:s') . "',vyrizeno='" . $zpusob_vyrizeni . "'" . $add_info . " where id=" . $GLOBALS['ID_PUVODNI'];
  $q->query($sql);
  $a = $tran-> ZapisZHistorie($GLOBALS['ID_PUVODNI']);
  NastavStatus($GLOBALS['ID_PUVODNI'], $GLOBALS[LAST_USER_ID]);
  $GLOBALS['EDIT_ID'] = $lastid;


}




@reset($lastid);
if (is_array($lastid) || is_array($GLOBALS['EDIT_ID'])) {
  if (is_array($lastid))
    while(list($key,$val) = each($lastid)) {
      if ($GLOBALS['CONFIG']['UPLOAD_ELO']) AktualizujElo($val);
      $novy_status = NastavStatus($val);
    }
  if (is_array($GLOBALS['EDIT_ID']))
    while(list($key,$val) = each($GLOBALS['EDIT_ID'])) {
      if ($GLOBALS['CONFIG']['UPLOAD_ELO']) AktualizujElo($val);
      $novy_status = NastavStatus($val);
    }
}
else {
  $novy_status = NastavStatus($GLOBALS["EDIT_ID"] ? $GLOBALS["EDIT_ID"]:$lastid);
  if ($GLOBALS['CONFIG']['UPLOAD_ELO']) AktualizujElo($GLOBALS["EDIT_ID"] ? $GLOBALS["EDIT_ID"]:$lastid);
}


if ($puvodni_status<>$novy_status && $GLOBALS['ODES_TYP']=='S' && $GLOBALS['ODESLANA_POSTA']<>'t' && $GLOBALS['EDIT_ID']>0 && $GLOBALS['ID_PUVODNI']>0 && $GLOBALS['CONFIG']["INTERNI_DORUCENKA_AZ_PO_PREVZETI"]) {
  include_once(FileUp2(".admin/config.inc"));
  include_once(FileUp2(".admin/upload_.inc"));
  include_once(FileUp2(".admin/oth_funkce.inc"));
  include_once(FileUp2("interface/.admin/upload_funkce.inc"));
  include_once('.admin/dorucenka.inc');
  //ulozime dorucenku pri zmene stavu
  if (!ExistujeDorucenka($GLOBALS['ID_PUVODNI']))
  {
     //echo $GLOBALS['ID_PUVODNI'];
     $sql="update posta set datum_doruceni='".Date('d.m.Y H:i:s')."' where id=".$GLOBALS['ID_PUVODNI'];
     $q->query($sql);
//     echo $sql;
     $edit_id=$GLOBALS['EDIT_ID'];
     UNSET($GLOBALS['EDIT_ID']);
     VytvorDorucenku($GLOBALS['ID_PUVODNI']);
     $GLOBALS['EDIT_ID']=$edit_id;
     //echo $sql;
//     print_r($GLOBALS);


  }
}
$exemplar = $GLOBALS['EXEMPLAR'];

//$lastid = Run_(array("outputtype" => 1 ,"no_unsetvars" => true));
if ($lastid == -1 && $GLOBALS["EDIT_ID"]) $lastid = $GLOBALS["EDIT_ID"];

PriradPodcislo($lastid);

if ($exemplar == -1) {
	//musime pridat dalsi exemplar
	EedTools::PriradExemplar($lastid);
}

if ($GLOBALS["CONFIG"]["POUZIVAT_UKOLY"] && $lastid) {
//echo "Jsm tu".$lastid;
  include_once(GetAgendaPath('UKOLY',false,false).'/../.admin/spol_func.inc');
  if (is_array($lastid))
    while(list($key,$val) = each($lastid))
      Kontrola_pz($val,$GLOBALS["REFERENT"]);
  else
    Kontrola_pz($GLOBALS["EDIT_ID"] ? $GLOBALS["EDIT_ID"]:$lastid,$GLOBALS["REFERENT"]);
//echo "Kioecn jsem tu";
}

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$LAST_USER_ID = $USER_INFO['ID'];

if ($GLOBALS['DOSPISU']>0) {
  $spis_obj = LoadClass('EedCj', $GLOBALS['DOSPISU']);
  $spis_info = $spis_obj->GetCjInfo($GLOBALS['DOSPISU']);
  $ps = $spis_info['CELE_CISLO'];
  $spis_nazev = $spis_info['CELY_NAZEV'];


  $cj_obj = new EedCj($lastid);
  $uloz = $lastid;
  if ($cj_obj->spis_id <> $lastid) $uloz = $cj_obj->spis_id;
  $cj_info = $cj_obj->GetCjInfo($lastid);
  $ns = $cj_info['CELE_CISLO'];

  $q = new DB_POSTA; //nejak zlobilo na decine, tak pro jistotu zavolam DB konektor znovu

  $sql = "INSERT INTO CIS_POSTA_SPISY (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID) VALUES ".
        "('$ps', '$ns', ".$GLOBALS['DOSPISU'].", $uloz,'$LAST_DATE','$LAST_TIME',$LAST_USER_ID,$LAST_USER_ID)";

  $q->query($sql);

  $text = 'dokument (<b>'.$lastid.'</b>) '.$ns.' byl vložen do spisu <b>' . $spis_nazev . '</b>';
  EedTransakce::ZapisLog($lastid, $text, 'DOC', $id_user);
  EedTransakce::ZapisLog($GLOBALS['DOSPISU'], $text, 'SPIS', $id_user);

}

if ($GLOBALS['DOSPISU'] == -1) {
  $cj_obj = new EedCj($lastid);
  $cj_info = $cj_obj->GetCjInfo($lastid);
  $ns = $cj_info['CELE_CISLO'];

  if ($cj_obj->spis_id <> $lastid) $uloz = $cj_obj->spis_id;
  else $uloz = $lastid;

  $q = new DB_POSTA; //nejak zlobilo na decine, tak pro jistotu zavolam DB konektor znovu

  $sql = "INSERT INTO CIS_POSTA_SPISY (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID,NAZEV_SPISU) VALUES ".
        "('$ns', '$ns', ".$uloz.", 0,'$LAST_DATE','$LAST_TIME',$LAST_USER_ID,$LAST_USER_ID,'".$GLOBALS['SpisCreateButton']."')";

  $q->query($sql);

  $text = 'Byl založen spis <b>' . $spis_nazev . '</b>';
  EedTransakce::ZapisLog($lastid, $text, 'DOC', $id_user);
  EedTransakce::ZapisLog($uloz, $text, 'SPIS', $id_user);

}



if ($GLOBALS["ODESLANA_POSTA"] == 't' && $GLOBALS["ODES_TYP"] == 'S' && $GLOBALS["DATUM_VYPRAVENI"]) {
  //jdeme zalozit vnitrni dokument 

//vzpnuto 16.2.2016, delalo duplikaty...
//    echo '
// <iframe id = "ifrm_get_value" name = "ifrm_get_value" style = "position:absolute;z-index:0;left:800;top:100;visibility:hidden" src = "zaloz.php?ID='.$lastid.'&otoc=1&zalozeni=1"></iframe>
// ';

/*
<script>
newwindow = window.open(\'zaloz.php ? ID = '.$lastid.'&otoc = 1&zalozeni = 1\',\'ifrm_get_value\',\'\');
newwindow.focus();
</script> 
';
*/
}
//Die('Jsem tu');

//Die ($GLOBALS["ROK"].$lastid);

//ulozime si do CISLO_JEDNACI cislo, ktere do dostalo - pri odchoyi [poste pro vice adresatu to MUSI dostat stejna cisla!

if (!is_array($lastid)) {
  $q->query("select ev_cislo,cislo_jednaci1,cislo_jednaci2,cislo_spisu1,cislo_spisu2 from posta where id = ".$lastid);
  $q->Next_Record();
  $GLOBALS["CISLO_JEDNACI1"] = $q->Record["CISLO_JEDNACI1"];
  $GLOBALS["CISLO_JEDNACI2"] = $q->Record["CISLO_JEDNACI2"];
  $GLOBALS["CISLO_SPISU1"] = $q->Record["CISLO_JEDNACI1"];
  $GLOBALS["CISLO_SPISU2"] = $q->Record["CISLO_JEDNACI2"];
  $GLOBALS["EV_CISLO"] = $GLOBALS["EV_CISLO"] ? $GLOBALS["EV_CISLO"]:$q->Record["EV_CISLO"];
}

$odesilatele = substr($GLOBALS["DALSI_PRIJEMCI"],1,-1);

//pokud se odesila nova pisemnost vice lidem, tak to dava cislo spisu, je potreba na to mit parametr...
/*
If (($GLOBALS["EDITOVANE_ID"] == "999999999") and ($odesilatele<>"") and ($GLOBALS["CONFIG"]["VYTVOR_SPIS"]))
{
  $q = new DB_POSTA;
  $idxxx = $lastid;
  $q->query("select ev_cislo,rok,cislo_jednaci1,cislo_spisu2 from posta where id = ".$idxxx);
  $q->Next_Record();
  $CISLOSPISU1 = $q->Record["CISLO_JEDNACI1"];
  $CISLOSPISU2 = ($q->Record["CISLO_SPISU2"]>0) ? $q->Record["CISLO_SPISU2"]:$q->Record["ROK"];
  $GLOBALS["CISLO_SPISU1"] = $CISLOSPISU1;
  $GLOBALS["CISLO_SPISU2"] = $CISLOSPISU2;
  $q->query ("update POSTA SET CISLO_SPISU1 = '$CISLOSPISU1' where id = $idxxx");
  $q->query ("update POSTA SET CISLO_SPISU2 = '$CISLOSPISU2' where id = $idxxx");
  $q->query ("update POSTA SET PODCISLO_SPISU = '0' where id = $idxxx");
}
*/



If ($lastid):
If (($GLOBALS["EDITOVANE_ID"]<>"") and ($GLOBALS["EDITOVANE_ID"]<>'999999999')) {
 //PriradPodcislo($lastid);
//  KontrolaNaSpis($lastid);
  $xxxx = new DB_POSTA;
  $sql = "update POSTA SET ID_PUVODNI = '".$GLOBALS["EDITOVANE_ID"]."' where id = ".$lastid;
//  Die($sql);
  $xxxx->query($sql);}
endif;

if ($GLOBALS[KOPIE_SOUBORU]) {
  $files_not_to_copy = array(
    'dorucenka_' . $GLOBALS[KOPIE_SOUBORU] . '.pdf',
    'dorucenka.zfo',
    'odchozi_datova_zprava.zfo'
  );
  //zkopirujeme soubory
  CopyFilesDokument('EED',$GLOBALS[KOPIE_SOUBORU],$lastid, $files_not_to_copy);
}

//$GLOBALS["EDITOVANE_ID"] = $lastid;


if ($GLOBALS['ZAPIS_TEXT']) {
    UNSET($GLOBALS['POSTA_OPT']['POSTA'][$lastid]);
    $cj_nov = LoadClass('EedCj', $lastid);
	  $text = $GLOBALS['ZAPIS_TEXT'] . 'Nové číslo jednací je <b>' . $cj_nov->cislo_jednaci.'</b>';

	  EedTransakce::ZapisLog($lastid, $text, 'DOC', $USER_INFO[ID]);
}


$NoPodcislo = false;
//echo "Cislo spisu je ".$GLOBALS['CISLO_SPISU1']; Die();

// rozesilame vice prijemcum....
If (($GLOBALS["DALSI_PRIJEMCI"]) AND ($GLOBALS["EDITOVANE_ID"]<>"") && $GLOBALS['ODES_TYP']<>'X') {
  // dalsi odesilatele....
  $odesilatele = explode(",",substr($GLOBALS["DALSI_PRIJEMCI"],1,-1));
  If ($EDITOVANE_ID == '999999999') $EDITOVANE_ID = $lastid;
  $id_puvodni = $EDITOVANE_ID;
  $ev_cislo = $GLOBALS[EV_CISLO] ? $GLOBALS[EV_CISLO]:0;
  $pocetprijemcu = count($odesilatele);
  $SUPERODBOR = $GLOBALS['SUPERODBOR'];

  $SKARTACE = $GLOBALS["SKARTACE"] ? $GLOBALS["SKARTACE"]:0;              
  $ODD_INT = $GLOBALS["ODDELENI"] ? $GLOBALS["ODDELENI"]:0;              
  $LAST_DATE = $GLOBALS["LAST_DATE"];
  $LAST_TIME = $GLOBALS["LAST_TIME"];
  $LAST_USER_ID = $GLOBALS["LAST_USER_ID"];
  $OWNER_ID = $GLOBALS["OWNER_ID"];
  $ODESLANO = $GLOBALS["DATUM_PODATELNA_PRIJETI"];
  $CISLO_JEDNACI1 = $GLOBALS["CISLO_JEDNACI1"] ? $GLOBALS["CISLO_JEDNACI1"]:0;
  $CISLO_JEDNACI2 = $GLOBALS["CISLO_JEDNACI2"] ? $GLOBALS["CISLO_JEDNACI2"]:0;
//    $CISLO_SPISU1 = $CISLO_SPISU1 ? $$CISLO_SPISU1:0;
//    $CISLO_SPISU2 = $CISLO_SPISU2 ? $$CISLO_SPISU2:0;
//echo "Cislo spisu je ".$GLOBALS['CISLO_SPISU1']; Die();
  $CISLO_SPISU1 = $GLOBALS["CISLO_SPISU1"] ? $GLOBALS["CISLO_SPISU1"]:0;
  $CISLO_SPISU2 = $GLOBALS["CISLO_SPISU2"] ? $GLOBALS["CISLO_SPISU2"]:0;
  $PODCISLO_SPISU = $GLOBALS["PODCISLO_SPISU"] ? $GLOBALS["PODCISLO_SPISU"]:0;
  $ODBOR_SPISU = $GLOBALS["ODBOR_SPISU"] ? $GLOBALS["ODBOR_SPISU"]:0;
  $PSC = str_replace(" ","",$PSC);
  $ZNACKA = $GLOBALS["ZNACKA"];
  $dalsi_id_agenda = $GLOBALS["DALSI_ID_AGENDA"] ? $GLOBALS["DALSI_ID_AGENDA"]:0;

  for ($aaa = 0; $aaa<$pocetprijemcu; $aaa++) {
    $idprijemce = $odesilatele[$aaa];
//echo "Jdu zpracovatet" . $idprijemce . "<br/>";


     $idprijemce_ciste = str_replace('X_','',$odesilatele[$aaa]);
     $idprijemce_ciste = str_replace('x_','',$idprijemce_ciste);
     $q = new DB_POSTA;
     $a = new DB_POSTA;
//     $sql = 'select cislo_spisu1,cislo_spisu2,podcislo_spisu from posta where id = '.$lastid;
//     $q->query($sql); $q->Next_Record();
//     $CISLO_SPISU1 = $q->Record["CISLO_SPISU1"] ? $q->Record["CISLO_SPISU1"]:$GLOBALS['CISLO_SPISU1'];
//     $CISLO_SPISU2 = $q->Record["CISLO_SPISU2"];
//     $PODCISLO_SPISU = $q->Record["PODCISLO_SPISU"] ? $q->Record["PODCISLO_SPISU"]:$GLOBALS['PODCISLO_SPISU'];

     If ($idprijemce == '') break;
     if (eregi('X_',$idprijemce))
        {$sql = 'SELECT odes_typ,odesl_jmeno,odesl_prijmeni,odesl_titul,odesl_ulice,odesl_cp,odesl_cor,odesl_psc,odesl_posta,odesl_odd,odesl_osoba,odesl_ico FROM posta WHERE id IN ('.str_replace(array('X_','x_'),array('',''),$idprijemce).')'; $table = 'posta';}
      else
        {$sql = 'SELECT * FROM cis_posta_prijemci WHERE id IN ('.$idprijemce.')'; $table = 'cis_posta_prijemci';}

     $q->query ($sql);
     while($q->next_record()) {    
       $ODESILATEL_TYP = $q->Record["ODES_TYP"];
       $JMENO = $q->Record["ODESL_JMENO"];
       $PRIJMENI = $q->Record["ODESL_PRIJMENI"];
       $TITUL = $q->Record["ODESL_TITUL"];
       $ULICE = $q->Record["ODESL_ULICE"];
       $CP = $q->Record["ODESL_CP"];
       $CO = $q->Record["ODESL_COR"];
       $PSC = $q->Record["ODESL_PSC"];
       $POSTA = $q->Record["ODESL_POSTA"];
       $ODD = $q->Record["ODESL_ODD"];
       $OSOBA = $q->Record["ODESL_OSOBA"];
       $ICO = $q->Record["ODESL_ICO"]; 
     }
     $ADRESAT_ID = $idprijemce ? $idprijemce : 0; 
     if ($getOdesTyp) {
       $adresa = LoadClass('EedAdresa', $idprijemce);
       $ODESILATEL_TYP = $adresa->typ; 
     }

//print_r($GLOBALS['jakodeslat']);
//print_r($GLOBALS['kymdeslat']);
//echo "ID prijemce je ".$idprijemce_ciste;
    $DOPORUCENE = $GLOBALS['jakodeslat'][$idprijemce_ciste] ? $GLOBALS['jakodeslat'][$idprijemce_ciste] : $GLOBALS['DOPORUCENE'];
    $VLASTNICH_RUKOU = $GLOBALS['kymdeslat'][$idprijemce_ciste] ? $GLOBALS['kymdeslat'][$idprijemce_ciste] : $GLOBALS['VLATNICH_RUKOU'];
//    echo "Doporucene je $DOPORUCENE a vlastnich je $VLASTNICH_RUKOU ";
      $sql = "insert into posta 
      (ev_cislo,rok,odbor,superodbor,oddeleni,typ_posty,odes_typ,vec,odesl_prijmeni,odesl_jmeno,odesl_titul,odesl_ico,odesl_ulice,odesl_cp,odesl_cor,
      odesl_psc,odesl_posta,datum_podatelna_prijeti,referent,odeslana_posta,doporucene,vlastnich_rukou,dorucenka,cislo_spisu1,cislo_spisu2,podcislo_spisu,
      id_puvodni,odesl_odd,odesl_osoba,last_date,last_time,last_user_id,owner_id,skartace,dalsi_prijemci,cislo_jednaci1,cislo_jednaci2,znacka,odbor_spisu,nazev_spisu,
      obalka_nevracet,obalka_10dni,pocet_priloh,pocet_listu,druh_priloh,adresat_id)
      values
      ($ev_cislo,'$ROK',$ODBOR,$SUPERODBOR,'$ODD_INT','$TYP_POSTY','$ODESILATEL_TYP','$VEC','$PRIJMENI','$JMENO','$TITUL','$ICO','$ULICE','$CP','$CO',
      '$PSC','$POSTA','$ODESLANO',$REFERENT,'t','$DOPORUCENE','$VLASTNICH_RUKOU','$DORUCENKA','$CISLO_SPISU1','$CISLO_SPISU2','$PODCISLO_SPISU',
      '$id_puvodni','$ODD','$OSOBA','$LAST_DATE','$LAST_TIME','$LAST_USER_ID','$OWNER_ID','$SKARTACE','$DALSI_PRIJEMCI',
      '$CISLO_JEDNACI1','$CISLO_JEDNACI2','$ZNACKA','$ODBOR_SPISU','".$GLOBALS["NAZEV_SPISU"]."',$GLOBALS[OBALKA_NEVRACET],$GLOBALS[OBALKA_10DNI],
      $GLOBALS[POCET_PRILOH],$GLOBALS[POCET_LISTU],'$GLOBALS[DRUH_PRILOH]',$ADRESAT_ID);
      ";     
//    }
//    echo $sql;
    if ($ODESILATEL_TYP<>'X') {
      $a->query($sql);
      $posle_id = $a->getlastid('posta', 'id');
      NastavStatus($posle_id);
      if ($GLOBALS[KOPIE_SOUBORU]) CopyFilesDokument('EED',$GLOBALS[KOPIE_SOUBORU],$posle_id);    
    }
  }
}


reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/run_end.php');

		if (File_Exists($file)) include($file);
  }
}


echo '
<script language="JavaScript" type="text/javascript">
  try {  
    window.opener.parent.$.fancybox.close();    
  } catch(err) { }  
  window.opener.document.location.reload();
</script>
';
require_once(Fileup2("html_footer.inc"));  



