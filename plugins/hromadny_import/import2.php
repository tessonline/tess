<?php

echo '
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta http-equiv="X-UA-Compatible" content="IE=Edge">
<meta name="viewport" content="width=device-width,initial-scale=1.0,maximum-scale=1.0,user-scalable=no">
<title>Elektronická evidence dokumentů</title>
<link href="/theme/square/styles/twist-layout.css" rel="stylesheet">
</head><body>
';
require('tmapy_config.inc');
require(FileUp2('.admin/run2_.inc'));
require(FileUp2('.admin/log.inc'));
require_once(FileUp2('.admin/table_func.inc'));
require(FileUp2('.config/config.inc'));
include_once(FileUp2('.admin/upload_.inc'));

/*$uplobj = Upload(array(
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
if (count($importFiles) > 0) {

  foreach ($importFiles  as $val) {
    if ($val['TYPEFILE'] == 'text/csv') {
      $datafile .= $uplobj['table']->GetUploadFiles($val);
    }
  }

  $datacsv = explode(chr(10), $datafile);

  $l=0;
  $col_names = array();
  $data = array();
  foreach($datacsv as $line) {
    $l++;
    if ($l==1) {
      foreach (str_getcsv($line,";") as $cell) {
        $col_names[] = $cell;
        $TABLE_CONFIG['schema'][] = array ('field'=>$cell,'label'=>$cell);
      }
    } else
      if (strlen($line)>1)
      {
        $i = 0;
        $dataitem = array();
        $dataitem["ID"] = $i;
        foreach (str_getcsv($line,";") as $cell) {
          $dataitem[$col_names[$i]] = $cell;
          $i++;
        }
        $data[] = $dataitem;
      }
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
}
*/
$PROPERTIES["NO_SHOW_START_PAGE_MESSAGE"] = 1;
//require(FileUp2('html_header_title.inc'));
//require_once(FileUp2("html_header_full.inc"));
set_time_limit(0);

$error = array();
//nacteme obyvatele DB
$q = new DB_POSTA;
$w = new DB_POSTA;

$table_import = $GLOBALS['PROPERTIES']['AGENDA_TABLE'];

$log = '**************************************************************************************************';
zapisLog($log);
$log = '********** Importer ********** SPUSTENO **********';
zapisLog($log);

$userInfo = $GLOBALS['TMAPY_SECURITY']->getUserInfo();

$LAST_DATE = CheckQuoteInValue($q->str2dbdate(date('d.m.Y')));
$LAST_TIME = CheckQuoteInValue(date('H:i:s'));
$LAST_USER_ID = intval($userInfo['ID']);

$dalsi_krok = $_GET['dalsi_krok'];

if ($dalsi_krok == 1 && $id) {
  $sql = 'update ' . $table_import . ' set stav=stav+1,last_date=\''.CheckQuoteInValue($LAST_DATE).'\',last_time=\''.CheckQuoteInValue($LAST_TIME).'\',last_user_id=' . intval($LAST_USER_ID) . ' where tid='.intval($id).' AND stav<6';
  $log = 'SQL: ' . $sql;
  zapisLog($log);
  $q->query($sql);
}


$sql = 'select * from ' . $table_import . ' where tid=' . intval($id);
$log = 'SQL: ' . $sql;
zapisLog($log);
$q->query($sql);
$q->Next_Record();
$POPIS= $q->Record['POPIS'];

//jdeme najit, jestli tam neni nejaky drivejsi zaznam
$sql = 'select * from ' . $table_import . ' where POPIS=\'' . $POPIS . '\' and tid<'.intval($id) . ' order by tid asc';
$log = 'SQL: ' . $sql;
zapisLog($log);
$q->query($sql);
if ($q->Num_Rows()>0) {
  while ($q->Next_Record()) {
    $LAST_DATE = CheckQuoteInValue($q->Record['LAST_DATE']);
    $LAST_TIME = CheckQuoteInValue($q->Record['LAST_TIME']);
    $id_puv = intval($q->Record['TID']);

    $log = 'Jdu uzamknout puvodni importy, id importu=' . $id_puv;
    zapisLog($log);

    $sql = 'update ' . $table_import . ' set last_date_import=\''.$LAST_DATE.'\',last_time_import=\''.$LAST_TIME.'\' where tid=' . intval($id);
    $log = 'SQL: ' . $sql;
    zapisLog($log);
    $q->query($sql);

    $sql = 'update ' . $table_import . ' set zamceno='.intval($id).' where tid='.$id_puv;
    $log = 'SQL: ' . $sql;
    zapisLog($log);
    $q->query($sql);

 /*   $sql = 'delete from ' . $GLOBALS['CONFIG_ROB']['TABLE']['IMPORT_OBYVATELE'] . ' where file_id='.$id_puv;
    $log = 'SQL: ' . $sql;
    zapisLog($log);
    $q->query($sql);*/
  }
}
  $sql = 'select * from ' . $table_import . ' where tid=' . intval($id);
  $log = 'SQL: ' . $sql;
  zapisLog($log);
  $q->query($sql);
  $q->Next_Record();




$stav = $q->Record['STAV'];

$mc = $q->Record['MC'];
$file_id = $id;

/*if ($restart == 1) {
  $stav = 1;
  $sql = 'update ' . $table_import . ' set stav=1,last_date=\''.$LAST_DATE.'\',last_time=\''.$LAST_TIME.'\',last_user_id='.$LAST_USER_ID.' where tid=' . intval($id);
  $log = 'SQL: ' . $sql;
  zapisLog($log);
  $q->query($sql);
}
if ($restart == 2) {
  $stav = 4;
  $sql = 'update ' . $table_import . ' set stav=4,last_date=\''.$LAST_DATE.'\',last_time=\''.$LAST_TIME.'\',last_user_id='.$LAST_USER_ID.' where tid=' . intval($id);
  $log = 'SQL: ' . $sql;
  zapisLog($log);
  $q->query($sql);
}*/

