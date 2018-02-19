<style>
th {background-color: gray;}
</style>
<?php
require('tmapy_config.inc');
include_once(FileUp2('.admin/classes/dokument/Rtf.php'));
include_once(FileUp2('.admin/classes/EedImport.inc'));

//echo '<p><span class="caption">'.$GLOBALS['RSTR_IMPORT']['import_potvrzeni'].'</span></p>';
$log = 'Zobrazení tabulky';
ZapisLog($log);
  $tid = $id; 
   
  $files = EedImport::getFiles($tid);
  
  $rtf = new Rtf();
  $rtf->files = $files;
  
  $data = $rtf->getTableData();
  if (count($data)>0) {
    include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
    $db_arr = new DB_Sql_Array;
    $db_arr->Data=$data;
    if (count($data)>0)
      Table(array("db_connector" => &$db_arr,
        "showaccess" => true,
        "showedit"=>false,
        "showinfo"=>false,
        "showdelete"=>false,
        "showupload"=>false,
        "table_schema" =>$rtf->getTableConfig()));
  }
  

echo '<p><input type="button" class="button btn" onclick="window.location.href=\'import2.php?id='.$tid.'&dalsi_krok=1\'" value="' . $GLOBALS['RSTR_IMPORT']['import_zip_to_upload'] . '">';

//echo '&nbsp;&nbsp;&nbsp;<input type="button" class="button btn" onclick="window.location.href=\'import2.php?id='.$tid.'&dalsi_krok=1&PDF=1\'" value="' . $GLOBALS['RSTR_IMPORT']['download_pdf'] . '">';

echo '</p>';

  
if (strlen($GLOBALS['DS'])>1) {
  $TABLE_CONFIG['schema'][] = array ('field'=>"ID",'label'=>"ID dokumentu");
  $data = array();
  $ids = explode(",",$GLOBALS['DS']);
  array_shift($ids);
  foreach ($ids as $id)
    $data[]['ID'] = $id;
  $db_arr = new DB_Sql_Array;
  $db_arr->Data=$data;    
  Table(array("db_connector" => &$db_arr,
    "showaccess" => true,
    "showedit"=>false,
    "showinfo"=>false,
    "showdelete"=>false,
    "showupload"=>false,
    "caption" => "Nalezeno více DS",
    "table_schema" =>$TABLE_CONFIG));
    
}
    
$sql = 'update ' . $table .' set stav=4,last_date=\''.$LAST_DATE.'\',last_time=\''.$LAST_TIME.'\',last_user_id='.$LAST_USER_ID.' where tid=' . intval($tid);
$log = 'SQL: ' . $sql;
ZapisLog($log);
//$q->query($sql);


//echo '<p><input type="button" class="button btn" onclick="window.location.href=\'import2.php?id='.$tid.'&dalsi_krok=1\'" value="' . $GLOBALS['RSTR_IMPORT']['import_download_zip'] . '"></p>';

