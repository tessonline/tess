<?php
require_once(FileUp2('plugins/npu/.config/config_pam_katalog.inc'));
require_once(FileUp2('interface/.admin/soap_funkce.inc'));

class PKIdent {
  var $id;
  var $jid;
  var $jmeno;
  var $popis;
  var $ochrana;
  var $url;
  var $typ;
  var $rejstrikoveCislo;
  var $katastr;
  var $adresa;
  var $kategoriePrvku;
  var $druhPrvku;
  var $lokalita;
  var $nahled;
  var $typ_kod;
  var $typ_text;
  var $error;

  function PKIdent($array) {
    $this->id = $array['id'];
    $this->jmeno = $array['jmeno'];
    $this->popis = $array['popis'];
    $this->url = $array['url'];
    $this->typ = $array['typ'];
    $this->ochrana = $array['ochrana'];
    $this->katastr = $array['katastr'];
    $this->adresa = $array['adresa'];
    $this->kategoriePrvku = $array['kategoriePrvku'];
    $this->typ_kod = $GLOBALS['PK_CIS'][$array['typ']]['kod'] ? $GLOBALS['PK_CIS'][$array['typ']]['kod'] : 'PK';
    $this->typ_text = $GLOBALS['PK_CIS'][$array['typ']]['text'] ? $GLOBALS['PK_CIS'][$array['typ']]['text'] : 'neuvedeno';;
    $this->rejstrikoveCislo = $array['rejstrikoveCislo'];
    $this->druhPrvku = $array['druhPrvku'];
    $this->lokalita = $array['lokalita'];
    $this->nahled = $array['nahled'];
  }

  function getArrayFromEed($docs) {
    $q = new DB_POSTA;
    $sql = "select * from posta_npu_pam_katalog where JID in (".implode(',',$docs).")";
    $res = array();
    $q->query($sql);
    while ($q->Next_Record()) {
      $agenda_id = $q->Record['DALSI_ID_AGENDA'];
      $temp = array();
      $temp['ID'] = $q->Record['ID'];
      $temp['JID'] = $q->Record['JID'];
      $temp['PK_ID'] = $q->Record['PK_ID'];
      $infoPK = $this->getInfoFromPK($q->Record['TYP_ID'], $temp['PK_ID']);
      $temp['jmeno'] = TxtEncodingFromSoap($infoPK['jmeno']);
      $temp['popis'] = TxtEncodingFromSoap($infoPK['popis']);
      $temp['url'] = $infoPK['url'];
      $temp['adresa'] = TxtEncodingFromSoap($infoPK['adresa']);
      $temp['katastr'] = TxtEncodingFromSoap($infoPK['katastr']);
      $temp['kategorieprvku'] = TxtEncodingFromSoap($infoPK['kategorie']);
      $temp['ochrana'] = str_replace(', ', '<hr/>', TxtEncodingFromSoap($infoPK['ochrana']));
      $temp['lokalita'] = TxtEncodingFromSoap($infoPK['lokalita']);
      $temp['REJSTRIKOVECISLO'] = str_replace(', ', '<hr/>', TxtEncodingFromSoap($infoPK['rejstrikoveCislo']));

      $temp['typ'] = $GLOBALS['PK_CIS'][$q->Record['TYP_ID']]['text'];
      if (!$temp['PK_ID']) {
        $temp['jmeno'] = '<i>zatím nepřiřazeno</i>';
        $temp['jmeno'] = $agenda_id;
        $temp['url'] = '';
      }
       if (!$infoPK) {
         $temp['jmeno'] = TxtEncodingFromSoap($this->error);;
      }
      $res[] = $temp;
    }
    return $res;

  }

  function getInfoFromPK($typ, $id) {
    global $USER_INFO;
    $service = $GLOBALS['PK_CIS'][$typ]['info'];
    if (!$service) return array();
    $cesta = 'plugins/npu/.admin/classes/' . $service . '.inc';
    include_once(FileUp2($cesta));
    $infoWS = new $service;
    $info = $infoWS->getInfo($id, $USER_INFO['LOGIN'] );
    if (!$info) $this->error = 'CHYBA: ' . $infoWS->client->faultstring;
    return $info;
  }

  function getCountOfIdent($jid) {
    $q = new DB_POSTA;
    $sql = "select * from posta_npu_pam_katalog where JID in (".$jid.") and TYP_ID>0";
    $q->query($sql);
    return $q->Num_Rows();
  }

  function uzJePrideleno($jid, $pk_typ, $pk_ident) {
    if (!$pk_ident) return false;
    if (!$pk_typ) return false;
    $q = new DB_POSTA;
    $sql = "select * from posta_npu_pam_katalog where JID in (".$jid.") and TYP_ID=".$pk_typ." and pk_id in (" . $pk_ident. ")" ;
    $q->query($sql);
    if ($q->Num_Rows()>0) return true;
    else return false;
  }

}
