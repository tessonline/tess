<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
//include(FileUp2(".admin/oth_funkce_2D.inc"));
include(FileUp2(".admin/run2_.inc"));
include(FileUp2("interface/.admin/soap_funkce.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

$q = new DB_POSTA;

$show = 1;

Function czdate2engCSV($engdatum)
{
  $date1 = $engdatum;
// Odstranime cas...
  $datumkod=explode(".",$date1);
  if (strlen($datumkod[0])<2) $datumkod[0]="0".$datumkod[0];
  if (strlen($datumkod[1])<2) $datumkod[1]="0".$datumkod[1];
  $odeslano=$datumkod[2]."-".$datumkod[1]."-".$datumkod[0];
//  $odeslano=strtotime ($datumkod[2]."-".$datumkod[1]."-".$datumkod[0]);
  return $odeslano;
}


function FormatText($text, $hodnota) {
  if ($text =='' || $hodnota == 0) $text = 'nenalezeno';
  if ($hodnota == 0)
    $text = '<font color=red>' . $text . '</font>';
  else
    $text = $text . ' (' . $hodnota . ')';
  return $text;
}

function VratSkartace($text) {
  global $q;
  $sql = "select * from cis_posta_skartace where text like '%$text%' and aktivni=1";
  $q->query($sql);
  if ($q->Num_Rows() == 1) {
    $q->NExt_Record();
    return $q->Record['ID'];
  }
  else {
    return 0;
  }

}

function VratCSVOdbor($text) {
  global $q;
  $sql = "select o.id from cis_posta_odbory o left join security_group g ON g.id=o.id_odbor where name like '%$text%'";
  $q->query($sql);
  if ($q->Num_Rows() == 1) {
    $q->NExt_Record();
    return $q->Record['ID'];
  }
  else {
    return 0;
  }
}

function VratMaxPoradove() {
  global $q;
  $sql = "select max(poradove) as MAX_PORAD from posta_spisovna";
  $q->query($sql);
  return $q->Record['MAX_PORAD'];
}


if (!$provest) {
  require(FileUp2('html_header_full.inc'));
  if ($_FILES['UPLOAD_FILE'][type] <> 'application/vnd.ms-excel') {
    echo "Soubor neni CSV type";
    Die();   
    
  }
  $file = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$_FILES["UPLOAD_FILE"]["name"];
  if(!move_uploaded_file($_FILES["UPLOAD_FILE"]["tmp_name"],$file))
  {
       echo "Something is wrong with the file";
        exit;
  }
//  $file = $_FILES['UPLOAD_FILE']['tmp_name'];
  
} else {
  $file = $file_import;
}
//Pořadové číslo předávky	Rok předávky	Předávající odbor/součást (spisový uzel)	Souhrn č.j. v předávce	Věc	Rok uzavření spisů	Spisový znak (podle OR č. 6/2013)
//Skartační znak a lhůta (podle spisového plánu platného v době uzavření spisu)	Předal	Převzal	Datum předání do spisovny	Vyřadit v roce	Uložení	Vyřazeno


$fp = fopen($file, 'r');
$data = fread($fp, filesize($file));
fclose($fp);


$data_array = explode(chr(13), $data);
$pocet = 0;
$max_pocet = VratMaxPoradove();

foreach($data_array as $data_radek ) {
  $pocet ++;
  if (strlen($data_radek)<10) continue;
  $data_radek = iconv('WINDOWS-1250', 'UTF-8', $data_radek);
  $data = explode(';', $data_radek );
  $dokument = array();
  $dokument['REGISTRATURA'] = -1; //rucni vlozeni
  $dokument['SPISOVNA_ID'] = $_GET['SPISOVNA_ID'];
  if ($data[0] == ($pocet + $max_pocet)) {
     $dokument['PORADOVE'] = $data[0];
  }
  else {
     $dokument['PORADOVE'] = '<font color=red>Neodpovídá pořadí:<br/>' . $data[0] . ' - má být '.($pocet+$max_pocet).'</font>';
     $show = false;
  }
//  $dokument['CISLO_SPISU1'] = $data[0];
  $dokument['ROK_PREDANI'] = $data[1];
  $dokument['ODBOR'] = VratCSVOdbor($data[2]);
  $dokument['ODBOR_TEXT'] = FormatText(UkazOdbor($dokument['ODBOR']), $dokument['ODBOR']);
  $dokument['VLOZENA_CJ'] = $data[3];
  $dokument['VEC'] = $data[4];
  $dokument['ROK_PREDANI'] = $data[5];
  $dokument['SKARTACE_ID'] = VratSkartace($data[6]);
  $dokument['SKARTACE_TEXT'] = FormatText($data[6], $dokument['SKARTACE_ID']);
  $dokument['SKAR_ZNAK'] = substr($data[7], 0, 1);
  $dokument['LHUTA'] = substr($data[7], 1);

  $dokument['LAST_USER_ID'] = (integer) $data[8];
  $dokument['LAST_USER_TEXT'] = FormatText(UkazUsera($dokument['LAST_USER_ID']), $dokument['LAST_USER_ID']);
  $dokument['PREVZAL_ID'] = (integer) $data[9] ? (integer) $data[9] : $USER_INFO['ID'];
  $dokument['PREVZAL_TEXT'] = FormatText(UkazUsera($dokument['PREVZAL_ID']), $dokument['PREVZAL_ID']);
  $dokument['DATUM_PREDANI'] = czdate2engCSV($data[10]);
  $dokument['LAST_DATE'] = czdate2engCSV($data[10]);

  $dokument['ROK_SKARTACE'] = $data[11]; //pokud neni, dopocitat
  $dokument['POZNAMKA'] = $data[12];
  if ($data[0]>0) $dokumenty[] = $dokument;

}


if ($provest) {
  $show = false;

  foreach($dokumenty as $dokument) {
    foreach($dokument as $key =>$val )
    	$GLOBALS[$key] = $dokument[$key];
    //ulozime
    Run_(array('agenda'=>'SKARTACNI_KNIHA','outputtype'=>1));
    UNSET($GLOBALS['EDIT_ID']);
  }
}

$pocet_celkem = count($dokumenty);
$pocet = 0;
$pocet_souboru = 0;


//echo $seznam->getAttribute('identifikatorArchivu');
//$id = -1;



include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
$db_arr = new DB_Sql_Array;
$db_arr->Data=$dokumenty;

//error_reporting (E_ALL);
UNSET($GLOBALS["ukaz_ovladaci_prvky"]);
Table(
  array(
    "db_connector" => &$db_arr,
    "schema_file" => ".admin/table_schema_csv.inc",
    "showaccess" => false,
    "caption" => "Načtené údaje",
    "showedit"=>false,
    "showdelete"=>false,
    "setvars" => false,
    "showinfo"=>false,
    "showhistory"=>false,
    "showcount"=>false,
//    "schema_file"=>".admin/table_schema_certifikat.inc"
  )
);

if ($show) {
  echo '
<form method="GET" action="#">
<input type="hidden" name="file_import" value="' . $file . '">
<input type="hidden" name="SPISOVNA_ID" value="' . $GLOBALS['SPISOVNA_ID'] . '">
<input type="hidden" name="provest" value="1">
<input type="submit" class="btn" value="  Skutečně importovat   ">
</form>

';
}
else {

echo '
	<input type="button" class="btn" value="  Zavřít   " onclick="window.opener.document.location.reload();">
	';
}
//print_r($xml->Dokumenty);
require_once(FileUp2("html_footer.inc"));

