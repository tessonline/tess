<?php 
require("tmapy_config.inc");
$csv = (isset($_GET['CSV'])) ? true : false;
$soubor = ($csv) ? "prehled_agend.csv" : "prehled_agend.txt";
header("Content-Description: File Transfer");
header("Content-Type: application/force-download");
header("Content-Disposition: attachment; filename=\"$soubor\"");
$q = new DB_POSTA;
$q2 = new DB_POSTA;
$q3 = new DB_POSTA;

$form_params["formtype"] = array($f_edit);
ob_start();
include_once $GLOBALS["TMAPY_LIB"]."/oohformsex.inc";
include_once(Fileup2(".admin/config.inc"));
include_once(Fileup2(".admin/el/of_text_.inc"));
include_once(Fileup2(".admin/el/of_date_.inc"));
include_once(Fileup2(".admin/el/of_select_.inc"));

include(FileUp2('.admin/form_schema_filter_all.inc'));

foreach($FORM_CONFIG['schema'] as $schema) {
   $label_full = $schema['label'];
   if (is_array($schema['elements'])) {
     foreach($schema['elements'] as $elem) {
       if ($elem['label']) $formy[$elem['name']] = array('label'=>$elem['label'], 'type'=>$elem['type']);
       else $formy[$elem['name']] = array('label'=>$label_full, 'type'=>$elem['type']);
     }
   }
}
ob_end_clean();

function getColumnName($hodnota) {
  global $formy;
  if ($formy[$hodnota]['label']<>'') {
    $ret = str_replace(': ', '', $formy[$hodnota]['label']);
    $ret = str_replace(':', '', $ret);
  }
  else
    $ret = $hodnota; //nenasli jsme
  return $ret;
}


function getColumnValue($column, $value, $q) {
  global $formy;
  if ($formy[$column]['type']<>'') {
    $class = 'of_'.$formy[$column]['type'];
    $cls = @new $class;
    $cls->value = $value;
    $GLOBALS["HISTORY_TABLE_IDENT_COLUM"]='NEW';
    if (Method_Exists($cls, "self_get_frozen")) {
        $ret = $cls->self_get_frozen($value, false, $count);
    }
    else
     $ret = $value;

    $ret = preg_replace("#<b>(.*)</b>#i", "\\1", $ret);
    if (preg_match("/<b>/i", $ret))
      $ret = preg_replace("#<b>(.*)</b>#i", "\\1", $ret);
    if ($cls->value != '' && preg_match("/select/i", $formy[$column]['type']))
      $ret .= " (".$cls->value.")";
    if ($cls->value > 0 && preg_match("/checkbox/i", $formy[$column]['type']))
      $ret = "ANO";
    if ($cls->value != '' && preg_match("/date_db/i", $formy[$column]['type']))
      $ret = " ".$q->dbdate2str($cls->value);
    $ret = strip_tags($ret);
    $ret = trim(str_replace('&nbsp;', '', $ret));
    if ($ret == "") $ret = $value;
  }
  else
    $ret = $value; //nenasli jsme
  return $ret;

}



function utfTo1250($text) {
  return iconv("utf-8","cp1250",$text);
}

function zapisCSVRadek($agenda="",$druh_dokumentu="",$spisovy_znak="",$workflow="",$dokument="", $pole="",$hodnota="",$zada_o="",$referent="") {
  $text = "\"".$agenda."\";\"".$druh_dokumentu."\";\"".$spisovy_znak."\";\"".$workflow."\";\"".$dokument."\";\"".$pole."\";\"".$hodnota."\";\"".$zada_o."\";\"".$referent."\"".PHP_EOL;
  echo utfTo1250($text);
}


$sql = "SELECT id, nazev from cis_posta_agenda";
if ($_GET['so']) $sql .= ' WHERE id_superodbor=' . $_GET['so'];
$sql.= " ORDER BY nazev";

