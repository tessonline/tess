<?php

function importJeSoubor($id,$vrat_pocet = false) {
  require_once(FileUp2('.admin/upload_.inc'));
  $uplobj = Upload(array(
    'create_only_objects' => true,
    'agenda' => 'POSTA_HROMADNY_IMPORT',
    'noshowheader' => true
  )
      );
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);
  if (count($upload_records) > 0) {
    if ($vrat_pocet) 
      return count($upload_records);
    else
    return true;
  }
  else return false;
}

function dateCheck($date) {
  if ($date=='')
    return 'NULL';
    else return 'to_date(\''.$date.'\',\'DD.MM.YYYY\')';
}

function importStavImporteru($stav, $id, $zamceno) {
  if ($zamceno>0) return '&nbsp;';
  if (!importJeSoubor($id)) return '<b>.... ' . $GLOBALS['RSTR_IMPORT']['import_nahrajete_soubory'] . '</b>';
  if ($stav == 0) $text = '<font size="+1"><b>' . $GLOBALS['RSTR_IMPORT']['import_sputit_importer'] . ' => ';
  else {
    if ($stav == 6) $img = '<img src="images/office_4_well.gif" title="' . $GLOBALS['RSTR_IMPORT']['import_dobehl'] . '">';
    else $img = '<img src="images/office_4_some.gif" title="' . $GLOBALS['RSTR_IMPORT']['import_nedobehl'] . '">';
    $text = ' <font size="+1"><b>' . $stav . '&nbsp;/&nbsp;6</b>&nbsp;&nbsp;&nbsp;' . $img . '&nbsp;';
  }
  $res = $text;
  $res .= '&nbsp;&nbsp;&nbsp;<a href="#" onclick="javascript:window.open(\'import2.php?id=' . $id . '\')">' . $GLOBALS['RSTR_IMPORT']['import_spustit'] . '</a>';
  $res .= '</font>';
  return $res;
}


function DownloadZip($id,$stav) { 
  $res = "";
  if (($stav>3)&&(importJeSoubor($id,true)>1))
  $res.='<a href="#" onclick="javascript:window.open(\'import2.php?id='.$id.'&restart=4\')"\"><img src=' .  FileUpImage('images/save') . ' border="0" title="'.$GLOBALS['RSTR_IMPORT']['import_vytvorit_zip'].'"></a>';
  return $res;
}

function testSablony($id) {
  $res = "";
  if ((importJeSoubor($id,true)>1))
    $res.='<a href="#" onclick="javascript:window.open(\'test_sablony.php?id='.$id.'\')"\"><img src=' .  FileUpImage('images/doc') . ' border="0" title="'.$GLOBALS['RSTR_IMPORT']['import_test_sablony'].'"></a>';
  return $res;
}

function delete($id,$zamceno) {
  if (($zamceno>-1))
    $res.='<a href="#" onclick="javascript:delete_('.$id.')"\"><img src=' .  FileUpImage('images/delete') . ' border="0" title="'.$RESOURCE_STRING['delete'].'"></a>';
    return $res;
}


?>
