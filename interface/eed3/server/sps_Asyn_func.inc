<?php

Function DokumentOtevreni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: dokument musí existovat; u¾ivatel musí být dr¾itelem dokumentu, spis musí být otevøený.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id,$request['Identifikator']['HodnotaID'],$request['Identifikator']['ZdrojID']," AND referent=".VratReferenta($request["Autorizace"])." AND NOT spis_vyrizen IS NULL")) {
    NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
    $sql = "update posta set spis_vyrizen=null $update_set where id=$id;";
    //echo "sql: ".$sql;die();
  
    if ($q->query($sql)) {
      NastavStatus($id,VratReferenta($request["Autorizace"]));
      $msg_popis = NastavPopis('DokumentOtevreni','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('DokumentOtevreni','1001','',$q->Error);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('DokumentOtevreni','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DokumentOtevreni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}

Function DokumentUprava($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: dokument musí existovat; u¾ivatel musí být dr¾itelem dokumentu.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id,$request['ProfilDokumentu']['Identifikator']['HodnotaID'],$request['ProfilDokumentu']['Identifikator']['ZdrojID']," AND referent=".VratReferenta($request["Autorizace"]))) {
    $dokument = NastavDokument($request['ProfilDokumentu']);
    
    if (UlozDokumentInfo($id, $dokument, $q, 'update')) {
      NastavStatus($id,VratReferenta($request["Autorizace"]));
      $msg_popis = NastavPopis('DokumentUprava','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('DokumentUprava','1001','',$q->Error);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('DokumentUprava','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }     

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DokumentUprava '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}

Function DokumentVlozeniDoSpisu($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: spis musí existovat; u¾ivatel musí být dr¾itelem spisu i dokumentu; spis nesmí být uzavøen.
  
  //test, zda existuje spis
  if (ExistujeSpis($id_spis,$request['SpisId']['Identifikator']['HodnotaID'],$request['SpisId']['Identifikator']['ZdrojID']," AND referent=".VratReferenta($request["Autorizace"])." AND spis_vyrizen IS NULL")) {
    //nacteni info spisu
    $spis = ConvertSpisId($id_spis);
    
    //zpracovani dokumentu
    $res = SpisDokumentZpracovani($request['DokumentyVlozene'], $request["Autorizace"], $id, $msg_popis);
    
    if ($res) {
      NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
      $sql = "update posta set cislo_spisu1='".$spis["CISLO_SPISU1"]."', cislo_spisu2='".$spis["CISLO_SPISU2"]."' $update_set where id=$id";
      //echo "sql: ".$sql;die();
    
      if ($q->query($sql)) {
        NastavStatus($id,VratReferenta($request["Autorizace"]));
        $msg_popis = NastavPopis('DokumentVlozeniDoSpisu','0000');
      }
      else {
        $res = false;
        $msg_popis = NastavPopis('DokumentVlozeniDoSpisu','1001','',$q->Error);
      }
    }
    else
      $msg_popis = NastavPopis('DokumentVlozeniDoSpisu','1002',$msg_popis["Popis"],$msg_popis["ErrSql"]);
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('DokumentVlozeniDoSpisu','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DokumentVlozeniDoSpisu '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
} 

Function DokumentVraceni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: dokument je v dr¾ení agendy; dokument není ve spisu.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id,$request['DokumentId']['Identifikator']['HodnotaID'],$request['DokumentId']['Identifikator']['ZdrojID']," AND stav=".($GLOBALS["KONEKTOR"]["ISRZP"]["STAV"]+2)." AND cislo_spisu1 IS NULL AND cislo_spisu2 IS NULL")) {
    NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
    $sql = "update posta set stav=0 $update_set where id=$id;";
    //echo $sql;die();
      
    if ($q->query($sql)) {
      NastavStatus($id,VratReferenta($request["Autorizace"]));
      $msg_popis = NastavPopis('DokumentVraceni','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('DokumentVraceni','1001','',$q->Error);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('DokumentVraceni','1000');
  } 

  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DokumentVraceni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function DokumentVyjmutiZeSpisu($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: dokument a spis musí existovat; u¾ivatelmusí být dr¾itelem spisu i dokumentu; spis nesmí být uzavøen.
  
  //test, zda existuje spis
  if (ExistujeSpis($id_spis,$request['SpisId']['Identifikator']['HodnotaID'],$request['SpisId']['Identifikator']['ZdrojID']," AND referent=".VratReferenta($request["Autorizace"])." AND spis_vyrizen IS NULL")) {
    //test, zda existuje dokument
    if (ExistujeDokument($id,$request['DokumentyVlozene']['DokumentIdVlozeny']['IdDokument']['Identifikator']['HodnotaID'],$request['DokumentyVlozene']['DokumentIdVlozeny']['IdDokument']['Identifikator']['ZdrojID'],"  AND referent=".VratReferenta($request["Autorizace"]))) {
      NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
      $sql = "update posta set cislo_spisu1=NULL, cislo_spisu2=NULL $update_set where id=$id";
      //echo "sql: ".$sql;die();
    
      if ($q->query($sql)) {
        NastavStatus($id,VratReferenta($request["Autorizace"]));
        $msg_popis = NastavPopis('DokumentVyjmutiZeSpisu','0000');
      }
      else {
        $res = false;
        $msg_popis = NastavPopis('DokumentVyjmutiZeSpisu','1002','',$q->Error);
      }
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('DokumentVyjmutiZeSpisu','1001');
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('DokumentVyjmutiZeSpisu','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DokumentVyjmutiZeSpisu '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
} 
    
Function DokumentZmenaZpracovatele($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: dokument nesmí být souèástí spisu; u¾ivatel má právo pøedat dokument jinému zpracovateli.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id,$request['DokumentPredani']['IdDokument']['Identifikator']['HodnotaID'],$request['DokumentPredani']['IdDokument']['Identifikator']['ZdrojID']," AND cislo_spisu1 IS NULL AND cislo_spisu2 IS NULL")) {
    NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
    $sql = "update posta set referent=".VratReferenta(false, $request['Prebirajici']['novyZpracovatel'])." $update_set where id=$id";
    //echo $sql;die();
    
    if ($q->query($sql)) {
      NastavStatus($id,VratReferenta($request["Autorizace"]));
      $msg_popis = NastavPopis('DokumentZmenaZpracovatele','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('DokumentZmenaZpracovatele','1001','',$q->Error);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('DokumentZmenaZpracovatele','1000');
  } 

  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DokumentZmenaZpracovatele '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}

Function DokumentZruseni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: dokument musí existovat; u¾ivatel musí být dr¾itelem dokumentu; v¹echna vypravení dokumentu musí být ve stavu „nevypraveno“ nebo „stornováno“.

  //test, zda existuje dokument
  if (ExistujeDokument($id,$request['DokumentZruseni']['Identifikator']['HodnotaID'],$request['DokumentZruseni']['Identifikator']['ZdrojID']," AND referent=".VratReferenta($request["Autorizace"])." AND stornovano IS NULL AND datum_vypraveni IS NULL")) {
    NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
    $sql = "update posta set stornovano='".NastavText('DokumentZruseni','001')."' $update_set where id=$id;";
    //echo $sql;die();
  
    if ($q->query($sql)) {
      NastavStatus($id,VratReferenta($request["Autorizace"]));
      $msg_popis = NastavPopis('DokumentZruseni','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('DokumentZruseni','1001','',$q->Error);
    }    
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('DokumentZruseni','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DokumentZruseni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}

Function DoruceniUprava($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: dokument musí existovat;musí se jednat o pøíchozí dokument; u¾ivatel musí být dr¾itelem dokumentu.
  
  //test, zda existuje dokument pøíchozí
  if (ExistujeDokument($id,$request['DokumentDoruceni']['IdDokument']['Identifikator']['HodnotaID'],$request['DokumentDoruceni']['IdDokument']['Identifikator']['ZdrojID']," AND odeslana_posta='f' AND referent=".VratReferenta($request["Autorizace"]))) {
    $dokument = NastavDokument($request['DokumentDoruceni']);
    
    if (UlozDokumentInfo($id, dokument, $q, 'update')) {
      NastavStatus($id,VratReferenta($request["Autorizace"]));
      $msg_popis = NastavPopis('DoruceniUprava','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('DoruceniUprava','1001','',$q->Error);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('DoruceniUprava','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DoruceniUprava '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}

Function SouborZalozeni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log) {
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  //Zpracovani...
  //Podmínky: u¾ivatelmusí být dr¾itel dokumentu.
  
  //test, zda existuje dokument
  $ref = VratReferenta($request["Autorizace"])?VratReferenta($request["Autorizace"]):0;
  if (UlozSoubor($id, $ref, $request['ZalozeniSouboru'], $message))
    $msg_popis = NastavPopis('SouborZalozeni','0000', $message);
  else {
    $res = false;
    $msg_popis = NastavPopis('SouborZalozeni','1001',$message);
  }

  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }

  //response
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SouborZalozeni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function SouborNovaVerze($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log) {
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
//Zpracovani...
  $ref = VratReferenta($request["Autorizace"])?VratReferenta($request["Autorizace"]):0;
  if (UlozSoubor($id, $ref, $request['NovaVerzeSouboru'], $message, true))
    $msg_popis = NastavPopis('SouborNovaVerze','0000');
  else {
    $res = false;
    $msg_popis = NastavPopis('SouborNovaVerze','1001',$message);
  }
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SouborNovaVerze '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}

Function SouborZruseni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //test, zda existuje dokument
    
  if (ZrusSoubor($id, $request['ZruseniSouboru'], $message))
    $msg_popis = NastavPopis('SouborZruseni','0000');
  else {
    $res = false;
    $msg_popis = NastavPopis('SouborZruseni','1001',$message);
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SouborZruseni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}

Function SouborVlozitKDokumentu($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log) {
  //print_r($request);
  $res = true;
  //attr
  $udalostId = $request['!UdalostId'];

  if ($sqlTran) $q->Tran_Begin();

  //Zpracovani...
  //Podmínky: u¾ivatelmusí být dr¾itel dokumentu
  //test, zda existuje dokument
  if (ExistujeDokument($id_dokument,$request['DokumentZaevidovaniSouboru']['IdDokument']['Identifikator']['HodnotaID'],$request['DokumentZaevidovaniSouboruVypraveni']['IdDokument']['Identifikator']['ZdrojID'], " AND referent=".VratReferenta($request["Autorizace"]))) {

    if (ZkopirujSoubor($id_dokument, $id, $request['DokumentZaevidovaniSouboru']['IdDokument']['Identifikator']['HodnotaID'], $message))
      $msg_popis = NastavPopis('SouborVlozitKDokumentu','0000');
    else {
      $res = false;
      $msg_popis = NastavPopis('SouborVlozitKDokumentu','1002',$message);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('SouborVlozitKDokumentu','1000');
  }

  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }

  //response
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SouborVlozitKVypraveni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);

  return $res;
}


Function SouborVlozitKVypraveni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: u¾ivatelmusí být dr¾itel dokumentu; vypravení musí být ve stavu nevypraveno.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id_dokument,$request['DokumentZaevidovaniSouboruVypraveni']['IdDokument']['Identifikator']['HodnotaID'],$request['DokumentZaevidovaniSouboruVypraveni']['IdDokument']['Identifikator']['ZdrojID'], " AND referent=".VratReferenta($request["Autorizace"]))) {
    //test, zda existuje dokument vypraveni
    if (ExistujeDokument($id,$request['DokumentZaevidovaniSouboruVypraveni']['Vypraveni']['Identifikator']['HodnotaID'],$request['DokumentZaevidovaniSouboruVypraveni']['Vypraveni']['Identifikator']['ZdrojID'], " AND id_puvodni=$id_dokument AND datum_vypraveni IS NULL")) {
      
      if (ZkopirujSoubor($id_dokument, $id, $request['DokumentZaevidovaniSouboruVypraveni']['Vypraveni']['ZasilkaInfo']['OdkazyNaSoubory'], $message))
        $msg_popis = NastavPopis('SouborVlozitKVypraveni','0000');
      else {
        $res = false;
        $msg_popis = NastavPopis('SouborVlozitKVypraveni','1002',$message);
      }
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('SouborVlozitKVypraveni','1001');
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('SouborVlozitKVypraveni','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }     

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SouborVlozitKVypraveni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function SouborVyjmoutZVypraveni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: u¾ivatelmusí být dr¾itel dokumentu; vypravení musí být ve stavu nevypraveno.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id_dokument,$request['DokumentZruseniSouboruVypraveni']['IdDokument']['Identifikator']['HodnotaID'],$request['DokumentZruseniSouboruVypraveni']['IdDokument']['Identifikator']['ZdrojID'], " AND referent=".VratReferenta($request["Autorizace"]))) {
    //test, zda existuje dokument vypraveni
    if (ExistujeDokument($id,$request['DokumentZruseniSouboruVypraveni']['Vypraveni']['Identifikator']['HodnotaID'],$request['DokumentZruseniSouboruVypraveni']['Vypraveni']['Identifikator']['ZdrojID'], " AND id_puvodni=$id_dokument AND datum_vypraveni IS NULL")) {
    
      if (ZrusSoubor($id, $request['DokumentZruseniSouboruVypraveni']['Vypraveni']['ZasilkaInfo']['Soubory'], $message))
        $msg_popis = NastavPopis('SouborVyjmoutZVypraveni','0000');
      else {
        $res = false;
        $msg_popis = NastavPopis('SouborVyjmoutZVypraveni','1002',$message);
      }
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('SouborVyjmoutZVypraveni','1001');
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('SouborVyjmoutZVypraveni','1000');
  } 
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SouborVyjmoutZVypraveni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function SpisOtevreni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: spis musí existovat; u¾ivatel musí být dr¾itelem spisu; spis musí být uzavøen.
  
  //test, zda existuje spis
  if (ExistujeSpis($id_spis,$request['SpisId']['Identifikator']['HodnotaID'],$request['SpisId']['Identifikator']['ZdrojID']," AND referent=".VratReferenta($request["Autorizace"])." AND NOT spis_vyrizen IS NULL")) {
    //nacteni info spisu
    $spis = ConvertSpisId($id_spis);
  
    NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
    $sql = "update posta set spis_vyrizen=NULL $update_set where cislo_spisu1='".$spis["CISLO_SPISU1"]."' AND cislo_spisu2='".$spis["CISLO_SPISU2"]."'";
    //echo "sql: ".$sql;die();
    
    if ($q->query($sql)) {
      NastavStatusSpis($id_spis,$request["Autorizace"]);
      $msg_popis = NastavPopis('SpisOtevreni','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('SpisOtevreni','1001','',$q->Error);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('SpisOtevreni','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SpisOtevreni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function SpisVraceni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: spis je v dr¾ení agendy.
  
  //test, zda existuje spis
  if (ExistujeSpis($id_spis,$request['SpisId']['Identifikator']['HodnotaID'],$request['SpisId']['Identifikator']['ZdrojID']," AND stav=".($GLOBALS["KONEKTOR"]["ISRZP"]["STAV"]+2))) {
    //nacteni info spisu
    $spis = ConvertSpisId($id_spis);
    
    NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
    $sql = "update posta set stav=0 $update_set where cislo_spisu1='".$spis["CISLO_SPISU1"]."' AND cislo_spisu2='".$spis["CISLO_SPISU2"]."'";
    //echo $sql;die();
      
    if ($q->query($sql)) {
      NastavStatusSpis($id_spis);
      $msg_popis = NastavPopis('SpisVraceni','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('SpisVraceni','1001','',$q->Error);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('SpisVraceni','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SpisVraceni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function SpisVyrizeni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: spis musí existovat; u¾ivatel musí být dr¾itelem spisu; musí být splnìny zákonné podmínky pro vyøízení spisu a jeho obsahu.
  
  //test, zda existuje spis
  if (ExistujeSpis($id_spis,$request['SpisId']['Identifikator']['HodnotaID'],$request['SpisId']['Identifikator']['ZdrojID']," AND referent=".VratReferenta($request["Autorizace"])." AND spis_vyrizen IS NULL")) {
    //nacteni info spisu
    $spis = ConvertSpisId($id_spis);

    NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
    $sql = "update posta set spis_vyrizen='".Date('Y-m-d')."',status=1 $update_set where cislo_spisu1='".$spis["CISLO_SPISU1"]."' AND cislo_spisu2='".$spis["CISLO_SPISU2"]."'";
    //echo "sql: ".$sql;die();
    
    if ($q->query($sql)) {
      NastavStatusSpis($id_spis,$request["Autorizace"]);
      $msg_popis = NastavPopis('SpisVyrizeni','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('SpisVyrizeni','1001','',$q->Error);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('SpisVyrizeni','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SpisVyrizeni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
   
Function SpisZalozeni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log) {   
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: dokument musí existovat; u¾ivatel musí být dr¾itelem dokumentu; spis nesmí existovat.
  
  //Zalozeni spisu
  $res = SpisDokumentZalozeni($request['ProfilSpisu'], $request['DokumentyVlozene'], $request['Autorizace'], $id_spis, $msg_popis);
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SpisZalozeni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}    
    
Function SpisZmenaZpracovatele($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: u¾ivatelmá právo pøedat spis jinému zpracovateli.
  
  //test, zda existuje spis
  if (ExistujeSpis($id_spis,$request['SpisPredani']['IdSpis']['Identifikator']['HodnotaID'],$request['SpisPredani']['IdSpis']['Identifikator']['ZdrojID'])) {
    //nacteni info spisu
    $spis = ConvertSpisId($id_spis);
    
    NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
    $sql = "update posta set referent=".$request['Prebirajici']['novyZpracovatel']." $update_set where cislo_spisu1='".$spis["CISLO_SPISU1"]."' AND cislo_spisu2='".$spis["CISLO_SPISU2"]."'";
    //echo $sql;die();
    
    if ($q->query($sql)) {
      NastavStatusSpis($id_spis,$request["Autorizace"]);
      $msg_popis = NastavPopis('SpisZmenaZpracovatele','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('SpisZmenaZpracovatele','1001','',$q->Error);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('SpisZmenaZpracovatele','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SpisZmenaZpracovatele '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function SpisZruseni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: u¾ivatel musí být dr¾itelem spisu, spis obsahuje iniciaèní dokument.
  
  //test, zda existuje spis
  if (ExistujeSpis($id_spis,$request['SpisId']['Identifikator']['HodnotaID'],$request['SpisId']['Identifikator']['ZdrojID']," AND referent=".VratReferenta($request["Autorizace"]))) {
    //nacteni info spisu
    $spis = ConvertSpisId($id_spis);
  
    NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
    $sql = "update posta set stornovano='".NastavText('SpisZruseni','001')."' $update_set where cislo_spisu1='".$spis["CISLO_SPISU1"]."' AND cislo_spisu2='".$spis["CISLO_SPISU2"]."'";
    //echo "sql: ".$sql;die();
    
    if ($q->query($sql)) {
      NastavStatusSpis($id_spis,$request["Autorizace"]);
      $msg_popis = NastavPopis('SpisZruseni','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('SpisZruseni','1001','',$q->Error);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('SpisZruseni','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SpisZruseni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function VypraveniDoruceno($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: vypravení musí existovat; vypravení musí být vypraveno.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id_dokument,$request['DokumentDoruceniVypraveni']['IdDokument']['Identifikator']['HodnotaID'],$request['DokumentDoruceniVypraveni']['IdDokument']['Identifikator']['ZdrojID'])) {
    //test, zda existuje dokument vypraveni
    if (ExistujeDokument($id,$request['DokumentDoruceniVypraveni']['Vypraveni']['Identifikator']['HodnotaID'],$request['DokumentDoruceniVypraveni']['Vypraveni']['Identifikator']['ZdrojID'], " AND id_puvodni=$id_dokument AND NOT datum_vypraveni IS NULL")) {
      NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
      $sql = "update posta set datum_doruceni='".ConvertDatumToString($request['DokumentDoruceniVypraveni']['Vypraveni']['ZasilkaInfo']['DatumDoruceni'])."' $update_set where id=$id";
      //echo "sql: ".$sql;die();
    
      if ($q->query($sql)) {
        NastavStatus($id,VratReferenta($request["Autorizace"]));
        $msg_popis = NastavPopis('VypraveniDoruceno','0000');
      }
      else {
        $res = false;
        $msg_popis = NastavPopis('VypraveniDoruceno','1002','',$q->Error);
      }
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('VypraveniDoruceno','1001');
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('VypraveniDoruceno','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }     

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'VypraveniDoruceno '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function VypraveniPredatVypravne($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: vypravení musí existovat; vypravení musí být ve stavu „nevypraveno“.
  
  if (array_key_exists('Obalka', $request)) 
    $request_Vypraveni = $request['Obalka']['ObalkaObsah']['Vypraveni'];
  else
    $request_Vypraveni = $request['Vypraveni'];
    
  //test, zda existuje dokument vypraveni
  if (ExistujeDokument($id,$request_Vypraveni['Identifikator']['HodnotaID'],$request_Vypraveni['Identifikator']['ZdrojID'], " AND datum_vypraveni IS NULL")) {
    NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
    $sql = "update posta set datum_podatelna_prijeti='".Date('d.m.Y H:i')."' $update_set where id=$id";
    //echo "sql: ".$sql;die();
  
    if ($q->query($sql)) {
      NastavStatus($id,VratReferenta($request["Autorizace"]));
      $msg_popis = NastavPopis('VypraveniPredatVypravne','0000');
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('VypraveniPredatVypravne','1001','',$q->Error);
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('VypraveniPredatVypravne','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }     

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'VypraveniPredatVypravne '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function VypraveniUprava($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: vypravení musí existovat; u¾ivatel je dr¾itelem dokumentu; vypravení musí být ve stavu „nevypraveno“.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id_dokument,$request['DokumentUpravaVypraveni']['IdDokument']['Identifikator']['HodnotaID'],$request['DokumentUpravaVypraveni']['IdDokument']['Identifikator']['ZdrojID']," AND referent=".VratReferenta($request["Autorizace"]))) {
    //test, zda existuje dokument vypraveni
    if (ExistujeDokument($id,$request['DokumentUpravaVypraveni']['Vypraveni']['Identifikator']['HodnotaID'],$request['DokumentUpravaVypraveni']['Vypraveni']['Identifikator']['ZdrojID'], " AND id_puvodni=$id_dokument AND datum_vypraveni IS NULL")) {
      //nastaveni dokumnetu
      $dokument = NastavDokument($request['DokumentUpravaVypraveni']['Vypraveni'], $request['DokumentUpravaVypraveni']['Vypraveni']['Adresat'], $request['DokumentUpravaVypraveni']['Vypraveni']['ZasilkaInfo']);
      
      //ulozeni dokumentu
      if (UlozDokumentInfo($id, $dokument, $q, 'update')) {
        NastavStatus($id,VratReferenta($request["Autorizace"]));
        $msg_popis = NastavPopis('VypraveniUprava','0000');
      }
      else {
        $res = false;
        $msg_popis = NastavPopis('VypraveniUprava','1002','',$q->Error);
      }
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('VypraveniUprava','1001');
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('VypraveniUprava','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }     

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'VypraveniUprava '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function VypraveniVypraveno($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: vypravení musí existovat; vypravení musí být ve stavu „nevypraveno“ nebo „pøedáno k vypravení“.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id_dokument,$request['DokumentVypravenoVypraveni']['IdDokument']['Identifikator']['HodnotaID'],$request['DokumentVypravenoVypraveni']['IdDokument']['Identifikator']['ZdrojID'])) {
    //test, zda existuje dokument vypraveni
    if (ExistujeDokument($id,$request['DokumentVypravenoVypraveni']['Vypraveni']['Identifikator']['HodnotaID'],$request['DokumentVypravenoVypraveni']['Vypraveni']['Identifikator']['ZdrojID'], " AND id_puvodni=$id_dokument AND datum_vypraveni IS NULL")) {
      NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
      $sql = "update posta set datum_vypraveni='".ConvertDatumToString($request['DokumentVypravenoVypraveni']['Vypraveni']['ZasilkaInfo']['DatumVypraveni'])."' $update_set where id=$id";
      //echo "sql: ".$sql;die();
    
      if ($q->query($sql)) {
        NastavStatus($id,VratReferenta($request["Autorizace"]));
        $msg_popis = NastavPopis('VypraveniVypraveno','0000');
      }
      else {
        $res = false;
        $msg_popis = NastavPopis('VypraveniVypraveno','1002','',$q->Error);
      }
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('VypraveniVypraveno','1001');
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('VypraveniVypraveno','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }     

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'VypraveniVypraveno '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function VypraveniZalozeni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: dokument musí existovat;musí se jednat o výstupní dokument; u¾ivatel je dr¾itelem dokumentu.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id_dokument,$request['DokumentZaevidovaniVypraveni']['IdDokument']['Identifikator']['HodnotaID'],$request['DokumentZaevidovaniVypraveni']['IdDokument']['Identifikator']['ZdrojID']," AND odeslana_posta='t' AND referent=".VratReferenta($request["Autorizace"]))) {
    //nacteni dokumentu
    $dokument_zaevidovani = VratDokumentInfo($id_dokument);
    //test, zda existuje dokument vypraveni
    if (!ExistujeDokument($id,$request['DokumentZaevidovaniVypraveni']['Vypraveni']['Identifikator']['HodnotaID'],$request['DokumentZaevidovaniVypraveni']['Vypraveni']['Identifikator']['ZdrojID'])) {
      //nastaveni dokumnetu
      $dokument = NastavDokument($request['DokumentZaevidovaniVypraveni']['Vypraveni'], $request['DokumentZaevidovaniVypraveni']['Vypraveni']['Adresat'], $request['DokumentZaevidovaniVypraveni']['Vypraveni']['ZasilkaInfo']);
      $dokument["id_puvodni"] = $id_dokument;
      $dokument["cislo_jednaci1"] = !ValueIsNull($dokument_zaevidovani[CISLO_JEDNACI1]) ? $dokument_zaevidovani[CISLO_JEDNACI1] : 'NULL';
      $dokument["cislo_jednaci2"] = !ValueIsNull($dokument_zaevidovani[CISLO_JEDNACI2]) ? $dokument_zaevidovani[CISLO_JEDNACI2] : 'NULL';
      $dokument["cislo_spisu1"] = !ValueIsNull($dokument_zaevidovani[CISLO_SPISU1]) ? $dokument_zaevidovani[CISLO_SPISU1] : 'NULL';
      $dokument["cislo_spisu2"] = !ValueIsNull($dokument_zaevidovani[CISLO_SPISU2]) ? $dokument_zaevidovani[CISLO_SPISU2] : 'NULL';
      $dokument["vec"] = !ValueIsNull($dokument_zaevidovani[VEC]) ? TxtEncodingFromSoap($dokument_zaevidovani[VEC]) : 'NULL';
      $dokument["stav"] = !ValueIsNull($dokument_zaevidovani[STAV]) ? $dokument_zaevidovani[STAV] : 'NULL';
      $dokument["odbor"] = !ValueIsNull($dokument_zaevidovani[ODBOR]) ? $dokument_zaevidovani[ODBOR] : 'NULL';
      $dokument["oddeleni"] = !ValueIsNull($dokument_zaevidovani[ODDELENI]) ? $dokument_zaevidovani[ODDELENI] : 'NULL';
      $dokument["referent"] = !ValueIsNull($dokument_zaevidovani[ZPRACOVATEL]) ? $dokument_zaevidovani[ZPRACOVATEL] : 'NULL';
      $dokument["skartace"] = !ValueIsNull($dokument_zaevidovani[SKARTACE_ID]) ? $dokument_zaevidovani[SKARTACE_ID] : 'NULL';
      $dokument["datum_podatelna_prijeti"] = '01.01.2100 12:00';
      $dokument["odeslana_posta"] = 't';
      $dokument["ev_cislo"] = '0';
      $dokument["rok"] = date('Y');
      if (!$dokument["odes_typ"]) $dokument["odes_typ"] = '';
      
      //ulozeni dokumentu
      if (UlozDokumentInfo($id, $dokument, $q)) {
        NastavStatus($id,VratReferenta($request["Autorizace"]));
        CopyFilesDokument($log,$id_dokument,$id); //zkopirujeme soubory ze zakladajiciho dokumentu
        $msg_popis = NastavPopis('VypraveniZalozeni','0000');
      }
      else {
        $res = false;
        $msg_popis = NastavPopis('VypraveniZalozeni','1002','',$q->Error);
      }
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('VypraveniZalozeni','1001');
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('VypraveniZalozeni','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }     

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'VypraveniZalozeni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function VypraveniZruseni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr  
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: vypravení musí existovat; u¾ivatel je dr¾itelem dokumentu.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id_dokument,$request['DokumentZruseniVypraveni']['IdDokument']['Identifikator']['HodnotaID'],$request['DokumentZruseniVypraveni']['IdDokument']['Identifikator']['ZdrojID']," AND referent=".VratReferenta($request["Autorizace"]))) {
    //test, zda existuje dokument vypraveni
    if (ExistujeDokument($id,$request['DokumentZruseniVypraveni']['Vypraveni']['Identifikator']['HodnotaID'],$request['DokumentZruseniVypraveni']['Vypraveni']['Identifikator']['ZdrojID'], " AND id_puvodni=$id_dokument")) {
      NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
      $sql = "update posta set stornovano='".NastavText('VypraveniZruseni','001')."' $update_set where id=$id";
      //echo "sql: ".$sql;die();
    
      if ($q->query($sql)) {
        NastavStatus($id,VratReferenta($request["Autorizace"]));
        $msg_popis = NastavPopis('VypraveniZruseni','0000');
      }
      else {
        $res = false;
        $msg_popis = NastavPopis('VypraveniZruseni','1002','',$q->Error);
      }
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('VypraveniZruseni','1001');
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('VypraveniZruseni','1000');
  }
  
  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }     

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'VypraveniZruseni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}

//********************************* IN *******************************************

Function DokumentPostoupeni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: dokument je v dr¾ení ESS; dokument nesmí být zaøazen do spisu.
  
  //test, zda existuje dokument
  if (ExistujeDokument($id_dokument,$request['DorucenyDokument']['Identifikator']['HodnotaID'],$request['DorucenyDokument']['Identifikator']['ZdrojID']," AND stav=".($GLOBALS["KONEKTOR"]["ISRZP"]["STAV"]+1)." AND cislo_spisu1 IS NULL AND cislo_spisu2 IS NULL")) {
    $dokumenty = VratDokumenty("id_puvodni=$id_dokument");
//    $dokumenty = VratDokumenty(" stav=".($GLOBALS["KONEKTOR"]["ISRZP"]["STAV"]+1));
    $dokumenty_ess = VratDokumenty("id_puvodni=$id_dokument AND stav=71");
//    $dokumenty_ess = VratDokumenty(" stav=".($GLOBALS["KONEKTOR"]["ISRZP"]["STAV"]+1));
    
    if (count($dokumenty)==count($dokumenty_ess)) {
      $dokumenty[] = $id_dokument;
      NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
      $sql = "update posta set stav=".($GLOBALS["KONEKTOR"]["ISRZP"]["STAV"]+2)." $update_set where id IN (".implode(",", $dokumenty).")";
      //echo $sql;die();
      
      if ($q->query($sql)) {
        NastavStatusDokumenty($dokumenty);
        $msg_popis = NastavPopis('DokumentPostoupeni','0000');
      }
      else {
        $res = false;
        $msg_popis = NastavPopis('DokumentPostoupeni','1002','',$q->Error);
      }
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('DokumentPostoupeni','1001');
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('DokumentPostoupeni','1000');
  } 

  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'DokumentPostoupeni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}
    
Function SpisPostoupeni($request,&$q,$sqlTran,$poradi,&$response_Zprava,&$log)
{
  //print_r($request);
  $res = true;
  //attr
  $udalostId = $request['!UdalostId'];
  
  if ($sqlTran) $q->Tran_Begin();
  
  //Zpracovani...
  //Podmínky: spis je v dr¾ení ESS
  
  //test, zda existuje dokument
  if (ExistujeSpis($id_spis,$request['ProfilSpisu']['Identifikator']['HodnotaID'],$request['ProfilSpisu']['Identifikator']['ZdrojID']," AND stav=0")) {
    $spis = ConvertSpisId($id_spis);
    
    $dokumenty = VratDokumenty('cislo_spisu1='.$spis[CISLO_SPISU1].' and cislo_spisu2='.$spis[CISLO_SPISU2]);
    $dokumenty_ess = VratDokumenty('cislo_spisu1='.$spis[CISLO_SPISU1].' and cislo_spisu2='.$spis[CISLO_SPISU2].' AND stav=0');
    
    if (count($dokumenty)==count($dokumenty_ess)) {
      NastavInfo($insert_fields, $insert_values, $update_set,VratReferenta($request["Autorizace"]));
      $sql = "update posta set stav=".($GLOBALS["KONEKTOR"]["ISRZP"]["STAV"]+2)." $update_set where id IN (".implode(",", $dokumenty).")";
      //echo $sql;die();
      
      if ($q->query($sql)) {
        NastavStatusSpis($id_spis,$request["Autorizace"]);
        $msg_popis = NastavPopis('SpisPostoupeni','0000');
      }
      else {
        $res = false;
        $msg_popis = NastavPopis('SpisPostoupeni','1002','',$q->Error);
      }
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('SpisPostoupeni','1001');
    }
  }
  else {
    $res = false;
    $msg_popis = NastavPopis('SpisPostoupeni','1000');
  } 

  if ($res) {
    if ($sqlTran) $q->Tran_Commit();
  } else {
    if ($sqlTran) $q->Tran_Rollback();
  }    

  //response 
  Response_Zprava($response_Zprava, $msg_popis["Kod"], $msg_popis["Popis"], $udalostId, $poradi);
  NastavLog($log, $msg_popis["Kod"].': '.$msg_popis["Popis"].($msg_popis["ErrSql"] ? ' | '.$msg_popis["ErrSql"] : '') , 'SpisPostoupeni '.$poradi.'|'.$udalostId, $msg_popis["Kod"]);
  
  return $res;
}

