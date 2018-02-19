<?php

foreach($zmeny as $zmena) {
  if ($zmena['REFERENT']) {

    if (!is_array($GLOBALS['EDIT_ID'])) {$idArray = array(); $idArray[] = $GLOBALS['EDIT_ID'];}
    else $idArray = $GLOBALS['EDIT_ID'];

    foreach($idArray as $id) {
      include_once(FileUp2('plugins/emaily/.admin/emaily_funkce.inc'));
      $USER_INFO_EMAIL = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($zmena['REFERENT'],true,0,1);;
      $komu = $USER_INFO_EMAIL['EMAIL'];

      $login = getEnv("REMOTE_USER");
      $kdo_poslal = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($login,true);
      $kdo = $kdo_poslal['FNAME'] . ' ' . $kdo_poslal['LNAME'];

      if (strlen($komu)>5   && $GLOBALS['ODESLANA_POSTA']=='f' && EedTools::MuzemePoslatEmail($zmena['REFERENT']) ) {
        OdesliEmail('nova_posta_precteni', $komu,$GLOBALS['DATUM_PODATELNA_PRIJETI'],$GLOBALS['VEC'],$id,$kdo,'Přiřazení nového dokumentu');
      }
    }
  }

  if ($zmena['DATUM_PM']) {

    if (!is_array($GLOBALS['EDIT_ID'])) {$idArray = array(); $idArray[] = $GLOBALS['EDIT_ID'];}
    else $idArray = $GLOBALS['EDIT_ID'];

    foreach($idArray as $id) {
      include_once(FileUp2('plugins/emaily/.admin/emaily_funkce.inc'));
      $doc = LoadClass('EedDokument', $id);
      $USER_INFO_EMAIL = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($doc->referent_id,true,0,1);;
      $komu = $USER_INFO_EMAIL['EMAIL'];

      $login = getEnv("REMOTE_USER");
      $kdo_poslal = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($login,true);
      $kdo = $kdo_poslal['FNAME'] . ' ' . $kdo_poslal['LNAME'];

      if (strlen($komu)>5   && $GLOBALS['ODESLANA_POSTA']=='t' && EedTools::MuzemePoslatEmail($GLOBALS['REFERENT']) ) {
        OdesliEmail('posta_pravni_moc', $komu,$GLOBALS['DATUM_PODATELNA_PRIJETI'],$GLOBALS['VEC'],$id,$kdo,'Nabytí právní moci');
      }
    }
  }

  if ($zmena['ODBOR'] && !$zmena['REFERENT']) {
  //pri zmene odboru
    if (!is_array($GLOBALS['EDIT_ID'])) {$idArray = array(); $idArray[] = $GLOBALS['EDIT_ID'];}
    else $idArray = $GLOBALS['EDIT_ID'];

    $EedUser = LoadClass('EedUser', 0);

    foreach($idArray as $id) {
      include_once(FileUp2('plugins/emaily/.admin/emaily_funkce.inc'));
      $odbor = $EedUser->VratOdborZSpisUzlu($zmena['ODBOR']);

      $sql = 'SELECT u.id,u.login_name,u.email FROM security_user u LEFT JOIN security_group g ON u.group_id = g.id WHERE group_id='.$odbor;
      $q->query($sql);
      while ($q->Next_Record()) {

        $komu = $q->Record['EMAIL'];

        $login = getEnv("REMOTE_USER");
        $kdo_poslal = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($login,true);
        $kdo = $kdo_poslal['FNAME'] . ' ' . $kdo_poslal['LNAME'];

        $sec = $GLOBALS["TMAPY_SECURITY"]->GetGroupsForUser($q->Record['LOGIN_NAME']);
        if (strlen($komu)>5 && $GLOBALS['VLASTNICH_RUKOU']==9  && $GLOBALS['ODESLANA_POSTA']=='f' && isset($sec['POSTA|POSTA|vedouci-odbor']) && EedTools::MuzemePoslatEmail($q->Record['ID']) ) {
          OdesliEmail('nova_posta_prideleni', $komu,$GLOBALS['DATUM_PODATELNA_PRIJETI'],$GLOBALS['VEC'],$id,$kdo,'Nová datová zpráva');
        }
      }
    }
  }

  if ($zmena['SUPERODBOR']) {
  //pri zmene odboru
    if (!is_array($GLOBALS['EDIT_ID'])) {$idArray = array(); $idArray[] = $GLOBALS['EDIT_ID'];}
    else $idArray = $GLOBALS['EDIT_ID'];

    $EedUser = LoadClass('EedUser', 0);

    foreach($idArray as $id) {
      include_once(FileUp2('plugins/emaily/.admin/emaily_funkce.inc'));
      $sql = 'SELECT u.id,u.login_name,u.email FROM security_user u LEFT JOIN security_group g ON u.group_id = g.id WHERE u.pracoviste='.$GLOBALS['SUPERODBOR'].' and u.pracoviste<>103';
      $q->query($sql);
      while ($q->Next_Record()) {

        $komu = $q->Record['EMAIL'];

        $login = getEnv("REMOTE_USER");
        $kdo_poslal = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($login,true);
        $kdo = $kdo_poslal['FNAME'] . ' ' . $kdo_poslal['LNAME'];
        $sec = $GLOBALS["TMAPY_SECURITY"]->GetGroupsForUser($q->Record['LOGIN_NAME']);
        if (strlen($komu)>5 && $GLOBALS['ODESLANA_POSTA']=='f' && $GLOBALS['VLASTNICH_RUKOU']==9 && isset($sec['POSTA|POSTA|podatelna']) && EedTools::MuzemePoslatEmail($q->Record['ID']) ) {
          OdesliEmail('nova_posta_prideleni', $komu,$GLOBALS['DATUM_PODATELNA_PRIJETI'],$GLOBALS['VEC'],$id,$kdo,'Nová datová zpráva');
        }
      }
    }
  }

}
