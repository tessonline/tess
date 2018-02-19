<?php
require_once(FileUp2('interface/.admin/soap_funkce.inc'));
require_once(FileUp2('.admin/status.inc'));
require_once(FileUp2('.admin/oth_funkce.inc'));
require_once(FileUp2('.admin/oth_funkce_2D.inc'));
require_once(FileUp2('.admin/upload_.inc'));

include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

$GLOBALS['status'] = getSelectDataEed(new of_select_status(array()));
$GLOBALS['jine'] = getSelectDataEed(new of_select_jine(array()));
$GLOBALS['typ_posty'] = getSelectDataEed(new of_select_typ_posty(array('selectfull'=>true)));


function _FormatujDatum( $datum = null )
{
  $strFormat = 'Y-m-d\TH:i:s.uP';
  $strFormat = 'Y-m-d\TH:i:s';
  if ($datum)
  {
    list($dat,$cas) = explode(' ',$datum);
    if (strpos($dat, '-') !== false) {
      list($rok,$mesic,$den) = explode('-',$dat);
    }
    else {
      list($rok,$mesic,$den) = explode('.',$dat);
    }
    list($hodina,$minuta,$sek) = explode(':',$cas);
    if (!$sek) $sek=00;
    $strDate = date( $strFormat , mktime($hodina,$minuta,$sek,$mesic,$den,$rok)) ;
    //$datum ? date( $strFormat, $datum );    
  }
  else
  {
    $strDate = date( $strFormat ) ;
  }
  return $strDate;
}


Function _GetSekce_DoplnujiciData(&$temp, $data = array()) {
  $ident = $temp->addChild('DoplnujiciData');
  $ident->addChild('PocetListu', $data['POCET_LISTU']);
  $ident->addChild('PocetPriloh', $data['POCET_PRILOH']);
  $ident->addChild('DruhPriloh', $data['DRUH_PRILOH']);
  $ident->addChild('OdesTyp', $data['ODES_TYP']);
  $ident->addChild('SkartaceID', $data['SKARTACE']);
  $ident->addChild('DatumPredani', $data['DATUM_PREDANI']);
  $ident->addChild('DatumPredaniVen', $data['DATUM_PREDANI_VEN']);
  $ident->addChild('TypDoc', $data['TYP_POSTY']);
  $ident->addChild('WhoisNumber', $data['WHOIS_NUMBER']);
  $ident->addChild('WhoisIdstudia', $data['WHOIS_IDSTUDIA']);
  $ident->addChild('TypDok', $data['TYP_DOKUMENTU']);
  $ident->addChild('OdeslEmail', $data['ODESL_EMAIL']);
  $ident->addChild('OdeslSubj', $data['ODESL_SUBJ']);
  $ident->addChild('OdeslBody', base64_encode($data['ODESL_BODY']));
  $ident->addChild('Vyrizeno', $data['VYRIZENO']);
  $ident->addChild('DatumVyrizeni', $data['DATUM_VYRIZENI']);

  return $temp;
}

