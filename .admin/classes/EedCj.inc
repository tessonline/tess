<?php
require_once ('EedDokument.inc');

class EedCj extends EedDokument{
  var $spis_id;
  var $skartace_id;
  
  /**
  * Constructor
  * @author onma
  * @description inicializuje objekt Eed_doc (potomek z DB atd.)    
  * @param id - identifikátor dokumentu  
  */
  function EedCj($id=0){

    if (!$id) $id = 0;
    parent::EedDokument($id);
    $cj = $this->GetCjInfo($id);
    $this->spis_id = $cj['SPIS_ID'];
  }

  function FormatCJednaci($doc_id=0) {
    if ($doc_id <> $this->id_dokument) {
      $doc = new EedDokument($doc_id);
      $res = $doc->cislo_jednaci_zaklad;
    }
    else {
      $res = $this->cislo_jednaci_zaklad;
    }
    
    if ($res->main_doc == 0) {
     $this->SetMainDoc($doc_id);
    }
    return $res;
  }

  function getCisloSpisu($id = 0){
    $sql='select cislo_jednaci1,cislo_jednaci2 from posta where id='.$id;
    $this->_sql_query($sql);
    $this->db->Next_Record();
    $ret = $this->db->Record;
    return $ret;
  }
  

  /**
  * @author onma
  * @name GetWhereForCJ
  * @description vrátí sql podmínku pro vyhledání dokumentů v čj.    
  * @param int $id (id dokumentu, které má být v cj)
  */    
  function GetWhereForCJ($id = 0){
    if (isset($GLOBALS['POSTA_OPT']['POSTA'][$id])) {
      $ret = $GLOBALS['POSTA_OPT']['POSTA'][$id];
    }
    else {
      $sql='select * from posta where id='.$id;
      $this->_sql_query($sql);
      $this->db->Next_Record();
      $ret = $this->db->Record;
      $GLOBALS['POSTA_OPT']['POSTA'][$id] = $ret;
    }
    $superodbor = $ret['SUPERODBOR'] ? $ret['SUPERODBOR']:0;
    if ($superodbor == 0 )
    {
      $this->ShowError('Není správně zadán superodbor!');
      $podminka=" CISLO_SPISU1=".$ret['CISLO_SPISU1']." AND CISLO_SPISU2=".$ret['CISLO_SPISU2'];
    }
    elseif ($GLOBALS['CONFIG']['USE_SUPERODBOR'])
      $podminka=" CISLO_SPISU1=".$ret['CISLO_SPISU1']." AND CISLO_SPISU2=".$ret['CISLO_SPISU2']." AND SUPERODBOR=".$superodbor;
    else
      $podminka=" CISLO_SPISU1=".$ret['CISLO_SPISU1']." AND CISLO_SPISU2=".$ret['CISLO_SPISU2'];

    if ($ret['CISLO_SPISU1'] == 0) {
      $podminka = 'id=' . $id;
    }
    if ($ret['MAIN_DOC']>100) {
      $podminka = 'id=' . $id . ' or id_puvodni=' . $id;
    }
    return $podminka;
  }

