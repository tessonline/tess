<?php
// require_once(FileUp2(".admin/oth_funkce.inc"));
// require_once(FileUp2(".admin/brow_.inc"));
// require_once(FileUp2('.admin/upload_.inc'));
require_once(FileUp2(".admin/classes/e_signing/ZfoFile.php"));
require_once(FileUp2(".admin/classes/e_signing/DatovaZprava.php"));

function KonvertJejichSpis($cj1, $spis1 = '', $smer = 1) {
  if ($smer == 2)
  {
    //musime rozdekodovat retezec
    if (strpos($cj1,', SPIS:')) 
    {
      return explode(', SPIS:',$cj1);
    }
    else
      return array($cj1,'');
  }
  else
  {
    //zapiseme k nam
    $res=$cj1;
    if ($spis1) $res.=", SPIS:".$spis1;
    return $res;
  }
}

function GetSouborzDS($id,$schranka)
{
  $zprava=$schranka->MessageDownload($id);
  $soubor=array();$a=0;
  //    while (list($keyz,$valz)=each($zprava[dmDm][dmFiles]))
  if ($zprava[dmDm][dmFiles])
  foreach($zprava[dmDm][dmFiles] as $v1) {
    foreach ($v1 as $k=> $v2) 
    {
      if (is_array($v2)) {
      $a++;
      foreach ($v2 as $k => $v3) {
          if ($k=='dmFileDescr') $soubor[$a][filename]=$v3;
          if ($k=='dmMimeType') $soubor[$a][filetype]=$v3;
          if ($k=='dmFileDescr') $soubor[$a][filedesc]=$v3;
          if ($k=='dmEncodedContent') $soubor[$a][filecont]=base64_encode($v3);
//          if ($k=='dmEncodedContent' && !$v3['!']) $soubor[$a][filecont]=$v3;
//          if ($k=='!' && strlen($soubor[$a][filecont])<1) $soubor[$a][filecont]=$v3;
//          if ($k=='dmEncodedContent' && strlen($v3['!'])>10) $soubor[$a][filecont]=$v3['!'];
      	}
      }
      else
      {
          if ($k=='dmFileDescr') $soubor[$a][filename]=$v2;
          if ($k=='dmMimeType') $soubor[$a][filetype]=$v2;
          if ($k=='dmFileDescr') $soubor[$a][filedesc]=$v2;
          if ($k=='dmEncodedContent') $soubor[$a][filecont]=base64_encode($v2);
      }
    }
    if ($soubor[$a][filecont]=='') print_r($soubor[$a]);
  }
   $a++;
   $zprava_signed=$schranka->SignedMessageDownload($id);
   $soubor[$a][filename]='prichozi_datova_zprava.zfo';
   $soubor[$a][filedesc]=TxtEncoding4Soap('<i>celá příchozí datová zpráva podepsaná MV ČR</i>');
   $soubor[$a][filecont]=base64_encode($zprava_signed['dmSignature']);

   $a++;
   $zprava_signed=$schranka->GetSignedDeliveryInfo($id);
   $soubor[$a][filename]='dorucenka_'.$id.'.zfo';
   $soubor[$a][filedesc]=TxtEncoding4Soap('<i>doručenka k datové zprávě podepsaná MV ČR</i>');
   $soubor[$a][filecont]= $zprava_signed['dmSignature'];

// ONMA Zapnout
//    $zfoFile = new ZfoFile(base64_encode($zprava_signed['dmSignature']));
//    $datovaZprava = new DatovaZprava($zprava, $zfoFile, $schranka);
//    $valid = $datovaZprava->verify();
//    $protocol = $datovaZprava->createProtocolContent('PDF');
//
//    $a++;
//    $soubor[$a][filename] = 'kontrola_podpisu.pdf';
//    $soubor[$a][filedesc] = TxtEncoding4Soap('<i>kontrola elektronickeho podpisu</i>');
//    $soubor[$a][filecont] = base64_encode('aaaa');

  return $soubor;
}

