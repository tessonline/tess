<?php
$dbname = './log/'.Date(dmY).'.txt';

Function ZapisText($file,$text) {
  If (file_exists($file)) $params = 'a'; else $params = 'w';
  $fp = @FOpen($file,$params);
	$a = Date('H:i:s')." - ".$text;
  @FWrite($fp,$a);
  @FClose($fp);
}

require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/security_name.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2("interface/.admin/soap_funkce.inc"));
include_once(FileUp2("interface/.admin/upload_funkce.inc"));
include_once(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/zaloz.inc"));
include_once(FileUp2("services/spisovka/uzavreni_spisu/funkce.inc"));

include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

$GLOBALS['status'] = getSelectDataEed(new of_select_status(array()));

Header("Pragma: no-cache");
Header("Cache-Control: no-cache");

Header("Content-Type: text/xml");

$session_id = Date('dmYHms');
$software_id = 'VITA';

    echo "<?xml version = \"1.0\" encoding = \"iso-8859-2\" \n?>";
      echo "  <pisemnost>\n";


//Die(print_r($_GET));

$rok = date('Y');

$text = '(ZALOZ_PISEMNOST) - query: '.str_replace('&',', ',urldecode($_SERVER['QUERY_STRING'])).'';
//WriteLog($software_id,$text,$session_id);

//zkratime pole vec na 99 znaku
if (strlen($GLOBALS[a_vec])>99) $GLOBALS[a_vec] = substr($GLOBALS[a_vec],0,99);
if (strlen($GLOBALS[a_prijobyv])>99) $GLOBALS[a_prijobyv] = substr($GLOBALS[a_prijobyv],0,99);
//smazeme z PSC prebytecne mezery
$GLOBALS[a_psc] = str_replace(" ","",$GLOBALS[a_psc]);

If ($GLOBALS["a_cj"]) list($CISLO_JEDNACI1,$CISLO_JEDNACI2) = explode("/",$GLOBALS["a_cj"]);
If ($GLOBALS["a_spisid"] and strpos($GLOBALS["a_spisid"],'/')) list($CISLO_SPISU1,$CISLO_SPISU2,$ODBOR_SPISU) = explode("/",$GLOBALS["a_spisid"]);
If ($GLOBALS["a_cp"]) list($EV_CISLO,$ROK) = explode("/",$GLOBALS["a_cp"]);

$qq = new DB_POSTA_ISO;
If ($GLOBALS["a_spisznak"]) {
  //jdeme najit ID skartacniho kodu
  $sql_skartace = "select id from cis_posta_skartace where text like '".$GLOBALS["a_spisznak"]." %'";
  $a = new DB_POSTA_ISO;
  $a->query($sql_skartace);
  $pocet = $a->Num_Rows();
  $a->Next_Record();
  If ($pocet == 1) $skartace = $a->Record["ID"]; else $skartace = 0;

  if ($pocet == 0 || $pocet>1)  {
    //zkusime alternativu s teckou
    $sql_skartace = "select id from cis_posta_skartace where text like '".$GLOBALS["a_spisznak"]." %' and aktivni = 1";
    $a = new DB_POSTA_ISO;
    $a->query($sql_skartace);
    $pocet = $a->Num_Rows();
    $a->Next_Record();
    If ($pocet == 1) $skartace = $a->Record["ID"]; else $skartace = 0;

  }
  $text = '(ZALOZ_PISEMNOST) - Hledam spisznak k '.$GLOBALS["a_spisznak"].' - nalezeno ID '.$skartace.'';
  WriteLog($software_id,$text,$session_id);

}
else
  $skartace = 0;

If ($GLOBALS["a_spisid"] and !strpos($GLOBALS["a_spisid"],'/'))  {
  $editace = false;
  //tak nam poslali id nejakyho dokumentu ze spisu a musime si zjistit jeho cislo spisu :(
  $a = new DB_POSTA_ISO;
  $a->query('select * from posta where id = '.$GLOBALS["a_spisid"]);
//echo 'select * from posta where id = '.$GLOBALS["a_spisid"];
  $a->Next_Record();
  $CISLO_SPISU1 = $a->Record["CISLO_SPISU1"];
  $CISLO_SPISU2 = $a->Record["CISLO_SPISU2"];
  if ($skartace == 0 && $a->Record["SKARTACE"]<>0) $skartace = $a->Record["SKARTACE"];
  $ODBOR_SPISU = $a->Record["ODBOR_SPISU"];
  if ($CISLO_SPISU1>0 && !$GLOBALS['a_vec']) {
    $editace = true;
  }
}

If ($GLOBALS["a_davyr"]) {
//jdeme uzavirat spis a potrebujeme cislo spisu z ID :(
  $a = new DB_POSTA_ISO;
  $a->query('select * from posta where id = '.$GLOBALS["a_id"]);
  $a->Next_Record();
  $CISLO_SPISU1 = $a->Record["CISLO_SPISU1"];
  $CISLO_SPISU2 = $a->Record["CISLO_SPISU2"];
  $ODBOR_SPISU = $a->Record["ODBOR_SPISU"];
  $REFERENT = $a->Record["REFERENT"];
  if ($CISLO_SPISU1 == 0 || $CISLO_SPISU1<0) {
     echo "    <b_error>Dokument nebyl nalezen!</b_error>\n";
     echo "    <b_id>".$GLOBALS[a_id]."</b_id>\n";
     echo "  </pisemnost>\n";
     Die();
  }
  if ($skartace == 0 && $a->Record["SKARTACE"]<>0) $skartace = $a->Record["SKARTACE"];
}

If ($GLOBALS["a_spisid"] == $GLOBALS["a_id"] && $GLOBALS["a_id"]<>'') {
//tak nam poslali id nejaky pisemnosti a musime si zjistit jeji cislo spisu :(
  $a = new DB_POSTA_ISO;
  $a->query('select * from posta where id = '.$GLOBALS["a_spisid"]);
  $a->Next_Record();
  $CISLO_SPISU1 = $a->Record["CISLO_SPISU1"];
  $CISLO_SPISU2 = $a->Record["CISLO_SPISU2"];
  $ODBOR_SPISU = UkazOdbor($a->Record["ODBOR"],true,false);
  if ($skartace == 0 && $a->Record["SKARTACE"]<>0) $skartace = $a->Record["SKARTACE"];

//    Die( $CISLO_SPISU1.' x '.$CISLO_SPISU2.' z '.$ODBOR_SPISU);
}

$jen10 = 0;
$nevracet = 0;
if (eregi('ux', $GLOBALS[a_doplsluzby])) $jen10 = 1;
if (eregi('sa', $GLOBALS[a_doplsluzby])) $nevracet = 1;

//pridano 2010-10-19, vnitrni posta, nova varianta
If ($GLOBALS[a_typdor] == 6) {
  $GLOBALS[a_TypAdr] = "S";
  $urad = trim($GLOBALS['a_prijobyv']);
  $kam = trim($GLOBALS['a_jmobyv']);

  $prijemce = $GLOBALS["KONEKTOR"]["VITA"]["MAP_ODBORU"][$urad][$kam];

  if ($prijemce[ODD]>0)
    $prijemce[ODBOR] = $prijemce[ODD];

  $GLOBALS['a_titul'] = $prijemce[URAD];
  $GLOBALS['a_cobce'] = $prijemce[ODBOR];

  $GLOBALS['a_odeslodd'] = $prijemce[ODD];

  $GLOBALS[a_prijobyv] = UkazOdbor($prijemce[ODBOR]);
  $GLOBALS[a_jmobyv] = '';
}

//pokud neprijde ID pracovnika, tak vezmeme ID vity!
$id_user = $GLOBALS[a_prac] ? $GLOBALS[a_prac] : $GLOBALS["CONFIG"]["VITA_ID"];
$zpusob_vyrizeni = $GLOBALS["KONEKTOR"]["VITA"]["ZPUSOB_VYRIZENI"] ? $GLOBALS["KONEKTOR"]["VITA"]["ZPUSOB_VYRIZENI"] : '';
$LAST_USER_ID = $id_user;
$OWNER_ID = $id_user;
$LAST_TIME = Date('H:i:s');
$LAST_DATE = Date('Y-m-d');

$add_info = "last_date = '$LAST_DATE',last_time = '$LAST_TIME',last_user_id = ".$LAST_USER_ID;

// list($datum, $cas) = explode(' ', $GLOBALS["a_ze_dne"]);
// $pocet_cas = explode(':', $cas);
// if (count($pocet_cas) == 2) $cas = $cas . ':00';
// //if (pocet = explode(':', $q->Record[$sloupec]);)
// $ODESLANO = $datum . ' ' . $cas; //mozna upravit datum
$ODESLANO=$qq->str2dbdate($GLOBALS["a_ze_dne"]); //mozna upravit datum


if ($GLOBALS["CISLO_SPISU1"] == 0) UNSET($GLOBALS["CISLO_SPISU1"]);
if ($GLOBALS["CISLO_SPISU2"] == 0) UNSET($GLOBALS["CISLO_SPISU2"]);

If ($GLOBALS["a_cp"] || $GLOBALS["a_id"] || ($GLOBALS["a_spisid"] && $GLOBALS["a_id"]) || $editace) {

  If (!$GLOBALS["a_id"] && !$GLOBALS["a_spisid"]) {
    // jdeme zjistit id zaznamu z cp
    $sql = 'select id from posta where EV_CISLO = '.$EV_CISLO.' and ROK = '.$ROK.'';
    $a = new DB_POSTA_ISO;
    $a->query($sql);
    $a->Next_Record();
    $GLOBALS["a_id"] = $a->Record["ID"];
  }


  // aktualizace zaznamu...
  $sql = array();
  If ($ODBOR) $sql[] = "update posta set odbor = ".$ODBOR." where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_typodesl]) $sql[] = "update posta set doporucene = '$GLOBALS[a_typodesl]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_typdor]) $sql[] = "update posta set vlastnich_rukou = '$GLOBALS[a_typdor]',$add_info where id = ".$GLOBALS["a_id"];

  If ($GLOBALS[a_TypAdr]) $sql[] = "update posta set odes_typ = '$GLOBALS[a_TypAdr]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_vec]) $sql[] = "update posta set vec = '$GLOBALS[a_vec]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_prijobyv]) $sql[] = "update posta set odesl_prijmeni = '$GLOBALS[a_prijobyv]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_jmobyv]) $sql[] = "update posta set odesl_jmeno = '$GLOBALS[a_jmobyv]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_RcIc]) $sql[] = "update posta set odesl_ico = '$GLOBALS[a_RcIc]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_cobce]) $sql[] = "update posta set odesl_ulice = '$GLOBALS[a_cobce]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_Cd]) $sql[] = "update posta set odesl_cp = '$GLOBALS[a_Cd]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_Cor]) $sql[] = "update posta set odesl_cor = '$GLOBALS[a_Cor]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_psc]) $sql[] = "update posta set odesl_psc = '$GLOBALS[a_psc]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_obec]) $sql[] = "update posta set odesl_posta = '$GLOBALS[a_obec]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_pisvyr]) $sql[] = "update posta set datum_vyrizeni = '".$qq->str2dbdate($GLOBALS[a_pisvyr])."',vyrizeno='$zpusob_vyrizeni',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_ds]) $sql[] = "update posta set odesl_datschranka = '$GLOBALS[a_ds]',$add_info where id = ".$GLOBALS["a_id"];
  if ($GLOBALS[a_doplsluzby]) $sql[] = "update posta set obalka_10dni = $jen10,obalka_nevracet = $nevracet,$add_info where id = ".$GLOBALS["a_id"];
  //pridano 2007-07-11
  If ($GLOBALS[a_idobyvatele]) $sql[] = "update posta set obyvatel_kod = '$GLOBALS[a_idobyvatele]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_druh_dokumentu]) $sql[] = "update posta set typ_posty = $GLOBALS[a_druh_dokumentu],$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_typdor]) $sql[] = "update posta set vlastnich_rukou = '$GLOBALS[a_typdor]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_spisznak]) $sql[] = "update posta set skartace = '$skartace',$add_info where id = ".$GLOBALS["a_id"];

  If ($GLOBALS[a_pocetlistu]) $sql[] = "update posta set pocet_listu = '$GLOBALS[a_pocetlistu]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_pocetpriloh]) $sql[] = "update posta set pocet_priloh = '$GLOBALS[a_pocetpriloh]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_druhpriloh]) $sql[] = "update posta set druh_priloh = '$GLOBALS[a_druhpriloh]',$add_info where id = ".$GLOBALS["a_id"];

  If ($GLOBALS[a_termin]) {
    $sql[] = "update posta set lhuta_vyrizeni = '".$qq->str2dbdate($GLOBALS[a_termin])."',
    lhuta = extract(DAY FROM to_timestamp('".$qq->str2dbdate($GLOBALS[a_termin])."','YYYY-FMMM-FMDD'))-extract(DAY FROM DATUM_PODATELNA_PRIJETI), $add_info where id = ".$GLOBALS["a_id"];
  }
  If ($GLOBALS[a_preruseno] == 1) $sql[] = "update posta set lhuta_vyrizeni = NULL,$add_info where id = ".$GLOBALS["a_id"];

  If ($ODESLANO) $sql[] = "update posta set datum_podatelna_prijeti = '".($ODESLANO)."',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_prac] && !$GLOBALS[a_spisid]) $sql[] = "update posta set referent = $GLOBALS[a_prac],$add_info where id = ".$GLOBALS["a_id"];
