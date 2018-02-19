<?php
//Funkce vrati nove cislo jednaci k dane zadosti... 
Function get_cj($session_id,$zpracovatel_id=0,$prichozi_id=0) {
  If (!$software_id=JeNalogovan($session_id)) return VratChybu($session_id,'get_cj','Neprovedena identifikace');
  $q=new DB_POSTA;
  $rok=Date('Y');
  $pracovnik=OdborPrac($zpracovatel_id);
  $odbor=$pracovnik['odbor']?$pracovnik['odbor']:$GLOBALS["KONEKTOR"][$software_id]["ODBOR"];
  $odd=$GLOBALS["CONFIG_POSTA_CP"]["odd"]?$GLOBALS["KONEKTOR"][$software_id]["odd"]:$pracovnik['oddeleni'];
  $stav=$GLOBALS["KONEKTOR"][$software_id]["STAV"]; 
  $stav=$stav+2;
  if ($zpracovatel_id==0)
    $zpracovatel=$GLOBALS["KONEKTOR"][$software_id]["ZPRACOVATEL"]?$GLOBALS["KONEKTOR"][$software_id]["ZPRACOVATEL"]:0;
  else
    $zpracovatel=$zpracovatel_id;
  $jmeno=$GLOBALS["KONEKTOR"][$software_id]["SOFTWARE"];
  if ($prichozi_id>0) {
    //nacteme udaje z puvodniho dokumentu, budeme je potrebovat na spis a cislo jednaci, aby se nevytvarelo nove    
  }
  else {
    $vec="přiřazení čj.";
    $LAST_USER_ID = $GLOBALS["LAST_USER_ID"]?$GLOBALS["LAST_USER_ID"]:$GLOBALS["KONEKTOR"][$software_id]["LAST_USER_ID"];
    $LAST_TIME=Date('H:m:i');
    $LAST_DATE=Date('Y-m-d');
    if ($GLOBALS["KONEKTOR"][$software_id]["OTOC_SMER_PRI_GETCJ"]) $smer='f'; else $smer='t';
    $odeslani='01.01.2100 12:00';
    $sql="insert into posta (ev_cislo,stav,rok,odes_typ,odesl_prijmeni,odesl_posta,datum_podatelna_prijeti,odeslana_posta,odbor,oddeleni,referent,last_date,last_time,last_user_id) values (0,$stav,'$rok','P','".$jmeno."','".$vec."','".$odeslani."','".$smer."',".$odbor.",'".$odd."',".$zpracovatel.",'".$LAST_DATE."','".$LAST_TIME."',".$LAST_USER_ID.")";
    $q->query($sql);
    $posle_id=$q->getlastid("posta", "ID");
  }
  If ($posle_id>0) {
    NastavStatus($posle_id,$LAST_USER_ID);
    $doc = LoadSingleton('EedDokument', $posle_id);
    $dokument_id = $posle_id;
    $cislo_jednaci = $doc->cislo_jednaci;



    $text='(GET_CJ) - vytvořeno čj. '.$cislo_jednaci.' pro dokument ('.$dokument_id.')';
    WriteLog($software_id,$text,$session_id);

    $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
    $vysledek = array(
      'return'=>new soapval('Result', 'tns:Result', $value),
      'dokument_id'=>new soapval('dokument_id', 'xsd:integer', $dokument_id),
      'cislo_jednaci'=>new soapval('cislo_jednaci', 'xsd:string', TxtEncoding4Soap($cislo_jednaci)),
    );
    return VratVysledek($vysledek);
//    return new soapval('Result','tns:Result',$value);
  }
  else {
    $text='(GET_CJ) - nepodařilo se vytvořit čj.';
    WriteLog($software_id,$text,$session_id,1);
    $value = array('RESULT'=>'ERROR','DESCRIPTION'=>TxtEncoding4Soap($text));
    return VratVysledek($value);
  }  
  return $return;
  
}
?>
