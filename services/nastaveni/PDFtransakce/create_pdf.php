<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(FileUp2('.admin/upload_.inc'));
require_once(FileUp2("/interface/.admin/upload_funkce.inc"));
require_once(FileUp2(".admin/status.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/zaloz.inc"));

$GLOBALS['DATUM'] = $GLOBALS['DATUM'] ? $GLOBALS['DATUM'] : Date('Y-m-d');

$tran = LoadClass('EedTransakce');
$data = $tran->getRecordsHistory($GLOBALS['DATUM']);

$w = new DB_POSTA;

$GLOBALS['CZ_DATUM'] = $w->dbdate2str($GLOBALS['DATUM']);

$GLOBALS['FILE_NAME'] = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar]. 'transakcni_protokol_' . $GLOBALS['CZ_DATUM'] . '.pdf';
$GLOBALS['FILE_NAME_PODPIS'] = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar]. 'transakcni_protokol_' . $GLOBALS['CZ_DATUM'] . '_podpis.pdf';
include_once(FileUp2('output/pdf/tran_protokol.php'));


if (!$fp=fopen($GLOBALS['FILE_NAME'],'w')) Die('chyba');
fwrite($fp,$fdata);
fclose($fp);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$LAST_USER_ID=$USER_INFO["ID"];
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');

if ($GLOBALS['CONFIG']['POUZIVAT_SBERNE_ARCHY']) {
  $cj = LoadClass('EedSql',0);
  $NOVEID = $cj->createDocWithCJ($GLOBALS[CONFIG_POSTA][HLAVNI][PROTOKOL_ID]);
}
else {
  $NOVEID = ZalozNovyDokument($GLOBALS[CONFIG_POSTA][HLAVNI][PROTOKOL_ID],0,2);
}
$sql = "update posta set vec='Transakční protokol za den ".$GLOBALS['CZ_DATUM']."',status=1 where id=".$NOVEID;
echo $sql;
$w->query($sql);

if (!$GLOBALS['CONFIG']['POUZIVAT_SBERNE_ARCHY']) {
  EedTools::PriradPodcislo($NOVEID);
}
else {
  $sql = 'select * from cis_posta_spisy where spis_id=' . $GLOBALS[CONFIG_POSTA][HLAVNI][PROTOKOL_ID] . ' and dalsi_spis_id=0';
  $w->query($sql);
  if ($w->Num_Rows()>0) {
    $spis_obj = LoadClass('EedCj', $GLOBALS[CONFIG_POSTA][HLAVNI][PROTOKOL_ID]);
    $spis_info = $spis_obj->GetCjInfo($GLOBALS[CONFIG_POSTA][HLAVNI][PROTOKOL_ID]);
    $ps = $spis_info['CELE_CISLO'];
    $spis_nazev = $spis_info['CELY_NAZEV'];


    $cj_obj = new EedCj($NOVEID);
    $cj_info = $cj_obj->GetCjInfo($NOVEID);
    $ns = $cj_info['CELE_CISLO'];

    $sql = "INSERT INTO CIS_POSTA_SPISY (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID) VALUES ".
          "('$ps', '$ns', ".$GLOBALS[CONFIG_POSTA][HLAVNI][PROTOKOL_ID].", $NOVEID,'$LAST_DATE','$LAST_TIME',$LAST_USER_ID,$LAST_USER_ID)";

    $w->query($sql);

    $text = 'dokument (<b>'.$NOVEID.'</b>) '.$ns.' byl vložen do spisu <b>' . $spis_nazev . '</b>';
    EedTransakce::ZapisLog($NOVEID, $text, 'DOC', $id_user);
    EedTransakce::ZapisLog($GLOBALS[CONFIG_POSTA][HLAVNI][PROTOKOL_ID], $text, 'SPIS', $id_user);

  }
}


if (!$fp=fopen($GLOBALS['FILE_NAME'],'w')) Die('chyba');
fwrite($fp,$data_protokol);
fclose($fp);
$uplobj_save = Upload(array('create_only_objects' => true, 'agenda' => 'POSTA', 'noshowheader' => true));
$GLOBALS['DESCRIPTION'] = '<i>transakční protokol</i>';
$GLOBALS['LAST_USER_ID'] = $val[LAST_USER_ID];
$GLOBALS['PRIVATE'] = $val['PRIVATE'];

$ret = $uplobj_save['table']->SaveFileToAgendaRecord($GLOBALS['FILE_NAME'], $NOVEID);


//je ulozeno, nacteme znovu dokument a ulozime ho podepsany...
include_once($GLOBALS['TMAPY_LIB'].'/upload/functions/SOAP_602_print2pdf.php');
//pod stejnzm souborem ulozi
$a=new SOAP_602_print2pdf($SERVER_CONFIG["UPLOAD_CONFIG"]["MODULES"]["table"]["STORAGE"]["Print2PDF_SERVICE"]);

if (strlen($GLOBALS["CONFIG_POSTA"]["HLAVNI"]["Print2PDF_TS_PROFIL"])>2) {
  list($fname,$fdata)=$a->ConvertStream('protokol.pdf',$data_protokol,$GLOBALS["CONFIG_POSTA"]["HLAVNI"]["Print2PDF_TS_PROFIL"]);

  if (strlen($data)>10) {
    //ulozime podepsany soubor...
    if (!$fp=fopen($GLOBALS['FILE_NAME_PODPIS'],'w')) Die('chyba');
    fwrite($fp,$fdata);
    fclose($fp);

    $GLOBALS['DESCRIPTION'] = '<i>transakční protokol s podpisem</i>';
    $GLOBALS['LAST_USER_ID'] = $val[LAST_USER_ID];
    $GLOBALS['PRIVATE'] = $val['PRIVATE'];
    $ret = $uplobj_save['table']->SaveFileToAgendaRecord($GLOBALS['FILE_NAME_PODPIS'], $NOVEID);

  }
}


