<?php
 

include_once(FileUp2(".admin/upload/table_func.inc"));

//$TABLE_CONFIG["schema"][] =	array( field => "ID", label => "ID");
$TABLE_CONFIG["schema"][] =	array( 
  'field' => "Url2File(ID,ID_H,DIRECTORY,NAME,TYPEFILE)", 
  'label' => $GLOBALS['RESOURCE_STRING']['name'], 
  'order_by' => 'name asc'
); 
$TABLE_CONFIG["schema"][] =	array( 
  'field' => "nl2br(DESCRIPTION)", 
  'label' => $GLOBALS['RESOURCE_STRING']['notice'], 
);

if ($GLOBALS['FULLTEXT_UPLOAD']) {
  $TABLE_CONFIG["schema"][]=array( 
    'field' => "Upload_GetFulltextHighlightedText(ID)", 
    'label' => $GLOBALS['RESOURCE_STRING']['fulltext']
  );
}

//$TABLE_CONFIG["schema"][] =	array( field => "FileSize_kB(FILESIZE)", label => "Velikost [kB]", order_by => 'filesize asc');

if(!$GLOBALS['USER_INFO']["is_anonymous"]){
  //$TABLE_CONFIG["schema"][] =	array( field => "RECORD_ID", label => "RECORD_ID");
  //$TABLE_CONFIG["schema"][] =	array( field => "DIRECTORY", label => "Adres��");
  //$TABLE_CONFIG["schema"][] =	array( field => "FILESIZE", label => "FILESIZE");
  //$TABLE_CONFIG["schema"][] =	array( field => "TYPEFILE", label => "TYPEFILE");
  $TABLE_CONFIG["schema"][] =	array( 
    'field' => "DatumCasVlozeni(LAST_DATE,LAST_TIME)", 
    'label' => $GLOBALS['RESOURCE_STRING']['date_insert'], 
    'order_by' => 'last_date asc, last_time asc'
  );
  $TABLE_CONFIG["schema"][] =	array( 
    'field' => "NahralKdo(LAST_USER_ID)", 
    'label' => $GLOBALS['RESOURCE_STRING']['last_editor'], 
    'order_by' => 'last_user_id asc'
  );
  if($GLOBALS['use_anonym_access']) {
    $TABLE_CONFIG["schema"][] =	array( 
      'field' => "AnoNe_Upload(ANONYM)", 
      'label' => $GLOBALS['RESOURCE_STRING']['anonymous_access_abr'],  
      'add' => "align='center'", 
      "width" => "1%", 
      'order_by' => 'anonym asc');
  }
  if($GLOBALS['use_private_access']) {
    $TABLE_CONFIG["schema"][] =	array( 
      'field' => "AnoNe_Upload(PRIVATE)", 
      'label' => $GLOBALS['RESOURCE_STRING']['secret_abr'],  
      'add' => "align='center'", 
      "width" => "1%", 
      'order_by' => 'private asc'
    );
  }
}

//zobrazi nahled obrazku
if($GLOBALS['IMAGE_PREVIEW']){
  $TABLE_CONFIG["schema"][] = array(
    "field" => "ShowPreviewFoto(ID)", 
    "label" => "&nbsp;", 
    "add" => "align=center", 
    "class" => "image", 
    "width" => "1%"
  );
}
  

if ($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['FULL_TEXT']) {
  $TABLE_CONFIG["schema"][] =	array( 
   'field' => "ShowText(ID)", 
   'label' => $GLOBALS['RESOURCE_STRING']['text_abr']
 );
}

if (!$GLOBALS['DELETE_ID'] && !$GLOBALS['HISTORY_ID'] && HasSubRole("update") && 
   (HasRole('upload_update') || HasAccessToRecord('update', $GLOBALS[RECORD_ID], $GLOBALS['PROPERTIES']['AGENDA_IDENT']))) {
  $TABLE_CONFIG["schema"][] =	array( 
    'field' => "ShowHistory(ID)", 
    'label' => "&nbsp;", 
    "add" => "align=center", 
    "class" => "image", 
    "width" => "1px"
  );
}

if (HasSubRole('read') && (HasRole('upload_read') || HasAccessToRecord('read', $GLOBALS[RECORD_ID], $GLOBALS['PROPERTIES']['AGENDA_IDENT']))) {
  $TABLE_CONFIG["schema"][] =	array( 
    'field' => "ShowInfo(ID)", 
    'label' => "&nbsp;", 
    "add" => "align=center", 
    "class" => "image", 
    "width" => "1px"
  );
}

//pokud se nejedna o mazani, tak nezobrazuj ostatni
if (!$GLOBALS['DELETE_ID'] && !$GLOBALS['HISTORY_ID']) {
  
  if (HasSubRole('update') && (HasRole('upload_update') || HasAccessToRecord('update', $GLOBALS[RECORD_ID], $GLOBALS['PROPERTIES']['AGENDA_IDENT']))) {
    $TABLE_CONFIG["schema"][] =	array( 
      'field' => "ShowEdit(ID)", 
      'label' => "&nbsp;", 
      "add" => "align=center", 
      "class" => "image", 
      "width" => "1px"
    );
  }
  
  if (HasSubRole('delete') && (HasRole('upload_delete') || HasAccessToRecord('delete', $GLOBALS[RECORD_ID], $GLOBALS['PROPERTIES']['AGENDA_IDENT']))) {
    $TABLE_CONFIG["schema"][] =	array( 
      'field' => "ShowDelete(ID)", 
      'label' => "&nbsp;", 
      "add" => "align=center", 
      "class" => "image", 
      "width" => "1px"
    );
  }
  
  if (HasSubRole('delete') && (HasRole('upload_delete') || HasAccessToRecord('delete', $GLOBALS[RECORD_ID], $GLOBALS['PROPERTIES']['AGENDA_IDENT']))) {
        $TABLE_TOP_MENU['style'] = 'button btn'; //anchor 
        $TABLE_TOP_MENU['schema'][] = array(
            'label'   => $GLOBALS['RESOURCE_STRING']['delete_all'],
            'url'     => 'javascript:NewWindowDelete_upload(\'ug_file.php?upload_modul=table&show_typ=3&DELETE_ID=-1&RECORD_ID='.$GLOBALS['RECORD_ID'].'\')',
            'Xtarget' => '_blank',
            'title'   => $GLOBALS['RESOURCE_STRING']['delete_all'],
        );
    }
    if (HasSubRole('read') && (HasRole('upload_read') || HasAccessToRecord('read', $GLOBALS[RECORD_ID], $GLOBALS['PROPERTIES']['AGENDA_IDENT']))) {
        $TABLE_TOP_MENU['style'] = 'button btn'; //anchor 
        $TABLE_TOP_MENU['schema'][] = array(
            'label'   => $GLOBALS['RESOURCE_STRING']['button_save'],
            'url'     => 'javascript:document.location.href=\'ug_file.php?upload_modul=table&_set_sess_ceche_limit_=1&FILE_ID=-1&RECORD_ID='.$GLOBALS['RECORD_ID'].'\'',
            'Xtarget' => '_blank',
            'title'   => $GLOBALS['RESOURCE_STRING']['all'].' st�hni'
        );
    }
    
}

