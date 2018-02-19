<?php



if ($GLOBALS['MAIN_DOC']>100 && strlen($GLOBALS['TEXT_CJ'])<1) {

  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  if (!$LAST_USER_ID) $LAST_USER_ID=$id_user;
  $OWNER_ID=$id_user;
  $LAST_TIME=Date('H:i:s');
  $LAST_DATE=Date('Y-m-d');

  $sql = "update posta set ev_cislo=(select nextval('posta_deniky_".$GLOBALS['MAIN_DOC']."_seq')),cislo_spisu2=rok,main_doc=".$GLOBALS['MAIN_DOC'].",last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id=".$GLOBALS['lastid'];
  $q->query($sql);
  $sql = "select ev_cislo,rok,main_doc from posta where id=".$GLOBALS['lastid'];
  $q->query($sql);
  $q->Next_Record();
  $ev_cislo = $q->Record['EV_CISLO'];
  $rok = $q->Record['ROK'];
  $main_doc = $q->Record['MAIN_DOC'];

  $sql = "select * from posta_cis_deniky where id=".$GLOBALS['MAIN_DOC'];
  $q->query($sql);
  $q->Next_Record();
  $zkratka = $q->Record['ZKRATKA'];

  $text = $zkratka . '/' . $GLOBALS['CONFIG']['OZNACENI_SPIS'] . '/' . $ev_cislo . '/' . $rok;
  ZapisCJ($GLOBALS['lastid'],$text);

//Die('ok');
}


