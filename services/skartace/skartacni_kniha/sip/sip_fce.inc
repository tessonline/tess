<?php

function getFiles(&$filesXML, $doc_id) {

  $soubory = LoadClass('EedUpload', $doc_id);
  $pocet = count($soubory);
  $res = array();
  if ($pocet>0) {
    foreach($soubory->uplobj_records as $soubor) {
      $grp = $filesXML->addChild('fileGrp');
      $file = $grp->addChild('file');
      $res[] = 'file_' . $soubor['ID'];

      $obsah = $soubory->getContent($soubor);

      $file->addAttribute('ID', 'file_' . $soubor['ID']);
 //     $file->addAttribute('DMDID', 'file_' . $soubor['ID']);
//      $file->addAttribute('CREATED', 'ESS_'. $data['ID']);
      $file->addAttribute('MIMETYPE', $soubor['TYPEFILE']);
      $file->addAttribute('SIZE', strlen($obsah));

      $file->addAttribute('CHECKSUM', md5($obsah));
      $file->addAttribute('CHECKSUMTYPE', 'MD5');
      $file->addAttribute('CREATED', $soubor['LAST_DATE'].'T'.$soubor['LAST_TIME']);
      $fContent = $file->addChild('FContent');
      $fContent->addChild('binData', base64_encode($obsah));
    }
//      <mets:file ID="file_001" CREATED="2009-10-11T12:36:00+01:00" MIMETYPE="application/msword" SIZE="19968" CHECKSUM="d30a3acb719f213932dca4bce76b73c5" CHECKSUMTYPE="MD5" OWNERID="FFRT54545N112">
//        <mets:FContent>

  }
  return $res;
}

function getDataSpisovna($doc_id, $rec_counter = 0) {
  $qx = new DB_POSTA;
  $sql = 'select * from posta_spisovna where dokument_id='.$doc_id;
  $qx->query($sql);
  $qx->Next_Record();
  if ($qx->Record['ID'] == '') {
    //zjistime ID spisu
    $cj_obj = LoadClass('EedCj', $doc_id);
    $cj_info = $cj_obj->GetCjInfo($doc_id);
    $data = ($rec_counter==1) ? "Chyba: data ve spisovně nebyla nalezena" : getDataSpisovna($cj_info['SPIS_ID'],$rec_counter);
    $rec_counter++;
  }
  else {
    $data = $qx->Record;
  }
  return $data;
}

function getDataSkartace($doc_id) {
  $qx = new DB_POSTA;
  $sql = 'select * from posta_skartace where id in (select skartace_id from posta_skartace_id where spisovna_id in (select id from posta_spisovna where dokument_id='.$doc_id.'))';
  $qx->query($sql);
  $qx->Next_Record();
  $spis_id = $qx->Record['SPIS_ID'] ? $qx->Record['SPIS_ID'] : 0;
  $datum = $qx->Record['DATUM_ZAHAJENI'];
  $sql = 'select * from posta where id=' . $spis_id;
  $qx->query($sql);
  $qx->Next_Record();
  $referent = $qx->Record['REFERENT'];
  return array('datum' => $datum, 'referent' => $referent);
}

function SIPVyrizeno($doc_id) {
  $qx = new DB_POSTA;
  $sql = 'select * from posta where id='.$doc_id;
  $qx->query($sql);
  $qx->Next_Record();
  $vyrizeno = $qx->Record['SPIS_VYRIZEN'];
  if (!$vyrizeno) $vyrizeno = $qx->Record['DATUM_VYRIZENI'];
  if (!$vyrizeno) $vyrizeno = $qx->Record['DATUM_VYPRAVENI'];
  if (!$vyrizeno) $vyrizeno = '1970-01-01';

  return $vyrizeno;
}