  /**
   * @author onma
   * @name GetCjInfo
   * @description vrátí základní informace o čísle jednacím, připadně celém spisu    
   * @param int $doc_id
   */    
  function GetCjInfo($doc_id,$nedelat_spis=false) {
    $ret = array();
    $ret_pom = array();

//echo '<hr/>Nacitam cj pro id ' . $doc_id. ' <br/>';
    $where=$this->GetWhereForCJ($doc_id);
//    $sql='select * from posta where '.$where.' and stornovano is null order by id asc';
    $sql='select * from posta where '.$where.' order by podcislo_spisu asc,id asc';
    $this->_sql_query($sql);
    $this->db->Next_Record();
    $ret_pom = $this->db->Record;
    $ret=$this->GetDocInfo($ret_pom['ID']);
    $ret['SPIS_ID']=$ret_pom['ID'];
    
    //spis..
    $spis = false;
    $spis_id = $this->JeSpis($ret['SPIS_ID']);
    if ($spis_id<>$ret['SPIS_ID'] && $spis_id>0 && !$nedelat_spis)
    {
      $ret=$this->GetDocInfo($spis_id);
      $ret['SPIS_ID']=$spis_id;
    }

    $ret['JE_ARCH'] = false;
    $ret['CELE_CISLO'] = $this->FormatCJednaci($ret['SPIS_ID']);
    $ret['TEXT_CJ']=$ret['CELE_CISLO'];
    $ret['JE_SPIS'] = false;

    if ($spis_id>0) {
      $ret['NAZEV']='spis ';
      $ret['JE_SPIS'] = true;
      $ret['JID_SPISU'] = $GLOBALS['CONFIG']['ID_PREFIX'].'SP'.$spis_id;

      $typovy_spis_id = $this->JeTypovySpis($ret['SPIS_ID']);
      $dil_typovy_spis_id = $this->JeDilTypovySpis($ret['SPIS_ID']);
      if ($typovy_spis_id>0) {
      	if ($dil_typovy_spis_id>0) {
      		$spis_id = $dil_typovy_spis_id;
      		$ret['SPIS_ID']=$spis_id;
      	}
      	$typovy_spis_idMain = $this->TypovySpisId($spis_id);
//     		$ret['SPIS_ID'] = $spis_id;
        $ret['JID_SPISU'] = $GLOBALS['CONFIG']['ID_PREFIX'].'TS'.$typovy_spis_idMain;
      	$ret['NAZEV']='díl typového spisu ';
        $ret['JE_TYPOVY_SPIS'] = true;
        $ret['TYPOVY_SPIS_ID'] = $typovy_spis_id;
        $ret['TYPOVY_SPIS_MAINID'] = $typovy_spis_idMain;

      	if ($doc_id == $typovy_spis_idMain)	$ret['SPIS_ID']=$doc_id;

        $ret['CELE_CISLO'] = $this->FormatCJednaci($typovy_spis_idMain);
        //$ret['CELE_CISLO'] = $this->FormatCisloJednaci($typovy_spis_idMain);
//        $ret['CELE_CISLO'] = $typovy_spis_idMain;

      }

    }
    else {
      $ret['NAZEV']='číslo jednací '; 
      if ($this->podlomeni>0) {
        $ret['JE_ARCH'] = true;
        $ret['JE_SPIS'] = true;
        $ret['NAZEV'] = 'sběrný arch ';
        $nazev = $this->NazevSpisu($doc_id);
        $ret['NAZEV_SPISU'] = $nazev;
      }
    }
    if ($ret['MAIN_DOC']>100) $ret['NAZEV']='';
    $ret['CELY_NAZEV']=$ret['NAZEV'] . $ret['TEXT_CJ'];

    if ($spis_id>0) {
      $nazev = $this->NazevSpisu($spis_id);
      $ret['NAZEV_SPISU'] = $nazev;
      $ret['NAZEV_TYPOVEHO_SPISU'] = $this->NazevSpisu($typovy_spis_idMain);

      if ($nazev<>'') $ret['CELY_NAZEV'] .= ' - '. $nazev;
    }
    $this->ShowDebug($ret);

    if (!$ret['SPIS_ID']) $ret['SPIS_ID'] = $doc_id; // kvuli stornovanym zaznamum
//  echo '<hr/>hotovo pro id ' . $doc_id. ' <br/>';
    return $ret;
  }
  
  /**
   * @author onma
   * @name GetDocsInCj
   * @description vrátí seznam dokumentů v daném čísle jednacím
   * @param int $doc_id
   */
  function GetDocsInSimpleCj($doc_id) {
    $where=$this->GetWhereForCJ($doc_id);

    $sql='select * from posta where '.$where.' and stornovano is null';
    $ret = array();
    $this->_sql_query($sql);
    while ($this->db->Next_Record())
      $ret[]=$this->db->Record['ID'];
    $dalsi_id=$this->SeznamCJvSpisu($doc_id);
    $ret = array_unique ($ret);
    return $ret;
  }

  /**
   * @author onma
   * @name GetDocsInCj
   * @description vrátí seznam dokumentů v daném čísle jednacím
   * @param int $doc_id
   */
  function GetDocsInCj($doc_id) {
    $where=$this->GetWhereForCJ($doc_id);

    $sql='select * from posta where '.$where.' and stornovano is null';
    $ret = array();
    $this->_sql_query($sql);
    while ($this->db->Next_Record())
      $ret[]=$this->db->Record['ID'];
    $dalsi_id=$this->SeznamCJvSpisu($doc_id);
    if (count($dalsi_id)>0)
    while (list($key,$val)=each($dalsi_id))
    {
      $where=$this->GetWhereForCJ($val);
      $sql='select * from posta where '.$where.' and stornovano is null';
      $this->_sql_query($sql);
      while ($this->db->Next_Record())
        $ret[]=$this->db->Record['ID'];

    }
    $ret = array_unique ($ret);
    return $ret;
  }

/**
   * @author onma
   * @name GetDocsInCj
   * @description vrátí seznam dokumentů v daném čísle jednacím
   * @param int $doc_id
   */
  function GetDocsInTypSpis($doc_id) {
//    $where=$this->GetWhereForCJ($doc_id);
//    $sql='select * from posta where '.$where.' and stornovano is null';
    $sql='select * from cis_posta_spisy where typovy_spis_id='.$doc_id.' ';
    $ret = array();
    $this->_sql_query($sql);
    while ($this->db->Next_Record()) {
      if ($this->db->Record['SPIS_ID']>1) $ret[]=$this->db->Record['SPIS_ID'];
      if ($this->db->Record['DALSI_SPIS_ID']>1) $ret[]=$this->db->Record['DALSI_SPIS_ID'];
    }
    $ret = array_unique ($ret);
    $pomocne = $ret;

    if (count($pomocne)>0)
    while (list($key,$val)=each($pomocne))  {
      $where=$this->GetWhereForCJ($val);
      $sql='select * from posta where '.$where.' and stornovano is null';
      $this->_sql_query($sql);
      while ($this->db->Next_Record())
        $ret[]=$this->db->Record['ID'];

    }
    return $ret;
  }