//duplicita
//    If ($CISLO_SPISU1) $sql[] = "update posta set cislo_spisu1 = $CISLO_SPISU1,$add_info where id = ".$GLOBALS["a_id"];
//    If ($CISLO_SPISU2) $sql[] = "update posta set cislo_spisu2 = $CISLO_SPISU2,$add_info where id = ".$GLOBALS["a_id"];
  //If ($LAST_DATE) $sql[] = "update posta set last_date = '$LAST_DATE' where id = ".$GLOBALS["a_id"];
  //If ($LAST_TIME) $sql[] = "update posta set last_time = '$LAST_TIME' where id = ".$GLOBALS["a_id"];
  //If ($LAST_USER_ID) $sql[] = "update posta set last_user_id = $LAST_USER_ID where id = ".$GLOBALS["a_id"];
  If ($CISLO_JEDNACI1 ) $sql[] = "update posta set cislo_jednaci1 = $CISLO_JEDNACI1,$add_info where id = ".$GLOBALS["a_id"];
  If ($CISLO_JEDNACI2) $sql[] = "update posta set cislo_jednaci2 = $CISLO_JEDNACI2,$add_info where id = ".$GLOBALS["a_id"];
  If ($ODBOR_SPISU && !$GLOBALS[a_prac]) $sql[] = "update posta set odbor_spisu = '$ODBOR_SPISU',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_dokumentid]) $sql[] = "update posta set id_puvodni = $GLOBALS[a_dokumentid],$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_stav] || $GLOBALS[a_stav] == '0') $sql[] = "update posta set stav = $GLOBALS[a_stav],$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_stav] == '3') $sql[] = "update posta set stav = $GLOBALS[a_stav],datum_vyrizeni = '".Date('d.m.Y H:i:s')."',$add_info where id = ".$GLOBALS["a_id"];

  //onma, tohle asi vytvarelo spis, opravime
  //If ($CISLO_SPISU1 && !$GLOBALS[a_prac]) $sql[] = "update posta set cislo_spisu1 = $CISLO_SPISU1,$add_info where id = ".$GLOBALS["a_id"];
  //If ($CISLO_SPISU2 && !$GLOBALS[a_prac]) $sql[] = "update posta set cislo_spisu2 = $CISLO_SPISU2,$add_info where id = ".$GLOBALS["a_id"];

  If ($GLOBALS["a_spisid"] && $GLOBALS["a_id"] && $GLOBALS["a_id"]<>'') {
    $spis = LoadClass('EedDokument', $GLOBALS['a_spisid']);
    $doc = LoadClass('EedDokument', $GLOBALS['a_id']);
    $sqlx="insert into cis_posta_spisy (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID)
    VALUES ('".$spis->cislo_jednaci."','".$doc->cislo_jednaci."',".$GLOBALS['a_spisid'].",".$GLOBALS['a_id'].",'$LAST_DATE','$LAST_TIME',$LAST_USER_ID,$LAST_USER_ID)";

    $x = new DB_POSTA_ISO;
    $x->query($sqlx);
    $text = 'VITA: dokument (<b>'.$GLOBALS['a_id'].'</b>) '.$doc->cislo_jednaci.' byl vlo¾en do spisu: <b>' . $spis->cislo_jednaci . '</b>';
//    EedTransakce::ZapisLog($GLOBALS["a_spisid"], $text, 'DOC', $id_user);
  }
  if ($GLOBALS[a_doplsluzby]) $sql[] = "update posta set obalka_nevracet = $nevracet,obalka_10dni = $jen10,$add_info where id = ".$GLOBALS["a_id"];

  //pridano 2010-10-19
  If ($GLOBALS[a_titul]) $sql[] = "update posta set odesl_titul = '$GLOBALS[a_titul]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_odeslodd]) $sql[] = "update posta set odesl_odd = '$GLOBALS[a_odeslodd]',$add_info where id = ".$GLOBALS["a_id"];

  //pridano 2009-02-17/
  If ($GLOBALS[a_prac] && $GLOBALS["a_spisid"] && $CISLO_SPISU1>0)  {
    //echo ":Jsem tu";
    $x = new DB_POSTA_ISO;
    $sql2 = "select * from posta where cislo_spisu1 = $CISLO_SPISU1 and cislo_spisu2 = $CISLO_SPISU2";
    //echo $sql2;
    $x->query($sql2);
    $x->Next_Record();
    $pozn = 'Zmìna oprávnìné osoby provedena ve Vita sw.';
    $old_zpracovatel  =  $x->Record["REFERENT"] ? $x->Record["REFERENT"] : $GLOBALS[a_prac];
    $old_odbor = $x->Record["ODBOR"]?$x->Record["ODBOR"]:0;
    //$GLOBALS['a_id'][] = $x->Record['ID'];
    $old_zpracovatel = $old_zpracovatel?$old_zpracovatel:0;
//      $GLOBALS["a_id"] = $x->Record["ID"];
    $sql2 = "insert into cis_posta_predani (old_referent,old_odbor,referent,odbor,datum,poznamka,last_date,last_time,last_user_id,cislo_spisu1,cislo_spisu2) VALUES ($old_zpracovatel,$old_odbor,".$GLOBALS[a_prac].",$old_odbor,'".Date('d.m.Y')."','".$pozn."','".$LAST_DATE."','".$LAST_TIME."',$LAST_USER_ID,$CISLO_SPISU1,$CISLO_SPISU2)";
    //echo $sql2;
    $x->query($sql2);
    $sql[] = "update posta set referent = '$GLOBALS[a_prac]',$add_info where cislo_spisu1 = $CISLO_SPISU1 and cislo_spisu2 = $CISLO_SPISU2";
  }