function getDokument(&$doc, $data) {
   $dokument = $doc->addChild('Dokument');
   $cj = LoadClass('EedCj', $data['ID']);
   $dokument->addAttribute('xmlns', 'nsesss');
    $dokument->addAttribute('ID', 'ESS_'. $data['ID']);
    $EvidencniUdaje = $dokument->addChild('EvidencniUdaje');
    $Identifikace = $EvidencniUdaje->addChild('Identifikace');

//      $identifikator = $Identifikace->addChild('Identifikator', $data['ID']);
      $identifikator = $Identifikace->addChild('Identifikator', $cj->barcode);
      $identifikator->addAttribute('zdroj', 'ERMS');

    $popis = $EvidencniUdaje->addChild('Popis');
    $popis->addChild('Nazev', substr($data['VEC'], 0, 99));

  //evidence
    $Evidence = $EvidencniUdaje->addChild('Evidence');
      $Evidence->addChild('EvidencniCislo', $cj->cislo_jednaci);
      $Evidence->addChild('PoradoveCislo', $data['CISLO_SPISU1']);


      $UrceneCasoveObdobi = $Evidence->addChild('UrceneCasoveObdobi');
      $UrceneCasoveObdobi->addChild('Rok', $data['ROK']);
      $Evidence->addChild('NazevEvidenceDokumentu', 'ERMS');

  //puvod
    $Puvod = $EvidencniUdaje->addChild('Puvod');

    if ($data['ODES_TYP'] == 'G' || $data['ODES_TYP'] == 'C') $data['ODES_TYP'] = 'O';

    if ($data['ODESLANA_POSTA']=='t') {
      $VlastniDokument = $Puvod->addChild('VlastniDokument');
        $temp1 = $VlastniDokument->addChild('DatumVytvoreni', ConvertDatumToXML($data['DATUM_PODATELNA_PRIJETI'] ? $data['DATUM_PODATELNA_PRIJETI'] : '1970-01-01', false));
//        $temp1->addAttribute('type', 'datetime');
        $Autor = $VlastniDokument->addChild('Autor');
        $Subjekt = $Autor->addChild('Subjekt');
        getSubjektUrad(&$Subjekt, $data);

    }
    else {

      $DorucenyDokument = $Puvod->addChild('DorucenyDokument');

        $temp2 = $DorucenyDokument->addChild('DatumDoruceni', ConvertDatumToXML($data['DATUM_PODATELNA_PRIJETI'] ? $data['DATUM_PODATELNA_PRIJETI'] : '1970-01-01', false));
//        $temp2->addAttribute('type', 'datetime');

        $Odesilatel = $DorucenyDokument->addChild('Odesilatel');
        $Subjekt = $Odesilatel->addChild('Subjekt');


        if ($data['ODES_TYP'] == 'O') {
          $ident = $Subjekt->addChild('IdentifikatorFyzickeOsoby', ($data['ODESL_DATNAR']));
          $ident->addAttribute('zdroj', 'ERMS');
          $Subjekt->addChild('NazevFyzickeOsoby', ($data['ODESL_JMENO'] . ' ' . $data['ODESL_PRIJMENI']));
          $Subjekt->addChild('PostovniAdresa', (UkazAdresu($data['ID'], ',')));
          $Subjekt->addChild('ElektronickyKontakt', ($data['ODESL_EMAIL']));
        }
        elseif ($data['ODES_TYP'] == 'S') {
          $ident = $Subjekt->addChild('IdentifikatorOrganizace', $GLOBALS['CONFIG']['ICO']);
          $ident->addAttribute('zdroj', 'IČ');
          $Subjekt->addChild('NazevOrganizace', $GLOBALS['CONFIG']['URAD']);
          $Subjekt->addChild('SidloOrganizace', $GLOBALS['CONFIG']['OBEC']);
          //$Subjekt->addChild('OrganizacniUtvar', $data['ODESL_PRIJMENI']);
        }
        elseif ($data['ODES_TYP'] == 'Z') {
          $ident = $Subjekt->addChild('IdentifikatorOrganizace', $GLOBALS['CONFIG']['ICO']);
          $ident->addAttribute('zdroj', 'IČ');
          $Subjekt->addChild('NazevOrganizace', $GLOBALS['CONFIG']['URAD']);
          $Subjekt->addChild('OrganizacniUtvar', $data['ODESL_PRIJMENI']);
          $Subjekt->addChild('SidloOrganizace', $GLOBALS['CONFIG']['OBEC']);
          $Subjekt->addChild('PracovniPozice', 'referent');
        }
        else {
          $ident = $Subjekt->addChild('IdentifikatorOrganizace', $data['ODESL_ICO'] ? $data['ODESL_ICO'] : '-1');
          $ident->addAttribute('zdroj', 'IČ');
          $Subjekt->addChild('NazevOrganizace', ($data['ODESL_PRIJMENI']));
          $Subjekt->addChild('OrganizacniUtvar', $data['ODESL_ODD']);
          $Subjekt->addChild('SidloOrganizace', $data['ODESL_POSTA']);
        }
//        $Subjekt->addChild('PracovniPozice', 'referent');
        
//        $temp3 = $DorucenyDokument->addChild('DatumDoruceni', ConvertDatumToXML($data['DATUM_PODATELNA_PRIJETI'] ? $data['DATUM_PODATELNA_PRIJETI'] : '1970-01-01', false));
//        $temp3->addAttribute('type', 'datetime');
        //$DorucenyDokument->addChild('OdesilatelovoEvidencniCislo', ($data['JEJICH_CJ']));

        
    }

  //trideni
    $Trideni = $EvidencniUdaje->addChild('Trideni');

      $skartace = EedTools::Skartace_Pole($data['SKARTACE']);
//      $Trideni->addChild('SpisovyZnak', ($skartace['kod']));
      $Trideni->addChild('JednoduchySpisovyZnak ', $skartace['kod']);
      $Trideni->addChild('PlneUrcenySpisovyZnak', ($skartace['plne_urceny']));
      //$Trideni->addChild('PlneUrcenySpisovyZnak', $skartace['text']);
      
       $TypDokumentu = $Trideni->addChild('TypDokumentu');
       $identTypDokumentu = $TypDokumentu->addChild('Identifikator', $data['TYP_POSTY']);
       $identTypDokumentu->addAttribute('zdroj', 'ERMS');
       $TypDokumentu->addChild('Nazev', ($GLOBALS['typ_posty'][$data['TYP_POSTY']] ? $GLOBALS['typ_posty'][$data['TYP_POSTY']] : 'neuvedeno' ));
       $TypDokumentu->addChild('Komentar', '');


  //vyrizeni
    $Vyrizeni = $EvidencniUdaje->addChild('Vyrizeni');

     if ($data['ODESLANA_POSTA']=='t') {
       $Vyrizeni->addChild('Datum', ConvertDatumToXML(($data['DATUM_VYPRAVENI'] ? $data['DATUM_VYPRAVENI'] : $data['DATUM_PODATELNA_PRIJETI']), false));
     }
     else {
       $Vyrizeni->addChild('Datum', ConvertDatumToXML(($data['DATUM_VYRIZENI']), false));
     }

     if ($data['VYRIZENO']<>'vzeti na vědomí'){
       $Vyrizeni->addChild('Zpusob', 'jiný způsob'); //($data['VYRIZENO'])); mozne hodnoty vyřízení dokumentem|postoupení|vzetí na vědomí|jiný způsob TODO: Pokud je odpoved, tak vyrizeni dokumentem
       $Vyrizeni->addChild('ObsahVyrizeni', $data['VYRIZENO'] ? $data['VYRIZENO'] : 'neuvedeno'); //($data['VYRIZENO'])); mozne hodnoty vyřízení dokumentem|postoupení|vzetí na vědomí|jiný způsob TODO: Pokud je odpoved, tak vyrizeni dokumentem
       $Vyrizeni->addChild('Oduvodneni', $data['VYRIZENO'] ? $data['VYRIZENO'] : 'neuvedeno'); //($data['VYRIZENO'])); mozne hodnoty vyřízení dokumentem|postoupení|vzetí na vědomí|jiný způsob TODO: Pokud je odpoved, tak vyrizeni dokumentem


     }
     else
       $Vyrizeni->addChild('Zpusob', 'vyřízení dokumentem'); //($data['VYRIZENO'])); mozne hodnoty vyřízení dokumentem|postoupení|vzetí na vědomí|jiný způsob TODO: Pokud je odpoved, tak vyrizeni dokumentem

     $Zpracovatel = $Vyrizeni->addChild('Zpracovatel');
     $Subjekt = $Zpracovatel->addChild('Subjekt');
     getSubjektUrad(&$Subjekt, $data);


    if ($data['ODESLANA_POSTA']=='t') {

//        $odkaz = $Vyrizeni->addChild('OdkazVyrizovanyDokument');


        $Vyrizeni->addChild('DatumOdeslani', ConvertDatumToXML(($data['DATUM_VYPRAVENI'] ? $data['DATUM_VYPRAVENI'] : $data['DATUM_PODATELNA_PRIJETI']), false));
        if ($data['TYP_DOKUMENTU'] == 'A') $Vyrizeni->addChild('OdeslaneMnozstvi', 'Listu: ' . $data['POCET_LISTU']);
        $Prijemce = $Vyrizeni->addChild('Prijemce');
        $Subjekt = $Prijemce->addChild('Subjekt');

        if ($data['ODES_TYP'] == 'O') {
          $ident = $Subjekt->addChild('IdentifikatorFyzickeOsoby', ($data['ODESL_DATNAR']));
          $ident->addAttribute('zdroj', 'ERMS');
          $Subjekt->addChild('NazevFyzickeOsoby', ($data['ODESL_JMENO'] . ' ' . $data['ODESL_PRIJMENI']));
          $Subjekt->addChild('PostovniAdresa', (UkazAdresu($data['ID'], ',')));
          $Subjekt->addChild('ElektronickyKontakt', ($data['ODESL_EMAIL']));
        }
        elseif ($data['ODES_TYP'] == 'S') {
          $ident = $Subjekt->addChild('IdentifikatorOrganizace', $GLOBALS['CONFIG']['ICO']);
          $ident->addAttribute('zdroj', 'IČ');
          $Subjekt->addChild('NazevOrganizace', $GLOBALS['CONFIG']['URAD']);
          $Subjekt->addChild('OrganizacniUtvar', $data['ODESL_PRIJMENI']);
          $Subjekt->addChild('PracovniPozice', 'referent');
          $Subjekt->addChild('SidloOrganizace', $GLOBALS['CONFIG']['OBEC']);
        }
        elseif ($data['ODES_TYP'] == 'Z') {
          $ident = $Subjekt->addChild('IdentifikatorOrganizace', $GLOBALS['CONFIG']['ICO']);
          $ident->addAttribute('zdroj', 'IČ');
          $Subjekt->addChild('NazevOrganizace', $GLOBALS['CONFIG']['URAD']);
          $Subjekt->addChild('OrganizacniUtvar', $data['ODESL_PRIJMENI']);
          $Subjekt->addChild('PracovniPozice', 'referent');
          $Subjekt->addChild('SidloOrganizace', $GLOBALS['CONFIG']['OBEC']);
        }
        else {
          $ident = $Subjekt->addChild('IdentifikatorOrganizace', $data['ODESL_ICO'] ? $data['ODESL_ICO'] : '-1');
          $ident->addAttribute('zdroj', 'IČ');
          $Subjekt->addChild('NazevOrganizace', ($data['ODESL_PRIJMENI']));
          $Subjekt->addChild('OrganizacniUtvar', $data['ODESL_ODD']);
          $Subjekt->addChild('SidloOrganizace', $data['ODESL_POSTA']);
        }
    }
    else {
       //OdkazVyrizujiciDokument
    }


  //vyrazovani
    $Vyrazovani = $EvidencniUdaje->addChild('Vyrazovani');
      $spisovna = getDataSpisovna($data['ID']);
      $skartacniRezim = $Vyrazovani->addChild('SkartacniRezim');
      $skartacniRezimIdent = $skartacniRezim->addChild('Identifikator', $spisovna['ID']);
      $skartacniRezimIdent->addAttribute('zdroj', 'ERMS');
      $nazev = substr($skartace['text'], 0, 99);
      $skartacniRezim->addChild('Nazev', $nazev ? $nazev : 'neni uveden');
      $skartacniRezim->addChild('Oduvodneni', ('podle platného typového skartačního rejstříku'));
      $skartacniRezim->addChild('SkartacniZnak', $spisovna['SKAR_ZNAK']);
      $skartacniRezim->addChild('SkartacniLhuta', $spisovna['LHUTA']);
      $skartacniRezim->addChild('SpousteciUdalost', ('uzavření spisu'));

      $dataceVyrazeni = $Vyrazovani->addChild('DataceVyrazeni');

      //nacist ze spisovny
      $dataceVyrazeni->addChild('RokSpousteciUdalosti', $spisovna['ROK_PREDANI']);
      $dataceVyrazeni->addChild('RokSkartacniOperace', $spisovna['ROK_SKARTACE']);

      if ($_POST['vcetne_priloh']) {
        $rizeni = $Vyrazovani->addChild('SkartacniRizeni');
        $skarRizeni = getDataSkartace($data['ID']);
        $rizeni->addChild('Datum', $skarRizeni['datum'] ? $skarRizeni['datum'] : '1970-01-01');
        $rizeni->addChild('SkartacniOperace', 'trvalé uložení');
        $posuzovatel = $rizeni->addChild('Posuzovatel');
        $Subjekt = $posuzovatel->AddChild('Subjekt');
        getSubjektUrad($Subjekt, array('REFERENT' => $skarRizeni['referent'] ));
      }

    //manipulace
    $Manipulace = $EvidencniUdaje->addChild('Manipulace');
      $Manipulace->addChild('NezbytnyDokument', 'ne');
      $Manipulace->addChild('AnalogovyDokument', $data['TYP_DOKUMENTU']=='D'?'ne':'ano');
      if ($data['TYP_DOKUMENTU']=='A') $Manipulace->addChild('UkladaciJednotka','box');


  //Komponenty
//   $komponenty = $doc->addChild('Komponenty'); //soubory
//   $komponenta = $komponenty->addChild('Komponenta');
}