  /**
   * @author onma
   * @name GetDocsInCj
   * @description vrátí seznam dokumentů v daném čísle jednacím    
   * @param int $doc_id
   */    
  function GetListuADigialnichVCj($doc_id) {
    $where=$this->GetWhereForCJ($doc_id);
    $sql='select * from posta where '.$where.' and stornovano is null';
    $ret = array();
    $this->_sql_query($sql);
    while ($this->db->Next_Record()) {
      if ($this->db->Record['TYP_DOKUMENTU'] == 'A') {
        $ret[listu] = $ret[listu] + $this->db->Record['LISTU'];
        $ret[priloh] = $ret[priloh] + $this->db->Record['LISTU'];
      }
      else {
        $ret[digitalnich]++;
      }
    }
    $dalsi_id = $this->SeznamCJvSpisu($doc_id);
    if (count($dalsi_id)>0) {
      while (list($key,$val) = each($dalsi_id)) {
        $where = $this->GetWhereForCJ($val);
        $sql = 'select * from posta where '.$where.' and stornovano is null';
        $this->_sql_query($sql);
        while ($this->db->Next_Record()) {
          if ($this->db->Record['TYP_DOKUMENTU'] == 'A') {
            $ret[listu] = $ret[listu] + $this->db->Record['LISTU'];
            $ret[priloh] = $ret[priloh] . $this->db->Record['LISTU'];
          }
          else {
            $ret[digitalnich]++;
          }
        }
      }
    }
    return $ret;
  }

  /**
  * @author onma
  * @name GetCjTypUlozeni
  * @description vrátí ulozeni cj analogove/hybridne/digitalne    
  * @param int $doc_id
  */    
  function GetCjTypUlozeni($doc_id) {
    $docs=$this->GetDocsInCj($doc_id);
    $ret = '';
    foreach($docs as $doc_id) {
      $doc = $this->GetDocInfo($doc_id);
      if ($doc['TYP_DOKUMENTU']=='D' && $ret == '') $ret = 'D'; 
      elseif ($doc['TYP_DOKUMENTU']=='A' && $ret == '') $ret = 'A'; 
      elseif ($doc['TYP_DOKUMENTU']=='A' && $ret == 'D') $ret = 'H'; 
      elseif ($doc['TYP_DOKUMENTU']=='D' && $ret == 'A') $ret = 'H';
    }    
    return $ret;
  }
  
  /**
   * @author onma
   * @name  _GetKrizCJ
   * @description privátní, rekurzivní funkce pro zjištění křížového odkazu    
   * @param int $doc_id,$sloupec
   */    
  function _GetKrizCJ($doc_id,$sloupec)
  {
    if ($sloupec=='PUVODNI_SPIS') $column='NOVY_SPIS'; else $column='PUVODNI_SPIS';
    $sql='select '.$column.' as HODNOTA from posta_krizovy_spis where '.$sloupec.'='.$doc_id;
    $this->_sql_query($sql);
    while ($this->db->Next_Record())
    {
      $ret[]=$this->db->Record['HODNOTA'];
      $cj=new EedCj($this->db->Record['HODNOTA']);
      $ret[]=$cj->_GetKrizCJ($this->db->Record['HODNOTA'],$sloupec);
    }
    if (count($ret)>0) return implode(',',$ret);
    else return '-1';
  }
  
