<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2(".admin/form_func.inc"));
require_once(FileUp2("html_header_full.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
include_once(FileUp2(".admin/status.inc")); 
require_once(FileUp2('.admin/upload_.inc')); 

set_time_limit(0);
echo "<h1>Modul SCANNER - načítání souborů</h1>";
$q=new DB_POSTA;
$id_user=468;

$cesta=$GLOBALS[CONFIG_POSTA][SCANNER][scanner_cesta];

$oddelovac='-';
$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($id);
//print_r($USER_INFO); Die();

if (!@$d = dir($cesta)) {
  $text='(SCAN) - Neexistuje cesta '.$val;
  WriteLog($software_id,$text,'',1);
  echo "<table>";
  echo "<tr><td><b>Cesta <i>".$cesta."</i> nenalezena!!!</b></td></tr></table>";
  require_once(FileUp2("html_footer.inc"));
  die;

}


while($entry=$d->read()) 
{
  if ($entry<>'.' && $entry<>'..')
  {
    list($ev_cislo,$pripona)=explode('.',$entry);
    $id=PrevedCPnaID($ev_cislo);
    if (!$id) $id = 0;
    $sql='select id from posta where id='.$id;
    $q->query($sql);
    $pocet=$q->Num_Rows();
    if (!$id || $id<0 || $pocet==0)
      $chybne[]=$entry; 
    else
      $file_scan[$id]=$entry;
  }
}

//print_r($file_scan);

if (!$skutecne_nacist) {
  echo "Našel jsem <b>".count($file_scan)."</b> souborů<br/>"; Flush();
  if (count($file_scan)>0)
    echo "<input type='button' class='button btn' value='Skutečně načíst' onclick=\"document.location.href='nacist.php?skutecne_nacist=1'\">";
  require_once(FileUp2("html_footer.inc"));
  Die();
}

echo "<table class=brow width=100% border=0 cellspacing=0><tr class=brow><th class=brow width='15%'>Soubor</th><th class=brow width='15%'>ID dokumentu</th><th class=brow width='50%'>Adresát</th><th class=brow width='20%'>Stav</th></tr>";
$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));

if (count($file_scan)>0) {

  $sql = "select * from security_user where login_name ilike '" . $GLOBALS['SERVER_CONFIG']['SECURITY']['ANONYMOUS_LOGIN'] . "'";
  $q->query($sql); $q->Next_Record(); $user_id = $q->Record['ID'];

  while (list($key,$val)=each($file_scan)) {
  //echo "Nactiam $key";
    $files=$uplobj['table']->getRecordsUploadForAgenda($key);
    $copy=true;
    while (list($key1,$val1)=each($files)) if ($val1[NAME]==$val) $copy=false;

    if ($class=='posta_brow') $class='posta_browdark'; else $class='posta_brow';
    echo "<tr class=brow><td class=$class><b>$val</b></td><td class=$class>$key</td><td class=$class>".UkazAdresu($key,', ')."</td><td class=$class>";

    $tmp_soubor=$cesta.'/'.$val;

    if ($copy) {
      $GLOBALS['DESCRIPTION'] = 'scan dokumentu';
      $GLOBALS['LAST_USER_ID'] = $id_user;
      $GLOBALS['CONVERT'] = false;
      $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
      $ret = $uplobj['table']->SaveFileToAgendaRecord($tmp_soubor, $key);
      if ($ret[err_msg]<>'' || $key==4682433) echo '<font color=red>Chyba pri uložení souboru '.basename($tmp_soubor).': '.$ret[err_msg]."</font>";
      else {
        echo '<font color=green><b>uloženo</b></font>';
        $text = 'K dokumentu (<b>'.$key.'</b>) byl vložen soubor <b>' . basename($tmp_soubor) . '</b>, velikost: '.filesize($tmp_soubor).' bytes';
        EedTransakce::ZapisLog($key, $text, 'DOC', $user_id);
        @unlink($tmp_soubor);
      }
    }
    else {
      echo "<i>soubor je již uložen</i>";
      @unlink($tmp_soubor);
    }

    echo "</td></tr>";
  }
}
//print_r($file_scan);
echo "</table><br/>";

if (count($chybne)>0)
  echo "<b><font color=red>Chyba:</font> Tyto soubory nebyly načteny: </b>".implode(', ',$chybne)."<br/><br/>";

echo "Import proběhl dne: ".Date('d.m.Y v H:i');
require_once(FileUp2("html_footer.inc"));