function GetPoleProDS($id,$client,$session_id)
{
  $q=new DB_POSTA;
  $a=new DB_POSTA;
  $sql='select * from posta where id='.$id;
  $q->query($sql);
  $q->Next_Record(); 
//   If ($GLOBALS["CONFIG"]["SHOW_C_JEDNACI"])
//     $cislo_jednaci=strip_tags(FormatCJednaci($q->Record["CISLO_JEDNACI1"],$q->Record["CISLO_JEDNACI2"],$q->Record["REFERENT"],$q->Record["ODBOR"]));
//   else
//     $cislo_jednaci=strip_tags(FormatSpis($q->Record["CISLO_SPISU1"],$q->Record["CISLO_SPISU2"],$q->Record["REFERENT"],$q->Record["ODBOR"],'',$q->Record["PODCISLO_SPISU"]));

  $doc = LoadSingleton('EedCj', $id);
  $cislo_jednaci = $doc->cislo_jednaci;
  $spis_id = $cj_info['SPIS_ID'];

  $ToHands=$q->Record[ODESL_OSOBA];
  $PersonalDelivery=($q->Record[DOPORUCENE]==4)?1:0;
  //koukneme, jestli v teto obalce nejsou dalsi cisla jednaci...
  $sql='select * from posta_hromadnaobalka where obalka_id='.$id;
  $a->query($sql);
  while ($a->Next_Record())
  {
    $cislo_jednaci.=", ".strip_tags(FormatCJednaci($a->Record["DOKUMENT_ID"]));
  }
  $SenderOrgUnit=EedTools::VratOdbor($q->Record[ODBOR]);
  $SenderOrgUnitNum=$q->Record[ODBOR];
  $AllowSubstDelivery=1;
//  $cislo_spisu=strip_tags(FormatSpis($q->Record["CISLO_SPISU1"],$q->Record["CISLO_SPISU2"],$q->Record["REFERENT"],$q->Record["ODBOR"],$q->Record["NAZEV_SPISU"]));
  $doc = LoadClass('EedCj', $id);
  $cislo_jednaci = $doc->cislo_jednaci;
  $cj_info = $doc->GetCjInfo($id);
  $cislo_spisu = $cj_info['CELE_CISLO'];

  $jejichcj=KonvertJejichSpis($q->Record[JEJICH_CJ],'',2);
  $obalka = array(
  	'dmSenderOrgUnit' => TxtEncoding4Soap($SenderOrgUnit),  //nepovinne
  	'dmSenderOrgUnitNum' => $SenderOrgUnitNum,  //nepovinne
  	'dbIDRecipient' => $q->Record[ODESL_DATSCHRANKA], //ID datove schranky!
  	'dmRecipientOrgUnit' => $RecipientOrgUnit,  //nepovinne
  	'dmRecipientOrgUnitNum' => $RecipientOrgUnitNum, //nepovinne
  	'dmToHands' => TxtEncoding4Soap($ToHands), //nepovinne, textove komu je urceno
  	'dmAnnotation' => ($q->Record[VEC]), //vec
  	'dmRecipientRefNumber' => TxtEncoding4Soap($jejichcj[0]), //jejich cj
  	'dmSenderRefNumber' => TxtEncoding4Soap($cislo_jednaci), //nae cj
  	'dmRecipientIdent' => TxtEncoding4Soap($jejichcj[1]),  //jejich spis
  	'dmSenderIdent' => TxtEncoding4Soap($cislo_spisu), //nas spis
  	'dmLegalTitleLaw' => $LegalTitleLaw, //zmocneni zakon
  	'dmLegalTitleYear' => $LegalTitleYear, //zmocneni rok
  	'dmLegalTitleSect' => $LegalTitleSect, //zmocneni paragraf
  	'dmLegalTitlePar' => $LegalTitlePar, //zmocneni odstavec
  	'dmLegalTitlePoint' => $LegalTitlePoint, //zmocneni pismeno 
  	'dmPersonalDelivery' => $PersonalDelivery, //zasilka do vlastnich rukou
  	'dmAllowSubstDelivery' => $AllowSubstDelivery //nahradni doruceni (durceni fikci)
  );
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);
/*
  //obalka je readz, nacteme soubory z uploadu
  $result = $client->call('get_files', array(
      'session_id'=>$session_id,
      'dokument_id'=>$id
      )
    );
*/
//  echo '<pre>' . htmlspecialchars($client->response, ENT_QUOTES) . '</pre>';
//  Die();
   $soubory2=array();
  $kontrola=true;
  while (list($key,$val)=@each($upload_records))
  {
    if (strpos($val[NAME],'.pdf') && $kontrola) {$soubory2[0]=$val; $kontrola=false;}
    else $soubory2[$key+1]=$val; 
  }
  $soubory3=array();
  $kontrola=true;
  while (list($key,$val)=@each($soubory2))
  {
    if (($val[DESCRIPTION]=='main' || $val[DESCRIPTION]=='MAIN') && $kontrola) {$soubory3[0]=$val; $kontrola=false;}
    else $soubory3[$key+1]=$val; 
  }