  /**
   * @author onma
   * @description Funkce, která vrátí předchozí číslo jednací v křížovém odkazu    
   * @param int $doc_id - Identifikátor
   */    
  function GetPredchoziCJ($doc_id)
  {
     $ret=$this->_GetKrizCJ($doc_id,'NOVY_SPIS');
     $ret=explode(',',$ret);
     while (list($key,$val)=each($ret)) //vycistime od -1
       if ($val==-1) UNSET($ret[$key]);
     return $ret; 
  }

  /**
   * @author onma
   * @description Funkce, která vrátí následující číslo jednací v křížovém odkazu    
   * @param int $doc_id - Identifikátor
   */    
  function GetNasledujiciCJ($doc_id)
  {
     $ret=$this->_GetKrizCJ($doc_id,'PUVODNI_SPIS');
     $ret=explode(',',$ret);
     while (list($key,$val)=each($ret)) //vycistime od -1
       if ($val==-1) UNSET($ret[$key]);
     return $ret; 
  }

  /**
   * @author onma
   * @name GetVypraveneDoc
   * @description Funkce, která vrátí sezam vypravených dokumentů
   * @param int $doc_id - Identifikátor
   */
  function GetVypraveneDoc($doc_id) {
    $ret=array();
    $where=$this->GetWhereForCJ($doc_id);
    $sql="select * from posta where odeslana_posta='t' and odes_typ<>'X' and odes_typ<>'Z' and datum_vypraveni is not null and ".$where;
    $this->_sql_query($sql);
    while ($this->db->Next_Record())
      $ret[]=$this->db->Record['ID'];
    return $ret;
  }
  /**
   * @author onma
   * @name GetVypraveni
   * @description Funkce, která vrátí sezam dokumentů, které jsou vypraveními k hlavnimu dokumentu
   * @param int $doc_id - Identifikátor
   */
  function GetVypraveni($doc_id) {
    $ret=array();
    $where=$this->GetWhereForCJ($doc_id);
    $sql="select * from posta where odeslana_posta='t' and odes_typ<>'X' and odes_typ<>'Z' and ".$where;
    $this->_sql_query($sql);
    while ($this->db->Next_Record())
      $ret[]=$this->db->Record['ID'];
    return $ret;
  }

  /** funkce pro spis?
   *
   */
  function JeSpis($spis_id = 0) {
    if (!$spis_id) $spis_id = 0;
    if ($spis_id == 0) return false;
    if (isset($GLOBALS['POSTA_OPT']['JE_SPIS'][$spis_id]['SPIS_ID']) && $spis_id>0) {return $GLOBALS['POSTA_OPT']['JE_SPIS'][$spis_id]['SPIS_ID'];} //usetrime si opakovane naciatni
    if (isset($GLOBALS['POSTA_OPT']['NENI_SPIS'][$spis_id]['SPIS_ID']) && $spis_id>0) {return false;} //usetrime si opakovane naciatni
    $sql="select * from cis_posta_spisy where spis_id=$spis_id or dalsi_spis_id=$spis_id order by id asc";
//    $sql="select * from cis_posta_spisy where spis_id=$spis_id and dalsi_spis_id>=0 order by id asc";
    $this->_sql_query($sql);
    $this->db->Next_Record();
    if (!$this->db->Record['ID']) {
      $GLOBALS['POSTA_OPT']['NENI_SPIS'][$spis_id] = $spis_id;
    }
    else
      $GLOBALS['POSTA_OPT']['JE_SPIS'][$spis_id] = $this->db->Record;
    return $this->db->Record['SPIS_ID'];
  }

