<?php
function Response_OperaceStatus(&$response,$kod=null, $popis=null) {
  $response = array(
    'Kod'=>$kod, 
    'Popis'=>TxtEncoding4Soap($popis)
  );
}

function Response_Zprava(&$response, $kod=null, $popis=null, $udalostId=null, $poradi=null) {
  $response = array(
    'Kod' => $kod,
    'Popis'=> TxtEncoding4Soap($popis),
    //attr
    'UdalostId'=> TxtEncoding4Soap($udalostId),
    'Poradi'=> TxtEncoding4Soap($poradi),
    'DatumVzniku'=> ConvertDatumToXML(date("Y-m-d H:i:s")),
  );
}

function Response_Dokument(&$response,$id, $dokumentTyp) {
  $res = true;
  
  $response = array(
		'Identifikator'=>array(
		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>null,
			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>null,
		),
		'Nazev'=>null,
		'Popis'=>null,
		'CisloJednaci'=>null,
		'SpisovaZnacka'=>null,
		'PodaciDenikPoradi'=>null,
		'PodaciDenikRok'=>null,
		'PodaciDenik'=>null,
		'DatumCasVytvoreni'=>null,
		'TypDokumentu'=>null,
		'SpisovyPlan'=>null,
		'SpisovyZnak'=>null,
		'SkartacniZnak'=>null,
		'SkartacniLhuta'=>null,
		'Poznamka'=>null,
		'CjOdesilatel'=>null,
	  'PocetListu'=>null,
		'PocetPriloh'=>null,
		'DruhPriloh'=>null,
		'PocetListuPriloh'=>null,
	);
	
	if ($dokumentTyp=='f') {
		$response['Doruceni'] = array(
      'Odesilatel'=>array(
        $GLOBALS["soap"]["namespace_ess"].'Subjekt'=>array(
          $GLOBALS["soap"]["namespace_ess"].'Identifikator'=>array(
            $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>null,
			      $GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>null,
          ),
          $GLOBALS["soap"]["namespace_ess"].'TypSubjektu'=>null,
          $GLOBALS["soap"]["namespace_ess"].'ObchodniNazev'=>null,
          $GLOBALS["soap"]["namespace_ess"].'IC'=>null,
          $GLOBALS["soap"]["namespace_ess"].'DatumNarozeni'=>null,
          $GLOBALS["soap"]["namespace_ess"].'MistoNarozeni'=>null,
          $GLOBALS["soap"]["namespace_ess"].'Jmeno'=>null,
          $GLOBALS["soap"]["namespace_ess"].'Prijmeni'=>null,
          $GLOBALS["soap"]["namespace_ess"].'Osloveni'=>null,
          $GLOBALS["soap"]["namespace_ess"].'TitulPred'=>null,
          $GLOBALS["soap"]["namespace_ess"].'TitulZa'=>null,
          $GLOBALS["soap"]["namespace_ess"].'FunkceUtvarPopis'=>null,
          $GLOBALS["soap"]["namespace_ess"].'FunkceUtvarIdentifikator'=>null,
          $GLOBALS["soap"]["namespace_ess"].'Poznamka'=>null,
          $GLOBALS["soap"]["namespace_ess"].'Adresy'=>null,
        ),
        $GLOBALS["soap"]["namespace_ess"].'Adresa'=>array(
          $GLOBALS["soap"]["namespace_ess"].'AdresaPostovni'=>array(
            $GLOBALS["soap"]["namespace_ess"].'Identifikator'=>array(
              $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>null,
			        $GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>null,
            ),
            $GLOBALS["soap"]["namespace_ess"].'Obec' => null,
            $GLOBALS["soap"]["namespace_ess"].'CastObce' => null,
            $GLOBALS["soap"]["namespace_ess"].'MestskaCast' => null,
            $GLOBALS["soap"]["namespace_ess"].'Ulice' => null,
            $GLOBALS["soap"]["namespace_ess"].'EvidencniCislo' => null,
            $GLOBALS["soap"]["namespace_ess"].'OrientacniCislo' => null,
            $GLOBALS["soap"]["namespace_ess"].'PopisneCislo' => null,
            $GLOBALS["soap"]["namespace_ess"].'Psc' => null,
            $GLOBALS["soap"]["namespace_ess"].'Zeme' => null,
            $GLOBALS["soap"]["namespace_ess"].'RuianVazba' => null,
            $GLOBALS["soap"]["namespace_ess"].'Poznamka' => null,
            $GLOBALS["soap"]["namespace_ess"].'POBOX' => null,
            $GLOBALS["soap"]["namespace_ess"].'TypAdresy' => null,
            $GLOBALS["soap"]["namespace_ess"].'DodaciPosta' => null,
            $GLOBALS["soap"]["namespace_ess"].'Okres' => null,
          ),
        ),
      ),
      $GLOBALS["soap"]["namespace_ess"].'ZasilkaInfo' => null,
    );
  }

	if ($dokumentTyp=='t') {
		$response['Vypraveni'] = array(
      $GLOBALS["soap"]["namespace_ess"].'ZasilkaInfo'=>array(
          $GLOBALS["soap"]["namespace_ess"].'TypSubjektu'=>null,
          $GLOBALS["soap"]["namespace_ess"].'ZpusobManipulaceId'=>null,
          $GLOBALS["soap"]["namespace_ess"].'ZpusobZachazeniId'=>null,
          $GLOBALS["soap"]["namespace_ess"].'DruhZasilkyId'=>null,
          $GLOBALS["soap"]["namespace_ess"].'DatumVypraveni'=>null,
          $GLOBALS["soap"]["namespace_ess"].'Vaha'=>null,
          $GLOBALS["soap"]["namespace_ess"].'Poplatek'=>null,
          $GLOBALS["soap"]["namespace_ess"].'PodaciCislo'=>null,
          $GLOBALS["soap"]["namespace_ess"].'IdZasilky'=>null,
          $GLOBALS["soap"]["namespace_ess"].'StavZasilky'=>null,
          $GLOBALS["soap"]["namespace_ess"].'Poznamka'=>null,
          $GLOBALS["soap"]["namespace_ess"].'DatumDoruceni'=>null,
          $GLOBALS["soap"]["namespace_ess"].'dmID'=>null,
        ),
      );
  }

  if ($id>0) {	
    $dokument = VratDokumentInfo($id);
    $doc_obj = LoadClass('EedCj', $id);
    $barcode = $doc_obj->barcode;


    if ($dokument['DALSI_ID_AGENDA'] <> '') {
      list ($ZdrojIdExt, $HodnotaIdExt) = explode(':', $dokument['DALSI_ID_AGENDA']);
    } else {
      $HodnotaIdExt = $doc_obj->id_dokument;
      $ZdrojIdExt = 'TmapEss';
    }

    
    $response = array(
  		'Identifikator'=>array(
//  		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$dokument[DALSI_ID_AGENDA],
  		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$HodnotaIdExt,
  			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>$ZdrojIdExt,
  		),
  		'Nazev'=>$dokument[VEC],
//  		$GLOBALS["soap"]["namespace_ess"].'Popis'=>null,
  		'CisloJednaci'=>$dokument[CISLO_JEDNACI],
//  		$GLOBALS["soap"]["namespace_ess"].'SpisovaZnacka'=>null,
  		'PodaciDenikPoradi'=>$dokument[CISLO_SPISU1],
  		'PodaciDenikRok'=>$dokument[ROK],
//  		$GLOBALS["soap"]["namespace_ess"].'PodaciDenik'=>null,
  		'DatumCasVytvoreni'=>$dokument[DATUM],
  		'TypDokumentu'=>$dokument[TYP_DOC],
//  		$GLOBALS["soap"]["namespace_ess"].'SpisovyPlan'=>null,
  		'SpisovyZnak'=>$dokument[SPIS_ZNAK],
  		'SkartacniZnak'=>$dokument[SKAR_ZNAK],
  		'SkartacniLhuta'=>$dokument[SKAR_LHUTA],
  		'Poznamka'=>$dokument[POZNAMKA],
  		'CjOdesilatel'=>$dokument[JEJICH_CJ],
		  'PocetListu'=>$dokument[POCET_LISTU],
			'PocetPriloh'=>$dokument[POCET_PRILOH],
			'DruhPriloh'=>$dokument[DRUH_PRILOH],
      'PocetListuPriloh' => 0,
      'VlastniKdo' => $doc_obj->referent_id,
      'StavDokumentu' => '',
  	);
  	

  	if ($dokumentTyp=='f') {
		  $response['Doruceni'] = array(
  		  'Odesilatel'=>array(
          $GLOBALS["soap"]["namespace_ess"].'Subjekt'=>array(
//            $GLOBALS["soap"]["namespace_ess"].'Identifikator'=>array(
//              $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>null,
//  			      $GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>null,
//            ),
            $GLOBALS["soap"]["namespace_ess"].'TypSubjektu'=>$dokument[TYP_ADR],
            $GLOBALS["soap"]["namespace_ess"].'ObchodniNazev'=>$dokument[ORGANIZACE],
//            $GLOBALS["soap"]["namespace_ess"].'IC'=>null,
            $GLOBALS["soap"]["namespace_ess"].'DatumNarozeni'=>$dokument[DATNAR],
//            $GLOBALS["soap"]["namespace_ess"].'MistoNarozeni'=>null,
            $GLOBALS["soap"]["namespace_ess"].'Jmeno'=>$dokument[JMENO],
            $GLOBALS["soap"]["namespace_ess"].'Prijmeni'=>$dokument[PRIJMENI],
            $GLOBALS["soap"]["namespace_ess"].'Osloveni'=>$dokument[OSLOVENI],
//            $GLOBALS["soap"]["namespace_ess"].'TitulPred'=>null,
//            $GLOBALS["soap"]["namespace_ess"].'TitulZa'=>null,
//            $GLOBALS["soap"]["namespace_ess"].'FunkceUtvarPopis'=>null,
//            $GLOBALS["soap"]["namespace_ess"].'FunkceUtvarIdentifikator'=>null,
//            $GLOBALS["soap"]["namespace_ess"].'Poznamka'=>null,
//            $GLOBALS["soap"]["namespace_ess"].'Adresy'=>null,
          ),
          $GLOBALS["soap"]["namespace_ess"].'Adresa'=>array(
            $GLOBALS["soap"]["namespace_ess"].'AdresaPostovni'=>array(
//              $GLOBALS["soap"]["namespace_ess"].'Identifikator'=>array(
//                $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>null,
//  			        $GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>null,
//              ),
              $GLOBALS["soap"]["namespace_ess"].'Obec' => $dokument[MESTO],
//              $GLOBALS["soap"]["namespace_ess"].'CastObce' => null,
//              $GLOBALS["soap"]["namespace_ess"].'MestskaCast' => null,
              $GLOBALS["soap"]["namespace_ess"].'Ulice' => $dokument[ULICE],
//              $GLOBALS["soap"]["namespace_ess"].'EvidencniCislo' => null,
              $GLOBALS["soap"]["namespace_ess"].'OrientacniCislo' => $dokument[COR],
              $GLOBALS["soap"]["namespace_ess"].'PopisneCislo' => $dokument[CP],
              $GLOBALS["soap"]["namespace_ess"].'Psc' => $dokument[PSC],
              $GLOBALS["soap"]["namespace_ess"].'Zeme' => 'cz',
//              $GLOBALS["soap"]["namespace_ess"].'RuianVazba' => null,
//              $GLOBALS["soap"]["namespace_ess"].'Poznamka' => null,
//              $GLOBALS["soap"]["namespace_ess"].'POBOX' => null,
//              $GLOBALS["soap"]["namespace_ess"].'TypAdresy' => null,
//              $GLOBALS["soap"]["namespace_ess"].'DodaciPosta' => $dokument[POSTA],
//              $GLOBALS["soap"]["namespace_ess"].'Okres' => null,
            ),
          ),
        ),
        $GLOBALS["soap"]["namespace_ess"].'ZasilkaInfo' => null,
      );
    }

    $odeslani = array_flip($GLOBALS["KONEKTOR"]["ISRZP"]["DRUH_ODESLANI"]);

  	if ($dokumentTyp=='t' && $doc_obj->odes_typ <> 'Z') {
		  $response['Vypraveni'] = array(
    		'Identifikator'=>array(
    		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$HodnotaIdExt,
    			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>$ZdrojIdExt,
    		),
  		  'Adresat'=>array(
          $GLOBALS["soap"]["namespace_ess"].'Subjekt'=>array(
//            $GLOBALS["soap"]["namespace_ess"].'Identifikator'=>array(
//              $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>null,
//  			      $GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>null,
//            ),
            $GLOBALS["soap"]["namespace_ess"].'TypSubjektu'=>$dokument[TYP_ADR],
            $GLOBALS["soap"]["namespace_ess"].'ObchodniNazev'=>$dokument[ORGANIZACE],
//            $GLOBALS["soap"]["namespace_ess"].'IC'=>null,
            $GLOBALS["soap"]["namespace_ess"].'DatumNarozeni'=>$dokument[DATNAR],
//            $GLOBALS["soap"]["namespace_ess"].'MistoNarozeni'=>null,
            $GLOBALS["soap"]["namespace_ess"].'Jmeno'=>$dokument[JMENO],
            $GLOBALS["soap"]["namespace_ess"].'Prijmeni'=>$dokument[PRIJMENI],
            $GLOBALS["soap"]["namespace_ess"].'Osloveni'=>$dokument[OSLOVENI],
//            $GLOBALS["soap"]["namespace_ess"].'TitulPred'=>null,
//            $GLOBALS["soap"]["namespace_ess"].'TitulZa'=>null,
//            $GLOBALS["soap"]["namespace_ess"].'FunkceUtvarPopis'=>null,
//            $GLOBALS["soap"]["namespace_ess"].'FunkceUtvarIdentifikator'=>null,
//            $GLOBALS["soap"]["namespace_ess"].'Poznamka'=>null,
//            $GLOBALS["soap"]["namespace_ess"].'Adresy'=>null,
          ),
          $GLOBALS["soap"]["namespace_ess"].'Adresa'=>array(
            $GLOBALS["soap"]["namespace_ess"].'AdresaPostovni'=>array(
//              $GLOBALS["soap"]["namespace_ess"].'Identifikator'=>array(
//                $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>null,
//  			        $GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>null,
//              ),
              $GLOBALS["soap"]["namespace_ess"].'Obec' => $dokument[MESTO],
//              $GLOBALS["soap"]["namespace_ess"].'CastObce' => null,
//              $GLOBALS["soap"]["namespace_ess"].'MestskaCast' => null,
              $GLOBALS["soap"]["namespace_ess"].'Ulice' => $dokument[ULICE],
//              $GLOBALS["soap"]["namespace_ess"].'EvidencniCislo' => null,
              $GLOBALS["soap"]["namespace_ess"].'OrientacniCislo' => $dokument[COR],
              $GLOBALS["soap"]["namespace_ess"].'PopisneCislo' => $dokument[CP],
              $GLOBALS["soap"]["namespace_ess"].'Psc' => $dokument[PSC],
              $GLOBALS["soap"]["namespace_ess"].'Zeme' => 'cz',
//              $GLOBALS["soap"]["namespace_ess"].'RuianVazba' => null,
//              $GLOBALS["soap"]["namespace_ess"].'Poznamka' => null,
//              $GLOBALS["soap"]["namespace_ess"].'POBOX' => null,
//              $GLOBALS["soap"]["namespace_ess"].'TypAdresy' => null,
//              $GLOBALS["soap"]["namespace_ess"].'DodaciPosta' => $dokument[POSTA],
//              $GLOBALS["soap"]["namespace_ess"].'Okres' => null,
            ),
            $GLOBALS["soap"]["namespace_ess"].'AdresaDS'=>array(
              $GLOBALS["soap"]["namespace_ess"].'IdDb' => $dokument[DS],
            ),
            $GLOBALS["soap"]["namespace_ess"].'AdresaElektronicka'=>array(
              $GLOBALS["soap"]["namespace_ess"].'Typ' => 'email',
              $GLOBALS["soap"]["namespace_ess"].'Kontakt' => $dokument['EMAIL'],
            ),
          ),
        ),
  		  'ZasilkaInfo'=>array(
            'TypSubjektu'=>$dokument[TYP_ADR],
            'ZpusobManipulaceId'=>$odeslani[$dokument[ODESLANI]],
//            'IC'=>null,
//            'MistoNarozeni'=>null,
            'DruhZasilkyId'=>$dokument[JMENO],
            'DatumVypraveni'=>$dokument[DATUM_VYPRAVENI],
            //'Vaha'=>$dokument[OSLOVENI],
            //'Poplatek'=>$dokument[OSLOVENI],
            'IdZasilky'=>$barcode,
            'Poznamka'=>$dokument[POZNAMKA],
            'DatumDoruceni'=>$dokument[DATUM_DORUCENI],
            'dmID'=>$dokument[DS],

           'PostovniSluzby' => array(
             'PostovniSluzbaId' => '',
             'PostovniSluzbaText' => ''
           ),
         )
      );
    }
    if ($dokument['ODES_TYP'] == 'M') {
      UNSET($response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaPostovni']);
      UNSET($response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaDS']);
      UNSET($response['Vypraveni']['Adresat'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaPostovni']);
      UNSET($response['Vypraveni']['Adresat'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaDS']);
    }
    if ($dokument['ODESLANI'] == '9') {
      UNSET($response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaPostovni']);
      UNSET($response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaElektronicka']);
      UNSET($response['Vypraveni']['Adresat'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaPostovni']);
      UNSET($response['Vypraveni']['Adresat'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaElektronicka']);
    }

    $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
    $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);
    if (count($upload_records)>0) {
      $pocet=0; $soubor = array();
      while (list($key,$val)=@each($upload_records))
      {
        $pocet++;
        $soubor[] = array(
        		'Identifikator'=>array(
        		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$val[ID],
        			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>'TmapEss',
        		)
//          )
        );
      }

      $response['OdkazyNaSoubory'] = $soubor;

    }


    if ($doc_obj->referent_id) {
      $user = LoadClass('EedUser', $doc_obj->referent_id);
      $response['VlastniKdo'] = $user->login;
    }
   if ($doc_obj->status) {
     if ($doc_obj->status>1 && $doc_obj->status<>9) $response['StavDokumentu'] = 'nevyrizen';
     elseif ($doc_obj->status == 9) $response['StavDokumentu'] = 'vyrizen';
     elseif ($doc_obj->status == 1) $response['StavDokumentu'] = 'uzavren';
     elseif ($doc_obj->status == -1) $response['StavDokumentu'] = 'stornovan';
     elseif ($doc_obj->status == -2) $response['StavDokumentu'] = 'skartovan';
     elseif ($doc_obj->status == -3) $response['StavDokumentu'] = 'predanDoSpisovny';
     elseif ($doc_obj->status == -6) $response['StavDokumentu'] = 'predanDoArchivu';

   }

  }
  return $res;
}

function Response_ProfilSpisu(&$response,$id_spis=false) {
  $res = true;
  
  $response = array(
		'Identifikator'=>array(
		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>null,
			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>null,
		),
		'Nazev'=>null,
		'Popis'=>null,
		'CisloJednaci'=>null,
		'SpisovaZnacka'=>null,
		'PodaciDenikPoradi'=>null,
		'PodaciDenikRok'=>null,
		'PodaciDenik'=>null,
		'DatumCasVytvoreni'=>null,
		'TypDokumentu'=>null,
		'SpisovyPlan'=>null,
		'SpisovyZnak'=>null,
		'SkartacniZnak'=>null,
		'SkartacniLhuta'=>null,
		'Poznamka'=>null,
		'DoplnujiciData' => array(
  		'ZpusobVedeni'=>null,
  	),
	);
  
  if ($id_spis) {	
    $dokument = VratDokumentInfo($id_spis);
    //print_r($dokument);
    
    $response = array(
  		'Identifikator'=>array(
  		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$dokument[DALSI_ID_SPIS_AGENDA],
  			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>$GLOBALS["KONEKTOR"]["ISRZP"]["ZdrojID"],
  		),
  		'Nazev'=>$dokument[VEC],
//  		'Popis'=>null,
  		'CisloJednaci'=>$dokument[CISLO_JEDNACI],
  		'SpisovaZnacka'=>$dokument[CISLO_SPISU],
  		'PodaciDenikPoradi'=>$dokument[CISLO_SPISU1],
  		'PodaciDenikRok'=>$dokument[ROK],
//  		'PodaciDenik'=>null,
  		'DatumCasVytvoreni'=>$dokument[DATUM],
  		'TypDokumentu'=>$dokument[TYP_DOC],
//  		'SpisovyPlan'=>null,
  		'SpisovyZnak'=>$dokument[SPIS_ZNAK],
  		'SkartacniZnak'=>$dokument[SKAR_ZNAK],
  		'SkartacniLhuta'=>$dokument[SKAR_LHUTA],
  		'Poznamka'=>$dokument[POZNAMKA],
  		'DoplnujiciData' => array(
    		'ZpusobVedeni'=>'Priorace', //Priorace, SbernyArch
    	),
    );  
  }

  return $res;
}

function Response_DokumentyVlozene(&$response,$id_spis=false) {
  $res = true;
  
  $response = array(
    'DokumentZkracenyVlozeny'=>array(
      'IdDokument'=>array(
    		'Identifikator'=>array(
    		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>null,
    			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>null,
    		),
    	),
  		'CisloJednaci'=>null,
  		'PodaciDenikPoradi'=>null,
  		'PodaciDenikRok'=>null,
  		'PodaciDenik'=>null,
  	),
  );
  
  if ($id_spis) {
    $dokumenty_arr = VratDokumentyKeSpisu($id_spis);
    if ($dokumenty_arr) {
      $id = $dokumenty_arr[0];
      $dokument = VratDokumentInfo($id);
      //print_r($dokument);
      
      $response = array(
        'DokumentZkracenyVlozeny'=>array(
          'IdDokument'=>array(
    		    'Identifikator'=>array(
        		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$dokument[DALSI_ID_AGENDA],
        			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>$GLOBALS["KONEKTOR"]["ISRZP"]["ZdrojID"],
        		),
        	),
      		'CisloJednaci'=>$dokument[CISLO_JEDNACI],
      		'PodaciDenikPoradi'=>$dokument[EV_CISLO],
      		'PodaciDenikRok'=>$dokument[ROK],
  //   		'PodaciDenik'=>null,
        ),
      );
    }  
  }

  return $res;
}
?>
