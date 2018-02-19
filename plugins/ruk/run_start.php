<?php

//kontrola, aby nedoslo k zadani duplicitniho PID.
//kontrola se dela jen tehdy, pokud se jedna o jinou kauzu (jine CJ)
//kopie nebo vypravene dokumenty mohou mit stejne PID

if ($GLOBALS['KOPIE'] == 0 && $GLOBALS['EXTERNI_CK']<>'') {
  $sql = "select * from posta_carovekody where ck like '" . $GLOBALS['EXTERNI_CK'] . "'";
  $q = new DB_POSTA;
  $q->query($sql);
  if ($q->Num_Rows() > 0) {
    $q->Next_Record();
    $id = $q->Record['DOKUMENT_ID'];
    $EedCj = LoadClass('EedCj', $id);
    $docIDS = $EedCj->GetDocsInCj($id);
//    $idTEST = $GLOBALS['EDIT_ID'] ? $GLOBALS['EDIT_ID'] : $GLOBALS['ID_PUVODNI'];
    $idTEST = $GLOBALS['EDIT_ID'] ? $GLOBALS['EDIT_ID'] : 0;
    if ($GLOBALS['KOPIE_SOUBORU']>0) $idTEST = $GLOBALS['ID_PUVODNI'];
    if (!in_array($idTEST, $docIDS)) {
       require(FileUp2('html_footer.inc'));
       echo '<h1>CHYBA: zadaný PID je již uveden na jiném dokumentu!</h1>';
       echo '<p>Je nutné využít jiný PID!</p><br/>';
       echo '<input type="button" class="btn" value="   Zpět   " onclick="history.go(-1);">';
       Die();
     }
  }
}