Function _GetSekce_Subjekt(&$temp, $data = array()) {
  $typ = array('P'=>'Pravnicka','U'=>'Pravnicka','F'=>'Osvc','O'=>'Fyzicka');
  $typ_prepocet = $typ[$data['ODES_TYP']]?$typ[$data['ODES_TYP']]:'Neurceno';

  $obalSubjekt = $temp->addChild('Subjekt');
  
  $obalSubjekt = _GetSekce_Identifikace($obalSubjekt, $data);

  $obalSubjekt->addChild('PocetListu', $data['LISTU']);
  $obalSubjekt->addChild('TypSubjektu', $typ_prepocet); //Neurceno (Neurčeno slouží pouze pro případy); kdy není právní forma subjektu známa) Fyzicka Osvc Pravnicka Zamestnanec Utvar
  $obalSubjekt->addChild('ObchodniNazev', TxtEncoding4Soap($data['ODESL_PRIJMENI'])); //Benefity a. s. //Element se neuvádí pouze v případě že TypSubjektu="Fyzicka"
  $obalSubjekt->addChild('IC', $data['ODESL_ICO']);  //27095231 IČO se uvádí); pokud je subjektu IČO přiděleno a je v době pořízení záznamu známé
  $obalSubjekt->addChild('DatumNarozeni', $data['ODESL_DATNAR']); //Datum narození. Element se uvádí pouze v případě že TypSubjektu="Fyzicka" nebo TypSubjektu="Osvc" a to pouze v případě); že je nutné odlišit dvě osoby stejného jména a stejného trvalého bydliště.
  $obalSubjekt->addChild('Jmeno', TxtEncoding4Soap($data['ODESL_JMENO'])); //Element se neuvádí v případě TypSubjektu="Pravnicka" a value="Utvar"
  $obalSubjekt->addChild('Prijmeni', TxtEncoding4Soap($data['ODESL_PRIJMENI']));  //Element se neuvádí v případě že TypSubjektu="Pravnicka" a value="Utvar"
  $obalSubjekt->addChild('Osloveni', ''); //Element se neuvádí v případě že TypSubjektu="Pravnicka" a value="Utvar"
  $obalSubjekt->addChild('TitulPred', TxtEncoding4Soap($data['ODESL_TITUL']));  //Element se neuvádí v případě že TypSubjektu="Pravnicka" a value="Utvar"
  $obalSubjekt->addChild('TitulZa', TxtEncoding4Soap($data['ODESL_TITUL_ZA']));  //Element se neuvádí v případě že TypSubjektu="Pravnicka" a value="Utvar"
  $obalSubjekt->addChild('Poznamka', '');
  return $temp;
}

Function _GetSekce_Adresa(&$temp, $data = array()) {

  $res = array();
  
  $obalAdresa = $temp->addChild('Adresa');
  
  $AdresaPostovni = $obalAdresa->addChild('AdresaPostovni');
  $AdresaPostovni = _GetSekce_Identifikace($AdresaPostovni, $data);

  $AdresaPostovni->addChild('Obec', TxtEncoding4Soap($data['ODESL_POSTA'])); //Praha 8</Obec>
  $AdresaPostovni->addChild('CastObce', $data['']);
  $AdresaPostovni->addChild('MestskaCast', $data['']);
  $AdresaPostovni->addChild('Ulice', TxtEncoding4Soap($data['ODESL_ULICE']));  //Pobřežní
  $AdresaPostovni->addChild('EvidencniCislo', $data['']);
  $AdresaPostovni->addChild('OrientacniCislo', TxtEncoding4Soap($data['ODESL_COR'])); //3
  $AdresaPostovni->addChild('PopisneCislo', $data['ODESL_CP']); //620
  $AdresaPostovni->addChild('Psc', $data['ODESL_PSC']); //186 00
  $AdresaPostovni->addChild('Poznamka', '');
  $AdresaPostovni->addChild('POBOX', '');
  $AdresaPostovni->addChild('DodaciPosta', $data['']);

  $AdresaDS = $obalAdresa->addChild('AdresaDS');
  $AdresaDS->addChild('IdDb', ''); //Id datové schránky
  $AdresaDS->addChild('OrgUnitNum', ''); //Organizační jednotka hodnotou z číselníku
  $AdresaDS->addChild('OrgUnit', ''); //Organizační jednotka slovně
  
  $AdresaElektronicka = $obalAdresa->addChild('AdresaElektronicka');
  $AdresaElektronicka = _GetSekce_Identifikace($AdresaElektronicka, $data);

  $AdresaElektronicka->addChild('Typ', 'email'); //  tel nebo fax nebo mail
  $AdresaElektronicka->addChild('Kontakt', $data['ODESL_EMAIL']); //Hodnota elektronické adresy); např. telefonní číslo); nebo email adresa.

  
  if ($data['ODES_TYP']=='M') $res = array('AdresaElektronicka'=>$AdresaElektronicka);
  elseif ($data['VLASTNICH_RUKOU']=='9') $res = array('AdresaDS'=>$AdresaDS);
  else
    $res = array('AdresaPostovni'=>$AdresaPostovni);
  return $res;
}

