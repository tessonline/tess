<?php

function ValueIsNull($value) {
  if (is_array($value)) {
    if (sizeof($value) > 0) {
      return false;
    } else {
      return true;
    }
  } else {
    if (($value != '') && (strtolower($value) != 'null') && (strlen(trim($value)) > 0)) {
      return false;
    } else {
      return true;
    }
  }
}

function SetAttr2DB($value, $type) {
  if ($value == 'NULL') return $value; 
   
  $value = str_replace("'", '', $value);
  if ($type == 'T') {
    $value = trim($value);
    if ($value) {
      $value = "'$value'";
    }
    else 
      $value = "''";
  }
  //if ($type == 'N') {}
  
	return $value;
}

function ExistujeSpis(&$id, $dalsi_id_spis_agenda, $dalsi_id_spis_ident, $where_add = '') {
  $res = false;
  $id = 0;
  
  if ($dalsi_id_spis_agenda) {
    $q = new DB_POSTA;
    $ident = $dalsi_id_spis_ident . ":" . $dalsi_id_spis_agenda;
    $sql = "SELECT id FROM posta WHERE dalsi_id_spis_agenda = '$ident' and stornovano is null $where_add";
//    echo "SQL: " . $sql;
    $q->query($sql);
    if ($q->Next_Record()) {
      $id = $q->Record["ID"];
      $res = true;
    }
  }
  
	return $res;
}

function SpisDokumentZalozeni($request_ProfilSpisu, $request_DokumentyVlozene, $request_autorizace, &$id_spis, &$msg_popis) {
  $res = true;
  //test, zda existuje spis
  if (ExistujeSpis($id_spis,$request_ProfilSpisu['Identifikator']['HodnotaID'],$request_ProfilSpisu['Identifikator']['ZdrojID']))
    $msg_popis = NastavPopis('SpisZalozeni','1000');
  //zalozeni
  else {
    //zpracovani dokumentu
    $res = SpisDokumentZpracovani($request_DokumentyVlozene, $request_autorizace, $id, $msg_popis);
    $id_spis = $id;
    
    //Vytvoreni spisu
    if ($res) {
      $res = UlozSpisDokumentInfo($id_spis, $request_ProfilSpisu['Identifikator']['HodnotaID'], $request_ProfilSpisu['Identifikator']['ZdrojID'], $q);
    
      if ($res) {
        NastavStatus($id_spis,VratReferenta($request_autorizace));
        $msg_popis = NastavPopis('SpisZalozeni','0000');
      }
      else
        $msg_popis = NastavPopis('SpisZalozeni','1001','',$q->Error);
    }
    else 
      $msg_popis = NastavPopis('SpisZalozeni','1002',$msg_popis["Popis"],$msg_popis["ErrSql"]);
  }
    
  return $res;
}	

function SpisDokumentZpracovani($request, $request_autorizace, &$id, &$msg_popis) {
  $res = true;
  
  /*
  //element - DokumentUplnyVlozeny
  if (array_key_exists('DokumentUplnyVlozeny', $request)) {
    //element - DorucenyDokument
    if (array_key_exists('DorucenyDokument', $request['DokumentUplnyVlozeny'])) {
      $DorucenyDokument = $request['DokumentUplnyVlozeny']['DorucenyDokument'];

      //Zalozeni dokumentu
      $res = DokumentZalozeni($DorucenyDokument, 'f', $request_autorizace, $id, $msg_popis);
    }
    
    //element - VlastniDokument
    if (array_key_exists('VlastniDokument', $request['DokumentUplnyVlozeny'])) {
      $VlastniDokument = $request['DokumentUplnyVlozeny']['VlastniDokument'];
      
      //Zalozeni dokumentu
      $res = DokumentZalozeni($VlastniDokument, 't', $request_autorizace, $id, $msg_popis); 
    }
  }
  */
  $res = DokumentZalozeni($request['DokumentUplnyVlozeny'], 't', $request_autorizace, $id, $msg_popis);

  //element - DokumentIdVlozeny
  if (array_key_exists('DokumentIdVlozeny', $request)) {
    $DokumentIdVlozeny = $request['DokumentIdVlozeny'];
    
    if (ExistujeDokument($id,$DokumentIdVlozeny['IdDokument']['Identifikator']['HodnotaID'],$DokumentIdVlozeny['IdDokument']['Identifikator']['ZdrojID'])) {
      $res = true;
    }
    else {
      $res = false;
      $msg_popis = NastavPopis('DokumentZalozeni','1002');
    }
  }
  
  return $res;
}  

function UlozSpisDokumentInfo($id_spis, $dalsi_id_spis_agenda, $dalsi_id_spis_ident, &$q) {
  $res = true;
  
  if (!$q) $q = new DB_POSTA;
  $q->ShowError = false;
	$q->Error_Die = false;
	if (!$dalsi_id_spis_agenda) $dalsi_id_spis_agenda = $id_spis;
	$ident = $dalsi_id_spis_ident . ':' . $dalsi_id_spis_agenda;

  $cj_obj = new EedCj($id_spis);
  $cj_info = $cj_obj->GetCjInfo($id_spis);
  $ns = $cj_info['CELE_CISLO'];

  if ($cj_obj->spis_id <> $lastid) $uloz = $cj_obj->spis_id;
  else $uloz = $id_spis;

  $sql = "INSERT INTO CIS_POSTA_SPISY (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID,NAZEV_SPISU) VALUES ".
        "('$ns', '$ns', ".$uloz.", 0,'$LAST_DATE','$LAST_TIME',$LAST_USER_ID,$LAST_USER_ID,'".$GLOBALS['SpisCreateButton']."')";

  if ($q->query($sql)) {
    $text = 'Byl zaloľen spis <b>' . $spis_nazev . '</b>';
    EedTransakce::ZapisLog($lastid, $text, 'DOC', $id_user);
    EedTransakce::ZapisLog($uloz, $text, 'SPIS', $id_user);
  }
  else {
    $res = false;
  }
	
	return $res;
}	

