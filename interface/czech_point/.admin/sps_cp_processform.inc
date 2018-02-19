<?php
//Zpracovani udaju od czechpointu 
Function ProcessXmlData($session_id,$dokument)
{
  //print_r($processform);
  $software_id='CP';
  $text="";
  $dokument=$dokument['dokument'];


  $typ_doc=$dokument['metadata']['typ_dokumentu'];

  $text="";
  $dokument_id=$dokument['identifikace']['dokument_id'];
  $zpracovatel=$GLOBALS["CONFIG_POSTA_CP"]["VALID_USERS"][$username]["id"]?$zpracovatel=$GLOBALS["CONFIG_POSTA_CP"]["VALID_USERS"][$username]["id"]:0;
  $GLOBALS["DOKUMENT_ID"]=$dokument_id;

  if (($typ_doc == 201 || $typ_doc == 202) && !$dokument_id) {
    $dokument_id = -1; //pri autorizovane konverzi neprijde obcas ID
  }

  If (!($dokument_id)) {
    $text='(PROCESSFORM) - nenĂ­ zadĂĄno sprĂĄvnÄ dokument_id';
    WriteLog($software_id,$text,'',1);
    $return=
      '
<ns1:processform_response ret="Exception" code="-2" xmlns:ns1="http://ws.exprit.cz/ws602">
  <ns1:desc>neni identifikace dokument_id</ns1:desc>
</ns1:processform_response>
  ';
    return $return;
  }


  While(list($key,$val)=each($dokument['metadata'])) $text.=$key."-".$val."|";
    WriteLog($software_id,$text);
  $metadata=$dokument['metadata'];
  $prilohy=$dokument['prilohy'];

  $adresa=$dokument['evidencni_udaje'];

  //$adresa=$dokument['adresy']['adresa']['0'];
  //if ($adresa['jmobyv']=='' && $adresa['prijobyv']=='') $adresa=$dokument['adresy']['adresa']['1'];

  if (trim($adresa['typ_zadatele']<>1))
  {
    //pravnicka osoba;
    $osoba=$adresa['pravnicka_osoba'];
    $typ_odesl='P';
    $odesl_prijmeni=$osoba['nazev_organicace']?$osoba['nazev_organicace']:$osoba['nazev_organizace'];
    $odesl_ico=$osoba['ico'];
  }
  else
  {
  //  Echo "Fyzicka osoba";
    $osoba=$adresa['fyzicka_osoba'];
  //  print_r($osoba);
    //fyzicka osoba;
    $typ_odesl='O';
    $odesl_prijmeni=$osoba['prijmeni'];
    $odesl_jmeno=$osoba['jmeno'].($osoba['titpredjm']?', '.$osoba['titpredjm']:'');

  }

  $odesl_ulice=$osoba['adresa']['ulice']?$osoba['adresa']['ulice']:$osoba['adresa_bydliste']['ulice'];
  $odesl_cpcor=$osoba['adresa']['cp_co']?$osoba['adresa']['cp_co']:$osoba['adresa_bydliste']['cp_co'];

  //if (strpos($odesl_cpcor,'/')) list((int)$odesl_cp,(int)$odesl_cor)=explode('/',$odesl_cpcor);
  if (strpos($odesl_cpcor,'/')) list($odesl_cp,$odesl_cor)=explode('/',$odesl_cpcor);
  else $odesl_cp=$odesl_cpcor;
  $odesl_cp=(int)$odesl_cp;
  $odesl_cor=(int)$odesl_cor;
  if ($odesl_cp==0) $odesl_cp='';
  if ($odesl_cor==0) $odesl_cor='';

  $odesl_posta=$osoba['adresa']['obec']?$osoba['adresa']['obec']:$osoba['adresa_bydliste']['obec'];
  $odesl_psc=$osoba['adresa']['psc']?$osoba['adresa']['psc']:$osoba['adresa_bydliste']['psc'];
  $poznamka=($adresa['telefon']?'telfon:'.$adresa['telefon']:'');



  if ($metadata['vec']=='')
    $vec=TxtEncoding4Soap($GLOBALS["CONFIG_POSTA_CP"]["DRUH_ZADOSTI"][$typ_doc]["NAZEV"]);
  else
    $vec=$metadata['vec'];


  $datum=$metadata['datum_dokumentu'];
  if (strpos($datum,"-"))
  {
    $datumkod=explode("-",$datum);
    $odeslano=$datumkod[2].".".$datumkod[1].".".$datumkod[0]." ".Date('H:m');
  }
  else
    $odeslano=$datum;

  //Die($vec);
  if (!trim($odesl_prijmeni))
  {
    $odesl_prijmeni='Czech Point';
    $odesl_jmeno='Ministerstvo vnitra';
    $status='f';
    $typ_odesl='P';
  }

  if ($typ_doc == 201 || $typ_doc == 202) {
    //autorizovana konverze
    $GLOBALS["CONFIG_POSTA_CP"]["UZAVRIT_SPIS"] = false;
    $typ_odesl = 'Z';
    $odesl_prijmeni = 'vlastnĂ­ zĂĄznam';
    $vec = TxtEncoding4Soap($GLOBALS["CONFIG_POSTA_CP"]["DRUH_ZADOSTI"][$typ_doc]["NAZEV"]);
    $EedSql = LoadClass('EedSql');

    if ($dokument_id>1) {
      //testneme, jestli to nahodou neni jen file_ID...
      $c = new DB_POSTA;
      $sql = 'select * from posta where id='.$dokument_id;
      $c->query($sql);
      if ($c->Num_Rows() == 0) {
        require_once(FileUp2('.admin/upload_.inc'));
        $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true,'skip_access'=>true));
        $file = $uplobj['table']->getRecordTable($dokument_id);
        $dokument_id = $file['RECORD_ID'] ? $file['RECORD_ID'] : 0;
      }
    }

    $puv = $dokument_id;
    if ($dokument_id<1) {
      $dokument_id = $EedSql->createCJ($zpracovatel);
    } else {
      $dokument_id = $EedSql->createDocWithCJ($dokument_id);
    }

    $text = 'zaloĹženĂ­ autorizovanĂŠ konverze z pĹŻvodnĂ­ho dokumentu (<b>'.$pub.'</b>) ';
    EedTransakce::ZapisLog($puv, TxtEncodingFromSoap($text), 'DOC', $LAST_USER_ID);

    $text = 'u dokumentu (<b>'.$puv.'</b>) '.$ns.' byla provedena autorizovanĂĄ konverze. VĂ˝sledek konverze uloĹžen pod (<b>'.$dokument_id.'</b>)';
    EedTransakce::ZapisLog($dokument_id, TxtEncodingFromSoap($text), 'DOC', $LAST_USER_ID);

    $odeslano = Date('d.m.Y H:i:s');
  }

  $sql="update posta set
    typ_posty=".($GLOBALS["CONFIG_POSTA_CP"]["DRUH_ZADOSTI"][$typ_doc]["TYP_DOC"]?$GLOBALS["CONFIG_POSTA_CP"]["DRUH_ZADOSTI"][$typ_doc]["TYP_DOC"]:0).",
    vec='".$vec."',
    stav=63,
    odes_typ='".$typ_odesl."',
    datum_podatelna_prijeti='".$odeslano."',
    odesl_prijmeni='".$odesl_prijmeni."',
    odesl_jmeno='".$odesl_jmeno."',
    odesl_ico='".$odesl_ico."',
    odesl_odd='".$odesl_oddeleni."',
    odesl_ulice='".$odesl_ulice."',
    odesl_cp='".$odesl_cp."',
    odesl_cor='".$odesl_cor."',
    odesl_posta='".$odesl_posta."',
    odesl_psc='".$odesl_psc."',
  ";

  //pokud mame adresni udaje, tak zrovna udelame vyrizeni dokumentu
  //ale nakonec jsme to vypnuli, a proste to zrovna uzavreme
  //if ($status<>'f')
  $sql.="
    datum_referent_prijeti='".$odeslano."',
    datum_vyrizeni='".$odeslano."',
    vyrizeno='VyĹĂ­zeno pĹes CzechPOINT',
    status=1,
  ";

  If ($GLOBALS["CONFIG_POSTA_CP"]["UZAVRIT_SPIS"])
  $sql.="
    spis_vyrizen='".Date('d.m.Y H:i')."',
  ";

  If ($GLOBALS["CONFIG_POSTA_CP"]["SKARTACE_ID"]>0)
  $sql.="
    skartace=".$GLOBALS["CONFIG_POSTA_CP"]["SKARTACE_ID"].",";

  $LAST_USER_ID=$GLOBALS["CONFIG_POSTA_CP"]["LAST_USER_ID"];
  $LAST_TIME=Date('H:m:i');
  $LAST_DATE=Date('Y-m-d');

  $sql.="
    last_date='".$LAST_DATE."',
    last_time='".$LAST_TIME."',
    last_user_id=".$LAST_USER_ID.",
    stornovano=NULL,
  ";


  $sql.="
  poznamka='".$poznamka."'

  where id=".$dokument_id."
  ";

  //echo $sql;
  /*$fp=fopen('stream.sql','w');
  fwrite($fp,$sql);
  fclose($fp);
  */
  //echo $sql;

  $sql=TxtEncodingFromSoap($sql);

  $q=new DB_POSTA;





  //Die();
  If ($q->query($sql))
  {

    $text = "Zapsany metainformace z CzP";
    EedTransakce::ZapisLog($dokument_id, $text, 'DOC');

    If ($GLOBALS["CONFIG_POSTA_CP"]["UZAVRIT_SPIS"]) {
      require(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedCj.inc');
      $cj_obj = new EedCj($dokument_id);
      $cj_info = $cj_obj->GetCjInfo($dokument_id);
      $ns = $cj_info['CELE_CISLO'];

      $sql="insert into cis_posta_spisy (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID)
      VALUES ('$ns','$ns',$dokument_id,0,'$LAST_DATE','$LAST_TIME',$LAST_USER_ID,$LAST_USER_ID)";
      //Die($sql);
      $q->query($sql);
      $text = 'Byl vytvoĹen spis: <b>' . $ns . '</b>';
      EedTransakce::ZapisLog($dokument_id, TxtEncodingFromSoap($text), 'SPIS', $LAST_USER_ID);

      $text = 'dokument (<b>'.$dokument_id.'</b>) '.$ns.' byl vloĹžen do spisu: <b>' . $ns . '</b>';
      EedTransakce::ZapisLog($dokument_id, TxtEncodingFromSoap($text), 'DOC', $LAST_USER_ID);
      EedTransakce::ZapisLog($dokument_id, TxtEncodingFromSoap($text), 'SPIS', $LAST_USER_ID);

      $text = 'Spis <b>' . $ns . '</b> byl uzavĹen';
      EedTransakce::ZapisLog($dokument_id, TxtEncodingFromSoap($text), 'SPIS', $LAST_USER_ID);

    }



    $text='(PROCESSFORM) - dokument byl odeslan - dokument ('.$dokument_id.')';
    WriteLog($software_id,$text,$session_id);
    if ($GLOBALS["CONFIG"]["UPLOAD"] || $GLOBALS["CONFIG"]["UPLOAD_NAS"] || $GLOBALS["CONFIG"]["TWIST_UPLOAD"])
      include('copy_upload.inc');
  //  if ($GLOBALS["CONFIG"]["UPLOAD_ELO"])
  //    include('copy_elo.inc');


     NastavStatus($dokument_id);

      $return ='
<ProcessXmlDataResponse xmlns="http://www.software602.cz/webservices/602xml"><ProcessXmlDataResult>1</ProcessXmlDataResult><Response>OK</Response></ProcessXmlDataResponse>
';


  return $return;

}
else 
{
  $text = "Nepovedlo se zapsat metainformace z CzP";
  EedTransakce::ZapisLog($dokument_id, $text, 'DOC');

  $text='(PROCESSFORM) - nepodarilo se odeslat dokument ('.$dokument_id.')';
  WriteLog($software_id,$text,$session_id,1);
  $return='
  <ns1:processform_response ret="Exception" code="-1" xmlns:ns1="http://ws.exprit.cz/ws602">
    <ns1:desc>cannot update document</ns1:desc>
  </ns1:processform_response>
';
}
return $return;
}
?>
