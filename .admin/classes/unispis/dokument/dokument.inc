<?php
require_once(FileUp2('.admin/upload_.inc'));
require_once(FileUp2('.admin/run2_.inc'));
require_once(FileUp2('.admin/status.inc'));
    require_once(FileUp2('interface/.admin/soap_funkce.inc'));
require_once('identifikator.inc');
require_once('doruceni.inc');
require_once('vypraveni.inc');
require_once('vyrizeni.inc');
require_once('odesilatel.inc');
require_once('adresat.inc');
require_once('adresat.inc');
require_once('zasilkaInfo.inc');
require_once('soubor.inc');

/**
 * trida dokument
 * hlavni trida pro praci s jednotlivym dokumentem
 * Dokument muze byt dvou typu:
 * 1. doruceny dokument = ma vyplnenou hodnotu Doruceni
 * 2. odesilany (vypracovany) dokument = ma vyplnou hodnotu Vypraveni    
 *
 * @author onma
 */
class dokument {
  /** identifikator dokumentu */
  var $Id;
  /** identifikator dokumentu */
  var $Identifikator;
  /** identifikator dokumentu */
  var $Dalsi_id_agenda;
  /** Krátká věc vystihující obsah dokumentu */
  var $Nazev;
  /** Podrobný popis obsahu dokumentu */
  var $Popis;
  /** textove pole cisla jednaciho */
  var $CisloJednaci;
  /** označení spisu */
  var $SpisovaZnacka;
  /** Pořadí v rámci roku (začíná od 1) a podacího deníku (či jiné evidenční pomůcky) */
  var $PodaciDenikPoradi;
  /** Rok podacího deníku */
  var $PodaciDenikRok;
  /** Označení podacího deníku či jiné evidenční pomůcky ( většinou se pro označení využívá výstižná zkratka ) */
  var $PodaciDenik;
  /** datum a cas vytvoreni dokumentu */
  var $DatumCasVytvoreni;
  /** Popis typu dokumentu */
  var $TypDokumentu;
  /** Stručný popis/označení spisového a skartačního plánu */
  var $SpisovyPlan; 
  /** Označení ukládacího znaku (330.0) nebo popis znaku spisového a  skartačního plánu */
  var $SpisovyZnak; 
  /** Znak pro oznaceni skartace - A-archivace, S-skartace, V-vytřídění na základě skartačního řízení */
  var $SkartacniZnak; 
  /** Skartační nebo archivační lhůta v letech */
  var $SkartacniLhuta;  
  /** Poznámka */
  var $Poznamka; 
  /** třída doručení příchozího dokumentu */
  var $Doruceni;
  /** pole tříd jednotlivých vypravení dokumentu */
  var $Vypraveni = array();
  /** pole tříd souboru */
  var $Soubory = array();
  /** id spisu */
  var $SpisId;
  /** pole pro informace o vyrizeni dokumentu */
  var $Vyrizeni;
  
  /** db konektor */
  private $db;

  // Settery
  public function __set($name, $value) {
    $this->$name = $value;
  } 

  // Gettery
  public function __get($name) {
    return $this->$name;
  }
  /** konstruktor
   *
   * @author onma
   * @param array $dokument vstupni pole pro konstruktor
   */            
  public function __construct() {
    if (!$this->db) $this->db = new DB_POSTA;
  }

  public function setFromObject(MyObject $object)
  {
    foreach (get_object_vars($object) as $key => $value) {
        $this->$key = $value;
    }
    if ($this->Identifikator->HodnotaID <> '')
      $this->Dalsi_id_agenda = $this->Identifikator->ZdrojID . ":" . $this->Identifikator->HodnotaID;

  }


