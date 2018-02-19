<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('.admin/brow_func.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));
require_once(FileUp2('.admin/has_access.inc'));

require(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));
require(FileUp2('html_header_full.inc'));
$EddSql = LoadClass('EedSql');

NewWindow(array("fname" => "AgendaSpis", "name" => "AgendaSpis", "header" => true, "cache" => false, "window" => "edit"));
NewWindow(array("fname" => "Guide", "name" => "Guide", "header" => true, "cache" => false, "window" => "edit"));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

$doc_id = $_GET['doc_id'];
$spis_id = $doc_id;
$cj_obj = LoadClass('EedCj',$doc_id);
$cj_info = $cj_obj->GetCjInfo($doc_id);
$main_doc = $cj_info['MAIN_DOC'];
$where_cj = $cj_obj->GetWhereForCJ($doc_id);
$spis_id = $cj_info['SPIS_ID'];

$hlavni_doc = $doc_id;

$spis_uzavren = false;
$lze_editovat = true;
$lze_uzavrit = LzeUzavritSpis_Obj($doc_id);

$mamPravaNaSpis = false;

$GLOBALS['EDIT_ID'] = $doc_id; //kvuli MaPristupKDokumentu_table
if ($USER_INFO[ID] == $cj_info['REFERENT']) $mamPravaNaSpis = true;
if (MaPristupKDokumentu_old($cj_info['REFERENT'],$doc_id)) $mamPravaNaSpis = true;

$q = new DB_POSTA;
if ($cj_info['SPIS_VYRIZEN']) $datum_uzavreni_spisu = $q->dbdate2str($cj_info['SPIS_VYRIZEN']);
else $datum_uzvreni_spisu = '';

echo '<h1> ';

If ($datum_uzavreni_spisu) {
  $spis_uzavren = true;
  $lze_editovat = false;

 echo "".$cj_info['CELY_NAZEV']." - uzavřeno dne ".$datum_uzavreni_spisu;
}

else {
  $spis_uzavren = false;
  echo $cj_info['CELY_NAZEV'];
}

echo '</h1>';
$q = new DB_POSTA;

EedLog::writeLog('Zobrazení čj/spisu', array('ID' => $GLOBALS['spis_id']));

if ($cj_info['JE_SPIS']) {
  echo "<a  class=\"btn btn-loading\" href=\"/ost/posta/brow_spis.php?doc_id=".$spis_id."\" >Zobrazit ".$cj_info['CELY_NAZEV']."</a>";
}



// ukazujeme pouze jeden spis...
UNSET($GLOBALS['SUPERODBOR']);

$GLOBALS["ukaz_ovladaci_prvky"]=false;


$sql = Table(array(
  "tablename" => $spis_id,
  "caption" => "Dokumenty k " . $cj_info['CELE_CISLO'],
  "sql" => "select * from posta WHERE ".$where_cj." order by id desc",
  //"showaccess" => true,
  "showupload" => false,
  "modaldialogs" => false,
  "schema_file" => '.admin/table_schema_spis.inc',
  "setvars" => true,
  'showcount' => false, //protahuje to tabulku
  "showhistory" => true,
  "showupload" => true,
  "select_id" => "ID" ,
  "unsetvars" => true ,
  ));
$GLOBALS["ukaz_ovladaci_prvky"]=true;
//$majitelspisu=MajitelSpisu($cislo_spisu1,$cislo_spisu2);



//jdeme z evidence, tak ukazeme tlacitko zpet.
If ($GLOBALS["FROM_EVIDENCE"])
  echo "<input type=button class=button onclick=\"history.back(-1)\" value='   Zpět   '>";


  //pokud je zapnuto pridavani dalsich zaznamu do spisu
if ($GLOBALS["CONFIG"]["SPIS_PREHLED_DALSI_ZAZNAMY"]) {
  if (!JeUzavrenSpis($cislo_spisu1,$cislo_spisu2,$referent) && !$GLOBALS["FROM_EVIDENCE"]) {
    $spis_where = " and cislo_spisu1 = $cislo_spisu1 and cislo_spisu2 = $cislo_spisu2";
    Table(array(
      "agenda"=>"POSTA_SPISPREHLED_ZAZNAMY",
      "tablename"=>"posta_spisprehled_zaznamy",
      "appendwhere"=>$spis_where,
      "maxnumrows"=>25,
      "nopaging"=>true,
      "showdelete"=>true,
      "showedit"=>true,
      "showinfo"=>true,
      "nocaption"=>false,
      "showaccess"=>true,
      "setvars"=>true,
      "unsetvars"=>true,
      "emptyoutput"=>true,
    ));
    $xx=new DB_POSTA;
  	$sql="select id,nazev_spisu from posta where cislo_spisu1='".$cislo_spisu1."' and cislo_spisu2='".$cislo_spisu2."'";
    $xx->query($sql);
  //	echo $sql;
  	$xx->Next_Record();
   	$nazev_spisu = $xx->Record["NAZEV_SPISU"];
    echo "
    <p><a class=\"btn btn-loading\" href=\"#\" onclick=\"javascript:NewWindowAgendaSpis('services/spisovka/spisprehled/edit.php?insert&cislo_spisu1=".$cislo_spisu1."&cislo_spisu2=".$cislo_spisu2."&referent=".$referent."&nazev_spisu=".$nazev_spisu."&cacheid=')\">Přidat dokument k ".$GLOBALS["CONFIG"]["CISLO_SPISU_3P"]." ".$cislospisu."</a>
    </p>";
  }
}

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/brow_cj_end.php');
		if (File_Exists($file)) include($file);
  }
}


require(FileUp2('html_footer.inc'));

//  print_r($vysledek);
