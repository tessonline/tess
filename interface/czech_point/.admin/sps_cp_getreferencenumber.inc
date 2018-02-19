<?php
//Funkce vrati nove cislo jednaci k dane zadosti... 
Function GetReferenceNumber($session_id)
{

  $software_id='CP';
  If (!($software_id=JeNalogovan($session_id))) 
  {
    $return='<ns1:GetReferenceNumberResponse ret="Exception" code="-3" xmlns:ns1="http://www.software602.cz/webservices/602xml">
        <ns1:Exception>Nejste prihlaseni</ns1:Exception> 
     </ns1:GetReferenceNumberResponse>
    ';
    $text='(GETREFERENCENUMBER) - není zadáno správně session_id';
    WriteLog('CP',$text,'',1);
    return $return;
  }
  $q=new DB_POSTA;
  $rok=Date('Y');
//  $odbor=$GLOBALS["CONFIG_POSTA_CP"]["ODBOR"]?$GLOBALS["CONFIG_POSTA_CP"]["ODBOR"]:0;
//  $zpracovatel=$GLOBALS["CONFIG_POSTA_CP"]["ZPRACOVATEL"]?$GLOBALS["CONFIG_POSTA_CP"]["ZPRACOVATEL"]:'';
  //nebo mame zpracovatele v session?
  $username=substr($session_id,0,strpos($session_id,'*'));
//  if ($zpracovatel=='')
  { 
    $zpracovatel=$GLOBALS["CONFIG_POSTA_CP"]["VALID_USERS"][$username]["id"]?$GLOBALS["CONFIG_POSTA_CP"]["VALID_USERS"][$username]["id"]:0;
    $pracovnik=OdborPrac($zpracovatel);
    $odbor=$pracovnik['odbor']?$pracovnik['odbor']:$GLOBALS["CONFIG_POSTA_CP"]["ODBOR"];
    $odd=$GLOBALS["CONFIG_POSTA_CP"]["odd"]?$GLOBALS["CONFIG_POSTA_CP"]["odd"]:$pracovnik['oddeleni'];
  }
  $LAST_USER_ID=$GLOBALS["CONFIG_POSTA_CP"]["LAST_USER_ID"];
  $LAST_TIME=Date('H:m:i');
  $LAST_DATE=Date('Y-m-d');
  $stornovano='přidělení čj pro CzechPoint';

  $sql="insert into posta (rok,odes_typ,odesl_prijmeni,odesl_posta,datum_podatelna_prijeti,odeslana_posta,odbor,oddeleni,referent,last_date,last_time,last_user_id,zpusob_podani,druh_priloh,stornovano) 
                   values ('$rok','P','Czech Point Interface','přiřazení čj.','".Date('d.m.Y H:m')."','f',".$odbor.",'".$odd."',".$zpracovatel.",'".$LAST_DATE."','".$LAST_TIME."',".$LAST_USER_ID.",3,'elektronické','".$stornovano."')";
//Die($sql);
  $q->query($sql);
  $posle_id=$q->getlastid("posta", "ID");


  
  If ($posle_id>0) {
    $sql='select * from posta where id='.$posle_id;
    $q->query($sql);
    $q->Next_Record(); 
    $dokument_id=$posle_id;

    $doc = LoadClass('EedDokument', $dokument_id);

    $text='(GETREFERENCENUMBER) - vytvořeno čj. '.$cislo_jednaci.' pro dokument ('.$dokument_id.')';
    WriteLog($software_id,$text,$session_id);

    $text = "Vytvoren dokument z CzP " . $doc->cislo_jednaci . "(".$dokument_id.")";
    EedTransakce::ZapisLog($dokument_id, $text, 'DOC');

    $return='<GetReferenceNumberResponse xmlns="http://www.software602.cz/webservices/602xml">
      <GetReferenceNumberResult>1</GetReferenceNumberResult>
      <ReferenceNumber>'.TxtEncoding4Soap($doc->cislo_jednaci).'</ReferenceNumber>
      <DocumentID>'.$dokument_id.'</DocumentID>
    </GetReferenceNumberResponse>';
    return $return;

  }
  else
  {
    $text='(GETREFERENCENUMBER) - nepodařilo se vytvořit čj.';
    WriteLog($software_id,$text,$session_id,1);
 
    $return=
    '
      <ns1:GetReferenceNumberResponse xmlns:ns1="http://www.software602.cz/webservices/602xml">
        <ns1:GetReferenceNumberResult>-1</ns1:GetReferenceNumberResult> 
        <ns1:Exception>Cannot create CJ</ns1:Exception> 
     </ns1:GetReferenceNumberResponse>
';

  }  
  return $return;
  
}
?>
