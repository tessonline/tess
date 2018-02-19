<?php
require_once ('db.inc');

class EedTransakce extends EED_db_object {

  var $nova = array();
  var $historie = array();
  var $dbT;
  /**
  * Constructor
  * @author onma  
  */  
  function EedTransakce(){
    parent::Eed_db_object();
    $this->dbT = new DB_POSTA;
  }
 

  function ZapisZHistorie($doc_id) {
    $zmena = array();
    $formy = array();
    $rozdily = $this->_CompareHistory($doc_id);
    $GLOBALS['EDIT_ID'] = $doc_id;
    $form_params["formtype"] = array($f_edit);
    include_once $GLOBALS["TMAPY_LIB"]."/oohformsex.inc";
    include_once(Fileup2(".admin/el/of_text_.inc"));
    include_once(Fileup2(".admin/el/of_date_.inc"));
    include_once(Fileup2(".admin/el/of_select_.inc"));
    include(FileUp2('.admin/form_schema_vnejsi.inc'));
    foreach($FORM_CONFIG['schema'] as $schema) {
       $label_full = $schema['label'];
       if (is_array($schema['elements'])) {
         foreach($schema['elements'] as $elem) {
           if ($elem['label']) $formy[$elem['name']] = array('label'=>$elem['label'], 'type'=>$elem['type']);
           else $formy[$elem['name']] = array('label'=>$label_full, 'type'=>$elem['type']);
         }
       }
    }

    if (!$rozdily) $this->ZapisLog($doc_id, 'Vytvoření nového dokumentu');
    else {
      $text = 'Provedena změna metadat: <br/>';

      include_once $GLOBALS["TMAPY_LIB"]."/oohformsex.inc";
      include_once(Fileup2(".admin/el/of_text_.inc"));
      include_once(Fileup2(".admin/el/of_date_.inc"));
      include_once(Fileup2(".admin/el/of_select_.inc"));
      foreach($rozdily as $key => $val) {
        if ($formy[$key]) {

          $GLOBALS[$val['field']] = $formy[$key];
          $class = 'of_'.$formy[$key]['type'];
          $cls = @new $class;
          $cls->value = $this->historie[$key];
          $GLOBALS["HISTORY_TABLE_IDENT_COLUM"]='NEW';
          if (Method_Exists($cls, "self_get_frozen"))
            $puvodni = $cls->self_get_frozen($val["new"], false, $count);
          else
            $puvodni = $this->historie[$key];

         $puvodni = preg_replace("#<b>(.*)</b>#i", "\\1", $puvodni);
         if (preg_match("/<b>/i", $puvodni))
           $puvodni = preg_replace("#<b>(.*)</b>#i", "\\1", $puvodni);
         if ($cls->value != '' && preg_match("/select/i", $formy[$key]['type']))
           $puvodni .= " (".$cls->value.")";
         if ($cls->value > 0 && preg_match("/checkbox/i", $formy[$key]['type']))
           $puvodni = "ANO";
         if ($cls->value != '' && preg_match("/date_db/i", $formy[$key]['type']))
           $puvodni = " ".$this->dbT->dbdate2str($cls->value);

          $cls->value = $this->nova[$key];
          $GLOBALS["HISTORY_TABLE_IDENT_COLUM"]='NEW';
          if (Method_Exists($cls, "self_get_frozen"))
            $nova = $cls->self_get_frozen($val["new"], false, $count);
          else
            $nova = $this->nova[$key];

         $nova = preg_replace("#<b>(.*)</b>#i", "\\1", $nova);
         if (preg_match("/<b>/i", $nova))
           $nova = preg_replace("#<b>(.*)</b>#i", "\\1", $nova);
         if ($cls->value != '' && preg_match("/select/i", $formy[$key]['type']))
           $nova .= " (".$cls->value.")";
         if ($cls->value > 0 && preg_match("/checkbox/i", $formy[$key]['type']))
           $nova = "ANO";
         if ($cls->value != '' && preg_match("/date_db/i", $formy[$key]['type']))
           $nova = " ".$this->dbT->dbdate2str($cls->value);

          unset($cls);
          $column = $formy[$key]['label'];
          if ($column<>'') {
            if (!strpos($column,':')) $column .= ':';
            $puvodni = str_replace('&nbsp;&nbsp;','', $puvodni);
            $nova = str_replace('&nbsp;&nbsp;','', $nova);
            $zmena[] = strip_tags('<b>'.$column.'</b> původně:<b>'.$puvodni.'</b>,nově:<b>'.$nova.'</b>','<b>');
          }

        }
      }
      if (count($zmena)>0) {
        $text .= implode('<br/>',$zmena);
        $this->ZapisLog($doc_id, $text);
      }
    }
    return $rozdily;
  }