function ExistujeDokument(&$id, $dalsi_id_agenda = 0, $dalsi_id_ident = '', $where_add = '') {
  $res = false;
  $id = 0;
//  if ($dalsi_id_agenda) 
  {
    $q = new DB_POSTA;

    $ident = $dalsi_id_ident . ":" . $dalsi_id_agenda;

    if ($dalsi_id_agenda>0)
      $sql = "SELECT id FROM posta WHERE dalsi_id_agenda = '$ident' and stornovano is null $where_add";
    else
      $sql = "SELECT id FROM posta WHERE stornovano is null $where_add";
    $q->query($sql);
    if ($q->Next_Record()) {
      $id = $q->Record["ID"];
      $res = true;
    }
  }
  
	return $res;
}

function DokumentZalozeni($request, $smer, $request_autorizace, &$id, &$msg_popis) {
  $res = false;
  
  if (array_key_exists('Doruceni', $request)) $smer = 'f';
  if (array_key_exists('Vypraveni', $request)) $smer = 't';
  //test, zda existuje dokument
  if (ExistujeDokument($id,$request['Identifikator']['HodnotaID'],$request['Identifikator']['ZdrojID']," AND referent = " . VratReferenta($request_autorizace) . " AND odeslana_posta = '$smer'"))
    $msg_popis = NastavPopis('DokumentZalozeni','1000');
  //zalozeni
  else {
    $dokument = NastavDokument($request);
    if (ValueIsNull($dokument["vec"])) $dokument["vec"] = NastavText('DokumentZalozeni','001');
    if (ValueIsNull($dokument["ev_cislo"])) $dokument["ev_cislo"] = 0;
    if (ValueIsNull($dokument["rok"])) $dokument["rok"] = Date('Y');
    if (ValueIsNull($dokument["datum_podatelna_prijeti"])) $dokument["datum_podatelna_prijeti"] = '01.01.2100 12:00';
    if (ValueIsNull($dokument["odes_typ"])) $dokument["odes_typ"] = '';
    $dokument["stav"] = $GLOBALS["KONEKTOR"]["ISRZP"]["STAV"]+2;
    $dokument["odeslana_posta"] = $smer;
//    $dokument["odbor"] = $GLOBALS["KONEKTOR"]["ISRZP"]["ODBOR"];
    $ref_odbor = OdborPrac(VratReferenta($request_autorizace));
    //print_r($ref_odbor);
    $dokument["odbor"] = $ref_odbor['odbor']?$ref_odbor['odbor']:$GLOBALS["KONEKTOR"]["ISRZP"]["ODBOR"];
    
    $dokument["oddeleni"] = $ref_odbor['oddeleni']?$ref_odbor['oddeleni']:$GLOBALS["KONEKTOR"]["ISRZP"]["ODDELENI"];
    $dokument["referent"] = VratReferenta($request_autorizace);
    $res = UlozDokumentInfo($id, $dokument, $q);
    
    if ($res) {
      NastavStatus($id,VratReferenta($request_autorizace));
      $msg_popis = NastavPopis('DokumentZalozeni','0000');
    }
    else {
      $msg_popis = NastavPopis('DokumentZalozeni','1001','',$q->Error);
    }
  }
  
  return $res;
}

