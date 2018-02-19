<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/upload_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/status.inc"));
require_once(FileUp2(".admin/run2_.inc"));
require_once(FileUp2("interface/.admin/soap_funkce.inc"));
require_once(FileUp2(".admin/security_name.inc"));
require_once(FileUp2(".admin/has_access.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2("html_header_full.inc"));

$GLOBALS['USER_INFO'] = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
$GLOBALS['VSE_STEJNE_CJ'] = 1;

if (!$GLOBALS['REFERENT'])
  $GLOBALS['REFERENT'] = $GLOBALS['USER_INFO']['ID'];


$usrObj = LoadClass('EedUser',$GLOBALS['REFERENT']);
$odbor = $usrObj->odbor_id;
$uzelArr = $usrObj->VratSpisUzelZOdboru($odbor);
$GLOBALS['ODBOR'] = $uzelArr['ID'] ? $uzelArr['ID'] : 0;
$GLOBALS['OWNER_ID'] = $GLOBALS['USER_INFO']['ID']; 
$GLOBALS['SUPERODBOR'] = $usrObj->zarizeni_id;

$puv['CISLO_JEDNACI1'] = $GLOBALS['CISLO_JEDNACI1'];
$puv['CISLO_JEDNACI2'] = $GLOBALS['CISLO_JEDNACI2'];


Access(array('agenda' => 'POSTA'));
$show = true;
$spis_zalozen = false;

$prvni_id = -1;
$sqlObj = LoadClass('EedSql');
 
function libxml_display_error($error)
{
    $return = "<br/>\n";
    switch ($error->level) {
        case LIBXML_ERR_WARNING:
            $return .= "<b>Upozornění: $error->code</b>: ";
            break;
        case LIBXML_ERR_ERROR:
            $return .= "<b>Chyba: $error->code</b>: ";
            break;
        case LIBXML_ERR_FATAL:
            $return .= "<b>Fatální chyba: $error->code</b>: ";
            break;
    }
    $return .= trim($error->message);
    if ($error->file) {
        $return .=    " v <b>".basename($error->file)."</b>";
    }
    $return .= " na řádku <b>$error->line</b>\n";

    return $return;
}

function libxml_display_errors() {
    $errors = libxml_get_errors();
    foreach ($errors as $error) {
        print libxml_display_error($error);
    }
    libxml_clear_errors();
}

// Enable user error handling
libxml_use_internal_errors(true);

function readImportXml($xmlFile, $sqlObj,$provest = false) {
  
  $xml = new DOMDocument('1.0', 'UTF-8');
  
  //print_r($_FILES); Die();
  ini_set('memory_limit','4096M');
  if ($GLOBALS['PROPERTIES_DEBUG']['SHOW_SQL']) echo "Nacitam soubor $xmlFile <br/>";
  $a = $xml->load($xmlFile, LIBXML_PARSEHUGE);

  //$xml->load('test2.xml');

  // if (!$xml->schemaValidate(FileUp2('.admin/xsd/schema.xsd'))) {
  //     print '<b>Byly nalezeny chyby XML</b>';
  //     libxml_display_errors();
  // }

  /*
  $je_spis = false;
  $spisy = $xml->getElementsByTagName( "Spis" );
  foreach( $spisy as $spis )
  {
    $je_spis = true;
    $vlozeneDoc = $xml->getElementsByTagName( "VlozenyDokument" );
    foreach( $vlozeneDoc as $VlozenyDoc )
    {
      $dokumenty = $VlozenyDoc->getElementsByTagName( "Dokument" );
      foreach( $dokumenty as $dokument )
      {
        $cjs = $dokument->getElementsByTagName( "CisloJednaci" );
      //  $cj = $cjs->item(0)->nodeValue;

        $cj = $dokument->getElementsByTagName( "CisloJednaci" )->item(0)->nodeValue;

      //  echo "$cj\n";
      }
    }
  }

  */

  $a = 0;
  
  $cj1 = $GLOBALS['CISLO_JEDNACI1'];
  $cj2 = $GLOBALS['CISLO_JEDNACI2'];
  if ($cj2<1) $cj2 = Date('Y');
  if ($cj1<1) $cj1 = 10000;
  //echo "CJ je ".$cj1;
  
  // if ($provest) {
  //   if ($cj1 == 10000) {
  //     $id = $sqlObj->createCJ($GLOBALS['REFERENT']);
  //     $prvni_id = $id;
  // //Die($id);
  //     $doc = LoadClass('EedDokument',$id);
  //     $cj1 = $doc->cj1;
  //     $cj2 = $doc->cj2;
  //     $GLOBALS['SUPERODBOR'] = $doc->zarizeni;
  //   }
  // }
  
  $pocet_celkem = count($dokumenty);
  $pocet = 0;
  $pocet_souboru = 0;
  

  $spisy = $xml->getElementsByTagName("Spis");
  $pocet_spisu = 0;
  foreach($spisy as $singleSpis) {
    $spis[$pocet_spisu]['SPIS_HOD'] = $singleSpis->getElementsByTagName("HodnotaID")->item(0)->nodeValue;
    $spis[$pocet_spisu]['SPIS_ZDR'] = $singleSpis->getElementsByTagName("ZdrojID")->item(0)->nodeValue;
    $spis[$pocet_spisu]['SPIS_NAZEV'] = $singleSpis->getElementsByTagName("Nazev")->item(0)->nodeValue;
    $spis[$pocet_spisu]['SPIS_ZNACKA'] = $singleSpis->getElementsByTagName("SpisovaZnacka")->item(0)->nodeValue;
    $spis[$pocet_spisu]['SPIS_DATUM'] = $singleSpis->getElementsByTagName("DatumCasVytvoreni")->item(0)->nodeValue;
    $spis[$pocet_spisu]['SPIS_SPISZNAK'] = $singleSpis->getElementsByTagName("SpisovyZnak")->item(0)->nodeValue;
    $spis[$pocet_spisu]['SPIS_SKARTZNAK'] = $singleSpis->getElementsByTagName("SkartacniZnak")->item(0)->nodeValue;
    $spis[$pocet_spisu]['SPIS_SKARTLHUTA'] = $singleSpis->getElementsByTagName("SkartacniLhuta")->item(0)->nodeValue;
    $spis[$pocet_spisu]['SPIS_POZNAMKA'] = $singleSpis->getElementsByTagName("Poznamka")->item(0)->nodeValue;
    $pocet_spisu++;
  }
  
  $dokumenty = $xml->getElementsByTagName("Dokument");
  foreach($dokumenty as $doc)
  {
    $soubor_save = array();
    $dokument['VEC'] = $doc->getElementsByTagName("Nazev")->item(0)->nodeValue;
    $dokument['CJ'] = $doc->getElementsByTagName("CisloJednaci")->item(0)->nodeValue;
    $dokument['DATUM_PODATELNA_PRIJETI'] = $doc->getElementsByTagName("DatumCasVytvoreni")->item(0)->nodeValue;
    $dokument['poznamka'] = $doc->getElementsByTagName("Poznamka")->item(0)->nodeValue;
    

    $dokument['poznamka'] = $doc->getElementsByTagName("Poznamka")->item(0)->nodeValue;

    $dokument['poznamka'] = $doc->getElementsByTagName("Poznamka")->item(0)->nodeValue;


    $dopln = $doc->getElementsByTagName("DoplnujiciData")->item(0);
    $dokument['POCET_LISTU'] = $dopln->getElementsByTagName("PocetListu")->item(0)->nodeValue;
    $dokument['POCET_PRILOH'] = $dopln->getElementsByTagName("PocetPriloh")->item(0)->nodeValue;
    $dokument['DRUH_PRILOH'] = $dopln->getElementsByTagName("DruhPriloh")->item(0)->nodeValue;
    $dokument['ODES_TYP'] = $dopln->getElementsByTagName("OdesTyp")->item(0)->nodeValue;
    $dokument['DATUM_PREDANI'] = $dopln->getElementsByTagName("DatumPredani")->item(0)->nodeValue;
    $dokument['DATUM_PREDANI_VEN'] = $dopln->getElementsByTagName("DatumPredaniVen")->item(0)->nodeValue;
    $dokument['TYP_POSTY'] = $dopln->getElementsByTagName("TypDoc")->item(0)->nodeValue;
    $dokument['WHOIS_NUMBER'] = $dopln->getElementsByTagName("WhoisNumber")->item(0)->nodeValue;
    $dokument['WHOIS_IDSTUDIA'] = $dopln->getElementsByTagName("WhoisIdstudia")->item(0)->nodeValue;
    $dokument['SKARTACE'] = $dopln->getElementsByTagName("SkartaceID")->item(0)->nodeValue;
    $dokument['TYP_DOKUMENTU'] = $dopln->getElementsByTagName("TypDok")->item(0)->nodeValue;

    $dokument['ODESL_EMAIL'] = $dopln->getElementsByTagName("OdeslEmail")->item(0)->nodeValue;
    $dokument['ODESL_SUBJ'] = $dopln->getElementsByTagName("OdeslSubj")->item(0)->nodeValue;
    $dokument['ODESL_BODY'] = base64_decode($dopln->getElementsByTagName("OdeslBody")->item(0)->nodeValue);

    $dokument['VYRIZENO'] = $dopln->getElementsByTagName("Vyrizeno")->item(0)->nodeValue;
    $dokument['DATUM_VYRIZENI'] = $dopln->getElementsByTagName("DatumVyrizeni")->item(0)->nodeValue;


    $spisZnak = $doc->getElementsByTagName("SpisovyZnak")->item(0)->nodeValue;
    if(strlen($spisZnak)>0 && !$dokument['SKARTACE']){
      $sql = "select id from cis_posta_skartace where kod like '%".$spisZnak."%' and aktivni=1";
      $q = new DB_POSTA;
      $q->query($sql);
      $q->next_record();
      $dokument["SKARTACE"] = ($q->Record["ID"]);
    }

    if ($doc->getElementsByTagName("Doruceni")->item(0)) {
      $dokument['ODESLANA_POSTA'] = 'f';
      $subjekt = $doc->getElementsByTagName("Doruceni")->item(0)->getElementsByTagName("Odesilatel")->item(0)->getElementsByTagName("Subjekt")->item(0);   
      $adresa = $doc->getElementsByTagName("Doruceni")->item(0)->getElementsByTagName("Odesilatel")->item(0)->getElementsByTagName("Adresa")->item(0);
  
      $dokument['ODESL_TYP_JEJICH'] = $subjekt->getElementsByTagName("TypSubjektu")->item(0)->nodeValue;
      if ($dokument['ODESL_TYP_JEJICH'] == 'Fyzicka') {
        $dokument['ODESL_PRIJMENI'] = $subjekt->getElementsByTagName("Prijmeni")->item(0)->nodeValue;
        $dokument['ODES_TYP'] = 'O';
      }
      elseif ($dokument['ODESL_TYP_JEJICH'] == 'Neurceno') {
        $dokument['ODES_TYP'] = 'Z';
      } else {
        $dokument['ODESL_PRIJMENI'] = $subjekt->getElementsByTagName("ObchodniNazev")->item(0)->nodeValue;
        $dokument['ODES_TYP'] = 'P';
      }  

      if ($doc->getElementsByTagName("OdesTyp")->item(0)->nodeValue) $dokument['ODES_TYP'] = $doc->getElementsByTagName("OdesTyp")->item(0)->nodeValue;
      if ($dokument['ODES_TYP'] == 'S') {
        $dokument['ODESL_PRIJMENI'] = $subjekt->getElementsByTagName("ObchodniNazev")->item(0)->nodeValue;
      }

      $dokument['ODESL_JMENO'] = $subjekt->getElementsByTagName("Jmeno")->item(0)->nodeValue;
      $dokument['ODESL_TITUL'] = $subjekt->getElementsByTagName("TitulPred")->item(0)->nodeValue;
      $dokument['ODESL_DATNAR'] = $subjekt->getElementsByTagName("DatumNarozeni")->item(0)->nodeValue;
    
      $dokument['ODESL_ULICE'] = $adresa->getElementsByTagName("Ulice")->item(0)->nodeValue;
      $dokument['ODESL_CP'] = $adresa->getElementsByTagName("PopisneCislo")->item(0)->nodeValue;
      $dokument['ODESL_COR'] = $adresa->getElementsByTagName("OrientacniCislo")->item(0)->nodeValue;
      $dokument['ODESL_PSC'] = str_replace(' ','',$adresa->getElementsByTagName("Psc")->item(0)->nodeValue);
      $dokument['ODESL_POSTA'] = $adresa->getElementsByTagName("Obec")->item(0)->nodeValue;
      $dokument['ODESL_DS'] = $adresa->getElementsByTagName("IdDb")->item(0)->nodeValue;
    


      if ($doc->getElementsByTagName("ZasilkaInfo")) {
        $zasilka = $doc->getElementsByTagName("ZasilkaInfo")->item(0);
        if ($doc->getElementsByTagName('Soubory')) {
          foreach($doc->getElementsByTagName('Soubory') as $soubor) {
            $dmFiles = $soubor->getElementsByTagName("dmFile");
            foreach($dmFiles as $dmFile) {
              $soubor_save[$pocet_souboru]['FILE_NAME'] = $dmFile->getAttribute('dmFileDescr');
              $soubor_save[$pocet_souboru]['FILE_TYPE'] = $dmFile->getAttribute('dmMimeType');
              $soubor_save[$pocet_souboru]['DESCRIPTION'] = $dmFile->getAttribute('dmFileMetaType');
              $soubor_save[$pocet_souboru]['CONTENT'] = base64_decode($dmFile->getElementsByTagName("dmEncodedContent")->item(0)->nodeValue);
              $soubor_save[$pocet_souboru]['VAZBA'] = $pocet;
              $pocet_souboru ++;
            }             
          }
        }
        $manipulaceId = $zasilka->getElementsByTagName("ZpusobManipulaceId")->item(0)->nodeValue;
        $dokument['DOPORUCENE'] = $GLOBALS["KONEKTOR"]["ISRZP"]["DRUH_ODESLANI"][$manipulaceId];
        $druhZasilkyId = $zasilka->getElementsByTagName("DruhZasilkyId")->item(0)->nodeValue;
        $dokument['VLASTNICH_RUKOU'] = $GLOBALS["KONEKTOR"]["ISRZP"]["TYP_ODESLANI"][$druhZasilkyId]['DOPORUCENE'];
        $dokument['OBALKA_NEVRACET'] = $GLOBALS["KONEKTOR"]["ISRZP"]["DRUH_ODESLANI"][$druhZasilkyId]['OBALKA_NEVRACET'];
        $dokument['OBALKA_JEN10DNI'] = $GLOBALS["KONEKTOR"]["ISRZP"]["DRUH_ODESLANI"][$druhZasilkyId]['OBALKA_JEN10DNI'];
        $dokument['DATUM_VYPRAVENI'] = $zasilka->getElementsByTagName("DatumVypraveni")->item(0)->nodeValue; 
        $dokument['DATUM_DORUCENI'] = $zasilka->getElementsByTagName("DatumDoruceni")->item(0)->nodeValue;
  //      $dokument['ODESL_DS'] = $zasilka->getElementsByTagName("IdDb")->item(0)->nodeValue;
    
      }
  
      //if ($pocet<=$pocet_celkem)
//       {
        
        if ($provest && $GLOBALS['VSE_NOVE_CJ'] == 1) {
          $id = $sqlObj->createCJ($GLOBALS['REFERENT']);
          $docObj = LoadClass('EedDokument',$id);
          $cj1 = $docObj->cj1;
          $cj2 = $docObj->cj2;
          $GLOBALS['SUPERODBOR'] = $docObj->zarizeni ? $docObj->zarizeni : 0;

        } elseif (($provest && $GLOBALS['VSE_STEJNE_CJ']==1)) {
          if ($prvni_id<0 || $prvni_id == '') {
            $id = $sqlObj->createCJ($GLOBALS['REFERENT']);
          }
          else {
            $id = $sqlObj->createDocWithCJ($prvni_id);
          }
          $docObj = LoadClass('EedDokument',$id);
          
          $cj1 = $docObj->cj1;
          $cj2 = $docObj->cj2;
          $GLOBALS['SUPERODBOR'] = $docObj->zarizeni ? $docObj->zarizeni : 0;
          $prvni_id = $id;
        	$text = 'dokument (<b>'.$id.'</b>) byl založen importem (ze souboru <b>'.basename($xmlFile).'</b>)';
        	EedTransakce::ZapisLog($id, $text, 'DOC');
        } else {
          $cj1++;
        }

        if ($spis[0]['SPIS_NAZEV'] && $id>0 && !$spis_zalozen) {
          $GLOBALS['SPIS_ID'] = $id;
          $spis_zalozen = true;
          $GLOBALS['DALSI_SPIS_ID'] = 0;
          $GLOBALS['NAZEV_SPISU'] = $spis[0]['SPIS_NAZEV'];
//           $GLOBALS['CISLO_SPISU1'] = $cj1;
//           $GLOBALS['CISLO_SPISU2'] = $cj2;
//           $GLOBALS['CISLO_JEDNACI1'] = $cj1;
//           $GLOBALS['CISLO_JEDNACI2'] = $cj2;
          $GLOBALS['PUVODNI_SPIS'] = $GLOBALS['NOVY_SPIS'] = $GLOBALS["CONFIG"]["PREFIX"].$docObj->cislo_jednaci;
          unset($GLOBALS['EDIT_ID']);
          chdir(getAgendaPath('POSTA_PRIDANI_SPISU',0,0));
          if ($GLOBALS['PROPERTIES_DEBUG']['SHOW_SQL']) echo "Volam 1. run pro POSTA_PRIDANI_SPISU <br/>";
          run_(
          		array(
          				'agenda' => 'POSTA_PRIDANI_SPISU',
          				'outputtype' => 1,
                  'noaccessrefresh' => true,
                  'noaccesscondition' => true,
                  'no_unsetvars' =>true,
          		)
          	);
        	$text = 'byl založen spis <b>' . $GLOBALS['NAZEV_SPISU'] . '</b> importem (ze souboru <b>'.basename($xmlFile).'</b>)';
        	EedTransakce::ZapisLog($id, $text, 'SPIS');
        	$text = 'dokument (<b>' . $id . '</b>) byl vložen do spisu <b>' . $GLOBALS['NAZEV_SPISU'].'</b>';
        	EedTransakce::ZapisLog($id, $text, 'DOC');

        }

//       }
      
        
      $dokument['ID'] = $id ? $id : -1;
      $dokument['CISLO_JEDNACI1'] = $cj1;
      $dokument['CISLO_JEDNACI2'] = $cj2;
      $dokument['CISLO_SPISU1'] = $cj1;
      $dokument['CISLO_SPISU2'] = $cj2;
      $dokument['REFERENT'] = $GLOBALS['REFERENT'];
      $dokument['ODBOR'] = $GLOBALS['ODBOR'];
      $dokument['OWNER_ID'] = $GLOBALS['OWNER_ID'];
      $dokument['SUPERODBOR'] = $GLOBALS['SUPERODBOR'] ? $GLOBALS['SUPERODBOR'] : 0;
  
      foreach($dokument as $key =>$val ) {
        $dokument_array[$a][$key]=TxtEncodingFromSoap($val);
      }
      $a ++;
  
    }
  
    if ($doc->getElementsByTagName("Vypraveni")->item(0))
    {
      $pocet ++;
      $dokument['ODESLANA_POSTA'] = 't';    
      $subjekt = $doc->getElementsByTagName("Vypraveni")->item(0)->getElementsByTagName("Adresat")->item(0)->getElementsByTagName("Subjekt")->item(0);   
      $adresa = $doc->getElementsByTagName("Vypraveni")->item(0)->getElementsByTagName("Adresat")->item(0)->getElementsByTagName("Adresa")->item(0);
  
    
      $dokument['ODESL_TYP_JEJICH'] = $subjekt->getElementsByTagName("TypSubjektu")->item(0)->nodeValue;
      if ($dokument['ODESL_TYP_JEJICH'] == 'Fyzicka') {
        $dokument['ODESL_PRIJMENI'] = $subjekt->getElementsByTagName("Prijmeni")->item(0)->nodeValue;
        $dokument['ODES_TYP'] = 'O';
      }
      elseif ($dokument['ODESL_TYP_JEJICH'] == 'Neurceno') {
        $dokument['ODES_TYP'] = 'Z';
      } else {
        $dokument['ODESL_PRIJMENI'] = $subjekt->getElementsByTagName("ObchodniNazev")->item(0)->nodeValue;
        $dokument['ODES_TYP'] = 'P';
      }  
      if ($doc->getElementsByTagName("OdesTyp")->item(0)->nodeValue) $dokument['ODES_TYP'] = $doc->getElementsByTagName("OdesTyp")->item(0)->nodeValue;
      $dokument['ODESL_JMENO'] = $subjekt->getElementsByTagName("Jmeno")->item(0)->nodeValue;
      $dokument['ODESL_TITUL'] = $subjekt->getElementsByTagName("TitulPred")->item(0)->nodeValue;
      $dokument['ODESL_DATNAR'] = $subjekt->getElementsByTagName("DatumNarozeni")->item(0)->nodeValue;
    
      $dokument['ODESL_ULICE'] = $adresa->getElementsByTagName("Ulice")->item(0)->nodeValue;
      $dokument['ODESL_CP'] = $adresa->getElementsByTagName("PopisneCislo")->item(0)->nodeValue;
      $dokument['ODESL_COR'] = $adresa->getElementsByTagName("OrientacniCislo")->item(0)->nodeValue;
      $dokument['ODESL_PSC'] = str_replace(' ','',$adresa->getElementsByTagName("Psc")->item(0)->nodeValue);
      $dokument['ODESL_POSTA'] = $adresa->getElementsByTagName("Obec")->item(0)->nodeValue;
      $dokument['ODESL_DS'] = $adresa->getElementsByTagName("IdDb")->item(0)->nodeValue;
    
      $dokument['ID'] = $id ? $id : -1;
      $dokument['CISLO_JEDNACI1'] = $cj1;
      $dokument['CISLO_JEDNACI2'] = $cj2;
      $dokument['CISLO_SPISU1'] = $cj1;
      $dokument['CISLO_SPISU2'] = $cj2;
      $dokument['REFERENT'] = $GLOBALS['REFERENT'];
      $dokument['ODBOR'] = $GLOBALS['ODBOR'];
      $dokument['OWNER_ID'] = $GLOBALS['OWNER_ID'];
      $dokument['SUPERODBOR'] = $GLOBALS['SUPERODBOR'] ? $GLOBALS['SUPERODBOR'] : 0;
    
      if ($doc->getElementsByTagName("ZasilkaInfo")) {
        $zasilka = $doc->getElementsByTagName("ZasilkaInfo")->item(0);
        if ($zasilka->getElementsByTagName('Soubory')) {
          foreach($zasilka->getElementsByTagName('Soubory') as $soubor) {
            $dmFiles = $soubor->getElementsByTagName("dmFile");
            foreach($dmFiles as $dmFile) {
              $soubor_save[$pocet_souboru]['FILE_NAME'] = $dmFile->getAttribute('dmFileDescr');
              $soubor_save[$pocet_souboru]['FILE_TYPE'] = $dmFile->getAttribute('dmMimeType');
              $soubor_save[$pocet_souboru]['DESCRIPTION'] = $dmFile->getAttribute('dmFileMetaType');
              $soubor_save[$pocet_souboru]['CONTENT'] = base64_decode($dmFile->getElementsByTagName("dmEncodedContent")->item(0)->nodeValue);
              $soubor_save[$pocet_souboru]['VAZBA'] = $pocet;
              $pocet_souboru ++;
            }             
          }
        }
        $manipulaceId = $zasilka->getElementsByTagName("ZpusobManipulaceId")->item(0)->nodeValue;
        $dokument['DOPORUCENE'] = $GLOBALS["KONEKTOR"]["ISRZP"]["DRUH_ODESLANI"][$manipulaceId];
        $druhZasilkyId = $zasilka->getElementsByTagName("DruhZasilkyId")->item(0)->nodeValue;
        $dokument['VLASTNICH_RUKOU'] = $GLOBALS["KONEKTOR"]["ISRZP"]["TYP_ODESLANI"][$druhZasilkyId]['DOPORUCENE'];
        $dokument['OBALKA_NEVRACET'] = $GLOBALS["KONEKTOR"]["ISRZP"]["DRUH_ODESLANI"][$druhZasilkyId]['OBALKA_NEVRACET'];
        $dokument['OBALKA_JEN10DNI'] = $GLOBALS["KONEKTOR"]["ISRZP"]["DRUH_ODESLANI"][$druhZasilkyId]['OBALKA_JEN10DNI'];
        $dokument['DATUM_VYPRAVENI'] = $zasilka->getElementsByTagName("DatumVypraveni")->item(0)->nodeValue; 
        $dokument['DATUM_DORUCENI'] = $zasilka->getElementsByTagName("DatumDoruceni")->item(0)->nodeValue;
  //      $dokument['ODESL_DS'] = $zasilka->getElementsByTagName("IdDb")->item(0)->nodeValue;
    
      }
      if ($doc->getElementsByTagName('Soubory')) {
        foreach($doc->getElementsByTagName('Soubory') as $soubor) {
          $dmFiles = $soubor->getElementsByTagName("dmFile");
          foreach($dmFiles as $dmFile) {
            $soubor_save[$pocet_souboru]['FILE_NAME'] = $dmFile->getAttribute('dmFileDescr');
            $soubor_save[$pocet_souboru]['FILE_TYPE'] = $dmFile->getAttribute('dmMimeType');
            $soubor_save[$pocet_souboru]['DESCRIPTION'] = $dmFile->getAttribute('dmFileMetaType');
            $soubor_save[$pocet_souboru]['CONTENT'] = base64_decode($dmFile->getElementsByTagName("dmEncodedContent")->item(0)->nodeValue);
            $soubor_save[$pocet_souboru]['VAZBA'] = $pocet;
            $pocet_souboru ++;
          }             
        }
      }
    
      //if ($pocet<=$pocet_celkem)
      {
        if ($provest && $GLOBALS['VSE_NOVE_CJ'] == 1) {
          $id = $sqlObj->createCJ($GLOBALS['REFERENT']);
          $docObj = LoadClass('EedDokument',$id);
          $cj1 = $docObj->cj1;
          $cj2 = $docObj->cj2;
          $GLOBALS['SUPERODBOR'] = $docObj->zarizeni ? $docObj->zarizeni : 0;
        } elseif (($provest && $GLOBALS['VSE_STEJNE_CJ']==1)) {
          if ($prvni_id<0 || $prvni_id == '') {
            $id = $sqlObj->createCJ($GLOBALS['REFERENT']);
          }
          else {
            $id = $sqlObj->createDocWithCJ($prvni_id);
          }
          $docObj = LoadClass('EedDokument',$id);
          $cj1 = $docObj->cj1;
          $cj2 = $docObj->cj2;
          $GLOBALS['SUPERODBOR'] = $docObj->zarizeni ? $docObj->zarizeni : 0;
          $prvni_id = $id;
        	$text = 'dokument (<b>'.$id.'</b>) byl založen importem (ze souboru <b>'.basename($xmlFile).'</b>)';
        	EedTransakce::ZapisLog($id, $text, 'DOC');
        } else {
          $cj1++;
        }
        if ($spis[0]['SPIS_NAZEV'] && $id>0 && !$spis_zalozen) {
          $GLOBALS['SPIS_ID'] = $id;
          $spis_zalozen = true;
          $GLOBALS['DALSI_SPIS_ID'] = 0;
          $GLOBALS['NAZEV_SPISU'] = $spis[0]['SPIS_NAZEV'];
          $GLOBALS['PUVODNI_SPIS'] = $GLOBALS['NOVY_SPIS'] = $docObj->cislo_jednaci;
          unset($GLOBALS['EDIT_ID']);
          chdir(getAgendaPath('POSTA_PRIDANI_SPISU',0,0));
          if ($GLOBALS['PROPERTIES_DEBUG']['SHOW_SQL']) echo "Volam 2. run pro POSTA_PRIDANI_SPISU <br/>";
          run_(
          		array(
          				'agenda' => 'POSTA_PRIDANI_SPISU',
          				'outputtype' => 1,
                  'noaccessrefresh' => true,
                  'noaccesscondition' => true,
          		    'no_unsetvars' =>true,
          		)
          	);
        	$text = 'byl založen spis <b>' . $GLOBALS['NAZEV_SPISU'] . '</b> importem (ze souboru <b>'.basename($xmlFile).'</b>)';
        	EedTransakce::ZapisLog($id, $text, 'SPIS');
        	$text = 'dokument (<b>' . $id . '</b>) byl vložen do spisu <b>' . $GLOBALS['NAZEV_SPISU'].'</b>';
        	EedTransakce::ZapisLog($id, $text, 'DOC');
        }
      }
      
      $dokument['ID'] = $id ? $id : -1;
      $dokument['CISLO_JEDNACI1'] = $cj1;
      $dokument['CISLO_JEDNACI2'] = $cj2;
      $dokument['CISLO_SPISU1'] = $cj1;
      $dokument['CISLO_SPISU2'] = $cj2;
      $dokument['REFERENT'] = $GLOBALS['REFERENT'];
      $dokument['ODBOR'] = $GLOBALS['ODBOR'];
      $dokument['OWNER_ID'] = $GLOBALS['OWNER_ID'];
      $dokument['SUPERODBOR'] = $GLOBALS['SUPERODBOR'] ? $GLOBALS['SUPERODBOR'] : 0;

      foreach($dokument as $key =>$val ) {
        $dokument_array[$a][$key]=TxtEncodingFromSoap($val);
      }
      $a++;
    }
     if ($provest == 1) {
        unset($upload);
   	    $upload = Upload(array('create_only_objects' => true, 'agenda' => 'POSTA', 'noshowheader' => true));
     	  $GLOBALS['EDIT_ID'] = $id;

     	  foreach($dokument as $key =>$val )
     	  	$GLOBALS[$key] = $dokument[$key];
  	  //ulozime

        chdir(getAgendaPath('POSTA',0,0));
        require(FileUp2('posta/.admin/properties.inc'));
        require(FileUp2('posta/.admin/access.inc'));
        //Access(array('agenda' => 'POSTA'));
        UNSET($GLOBALS['RECORD_ID']);
        if ($GLOBALS['PROPERTIES_DEBUG']['SHOW_SQL']) echo "Volam run pro POSTA <br/>";
     	  Run_(array(
           //'agenda'=>'POSTA',
           'noaccessrefresh' => true,
           //'noaccesscondition' => true,
           'outputtype'=>1));
        if ($GLOBALS['PROPERTIES_DEBUG']['SHOW_SQL']) echo "Run pro POSTA je hotov<br/>";
     	  NastavStatus($id, $GLOBALS['REFERENT']);
    	  $slozkaTmp = $GLOBALS['CONFIG_POSTA']['HLAVNI']['tmp_adresar'].'ePodatelnaImport';
    	  if(!file_exists($slozkaTmp)) {
    	    mkdir($slozkaTmp, 0777);
   	    }
    	  $slozkaTmp = $GLOBALS['CONFIG_POSTA']['HLAVNI']['tmp_adresar'].''.$id.'/';
    	  if(!file_exists($slozkaTmp)) {
    	    mkdir($slozkaTmp, 0777);
   	    }
//         echo "onma, id je $id <br/>";
        $zaloha_id = $GLOBALS["EDIT_ID"];
        unset($GLOBALS["EDIT_ID"]);
        if($soubor_save) {
      	  foreach($soubor_save as $singleSoubor) {
      	    $souborTmp = $slozkaTmp."".$singleSoubor['FILE_NAME'];
            $handle = fopen($souborTmp, 'w');
            fwrite($handle, $singleSoubor['CONTENT']);
            $singleSoubor['MD5'] = md5($singleSoubor['CONTENT']);
            fclose($handle);
            $singleSoubor['SIZE'] = filesize($souborTmp);
            $GLOBALS['RENAME'] = $singleSoubor['FILE_NAME'];
            $upload['table']->saveFileToAgendaRecord($souborTmp, $id);
            $text = 'K dokumentu (<b>'.$id.'</b>) byl vložen soubor <b>' . $singleSoubor['FILE_NAME'] . '</b>, velikost: '.$singleSoubor['SIZE'].' bytes, MD5 ' . $singleSoubor['MD5'];
            EedTransakce::ZapisLog($id, $text, 'DOC');
           // unlink($souborTmp);
      	  }
        }
    	  $GLOBALS["EDIT_ID"] = $zaloha_id;
      }
  } 

  // die(print_r($dokument_array));
  include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
  $db_arr = new DB_Sql_Array;
  $db_arr->Data=$dokument_array;

  
  // error_reporting (E_ALL);
  UNSET($GLOBALS["ukaz_ovladaci_prvky"]);
  echo "<h2>Soubor ".basename($xmlFile).":</h2>";
  $count = Table(
    array(
      "db_connector" => &$db_arr,
      "schema_file" => FileUp2("posta/plugins/epodatelna/.admin/table_schema_import.inc"),
      "showaccess" => true,
      "caption" => "Načtené údaje",
      "showedit"=>false,
      "showdelete"=>false,
      "setvars" => true,
      "showinfo"=>false,
      "showcount"=>false,
  //    "schema_file"=>".admin/table_schema_certifikat.inc"
    )
  );
  return $count;
}

//$tmpDir = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'posta'.DIRECTORY_SEPARATOR.'importXml'.DIRECTORY_SEPARATOR;
$tmpDir = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'ePodatelnaImport/';
if(!file_exists($tmpDir)) {
  mkdir($tmpDir, 0777);
}
if (!$provest) {
  $handle = opendir($tmpDir);
  while (false !== ($entry = readdir($handle))) {
    if($entry!='.' && $entry!='..' && strpos($entry, '.zip')===FALSE ) {
        unlink($tmpDir.$entry);
    }
  }
  closedir($handle);
  $filesToImport = '';
  if (!file_exists($tmpDir)) {
    mkdir($tmpDir, 0777, true);
  }
  $file = $tmpDir.$_FILES["UPLOAD_FILE"]["name"];
  if (strpos($_FILES['UPLOAD_FILE']['name'], '.zip')!==FALSE) { 
    if (!move_uploaded_file($_FILES["UPLOAD_FILE"]["tmp_name"],$file))
    {
      echo "Something is wrong with the file";
      exit;
    }
    $zipArchive = new ZipArchive();
    if($zipArchive->open($file) === TRUE) {
      $zipArchive->extractTo($tmpDir);
      $zipArchive->close();
    }
    unlink($file);
    $handle = opendir($tmpDir);
    while (false !== ($entry = readdir($handle))) {
      if ($entry!='.' && $entry!='..') {
        $count = readImportXml($tmpDir.$entry, $sqlObj);
        if ($count>0) {
          if ($filesToImport != '') {
            $filesToImport.=',';
          }
          $filesToImport.=$entry;
        }
        else {
          //unlink($tmpDir.$entry);
        }
      }
    }
    closedir($handle);
  }
  elseif ($_FILES['UPLOAD_FILE'][type] == 'text/xml') {
    if(!move_uploaded_file($_FILES["UPLOAD_FILE"]["tmp_name"],$file))
    {
      echo "Something is wrong with the file";
      exit;
    }
    readImportXml($file, $sqlObj);
    $filesToImport = $_FILES["UPLOAD_FILE"]["name"];
  }
  else {
    echo "Soubor neni XML nebo ZIP type";
    Die();
  }
  

  //  $file = $_FILES['UPLOAD_FILE']['tmp_name'];

} else {
  if(strpos($file_import, ',')) {
    $filesToImport = explode(',',$file_import);
  }
  else {
    $filesToImport[] = $file_import;
  }
  foreach($filesToImport as $singleFile) {
    $proved_provest = $provest;
    readImportXml($tmpDir.$singleFile, $sqlObj, 1);
    $provest = $proved_provest;
    unlink($tmpDir.$singleFile);
  }
}
if ($show && $provest <> 1) {
  echo '
<form method="GET" action="#">
<input type="hidden" name="file_import" value="' . $filesToImport . '">
<input type="hidden" name="provest" value="1">
<input type="hidden" name="REFERENT" value="' . $GLOBALS['REFERENT']. '">
<input type="hidden" name="CISLO_JEDNACI1" value="' . $puv['CISLO_JEDNACI1']. '">
<input type="hidden" name="CISLO_JEDNACI2" value="' . $puv['CISLO_JEDNACI2']. '">
<input type="hidden" name="VSE_NOVE_CJ" value="' . $GLOBALS['VSE_NOVE_CJ']. '">
<input type="hidden" name="VSE_STEJNE_CJ" value="' . $GLOBALS['VSE_STEJNE_CJ']. '">
<input type="submit" class="btn" value="  Skutečně importovat   ">
</form>

';
}
if ($show && $provest == 1) {
echo '
	<input type="button" class="btn" value="  Zavřít   " onclick="window.close()">
	';
}
//print_r($xml->Dokumenty);
require_once(FileUp2("html_footer.inc"));

