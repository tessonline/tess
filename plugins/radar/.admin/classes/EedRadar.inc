<?php
include_once(FileUp2('.admin/upload_.inc'));
include_once(FileUp2('.admin/run2_.inc'));
include_once(FileUp2('.admin/zaloz.inc'));
include_once(FileUp2('.admin/status.inc'));
include_once(FileUp2('interface/.admin/upload_funkce.inc'));

class EedRadar extends eed_db_object {

  function getIDKonfigurace() {
    $db = eed_db_object::getInstanceDb();
    $sql = "select * from posta where dalsi_id_spis_agenda='TmapEss:RADARSETTING'";
    $db->query($sql);
    if ($db->Num_Rows() == 0) return false;
    else {
      $db->Next_Record();
      return $db->Record['ID'];
    }
  }

  function setIDKonfigurace() {
    $db = eed_db_object::getInstanceDb();
    $sql = "insert into posta (ROK,ODES_TYP,CISLO_JEDNACI1,CISLO_JEDNACI2,CISLO_SPISU1,CISLO_SPISU2,DALSI_ID_SPIS_AGENDA,status) VALUES (0,'Z',1,0,1,0,'TmapEss:RADARSETTING',99)";
    $db->query($sql);
    return EedRadar::getIDKonfigurace();

  }

  function loadXML($file) {
    $xml = simplexml_load_file($file, 'SimpleXMLElement',LIBXML_NOCDATA);
    $text='(RADAR) - parsuju ' . $file;
    WriteLog('RADAR',$text,'SESSradar');

    $ns = $xml->getNamespaces(true);;
    $ess = $xml->children($ns['ess']);
    $subjekt = $ess->Spis->SouvisejiciSubjekty->SouvisejiciSubjekt->Subjekt;

    $data['%SUBJEKT_JMENO%'] = ($subjekt->TypSubjektu == 'Fyzicka' ? $subjekt->Jmeno.' ' . $subjekt->Prijmeni : (string)$subjekt->ObchodniNazev);
    $data['%SUBJEKT_IC%'] = ($subjekt->TypSubjektu == 'Fyzicka' ? (string)$subjekt->DatumNarozeni[0] : (string)$subjekt->IC);

    $data['%SUBJEKT_OBEC%'] = (string)$subjekt->Adresy->AdresaPostovni->Obec[0];
    $data['%SUBJEKT_COBCE%'] = (string)$subjekt->Adresy->AdresaPostovni->CastObce;
    $data['%SUBJEKT_ULICE%'] = (string)$subjekt->Adresy->AdresaPostovni->Ulice;
    $data['%SUBJEKT_COR%'] = (string)$subjekt->Adresy->AdresaPostovni->OrientacniCislo;
    $data['%SUBJEKT_CP%'] = (string)$subjekt->Adresy->AdresaPostovni->PopisneCislo;
    $data['%SUBJEKT_PSC%'] = (string)$subjekt->Adresy->AdresaPostovni->Psc;
    $data['%SUBJEKT_DS%'] = (string)$subjekt->Adresy->AdresaDS->IdDb;

    $a = 0;
    if ($ess->Spis->Soubory->dmFile) {
      foreach($ess->Spis->Soubory->dmFile as $file) {
        $attr = $file->attributes();
        $data['SOUBORY'][$a]['CONTENT'] = (string)$file->dmEncodedContent;
        $data['SOUBORY'][$a]['NAME'] = (string)$attr['dmFileDescr'];
        $a++;
      }
    }


    $pr = $ess->Spis->DoplnujiciData->children($ns['pr']);

    $data['%PRESTUPEK_RZ%'] = (string)$pr->Prestupek->RZ;
    $data['%PRESTUPEK_NAMERENA%'] = (string)$pr->Prestupek->Rychlost->Namerena;
    $data['%PRESTUPEK_TOLERANCE%'] = (string)$pr->Prestupek->Rychlost->Tolerance;
    $data['%PRESTUPEK_VYPOCTENA%'] = (string)$pr->Prestupek->Rychlost->Vypoctena;
    $data['%PRESTUPEK_DATUM%'] = (string)$pr->Prestupek->Spachano;
    $data['%PRESTUPEK_CJ%'] = (string)$ess->Spis->VlozeneDokumenty->VlozenyDokument->Dokument->CisloJednaci;

    return $data;
  }

