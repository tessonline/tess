<?php

//Funkce vrati nove cislo jednaci k dane zadosti... 
function vlozDokument($VlastniDokument) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];
  
  //print_r($server->methodparams);ok
  $UdalostiPredchazejici = $server->methodparams["UdalostiPredchazejici"];
//  $VlastniDokument = $server->methodparams["VlastniDokument"];
  $Autorizace = $server->methodparams["Autorizace"];

  $idDZ = $VlastniDokument['Identifikator']['HodnotaID'];

  //print_r($UdalostiPredchazejici);
  //print_r($VlastniDokument);
  //print_r($Autorizace);
  //response null
  Response_Dokument($response_VlastniDokument, false, 'f');

  if (!$VlastniDokument['DoplnujiciData']['PocetListu']) $VlastniDokument['DoplnujiciData']['PocetListu'] = 1;

  if ($VlastniDokument['ZasilkaInfo']['Poznamka']) $VlastniDokument['Poznamka'] = $VlastniDokument['ZasilkaInfo']['Poznamka'];


  //Zpracovani...
//  if (ErmsAsynUdalosti($UdalostiPredchazejici, $vysledek)) {
  //Zalozeni dokumentu
  $res = DokumentZalozeni($VlastniDokument, 'f', $Autorizace, $id, $msg_popis);

  $sql = 'update posta set ZPUSOB_PODANI=3,vlastnich_rukou=9,DRUH_PRILOH=\'elektronické\',typ_dokumentu=\'D\',datum_predani=datum_podatelna_prijeti where id='.$id;
  $q = new DB_POSTA;
  $q->query($sql);

  $text = "Vytvoření nového dokumentu z datového rocestníku (<b>$id</b>)";
  EedTransakce::ZapisLog($id, $text, 'DOC');


  $sql="insert into posta_DS (posta_id,DS_id,odeslana_posta,datum_odeslani,last_date,last_time,last_user_id) VALUES
  ($id,$idDZ,'f','".Date('d.m.Y H:m')."','".Date('Y-m-d')."','".Date('H:i:s')."',0)";
//  echo $sql."<br/>";
  $q->query($sql);

  //Nacteni dokumentu
  If ($id>0) Response_Dokument($response_VlastniDokument, $id, 'f');



//   }
//   else
//    $msg_popis = NastavPopis('DokumentZalozeni','0000');

  if ($VlastniDokument['Soubory']) {
    //$id, $referent, $request, &$message, $replace_file = false
    foreach($VlastniDokument['Soubory'] as $doc_temp) {
      foreach($doc_temp as $doc) {
  //        print_r($doc); echo "------ konec ";
        $temp = array();
        $temp['dmFile'] = $doc;
        UlozSoubor($id, 0, $temp, $message);
        $text = "Vložení souboru ".$temp["dmFile"]["!dmFileDescr"];
        EedTransakce::ZapisLog($id, $text, 'DOC');
      }
    }
  }

  //response
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'VlastniDokumentZalozeniRequest', $msg_popis["Kod"]);

  $vysledek = array(
    'SpslStatus'=>new soapval('SpslStatus', false, $response_OperaceStatus),  //'tns:tOperaceStatus'
  );  
//  print_r($vysledek);
//  ZapisLog($log);
    $return='
<vlozDokumentResponse>
  <SpslStatus>
     <StatusCode>0000</StatusCode>
     <StatusMessage>Dokument vlozen</StatusMessage>
     <Identifikatory>
       <Identifikator>
         <HodnotaID>'.$id.'</HodnotaID>
         <ZdrojID>TMAPES</ZdrojID>
       </Identifikator>
    </Identifikatory>
  </SpslStatus>
</vlozDokumentResponse>

  ';
    return $return;

//  return VratVysledek($vysledek);
}