  public function setFromArray($dokument = array()) {
    $this->Id = ($dokument['Id']);
    $this->Identifikator = new Identifikator($dokument['Identifikator']);
    $this->Dalsi_id_agenda = $this->Identifikator->ZdrojID . ":" . $this->Identifikator->HodnotaID;
    $this->SpisId = ($dokument['SpisId']);
    $this->Nazev = ($dokument['Nazev']);
    $this->Popis = ($dokument['Popis']);
    $this->CisloJednaci = ($dokument['CisloJednaci']);
    $this->SpisovaZnacka = ($dokument['SpisovaZnacka']);
    $this->PodaciDenikPoradi = ($dokument['PodaciDenikPoradi']);
    $this->PodaciDenikRok = ($dokument['PodaciDenikRok']);
    $this->PodaciDenik = ($dokument['PodaciDenik']);
    $this->DatumCasVytvoreni = ($dokument['DatumCasVytvoreni']);
    $this->TypDokumentu = ($dokument['TypDokumentu']);
    $this->SpisovyPlan = ($dokument['SpisovyPlan']);
    $this->SpisovyZnak = ($dokument['SpisovyZnak']);
    $this->SkartacniZnak = ($dokument['SkartacniZnak']);
    $this->SkartacniLhuta = ($dokument['SkartacniLhuta']);
    $this->Poznamka = ($dokument['Poznamka']);

//    if ($dokument['Doruceni']) {
//      foreach($dokument['Doruceni'] as $doruceni) {
        $this->Doruceni = new doruceni($dokument['Doruceni']); 
//      }   
//    }

     if ($dokument['Vypraveni']) {
       foreach($dokument['Vypraveni'] as $vypraveni) {
        $this->Vypraveni[] = new vypraveni($vypraveni);
       }
    }
    $this->Vyrizeni = new vyrizeni($dokument['Vyrizeni']);
//     if ($dokument['Vyrizeni']) {
//       $this->Vyrizeni = new vyrizeni($dokument['Vyrizeni']);
//     }

  }

  public function addSoubor(&$soubor) {
    $this->Soubory[] = $soubor;
  }

  public function existujeId() {
    if (!$this->Dalsi_id_agenda || $this->Dalsi_id_agenda == '') return false;
    $sql = "select * from posta where dalsi_id_agenda='" .  $this->Dalsi_id_agenda ."'";
    $this->db->query($sql);
    if ($this->db->Num_Rows() == 0) return false;
    else {
      $this->db->Next_Record();
      if (!$this->id) $this->id = $this->db->Record['ID'];
      return true;
    }
  }