/*
  // pridano 2010-10-19, nova interni posta
  if ($GLOBALS[a_typdor] == 6)
  {
    $sql = "update posta set odes_typ = ''";


$GLOBALS["ODESL_PRIJMENI"] = UkazOdbor($GLOBALS["ODESL_ODBOR"]);
$GLOBALS["ODESL_JMENO"] = UkazUsera($GLOBALS['a_prac']);
$GLOBALS["ODESL_TITUL"] = $GLOBALS["ODESL_URAD"];
$GLOBALS["ODESL_ULICE"] = $GLOBALS["ODESL_ODBOR"];
$GLOBALS["ODESL_ODD"] = $GLOBALS["ODESL_ODD2"];
$GLOBALS["ODESL_OSOBA"] = $GLOBALS["ODESL_PRAC2"];


  }
*/
  $a = new DB_POSTA_ISO;
  while(list($key,$val) = each($sql))
  {
    $chyba = false;
    If (!$a->query($val))
      $chyba = true;

     If ($chyba)
     {
        echo "    <b_error>SQL error:".$val."</b_error>\n";
        $text = '(ZALOZ_PISEMNOST) - query: '.$val;
        WriteLog($software_id,$text,$session_id,1);
     }

  }
  If ($GLOBALS[a_davyr]) {
    $chyba = array();
    //prepocitame spis
//  $idcka = VratDokumentyKeSpisu($CISLO_SPISU1,$CISLO_SPISU2,$REFERENT);
   $cj_obj = LoadClass('EedCj', $GLOBALS['a_id']);
   $idcka = $cj_obj->GetDocsInCj($GLOBALS['a_id'], 1);
   while (list($key,$val) = each($idcka)) {
     $doc = LoadClass('EedDokument', $val);
     if ($doc->status>1 && $doc->status<>9 && $doc->status<80 && $doc->datum_podatelna_prijeti<>'31.12.2100 00:00') {
// vypnuto na zadost Decina
//        $chyba[$val] = 'Chyba: Dokument JID ' . $doc->barcode . ' je ve stavu: ' . $GLOBALS['status'][$doc->status]. '. Nelze uzavøít spis.';
     }

  }
  if (count($chyba)>0) {
    while (list($key,$val) = each($chyba)) {
      echo "    <b_error>".$val."</b_error>\n";
      $text = '(ZALOZ_PISEMNOST) - chyba: '.$val;
      WriteLog($software_id,$text,$session_id,1);
    }
    echo "  </pisemnost>\n";
    Die();
  }
   reset($idcka);
   while (list($key,$val) = each($idcka)) {
     $sqla = "update posta set spis_vyrizen = '$GLOBALS[a_davyr]',datum_vyrizeni = '".$qq->str2dbdate($GLOBALS[a_davyr])."',$add_info where id=" . $val;
     $a->query($sqla);

     $text = 'VITA: dokument (<b>'.$GLOBALS['a_id'].'</b>) byl vyøízen.';
//     EedTransakce::ZapisLog($val, $text, 'DOC', $id_user);

     NastavStatus($val,$id_user);
   }
  }
  If (!$chyba)
  {
     echo "    <b_error>0</b_error>\n";
    if ($GLOBALS['a_id']>0 && !is_array($GLOBALS['a_id'])) {
      echo "    <b_id>".$GLOBALS[a_id]."</b_id>\n";
      NastavStatus($GLOBALS["a_id"]);
    }
  }
}

