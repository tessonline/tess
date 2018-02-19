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

function Response_Dokument(&$response,$id, $dokumentTyp)
{
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
		'DoplnujiciData'=>array(
		  'PocetListu'=>null,
			'PocetPriloh'=>null,
			'DruhPriloh'=>null,
      'IdSpisu' => null,
		),
	);

  if ($id>0) {
    $dokument = VratDokumentInfo($id);
//     $EedCj = LoadClass('EedCj', $id);
//     $spisId = $EedCj->spis_id;
//     $dokument2 = VratDokumentInfo($spisId);
//     if (!$dokument['TYP_DOC']) $dokument['TYP_DOC'] = $dokument2['TYP_DOC'];
  }
//print_r($response);

  if (!$dokumentTyp) $dokumentTyp = $dokument['ODESLANA_POSTA'] ? $dokument['ODESLANA_POSTA'] : 't';

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

	//if ($dokumentTyp=='t')
  {
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
  $response['Soubory'] = null;

  if ($id>0) {	
    $dokument = VratDokumentInfo($id);
   $response = array(
//   		'Identifikator'=>array(
//   		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$dokument[DALSI_ID_AGENDA],
//   			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>$GLOBALS["KONEKTOR"]["ISRZP"]["ZdrojID"],
//   		),
  		'Identifikator'=>array(
  		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$id,
  			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>'TmapEss',
  		),
  		'Nazev'=>$dokument[VEC],
//  		$GLOBALS["soap"]["namespace_ess"].'Popis'=>null,
  		'CisloJednaci'=>$dokument[CISLO_JEDNACI],
//  		$GLOBALS["soap"]["namespace_ess"].'SpisovaZnacka'=>null,
  		'PodaciDenikPoradi'=>$dokument[CISLO_SPISU1],
  		'PodaciDenikRok'=>$dokument[CISLO_SPISU2],
//  		$GLOBALS["soap"]["namespace_ess"].'PodaciDenik'=>null,
  		'DatumCasVytvoreni'=>$dokument[DATUM],
  		'TypDokumentu'=>$dokument[TYP_DOC],
//  		$GLOBALS["soap"]["namespace_ess"].'SpisovyPlan'=>null,
  		'SpisovyZnak'=>$dokument[SPIS_ZNAK],
  		'SkartacniZnak'=>$dokument[SKAR_ZNAK],
  		'SkartacniLhuta'=>$dokument[SKAR_LHUTA],
  		'Poznamka'=>$dokument[POZNAMKA],
  		'CjOdesilatel'=>$dokument[JEJICH_CJ],
  		'CjOdesilatelZeDne'=>$dokument[JEJICH_CJ_DNE],
  		'DoplnujiciData'=>array(
  		  'PocetListu'=>$dokument[POCET_LISTU],
  			'PocetPriloh'=>$dokument[POCET_PRILOH],
  			'DruhPriloh'=>$dokument[DRUH_PRILOH],
  		),
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
//            $GLOBALS["soap"]["namespace_ess"].'IC'=>null,
            $GLOBALS["soap"]["namespace_ess"].'DatumNarozeni'=>$dokument[DATNAR],
//            $GLOBALS["soap"]["namespace_ess"].'MistoNarozeni'=>null,
            $GLOBALS["soap"]["namespace_ess"].'Osloveni'=>$dokument[OSLOVENI],
//            $GLOBALS["soap"]["namespace_ess"].'TitulPred'=>null,
//            $GLOBALS["soap"]["namespace_ess"].'TitulZa'=>null,
            $GLOBALS["soap"]["namespace_ess"].'FunkceUtvarPopis'=>$dokument[OSOBA],
            $GLOBALS["soap"]["namespace_ess"].'FunkceUtvarIdentifikator'=>$dokument[ODDELENI],
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
            $GLOBALS["soap"]["namespace_ess"].'AdresaElektronicka'=>array(
              $GLOBALS["soap"]["namespace_ess"].'Typ' => 'email',
              $GLOBALS["soap"]["namespace_ess"].'Kontakt' => $dokument['EMAIL'],
            ),
            $GLOBALS["soap"]["namespace_ess"].'AdresaDS'=>array(
              $GLOBALS["soap"]["namespace_ess"].'IdDb' => $dokument['DS'],
            ),
          ),
        ),
        $GLOBALS["soap"]["namespace_ess"].'ZasilkaInfo' => null,
      );
    }

            if ($dokument['TYP_ADR'] == 'Fyzicka') {
              $response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Subjekt'][$GLOBALS["soap"]["namespace_ess"].'Jmeno'] = $dokument[JMENO];
              $response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Subjekt'][$GLOBALS["soap"]["namespace_ess"].'Prijmeni'] =$dokument[PRIJMENI];
              $response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Subjekt'][$GLOBALS["soap"]["namespace_ess"].'ObchodniNazev']='';
            }
            else {
              $response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Subjekt'][$GLOBALS["soap"]["namespace_ess"].'Jmeno']='';
              $response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Subjekt'][$GLOBALS["soap"]["namespace_ess"].'Prijmeni'] = '';
              $response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Subjekt'][$GLOBALS["soap"]["namespace_ess"].'ObchodniNazev'] = $dokument[ORGANIZACE];
            }


  	if ($dokumentTyp=='t') {
		  $response['Vypraveni'] = array(
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
            $GLOBALS["soap"]["namespace_ess"].'AdresaElektronicka'=>array(
              $GLOBALS["soap"]["namespace_ess"].'Typ' => 'email',
              $GLOBALS["soap"]["namespace_ess"].'Kontakt' => $dokument['EMAIL'],
            ),
            $GLOBALS["soap"]["namespace_ess"].'AdresaDS'=>array(
              $GLOBALS["soap"]["namespace_ess"].'IdDb' => $dokument['DS'],
            ),
          ),
        ),
        $GLOBALS["soap"]["namespace_ess"].'ZasilkaInfo' => null,
      );
    }
    if ($dokument['ODES_TYP'] == 'M') {
      UNSET($response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaPostovni']);
      UNSET($response['Doruceni']['Odesilatel'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaDS']);
      UNSET($response['Vypraveni']['Adresat'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaPostovni']);
      UNSET($response['Vypraveni']['Adresat'][$GLOBALS["soap"]["namespace_ess"].'Adresa'][$GLOBALS["soap"]["namespace_ess"].'AdresaDS']);
    }

$odeslani = array_flip($GLOBALS["KONEKTOR"]["ISRZP"]["DRUH_ODESLANI"]);
//print_r($obalka);
  	if ($dokumentTyp=='f') {
		  $response['Doruceni']['ZasilkaInfo'] = array(
          'TypSubjektu'=>$dokument[TYP_ADR],
          'ZpusobManipulaceId'=>$odeslani[$dokument[ODESLANI]],
//            'IC'=>null,
//            'MistoNarozeni'=>null,
          'DruhZasilkyId'=>$dokument[JMENO],
          'DatumVypraveni'=>$dokument[DATUM_VYPRAVENI],
          //'Vaha'=>$dokument[OSLOVENI],
          //'Poplatek'=>$dokument[OSLOVENI],
          'IdZasilky'=>VratCarovyKod($id),
          'Poznamka'=>$dokument[POZNAMKA],
          'DatumDoruceni'=>$dokument[DATUM_DORUCENI],
          'dmID'=>$dokument[DS],
      );
    }
  	if ($dokumentTyp=='t') {
		  $response['Vypraveni']['ZasilkaInfo'] = array(
          'TypSubjektu'=>$dokument[TYP_ADR],
          'ZpusobManipulaceId'=>$odeslani[$dokument[ODESLANI]],
//            'IC'=>null,
//            'MistoNarozeni'=>null,
          'DruhZasilkyId'=>$dokument[JMENO],
          'DatumVypraveni'=>$dokument[DATUM_VYPRAVENI],
          //'Vaha'=>$dokument[OSLOVENI],
          //'Poplatek'=>$dokument[OSLOVENI],
          'IdZasilky'=>VratCarovyKod($id),
          'Poznamka'=>$dokument[POZNAMKA],
          'DatumDoruceni'=>$dokument[DATUM_DORUCENI],
          'dmID'=>$dokument[DS],
      );
    }


    $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
    $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);
    $pocet=0;
    while (list($key,$val)=@each($upload_records))
    {
      $pocet++;
      $soubor[]=new SoapVal(
        'dmFile',
        '',
        array(
    	   // 'dmEncodedContent'=>base64_encode($uplobj['table']->GetUploadFiles($val))
    	    'dmEncodedContent'=>''
        ),
        false,
        false,
        array(
          'dmMimeType'=>$val[TYPEFILE], //mimetype, nevyuziva se
          'dmFileGuid'=>$val[ID], //interni oznaceni dokumentu, nepouziva se v DS
//          'dmUpFileGuid'=>$$val[ID], //interni oznaceni dokumentu, nepouziva se v DS
          'dmFileDescr'=>TxtEncoding4Soap($val[NAME]), //popis souboru
        )
      );
    }
    $response['Soubory'] = $soubor;
  }

  if ($id) {
    $q = new DB_POSTA;
    $sql = 'select id from cis_posta_spisy where spis_id='.$id.' and dalsi_spis_id=0 order by id asc';
    $q->query($sql);
    $q->Next_Record();
    $id = $q->Record[ID];

	$response['DoplnujiciData']['IdSpisu'] = array(
     'Identifikator'=>array(
  		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$id,
	  		$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>'TmapEss',
		 ),
    );
  }



  if ($dokument['DALSI_ID_SPIS_AGENDA'] <> '') {
    list ($HodnotaIdExt, $ZdrojIdExt) = explode(':', $dokument['DALSI_ID_SPIS_AGENDA']);
  	$response['DoplnujiciData']['IdSpisu'] = array(
     'Identifikator'=>array(
  		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$HodnotaIdExt,
	  		$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>$ZdrojIdExt,
		 ),
    );
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
  		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$id_spis,
  			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>'TmapEss',
  		),
  		'Nazev'=>$dokument[VEC],
//  		'Popis'=>null,
  		'CisloJednaci'=>$dokument[CISLO_JEDNACI],
  		'SpisovaZnacka'=>$dokument[CISLO_SPISU],
  		'PodaciDenikPoradi'=>$dokument[EV_CISLO],
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
  
//   $response = array(
//     'DokumentZkracenyVlozeny'=>array(
//       'IdDokument'=>array(
//     		'Identifikator'=>array(
//     		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>null,
//     			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>null,
//     		),
//     	),
//   		'CisloJednaci'=>null,
//   		'PodaciDenikPoradi'=>null,
//   		'PodaciDenikRok'=>null,
//   		'PodaciDenik'=>null,
//   	),
//   );
  
  if ($id_spis) {
    $dokumenty_arr = VratDokumentyKeSpisuEed($id_spis);
    foreach($dokumenty_arr as $id)
//    if ($dokumenty_arr)
    {
      $dokument = VratDokumentInfo($id);
      $response[] = array(
          'IdDokument'=>array(
    		    'Identifikator'=>array(
        		  $GLOBALS["soap"]["namespace_ess"].'HodnotaID'=>$id,
        			$GLOBALS["soap"]["namespace_ess"].'ZdrojID'=>'TmapEss',
        		),
        	),
      		'CisloJednaci'=>$dokument[CISLO_JEDNACI],
      		'PodaciDenikPoradi'=>$dokument[EV_CISLO],
      		'PodaciDenikRok'=>$dokument[ROK],
  //   		'PodaciDenik'=>null,
      );
    }  
  }

  return $res;
}
?>