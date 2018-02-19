<?php
require_once(FileUp2('.admin/upload_.inc'));
include_once(FileUp2("interface/.admin/soap_funkce.inc"));

function ShowError($a, $b, $text) {
 $texta = '(' . $b . ') - ' . $text;
 WriteLog($a, $texta, $session_id, 1);
 return $text;
}

function CopyFilesDokument($session_id, $puvodni, $nove, $omezeni = array()) {
  $edit_id = $GLOBALS['EDIT_ID'];
  $uplobj = Upload(array('create_only_objects' => true, 'agenda' => 'POSTA', 'noshowheader' => true));
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($puvodni);

  while (list($key, $val) = each($upload_records)) {
    if (((count($omezeni)>0 && !in_array($val[NAME], $omezeni)) || count($omezeni) == 0)) {
      $soubory[$key] = $val;
      $soubory[$key][FILE_DESC] = $val[DESCRIPTION];
      $soubory[$key][data] = $uplobj['table']->GetUploadFiles($val);
      $soubory[$key][LAST_USER_ID] = $val[LAST_USER_ID];
      $soubory[$key]['PRIVATE'] = $val['PRIVATE'];
    }
  }
  if (count($soubory) == 0) return ShowError($session_id, 'COPYFILES', 'u dokumentu ' . $puvodni . ' nenalezeny žádné odpovídající soubory ke kopírování');

  UNSET($GLOBALS['EDIT_ID']); //blbne pri ukladani, nesmi byt hodnota EDIT_ID
  unset($uplobj);
  $uplobj_save = Upload(array('create_only_objects' => true, 'agenda' => 'POSTA', 'noshowheader' => true));
  while (list($key, $val) = each($soubory)) {

    $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$val["NAME"];
    $tmp_soubor_x = TxtEncoding4Soap($GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$val["NAME"]);
    if (is_file($tmp_soubor_x)) unlink($tmp_soubor_x);
    $data = $val[data];
//    echo "ulozime soubor pod $tmp_soubor_x <br/>";
    if (strlen($data)<1) return ShowError($session_id, 'COPYFILES', 'Není k dispozici obsah souboru ' . $val["NAME"]);
    if (!$fp = fopen($tmp_soubor_x, 'w')) return ShowError($session_id, 'COPYFILES', 'Chyba pri ulozeni tmp souboru ' . $tmp_soubor);
    fwrite($fp, $data);
    fclose($fp);
    chmod($tmp_soubor_x, 0777);
    $GLOBALS['DESCRIPTION'] = $val[FILE_DESC];
    $GLOBALS['LAST_USER_ID'] = $val[LAST_USER_ID];
    $GLOBALS['PRIVATE'] = $val['PRIVATE'];
//    echo "Ukladam ".$tmp_soubor_x." do ".$nove."<br/>";
    $ret = $uplobj_save['table']->SaveFileToAgendaRecord($tmp_soubor, $nove);
//    print_r($ret); Die();
    if ($ret[err_msg]>0) return ShowError($session_id, 'COPYFILES', 'Chyba pri ulozeni souboru ' . $val["NAME"] . ': ' . $ret[err_msg]);
    $file_ident = $ret[file_id];
    $text = '(COPYFILES) - k dokumentu (' . $nove . ') byl vložen soubor ' . $val["NAME"] . ' - ID: (' . $file_ident . ')';
    WriteLog($session_id, $text, $session_id);
    $file[$counter2][FILE_ID] = $file_ident;
    $file[$counter2][FILE_NAME] = $val["FILE_NAME"];
    $file[$counter2][FILE_DESC] = $GLOBALS['DESCRIPTION'];
    $file[$counter2][FILE_SIZE] = ' ';
    $file[$counter2][BIND_TYPE] = ' ';
    $file[$counter2][FILE_DATA] = ' ';
  }

  $GLOBALS['EDIT_ID'] = $edit_id;
  return 'OK';

}

function JePodepsanyDokument($file) {
 $uplobj = Upload(array('create_only_objects' => true, 'agenda' => 'POSTA', 'noshowheader' => true));
 $data = $uplobj['table']->GetUploadFiles($file); 
 if (strpos($data, '/Type/Sig') || strpos($data, '/Type /Sig') || strpos($data, '/FT /Sig') || strpos($data, '/FT/Sig') ) return true;
 else return false;
}