  function JeTypovySpis($spis_id = 0) {
    if (!$spis_id) $spis_id = 0;
    if (isset($GLOBALS['POSTA_OPT']['JE_TYPOVY_SPIS'][$spis_id]['TYPOVY_SPIS']) && $spis_id>0) {return $GLOBALS['POSTA_OPT']['JE_TYPOVY_SPIS'][$spis_id]['TYPOVY_SPIS'];} //usetrime si opakovane naciatni
    if (isset($GLOBALS['POSTA_OPT']['NENI_TYPOVY_SPIS'][$spis_id]) && $spis_id>0) {return false;} //usetrime si opakovane naciatni

    $sql="select * from cis_posta_spisy where (spis_id=$spis_id or dalsi_spis_id=$spis_id) and typovy_spis>0 limit 1";
    $this->_sql_query($sql);
    $this->db->Next_Record();
    if (!$this->db->Record['ID']) {
      $GLOBALS['POSTA_OPT']['NENI_TYPOVY_SPIS'][$spis_id] = $spis_id;
    }
    else
      $GLOBALS['POSTA_OPT']['JE_TYPOVY_SPIS'][$spis_id] = $this->db->Record;
    return $this->db->Record['TYPOVY_SPIS'];
  }
  function TypovySpisId($spis_id = 0) {
    if (!$spis_id) $spis_id = 0;
    if (isset($GLOBALS['POSTA_OPT']['JE_TYPOVY_SPIS'][$spis_id]['TYPOVY_SPIS_ID']) && $spis_id>0) {return $GLOBALS['POSTA_OPT']['JE_TYPOVY_SPIS'][$spis_id]['TYPOVY_SPIS_ID'];} //usetrime si opakovane naciatni
    if (isset($GLOBALS['POSTA_OPT']['NENI_TYPOVY_SPIS'][$spis_id]) && $spis_id>0) {return false;} //usetrime si opakovane naciatni

    $sql="select * from cis_posta_spisy where (spis_id=$spis_id or dalsi_spis_id=$spis_id) and typovy_spis>0 limit 1";
    $this->_sql_query($sql);
    $this->db->Next_Record();
    if (!$this->db->Record['ID']) {
      $GLOBALS['POSTA_OPT']['NENI_TYPOVY_SPIS'][$spis_id] = $spis_id;
    }
    else
      $GLOBALS['POSTA_OPT']['JE_TYPOVY_SPIS'][$spis_id] = $this->db->Record;
    return $this->db->Record['TYPOVY_SPIS_ID'];
  }
  function JeDilTypovySpis($spis_id = 0) {
  	if (!$spis_id) $spis_id = 0;
    if (isset($GLOBALS['POSTA_OPT']['JE_TYPOVY_SPIS'][$spis_id]['SPIS_ID']) && $spis_id>0) {return $GLOBALS['POSTA_OPT']['JE_TYPOVY_SPIS'][$spis_id]['SPIS_ID'];} //usetrime si opakovane naciatni
  	$sql="select * from cis_posta_spisy where (spis_id=$spis_id  or dalsi_spis_id=$spis_id) and typovy_spis>0 limit 1";
  	$this->_sql_query($sql);
  	$this->db->Next_Record();
    $GLOBALS['POSTA_OPT']['JE_TYPOVY_SPIS'][$spis_id] = $this->db->Record;
  	return $this->db->Record['SPIS_ID'];
  }
  
  function NazevSpisu($spis_id = 0, $dil = 0) {
    if (!$spis_id) $spis_id = 0;
    if ($spis_id == 0) return '';
    if (isset($GLOBALS['POSTA_OPT']['CIS_POSTA_SPISY'][$spis_id]['NAZEV_SPISU'])) return $GLOBALS['POSTA_OPT']['CIS_POSTA_SPISY'][$spis_id]['NAZEV_SPISU'];

//    $sql="select nazev_spisu from cis_posta_spisy where spis_id=$spis_id or dalsi_spis_id=$spis_id order by id asc";
    $sql="select nazev_spisu from cis_posta_spisy where spis_id=$spis_id and dalsi_spis_id=0 order by id asc";
    if ($dil>0)
      $sql="select nazev_spisu from cis_posta_spisy where typovy_spis_id=$spis_id and soucast=0 and dil=0 order by id asc";
    $this->_sql_query($sql);

    $this->db->Next_Record();
    $GLOBALS['POSTA_OPT']['CIS_POSTA_SPISY'][$spis_id]['NAZEV_SPISU'] = $this->db->Record['NAZEV_SPISU'];
    return $this->db->Record['NAZEV_SPISU'];
  }

  function NazevTypovehoSpisu($spis_id = 0) {
    if (!$spis_id) $spis_id = 0;
    $sql="select nazev_spisu from cis_posta_spisy where typovy_spis_id=$spis_id and soucast=0 and dil=0 order by id asc";
    $this->_sql_query($sql);
    $this->db->Next_Record();
    return $this->db->Record['NAZEV_SPISU'];
  }

  function NazevSablonyTypovehoSpisu($spis_id = 0) {
    if (!$spis_id) $spis_id = 0;

    $sql="select nazev from posta_cis_typovy_spis where id=$spis_id";
    $this->_sql_query($sql);
    $this->db->Next_Record();
    return $this->db->Record['NAZEV'];
  }

  /** funkce pro spis?
   *
   */
  function SpisVazba($spis_id, $spis_id_dalsi = 0) {
    $sql="select * from cis_posta_spisy where spis_id=$spis_id and dalsi_spis_id=$spis_id_dalsi order by id asc";
    $this->_sql_query($sql);
    $this->db->Next_Record();
    return $this->db->Record;
  }