  function replaceData($id, $pole) {
    $db = eed_db_object::getInstanceDb();
    $text='(RADAR) - aktualizuju data pro '. $id;
    WriteLog('RADAR',$text,'SESSradar');
    $sql = "select * from posta where id=" . $id;
    $db->query($sql);
    $db->Next_Record();
    $db->Record['JEJICH_CJ'] = '%PRESTUPEK_CJ%';
    foreach($db->Record as $key => $val) {

      foreach($pole as $key1 => $val1) {
        $val = str_replace($key1, $val1, $val);
      }
      if (!is_int($key)) $save[$key] = $val;
    }
    unset($save['TSV']); //ten se spocita sam
    $sql = 'update posta set ';
    foreach ($save as $key => $val)
      if ($val<>'') $sql .= $key . "='".$val."',";
    $sql = substr($sql, 0, -1);
    $sql .= ' where id=' . $id;

    if ($db->query($sql)) {
      $text='(RADAR) - povedlo se, data aktualni pro '. $id;
      WriteLog('RADAR',$text,'SESSradar');
      return true;
    }
  }

  function PrepisXMLEED($file, $id = 000) {
    $xml = simplexml_load_file($file, 'SimpleXMLElement',LIBXML_NOCDATA);
    $ns = $xml->getNamespaces(true);;
    $ess = $xml->children($ns['ess']);


    $id = EedRadar::getIDKonfigurace();
    $q = new DB_POSTA;
    $q->query('select * from posta where id=' . $id);
    $q->Next_Record(); $data = $q->Record;

    $doc = $ess->Spis->SouvisejiciSubjekty;
    $oznamovatel2 = $doc->addChild('SouvisejiciSubjekt');
    $oznamovatel = $oznamovatel2->addChild('Subjekt');

    if ($data['ODES_TYP'] == 'U' || $data['ODES_TYP'] == 'P') {
      $oznamovatel->TypSubjektu = 'Pravnicka';
      $oznamovatel->ObchodniNazev = $data['ODESL_PRIJMENI'];
      $oznamovatel->IC = $data['ODESL_ICO'];
    }
    else {
      $oznamovatel->TypSubjektu = 'Fyzicka';
      $oznamovatel->Prijmeni = $data['ODESL_PRIJMENI'];
      $oznamovatel->Jmeno = $data['ODESL_JMENO'];
    }
    $oznamovatel->Adresy->AdresaPostovni->Obec = $data['ODESL_POSTA'];
    $oznamovatel->Adresy->AdresaPostovni->Ulice = $data['ODESL_ULICE'];
    $oznamovatel->Adresy->AdresaPostovni->OrientacniCislo = $data['ODESL_COR'];
    $oznamovatel->Adresy->AdresaPostovni->PopisneCislo = $data['ODESL_CP'];
    $oznamovatel->Adresy->AdresaPostovni->Psc = $data['ODESL_PSC'];
    $oznamovatel->Adresy->AdresaPostovni->Zeme = 'CZ';

    $data = $oznamovatel->addChild('DoplnujiciData');
    $role = $data->addChild('pr:Role','Oznamovatel', 'http://www.vitasw.cz/NS/Prestupky');

    if ($ess->Spis->Soubory) UNSET($ess->Spis->Soubory);
    if ($ess->Spis->VlozeneDokumenty->VlozenyDokument->Dokument->Identifikator->HodnotaId) $ess->Spis->VlozeneDokumenty->VlozenyDokument->Dokument->Identifikator->HodnotaId = $id;
    if ($ess->Spis->VlozeneDokumenty->VlozenyDokument->Dokument->Identifikator->ZdrojId) $ess->Spis->VlozeneDokumenty->VlozenyDokument->Dokument->Identifikator->ZdrojId = 'TmapEss';
    return $xml->asXML();
  }

