<?php
require_once('EedCj.inc');

/**
* trida EED_SpisovnaSimple, ktera nenacita vsechny dokumenty z CJ
*@author onma  
*/
class EedSpisovnaSimple extends EedCj {
  /**
  * Constructor
  * @author onma  
  * @param int $id - id dokumentu   
  */
  
  var $spisovyZnak;
  var $spisZnakLhuta;
  var $spisZnakKod;
  var $spisZnakPismeno;
  var $spisZnakText;
//   var $spisForma;
//   var $spisVyrazeno;
//   var $spisListu;
//   var $spisPriloh;
//   var $spisDigitalnich;

  /* staticka promenna pro singleton */
  private static $SpisovnaSimpleInstance;
  
  function EedSpisovnaSimple($id) {
    parent::EedCj($id);
    $skartace = $this->skartace_id;
    if (!$skartace) $skartace = 0;

    $sql='select * from cis_posta_skartace where id = '.$skartace;
    $this->_sql_query($sql);
    $this->db->Next_Record();
    $ret=$this->db->Record;

    $this->spisZnakLhuta = $ret['DOBA'];
    $this->spisZnakPismeno = $ret['SKAR_ZNAK'];

    $this->spisVyrazeno = $ret['ROK_SKARTACE']; //TODO

    $this->spisZnakKod = $ret['KOD'];
    $this->spisZnakText = $ret['KOD'] . ' ' . $ret['TEXT'];
  }

  /** 
   *  Vytvoreni Instance singletonu pro jednotlive id
   * 
   *@author onma
   *@param int $id - id dokumentu
   */
  public static function getInstance($id) {
    if (self::$SpisovnaSimpleInstance[$id] === NULL) {
      self::$SpisovnaSimpleInstance[$id] = new self($id);
    }
    return self::$SpisovnaSimpleInstance[$id];
  }
 
  function JeVeSpisovne() {
//    if (!$spis_id || $spis_id = 0) $spis_id = $this->spis_id;
    $sql = 'select * from posta_spisovna where dokument_id=' . $this->spis_id;
    $this->_sql_query($sql);
    $this->db->Next_Record();
    $ret=$this->db->Record;
    if ($ret['ID']<0) return false;
    else 
      return $ret;
  }    

  function GetListuADigialnichVSpisovne() {
    $sql = 'select * from posta_spisovna where dokument_id=' . $this->spis_id;
    $this->_sql_query($sql);
    $this->db->Next_Record();
    $ret=$this->db->Record;

    $res = array();
    $res['listu'] = $ret['LISTU']; 
    $res['priloh'] = $ret['PRILOHY']; 
    $res['digitalnich'] = $ret['DIGITALNI'];  
   
    return $res;
  }

  function NazevSpisovny() {
    $spisovna = $this->JeVeSpisovne();
    $spisovna_id = $spisovna['SPISOVNA_ID'] ? $spisovna['SPISOVNA_ID'] : 0;
    $sql = 'select * from posta_cis_spisovna where id=' . $spisovna_id;
   $this->_sql_query($sql);
    $this->db->Next_Record();
    $data = $this->db->Record;
    $ret = array();
    $ret['SPISOVNA'] = $data['SPISOVNA'];
    $ret['PREDANO'] = $spisovna['DATUM_PREDANI'];
    $ret['PREVZAL_ID'] = $spisovna['PREVZAL_ID'];
    $ret['PREVZAL_JMENO'] = $this->GetUserName($spisovna['PREVZAL_ID']);
    return $ret;
     
  }  
}
