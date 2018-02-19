<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/zaloz.inc"));
require(FileUp2("html_header_full.inc"));

include_once(FileUp2('.config/config.inc'));


set_time_limit(0);

if (!$_POST['omez_typ']) Die('Vnitřní chyba, není předán druh studia');

if(!$GLOBALS['TMAPY_SECURITY_WHOIS']) { ///TODO: kdyz nebude, tak ho vytvorit
  $sec_file = $GLOBALS["TMAPY_LIB"] . "/security/whois.inc";
  include($sec_file);
  $GLOBALS["TMAPY_SECURITY_WHOIS"] = new Security_Obj_WhoIS();
//    $this->ShowError('T-WIST security object not exist !', true) ;
}
$q = new DB_POSTA;

foreach($_POST['SELECT_ID'] as $key) {

  Access(array(
    "agenda"=>"POSTA_PLUGINS_UK_STUDENT",
    ));

  $student = $GLOBALS['TMAPY_SECURITY_WHOIS']->GetStudent(0, array('studium_typ' => $_POST['omez_typ'],'IDStudia'=>$key));
  $znacka = 'S' . $student['CISLO_UK'] . '/' . $student['STUD_ID'];
  $nazev = 'Student ' . $student['PRIJMENI'] . ' ' . $student['JMENO'];
  $id = ZalozTypovySpis($znacka, $nazev, $student['ID_ORG'], $_POST['REFERENT'], $_POST['TYPOVY_SPIS']);

  //dodelat pripadny update pro dokument -
   UNSET($GLOBALS['ID']);
   $GLOBALS['EDIT_ID'] = $id;
   $GLOBALS['ODESL_JMENO'] = $student['JMENO'];
   $GLOBALS['ODESL_PRIJMENI'] = $student['PRIJMENI'];
   $GLOBALS['WHOIS_NUMBER'] = $student['CISLO_UK'];
   $GLOBALS['WHOIS_IDSTUDIA'] = $student['STUD_ID'];
   UNSET($GLOBALS['NAZEV_SPISU']);
   $GLOBALS['ODES_TYP'] = 'C';
   $GLOBALS['STATUS'] = '-7'; //otevreny typovy spis

   $GLOBALS['POZNAMKA'] = 'PREDCHOZI=' . $student['RODNE_PRIJMENI'] . '
FAKULTA=' . $student['HRANA_NAZEV'] . '
PROGRAM=' . $student['STUD_PROGRAM'] . '
OBOR=' . $student['STUD_OBOR_1'] . '
FORMA=' . $student['STUD_FORMA'] . '
ROK=' . $student['DATUM_OD'] . '
';
  echo "Založen typový spis $znacka - $nazev  - $id<br/>";
//	$sql = Run_(array("agenda"=>"POSTA", "showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>true,"returntype"=>2));
//  echo $sql;
//  $q->query($sql);
  Access(array(
    "agenda"=>"POSTA_PLUGINS_UK_STUDENT",
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
