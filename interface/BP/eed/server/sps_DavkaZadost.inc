<?php

//Funkce vrati seznam udalosti v dane davce...
function DavkaZadost($app_id, $davka) {
  //nastaveni parametru
  global $server, $soap;

  $q=new DB_POSTA;
  $q->ShowError = false;
	$q->Error_Die = false;

  $poradi = $davka['Poradi'];

  $sql = 'select * from posta_eed_udalosti where app_id=' . $app_id.' and poradi='.$poradi.' order by poradi asc, id asc';
  $q->query($sql);
  $puv_poradi = 0;

  if ($q->Num_Rows() == 0) {
    $msg_popis = NastavPopis('DavkaZadost','1000');
  }
  else {
    while ($q->Next_Record()) {
      $key = $q->Record['UDALOST'];
      $temp = array(
//        "__" => unserialize($q->Record['HODNOTY']),
        'UdalostID' => 1,
        'DatumCasVytvoreni' => '1010-10-10'
      );
      $tUdalost[$key] = unserialize($q->Record['HODNOTY']);
      $tUdalost[$key]['DatumCasVytvoreni'] = '1010-10-10';
  //    $tUdalost[$key] = $temp;

    }
    $msg_popis = NastavPopis('DavkaZadost','0000');
  }
  print_r($tUdalost);
  Response_Zprava($response, $msg_popis['Kod'], $msg_popis['Popis'], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DavkaZadost', $msg_popis["Kod"]);

  $result = array(
    'Udalosti' => $tUdalost,
    'Zpravy' => array('Zprava' => $response),
  );

  return $result;
}

