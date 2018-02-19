<?php
require_once ('EedUser.inc');
/**
* trida EED_doc, pro praci s jednotlivymi dokumenty
*@author onma  
*/
class EedDokument extends EedUser {

   var $cj1_column = 'CISLO_SPISU1';
   var $cj2_column = 'CISLO_SPISU2';
  var $zarizeni_column = 'SUPERODBOR';

  var $id_dokument;
  var $main_doc;
  var $ev_cislo;
  var $rok;
  var $barcode;
  var $cj1;
  var $cj2;
  var $podlomeni;
  var $exemplar;
  var $cislo_jednaci;
  var $cislo_jednaci_zaklad; //bez podlomeni a exemplare
  var $zarizeni;
  var $datum_podatelna_prijeti;
  var $odbor;
  var $uzel_text;
  var $uzel_text_cele;
  var $nazev;
  var $vec;
  var $status;
  var $lhuta;
  var $rekomando;
  var $text_cj;
  var $typ_dokumentu;
  var $odes_typ;
  var $pocet_listu;
  var $pocet_priloh;
  var $druh_priloh;
  var $datum_narozeni;

  var $odmitnuti = array();

  var $skartace_id;
  var $referent_id;
  var $referent_text;
  var $referent_zkratka;
  
  var $jejich_cj;
  var $jejich_cj_dne;
  var $dalsi_prijemci;

  /* staticka promenna pro singleton */
  private static $DokumentInstance; 