Function _GetSekce_ZasilkaInfo(&$temp, $data = array()) {
  $ZpusobManipulaceId='';
  $ZpusobManipulaceText='';
  if ($GLOBALS['ODESLANA_POSTA']=='t') //odchozi dokument
  while (list($key,$val)=each($GLOBALS["CONFIG"]["TYP_ODESLANI"])) {
      $id=$val['VALUE'];
      if ($id == $data['VLASTNICH_RUKOU'])
        if ($val['UNISPIS']<>'') $ZpusobManipulaceId = $val['UNISPIS']; 
        else $ZpusobManipulaceText = $val['UNISPIS_TEXT'];
  }
  else
  { //prichozi dokument
    $zpusob_podani = array('1'=>'Psani','2'=>'Osobne','3'=>'ElektronickaPosta');
    $ZpusobManipulaceId = $zpusob_podani[$data['ZPUSOB_PODANI']];
  }

  $temp->addChild('ZpusobManipulaceId', $ZpusobManipulaceId); //Posta Osobne  VerejnaVyhlaska DetasovanaPosta Kuryr DorucovaciSluzba ElektronickaPosta Fax DalnopisTelegram Telefon UstneDoProtokolu  EPodatelnaNosic  EPodatelnaWeb EPodatelnaMail EPodatelnaMailElPodpis Rep DatovaSchranka
  $temp->addChild('ZpusobManipulaceText', $ZpusobManipulaceText); //Pojmenování způsobu manipulace. Tento prvek se použije pouze v případě); že nelze použít jednu z možností uvedenou ve výčtu možných hodnot položky "ZpusobManipulaceId".
  $temp->addChild('ZpusobZachazeniId', '');  //BezDoplnkoveSluzby Dodejka DodejkaModra DodejkaCervena Dodejka3D DodejkaModra3D DodejkaCervena3D Dodejka10D DodejkaModra10D DodejkaCervena10D Dodejka1M DodejkaModra1M DodejkaCervena1M
  $temp->addChild('ZpusobZachazeniText', ''); //Pojmenování způsobu zacházení se zásilkou. Tento prvek se použije pouze v případě); že nelze použít jednu z možností uvedenou ve výčtu možných hodnot položky "ZpusobZachazeniId".

  $temp->addChild('DruhZasilkyId', ''); //Balik CennePsani CennyBalik Psani SlepeckaZasilka PsaniStandard
  $temp->addChild('IdZasilky', ''); //762439
  $temp->addChild('DatumDoruceni', _FormatujDatum($data['DATUM_DORUCENI'])); //2010-07-22
  $temp->addChild('DatumVypraveni', _FormatujDatum($data['DATUM_VYPRAVENI']));

  return $temp;
}

Function _GetSekce_Soubory(&$temp, $data = array()) {
  $ident = $temp->addChild('Soubory');
//  return $temp;

  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($data['ID'], '', true);

  while (list($key,$val)=@each($upload_records)) {
    if ($val[ID]) {

      $dmFile = $ident->addChild('dmFile');
      $dmFile->addAttribute('dmMimeType', $val[TYPEFILE]);

      $dmFile->addAttribute('dmFinalniVerze', ($val[ID_H] <> '' ? 'N' : 'A'));
      $dmFile->addAttribute('dmFileMetaType', ($pocet==1)?'main':'enclosure'); //druh pisemnosti, prvni musi byt typ main!
      $dmFile->addAttribute('dmFileGuid', $val[ID]); //interni oznaceni dokumentu, nepouziva se v DS
      $dmFile->addAttribute('dmUpFileGuid', $$val[ID]); //interni oznaceni dokumentu, nepouziva se v DS
      $dmFile->addAttribute('dmFileDescr', TxtEncoding4Soap($val[NAME])); //popis souboru
      $dmFile->addAttribute('dmFormat', $Format); //nepovinne,

      $dmFile->addChild('dmEncodedContent', base64_encode($uplobj['table']->GetUploadFiles($val)));
    }

  }
  return $temp;
}

