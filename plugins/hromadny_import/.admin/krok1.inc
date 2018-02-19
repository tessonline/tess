<style>
th {background-color: gray;}
</style>
<?php
//echo '<p><span class="caption">'.$GLOBALS['RSTR_IMPORT']['import_dat'].'</span></p>';
$log = 'Nacitam csv data z uploadu';
ZapisLog($log);



if ($restart!='1') 
  $restart = EedImport::restartVal($id);
else
  $restart = 't';


$uplobj = Upload(array(
  'create_only_objects' => true,
  'agenda' => $GLOBALS['PROPERTIES']['AGENDA_IDENT'],
  'noshowheader' => true,
));


$importFiles = array();
$upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);
while (list($key, $val) = each($upload_records)) {
  if (strpos($val['NAME'], 'import_log') === false) {
    $importFiles[] = $val;
  }
}

$csv = 0;
$rtf = 0;
$doc = 0;
$other_ext = 0;



//$if_count = count($importFiles);


  foreach ($importFiles  as $val) {
    $ext = pathinfo($val['NAME'], PATHINFO_EXTENSION);
    if ($val['TYPEFILE'] == 'text/csv') {
      $datafile .= $uplobj['table']->GetUploadFiles($val);
      $csv++;
    } else
    if ($val['TYPEFILE'] == 'application/rtf') {
      $rtf++;
    } else 
      if (strtolower($ext) == 'docx') {
      $doc++;
    } else 
      if ($val['TYPEFILE'] == 'application/zip') {
      
    } else
      $other_ext++;
  }

 
  //if (($csv==0)||(($rtf==0)&&($doc==0))||($other_ext!=0)) {
  //musi obsahovat prave jeden CSV nebo prave jeden CSV a jeden RTF nebo DOC a zadny jiny
  if (!(((($csv==1)||(($csv==1)&&(($rtf==1)||$doc==1)))&&($other_ext==0)))) {
    $log = $GLOBALS['RSTR_IMPORT']['import_chybne_soubory_v_uploadu'];
    ZapisLog($log, 1);
    echo '<br /><p class="caption">' . $GLOBALS['RSTR_IMPORT']['import_chybne_soubory_v_uploadu'] . '</p>';
    echo '<a href="index.php">' . $GLOBALS['RESOURCE_STRING']['button_back']  . '</a>';
    require(FileUp2('html_footer.inc'));
    $log = 'Cekam na odezvu uzivatele';
    ZapisLog($log);
    CommitLog($id);
    Die();
  }
  
  $datacsv = explode(chr(10), $datafile);

  $l=0;
  $col_names = array();
  $data = array();
  $column1_sc = 0;
  //$columnX_sc = 0;
  $line_error = 0;
  foreach($datacsv as $line) {
    if (substr_count($line,';')<(strlen($line)-1)) {
      $l++;
      if ($l==1) {
        $column1_sc = substr_count($line, ';');
//        $columnX_sc = $column1_sc;
        foreach (str_getcsv($line,";") as $cell) {
          $col_names[] = $cell;
          $TABLE_CONFIG['schema'][] = array ('field'=>$cell,'label'=>$cell);
        }  
      } else
      if (strlen($line)>1) 
      {
        $sc = substr_count($line, ';');
        if ($sc!=$column1_sc) { 
//          $columnX_sc = $sc;
          $line_error = $l;
        }
        $i = 0;
        $dataitem = array();
        $dataitem["ID"] = $i; 
        foreach (str_getcsv($line,";") as $cell) {
          $dataitem[$col_names[$i]] = iconv('CP1250', 'UTF-8', $cell);
          $i++;
        } 
        $data[] = $dataitem;
      }
    }
  }
  
  if ($line_error>0) {
    $log = $GLOBALS['RSTR_IMPORT']['import_chybny_pocet_sloupcu'];
    ZapisLog($log, 1);
    echo '<br /><p class="caption">' . $GLOBALS['RSTR_IMPORT']['import_sloupcu_na_radku'].$line_error.$GLOBALS['RSTR_IMPORT']['import_neodpovida_pocet_sloupcu'] .'</p>';
    echo '<a href="index.php">' . $GLOBALS['RESOURCE_STRING']['button_back']  . '</a>';
    require(FileUp2('html_footer.inc'));
    $log = 'Cekam na odezvu uzivatele';
    ZapisLog($log);
    CommitLog($id);
    Die();
  }

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
        "table_schema" =>$TABLE_CONFIG));
  }  


$log = 'Data z CSV souboru zobrazena';
ZapisLog($log);

$userInfo = $GLOBALS['TMAPY_SECURITY']->getUserInfo();
$q = new DB_POSTA();
$LAST_DATE = CheckQuoteInValue($q->str2dbdate(date('d.m.Y')));
$LAST_TIME = CheckQuoteInValue(date('H:i:s'));
$LAST_USER_ID = intval($userInfo['ID']);
       

$sql = 'update ' . $GLOBALS['PROPERTIES']['AGENDA_TABLE'] .' set stav=1,restart=\''.$restart.'\',last_date=\''.$LAST_DATE.'\',last_time=\''.$LAST_TIME.'\',last_user_id='.$LAST_USER_ID.' where tid=' . intval($id);
//echo $sql;
$log = 'SQL: ' . $sql;
ZapisLog($log);
$q->query($sql);

$csv_only_link = (($doc==0)&&($rtf==0)) ? '&csv_only=1' : '';

//echo '<p><input type="button" class="button btn" onclick="window.location.href=\'import2.php?id='.$id.'&dalsi_krok=1&restart='.$restart.'\'" value="' . $GLOBALS['RSTR_IMPORT']['import_pokracovat'] . '"></p>';
echo '<p><input type="button" class="button btn" onclick="window.location.href=\'import2.php?id='.$id.'&dalsi_krok=1'.$csv_only_link.'\'" value="' . $GLOBALS['RSTR_IMPORT']['import_pokracovat'] . '"></p>';

