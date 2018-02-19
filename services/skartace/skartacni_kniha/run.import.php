<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2("interface/.admin/soap_funkce.inc"));
require(FileUp2('html_header_full.inc'));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$last_date=Date('Y-m-d');
$last_time=Date('H:i:s');
$datum=date('d.m.Y H:m');

function libxml_display_error($error)
{
    $return = "<br/>\n";
    switch ($error->level) {
        case LIBXML_ERR_WARNING:
            $return .= "<b>Upozornění: $error->code</b>: ";
            break;
        case LIBXML_ERR_ERROR:
            $return .= "<b>Chyba: $error->code</b>: ";
            break;
        case LIBXML_ERR_FATAL:
            $return .= "<b>Fatální chyba: $error->code</b>: ";
            break;
    }
    $return .= trim($error->message);
    if ($error->file) {
        $return .=    " v <b>".basename($error->file)."</b>";
    }
    $return .= " na řádku <b>$error->line</b>\n";

    return $return;
}

function libxml_display_errors() {
    $errors = libxml_get_errors();
    foreach ($errors as $error) {
        print libxml_display_error($error);
    }
    libxml_clear_errors();
}

// Enable user error handling
libxml_use_internal_errors(true);

$xml = new DOMDocument();

//print_r($_FILES); Die();