function NastavDokument($request, $request_Odesilatel = false, $request_ZasilkaInfo = false) {
  $odes_typ = array(
    'Fyzicka' => 'O',
    'Pravnicka' => 'P',
    'Osvc' => 'F',
    'Zamestnanec' => 'F',
    'Utvar' => 'P',
    'Neurceno' => ''
  );
  if (!$request_Odesilatel) $request_Odesilatel = $request['Doruceni']['Odesilatel'];
  if (!$request_ZasilkaInfo) $request_ZasilkaInfo = $request['Doruceni']['ZasilkaInfo'];
  $dokument = array();
  // >> Identifikator
    if (!ValueIsNull($request['Identifikator']['HodnotaID'])) $dokument["dalsi_id_agenda"] = TxtEncodingFromSoap($request['Identifikator']['ZdrojID'].":".$request['Identifikator']['HodnotaID']);
    //ZdrojID
    
  if (!ValueIsNull($request['Nazev'])) $dokument["vec"] = TxtEncodingFromSoap($request['Nazev']);
  //Popis
  //CisloJednaci
  //SpisovaZnacka
  if (!ValueIsNull($request['PodaciDenikPoradi'])) $dokument["ev_cislo"] = $request['PodaciDenikPoradi'];
  if (!ValueIsNull($request['PodaciDenikRok'])) $dokument["rok"] = $request['PodaciDenikRok'];
  //PodaciDenik
  if (!ValueIsNull($request['DatumCasVytvoreni'])) $dokument["datum_podatelna_prijeti"] = ConvertDatumToString($request['DatumCasVytvoreni']);
  //TypDokumentu
  //SpisovyPlan
  if (!ValueIsNull($request['SpisovyZnak'])) $dokument["spis_znak"] = $request['SpisovyZnak'];
  if (!ValueIsNull($request['SkartacniZnak'])) $dokument["skar_znak"] = $request['SkartacniZnak'];
  if (!ValueIsNull($request['SkartacniLhuta'])) $dokument["skar_lhuta"] = $request['SkartacniLhuta'];
  if (!ValueIsNull($request['Poznamka'])) $dokument["poznamka"] = TxtEncodingFromSoap($request['Poznamka']);

  // >> Doruceni
    // >> Doruceni - Odesilatel
      // >> Doruceni - Odesilatel - Subjekt
        // >> Doruceni - Odesilatel - Subjekt - Identifikator
          //HodnotaID
          //ZdrojID
      if (!ValueIsNull($request_Odesilatel['Subjekt']['TypSubjektu'])) $dokument["odes_typ"] = $odes_typ[TxtEncodingFromSoap($request_Odesilatel['Subjekt']['TypSubjektu'])];
      if (!ValueIsNull($request_Odesilatel['Subjekt']['ObchodniNazev'])) $dokument["odesl_prijmeni"] = TxtEncodingFromSoap($request_Odesilatel['Subjekt']['ObchodniNazev']);
      //IC
      if (!ValueIsNull($request_Odesilatel['Subjekt']['IC'])) $dokument["odesl_ico"] = TxtEncodingFromSoap($request_Odesilatel['Subjekt']['IC']);
      //DatumNarozeni
      if (!ValueIsNull($request_Odesilatel['Subjekt']['DatumNarozeni'])) $dokument["odesl_datnar"] = ConvertDatumToXML($request_Odesilatel['Subjekt']['DatumNarozeni']);
      //DatumNarozeni
      //MistoNarozeni
      if (ValueIsNull($request_Odesilatel['Subjekt']['ObchodniNazev'])) {
        if (!ValueIsNull($request_Odesilatel['Subjekt']['Jmeno'])) $dokument["odesl_jmeno"] = TxtEncodingFromSoap($request_Odesilatel['Subjekt']['Jmeno']);
        if (!ValueIsNull($request_Odesilatel['Subjekt']['Prijmeni'])) $dokument["odesl_prijmeni"] = TxtEncodingFromSoap($request_Odesilatel['Subjekt']['Prijmeni']);
      }
      //Osloveni
      //TitulPred
      //TitulZa
      //FunkceUtvarPopis
      //FunkceUtvarIdentifikator
      //Poznamka

      // >> Doruceni - Odesilatel - Adresa
        // >> Doruceni - Odesilatel - Adresa - AdresaPostovni
          // >> Doruceni - Odesilatel - Adresa - AdresaPostovni - Identifikator
            //HodnotaID
            //ZdrojID

          //identifikator ISDS
          if (!ValueIsNull($request_Odesilatel['Adresa']['AdresaDS']['IdDb'])) $dokument["odesl_datschranka"] = TxtEncodingFromSoap($request_Odesilatel['Adresa']['AdresaDS']['IdDb']);
          
          if (!ValueIsNull($request_Odesilatel['Adresa']['AdresaPostovni']['Obec'])) $dokument["odesl_posta"] = TxtEncodingFromSoap($request_Odesilatel['Adresa']['AdresaPostovni']['Obec']);
          //CastObce
          //MestskaCast
          if (!ValueIsNull($request_Odesilatel['Adresa']['AdresaPostovni']['Ulice'])) $dokument["odesl_ulice"] = TxtEncodingFromSoap($request_Odesilatel['Adresa']['AdresaPostovni']['Ulice']);
          //EvidencniCislo
          if (!ValueIsNull($request_Odesilatel['Adresa']['AdresaPostovni']['OrientacniCislo'])) $dokument["odesl_cor"] = TxtEncodingFromSoap($request_Odesilatel['Adresa']['AdresaPostovni']['OrientacniCislo']);
          if (!ValueIsNull($request_Odesilatel['Adresa']['AdresaPostovni']['PopisneCislo'])) $dokument["odesl_cp"] = TxtEncodingFromSoap($request_Odesilatel['Adresa']['AdresaPostovni']['PopisneCislo']);
          if (!ValueIsNull($request_Odesilatel['Adresa']['AdresaPostovni']['Psc'])) $dokument["odesl_psc"] = TxtEncodingFromSoap($request_Odesilatel['Adresa']['AdresaPostovni']['Psc']);
          //Zeme
          //RuianVazba
          //Poznamka
          //POBOX
          //TypAdresy
          //DodaciPosta
          //Okres
          
        // >> Doruceni - Odesilatel - Adresa - AdresaDS
        
        // >> Doruceni - Odesilatel - Adresa - AdresaElektronicka
      
    // >> Doruceni - ZasilkaInfo
    if (!ValueIsNull($request_ZasilkaInfo['ZpusobManipulaceId'])) $dokument["vlastnich_rukou"] = $GLOBALS["KONEKTOR"]["ISRZP"]["DRUH_ODESLANI"][TxtEncodingFromSoap($request_ZasilkaInfo['ZpusobManipulaceId'])];
    if (!ValueIsNull($request_ZasilkaInfo['ZpusobZachazeniId'])) {
      $dokument["doporucene"] = $GLOBALS["KONEKTOR"]["ISRZP"]["TYP_ODESLANI"][TxtEncodingFromSoap($request_ZasilkaInfo['ZpusobZachazeniId'])]["DOPORUCENE"];
      $dokument["obalka_nevracet"] = $GLOBALS["KONEKTOR"]["ISRZP"]["TYP_ODESLANI"][TxtEncodingFromSoap($request_ZasilkaInfo['ZpusobZachazeniId'])]["OBALKA_NEVRACET"];
      $dokument["obalka_10dni"] = $GLOBALS["KONEKTOR"]["ISRZP"]["TYP_ODESLANI"][TxtEncodingFromSoap($request_ZasilkaInfo['ZpusobZachazeniId'])]["OBALKA_10DNI"];
    }
  
  // >> DoplnujiciData
    if (!ValueIsNull($request['DoplnujiciData']['PocetListu'])) $dokument["pocet_listu"] = $request['DoplnujiciData']['PocetListu'];
    if (!ValueIsNull($request['DoplnujiciData']['PocetPriloh'])) $dokument["pocet_priloh"] = $request['DoplnujiciData']['PocetPriloh'];
    if (!ValueIsNull($request['DoplnujiciData']['DruhPriloh'])) $dokument["druh_priloh"] = TxtEncodingFromSoap($request['DoplnujiciData']['DruhPriloh']);
  
  return $dokument;
}