  /**
  * Constructor
  * @author onma  
  * @param int $id - id dokumentu   
  */  
  function EedDokument($id){
    parent::EedUser();
    if (!$id) $id = 0;
    if (is_array($id)) $id = implode(',', $id);
    //echo "Load Dokument $id <br/>";
    if ($GLOBALS['CONFIG']['ODMITNUTI_DOKUMENTU']) {
      $sql = 'select * from posta_odmitnuti where posta_id in ('.$id.')';

      $this->_sql_query($sql);
      while ($this->db->Next_Record()) {
         $this->odmitnuti[] = array(
           'last_date' => $this->db->dbdate2str($this->db->Record['LAST_DATE']),
           'user_id' => $this->db->Record['LAST_USER_ID'],
           'user_text' => $this->GetUserName($this->db->Record['LAST_USER_ID']),
           'duvod' => $this->db->Record['DUVOD'],
         );
      }

    }
    if (isset($GLOBALS['POSTA_OPT']['POSTA'][$id])) {
      $ret = $GLOBALS['POSTA_OPT']['POSTA'][$id];
    }
    else {
      $sql = 'select * from posta where id in ('.$id.')';
      $this->_sql_query($sql);
      $this->db->Next_Record();
      $ret = $this->db->Record;
      $GLOBALS['POSTA_OPT']['POSTA'][$id] = $ret;
    }
    
    $this->superodbor = $ret['SUPERODBOR'];

    $prefix  = $GLOBALS['CONFIG_POSTA']['HLAVNI'][$this->superodbor]['prefix_id'];
    if (!$prefix) $prefix  = $GLOBALS['CONFIG']['ID_PREFIX'];
    $this->barcode = $prefix . $id;

    $this->main_doc = $ret['MAIN_DOC'];
    $this->skartace = $ret['SKARTACE'];
    $this->ev_cislo = $ret['EV_CISLO'];
    $this->rok = $ret['ROK'];
    $this->id_dokument = $ret['ID'];
    $this->podlomeni = $ret['PODCISLO_SPISU'];
    $this->exemplar = $ret['EXEMPLAR'];
    $this->text_cj = $ret['TEXT_CJ'];
    $this->typ_dokumentu = $ret['TYP_DOKUMENTU'];
    $this->datum_podatelna_prijeti = $ret['DATUM_PODATELNA_PRIJETI'];
    $this->rekomando = $ret['ODESL_REKOMANDO'];
    $this->datum_narozeni = $ret['ODESL_DATNAR'];
    
    $this->cj1 = $ret[$this->cj1_column];
    $this->cj2 = $ret[$this->cj2_column];
    $this->zarizeni = $ret[$this->zarizeni_column];

    $this->odes_typ = $ret['ODES_TYP'];

    
    $this->jejich_cj = $ret["JEJICH_CJ"];
    $this->jejich_cj_dne = $this->db->dbdate2str($ret["JEJICH_CJ_DNE"]);
    $this->dalsi_prijemci = $ret["DALSI_PRIJEMCI"];

    if ($ret['ODBOR']>0) {
      $odbor = $this->GetNadrizenouUnit($this->VratOdborZSpisUzlu($ret['ODBOR']));
      if ($odbor>0) {
        $unita = $this->VratSpisUzelZOdboru($odbor);
        $this->uzel_text = $this->_VratZkratkuSpisovehoUzlu($unita['ID']);
        $this->uzel_text_cele = $this->GetUnitName($odbor);
      }
      else {

      }
    }
        $this->uzel_text = $this->_VratZkratkuSpisovehoUzlu($ret['ODBOR']);
        $this->uzel_text_cele = $this->GetUnitName($this->VratOdborZSpisUzlu($ret['ODBOR']));

    $this->nazev = $ret['VEC'];
    $this->vec = $ret['VEC'];
    $this->odbor = $ret['ODBOR'];
    $this->lhuta = $ret['LHUTA'];
    $this->pocet_listu = $ret['POCET_LISTU'];
    $this->pocet_priloh = $ret['POCET_PRILOH'];
    $this->druh_priloh = $ret['DRUH_PRILOH'];
    $this->skartace_id = $ret['SKARTACE'];
    $this->referent_id = $ret['REFERENT'];
    if ($this->referent_id>0) {
      $this->referent_text = $this->GetUserName($this->referent_id);
      $this->referent_zkratka = $this->GetUserZkratka($this->referent_id);
      $res = $this->_GetUserPole($this->referent_id);
      $this->id_user = $res['ID'];
      $this->jmeno = $res['FNAME'];
      $this->email = $res['EMAIL'];
      $this->prijmeni = $res['LNAME'];
      $this->odbor_id = $res['GROUP_ID'];
      $this->odbor_text = $this->GetUnitName($res['GROUP_ID']);
      $this->zarizeni_id = $this->getMainUnit($res['GROUP_ID']);
      $this->zarizeni_text = $this->GetUnitName($this->zarizeni_id);
    }
    $this->cislo_jednaci = $ret['TEXT_CJ'] ? $ret['TEXT_CJ'] : $this->FormatCisloJednaci();
    $this->cislo_jednaci_zaklad = $ret['TEXT_CJ'] ? $ret['TEXT_CJ'] : $this->FormatCisloJednaci();
    $this->status = $ret['STATUS'];

    if ($this->skartace > 0) {

      if (isset($GLOBALS['POSTA_OPT']['CIS_POSTA_SKARTACE'][$this->skartace])) {
        $ret = $GLOBALS['POSTA_OPT']['CIS_POSTA_SKARTACE'][$this->skartace];
      }
      else {
        $sql='select * from cis_posta_skartace where id = '.$this->skartace;
        $this->_sql_query($sql);
        $this->db->Next_Record();
        $ret=$this->db->Record;
        $GLOBALS['POSTA_OPT']['CIS_POSTA_SKARTACE'][$this->skartace] = $ret;
      }
      $this->spisZnakLhuta = $ret['DOBA'];
      $this->spisZnakPismeno = $ret['SKAR_ZNAK'];

      $this->spisVyrazeno = $ret['ROK_SKARTACE']; //TODO

      $this->spisZnakKod = $ret['KOD'];
      $this->spisZnakText = $ret['KOD'] . ' ' . $ret['TEXT'];
    }

    $ret['CJ1']=$this->db->Record[$this->cj1_column];
    $ret['CJ2']=$this->db->Record[$this->cj2_column];
    $ret['ZARIZENI']=$this->db->Record[$this->zarizeni];

    if ($ret['TYP_DOKUMENTU'] == '') $ret['TYP_DOKUMENTU'] = 'A';

  }

  /** 
   *  Vytvoreni Instance singletonu pro jednotlive id
   * 
   *@author onma
   *@param int $id - id dokumentu
   */
  public static function getInstance($id) {
    if (self::$DokumentInstance[$id] === NULL) {
      self::$DokumentInstance[$id] = new self($id);
    }
    return self::$DokumentInstance[$id];
  }

  function GetDocInfo($id)  {
    if (!$id) $id = 0;
    if (isset($GLOBALS['POSTA_OPT']['POSTA'][$id])) return $GLOBALS['POSTA_OPT']['POSTA'][$id];
    $sql = 'select * from posta where id='.$id;
    $this->_sql_query($sql);
    $this->db->Next_Record();
    $ret=$this->db->Record;
    $ret['CJ1']=$this->db->Record[$this->cj1_column];
    $ret['CJ2']=$this->db->Record[$this->cj2_column];
    $ret['ZARIZENI']=$this->db->Record[$this->zarizeni];

    if ($ret['TYP_DOKUMENTU'] == '') $ret['TYP_DOKUMENTU'] = 'A';
    $GLOBALS['POSTA_OPT']['POSTA'][$id] = $ret;
    return $ret;
  }

  function GetDocReferent($id)
  {
    $doc=$this->GetDocInfo($id);
    return $doc['REFERENT'];
  }

