<?php
if ($GLOBALS['noveID']) {
  $doc = LoadClass('EedDokument', $GLOBALS['noveID']);
  include_once(FileUp2('plugins/emaily/.admin/emaily_funkce.inc'));

  //odesleme email zpracovateli
  $USER_INFO_EMAIL = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($doc->referent_id,true,0,1);;
  $komu = $USER_INFO_EMAIL['EMAIL'];
  $login = getEnv("REMOTE_USER");
  $kdo_poslal = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($login,true);
  $kdo = $kdo_poslal['FNAME'] . ' ' . $kdo_poslal['LNAME'];

  $vec = '--- Nová interní pošta ---';
  if (strlen($komu)>5   && EedTools::MuzemePoslatEmail($doc->referent_id) ) {
    OdesliEmail('nova_posta_precteni', $komu,$doc->datum_podatelna_prijeti,$vec.$doc->vec,$doc->id_dokument,$kdo,'Přiřazení nového dokumentu');
  }

  //odesleme email na spisovy uzel (pokud neni referent)
  if ($doc->referent_id == 0 && $doc->odbor > 0) {

    $q = new DB_POSTA;
    $uzel = $doc->_VratSpisovyUzel($doc->odbor);
    $sql = 'SELECT u.id,u.login_name,u.email FROM security_user u LEFT JOIN security_group g ON u.group_id = g.id WHERE group_id='.$uzel['ID_ODBOR'];
    $q->query($sql);
    while ($q->Next_Record()) {

      $komu = $q->Record['EMAIL'];

      $login = getEnv("REMOTE_USER");
      $kdo_poslal = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($login,true);
      $kdo = $kdo_poslal['FNAME'] . ' ' . $kdo_poslal['LNAME'];

      $sec = $GLOBALS["TMAPY_SECURITY"]->GetGroupsForUser($q->Record['LOGIN_NAME']);
      if (strlen($komu)>5 && isset($sec['POSTA|POSTA|vedouci-odbor']) && EedTools::MuzemePoslatEmail($q->Record['ID']) ) {
        OdesliEmail('nova_posta_prideleni', $komu,$doc->datum_podatelna_prijeti,$vec.$doc->vec,$doc->id_dokument,$kdo,'Přiřazení nového dokumentu');
      }
    }
  }


}