function UlozDokumentInfo(&$id, $dokument, &$q, $type_sql = 'insert') //$type_sql -> insert || update
{
  $res = true;
  
  if (!$q) $q = new DB_POSTA;
  $q->ShowError = false;
	$q->Error_Die = false;
  $sql_field_arr = array();
  if (array_key_exists('dalsi_id_agenda', $dokument)) $sql_field_arr["dalsi_id_agenda"] = SetAttr2DB($dokument["dalsi_id_agenda"],'T');
  if (array_key_exists('ev_cislo', $dokument)) $sql_field_arr["ev_cislo"] = SetAttr2DB($dokument["ev_cislo"],'N');
  if (array_key_exists('stav', $dokument)) $sql_field_arr["stav"] = SetAttr2DB($dokument["stav"],'N');
  if (array_key_exists('rok', $dokument)) $sql_field_arr["rok"] = SetAttr2DB($dokument["rok"],'T');
  if (array_key_exists('odes_typ', $dokument)) $sql_field_arr["odes_typ"] = SetAttr2DB($dokument["odes_typ"],'T');
  if (array_key_exists('odesl_prijmeni', $dokument)) $sql_field_arr["odesl_prijmeni"] = SetAttr2DB($dokument["odesl_prijmeni"],'T');
  if (array_key_exists('odesl_jmeno', $dokument)) $sql_field_arr["odesl_jmeno"] = SetAttr2DB($dokument["odesl_jmeno"],'T');
  if (array_key_exists('vec', $dokument)) $sql_field_arr["vec"] = SetAttr2DB($dokument["vec"],'T');
  if (array_key_exists('datum_podatelna_prijeti', $dokument)) $sql_field_arr["datum_podatelna_prijeti"] = SetAttr2DB($dokument["datum_podatelna_prijeti"],'T');
  if (array_key_exists('odeslana_posta', $dokument)) $sql_field_arr["odeslana_posta"] = SetAttr2DB($dokument["odeslana_posta"],'T');
  if (array_key_exists('odbor', $dokument)) $sql_field_arr["odbor"] = SetAttr2DB($dokument["odbor"],'N');
  if (array_key_exists('oddeleni', $dokument)) $sql_field_arr["oddeleni"] = SetAttr2DB($dokument["oddeleni"],'T');
  if (array_key_exists('referent', $dokument)) $sql_field_arr["referent"] = SetAttr2DB($dokument["referent"],'N');
  
  if (array_key_exists('pocet_listu', $dokument)) $sql_field_arr["pocet_listu"] = SetAttr2DB($dokument["pocet_listu"],'N');
  if (array_key_exists('pocet_priloh', $dokument)) $sql_field_arr["pocet_priloh"] = SetAttr2DB($dokument["pocet_priloh"],'N');
  if (array_key_exists('druh_priloh', $dokument)) $sql_field_arr["druh_priloh"] = SetAttr2DB($dokument["druh_priloh"],'T');
  
  if (array_key_exists('odesl_posta', $dokument)) $sql_field_arr["odesl_posta"] = SetAttr2DB($dokument["odesl_posta"],'T');
  if (array_key_exists('odesl_datnar', $dokument)) $sql_field_arr["odesl_datnar"] = SetAttr2DB($dokument["odesl_datnar"],'T');
  if (array_key_exists('odesl_ico', $dokument)) $sql_field_arr["odesl_ico"] = SetAttr2DB($dokument["odesl_ico"],'T');
  if (array_key_exists('odesl_ulice', $dokument)) $sql_field_arr["odesl_ulice"] = SetAttr2DB($dokument["odesl_ulice"],'T');
  if (array_key_exists('odesl_cor', $dokument)) $sql_field_arr["odesl_cor"] = SetAttr2DB($dokument["odesl_cor"],'T');
  if (array_key_exists('odesl_cp', $dokument)) $sql_field_arr["odesl_cp"] = SetAttr2DB($dokument["odesl_cp"],'T');
  if (array_key_exists('odesl_psc', $dokument)) $sql_field_arr["odesl_psc"] = SetAttr2DB($dokument["odesl_psc"],'T');
  
  if (array_key_exists('odesl_datschranka', $dokument)) $sql_field_arr["odesl_datschranka"] = SetAttr2DB($dokument["odesl_datschranka"],'T');

  if (array_key_exists('cislo_jednaci1', $dokument)) $sql_field_arr["cislo_jednaci1"] = SetAttr2DB($dokument["cislo_jednaci1"],'N');
  if (array_key_exists('cislo_jednaci2', $dokument)) $sql_field_arr["cislo_jednaci2"] = SetAttr2DB($dokument["cislo_jednaci2"],'N');
  if (array_key_exists('cislo_spisu1', $dokument)) $sql_field_arr["cislo_spisu1"] = SetAttr2DB($dokument["cislo_spisu1"],'N');
  if (array_key_exists('cislo_spisu2', $dokument)) $sql_field_arr["cislo_spisu2"] = SetAttr2DB($dokument["cislo_spisu2"],'N');  
  if (array_key_exists('id_puvodni', $dokument)) $sql_field_arr["id_puvodni"] = SetAttr2DB($dokument["id_puvodni"],'N');
  
  if (array_key_exists('vlastnich_rukou', $dokument)) $sql_field_arr["vlastnich_rukou"] = SetAttr2DB($dokument["vlastnich_rukou"],'T');
  if (array_key_exists('doporucene', $dokument)) $sql_field_arr["doporucene"] = SetAttr2DB($dokument["doporucene"],'T');
  if (array_key_exists('obalka_nevracet', $dokument)) $sql_field_arr["obalka_nevracet"] = SetAttr2DB($dokument["obalka_nevracet"],'N');
  if (array_key_exists('obalka_10dni', $dokument)) $sql_field_arr["obalka_10dni"] = SetAttr2DB($dokument["obalka_10dni"],'N');
  if (array_key_exists('skartace', $dokument)) $sql_field_arr["skartace"] = SetAttr2DB($dokument["skartace"],'N');
  //print_r($dokument);
  if ($type_sql=='insert' && $sql_field_arr["odes_typ"]=="''")
  {
    $sql_field_arr["odes_typ"] = "'Z'";
    $sql_field_arr["odesl_prijmeni"] = TxtEncodingFromSoap("'VlastnĂ­ zĂĄznam'");
    $sql_field_arr["odesl_prijmeni"] = TxtEncodingFromSoap("'VlastnĂ­ zĂĄznam'");
    $sql_field_arr["doporucene"] = "'X'" ;
    $sql_field_arr["vlastnich_rukou"] = "'0'" ;
  }
  
  //skartace
  if (array_key_exists('spis_znak', $dokument)) {
    $sql_skartace = "select * from cis_posta_skartace where text like '" . $dokument["spis_znak"] . "%'";
    $q->query($sql_skartace);
    $pocet = $q->Num_Rows();
    //skartace existuje
    if ($pocet>0) {
      $q->Next_Record();
      $id_skartace = $q->Record["ID"];
      $sql_field_arr["skartace"] = SetAttr2DB($id_skartace,'N');
      
      //oprava
      $sql_skartace_field_arr = array();
      if (array_key_exists('skar_znak', $dokument) && ($q->Record["SKAR_ZNAK"]<>$dokument["skar_znak"])) $sql_skartace_field_arr["skar_znak"] = SetAttr2DB($dokument["skar_znak"],'T');
      if (array_key_exists('skar_lhuta', $dokument) && ($q->Record["DOBA"]<>$dokument["skar_lhuta"])) $sql_skartace_field_arr["doba"] = SetAttr2DB($dokument["skar_lhuta"],'N');
      if (count($sql_skartace_field_arr)>0) {
        $oddelovac = '';
        $sql_field_value = '';
        foreach ($sql_skartace_field_arr as $field  =>  $value) {
          $sql_field_value .=  $oddelovac.$field.' = ' . $value;
          $oddelovac = ',';
        } 
        $sql = "update cis_posta_skartace set $sql_field_value where id = $id_skartace;";
        //echo "sql: " . $sql;die();
        
        if ($q->query($sql)) {
        }
        else {
          $res = false;
          return $res;
        }
      }
    }
    //skartace neexistuje, nutno vytvorit
    else {
      $sql_skartace_field_arr = array();
      if (array_key_exists('spis_znak', $dokument)) {
        $kod_skartace_arr = explode(" . ", $dokument["spis_znak"]);
        $sql_skartace_field_arr["kod"] = SetAttr2DB((int) $kod_skartace_arr[0],'N');
        $sql_skartace_field_arr["text"] = SetAttr2DB($dokument["spis_znak"],'T');
      }
      if (array_key_exists('skar_znak', $dokument)) $sql_skartace_field_arr["skar_znak"] = SetAttr2DB($dokument["skar_znak"],'T');
      if (array_key_exists('skar_lhuta', $dokument)) $sql_skartace_field_arr["doba"] = SetAttr2DB($dokument["skar_lhuta"],'N');
      $sql_skartace_field_arr["aktivni"] = SetAttr2DB(1,'N');
      
      $oddelovac = '';
      $sql_field = '';
      $sql_value = '';
      foreach ($sql_skartace_field_arr as $field  =>  $value) {
        $sql_field .=  $oddelovac.$field;
        $sql_value .=  $oddelovac.$value;
        $oddelovac = ',';
      } 
      $sql = "insert into cis_posta_skartace ($sql_field) values ($sql_value);";
      //echo "sql: " . $sql;die();
      
      if ($q->query($sql)) {
        $sql_field_arr["skartace"] = $q->getlastid("cis_posta_skartace", "ID");
      }
      else {
        $res = false;
        return $res;
      }
    }
  }
  NastavInfo($insert_fields, $insert_values, $update_set, $sql_field_arr["referent"]); 
    
  //insert sql
  if ($type_sql == 'insert') {
    $oddelovac = '';
    $sql_field = '';
    $sql_value = '';
    foreach ($sql_field_arr as $field  =>  $value) {
      $sql_field .=  $oddelovac.$field;
      $sql_value .=  $oddelovac.$value;
      $oddelovac = ',';
    } 
    $ref = $sql_field_arr["referent"]?$sql_field_arr["referent"]:0;
    $sql = "insert into posta ($sql_field $insert_fields,owner_id) values ($sql_value $insert_values,$ref);";
    if ($q->query($sql)) {
      $id = $q->getlastid("posta", "ID");
      $sql = "update posta set dalsi_id_agenda = id where id = $id and dalsi_id_agenda is null;";
      $q->query($sql);
    }
    else {
      $id = 0;
      $res = false;
    }
  }
  //update sql
  elseif ($type_sql == 'update') {
    $oddelovac = '';
    $sql_field_value = '';
    foreach ($sql_field_arr as $field  =>  $value) {
      $sql_field_value .=  $oddelovac.$field.' = ' . $value;
      $oddelovac = ',';
    } 
    $sql = "update posta set $sql_field_value $update_set where id = $id;";
//    echo "sql: " . $sql;die();
    
    if ($q->query($sql)) {}
    else {
      $res = false;
    }
  }
  
  return $res;
}