Function _GetSekce_Identifikace(&$temp, $data = array()) {
  $ident = $temp->addChild('Identifikator');
  $ident->addChild('HodnotaID', $data['ID']);
  $ident->addChild('ZdrojID', $data['ZdrojID'] ? $data['ZdrojID'] : 'TmapEss');
 return $temp;
}

Function GetPoleDokument(&$doc, $id) {
  $q = new DB_POSTA;
  $qTemp = new DB_POSTA;

  $dokument = $doc->addChild('Dokument');
  $sql = 'select * from posta where id='.$id;
  $q->query($sql);
  $q->Next_Record();
  $data = $q->Record;

  $EedDoc = LoadClass('EedDokument', $id);
  $skartace = Skartace_Pole($data['SKARTACE']);

  $dokument = _GetSekce_Identifikace($dokument, $data);
  $dokument->addChild('Nazev', TxtEncoding4Soap($data['VEC']));
  $dokument->addChild('CisloJednaci', TxtEncoding4Soap($EedDoc->cislo_jednaci));
  $dokument->addChild('PodaciDenikPoradi', $data['EV_CISLO']);
  $dokument->addChild('PodaciDenikRok', $data['ROK']);
  $dokument->addChild('DatumCasVytvoreni', _FormatujDatum($data['DATUM_PODATELNA_PRIJETI']));
  $dokument->addChild('TypDokumentu', TxtEncoding4Soap($GLOBALS['typ_posty'][$data['TYP_POSTY']]));
  $dokument->addChild('SpisovyZnak', $skartace['kod']);
  $dokument->addChild('SkartacniZnak', $skartace['znak']);
  $dokument->addChild('SkartacniLhuta', $skartace['doba']);
  $dokument->addChild('Poznamka', TxtEncoding4Soap($data['POZNAMKA']));


  _GetSekce_DoplnujiciData(&$dokument, $data);


  if ($data['ODESLANA_POSTA']=='f') {
    $doruceni = $dokument->addChild('Doruceni');
    $Odesilatel = $doruceni->addChild('Odesilatel');
    $Odesilatel = _GetSekce_Subjekt($Odesilatel, $data);
    $Odesilatel = _GetSekce_Adresa($Odesilatel, $data);

    $zasilkaInfo = $doruceni->addChild('ZasilkaInfo');
    $zasilkaInfo = _GetSekce_ZasilkaInfo($zasilkaInfo, $data);
  }
  else {
    $vypraveni = $dokument->addChild('Vypraveni');
    $Adresat = $vypraveni->addChild('Adresat');
    $Adresat = _GetSekce_Subjekt($Adresat, $data);
    $Adresat = _GetSekce_Adresa($Adresat, $data);

    $zasilkaInfo = $vypraveni->addChild('ZasilkaInfo');
    $zasilkaInfo = _GetSekce_ZasilkaInfo($zasilkaInfo, $data);
  }

  /*
  $sql = 'select * from posta where cislo_spisu1='.$data['CISLO_SPISU1'].' and cislo_spisu2='.$data['CISLO_SPISU2'].' and main_doc=0 order by id desc';
  $qTemp->query($sql);
  while ($qTemp->Next_Record()) {
    $dalsiData = $qTemp->Record;
    if ($dalsiData['ODESLANA_POSTA']=='f') {
      $doruceni = $dokument->addChild('Doruceni');
      $Odesilatel = $doruceni->addChild('Odesilatel');
      $Odesilatel = _GetSekce_Subjekt($Odesilatel, $dalsiData);
      $Odesilatel = _GetSekce_Adresa($Odesilatel, $dalsiData);

      $zasilkaInfo = $doruceni->addChild('ZasilkaInfo');
      $zasilkaInfo = _GetSekce_ZasilkaInfo($zasilkaInfo, $dalsiData);
    }
    else {
      $vypraveni = $dokument->addChild('Vypraveni');
      $Adresat = $vypraveni->addChild('Adresat');
      $Adresat = _GetSekce_Subjekt($Adresat, $dalsiData);
      $Adresat = _GetSekce_Adresa($Adresat, $dalsiData);

      $zasilkaInfo = $vypraveni->addChild('ZasilkaInfo');
      $zasilkaInfo = _GetSekce_ZasilkaInfo($zasilkaInfo, $dalsiData);
    }

  }
  */
   _GetSekce_Soubory(&$dokument, $data);

  return $doc;
};