if ($restart>0) {
  $stav = $restart;
  $sql = 'update ' . $table_import . ' set stav='.$stav.',last_date=\''.$LAST_DATE.'\',last_time=\''.$LAST_TIME.'\',last_user_id='.$LAST_USER_ID.' where tid=' . intval($id);
  $log = 'SQL: ' . $sql;
  zapisLog($log);
  $q->query($sql);
}


if  ($stav == 0) $stav = 1;
if  ($stav > 6) $stav = 6;


echo '
		<link type="text/css" href="css/jquery-ui.css" rel="stylesheet" />
		<script type="text/javascript" src="js/jquery-1.7.1.min.js"></script>	
		<script type="text/javascript" src="js/jquery-ui-1.8.18.custom.min.js"></script>
<script type="text/javascript">
  $(function() {
    $( "#tabs" ).tabs({ selected: '.($stav-1).' });

     if (document.getElementById(\'upl_wait_message-'.$stav.'\') !=null)   
     document.getElementById(\'upl_wait_message-'.$stav.'\').style.display = \'block\';
     var url = "loadAjax.php?id='.$id
     .'&krok='.$stav
     .'&skutecne='.$skutecne
     .'&restart='.$restart
     .'&csv_only='.$csv_only
     .'&DOPORUCENE='.$DOPORUCENE
     .'&VEC='.urlencode($VEC)
     .'&SKARTACE='.$SKARTACE
     .'&AGENDA_DOKUMENTU='.$AGENDA_DOKUMENTU
     .'&TYP_POSTY='.$TYP_POSTY
     .'&REFERENT='.$REFERENT
     .'&VLASTNICH_RUKOU='.$VLASTNICH_RUKOU
     .'&DAT_VYP='.$DAT_VYP
     .'&DAT_DOR='.$DAT_DOR
     .'&OBALKA_NEVRACET='.$OBALKA_NEVRACET
     .'&OBALKA_10DNI='.$OBALKA_10DNI
     .'&PDF='.$PDF
     .'&DS='.$DS
     .'&POZNAMKA='.urlencode($POZNAMKA)
     .'&ODES_TYP='.$ODES_TYP
     .'&ODESL_OTOCIT='.$ODESL_OTOCIT
     .'&DNAME='.$DNAME.'"; 
     $( "#tabs-'.$stav.'" ).load(url,
         function() {

            if (window.opener.parent.frames[1]!=null) {
              window.opener.parent.frames[1].location.reload();
            }
             if (document.getElementById(\'upl_wait_message-'.$stav.'\') !=null)   
            document.getElementById(\'upl_wait_message-'.$stav.'\').style.display = \'none\';       
         }
    );
  });
</script>
 ';


$img_wait = FileUpUrl('images/progress.gif');

$log = 'Predavam zpracovani na LoadAjax knihovnu';
zapisLog($log);
commitLog($id);

print '<div id="tabs">' . "\n";
print '<ul>' . "\n";
print '<li><a href="">1. '. $GLOBALS['RSTR_IMPORT']['import_obsah_csv'] .'</a></li>';
print '<li><a href="">2. '. $GLOBALS['RSTR_IMPORT']['import_nastaveni'] .'</a></li>';
print '<li><a href="">3. '. $GLOBALS['RSTR_IMPORT']['import'] .'</a></li>';
print '<li><a href="">4. '. $GLOBALS['RSTR_IMPORT']['import_potvrzeni'] .'</a></li>';
print '<li><a href="">5. '. $GLOBALS['RSTR_IMPORT']['import_download'] .'</a></li>';
print '<li><a href="">6. '. $GLOBALS['RSTR_IMPORT']['import_hotovo'] .'</a></li>';
print '</ul>' . "\n";

print '<div id="tabs-1">' . "\n";

echo '<div id="upl_wait_message-1" style="display:none"><p><img src="' . $img_wait . '" title="pracuji ..." alt="pracuji ..."></p></div>';
print '</div>' . "\n";

print '<div id="tabs-2">' . "\n";
echo '<div id="upl_wait_message-2" style="display:none"><p><img src="' . $img_wait . '" title="pracuji ..." alt="pracuji ..."></p></div>';
print '</div>' . "\n";

print '<div id="tabs-3">' . "\n";
echo '<div id="upl_wait_message-3" style="display:none"><p><img src="' . $img_wait . '" title="pracuji ..." alt="pracuji ..."></p></div>';
print '</div>' . "\n";

print '<div id="tabs-4">' . "\n";
echo '<div id="upl_wait_message-4" style="display:none"><p><img src="' . $img_wait . '" title="pracuji ..." alt="pracuji ..."></p></div>';
print '</div>' . "\n";

print '<div id="tabs-5">' . "\n";
echo '<div id="upl_wait_message-5" style="display:none"><p><img src="' . $img_wait . '" title="pracuji ..." alt="pracuji ..."></p></div>';
print '</div>' . "\n";

print '<div id="tabs-6">' . "\n";
echo '<div id="upl_wait_message-6" style="display:none"><p>' . $GLOBALS['RSTR_IMPORT']['import_mate_hotovo'] .'</p></div>';
print '</div>' . "\n";
echo "</body></html>";
//require(FileUp2('html_footer.inc'));