  function ZapisZHistorieTable($doc_id, $dokument_id = 0, $table, $caption, $form_schema = '.admin/form_schema.inc') {
    $zmena = array();
    $formy = array();
    $rozdily = $this->_CompareHistoryTable($doc_id, $table);
    $GLOBALS['EDIT_ID'] = $doc_id;
    $form_params["formtype"] = array($f_edit);
    include(FileUp2($form_schema));
    foreach($FORM_CONFIG['schema'] as $schema) {
       $label_full = $schema['label'];
       if (is_array($schema['elements'])) {
         foreach($schema['elements'] as $elem) {
           if ($elem['label']) $formy[$elem['name']] = array('label'=>$elem['label'], 'type'=>$elem['type']);
           else $formy[$elem['name']] = array('label'=>$label_full, 'type'=>$elem['type']);
         }
       }
    }

    if (!$rozdily) {
      $this->ZapisLog($doc_id, '<b>Vytvoření nového záznamu <b>'.$caption.'</b>');
    }
    else {
      $text = 'Provedena změna metadat<b>'.$caption.'</b>: <br/>';

      include_once $GLOBALS["TMAPY_LIB"]."/oohformsex.inc";
      include_once(Fileup2(".admin/el/of_text_.inc"));
      include_once(Fileup2(".admin/el/of_date_.inc"));
      include_once(Fileup2(".admin/el/of_select_.inc"));
      foreach($rozdily as $key => $val) {
        if ($formy[$key]) {

          $GLOBALS[$val['field']] = $formy[$key];
          $class = 'of_'.$formy[$key]['type'];
          $cls = @new $class;
          $cls->value = $this->historie[$key];
          $GLOBALS["HISTORY_TABLE_IDENT_COLUM"]='NEW';
          if (Method_Exists($cls, "self_get_frozen"))
            $puvodni = $cls->self_get_frozen($val["new"], false, $count);
          else
            $puvodni = $this->historie[$key];

         $puvodni = preg_replace("#<b>(.*)</b>#i", "\\1", $puvodni);
         if (preg_match("/<b>/i", $puvodni))
           $puvodni = preg_replace("#<b>(.*)</b>#i", "\\1", $puvodni);
         if ($cls->value != '' && preg_match("/select/i", $formy[$key]['type']))
           $puvodni .= " (".$cls->value.")";
         if ($cls->value > 0 && preg_match("/checkbox/i", $formy[$key]['type']))
           $puvodni = "ANO";
         if ($cls->value != '' && preg_match("/date_db/i", $formy[$key]['type']))
           $puvodni = " ".$this->dbT->dbdate2str($cls->value);

          $cls->value = $this->nova[$key];
          $GLOBALS["HISTORY_TABLE_IDENT_COLUM"]='NEW';
          if (Method_Exists($cls, "self_get_frozen"))
            $nova = $cls->self_get_frozen($val["new"], false, $count);
          else
            $nova = $this->nova[$key];

         $nova = preg_replace("#<b>(.*)</b>#i", "\\1", $nova);
         if (preg_match("/<b>/i", $nova))
           $nova = preg_replace("#<b>(.*)</b>#i", "\\1", $nova);
         if ($cls->value != '' && preg_match("/select/i", $formy[$key]['type']))
           $nova .= " (".$cls->value.")";
         if ($cls->value > 0 && preg_match("/checkbox/i", $formy[$key]['type']))
           $nova = "ANO";
         if ($cls->value != '' && preg_match("/date_db/i", $formy[$key]['type']))
           $nova = " ".$this->dbT->dbdate2str($cls->value);

          unset($cls);
          $column = $formy[$key]['label'];
          if ($column<>'') {
            if (!strpos($column,':')) $column .= ':';
            $zmena[] = strip_tags('<b>'.$column.'</b> původně:<b>'.$puvodni.'</b>,nově:<b>'.$nova.'</b>','<b>');
          }

        }
      }
      if (count($zmena)>0) {
        $text .= implode('<br/>',$zmena);
        $this->ZapisLog($dokument_id, $text);
      }
    }
    return $rozdily;
  }