else {
   //zalozime novy dokument

  //  $OWNER_ID = $GLOBALS[a_prac];
  $LAST_USER_ID = $OWNER_ID;
  //  echo $GLOBALS["a_prac"];
  IF ($CISLO_JEDNACI1>0) $ev_cislo = $CISLO_JEDNACI1; else $ev_cislo = 0;
  $a = new DB_POSTA_ISO;

  $a->query("select * from security_user where id = ".$OWNER_ID);
  //  echo "select * from security_user where id = ".$OWNER_ID;
  $a->Next_Record();
  $ODBOR2  =  $a->Record["GROUP_ID"];
  $ODBOR2 = $ODBOR2?$ODBOR2:0;
  $a->query ("SELECT id from cis_posta_odbory where id_odbor = ".$ODBOR2);
  $a->Next_Record();
  $ODBOR = $a->Record["ID"];
  $ODBOR = $ODBOR?$ODBOR:999;

  //pokud pouzivame oddeleni, tak je musime prepocitat na odbor...
  If ($GLOBALS["CONFIG"]["ODDELENI"])
  {
    $jaky_odbor = UkazOdbor($ODBOR,0,0,1);
    If (GetParentGroup($jaky_odbor) == 0)
    {
      //jsem v odboru, nejsem v oddeleni
      $odbor = $ODBOR;
      $oddeleni = 0;
    }
    else
    {
      //jsem v odboru,  a jsem v oddeleni
      $odbor = VratOdbor(GetParentGroup($jaky_odbor));
      $oddeleni = VratOdbor($jaky_odbor);
    }
  }
  else
  {
    $oddeleni = 0;
    $odbor = $ODBOR;
  }

  $GLOBALS[a_prac] = $GLOBALS[a_prac]?$GLOBALS[a_prac]:0;
  $GLOBALS[a_idobyvatele] = $GLOBALS[a_idobyvatele]?$GLOBALS[a_idobyvatele]:0;
  $CISLO_SPISU1 = $CISLO_SPISU1?$CISLO_SPISU1:0;
  $CISLO_SPISU2 = $CISLO_SPISU2?$CISLO_SPISU2:0;
  $GLOBALS[a_dokumentid] = $GLOBALS[a_dokumentid]?$GLOBALS[a_dokumentid]:0;
  $CISLO_JEDNACI1 = $CISLO_JEDNACI1?$CISLO_JEDNACI1:0;
  $CISLO_JEDNACI2 = $CISLO_JEDNACI2?$CISLO_JEDNACI2:0;
  $GLOBALS[a_TypAdr] = $GLOBALS[a_TypAdr]?$GLOBALS[a_TypAdr]:'0';
//  $ODESLANO = $GLOBALS["a_ze_dne"]; //mozna upravit datum
  $DOPORUCENE = $GLOBALS["a_typodesl"];

  $listu = $GLOBALS[a_pocetlistu] ? $GLOBALS[a_pocetlistu] : 0;
  $priloh = $GLOBALS[a_pocetpriloh] ? $GLOBALS[a_pocetpriloh] : 0;
  $druh_priloh = $GLOBALS[a_druhpriloh] ? $GLOBALS[a_druhpriloh] : 'písemné';
   If ($GLOBALS[a_pocetlistu]) $sql[] = "update posta set pocet_listu = '$GLOBALS[a_pocetlistu]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_pocetpriloh]) $sql[] = "update posta set pocet_priloh = '$GLOBALS[a_pocetpriloh]',$add_info where id = ".$GLOBALS["a_id"];
  If ($GLOBALS[a_druhpriloh]) $sql[] = "update posta set druh_priloh = '$GLOBALS[a_druhpriloh]',$add_info where id = ".$GLOBALS["a_id"];

  //odeslani ceskou postou
  If (!$GLOBALS[a_typdor]) $VLASTNICH_RUKOU = 1; else $VLASTNICH_RUKOU = $GLOBALS[a_typdor];

  If ($GLOBALS[a_odbor_id]) {
    $GLOBALS[a_TypAdr] = "X";
    $GLOBALS[a_prijobyv] = UkazOdbor($ODBOR);
    $GLOBALS[a_jmobyv] = UkazUsera($GLOBALS["a_prac"]);
  }


  //druh dokumentu
  If (!$GLOBALS["a_druh_dokumentu"]) $typ_posty = 0; else $typ_posty = $GLOBALS["a_druh_dokumentu"];
  if (!$odbor || $odbor == 0) {
    $text = '(ZALOZ_PISEMNOST) - Nenalezen odbor '.$ODBOR.' ('.$odbor.') pro pracovníka '.$GLOBALS["a_prac"];
    WriteLog($software_id,$text,$session_id,1);
    echo "    <b_error>$text</b_error>\n";
    echo "    </pisemnost>\n";
    Die();
  }

   if ($CISLO_JEDNACI1 == 0) {
     $CISLO_SPISU1 = 0;
     $CISLO_SPISU2 = 0;
   }
   else {
     $CISLO_SPISU1 = $CISLO_JEDNACI1;
     $CISLO_SPISU2 = $CISLO_JEDNACI2;
   }
        $sql = "insert into posta (ev_cislo,rok,odbor,oddeleni,typ_posty,odes_typ,vec,odesl_prijmeni,odesl_jmeno,odesl_titul,odesl_ico,odesl_ulice,odesl_cp,odesl_cor,
odesl_psc,  odesl_posta,odesl_datschranka,datum_podatelna_prijeti,referent,odeslana_posta,doporucene,vlastnich_rukou,dorucenka,cislo_spisu1,cislo_spisu2,id_puvodni,
odesl_odd,  odesl_osoba,last_date,last_time,last_user_id,owner_id,skartace,dalsi_prijemci,cislo_jednaci1,cislo_jednaci2,odbor_spisu,obyvatel_kod,obalka_nevracet,obalka_10dni,
pocet_listu, pocet_priloh, druh_priloh )  values
($ev_cislo,$rok,$odbor,$oddeleni,$typ_posty,'$GLOBALS[a_TypAdr]','$GLOBALS[a_vec]','$GLOBALS[a_prijobyv]','$GLOBALS[a_jmobyv]','$GLOBALS[a_titul]','$GLOBALS[a_RcIc]','$GLOBALS[a_cobce]','$GLOBALS[a_Cd]','$GLOBALS[a_Cor]',
'$GLOBALS[a_psc]','$GLOBALS[a_obec]','$GLOBALS[a_ds]','$ODESLANO',$GLOBALS[a_prac],'t','$DOPORUCENE','$VLASTNICH_RUKOU','$DORUCENKA',$CISLO_SPISU1,$CISLO_SPISU2,$GLOBALS[a_dokumentid],
'$GLOBALS[a_odeslodd]','$osoba','$LAST_DATE','$LAST_TIME',$LAST_USER_ID,$OWNER_ID,'$skartace','$DALSI_PRIJEMCI',$CISLO_JEDNACI1,$CISLO_JEDNACI2,'$ODBOR_SPISU',$GLOBALS[a_idobyvatele],$nevracet,$jen10,
$listu,$priloh, '$druh_priloh')";
   ZapisText($dbname,$sql);
    $a = new DB_POSTA_ISO;
    $a->query($sql);
    $posle_id = $a->getlastid("posta", "ID");

    $sql = 'select * from posta where id = '.$posle_id;
    if (!$a->query($sql))
    {
        $text = '(ZALOZ_PISEMNOST) - query: '.$sql;
        WriteLog($software_id,$text,$session_id,1);
        echo "    <b_error>CHYBA pri ulozeni do DB</b_error>\n";
        echo "    </pisemnost>\n";
        Die();
    }
    $a->Next_Record(); $EV_CISLO = $a->Record["EV_CISLO"];

    $doc = LoadClass('EedDokument', $posle_id);
    $cj = $doc->cislo_jednaci;
    $text = '(ZALOZ_PISEMNOST) - ulo¾eno èj. '.$cj.'';
