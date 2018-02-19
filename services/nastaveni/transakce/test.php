<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(FileUp2('.admin/upload_.inc'));
require_once(FileUp2("/interface/.admin/upload_funkce.inc"));
require(FileUp2(".admin/status.inc"));
require(FileUp2(".admin/zaloz.inc"));

$GLOBALS['DATUM'] = $GLOBALS['DATUM'] ? $GLOBALS['DATUM'] : Date('Y-m-d');

$tran = LoadClass('EedTransakce');
$data = $tran->getRecordsHistory($GLOBALS['DATUM']);


$GLOBALS['FILE_NAME'] = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar]. 'transakcni_protokol_' . $GLOBALS['DATUM'] . '.pdf';
include_once(FileUp2('output/pdf/tran_protokol.php'));

include_once($GLOBALS['TMAPY_LIB'].'/upload/functions/SOAP_602_print2pdf.php');
//pod stejnzm souborem ulozi
$a=new SOAP_602_print2pdf($SERVER_CONFIG["UPLOAD_CONFIG"]["MODULES"]["table"]["STORAGE"]["Print2PDF_SERVICE"]);
if (strlen($GLOBALS["CONFIG_POSTA"]["HLAVNI"]["Print2PDF_TS_PROFIL"])>2) {
  try {
    list($fname,$fdata)=$a->ConvertStream('protokol.pdf',$data_protokol,$GLOBALS["CONFIG_POSTA"]["HLAVNI"]["Print2PDF_TS_PROFIL"]);

  }
}
else {
  $fdata = $data_protokol;
}

if (!$fp=fopen($GLOBALS['FILE_NAME'],'w')) Die('chyba');
fwrite($fp,$fdata);
fclose($fp);

$NOVEID = ZalozNovyDokument($GLOBALS[CONFIG_POSTA][HLAVNI][PROTOKOL_ID],0,2);

$w = new DB_POSTA;
$sql = "update posta set vec='Transakční protokol za den ".$GLOBALS['DATUM']."',status=1 where id=".$NOVEID;
$w->query($sql);

$uplobj_save = Upload(array('create_only_objects' => true, 'agenda' => 'POSTA', 'noshowheader' => true));
$GLOBALS['DESCRIPTION'] = '<i>transakční protokol</i>';
$GLOBALS['LAST_USER_ID'] = $val[LAST_USER_ID];
$GLOBALS['PRIVATE'] = $val['PRIVATE'];
$ret = $uplobj_save['table']->SaveFileToAgendaRecord($GLOBALS['FILE_NAME'], $NOVEID);
