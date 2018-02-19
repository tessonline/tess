<?php

//Funkce vrati seznam nevyrizenych davek pro danou aplikaci...
function DavkySeznam($app_id) {
  //nastaveni parametru
  global $server, $soap;


  $q=new DB_POSTA;
  $q->ShowError = false;
	$q->Error_Die = false;

  $cil = $server->methodparams['!Cil'];
  $datumVzniku = $server->methodparams['!DatumVzniku'];
  $poradi = $server->methodparams['!Poradi'] ? $server->methodparams['!Poradi'] : 1;
  $zdroj = $server->methodparams['!Zdroj'];

  $sql = 'select * from posta_eed_udalosti where chyba=0 and zpracovano is null and app_id=' . $app_id.' order by poradi asc, id asc';
  $q->query($sql);
  $tDavka = array();
  $puv_poradi = 0;
  while ($q->Next_Record()) {
    if ($puv_poradi <> $q->Record['PORADI']) {
      $tDavka[] = array(
        'Poradi' => $q->Record['PORADI'],
        'DatumVzniku' => $q->Record['VLOZENO'],
      );
    }
    $puv_poradi = $q->Record['PORADI'];
  }

  $result = array(
    'Davka' => $tDavka,
  );

  return $result;
}