  function ZapisLog($doc_id = 0, $text, $typ = 'DOC', $user_id = 0) {
    if (!$dbT) $dbT = new DB_POSTA;
    if ($user_id == 0) {
      $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    } else {
      $user = LoadClass('EedUser', $user_id);
      //z ID pracovnika vrati odbor a oddeleni
      $USER_INFO['FNAME'] = $user->jmeno;
      $USER_INFO['LNAME'] = $user->prijmeni;
      $USER_INFO['ID'] = $user_id;
    }
    $user_id = $USER_INFO['ID'];
    $text = str_replace("'", "", $text);
    $jmeno = $USER_INFO['FNAME'] . ' ' . $USER_INFO['LNAME'];
    $so = $USER_INFO['PRACOVISTE'] ? $USER_INFO['PRACOVISTE'] : 0;
    $sql = 'insert into posta_transakce (DOC_ID, JMENO, TEXT, TYP,LAST_USER_ID,ID_SUPERODBOR) VALUES';
    $sql .= "($doc_id,'$jmeno','$text','$typ',$user_id,$so)";
    $dbT->query($sql);
    $operace = explode(',', strtolower($GLOBALS['CONFIG_POSTA']['SYS']['logovane_operace']));
    if (in_array(strtolower($typ), $operace)) {
        chdir(getAgendaPath('POSTA_PLUGINS', 0, 0) . '/epodatelna');
    	  include_once(FileUp2('plugins/epodatelna/.admin/error.inc'));
        $text = strip_tags($text);
        OdesliEmail($GLOBALS['CONFIG_POSTA']['SYS']['email_spravce'],$text,Date('Y-m-d'),'EED - Notifikace transakcniho protokolu',$soubory, array('EMAIL' => ''));
    }

  }

  function _CompareHistoryTable($doc_id, $table) {
    $sql = "select * from $table where id=" . $doc_id;
    $this->dbT->query($sql);
    $this->dbT->Next_Record();
    $data = $this->dbT->Record;
    if ($table == 'posta_konfigurace') $data['HODNOTA'] = $data['HODNOTA'] . ' (' . $data['PARAMETR'] . ')';
    $this->nova = $data;
    $sql = "select * from ".$table."_h where id=" . $doc_id . " order by id_h desc";
    $this->dbT->query($sql);

    if ($this->dbT->Num_Rows() == 0) {
      return false;
    }
    else {
      $this->dbT->Next_Record();
      $puv = $this->dbT->Record;
      if ($table == 'posta_konfigurace') $puv['HODNOTA'] = $puv['HODNOTA'] . ' (' . $puv['PARAMETR'] . ')';
      $this->historie = $puv;
      $rozdily = array_diff_assoc($data, $puv);
    }
    return $rozdily;
  }

  function _CompareHistory($doc_id) {
    return $this->_CompareHistoryTable($doc_id, 'posta');
  }

  function getRecordsHistory($date) {
    $data = array();
    $a = 0;
    $sql = "select * from posta_transakce where last_time>'" . $date ." 00:00' and last_time<'" . $date ." 23:59:59' order by id asc ";
    $this->dbT->query($sql);
    while ($this->dbT->Next_Record()) {
      $data[$a]['ID'] = $this->dbT->Record['ID'];
      $data[$a]['LAST_TIME'] = $this->dbT->Record['LAST_TIME'];
      $data[$a]['DOC_ID'] = $this->dbT->Record['DOC_ID'];
      $data[$a]['JMENO'] = $this->dbT->Record['JMENO'];
      $data[$a]['TEXT'] = $this->dbT->Record['TEXT'];
      $a++;
    }
    return $data;
  }



}