  function FormatCisloJednaci($id = 0, $add_podlomeni = true, $add_exemplar = true) {
    include_once(FileUp2('.admin/security_name.inc'));

    $text_cisla = $this->cj1 . '/' . $this->cj2;
    if ($this->cj1 == 0 && $this->cj2 == 0) return '';
    $referent=$this->referent_id ? ('/' . UkazUsera($this->referent_id,true)) : '/--';
//    $odbor=$this->_VratZkratkuSpisovehoUzlu($this->odbor);
    $odbor = $this->uzel_text;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU1"]) $text_cislo_jednaci=$GLOBALS["CONFIG"]["OZNACENI_SPIS"].$text_cisla;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU2"]) $text_cislo_jednaci=$odbor."/".$text_cisla;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU3"]) $text_cislo_jednaci=$odbor."/".$this->cj1."/".substr($this->cj2, -2);

    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU4"]) {
      $text_cislo_jednaci = $this->cj1;
      if ($podcislo<>0) $text_cislo_jednaci.='-'.$podcislo;
      $text_cislo_jednaci.='/'.$this->cj2.'-'.$GLOBALS["CONFIG"]["OZNACENI_SPIS"].'/'.$nadodbor.'/'.$odbor;
    }

    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU5"]) {
//      $nadodbor_id=EedTools::VratOdbor($this->superodbor);
      $nadodbor_id=$this->superodbor;
      $nadodbor=UkazOdbor($nadodbor_id,true);
      $text_cislo_jednaci=$this->cj1;
      $text_cislo_jednaci=$GLOBALS["CONFIG"]["OZNACENI_SPIS"].$nadodbor.'/'.$this->cj1.'/'.$this->cj2;
    }

    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU6"]) {
      $text_cislo_jednaci=$GLOBALS["CONFIG"]["OZNACENI_SPIS"].$odbor.'/'.$this->cj1.'/'.$this->cj2.'/'.$this->referent_zkratka;
    }


    If ($nazev_spisu) $text_cislo_jednaci.="-".$nazev_spisu;
    $tvar_cj_dokument = $GLOBALS['CONFIG_POSTA']['HLAVNI'][$this->superodbor]['tvar_cj'];
    if (!$tvar_cj_dokument) $tvar_cj_dokument = $GLOBALS['CONFIG_POSTA']['HLAVNI']['tvar_cj'];;
    if (strlen($tvar_cj_dokument)>1) {
      $text_cislo_jednaci = $tvar_cj_dokument;
      $text_cislo_jednaci = str_replace('%PORAD%', $this->cj1, $text_cislo_jednaci);	
      $text_cislo_jednaci = str_replace('%ROK%', $this->cj2, $text_cislo_jednaci);
      $text_cislo_jednaci = str_replace('%ODBOR%', $odbor, $text_cislo_jednaci);

      if ($this->referent_id) $text_cislo_jednaci = str_replace('%REFERENT%', '/' . $referent, $text_cislo_jednaci);
      else $text_cislo_jednaci = str_replace('%REFERENT%', '', $text_cislo_jednaci);

      $this->cislo_jednaci_zaklad = $text_cislo_jednaci;
      $this->cislo_jednaci_zaklad = str_replace('%PODLOMENI%', '', $this->cislo_jednaci_zaklad);
      $this->cislo_jednaci_zaklad = str_replace('%EXEMPLAR%', '', $this->cislo_jednaci_zaklad);

      if ($this->podlomeni && $add_podlomeni) $text_cislo_jednaci = str_replace('%PODLOMENI%', '-' . $this->podlomeni, $text_cislo_jednaci);
      else $text_cislo_jednaci = str_replace('%PODLOMENI%', '', $text_cislo_jednaci);

      if ($this->exemplar && $add_exemplar) $text_cislo_jednaci = str_replace('%EXEMPLAR%', '-' . $this->exemplar, $text_cislo_jednaci);
      else $text_cislo_jednaci = str_replace('%EXEMPLAR%', '', $text_cislo_jednaci);

    }
    
//    if ($this->text_cj || $this->cj1 == 0) $text_cislo_jednaci = $this->text_cj;
    $res=$text_cislo_jednaci;
    return $res;    
  }


  function SeznamSchvalovatelu($id) {
    $sql = 'select * from posta_schvalovani where posta_id='.$id;
    $this->_sql_query($sql);
    $res=array();
    while ($this->db->Next_Record()) {
      $res[]=$this->db->Record['SCHVALUJICI_ID'];     
    }    
    return $res;
  }

  function SetMainDoc($id=0) {
//     if ($id > 0) {
//       $sql = 'update posta set main_doc=1 where id=' . $id;
//       $this->_sql_query($sql);
//     }
  }
}