  /** funkce pro spis?
   *
   */
  function SeznamCJvSpisu($cj_id) {
    $ret=array();
    $pouzita_cj = array();
    $cj_info = $this->GetCjInfo($cj_id);   
    $spis_id = $cj_info['SPIS_ID'];
//    $sql="select DISTINCT ON (novy_spis) * from cis_posta_spisy where (spis_id=$cj_id or dalsi_spis_id=$cj_id) and dalsi_spis_id>0 and puvodni_spis<>novy_spis order by novy_spis desc, dalsi_spis_id desc";
    $sql="select  * from cis_posta_spisy where (spis_id=$cj_id or dalsi_spis_id=$cj_id) and dalsi_spis_id>0 and puvodni_spis<>novy_spis order by dalsi_spis_id desc";
    $this->_sql_query($sql);
    while ($this->db->Next_Record()) {
      if (in_array($this->db->Record['NOVY_SPIS'], $pouzita_cj)) continue;
      else $pouzita_cj[] = $this->db->Record['NOVY_SPIS'];
      if ($this->db->Record['SPIS_ID']<>$spis_id) $ret[]=$this->db->Record['SPIS_ID'];
      if ($this->db->Record['DALSI_SPIS_ID']<>$spis_id) $ret[]=$this->db->Record['DALSI_SPIS_ID'];
    }
    $ret = array_unique($ret);
    return $ret;
  }

  function SeznamCJvTypovemSpisu($cj_id, $soucast_id, $dil) {
    $ret=array();
    $pouzita_cj = array();
    $cj_info = $this->GetCjInfo($cj_id);
    $spis_id = $cj_info['SPIS_ID'];
//    $sql="select DISTINCT ON (novy_spis) * from cis_posta_spisy where (spis_id=$cj_id or dalsi_spis_id=$cj_id) and dalsi_spis_id>0 and puvodni_spis<>novy_spis order by novy_spis desc, dalsi_spis_id desc";
    $sql="select  * from cis_posta_spisy where (typovy_spis_id=$cj_id) and dalsi_spis_id>-1 and soucast=$soucast_id and dil=$dil order by dalsi_spis_id asc";
    $this->_sql_query($sql);
    while ($this->db->Next_Record()) {
        if($this->db->Record['DALSI_SPIS_ID'] == 0) 	$ret[]=$this->db->Record['SPIS_ID'];
        else $ret[] = $this->db->Record['DALSI_SPIS_ID'];
    }
    $ret = array_unique($ret);
    return $ret;
  }

  function SeznamDiluvTypovemSpisuSoucasti($cj_id, $soucast_id) {
  	$ret=array();
  	$pouzita_cj = array();
  	$cj_info = $this->GetCjInfo($cj_id);
  	$spis_id = $cj_info['SPIS_ID'];
  	//    $sql="select DISTINCT ON (novy_spis) * from cis_posta_spisy where (spis_id=$cj_id or dalsi_spis_id=$cj_id) and dalsi_spis_id>0 and puvodni_spis<>novy_spis order by novy_spis desc, dalsi_spis_id desc";
  	$sql="select  * from cis_posta_spisy where (typovy_spis_id=$cj_id) and dalsi_spis_id=-1 and soucast=$soucast_id order by dil asc";
  	$this->_sql_query($sql);
  	while ($this->db->Next_Record()) {
  		$dil = $this->db->Record['DIL'];  		
  		$id = $this->db->Record['ID'];  		
  		$ret[$dil] = $this->db->Record;
  		$ret[$dil]['JID'] = $GLOBALS['CONFIG']['ID_PREFIX'] . 'TSD' . $id;
  	}
  	return $ret;
  }
  
  function GetDil($dil_id) {
  	$ret=array();
  	$pouzita_cj = array();
  	//    $sql="select DISTINCT ON (novy_spis) * from cis_posta_spisy where (spis_id=$cj_id or dalsi_spis_id=$cj_id) and dalsi_spis_id>0 and puvodni_spis<>novy_spis order by novy_spis desc, dalsi_spis_id desc";
  	$sql="select  * from cis_posta_spisy where (id=$dil_id) and dalsi_spis_id=-1 order by dil asc";
  	$this->_sql_query($sql);
  	while ($this->db->Next_Record())
//  	$this->db->Next_Record();
    {
  		$dil = $this->db->Record['DIL'];
  		$id = $this->db->Record['ID'];
  		$ret = $this->db->Record;
  		$ret['JID'] = $GLOBALS['CONFIG']['ID_PREFIX'] . 'TSD' . $id;
  	}
  	return $ret;
  }
  
