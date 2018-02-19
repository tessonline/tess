<?php

//Funkce vrati nove cislo jednaci k dane zadosti...
function vlozPrilohu($VlastniDokument) {
  //nastaveni parametru
  global $server, $soap;
  $server->responseMethodname = str_replace("Request", "", $server->methodname).'Response';
  $server->methodURI = $soap["methodURI"];

  //print_r($server->methodparams);
  //$UdalostiPredchazejici = $server->methodparams["UdalostiPredchazejici"];
//  $VlastniDokument = $server->methodparams["VlastniDokument"];
  //$Autorizace = $server->methodparams["Autorizace"];
  //print_r($UdalostiPredchazejici);
  //print_r($VlastniDokument);
  //print_r($Autorizace);

  //response null

  $id = $VlastniDokument['Identifikator']['HodnotaID'];

  if ($id>0)  {

    //Zpracovani...
  //  if (ErmsAsynUdalosti($UdalostiPredchazejici, $vysledek)) {
      //Zalozeni dokumentu
  //    $res = DokumentZalozeni($VlastniDokument, 'f', $Autorizace, $id, $msg_popis);

      //Nacteni dokumentu
  //    If ($id>0) Response_Dokument($response_VlastniDokument, $id, 'f');
  //   }
  //   else
      $msg_popis = NastavPopis('DokumentZalozeni','0000');

    if ($VlastniDokument['Soubory']) {
      //$id, $referent, $request, &$message, $replace_file = false
      foreach($VlastniDokument['Soubory'] as $doc_temp) {
        if ($doc_temp['!dmFileDescr']) {
          $a = $doc_temp;
          unset($doc_temp); $doc_temp = array();
          $doc_temp['0'] = $a;
        }
        foreach($doc_temp as $doc) {
//            print_r($doc); echo "------ konec ";
          $temp = array();
          $temp['dmFile'] = $doc;

          $file = base64_decode($doc['dmEncodedContent']);
          //echo "onma $datum $status $doruceni " . strlen($file);

          $datumOd = strpos($file, "<q:dmDeliveryTime>") + 18;
          $datumDo = strpos($file, "</q:dmDeliveryTime>");

          //echo "$datumOd - $datumDo";

          $datum = substr($file, $datumOd, $datumDo-$datumOd);

          $datum = ConvertDatumToString($datum);

          $statusOd = strpos($file, "<q:dmMessageStatus>")+19;
          $statusDo = strpos($file, "</q:dmMessageStatus>");

          $status = substr($file, $statusOd, $statusDo-$statusOd);
          $doruceni = $GetListOfMessagesResponse[$status];

          // echo "onma $datum  XX$status $doruceni";

          UlozSoubor($id, 0, $temp, $message);
        }
      }
    }

  $sql = "update posta set datum_doruceni='".$datum."', poznamka='ISDS: ".($doruceni)."',status=1 where id=".$id;
  $q = new DB_POSTA;
  $q->query($sql);

  $text = "Uložena doručenka z datového rozcestníku (<b>$id</b>)";
  EedTransakce::ZapisLog($id, $text, 'DOC');

  }
  $response_OperaceStatus = NastavPopis('DokumentZalozeni','0000');
  //response
  Response_OperaceStatus($response_OperaceStatus, $msg_popis["Kod"], $msg_popis["Popis"]);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'VlastniDokumentZalozeniRequest', $msg_popis["Kod"]);

  $vysledek = array(
    'SpslStatus'=>new soapval('SpslStatus', false, $response_OperaceStatus),  //'tns:tOperaceStatus'
  );

  $return='
<vlozPrilohuResponse>
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
</vlozPrilohuResponse>
  ';
  return $return;
}