$q->query($sql);
if ($csv) {
  echo utfTo1250("\"Agenda\";\"Druh dokumentu\";\"Spisovy znak\";\"Workflow\";\"Dokument\";\"Pole\";\"Hodnota\";\"Žádá o\";\"Referent\"").PHP_EOL;
}
while ($q->next_record()) {    
//  echo "Agenda ".$q->Record['NAZEV']." obsahuje následující druhy dokumentů: ";
  echo ($csv) ? "" : "Agenda \"".$q->Record['NAZEV']."\" ".PHP_EOL;
  echo ($csv) ? "":"=========================================================================".PHP_EOL;
  $agenda_csv = $q->Record['NAZEV'];
  
  $sql2 = "SELECT c.id, c.nazev, s.kod FROM cis_posta_typ c left join cis_posta_skartace s on s.id = c.skartace_id where c.id_agendy=".$q->Record['ID'];
  $q2->query($sql2);
  while ($q2->next_record()) {
    echo ($csv) ? "" : "Druh dokumentu \"".$q2->Record['NAZEV']."\"";
    $druh_dokumentu_csv = $q2->Record['NAZEV'];
    $spisovy_znak_csv = $q2->Record['KOD'];
    
    $sql3 = "SELECT id_workflow,dokument,promenna,hodnota from posta_workflow where id_typ=".$q2->Record['ID']." order by id_workflow asc";
    $q3->query($sql3);
    if ($q3->Num_Rows()>0) 
      echo ($csv) ? "":" má definované následující workflow:".PHP_EOL;
    else {
      echo ($csv) ? "":PHP_EOL."- workflow není definováno".PHP_EOL;
      if ($csv) zapisCSVRadek($agenda_csv,$druh_dokumentu_csv,$spisovy_znak_csv);
    }
      echo ($csv) ? "":"--------------------------------------------------------------------------------------------------".PHP_EOL;
    while ($q3->next_record()) {
      $odchozi_prichozi = ($q3->Record['DOKUMENT']=="O") ? "odchozího" : (($q3->Record['DOKUMENT']=="P") ? "příchozího" : "příchozího i odchozího");
      $dokument_csv = ($q3->Record['DOKUMENT']=="O") ? "odchozí" : (($q3->Record['DOKUMENT']=="P") ? "příchozí" : "příchozí i odchozí");
      
      $id_workflow = $q3->Record['ID_WORKFLOW'];
      if ($id_workflow == 1)  {
        $workflow_csv = "změna dat";
        $pole = $q3->Record['PROMENNA'];
        $pole_csv = getColumnName($pole);
        $hodnota_csv = getColumnValue($pole,$q3->Record['HODNOTA'],$q);
        echo ($csv) ? "": PHP_EOL."Definováno workflow \"změna dat\", které u ".$odchozi_prichozi." dokumentu nastaví pole \"".getColumnName($pole)."\" na hodnotu \"".getColumnValue($pole,$q3->Record['HODNOTA'],$q)."\"".PHP_EOL;
        if ($csv) zapisCSVRadek($agenda_csv,$druh_dokumentu_csv,$spisovy_znak_csv,$workflow_csv,$dokument_csv, $pole_csv,$hodnota_csv);
      }
      if ($id_workflow == 2) {
        $workflow_csv = "založení schvalovacího procesu";
        $zadam_o = $q3->Record['PROMENNA'];
        $referent = $q3->Record['HODNOTA'];
        $zada_o_csv = getColumnName($zadam_o);
        $referent_csv = getColumnValue('select_referent',$referent,$q);
        echo ($csv) ? "": PHP_EOL."Definováno workflow \"založ schvalovací proces\", které u ".$odchozi_prichozi." dokumentu žádá o \"".getColumnName($zadam_o)."\" referenta \"".getColumnValue('select_referent',$referent,$q)."\"".PHP_EOL;
        if ($csv) zapisCSVRadek($agenda_csv,$druh_dokumentu_csv,$spisovy_znak_csv,$workflow_csv,$dokument_csv, "","",$zada_o_csv,$referent_csv);
        
      }
      
    }
    echo ($csv) ? "":PHP_EOL;

  }
  echo ($csv) ? "":PHP_EOL;
  
}
?>

