<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/zaloz.inc"));
require(FileUp2("html_header_full.inc"));

include_once(FileUp2('.config/config.inc'));

if(!$GLOBALS['TMAPY_SECURITY_WHOIS']) { ///TODO: kdyz nebude, tak ho vytvorit
  $sec_file = $GLOBALS["TMAPY_LIB"] . "/security/whois.inc";
  include($sec_file);
  $GLOBALS["TMAPY_SECURITY_WHOIS"] = new Security_Obj_WhoIS();
//    $this->ShowError('T-WIST security object not exist !', true) ;
}
$q = new DB_POSTA;

foreach($_POST['SELECT_ID'] as $key) {

  Access(array(
    "agenda"=>"POSTA_PLUGINS_UK_PRAC",
    ));

  $pracovnik = $GLOBALS['TMAPY_SECURITY_WHOIS']->GetPracovnik($key);
  $znacka = 'Z' . $pracovnik['CISLO_UK'] . '/' . $pracovnik['ID_ORG'];
  $nazev = 'Pracovník ' . $pracovnik['PRIJMENI'] . ' ' . $pracovnik['JMENO'];
//Die(print_r($pracovnik));
  $id = ZalozTypovySpis($znacka, $nazev, $pracovnik['ID_ORG'], $_POST['REFERENT'], $_POST['TYPOVY_SPIS']);

  //dodelat pripadny update pro dokument -
   UNSET($GLOBALS['ID']);
   $GLOBALS['EDIT_ID'] = $id;
   $GLOBALS['ODESL_JMENO'] = $pracovnik['JMENO'];
   $GLOBALS['ODESL_PRIJMENI'] = $pracovnik['PRIJMENI'];
   $GLOBALS['WHOIS_NUMBER'] = $pracovnik['CISLO_UK'];
//   $GLOBALS['WHOIS_IDSTUDIA'] = $pracovnik['STUD_ID'];
   UNSET($GLOBALS['NAZEV_SPISU']);
   $GLOBALS['ODES_TYP'] = 'G';
   $GLOBALS['STATUS'] = '-7'; //otevreny typovy spis
/*
   $GLOBALS['POZNAMKA'] = 'PREDCHOZI=' . $pracovnik['RODNE_PRIJMENI'] . '
FAKULTA=' . $pracovnik['HRANA_NAZEV'] . '
PROGRAM=' . $pracovnik['STUD_PROGRAM'] . '
OBOR=' . $pracovnik['STUD_OBOR_1'] . '
FORMA=' . $pracovnik['STUD_FORMA'] . '
ROK=' . $pracovnik['DATUM_OD'] . '
';
*/
  echo "Založen typový spis $znacka - $nazev  - $id<br/>";
//	$sql = Run_(array("agenda"=>"POSTA", "showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>true,"returntype"=>2));
//  echo $sql;
//  $q->query($sql);
  Access(array(
    "agenda"=>"POSTA_PLUGINS_UK_PRAC",
    ));

	Run_(array("agenda"=>"POSTA", "showaccess"=>false,"outputtype"=>1));
//  Die();
}

echo '<a class="btn" href="synchro.php?insert&cacheid=" title="Návrat zpět">Návrat zpět</a>';
require(FileUp2("html_footer.inc"));

/*
Sxxxxxxx/yyyyy
S ……. Student
xxxxxxx …….. číslo osoby z Whois
yyyy …………    identifikace oboru studia (studijního programu) ze SISU
*/
