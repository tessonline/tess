<?php

function tableBarcode_RUK($ID, $kopie) {
  $sql="select ck from posta_carovekody where dokument_id=".$ID."";
  static $xxx;
  If (!$xxx) $xxx=new DB_POSTA;
  $xxx->query($sql);
  If ($xxx->Num_Rows()==1) {$xxx->Next_Record(); $res=$xxx->Record["CK"];}
  else $res = $GLOBALS['CONFIG']['ID_PREFIX'] . str_pad($ID, 10, '0', STR_PAD_LEFT);

  if ($kopie == 1) $res = $res . 'K';
  return $res;
}