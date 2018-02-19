<?php

include_once('db.inc');
class EedImport extends eed_db_object {
  
  private $next_id_pos;
  private $id_array = array();
  
  function EedImport($import_id=null,$table=null) {
    $q = eed_db_object::getInstanceDb();
    $this->next_id_pos = 0;
    if ($import_id!=null) { 
      $sql = 'SELECT id_posta FROM ' . $table .'_POSTA WHERE id_import=' . intval($import_id);
      $q->query($sql);
      while ($q->Next_Record()) {
        $this->id_array[] = $q->Record['ID_POSTA'];
      }
    }
  }
    
  public function countDocuments($tid, $table = null) {
    $q = eed_db_object::getInstanceDb();
    if ($table==null) $table = $GLOBALS['PROPERTIES']['AGENDA_TABLE'];
    $sql = 'SELECT count(id_posta) as pocet FROM ' . $table .'_POSTA WHERE id_import=' . intval($tid);
    $q->query($sql);
    $q->Next_Record();
    return $q->Record['POCET'];    
  }
  
  public function getNextId() {
    if ($this->next_id_pos<sizeof($this->id_array))
      $res = $this->id_array[$this->next_id_pos];
    else 
      $res = false;
    $this->next_id_pos++;
    return $res;
  }
  
  public function getFiles($tid, $table = null) {
    $q = eed_db_object::getInstanceDb();
    
    if ($table==null) $table = $GLOBALS['PROPERTIES']['AGENDA_TABLE'];
    $sql = 'SELECT id_posta FROM ' . $table .'_POSTA WHERE id_import=' . intval($tid);
    
    $q->query($sql);
    
    $id_array = array();
    while ($q->Next_Record()) {
      $id_array[] =  $q->Record['ID_POSTA'];
    }
    
    $uplobj = Upload(array(
      'create_only_objects' => true,
      'agenda' => 'POSTA',
      'noshowheader'=>true)
        );
    
    $i = 0;
    $files = array();
    foreach ($id_array as $id) {
      $upload_item =  $uplobj['table']->GetRecordsUploadForAgenda($id);
      foreach ($upload_item as $item) {
        //osetreni aby se nepridavaly jine soubory nez obsahujici cislo dokumentu
        $pos = strpos($item['NAME'], $id);
        if ($pos!==false) {
          $files[$i]['ID'] = $id;
          $files[$i]['FILENAME'] = $item['NAME'];
          $files[$i]['FILEID'] = $item['ID'];
          $i++;
        }
      }
    }
    return $files;
  }
  
  public function getTemplateNames($id) {
    $uplobj = Upload(array(
      'create_only_objects' => true,
      'agenda' => 'POSTA_HROMADNY_IMPORT',
      'noshowheader'=>true)
        );
    $importFiles = array();
    $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);
    while (list($key, $val) = each($upload_records)) {
      if (strpos($val['NAME'], 'import_log') === false) {
        $importFiles[] = $val;
      }
    }
    $filesCount = count($importFiles);
    $template = array();
    
    if ($filesCount > 0) {
      foreach ($importFiles  as $val) {
        $ext = pathinfo($val['NAME'], PATHINFO_EXTENSION);
        if ($val['TYPEFILE'] == 'application/rtf') {
          $template[] = $val['NAME'];
        }
        if (strtolower ($ext) == 'docx') {
          $template[] = $val['NAME'];
        }
      }
    }
    return $template; 
  }
  
  public function getImportedDocData($template_name,$id) {
    $uplobj = Upload(array(
      'create_only_objects' => true,
      'agenda' => 'POSTA',
      'noshowheader'=>true)
        );
    $upload_records =  $uplobj['table']->GetRecordsUploadForAgenda($id);
    foreach ($upload_records as $record) {
      if (strpos($record['NAME'], $template_name)) {
        $res['NAME'] = $record['NAME'];
        $res['DATA'] = $uplobj['table']->GetUploadFiles($record);
        return $res;
      }
    }
    return null;      
  }
  
  public function getImportedFileId($template_name,$id) {
    $uplobj = Upload(array(
      'create_only_objects' => true,
      'agenda' => 'POSTA',
      'noshowheader'=>true)
        );
    $upload_records =  $uplobj['table']->GetRecordsUploadForAgenda($id);
    //var_dump($upload_records);
    //die();
    foreach ($upload_records as $record) {
      if (strpos($record['NAME'], $template_name)) {
        $res = $record['DIRECTORY'];
        return $res;
      }
    }
    return null;
  }
  
 
  public function glob2db($id_array,$tid) {
    $q = eed_db_object::getInstanceDb();
    $gl_array = array();
    foreach ($id_array as $id) {
      $gl_array[$id] = $GLOBALS[$id];
    }
    $gl = json_encode($gl_array);
    $sql = 'UPDATE ' . $GLOBALS['PROPERTIES']['AGENDA_TABLE'] .' SET predef_vars=\''.addslashes($gl).'\' WHERE tid=' . intval($tid);
    $q->query($sql);

  }
  
  public function db2glob($tid) {
    $q = eed_db_object::getInstanceDb();
    $sql = 'SELECT predef_vars FROM ' . $GLOBALS['PROPERTIES']['AGENDA_TABLE'].' WHERE tid=' . intval($tid);
    $q->query($sql);
    $q->Next_Record();
    $pv = $q->Record['PREDEF_VARS'];
    if ($pv=='') return false;
    $pv = stripslashes(stripslashes($pv));
    $gl = json_decode($pv);
    foreach ($gl as $id=>$value) {
      $GLOBALS[$id] = $value;
    }
    return true;
  }

  
  public function restartVal($tid) 
  {
    $q = eed_db_object::getInstanceDb();
    $sql = 'SELECT restart FROM ' . $GLOBALS['PROPERTIES']['AGENDA_TABLE'] .' WHERE tid=' . intval($tid);
    $q->query($sql);
    $q->Next_Record();
    $res = $q->Record["RESTART"];
    return $res;
  }

  public function isRestart($tid)
  {
    
    $v = EedImport::restartVal($tid);
    if ($v == 't') 
      return true;
    else 
      return false;
  }
  
 
}