<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));

if ($GLOBALS['DELETE_ID']) {
  $sql = 'SELECT * FROM POSTA_KRIZOVY_SPIS WHERE ID IN (' . $GLOBALS['DELETE_ID'] . ')';
  $q = new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
  $puv = $q->Record['PUVODNI_SPIS'];
  $nov = $q->Record['NOVY_SPIS'];
  $puvObj = LoadClass('EedCj', $puv);
  $novObj = LoadClass('EedCj', $nov);
  $text = 'Byla zrušena křížová vazba mezi ' . $puvObj->cislo_jednaci_zaklad. ' (<b>'.$puv.'</b>) a ' . $novObj->cislo_jednaci_zaklad . ' (<b>'. $nov . '</b>) ';

  EedTransakce::ZapisLog($puv, $text, 'DOC');
  EedTransakce::ZapisLog($puv, $text, 'SPIS');

  EedTransakce::ZapisLog($nov, $text, 'DOC');
  EedTransakce::ZapisLog($nov, $text, 'SPIS');


}

Run_(array("showaccess"=>true,"outputtype"=>3));
require_once(Fileup2("html_footer.inc"));  