  public function Save($smer) {
    global $typ_odesl_unispis, $typ_odesl_tess;
    if (!$this->existujeId()) {
       $sq = LoadClass('EedSql', 0);
       $this->id = $sq->createCJwithExternalID(0, $this->Dalsi_id_agenda);
    }
    $data = array();
    if ($this->Nazev) $data['VEC'] = $this->Nazev;
    if ($this->DatumCasVytvoreni) $data['DATUM_PODATELNA_PRIJETI'] = $this->DatumCasVytvoreni;
    if ($this->Poznamka) $data['POZNAMKA'] = $this->Poznamka;


    if ($smer == 'f')
      $adresa = $this->Doruceni;
    else
      $adresa = $this->Vypraveni;

    if ($adresa->Adresat->Adresa->AdresaDS->IdDb) $data['ODESL_DATSCHRANKA'] = $adresa->Adresat->Adresa->AdresaDS->IdDb;

    $subjekt = $adresa->subjekt;
    $data['ODES_TYP'] = str_replace($typ_odesl_unispis, $typ_odesl_tess, $subjekt->TypSubjektu);
    $data['ODES_TYP'] = $data['ODES_TYP'] ? $data['ODES_TYP'] : 'U';
    $data['ODESL_ICO'] = $subjekt->ic;
    $data['ODESL_PRIJMENI'] = $subjekt->Prijmeni ? $subjekt->Prijmeni : $subjekt->ObchodniNazev;
    $data['ODESL_JMENO'] = $subjekt->Jmeno;

    $adresaPostovni = $subjekt->Adresa->AdresaPostovni;
    $data['ODESL_ULICE'] = $adresaPostovni[0]->Ulice;
    $data['ODESL_CP'] = $adresaPostovni[0]->PopisneCislo;
    $data['ODESL_COR'] = $adresaPostovni[0]->OrientacniCislo;
    $data['ODESL_PSC'] = $adresaPostovni[0]->Psc;
    $data['ODESL_POSTA'] = $adresaPostovni[0]->Obec;
    $data['ODESL_DATSCHRANKA'] = $subjekt->Adresa->AdresaDS->IdDb;

    $data['DATUM_PREDANI_VEN'] = Date('Y-m-d H:i:s');

    $update = array();
    foreach($data as $key=>$val) {
      $update[] = $key ."='" . $val . "'";
    }
    if (count($update)>0) {
      $sql = "update posta set "  . implode(',' , $update) . " where id=" . $this->id;
      $this->db->query($sql);
      NastavStatus($this->id);
    }

    if ($this->Soubory) {

      $uplobj = Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
      $soubor = array();
      $a = 0;
      //prisel jenom jeden soubor
      if (!is_array($this->Soubory->dmFile)) {
        $temp = $this->Soubory;
        $this->Soubory = array();
        $this->Soubory[0] = $temp;
      }

      foreach($this->Soubory as $file) {
          foreach ($file as $k=> $v2)
          {
            $file = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].'/drfile';
            $fp = fopen($file, "w");
            fwrite($fp, $v2->dmEncodedContent);
            fclose($fp);

            $GLOBALS['DESCRIPTION'] = $v2->dmFileMetaType;
            $GLOBALS['RENAME'] = $v2->dmFileDescr;
            $ret = $uplobj['table']->SaveFileToAgendaRecord($file, $this->id);
            unlink($file);
          }
      }
    }

  }

  public function SaveAsPrichozi() {

    $this->save('f');
  }

  public function SaveAsOdchozi() {
    $this->save('t');
  }

  public function InsertAdresaFromDS() {
    $schranka = new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);

    $adresa = $this->Vypraveni;
    if ($adresa->Adresat->Adresa->AdresaDS->IdDb) {
      $ds = $adresa->Adresat->Adresa->AdresaDS->IdDb;
      $dbOwnerInfo=array('dbID' => $ds);

      $hodnoty=$schranka->FindDataBox($dbOwnerInfo);

      $hodnoty=$hodnoty[0];
      $typ = 'Fyzicka';
      if ($hodnoty[dbType]=='PO') $typ='Pravnicka';
      if ($hodnoty[dbType]=='OVM') $typ='OVM';
      

      $ds=$hodnoty[dbID];
      $subjekt['TypSubjektu'] = $typ;
      $subjekt['IC'] = $hodnoty[ic];
      $subjekt['Jmeno'] = $hodnoty[pnFirstName];
      $subjekt['Prijmeni'] = $hodnoty[pnLastName];
      $subjekt['ObchodniNazev'] = $hodnoty[firmName];

      $subjekt['Adresa']['AdresaPostovni']['Ulice'] = $hodnoty[adStreet];
      $subjekt['Adresa']['AdresaPostovni']['PopisneCislo'] = $hodnoty[adNumberInMunicipality];
      $subjekt['Adresa']['AdresaPostovni']['OrientacniCislo'] = $hodnoty[adNumberInStreet];

      $subjekt['Adresa']['AdresaPostovni']['Obec'] = $hodnoty[adCity];
      $psc=str_replace(' ','',$hodnoty[adZipCode]);
      $subjekt['Adresa']['AdresaPostovni']['Psc'] = $psc;

      $subjekt['Adresa']['AdresaDS']['IdDb'] = $ds;
      $adresa->subjekt = new Subjekt($subjekt);
    }
  }

}
