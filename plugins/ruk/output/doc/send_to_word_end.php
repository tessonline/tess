<?php

$sql = 'select * from posta_carovekody where dokument_id=' . $GLOBALS['ID'];
$aa = new DB_POSTA;
$aa->query($sql);
$aa->Next_Record();
if ($aa->Record['CK']<>'') {
  $barcode = '{\pict\pngblip\picw400\pich50\wbmbitspixel1\wbmplanes1\wbmwidthbytes22
  '.Code39Pic($aa->Record['CK']).'}';
}