//  reset($soubory);
//  ksort($soubory3);
//  print_r($soubory3); Die();
  $pocet=0;
  while (list($key,$val)=@each($soubory3))
  {
    $pocet++;
//     $soubor[]=new SoapVal(
//       'dmFile',
//       '',
//       array(
//   	    'dmEncodedContent'=>base64_encode($uplobj['table']->GetUploadFiles($val))
//       ),
//       false,
//       false,
//       array(
//         'dmMimeType'=>$val[TYPEFILE], //mimetype, nevyuziva se
//         'dmFileMetaType'=>($pocet==1)?'main':'enclosure', //druh pisemnosti, prvni musi byt typ main!
//         'dmFileGuid'=>$val[ID], //interni oznaceni dokumentu, nepouziva se v DS
//         'dmUpFileGuid'=>$$val[ID], //interni oznaceni dokumentu, nepouziva se v DS
//         'dmFileDescr'=>TxtEncoding4Soap($val[NAME]), //popis souboru
//         'dmFormat'=>$Format, //nepovinne,
//       )
//     );

    $soubor[] =  array(
      "_" => '',
      'dmMimeType'=>$val[TYPEFILE], //mimetype, nevyuziva se
      'dmFileMetaType'=>($pocet==1)?'main':'enclosure', //druh pisemnosti, prvni musi byt typ main!
      'dmFileGuid'=>$val[ID], //interni oznaceni dokumentu, nepouziva se v DS
      'dmUpFileGuid'=>$val[ID], //interni oznaceni dokumentu, nepouziva se v DS
      'dmFileDescr'=>TxtEncoding4Soap($val[NAME]), //popis souboru
      'dmFormat'=>$Format, //nepovinne,
	    'dmEncodedContent'=>$uplobj['table']->GetUploadFiles($val),

    );


  }

  $MessageCreateInput = array(
  	'dmEnvelope' => $obalka,
  	'dmFiles' => $soubor,
  );

  return $MessageCreateInput;
}