//    WriteLog($software_id,$text,$session_id);

    $text = 'VITA: Vytvoøení nového dokumentu z Vity';
//    EedTransakce::ZapisLog($posle_id, $text, 'DOC', $id_user);

    If ($GLOBALS["a_spisid"]) {

      $spis = LoadClass('EedDokument', $GLOBALS['a_spisid']);
      $doc = LoadClass('EedDokument', $posle_id);

      if ($spis->cislo_jednaci <> $doc->cislo_jednaci) {
        $sqlx="insert into cis_posta_spisy (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID) VALUES ('".$spis->cislo_jednaci."','".$doc->cislo_jednaci."',".$GLOBALS['a_spisid'].",".$posle_id.",'$LAST_DATE','$LAST_TIME',$LAST_USER_ID,$LAST_USER_ID)";
        $a->query($sqlx);

        $text = 'VITA: dokument (<b>'.$posle_id.'</b>) '.$doc->cislo_jednaci.' byl vlo¾en do spisu: <b>' . $spis->cislo_jednaci . '</b>';
//        EedTransakce::ZapisLog($GLOBALS["a_spisid"], $text, 'DOC', $id_user);
      }
    }

   if ($GLOBALS[a_dokumentid]) {
      //prekopirujeme vsechny soubory, co jsou

      if ($GLOBALS[a_files])
        $ktere = explode(',',$GLOBALS[a_files]);
      else
        $ktere = array();

     $text = CopyFilesDokument('VITA',$GLOBALS[a_dokumentid],$posle_id,$ktere);
   }

   EedCeskaPosta::NastavCK($posle_id);
   $barcode = EedCeskaPosta::VratCK($posle_id);
   $carovy_kod = $barcode ? $barcode : $EV_CISLO."/".$rok;

   echo "    <b_error>0</b_error>\n";
   echo "    <b_id>$posle_id</b_id>\n";
   echo "    <b_cp>$carovy_kod</b_cp>\n";
   echo "    <b_cj>".$a->Record["CISLO_SPISU1"]."/".$a->Record["CISLO_SPISU2"]."</b_cj>\n";
   echo "    <b_cj_full>".$cj."</b_cj_full>\n";


   NastavStatus($posle_id,$id_user);

  If ($GLOBALS[a_odbor_id]) {
  //zalozime vnitrni postu pracovnikovi...
    $nazev_odboru = UkazOdbor($ODBOR);
    $pracovnik = UkazUsera($GLOBALS["a_prac"]);
    $cj1 = $a->Record["CISLO_JEDNACI1"];
    $cj2 = $a->Record["CISLO_JEDNACI2"];
    $sql = "insert into posta (ev_cislo,rok,odbor,typ_posty,odes_typ,vec,odesl_prijmeni,odesl_jmeno,
    datum_podatelna_prijeti,referent,odeslana_posta,cislo_spisu1,cislo_spisu2,id_puvodni,
    last_date,last_time,last_user_id,owner_id,skartace,dalsi_prijemci,cislo_jednaci1,cislo_jednaci2,odbor_spisu,obalka_nevracet,obalka_10dni)  values
    ($ev_cislo,$rok,$GLOBALS[a_odbor_id],0,'X','$GLOBALS[a_vec]','$nazev_odboru','$pracovnik',
    '$ODESLANO',NULL,'f',$CISLO_SPISU1,$CISLO_SPISU2,$GLOBALS[a_dokumentid],
    '$LAST_DATE','$LAST_TIME',$LAST_USER_ID,$OWNER_ID,'$SKARTACE','$DALSI_PRIJEMCI',$cj1,$cj2,'$ODBOR_SPISU',$nevracet,$jen10)";
    $a->query($sql);

    $text = '(ZALOZ_PISEMNOST) - ulo¾en vnitøní dokument';
    WriteLog($software_id,$text,$session_id);

  }
  $GLOBALS['a_id'] = $posle_id;
}
If ($GLOBALS[a_typdor] == 6) {
  ZalozNovyDokument($GLOBALS['a_id'],1,1);
  $a = new DB_POSTA_ISO;
  $sql="update posta set datum_vypraveni='".date('Y-m-d H:i:s')."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$id_user where id=".$GLOBALS['a_id'];
  $a->query($sql);
  NastavStatus($GLOBALS['a_id'], $id_user);



}
echo "  </pisemnost>\n";