Function GetPoleSpis(&$doc, $id) {
	$q = new DB_POSTA;
	$qTemp = new DB_POSTA;

	$spis = $doc->addChild('Spis');
	$sql = 'select * from cis_posta_spisy where spis_id=' . $id .' and (dalsi_spis_id=0 or dalsi_spis_id='.$id.')';
	$q->query($sql);
	$q->Next_Record();
	$spis_array = $q->Record;
	$sql = 'select * from posta where id='.$id;
	$q->query($sql);
	$q->Next_Record();
	$data = $q->Record;

	$skartace = Skartace_Pole($data['SKARTACE']);

	$spis = _GetSekce_Identifikace($spis, $data);
	$spis->addChild('Nazev', TxtEncoding4Soap($spis_array['NAZEV_SPISU']));
	$spis->addChild('SpisovaZnacka', TxtEncoding4Soap($spis_array['PUVODNI_SPIS']));
	$spis->addChild('DatumCasVytvoreni', _FormatujDatum($data['DATUM_PODATELNA_PRIJETI']));
	$spis->addChild('SpisovyZnak', $skartace['kod']);
	$spis->addChild('SkartacniZnak', $skartace['znak']);
	$spis->addChild('SkartacniLhuta', $skartace['doba']);
	$spis->addChild('Poznamka', TxtEncoding4Soap($data['POZNAMKA']));

	$VlozeneDokumenty = $spis->addChild('VlozeneDokumenty');
// 	$dokumenty = $VlozeneDokumenty->addChild('Dokumenty');
    $VlozenyDokument = $VlozeneDokumenty->addChild('VlozenyDokument'); 
//	_GetSekce_DoplnujiciData(&$dokument, $data);
	
	$eed = LoadClass('EedCj', $id);
	$docs = $eed->getDocsInCJ($id);
  sort($docs, SORT_NUMERIC);
  //$docs = asort($docs);
	foreach ($docs as $doc_id) {
		GetPoleDokument(&$VlozenyDokument, $doc_id);
	
	}
	
	return $doc;
};

function getXMLDoc ($id) {
	$xmlstr = <<<XML
<?xml version='1.0'?>
<root>
</root>
XML;
	
	$doc = @new SimpleXMLElement($xmlstr);
    $q = new DB_POSTA;
	$sql = 'select * from cis_posta_spisy where spis_id=' . $id;
    $q->query($sql);
    if ($q->Num_Rows()>0) {
      GetPoleSpis($doc, $id);      		    	
    }
	else {
	  $dokumenty = $doc->addChild('Dokumenty');
		$eed = LoadClass('EedCj', $id);
		$docs = $eed->getDocsInCJ($id);
		foreach ($docs as $doc_id) {
  		GetPoleDokument($dokumenty, $doc_id);
			
		}
		
	}
	$res = $doc->asXML(); 
	$res = html_entity_decode($res, 0, 'UTF-8');
	
	return $res;
}
