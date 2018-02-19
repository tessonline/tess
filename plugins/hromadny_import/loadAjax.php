<?php
require('tmapy_config.inc');
require(FileUp2('.admin/run2_.inc'));
require(FileUp2('.admin/log.inc'));
require_once(FileUp2('.admin/table_func.inc'));
require(FileUp2('.config/config.inc'));
include_once(FileUp2('.admin/upload_.inc'));
include_once(FileUp2('.admin/classes/EedImport.inc'));

$log = '********** LoadAjax: ********** Zacatek souboru **********';
zapisLog($log);
commitLog($id);

$PROPERTIES["NO_SHOW_START_PAGE_MESSAGE"] = 1;
require(FileUp2('html_header_title.inc'));
set_time_limit(0);

$error = array();

$q = new DB_POSTA;


$append ='1=1';

$userInfo = $GLOBALS['TMAPY_SECURITY']->getUserInfo();

$LAST_DATE = CheckQuoteInValue($q->str2dbdate(date('d.m.Y')));
$LAST_TIME = CheckQuoteInValue(date('H:i:s'));
$LAST_USER_ID = intval($userInfo['ID']);

$sql = 'select * from ' . $GLOBALS['PROPERTIES']['AGENDA_TABLE'] . ' where tid=' . intval($id);
//echo $sql;
$q->query($sql);
$q->Next_Record();
$LAST_DATE_IMPORT = CheckQuoteInValue(($q->Record['LAST_DATE_IMPORT']<>'') ? $q->Record['LAST_DATE_IMPORT'] : Date('d.m.Y'));
$LAST_TIME_IMPORT = CheckQuoteInValue(($q->Record['LAST_TIME_IMPORT']<>'') ? $q->Record['LAST_TIME_IMPORT'] : Date('H:i:s'));

$datum = explode('.', $q->dbdate2str($LAST_DATE_IMPORT));
$time = explode(':', $LAST_TIME_IMPORT);
$update_diff = mktime($time[0], $time[1], $time[2], $date[1], $date[0], $date[2]);
if (!$LAST_DATE_IMPORT) $LAST_DATE_IMPORT = $LAST_DATE;
$file_id = intval($id);

$table = $GLOBALS['PROPERTIES']['AGENDA_TABLE'];

$krok = (int) $krok;
$log = '********** LoadAjax: ********** Zpracovavam krok ' . $krok . '/5 **********';
zapisLog($log);
echo '<table width="95%" align="center"><tr><td>';
include('.admin/krok'.$krok.'.inc');
$log = 'Cekam na odezvu uzivatele';
zapisLog($log);
//commitLog($id);

echo '</td></tr></table>';
echo '<p>&nbsp;</p>';
require(FileUp2('html_footer.inc'));