  function GetSoucast($soucast_id) {
  	$ret=array();
  	$pouzita_cj = array();
  	//    $sql="select DISTINCT ON (novy_spis) * from cis_posta_spisy where (spis_id=$cj_id or dalsi_spis_id=$cj_id) and dalsi_spis_id>0 and puvodni_spis<>novy_spis order by novy_spis desc, dalsi_spis_id desc";
  	$sql="select  * from cis_posta_spisy where (id=$soucast_id) and dalsi_spis_id=-1 order by dil asc";
  	$this->_sql_query($sql);
  	while ($this->db->Next_Record()) {
  		$dil = $this->db->Record['SOUCAST'];
  		$id = $this->db->Record['ID'];
  		$ret = $this->db->Record;
  		$ret['JID'] = $GLOBALS['CONFIG']['ID_PREFIX'] . 'TSS' . $id;
  	}
  	return $ret;
  }
  
  
  function SpisZnak($spis_id) {
    $docIDS = $this->GetDocsInCj($spis_id);
    $pole = EedTools::Skartace_Pole($this->skartace_id);
    $znak = $pole['znak'];
    $doba = $pole['doba'];
    $text = $pole['text'];
    $q = new DB_POSTA;
    $sql = 'select * from posta where id in (' . implode(',', $docIDS). ')';
    $q->query($sql);

    while ($q->Next_Record()) {
      $poleID = EedTools::Skartace_Pole($q->Record['SKARTACE']);
      if ($poleID['doba'] > $doba) {
          $skartace_id = $q->Record['SKARTACE'];
          $pole = $poleID;
          $doba = $poleID['doba'];
      }
      if ($znak == 'S' and ($poleID['znak']=='A' || $poleID['znak']=='V')) {
        $skartace_id = $q->Record['SKARTACE'];
        $znak = $poleID['znak'];
        $pole = $poleID;
      }
      if ($znak == 'V' and $poleID['znak']=='A') {
        $skartace_id = $q->Record['SKARTACE'];
        $znak = $poleID['znak'];
        $pole = $poleID;
      }
    }
    return array('znak'=>$znak, 'doba'=>$doba, 'id'=>$this->skartace_id, 'text'=>$text, 'kod'=>$pole['kod']);
  }

  function SpisZnakTypSpis($typspis_id) {
    $spisZnak = array();
    $casti = EedTools::GetSoucastiTypovehoSpisu($typspis_id);
    $spisZnak['ZNAK'] = 'S';
    $spisZnak['DOBA'] = '0';
    $spisZnak['KOD'] = '';
    foreach($casti as $key=> $soucast) {
      $dily = $this->SeznamDiluvTypovemSpisuSoucasti($typspis_id, $soucast['SOUCAST']);
      foreach($dily as $keyD => $dil){
        $cj = $this->SeznamCJvTypovemSpisu($typspis_id, $soucast['SOUCAST'],  $keyD);
        $pole = array();

        $spisZnak[$key]['ZNAK'] = $casti[$key]['ZNAK'];
        $spisZnak[$key]['DOBA'] = $casti[$key]['DOBA'];
        $spisZnak[$key]['KOD'] = $casti[$key]['KOD'];

        if (count($cj)>0) {
          $pole = $this->SpisZnak($cj[0]);
        }
        $spisZnak[$key][$keyD]['KOD'] = $pole['kod'];
        $spisZnak[$key][$keyD]['ZNAK'] = $pole['znak'];
        $spisZnak[$key][$keyD]['DOBA'] = $pole['doba'];

        //a spocteme nejvyssi znak soucasti
        if ($spisZnak[$key][$keyD]['DOBA'] > $spisZnak[$key]['DOBA']) {
            $spisZnak[$key]['KOD'] = $spisZnak[$key][$keyD]['KOD'];
            $spisZnak[$key]['DOBA'] = $spisZnak[$key][$keyD]['DOBA'];
        }
        if ($spisZnak[$key]['ZNAK'] == 'S' and ($spisZnak[$key][$keyD]['ZNAK']=='A' || $spisZnak[$key][$keyD]['ZNAK']=='V')) {
            $spisZnak[$key]['ZNAK'] = $spisZnak[$key][$keyD]['ZNAK'];
            $spisZnak[$key]['KOD'] = $spisZnak[$key][$keyD]['KOD'];
        }
        if ($spisZnak[$key]['ZNAK'] == 'V' and $spisZnak[$key][$keyD]['ZNAK']=='A') {
            $spisZnak[$key]['ZNAK'] = $spisZnak[$key][$keyD]['ZNAK'];
            $spisZnak[$key]['KOD'] = $spisZnak[$key][$keyD]['KOD'];
        }

      }
      //a spocteme nejvyssi znak typoveho spisu
      if ($spisZnak['DOBA'] < $spisZnak[$key]['DOBA']) {
          $spisZnak['KOD'] = $spisZnak[$key]['KOD'];
          $spisZnak['DOBA'] = $spisZnak[$key]['DOBA'];
      }
      if ($spisZnak['ZNAK'] == 'S' and ($spisZnak[$key]['ZNAK']=='A' || $spisZnak[$key]['ZNAK']=='V')) {
          $spisZnak['ZNAK'] = $spisZnak[$key]['ZNAK'];
          $spisZnak['KOD'] = $spisZnak[$key]['KOD'];
      }
      if ($spisZnak['ZNAK'] == 'V' and $spisZnak[$key]['ZNAK']=='A') {
          $spisZnak['ZNAK'] = $spisZnak[$key]['ZNAK'];
          $spisZnak['KOD'] = $spisZnak[$key]['KOD'];
      }
    }
    return $spisZnak;
  }

