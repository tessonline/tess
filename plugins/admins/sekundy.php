<?php
require('tmapy_config.inc');
require(FileUp2('.admin/config.inc'));
require(FileUp2('.admin/status.inc'));
require(FileUp2('html_header_full.inc'));

echo '<h1>Oprava sekund</h1>';
$doc_id = (int) $_GET['DOC_ID'];
if (!$doc_id) Die('stop');
$cj_obj = LoadClass('EedCj',$doc_id);
$docs = $cj_obj->GetDocsInCj($doc_id);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$LAST_USER_ID = $USER_INFO['ID'];
$OWNER_ID = $USER_INFO['ID'];
$LAST_TIME = Date('H:i:s');
$LAST_DATE = Date('Y-m-d');

$q = new DB_POSTA;
$sloupce = array('DATUM_PODATELNA_PRIJETI','DATUM_SPRAVCE_PRIJETI','DATUM_REFERENT_PRIJETI','DATUM_VYRIZENI','DATUM_DORUCENO','DATUM_VYPRAVENI','DATUM_PREDANI','DATUM_PREDANI_VEN');

foreach($docs as $posta_id) {

  $opravy = array();
  $sql = 'select * from posta where id=' . $posta_id;
  $q->query($sql);
  $q->Next_Record();
  foreach($sloupce as $sloupec) {
    $pocet = explode(':', $q->Record[$sloupec]);
    if (count($pocet)>3) {
      $opravy[] = $sloupec . "='" . $pocet[0].':'.$pocet[1].':'.$pocet[2]."'";
    }
    if (count($pocet)== 2) {
      $opravy[] = $sloupec . "='" . $pocet[0].':'.$pocet[1].":00'";
    }
  }
  if (count($opravy)>0) {
    echo "Provádím opravu sekund $posta_id - ";
    $sql = 'update posta set ' . implode(', ', $opravy) . ",last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id=" . $posta_id;
    $q->query($sql);
//    echo $sql.'<br/>';
    echo "hotovo.<br/>";
  }

}

echo '<p><br/><h2>vše hotovo</h2></p>';
echo '<input type="button" name="" value="Zavřít" class="btn" onclick="window.opener.document.location.reload();">';

require(FileUp2('html_footer.inc'));