function getMaterskaEntitaVS(&$entita, $data) {
  $entita2 = $entita->addChild('MaterskaEntita');
   $vecnaSkupina = $entita2->addChild('VecnaSkupina');
   $sql = 'select * from cis_posta_skartace where id=' . $data['SKARTACE'];
   $qx = new DB_POSTA;
   $qx->query($sql); $qx->Next_Record();
//    $vecnaSkupina->addAttribute('ID', 'ESS_VS'.$data['ID']);
    $vecnaSkupina->addAttribute('ID', ($qx->Record['JID'] ? $qx->Record['JID'] : $GLOBALS['CONFIG']['ID_PREFIX'].$qx->Record['ID']));
    $GLOBALS['JID_VS_SKARTACE'] = ($qx->Record['JID'] ? $qx->Record['JID'] : $GLOBALS['CONFIG']['ID_PREFIX'].$qx->Record['ID']);
    $GLOBALS['JID_SP_SKARTACE'] = 'SP'.$qx->Record['MAIN_ID'];

    $skartace = EedTools::Skartace_Pole($data['SKARTACE']);

    $EvidencniUdaje = $vecnaSkupina->addChild('EvidencniUdaje');

    $Identifikace = $EvidencniUdaje->addChild('Identifikace');
    $identifikator = $Identifikace->addChild('Identifikator', $GLOBALS['JID_VS_SKARTACE'] );
      $identifikator->addAttribute('zdroj', 'ERMS');

    $popis = $EvidencniUdaje->addChild('Popis');
    $popis->addChild('Nazev', substr($qx->Record['TEXT'], 0, 99));

    //Puvod
    $Puvod = $EvidencniUdaje->addChild('Puvod');
    $Puvod->addChild('DatumVytvoreni',  ConvertDatumToXML($qx->Record['LAST_DATE'] ? $qx->Record['LAST_DATE'] : '1970-01-01', false)); //TODO: zapsat datum vytvoreni spisoveho planu

    //Trideni
    $Trideni = $EvidencniUdaje->addChild('Trideni');
      $Trideni->addChild('JednoduchySpisovyZnak ', $skartace['kod']);
      $Trideni->addChild('PlneUrcenySpisovyZnak', ($skartace['plne_urceny']));
      $spisPlan = $Trideni->addChild('SpisovyPlan');
      $spisPlan->addAttribute('ID', $GLOBALS['JID_SP_SKARTACE']); //ID spisoveho planu


      $sql = 'select * from posta_cis_skartace_main where id=' . $qx->Record['MAIN_ID'];
      $qx = new DB_POSTA;
      $qx->query($sql); $qx->Next_Record();
      //spisPlan
      $identifikator = $spisPlan->addChild('Identifikator',$GLOBALS['JID_SP_SKARTACE']);
      $identifikator->addAttribute('zdroj', 'ERMS');
      $spisPlan->addChild('Nazev', $qx->Record['TEXT'] ? $qx->Record['TEXT'] : 'spisový plán organizace');
      $Manipulace = $spisPlan->addChild('Manipulace');
      $Manipulace->addChild('DatumOtevreni', ($qx->Record['PLATNOST_OD'] ? $qx->Record['PLATNOST_OD'] : '1970-01-01'));
      $Vydavatel = $spisPlan->AddChild('Vydavatel');
      $Subjekt = $Vydavatel->AddChild('Subjekt');
      getSubjektUrad($Subjekt, array());

    //Vyrazovani

    $Vyrazovani = $EvidencniUdaje->addChild('Vyrazovani');
    $spisovna = getDataSpisovna($data['ID']);
       $SkartacniRezim = $Vyrazovani->addChild('SkartacniRezim');
       $identSkartace = $SkartacniRezim->addChild('Identifikator', 'VSS_'.$spisovna['ID']);
       $identSkartace->addAttribute('zdroj', 'ERMS');
       $SkartacniRezim->addChild('Nazev', ($qx->Record['TEXT']));
      $SkartacniRezim->addChild('Oduvodneni', ('podle platného typového skartačního rejstříku'));
      $SkartacniRezim->addChild('SkartacniZnak', $spisovna['SKAR_ZNAK']);
      $SkartacniRezim->addChild('SkartacniLhuta', $spisovna['LHUTA']);
      $SkartacniRezim->addChild('SpousteciUdalost', ('uzavření spisu'));

      $dataceVyrazeni = $Vyrazovani->addChild('DataceVyrazeni');
      //nacist ze spisovny
      $dataceVyrazeni->addChild('RokSpousteciUdalosti', $spisovna['ROK_PREDANI']);
      $dataceVyrazeni->addChild('RokSkartacniOperace', $spisovna['ROK_SKARTACE']);



    $Manipulace = $EvidencniUdaje->addChild('Manipulace');
      $Manipulace->addChild('NezbytnyDokument', 'ne');
      $Manipulace->addChild('AnalogovyDokument', $data['TYP_DOKUMENTU']=='D'?'ne':'ano');
      $Manipulace->addChild('DatumOtevreni', '2016-01-01'); //TODO: zapsat datum vytovrnei spisu

//
}