function VratDokumentInfo($id)
{
  $odes_typ = array('O' => 'Fyzicka','P' => 'Pravnicka','F' => 'Osvc','FF' => 'Zamestnanec','PP' => 'Utvar','' => 'Neurceno');

  if (!$q) $q = new DB_POSTA;
  if (!$a) $a = new DB_POSTA;
  $sql = 'select p.*, pco.nazev AS PCO_NAZEV from posta p LEFT JOIN posta_cis_osloveni pco ON (p.odesl_osloveni = cast(pco.id as varchar)) where p.id = ' . $id;
  //echo $sql;
  $q->query($sql);
  $q->Next_Record();

  $cislo_spisu = FormatSpis($q->Record["CISLO_SPISU1"],$q->Record["CISLO_SPISU2"],$q->Record["REFERENT"],$q->Record["ODBOR"],$q->Record["NAZEV_SPISU"],$q->Record["PODCISLO_SPISU"]);

  $cj = LoadClass('EedCj', $id);
  $cislo_jednaci = $cj->cislo_jednaci;

  if ($q->Record["SKARTACE"]) {
    $sql_skartace = "select * from cis_posta_skartace where id = " . $q->Record["SKARTACE"];
    $a->query($sql_skartace);
    $pocet = $a->Num_Rows();
    $a->Next_Record();
    $spis_znak = substr($a->Record["TEXT"],0,strpos($a->Record["TEXT"],' '));
    $skar_znak = $a->Record["SKAR_ZNAK"];
    $skar_lhuta = $a->Record["DOBA"];
  }

  if ($q->Record["TYPDOC"]) {
    $sql_typdoc = "select * from cis_posta_typ where id = " . $q->Record["TYPDOC"];
    $a->query($sql_typdoc);    
    $a->Next_Record();
    $typ_doc = $a->Record['NAZEV'];
  }

  $dokument[DALSI_ID_AGENDA] = $q->Record["DALSI_ID_AGENDA"];
  $dokument[DALSI_ID_SPIS_AGENDA] = $q->Record["DALSI_ID_SPIS_AGENDA"];
  $dokument[DOKUMENT_ID] = $q->Record["ID"];
  $dokument[STAV] = $q->Record["STAV"];
  $dokument[TYP_DOC] = $typ_doc;
  $dokument[ROK] = $q->Record["ROK"];
  $dokument[EV_CISLO] = $q->Record["EV_CISLO"]; // . "/" . $q->Record["ROK"];
  $dokument[CISLO_JEDNACI] = TxtEncoding4Soap($cislo_jednaci);
  $dokument[CISLO_JEDNACI1] = TxtEncoding4Soap($q->Record["CISLO_JEDNACI1"]);
  $dokument[CISLO_JEDNACI2] = TxtEncoding4Soap($q->Record["CISLO_JEDNACI2"]);
  $dokument[CISLO_SPISU] = TxtEncoding4Soap($cislo_spisu);
  $dokument[CISLO_SPISU1] = TxtEncoding4Soap($q->Record["CISLO_SPISU1"]);
  $dokument[CISLO_SPISU2] = TxtEncoding4Soap($q->Record["CISLO_SPISU2"]);
  $dokument[NAZEV_SPISU] = TxtEncoding4Soap($q->Record["NAZEV_SPISU"]);
  $dokument[DATUM] = ConvertDatumToXML($q->Record["DATUM_PODATELNA_PRIJETI"]);
  $dokument[VEC] = TxtEncoding4Soap($q->Record["VEC"]);
  $dokument[TYP_ADR] = $odes_typ[$q->Record["ODES_TYP"]];
  $dokument[JEJICH_CJ] = $q->Record["JEJICH_CJ"];
  
  $dokument[POCET_LISTU] = $q->Record["POCET_LISTU"] ? $q->Record["POCET_LISTU"] : 0;
  $dokument[POCET_PRILOH] = $q->Record["POCET_PRILOH"] ? $q->Record["POCET_PRILOH"] : 0;
  $dokument[DRUH_PRILOH] = $q->Record["DRUH_PRILOH"];
  
  $dokument[DATNAR] = ConvertDatumToXML($q->Record["ODESL_DATNAR"]);
  $dokument[PRIJMENI] = TxtEncoding4Soap($q->Record["ODESL_PRIJMENI"]);
  $dokument[TITUL] = TxtEncoding4Soap($q->Record["ODESL_TITUL"]);
  $dokument[JMENO] = TxtEncoding4Soap($q->Record["ODESL_JMENO"]);
  $dokument[OSLOVENI] = $q->Record["PCO_NAZEV"];

  $dokument[ORGANIZACE] = TxtEncoding4Soap($q->Record["ODESL_PRIJMENI"]);
  $dokument[ODDELENI] = TxtEncoding4Soap($q->Record["ODESL_ODD"]);
  $dokument[OSOBA] = TxtEncoding4Soap($q->Record["ODESL_OSOBA"]);
  $dokument[ULICE] = TxtEncoding4Soap($q->Record["ODESL_ULICE"]);
  $dokument[CP] = TxtEncoding4Soap($q->Record["ODESL_CP"]);
  $dokument[COR] = TxtEncoding4Soap($q->Record["ODESL_COR"]);
  $dokument[MESTO] = TxtEncoding4Soap($q->Record["ODESL_POSTA"]);
  $dokument[PSC] = TxtEncoding4Soap($q->Record["ODESL_PSC"]);
  $dokument[DS] = TxtEncoding4Soap($q->Record["ODESL_DATSCHRANKA"]);
  $dokument[ADRESAT_CJ] = TxtEncoding4Soap($q->Record["JEJICH_CJ"]);
  $dokument[ODBOR] = $q->Record["ODBOR"];
  $dokument[ZPRACOVATEL] = $q->Record["REFERENT"];
  $dokument[OBALKA] = $q->Record["DOPORUCENE"];
  $dokument[ODESLANI] = $q->Record["VLASTNICH_RUKOU"];
  $dokument[SKARTACE_ID] = $q->Record["SKARTACE"];

  $dokument[SPIS_ZNAK] = $spis_znak;
  $dokument[SKAR_ZNAK] = $skar_znak;
  $dokument[SKAR_LHUTA] = $skar_lhuta;

  $dokument[ZMOCNENI_ZAKON] = TxtEncoding4Soap($q->Record["ZMOCNENI_ZAKON"]);
  $dokument[ZMOCNENI_ROK] = TxtEncoding4Soap($q->Record["ZMOCNENI_ROK"]);
  $dokument[ZMOCNENI_PAR] = TxtEncoding4Soap($q->Record["ZMOCNENI_PAR"]);
  $dokument[ZMOCNENI_ODST] = TxtEncoding4Soap($q->Record["ZMOCNENI_ODST"]);
  $dokument[ZMOCNENI_PISMENO] = TxtEncoding4Soap($q->Record["ZMOCNENI_PISMENO"]);
  $dokument[DATUM_VYPRAVENI] = ConvertDatumToXML($q->Record["DATUM_VYPRAVENI"]);
  $dokument[DATUM_DORUCENI] = ConvertDatumToXML($q->Record["DATUM_DORUCENI"]);
  $dokument[SPIS_CISLO] = $q->Record["CISLO_SPISU1"].'/' . $q->Record["CISLO_SPISU2"];
  $dokument[SPIS_NAZEV] = TxtEncoding4Soap($q->Record["NAZEV_SPISU"]);
  $dokument[POZNAMKA] = TxtEncoding4Soap($q->Record["POZNAMKA"]);

  return $dokument;
}