Function UlozDZ($id,$vypis=false,$session_id,$prac_id=0,$multiselect=0, $so = 0)
{
  global $schranka;
  global $client;
  global $q;
  require_once(FileUp2(".admin/nastaveni.inc"));
  global $typDS;

   $dm_id=$id;
  $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  $jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
  $LAST_USER_ID=$id_user;
  $LAST_TIME=Date('H:i:s');
  $LAST_DATE=Date('Y-m-d');
  $LAST_DATE=Date('d.m.Y');

  if ($prac_id>0)
  {
    $pracovnik=OdborPrac($prac_id);
  }
  
  $zprava=$schranka->MessageDownload($id);
  
  //zpravy urcene do vlastnich rukou se nemohou nacitat multiselectem
  if (!($zprava[dmDm][dmPersonalDelivery]=='true' && $multiselect=='true' && $GLOBALS[CONFIG_POSTA][DS][ds_vlastnich_rukou]>0)) 
  {
  //  print_r($zprava);
    $soubor=array();

    foreach($zprava[dmDm][dmFiles] as $v1) {
      foreach ($v1 as $k=> $v2)
      {
        if (is_array($v2)) {
        $a++;
        foreach ($v2 as $k => $v3) {
            if ($k=='dmFileDescr') $soubor[$a][filename]=$v3;
            if ($k=='dmMimeType') $soubor[$a][filetype]=$v3;
            if ($k=='dmFileDescr') $soubor[$a][filedesc]=$v3;
            if ($k=='dmEncodedContent') $soubor[$a][filecont]=base64_encode($v3);
  //          if ($k=='dmEncodedContent' && !$v3['!']) $soubor[$a][filecont]=$v3;
  //          if ($k=='!' && strlen($soubor[$a][filecont])<1) $soubor[$a][filecont]=$v3;
  //          if ($k=='dmEncodedContent' && strlen($v3['!'])>10) $soubor[$a][filecont]=$v3['!'];
        	}
        }
        else
        {
            if ($k=='dmFileDescr') $soubor[$a][filename]=$v2;
            if ($k=='dmMimeType') $soubor[$a][filetype]=$v2;
            if ($k=='dmFileDescr') $soubor[$a][filedesc]=$v2;
            if ($k=='dmEncodedContent') $soubor[$a][filecont]=base64_encode($v2);
        }
      }
      if ($soubor[$a][filecont]=='') print_r($soubor[$a]);
    }
  
    $a++;
    $soubor[$a][filename]='prichozi_datova_zprava.zfo';
    $soubor[$a][filedesc]=TxtEncoding4Soap('<i>celá příchozí datová zpráva podepsaná MV ČR</i>');
    $soubor[$a][filetype]='aplication/pdf';
  
    $a++;
    $zprava_signed=$schranka->GetSignedDeliveryInfo($id);
    $soubor[$a][filename]='dorucenka_'.$id.'.zfo';
    $soubor[$a][filedesc]=TxtEncoding4Soap('<i>doručenka k datové zprávě podepsaná MV ČR</i>');
    $soubor[$a][filecont]=$zprava_signed['dmSignature'];

// ONMA Zapnout
//     $a++;
//     $soubor[$a][filename] = 'kontrola_podpisu.pdf';
//     $soubor[$a][filedesc] = TxtEncoding4Soap('<i>kontrola elektronickeho podpisu</i>');
//     $soubor[$a][filecont] = base64_encode($protocol);

    $EedSql = LoadClass('EedSql');
    $dokument_id = $EedSql->createCJ();

  
    //zjistime si info z datove schranky
    $dmIdSender=$zprava[dmDm][dbIDSender];
//  echo $dmIdSender;
    $datschranka=$schranka->FindDataBox(array('dbID'=>$dmIdSender));
  
    $datschranka=$datschranka[0];
//   print_r($soubor);
  
  //  $ds=$datschranka[dbType];
  //print_r($datschranka);
    $odes_typ=$GLOBALS[TypDS][$datschranka[dbType]];
    //Die($odes_typ);
  
    if ($odes_typ=='U' || $odes_typ=='P')
      $prijmeni=$datschranka[firmName];
    else
      $prijmeni=$datschranka[pnLastName];
    if ($datschranka[dbType]=='OVM_NOTAR' || $datschranka[dbType]=='OVM_EXEKUT') $prijmeni=$datschranka[firmName];
  
    $private=0;
    $lhuta = $GLOBALS['CONFIG']['DATOVE_ZPRAVY_LHUTA'] ? $GLOBALS['CONFIG']['DATOVE_ZPRAVY_LHUTA'] : 7;
//    print_r($zprava);
    if ($zprava[dmDm][dmPersonalDelivery]=='true') {$pozn=' DO VLASTNÍCH RUKOU '; $private=1;}
    if ($GLOBALS['CONFIG']['DATOVE_ZPRAVY_NE_DO_VLASTNICH_RUKOU']) $private = 0;

    if ($zprava[dmDm][dmToHands]<>'') $pozn.=" K rukám: ".str_replace("'",'',TxtEncodingFromSoap($zprava[dmDm][dmToHands]))."";

    if ($so == 0) $so = $GLOBALS["CONFIG"]['DEFAULT_SUPERODBOR'];
   
    $pozn = str_replace(' ','',$pozn);
    if ($vypis)  echo "Zpracovávám dat. zpravu od <b>".TxtEncodingFromSoap($prijmeni)."</b><br/>"; Flush();
    $sql="update posta set ";
    $sql.="vec='".TxtEncoding4Soap(mb_substr(str_replace("'",'',TxtEncodingFromSoap($zprava[dmDm][dmAnnotation])),0,199))."', ";
    $sql.="odes_typ='".$odes_typ."', ";
    $sql.="datum_podatelna_prijeti='".ConvertDatumToString($zprava[dmDeliveryTime])."', ";
  
    $sql.="odesl_prijmeni='".TxtEncoding4Soap(mb_substr(TxtEncodingFromSoap($prijmeni),0,99))."', ";
    $sql.="odesl_datschranka='".$zprava[dmDm][dbIDSender]."', ";
    $sql.="vlastnich_rukou=9, ";
    $sql.="odesl_jmeno='".$datschranka[pnFirstName]." ".$datschranka[pnMiddleName]."', ";
    $sql.="odesl_ulice='".$datschranka[adStreet]."', ";
    $sql.="odesl_cp='".$datschranka[adNumberInStreet]."', ";
    $sql.="odesl_cor='".$datschranka[adNumberInMunicipality]."', ";
    $sql.="odesl_psc='".str_replace(' ','',$datschranka[adZipCode])."', ";
    $sql.="odesl_posta='".$datschranka[adCity]."', ";
    $sql.="jejich_cj='".KonvertJejichSpis($zprava[dmDm][dmSenderRefNumber],$zprava[dmDm][dmSenderIdent],1)."',";
    $sql.="lhuta=".$lhuta.", ";
    $sql.="private=".$private.", ";
    $sql.="zpusob_podani='3', ";
    $sql.="superodbor=$so, ";
    $sql.="druh_priloh='".TxtEncoding4Soap('elektronické')."', ";
    $sql.="pocet_priloh='".count($soubor)."', ";
    $sql.="poznamka='".TxtEncoding4Soap($pozn)."', ";
//     if ($prac_id>0)
//       $sql.="odbor='".$pracovnik['odbor']."',oddeleni='".$pracovnik['oddeleni']."',referent=".$prac_id.",";
  
    $sql.="stav=2 ";
    $sql.="where id=".$dokument_id;
    $sql=TxtEncodingFromSoap($sql);
  //   Die();
    $q->query($sql);
    

    // VYHODNOCENI FILTRU   
        
    // Ziskani filtrů
    // Vyhodnoceni filtru podle priority: filtry s nejvyssi prioritou se provadi na zaver tzn.,
    // ze posledni aplikovany filtr (ma nejvyssi prioritu) prebyje vsechny predchozi
    $sql = 'SELECT * FROM posta_ds_filtry ORDER BY priority ASC';
    $q->query($sql);
    
    while ($q->next_record()) {
      // polozka datove zpravy, ktera je porovnavana
      $compared_item = $q->Record['DM_ITEM'];
      // ... jeji hodnota
      $compared_value = TxtEncodingFromSoap($zprava[dmDm][$compared_item]);
      // hodnoty, ktere se provnavaji s hodnotou polozky datove zpravy
      $filter_values = parseComparedValues($q->Record['DM_ITEM_COMPARED_VALUES'], '|');
      
      foreach ($filter_values as $filter_value) {        
        if (compareValues($compared_value, $filter_value)) {
          updateElectronicDocument($q, $dokument_id,
                                    $q->Record['ED_ITEM_SUPERODBOR'],
                                    $q->Record['ED_ITEM_ODBOR'],
                                    $q->Record['ED_ITEM_REFERENT'],
                                    $q->Record['ED_STAV']);
        }
      }
    }
    
    // KONEC VYHODNOCENI FILTRU

  //  unset($soubor);
    $soubory=array();
    $soubory_pocet=0;
    if (count($soubor)>0)
    {
      while (list($key,$val)=each($soubor))
      {
        $soubory[$soubory_pocet]['FILE_NAME']=$val['filename'];
        $soubory[$soubory_pocet]['FILE_DESC']=$val['filedesc'];
        $soubory[$soubory_pocet]['FILE_DATA']=$val['filecont'];
        $soubory[$soubory_pocet]['BIND_TYPE']=$val['filetype'];
        $soubory_pocet++;
      }
      echo "Ukládám přílohy... <br/>"; Flush();
      $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
    
      $citac=0; $ulozeno=array();
      while (list($key,$val)=each($soubory))
      {
        $citac++;
        $cesta=$GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$id.'/';
        $pripona=substr($val[FILE_NAME],strrpos($val[FILE_NAME],'.'));
        $valz[FILE_NAME]=$dm_id.'-'.$citac;
        $tmp_soubor=$cesta.$valz[FILE_NAME];
        $GLOBALS['DESCRIPTION'] = TxtEncodingFromSoap($val[FILE_DESC]);
        $GLOBALS['TYPEFILE'] = $valz[BIND_TYPE];
        $GLOBALS['LAST_USER_ID'] = $val[LAST_USER_ID];
  
        $fname=$val[FILE_NAME];
        $fname=str_replace("\\","",$fname);
        //pokud nemame nazev souboru, nebo pokud je nulovy, nebo pokud poslali dva soubory se stejnym nazvem
//        echo "Pripona je $pripona, soubor je $fname puvodni je ".$val[FILE_NAME]." x ".strlen(TxtEncodingFromSoap($fname))." ".in_array($fname,$ulozeno)."<br/>";
        if (strlen(TxtEncodingFromSoap($fname))<1 || in_array($fname,$ulozeno))       
        {
          $pripona=substr($fname,strpos($fname,'.'));
          $fname='soubor_'.$dm_id.'-'.$citac.$pripona; $add_text='<br/>&nbsp;zmena nazvu z: '.$valz[filename];
          $GLOBALS['RENAME'] = $fname;
        }
        else
          $GLOBALS['RENAME'] = TxtEncodingFromSoap($val[FILE_NAME]);
        
        $ulozeno[]=$val[FILE_NAME]; //ulozime nazev souboru, obcas poslou soubory s duplicitnim nazvem
        
        if (filesize($tmp_soubor)<1) echo '<font color=red><b>Soubor '.$valz[FILE_NAME].' ma velikost 0 bajtu!!!</b></font><br/>';
        $ret = @$uplobj['table']->SaveFileToAgendaRecord(TxtEncodingFromSoap($tmp_soubor), $dokument_id);
        if ($ret[err_msg]<>'') echo 'Chyba pri ulozeni souboru '.$val["NAME"].': '.$ret[err_msg];
  //        else unlink($tmp_soubor);
      }
    }
  //  Die();
    $nowd = EReg_Replace("[.]0",".", date('d.m.Y H:i'));
    $nowd = EReg_Replace("^0","", $nowd);
    $datum_prijeti=$nowd;
    //$sql="update posta set stav=0,status=7,datum_predani='$datum_prijeti' where id=".$dokument_id;
    $sql="update posta set stav=0,status=7,pocet_listu=0,typ_dokumentu='D',datum_predani='$datum_prijeti' where id=".$dokument_id;
    $q->query($sql);
  //  NastavStatus($dokument_id);
  
    if ($vypis) echo "Ukládám informaci o přečtení... <br/>"; Flush();
    $text = 'dokument (<b>'.$dokument_id.'</b>) byl založen načtením z ISDS, datová zpráva ID '. $dm_id;
	EedTransakce::ZapisLog($dokument_id, $text, 'DOC');
    $sql="insert into posta_DS (posta_id,DS_id,odeslana_posta,datum_odeslani,last_date,last_time,last_user_id) VALUES
    ($dokument_id,$dm_id,'f','".Date('Y-m-d H:i:s')."','".$LAST_DATE."','".$LAST_TIME."',$LAST_USER_ID)";
    //echo $sql."<br/>";
    $q->query($sql);
  //    echo $sql."<br/>";
    NastavStatus($dokument_id);
    $datschranka_nastav=$schranka->MarkMessageAsDownloaded($dm_id);
  
    //echo $sql;
  //  $q->query($sql);
    if ($vypis) echo "Hotovo... <br/>";
    if ($vypis) Flush();
  }  

}

