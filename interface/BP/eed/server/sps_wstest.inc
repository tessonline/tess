<?php

//Funkce vrati nove cislo jednaci k dane zadosti... 
function WsTestRequest($text, $Autorizace) {
  //nastaveni parametru
  global $server, $soap;

  if (count($Autorizace)>1) {
    if (VratReferenta($Autorizace)==0)
      return VratChybu($log,'Nepovedlo se identifikovat uzivatele v parametru ProvedlKdo');
  }

  $msg_popis = NastavPopis('wsTestRequest','0000');
  //response 
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'WsTestRequest', $msg_popis["Kod"]);
  
  $vysledek = array(
    'WsTestId'=> $text, //tns:tProfilSpisu
    'PosledniPrijataDavka' => array(
      'Cislo' => 1,
      'Stav' => 'Odeslana',
    ),
    'PosledniOdeslanaDavka' => array(
      'Cislo' => 0,
      'Stav' => 'Neodeslana',
    ),
    'OperaceStatus' => $response_OperaceStatus
  );
  
  ZapisLog($log); 
/*
		<xs:enumeration value="Neodeslana"/>
										<xs:enumeration value="Odeslana"/>
										<xs:enumeration value="OdeslanaOdmitnuta"/>
										<xs:enumeration value="PotvrzenaBezChyb"/>
										<xs:enumeration value="PotvrzenaSChybou"/>
*/

  return $vysledek;
}

?>