Function UlozSoubor($id, $referent, $request, &$message, $replace_file = false)
{
  //print_r($request);

  $uplobj = Upload(array('create_only_objects' => true,'agenda' => 'POSTA','noshowheader' => true));
    
  //nazvu souboru
  if (!$request["Soubor"]["!dmFileDescr"]) {
    $message = 'Neni zadan nazev souboru';
    return false;
  }
  else 
    $file_name = $request["dmFile"]["!dmFileDescr"];
  
  $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$file_name;
  if (is_file($tmp_soubor)) unlink($tmp_soubor);
  
  //kontrola existujicich priloh
  $update = false;
  if ($request["Soubor"]["Identifikator"]["HodnotaID"]) {
    $GLOBALS['EXTERNAL_ID'] = TxtEncoding4Soap($request["Soubor"]["Identifikator"]["HodnotaID"]);
    $GLOBALS['NAME_ID'] = TxtEncoding4Soap($request["Soubor"]["!dmFileDescr"]);
    $upload_records = $uplobj['table']->GetRecordsUploadForAgenda(-99);
    while (list($key,$val) = each($upload_records)) {
//      if ($GLOBALS['EXTERNAL_ID'] == $val[EXTERNAL_ID]) { // budeme nahrazovat dle nazvu souboru
      if ($GLOBALS['NAME_ID'] == $val[NAME]) {
        $update = true;
        $file_name = $val[NAME];
        $file_ident = $val[ID];
        $GLOBALS["ID"] = $val[ID];
        $GLOBALS["FILE_ID"] = $val[ID];
        $GLOBALS["UPL_FILE"] = $file_name;
        $GLOBALS["LAST_DATE"] = Date('Y-m-d');
        $GLOBALS["OWNER_ID"] = $val[LAST_USER_ID];
//        $GLOBALS["UPL_DIR"] = ' . ';
        $GLOBALS['archiv_file_system'] = true;
        $tmp_soubor = '/tmp/upload/' . $file_name;
        $tmp_soubor = TxtEncoding4Soap($tmp_soubor);
        $GLOBALS['COSTIM'] = 'archiv_a'; //archivuj puvodni
        $GLOBALS['show_typ'] = 2;
        $GLOBALS['EDIT_ID'] = $val[ID];
        break;
      }
    }
  }
  $GLOBALS['LAST_USER_ID'] = $referent?$referent:$GLOBALS["KONEKTOR"]["ISRZP"]["LAST_USER_ID"];
  $GLOBALS['OWNER_ID'] = $referent?$referent:$GLOBALS["KONEKTOR"]["ISRZP"]["LAST_USER_ID"];
  
  //test, zalozeni souboru 
  if ($update && ($replace_file == false)) {
    $message = 'Soubor ' . $file_name.' jiz existuje';
    return false;
  }
  //test, aktualizace souboru 
  if (($update == false) && $replace_file) {
    $message = 'Soubor ' . $file_name.' neexistuje';
    return false;
  }
  
  //obsah
  $data = '';
  if ($request["Soubor"]["dmEncodedContent"]) $data = base64_decode($request["Soubor"]["dmEncodedContent"]);
  if (strlen($data)<1) {
    $message = 'Neni k dispozici obsah souboru ' . $file_name;
    return false;
  }
  
  //vytvoreni souboru
  if (!$fp = fopen($tmp_soubor,'w')) {
    $message = 'Chyba pri ulozeni tmp souboru ' . $tmp_soubor;
    return false;
  }
  fwrite($fp,$data);
  fclose($fp);
  
  $tmp_soubor_2 = TxtEncodingFromSoap($tmp_soubor);
  $ret = @$uplobj['table']->SaveFileToAgendaRecord($tmp_soubor_2, '-99');
  if ($ret[err_msg]<>'') {
    $message = 'Chyba pri ulozeni souboru ' . $file_name.': ' . $ret[err_msg];
    return false;
  }
  if ($update) {
    $file_ident = $file_ident;
  }
  else {
    $file_ident = $ret[file_id];
    $uplobj['table']->q->query("UPDATE " . $uplobj['table']->upl_table . " SET external_id = id WHERE id = $file_ident");
  }
  if (is_file($tmp_soubor)) unlink($tmp_soubor);
  
  if (!$replace_file)
    $message = 'K dokumentu (' . $id.') byl vlozen soubor ' . $file_name.' - ID: (' . $file_ident.')';
  else
    $message = 'Byl zmenen obsah soubor ' . $file_name.' - ID: (' . $file_ident.')';

  return true;
}

