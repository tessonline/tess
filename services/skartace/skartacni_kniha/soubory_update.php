<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('sip/sip.inc'));
require(FileUp2('html_header_full.inc'));
echo '<h1>Aktualizace časových razítek</h1>';

$q = new DB_POSTA;
$q->query($_POST['sql']);

while($q->Next_Record()) {
  $IDs[] = $q->Record['ID'];
   $upl_obj = LoadClass('EedUploadPdf', $q->Record['RECORD_ID']);
   echo 'Zpracovávám soubor ' . $q->Record['NAME'] . ' ';
   $files_to_convert = $upl_obj->UpdatePDF($q->Record);
   echo "<br/>";
}
echo '<h1>Hotovo</h1>';
echo '<a href="edit.php?filter">Klikněte pro návrat</a>';
require(FileUp2('html_footer.inc'));