function getSpisInfo(&$spis, $data) {
  $EvidencniUdaje = $spis->addChild('EvidencniUdaje');
  $cj = LoadClass('EedCj',$data['ID']);
  $spisovna = getDataSpisovna($data['ID']);
  $cj_info = $cj->GetCjInfo($data['ID']);

      $Identifikace = $EvidencniUdaje->addChild('Identifikace');
    $identifikator = $Identifikace->addChild('Identifikator', ($cj_info['JID_SPISU'] ? $cj_info['JID_SPISU'] : $cj->barcode));
      $identifikator->addAttribute('zdroj', 'ERMS');

//$cj->cislo_jednaci_zaklad;

    $popis = $EvidencniUdaje->addChild('Popis');
    $popis->addChild('Nazev', (substr(($cj_info['NAZEV_SPISU']<>'' ? $cj_info['NAZEV_SPISU'] : $data['VEC']), 0, 99)));

    //Evidence
    $Evidence = $EvidencniUdaje->addChild('Evidence');
      $Evidence->addChild('EvidencniCislo', $cj->cislo_jednaci_zaklad);
      $Evidence->addChild('PoradoveCislo', $cj->cj1);
      $UrceneCasoveObdobi = $Evidence->addChild('UrceneCasoveObdobi');
        $UrceneCasoveObdobi->addChild('Rok', $data['ROK']);
      $Evidence->addChild('NazevEvidenceDokumentu', 'ERMS');

    //Puvod
    $Puvod = $EvidencniUdaje->addChild('Puvod');
    $Puvod->addChild('DatumVytvoreni', ConvertDatumToXML($data['DATUM_PODATELNA_PRIJETI'], false)); //TODO: zapsat datum vytovrnei spisu


      $skartace = EedTools::Skartace_Pole($data['SKARTACE']);

    //Trideni
    $Trideni = $EvidencniUdaje->addChild('Trideni');
      $Trideni->addChild('JednoduchySpisovyZnak ', $skartace['kod']);
      $Trideni->addChild('PlneUrcenySpisovyZnak', $skartace['plne_urceny']);
     getMaterskaEntitaVS($Trideni, $data);

    //VyrizeniUzavreni
    $Vyrizeni = $EvidencniUdaje->addChild('VyrizeniUzavreni');
//      $Vyrizeni->addChild('DatumVyrizeni', ConvertDatumToXML($data['DATUM_VYRIZENI'], false));
      $Vyrizeni->addChild('Datum', ConvertDatumToXML(SIPVyrizeno($data['ID']), false));

//      $Vyrizeni->addChild('Zpusob', ('vzetí na vědomí')); //($data['VYRIZENO'])); mozne hodnoty vyřízení dokumentem|postoupení|vzetí na vědomí|jiný způsob TODO: Pokud je odpoved, tak vyrizeni dokumentem
     $Vyrizeni->addChild('Zpusob', 'jiný způsob'); //($data['VYRIZENO'])); mozne hodnoty vyřízení dokumentem|postoupení|vzetí na vědomí|jiný způsob TODO: Pokud je odpoved, tak vyrizeni dokumentem
     $Vyrizeni->addChild('ObsahVyrizeni', 'dokumentem ve spisu'); //($data['VYRIZENO'])); mozne hodnoty vyřízení dokumentem|postoupení|vzetí na vědomí|jiný způsob TODO: Pokud je odpoved, tak vyrizeni dokumentem
     $Vyrizeni->addChild('Oduvodneni', 'spis neobsahuje samostatně způsob vyřízení'); //($data['VYRIZENO'])); mozne hodnoty vyřízení dokumentem|postoupení|vzetí na vědomí|jiný způsob TODO: Pokud je odpoved, tak vyrizeni dokumentem

      $Zpracovatel = $Vyrizeni->addChild('Zpracovatel');
      $Subjekt = $Zpracovatel->addChild('Subjekt');
      getSubjektUrad($Subjekt, $data);


    //Vyrazovani
    $Vyrazovani = $EvidencniUdaje->addChild('Vyrazovani');
       $SkartacniRezim = $Vyrazovani->addChild('SkartacniRezim');
       $identSkartace = $SkartacniRezim->addChild('Identifikator', $data['SKARTACE']);
       $identSkartace->addAttribute('zdroj', 'ERMS');
       $SkartacniRezim->addChild('Nazev', ($data['SKARTACE']));
      $SkartacniRezim->addChild('Oduvodneni', ('podle platného typového skartačního rejstříku'));
      $SkartacniRezim->addChild('SkartacniZnak', $skartace['znak'] ? $skartace['znak'] : 'A') ;
      $SkartacniRezim->addChild('SkartacniLhuta', $skartace['doba']);
      $SkartacniRezim->addChild('SpousteciUdalost', ('uzavření spisu'));

      $dataceVyrazeni = $Vyrazovani->addChild('DataceVyrazeni');
      //nacist ze spisovny
      $dataceVyrazeni->addChild('RokSpousteciUdalosti', $spisovna['ROK_PREDANI']);
      $dataceVyrazeni->addChild('RokSkartacniOperace', $spisovna['ROK_SKARTACE']);


    $Manipulace = $EvidencniUdaje->addChild('Manipulace');
      $Manipulace->addChild('NezbytnyDokument', 'ne');
      $Manipulace->addChild('AnalogovyDokument', $data['TYP_DOKUMENTU']=='D'?'ne':'ano');
      $Manipulace->addChild('DatumOtevreni', ConvertDatumToXML($data['DATUM_PODATELNA_PRIJETI'], false)); //TODO: zapsat datum vytovrnei spisu

   $Dokumenty = $spis->addChild('Dokumenty');
   //pridat generovani vsech dokumentu....
   $docs = $cj->getDocsInCJ($data['ID']);
   $db = new DB_POSTA;
   foreach($docs as $doc_id) {
   	 $sql = 'select * from posta where id=' . $doc_id;
   	 $db->query($sql);
   	 $db->Next_Record();
   	 $data_doc = $db->Record; 
     getDokument($Dokumenty, $data_doc);
   }

//   getDokument($Dokumenty, $data);
    
}

function getSubjektUrad(&$Subjekt, $data = array()) {
      $subjektIco = $Subjekt->addChild('IdentifikatorOrganizace', $GLOBALS['CONFIG']['ICO']);
      $subjektIco->addAttribute('zdroj', ('IČ'));
      $user = LoadClass('EedUser', $data['REFERENT']);
      $Subjekt->addChild('NazevOrganizace', ($GLOBALS['CONFIG']['URAD']));
      $subjektFyzOsob = $Subjekt->addChild('IdentifikatorFyzickeOsoby', $user->login);
      $subjektFyzOsob->addAttribute('zdroj', ('evidence zaměstanců'));
      $Subjekt->addChild('NazevFyzickeOsoby', $user->cele_jmeno);
      $Subjekt->addChild('OrganizacniUtvar', $user->odbor_text);
      $Subjekt->addChild('PracovniPozice', 'referent');
      $Subjekt->addChild('SidloOrganizace', ($GLOBALS['CONFIG']['OBEC']));
}