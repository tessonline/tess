<?php
require_once('EedCj.inc');
/**
* trida EED_doc, pro praci s jednotlivymi dokumenty
*@author onma  
*/
class EedSpisovna extends EedCj {
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
  var $spisForma;
  var $spisVyrazeno;
  var $spisListu;
  var $spisPriloh;
  var $spisDigitalnich;

  /* staticka promenna pro singleton */
  private static $SpisovnaInstance; 
  
  function EedSpisovna($id) {
    parent::EedCj($id);
    $skartace = $this->skartace_id;
    if (!$skartace) $skartace = 0;

    $sql='select * from cis_posta_skartace where id = ' . $skartace;
    $this->_sql_query($sql);
    $this->db->Next_Record();
    $ret=$this->db->Record;

    $this->spisZnakLhuta = $ret['DOBA'];
    $this->spisZnakPismeno = $ret['SKAR_ZNAK'];

    $this->spisVyrazeno = $ret['ROK_SKARTACE']; //TODO

    list($this->spisZnakKod, $this->spisZnakText) = explode(' ', $ret['TEXT'], 2);

    $this->spisForma = $this->GetCjTypUlozeni($this->spis_id);
    $res = $this->GetListuADigialnichVCj($this->spis_id);

    $this->spisListu = $res['listu']; 
    $this->spisPriloh = $res['priloh']; 
    $this->spisDigitalnich = $res['digitalnich']; 
  
    $res2 = $this->GetListuADigialnichVSpisovne();
    if ($res2['listu']>0) $this->spisListu = $res2['listu'];
    if ($res2['priloh']>0) $this->spisPriloh = $res2['priloh'];
    if ($res2['digitalnich']>0) $this->spisDigitalnich = $res2['digitalnich'];

    if (!$this->spisListu) $this->spisListu = 0;
    if (!$this->spisPriloh) $this->spisPriloh = 0;
    if (!$this->spisDigitalnich) $this->spisDigitalnich = 0;

  }

  /** 
   *  Vytvoreni Instance singletonu pro jednotlive id
   * 
   *@author onma
   *@param int $id - id dokumentu
   */
  public static function getInstance($id) {
    if (self::$SpisovnaInstance[$id] === NULL) {
      self::$SpisovnaInstance[$id] = new self($id);
    }
    return self::$SpisovnaInstance[$id];
  }
 
  function JeVeSpisovne() {
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
