<?php
require(FileUpUrl('.admin/config.inc'));

/**
* trida EED_doc, pro praci s uzivateli
*@author onma  
*/
class Eed_db_object {
  var $show_debug_work = false; //ukazovat debug?
  var $show_debug_sql = false; //ukazovat debug?
  var $show_debug_error = false; //ukazovat chyby?
  var $error = ''; //pripadna error zprava
  
  /* staticka promenna pro singleton */
  private static $DbInstance;
  /**
  * Constructor
  * @author onma  
  * @param int $id - id dokumentu   
  */  
  function Eed_db_object(){
    
    //$this->db = $this->getInstanceDb();
    $this->db = new DB_POSTA;
    
  }

  public static function getInstanceDb() {
    if (self::$DbInstance === NULL) {
      self::$DbInstance = new DB_POSTA;
    }
    return self::$DbInstance;
  }


  function _sql_query($sql) {
    $this->ShowDebugSQL($sql);
    return $this->db->query($sql);
  }
  
  
  function ShowDebug($text)
  {
    if ($this->show_debug_work)
    {
      if (is_array($text))
      {
        echo "<font color=green><b>DEBUG:</b></font> ".Date('d.m.Y H:i:s.u')." - POLE HODNOT: ";
        print_r($text);
        echo "<br/>";
      }
      else    
        echo "<font color=green><b>DEBUG:</b></font> ".Date('d.m.Y H:i:s.u')." - ".$text."<br/>";    
    } 
  }
  
  function ShowDebugSQL($text)
  {
    if ($this->show_debug_sql) 
      echo "<font color=blue><b>DEBUG: (".get_class($this).")</b></font> ".Date('d.m.Y H:i:s.u')." - ".$text." <br/>";
  }
  
  function ShowError($text)
  {
    if ($this->show_debug_error) 
      echo "<font color=red><b>CHYBA:</b></font> ".Date('d.m.Y H:i:s')." - ".$text."<br/>";    
  }
  
  function JeZaznamVDB($sql)
  {
    $this->_sql_query($sql);
    if ($this->db->Num_Rows()>0) return true;
    else return false;
  }

  function getMainUnit($unit_id = 0)
  {
    while ($unit_id>0) {
      $last_odbor = $unit_id;
       if (!$id = $this->GetUnitParent($unit_id)) break;
      $unit_id = $id;
    }
    return $last_odbor;
  }

  function GetUnitName($unit_id = 0)
  {
    if (!$unit_id) return false;
    if (isset($GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$unit_id]['NAME'])) return $GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$unit_id]['NAME'];

    $sql = "select * from security_group where id=".$unit_id;
    $this->db_temp = new DB_POSTA;
    $this->db_temp->query($sql);

    If ($this->db_temp->Num_Rows()>0) {
      $this->db_temp->Next_Record();
      $GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$unit_id] = $this->db_temp->Record;
      return $this->db_temp->Record["NAME"];
    }
    else return '';
  }

  function GetUnitParent($unit_id = 0)
  {
    if (!$unit_id) return false;
    if (isset($GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$unit_id]['PARENT_GROUP_ID'])) return $GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$unit_id]['PARENT_GROUP_ID'];
    $sql = "select * from security_group where id=".$unit_id;
    $this->_sql_query($sql);
    If ($this->db->Num_Rows()>0) {
      $this->db->Next_Record();
      $GLOBALS['POSTA_OPT']['SECURITY_GROUP'][$unit_id] = $this->db->Record;
      return $this->db_temp->Record["PARENT_GROUP_ID"];
    }
    else return false;
  }


}