// Vytvori casove razitko k prevodu datove zpravy (dana podle $dm_id), (Dm DataMessage).
// Zavedeno z duvodu, ze nastavaji situace,
// kdy se do EED prevedly v jeden okamzik nektere datove zpravy vicekrat.
function createDmTimestamp($dm_id) {
  $q = new DB_POSTA;
  $sql = "INSERT INTO posta_ds_dm_timestamp (dm_id, timestamp) VALUES ($dm_id, CURRENT_TIMESTAMP)";
  $q->query($sql);
}

// Vymaze casova razitka u datovych zprav, ktera jsou starsi nez zadany pocet sekund ($seconds).
function deleteExpiredDmTimestamps($seconds) {
  $q = new DB_POSTA;
  $sql = "DELETE FROM posta_ds_dm_timestamp
            WHERE timestamp < (current_timestamp - interval '$seconds seconds')";
  $q->query($sql);
}

// Testuje, zda uz byla dana datova zprava ($dm_id) ulozena do EED
// Ve skutecnosti se zjistuje, zda existuje zaznam v tabulce s casovymi razitky.
// Pokud zaznam existuje return TRUE, jinak FALSE.
// dm - DataMessage
function isDmSaved($dm_id) {
  $q = new DB_POSTA;
  $sql = "SELECT * FROM posta_ds_dm_timestamp WHERE dm_id = $dm_id";
  $q->query($sql);
  return $q->num_rows() > 0;
}