  function ZalozZaznam($file) {
    $text='(RADAR) - ------ NOVY ZAZNAM ------ '. $file;
    WriteLog('RADAR',$text,'SESSradar');

    $db = eed_db_object::getInstanceDb();
    $sql = "select * from posta_plugins_radar_ulozeno where file like '".basename($file)."'";
    $db->query($sql);
    if ($db->Num_Rows()>0) {
        $text='(RADAR) - soubor '.basename($file).' uz byl zalozen, ignoruji ho';
        WriteLog('RADAR',$text,'SESSradar', 1);
        return false;
    }

    $data = EedRadar::LoadXML($file);
    $idTemp = EedRadar::getIDKonfigurace();
    $nove_id = ZalozNovyDokument($idTemp, 0, 2);
    if (EedRadar::replaceData($nove_id, $data)) {
      $text = 'dokument (<b>'.$nove_id.'</b>) byl založen načtením z modulu RADAR. Data načtena z '.$file;
      EedTransakce::ZapisLog($nove_id, $text, 'DOC');

      EedRadar::InsertFile($nove_id, $file, $data);
      EedRadar::SmazXML($file);

      $sql = "insert into posta_plugins_radar_ulozeno (posta_id,file) VALUES (" . $nove_id .",'" . basename($file) . "')";
      $db->query($sql);
      return true;
    }
    else return false;
  }

  function InsertFile($id, $file, &$data) {
    $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));

    //upravime XML, aby obsahovalo nase data
    $soubor = EedRadar::PrepisXMLEED($file, $id);
    $tmp_soubor = $GLOBALS['CONFIG_POSTA']['RADAR']['adresar'].'/'.'zadost_a3787.xml';
    @unlink($tmp_soubor);
    $fp = fopen($tmp_soubor, 'w');
    fwrite($fp, $soubor);
    fclose($fp);

    // a ulozime ho
    $ret = $uplobj['table']->SaveFileToAgendaRecord($tmp_soubor, $id);

    if ($ret[err_msg]<>'') {
      $text='(RADAR) - Chyba pri ulozeni souboru '.$val["NAME"].': '.$ret[err_msg];
      WriteLog('RADAR',$text,'SESSradar', 1);
    }
    else {
      $text = '(RADAR) - ulozil jsem soubor ' . $file .' do uploadu ' . $id;
      WriteLog('RADAR',$text,'SESSradar');
    }
    @unlink($tmp_soubor);

    //a pripadne ulozime prilohy
    if (is_array($data['SOUBORY']))
    foreach($data['SOUBORY'] as $soubor) {
      $tmp_soubor = $GLOBALS['CONFIG_POSTA']['RADAR']['adresar'].'/'.$soubor['NAME'];
      @unlink($tmp_soubor);
      $fp = fopen($tmp_soubor, 'w');
      fwrite($fp, base64_decode($soubor['CONTENT']));
      fclose($fp);
      $ret = $uplobj['table']->SaveFileToAgendaRecord($tmp_soubor, $id);

      if ($ret[err_msg]<>'') {
        $text='(RADAR) - Chyba pri ulozeni souboru '.$val["NAME"].': '.$ret[err_msg];
        WriteLog('RADAR',$text,'SESSradar', 1);
      }
      else {
        $text = '(RADAR) - ulozil jsem soubor ' . basename($tmp_soubor) .' do uploadu ' . $id;
        WriteLog('RADAR',$text,'SESSradar');
      }
      @unlink($tmp_soubor);

    }


  }

  function SmazXML($file) {
    if (!unlink($file)) {
      $text='(RADAR) - Nepovedlo se smazat soubor '.$file;
      WriteLog('RADAR',$text,'SESSradar', 1);
    }
    else {
      $text = '(RADAR) - smazal jsem soubor ' . basename($file).', vse je ok';
      WriteLog('RADAR',$text,'SESSradar');
    }
    return true;
  }

}
