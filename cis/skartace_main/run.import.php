<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2("interface/.admin/soap_funkce.inc"));


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
/*
// Enable user error handling
libxml_use_internal_errors(true);

$xml = new DOMDocument();
*/


//print_r($_FILES); Die();
require(FileUp2('html_header_full.inc'));

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

$xml=simplexml_load_file($file);

$json = json_encode($xml);
$array = array();
$array = json_decode($json,TRUE);

//$xml->load('test2.xml');

/*
if (!$xml->schemaValidate(FileUp2('xsd/nsesss-plan.xsd'))) {
    print '<b>Byly nalezeny chyby XML</b>';
    libxml_display_errors();
}
*/

//echo $seznam->getAttribute('identifikatorArchivu');
//$id = -1;

function UlozVecnyPlan($plan, $nadrazene_id) {
  global $ret;

  $id = $plan['@attributes']['ID'];
  $ret[$id]['ID'] = $id;
  $ret[$id]['KOD'] = $plan['EvidencniUdaje']['Trideni']['PlneUrcenySpisovyZnak'];
  if (strlen($plan['EvidencniUdaje']['Popis']['Nazev'])>5)
    $ret[$id]['TEXT'] = $plan['EvidencniUdaje']['Popis']['Nazev'];
  else 
  	$ret[$id]['TEXT'] = $plan['EvidencniUdaje']['Popis'];
  	 
  $ret[$id]['SKAR_ZNAK'] = $plan['EvidencniUdaje']['Vyrazovani']['SkartacniRezim']['SkartacniZnak'];
  $ret[$id]['DOBA'] = $plan['EvidencniUdaje']['Vyrazovani']['SkartacniRezim']['SkartacniLhuta'];
  if ($ret[$id]['DOBA']>0) $ret[$id]['TYP'] = 2; else $ret[$id]['TYP'] = 1;
  
  $ret[$id]['NADRAZENE_ID'] = $nadrazene_id;
  if ($plan['PlanVecnaSkupina']) {
    if($plan['PlanVecnaSkupina']['@attributes']) {
      $pomocnik = array();
      $pomocnik = $plan['PlanVecnaSkupina'];
      unset($plan['PlanVecnaSkupina']);
      $plan['PlanVecnaSkupina'] = array();
      $plan['PlanVecnaSkupina'][0] = $pomocnik;
      unset($pomocnik);
    }
  	foreach($plan['PlanVecnaSkupina'] as $plan2)
  	{
  	  UlozVecnyPlan($plan2, $id);
  	} 
  }
}

foreach($array['PlanVecnaSkupina'] as $plan)
{
  UlozVecnyPlan($plan, 0);
}


include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
$db_arr = new DB_Sql_Array;
$db_arr->Data=$GLOBALS['ret'];


if (!$provest) {
  
	UNSET($GLOBALS["ukaz_ovladaci_prvky"]);
	Table(
			array(
					"db_connector" => &$db_arr,
					"showaccess" => true,
					"caption" => "Načtené údaje",
					"agenda"=>'POSTA_CIS_SKARTACE',
					"showedit"=>false,
					"showdelete"=>false,
					"setvars" => true,
					"showinfo"=>false,
					"showcount"=>false,
					"page_size" => 10000,
					//    "schema_file"=>".admin/table_schema_certifikat.inc"
			)
			);
	
}
else {
  error_reporting(E_ERROR & E_PARSE);
  $sql = 'select max(id) as max_id from cis_posta_skartace';
  $q = new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
  $max_id = $q->Record['MAX_ID'] + 10;
  $mainid = $GLOBALS['MAIN_ID'];
  require_once(FileUp2('.admin/run2_.inc'));
	foreach($GLOBALS['ret'] as $udaj) {
      $udaj['ID'] = $udaj['ID'] + $max_id;
      if ($udaj['NADRAZENE_ID']>0) $udaj['NADRAZENE_ID'] = $udaj['NADRAZENE_ID'] + $max_id;
      foreach($udaj as $key => $val) $GLOBALS[$key] = $val;
      UNSET($GLOBALS['EDIT_ID']);
      $GLOBALS['MAIN_ID'] = $mainid;
       Run_(array(
		"agenda"=>'POSTA_CIS_SKARTACE',
      		"showaccess"=>true,
      		"outputtype"=>1
      ));
	}
echo '
<input type="button" class="btn" value="  Vše importováno, zavřít   " onclick="window.opener.document.location.reload();">
		';
	require_once(FileUp2("html_footer.inc"));
Die();
}
if (!$provest) {
  echo '
<form method="GET" action="#">
<input type="hidden" name="file_import" value="' . $file . '">
<input type="hidden" name="provest" value="1">
<input type="hidden" name="MAIN_ID" value="'.$GLOBALS['MAIN_ID'].'">
		<input type="submit" class="btn" value="  Skutečně importovat   ">
</form>

';
}
//print_r($xml->Dokumenty);
require_once(FileUp2("html_footer.inc"));