Function ZkopirujSoubor($id_puvodni, $id, $request, &$message)
{
  //print_r($request);
  
  $uplobj = Upload(array('create_only_objects' => true,'agenda' => 'POSTA','noshowheader' => true));
  
  //identifikator
  if (!$request["FileLink"]["Identifikator"]["HodnotaID"]) {
    $message = 'Neni zadan identifikator souboru';
    return false;
  }
  else 
    $GLOBALS['EXTERNAL_ID'] = TxtEncoding4Soap($request["FileLink"]["Identifikator"]["HodnotaID"]);
    
  //nazvu souboru
  if (!$request["FileLink"]["!dmFileDescr"]) {
    $message = 'Neni zadan nazev souboru';
    return false;
  }
  else 
    $file_name = $request["FileLink"]["!dmFileDescr"];
  
  $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$file_name;
  if (is_file($tmp_soubor)) unlink($tmp_soubor);
  
  //kontrola existujicich priloh
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id_puvodni);
  $copy = false;
  while (list($key,$val) = each($upload_records)) {
    if ($GLOBALS['EXTERNAL_ID'] == $val[EXTERNAL_ID]) {
      $copy = true;
      $data =  $uplobj['table']->GetUploadFiles($val);
      $GLOBALS['DESCRIPTION'] = $val[DESCRIPTION];
      break;
    }
  }
  $GLOBALS['LAST_USER_ID'] = $GLOBALS["KONEKTOR"]["ISRZP"]["LAST_USER_ID"];
  
  //test, zda existuje priloha
  if (!$copy) {
    $message = 'U dokumentu (' . $id_puvodni.') soubor ' . $file_name.' neexistuje';
    return false;
  }
  
  //obsah
  if (strlen($data)<1) {
    $message = 'Neni k dispozici obsah souboru ' . $file_name;
    return false;
  }
  
  //vytvoreni souboru
  if (!$fp = fopen($tmp_soubor,'w')) {
    $message = 'Chyba pri ulozeni tmp souboru ' . $tmp_soubor;
    return false;
  }
  fwrite($fp,$data);
  fclose($fp);
  
  $uplobj_save = Upload(array('create_only_objects' => true,'agenda' => 'POSTA','noshowheader' => true));
  
  $tmp_soubor_2 = TxtEncodingFromSoap($tmp_soubor);
  $ret = $uplobj_save['table']->SaveFileToAgendaRecord($tmp_soubor_2, $id);
  if ($ret[err_msg]<>'') {
    $message = 'Chyba pri ulozeni souboru ' . $file_name.': ' . $ret[err_msg];
    return false;
  }
  if (is_file($tmp_soubor)) unlink($tmp_soubor);
  
  $file_ident = $ret[file_id];
  $message = 'K vypraveni (' . $id.') byl vlozen soubor ' . $file_name.' - ID: (' . $file_ident.')';

  return true;
}