function parseComparedValues($compared_values, $separator) {      
  return explode($separator, $compared_values);
}

// Provede zmeny na danem spisu.
function updateElectronicDocument($db, $id, $superodbor, $odbor, $referent) {

  if (!$superodbor) $superodbor = 'NULL';
  if (!$odbor) $odbor = 'NULL';
  if (!$referent) $referent = 'NULL';

  if (!$stav) $stav = 7;

  $set = '';
  $set .= "superodbor = $superodbor, ";
  $set .= "odbor = $odbor, ";
  $set .= "referent = $referent, ";
  $set .= "stav = $stav";

  $sql = "UPDATE posta SET $set WHERE id = $id";

  $db = clone $db;
  $db->query($sql);
}

function compareValues($compared_value, $filter_value) {
  $is_equal = FALSE;

  // test, zda je retezec obalen hvezdickami
  if (preg_match('/^\*.*\*$/', $filter_value)) {
    // odstraneni hvezdicek
    $filter_value = preg_replace('/\*/', '', $filter_value);
    // porovna jestli je soucast retezce (retezec v retezci)
    if (stripos($compared_value, $filter_value) !== FALSE) {
      $is_equal = TRUE;
    }
  }
  else {
    // porovnava cely retezec
    if (strcasecmp($compared_value, $filter_value) == 0) {
      $is_equal = TRUE;
    }
  }

  return $is_equal;
}