  function getObsahTypSpis($typspis_id) {
    $spis = array();
    $casti = EedTools::GetSoucastiTypovehoSpisu($typspis_id);
    foreach($casti as $key=> $soucast) {
      $spis['soucast'][$key] = $soucast;
      $dily = $this->SeznamDiluvTypovemSpisuSoucasti($typspis_id, $soucast['SOUCAST']);
      foreach($dily as $keyD => $dil){
        $spis['soucast'][$key]['dil'][$keyD] = $dil;
      }
    }
    return $spis;
  }

  function getSkartacniRezim($doc_id) {
    $ret = array();
    $q = new DB_POSTA;
    $sql = 'select * from posta_spisovna where dokument_id=' . $doc_id;
    $q->query($sql);
    $q->Next_Record();
    $rezim_id = $q->Record['REZIM_ID'];
    if ($rezim_id>0) {
      $sql = 'select * from posta_cis_skartacni_rezimy where id=' . $rezim_id;
      $q->query($sql);
      $q->Next_Record();
      if ($q->Record['SKAR_ZNAK']<>'') $ret = array('jid' => $q->Record['JID'], 'znak' => $q->Record['SKAR_ZNAK'], 'doba' => $q->Record['SKAR_LHUTA']);
    }
    return $ret;
  }

  function dejDokumentDoTypSpisu($doc_id, $typovy_spis_mainID, $soucast) {

		$cj_info = $this->GetCjInfo($doc_id);
    $typovy_spis = EedTools::VratTypovySpisColumn($typovy_spis_mainID);
		$spis_id = $cj_info['SPIS_ID'];
		$dil = EedTools::VratOtevrenyDil($typovy_spis_mainID, $soucast);

		//testneme, jeslti je dil prazdn
		$dil_id = EedTools::JeDilPrazdny($typovy_spis_mainID, $soucast, $dil);
		If ($dil_id == 0) {
            $spis_id = $doc_id;
            $datum_otevreni = Date('Y-m-d');
			$dalsi_spis_id = 0;
		}
		else {
			$spis_id = $dil_id;
			$datum_otevreni = Date('Y-m-d');
			$dalsi_spis_id = $doc_id;
		}
		$cj_obj = new EedCj($spis_id);
		$cj_info = $cj_obj->GetCjInfo($spis_id);
		$spis_id = $cj_info['SPIS_ID'];
       $ps = $cj_info['CELE_CISLO'];
		$ns = '';
        if ($dalsi_spis_id>0) {
        	$cj_obj = new EedCj($dalsi_spis_id);
        	$cj_info = $cj_obj->GetCjInfo($dalsi_spis_id);
        	$ns = $cj_info['CELE_CISLO'];

        }
		$sql = "INSERT INTO CIS_POSTA_SPISY (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID,SOUCAST,DIL,TYPOVY_SPIS,TYPOVY_SPIS_ID,DATUM_OTEVRENI) VALUES ".
				"('$ps', '$ns',  $spis_id,$dalsi_spis_id, '".Date('Y-m-d')."','".Date('H:i:s')."',".$cj_obj->id_user.",".$cj_obj->id_user.",$soucast,$dil,$typovy_spis,$typovy_spis_mainID,'$datum_otevreni')";
    $q = new DB_POSTA;
		$q->query($sql);
		$text = 'dokument (<b>'.$doc_id.'</b>) '.$ns.' byl vložen do dílu typového spisu <b>' . $ps . '</b>';
		EedTransakce::ZapisLog($doc_id, $text, 'DOC', $id_user);
		EedTransakce::ZapisLog($doc_id, $text, 'SPIS', $id_user);

  }

}