Function ZrusSoubor($id, $request, &$message)
{
  //print_r($request);

  $uplobj = Upload(array('create_only_objects' => true,'agenda' => 'POSTA','noshowheader' => true));
  
  //identifikator
  if (!$request["dmFileID"]["tFile"]["Identifikator"]["HodnotaID"]) {
    $message = 'Neni zadan identifikator souboru';
    return false;
  }
  else 
    $GLOBALS['EXTERNAL_ID'] = TxtEncoding4Soap($request["dmFileID"]["tFile"]["Identifikator"]["HodnotaID"]);
    
  //kontrola existujicich priloh
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);
  $delete = false;
  while (list($key,$val) = each($upload_records)) {
    if ($GLOBALS['EXTERNAL_ID'] == $val[EXTERNAL_ID]) {
      $delete = true;
      $file_name = $val[NAME];
      $file_ident = $val[ID];
      break;
    }
  }
  
  if (!$delete) {
    $message = 'Priloha s identifikatorem ' . $GLOBALS['EXTERNAL_ID'].' neexistuje';
    return false;
  }
  
  $delete_id_arr[] = $file_ident;
  $ret = $uplobj['table']->deleteAllUploadForAgendaRecord($id, $delete_id_arr);
  if ($ret[err_msg]<>'') {
    $message = 'Chyba pri mazani souboru ' . $file_name.': ' . $ret[err_msg];
    return false;
  }
  
  $message = 'Z dokumentu \ vypraveni (' . $id.') byl odstranen soubor ' . $file_name.' - ID: (' . $file_ident.')';

  return true;
}

Function ConvertSpisId($spisID = 0) {
  static $q;
  if (!$q) $q = new DB_POSTA;
  if (strlen($spisID)<1) $spisID = 0;
  if (!strpos($spisID,'/'))
  {
    $spis = array();
    $sql = 'select cislo_spisu1,cislo_spisu2,nazev_spisu,spis_vyrizen from posta where id = ' . $spisID;
    //echo $sql . "<br/>";
    $q->query($sql);
    $q->Next_Record();
    //print_r($q->Record);
    $spis[CISLO_SPISU1] = $q->Record[CISLO_SPISU1];
    $spis[CISLO_SPISU2] = $q->Record[CISLO_SPISU2];
    $spis[NAZEV_SPISU] = $q->Record[NAZEV_SPISU];
    $spis[SPIS_VYRIZEN] = ($q->Record[SPIS_VYRIZEN]<>'')?true:false;
    //print_r($spis);
    //$spis[CISLO_SPISU1] = $spis[CISLO_SPISU1]?$spis[CISLO_SPISU1]:0;
    //$spis[CISLO_SPISU2] = $spis[CISLO_SPISU2]?$spis[CISLO_SPISU2]:0;
    return ($spis);
  }
  else
  {
    list($cs1,$cs2) = explode('/',$spisID);
    $sql = 'select id from posta where cislo_spisu1 = ' . $cs1.' and cislo_spisu2 = ' . $cs2;
    //echo $sql . "<br/>";
    $q->query($sql);
    $q->Next_Record();
    $id = $q->Record[ID];
    //zavolame fci znova, aby se nam vratil i nazev spisu
    return ConvertSpisId($id);
  }
}

Function VratDokumenty($where) {
  static $q;
  if (!$q) $q = new DB_POSTA;
  $dokumenty = array();
  $sql = 'select id from posta where ' . $where;
  //echo $sql;
  $q->query($sql);
  while ($q->Next_Record()) $dokumenty[] = $q->Record[ID];
  return $dokumenty;
}

Function VratDokumentyKeSpisu($spis_id = 0) {
  static $q;
  if (!$q) $q = new DB_POSTA;
  //echo 'SPis id ' . $spis_id;Flush();
  $dokumenty = array();
  $spis = ConvertSpisID($spis_id);
  //print_r($spis);
  if ($spis[CISLO_SPISU1]<1) return false;
  $sql = 'select id from posta where cislo_spisu1 = ' . $spis[CISLO_SPISU1].' and cislo_spisu2 = ' . $spis[CISLO_SPISU2];
  $q->query($sql);
  while ($q->Next_Record()) $dokumenty[] = $q->Record[ID];
  return $dokumenty;
}

Function NastavStatusSpis($spis_id,$request_autorizace) {
  $ref = VratReferenta($request_autorizace);
  $dokumenty = VratDokumentyKeSpisu($spis_id);
  NastavStatusDokumenty($dokumenty,$ref);
}

Function NastavStatusDokumenty($dokumenty, $referent = 0) {
  reset($dokumenty);
  while (list($key,$id) = each($dokumenty)) NastavStatus($id,$referent);
}

Function NastavInfo(&$insert_fields, &$insert_values, &$update_set, $ref = 0) {
  
  $LAST_USER_ID = $ref?$ref:$GLOBALS["KONEKTOR"]["ISRZP"]["LAST_USER_ID"];
  $LAST_TIME = Date('H:i:s');
  $LAST_DATE = Date('Y-m-d');

  $update_set = ",last_date = '" . $LAST_DATE . "',last_time = '" . $LAST_TIME . "',last_user_id = " . $LAST_USER_ID;
  $insert_fields = ",last_date,last_time,last_user_id";
  $insert_values = ",'" . $LAST_DATE . "','" . $LAST_TIME . "'," . $LAST_USER_ID;
}

Function VratReferenta($request_autorizace, $novyZpracovatel = false) {
  //print_r($request_autorizace);
  //echo $novyZpracovatel;
 
  $chyba = false;
  if (!$q) $q = new DB_POSTA;
  if (!$request_autorizace["provedlKdo"] || $request_autorizace["provedlKdo"]<1) {
    $request_autorizace["provedlKdo"] = 0; 
    $chyba = true;
  }
  $sql = 'select twist_id from posta_isrzp_pracovnici where idrzp = ' . $request_autorizace["provedlKdo"];
  //echo $sql;
  if ($q->query($sql)) {
    $q->Next_Record();
    $res = $q->Record["TWIST_ID"]?$q->Record["TWIST_ID"]:0;
  }
  else
    $chyba = true;
  return $res;
}

Function NastavLog(&$log,$text,$session_id = '',$kod) {
  $log[] = array(
    'text'  =>  $text,
    'session_id'  =>  $session_id,
    'chyba'  =>  $kod == '0000' ? '0' : '1',
  );
}

Function ZapisLog($log) {
  reset($log);
  while (list($key,$val) = each($log)) WriteLog('Unispis', $val["text"], $val["session_id"], $val["chyba"]);
}