if (!$provest) {
  if ($_FILES['UPLOAD_FILE'][type] <> 'text/xml') {
    echo "Soubor neni XML type";
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
  
$xml->load($file);
//$xml->load('test2.xml');

if (!$xml->schemaValidate(FileUp2('.admin/xsd/import_schema.xsd'))) {
    print '<b>Byly nalezeny chyby XML</b>';
    libxml_display_errors();
}



if ($provest) {
  if ($cj1 == 10000) {
    $id = $sqlObj->createCJ($GLOBALS['REFERENT']);
    $prvni_id = $id;
//Die($id);
    $doc = LoadClass('EedDokument',$id);
    $cj1 = $doc->cj1;
    $cj2 = $doc->cj2;
    $GLOBALS['SUPERODBOR'] = $doc->zarizeni;
  }
}

$pocet_celkem = count($dokumenty);
$pocet = 0;
$pocet_souboru = 0;



$seznam = $xml->getElementsByTagName("Seznam")->item(0);

foreach($seznam->attributes as $singleAttr) {
  $arrAtributy[$singleAttr->nodeName] = $singleAttr->nodeValue;
}
$archiv = "Identifikátor archivu: <b>".$arrAtributy["identifikatorArchivu"]."</b>"
        . ", Identifikátor skartačního řízení: <b>".$arrAtributy["identifikatorSkartacnihoRizeni"]."</b>"
        . ", Datum vytvoření skartačního řízení: <b>".$arrAtributy["datumVytvoreni"]."</b>";

// print_r($archiv);
// die($valueID);
$entity = $xml->getElementsByTagName("EntitaSeznamu");

$qq = new DB_POSTA;
$sql = 'SELECT s.* FROM posta_spisovna s WHERE s.id in (select spisovna_id from posta_skartace_id WHERE skartace_id=' . $GLOBALS['SKARTACNI_RIZENI_ID'].')';
$qq->query($sql);
$doc_ids = array();
while ($qq->Next_Record()) {
  $doc_ids[$qq->Record['DOKUMENT_ID']] = $qq->Record['ID'];	
}

$dokument_array = array();
//echo $seznam->getAttribute('identifikatorArchivu');
//$id = -1;
foreach($entity as $entita)
{
  $pocet ++;

  $dokument = array();
  $dokument['ID'] = $entita->getElementsByTagName("Identifikator")->item(0)->nodeValue;
  $dokument['IDARCH'] = $entita->getElementsByTagName("IdentifikatorDA")->item(0)->nodeValue;
  $dokument['OPERACE'] = TxtEncodingFromSoap($entita->getElementsByTagName("Operace")->item(0)->nodeValue);

  $doc = LoadClass('EedCj', $dokument['ID']);
  $dokument['CJ'] = $doc->cislo_jednaci;
  //if (in_array($dokument['ID'], $doc_ids))
  $doc_id = $dokument['ID'];

  if ($provest) {
  	switch ($dokument['OPERACE']) {
  	case 'vyřadit z výběru':
  		$sql = 'delete from posta_skartace_id where skartace_id=' . $GLOBALS['SKARTACNI_RIZENI_ID'] . ' and spisovna_id=' . ($doc_ids[$doc_id] ? $doc_ids[$doc_id] : 0);
  		$protokol = "Spis/čj. <b>" . $doc_id ." </b> byl vyjmut ze skartačního řízení. ".$archiv;
  		$text = 'vyřazeno ze seznamu';
  		break;
  	case 'vybrat za archiválii':
  		$sql = "update posta_spisovna set skar_znak_alt='A',skar_znak='A',last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where dokument_id=" . $doc_id;
  		$protokol = "Spis/čj. <b>" . $doc_id ." </b> byl označen skartačním znakem A. ".$archiv;
  		$text = 'nastavena archiválie';
  	    break;
  	case 'zničit':
  		$sql = "update posta_spisovna set skar_znak_alt='S',skar_znak='S',last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where dokument_id=" . $doc_id;
  		$protokol = "Spis/čj. <b>" . $doc_id ." </b> byl označen skartačním znakem S. ".$archiv;
  		$text = 'nastaven stoupa';
  		break;
  	}
  		$dokument['OPERACE'] = $text;
        EedTransakce::ZapisLog($doc_id, $protokol, 'SPIS', $id_user);
        EedTransakce::ZapisLog($doc_id, $protokol, 'DOC', $id_user);

      if ($dokument['IDARCH']<>'') {
    		$protokol = "Spis/čj. <b>" . $doc_id ." </b> byl zadán identifikátor archivu <b>".$dokument['IDARCH']."</b> - " . $archiv;
        EedTransakce::ZapisLog($doc_id, $protokol, 'SPIS', $id_user);
        EedTransakce::ZapisLog($doc_id, $protokol, 'DOC', $id_user);
      }
        if ($sql<> '') $qq->query($sql); 
  }
  if (!array_key_exists($doc_id, $dokument_array))  $dokument_array[$doc_id] = $dokument;
} 

//$dokument_array = array_unique( $dokument_array );



include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
$db_arr = new DB_Sql_Array;
$db_arr->Data = $dokument_array;

//error_reporting (E_ALL);
UNSET($GLOBALS["ukaz_ovladaci_prvky"]);

$GLOBALS['DO_NOT_LOAD_FUNC'] = true;

Table(
  array(
    "db_connector" => &$db_arr,
    "showaccess" => true,
    "showedit"=>false,
    "showdelete"=>false,
    "setvars" => true,
    "showinfo"=>false,
  	"showhistory"=>false,
    "showcount"=>false,
    "schema_file" => ".admin/table_schema_import.inc",
    "caption" => "Načtené údaje",
  )
);
//   Table(array(
//   "db_connector" => &$db_arr,
//   "showaccess" => true,
//   "appendwhere"=>$where2,
//   "showedit"=>false,
//   "showdelete"=>false,
//   "showselect"=>false,
//   "showinfo"=>false,
//   "multipleselect"=>false,
//   "schema_file"=>".admin/table_schema_DORUCENKY.inc",
//   "caption"=>"Doručenky"));



if (!$provest) {
  echo '
<form method="GET" action="#">
<input type="hidden" name="file_import" value="' . $file . '">
<input type="hidden" name="SKARTACNI_RIZENI_ID" value="' . $GLOBALS['SKARTACNI_RIZENI_ID'] . '">
		<input type="hidden" name="provest" value="1">
<input type="submit" class="btn" value="  Skutečně importovat   ">
</form>

';
} 
else {
	echo '<h1>Import dokončen </h1>';
  echo '<p>
	<input type="button" class="btn" value="  Zavřít   " onclick="window.opener.document.location.reload();"></p>
	';
}
//print_r($xml->Dokumenty);
require_once(FileUp2("html_footer.inc"));

