<?php

require_once ('db.inc');

class EedVersion extends EED_db_object {

  var $verze;
  var $datum;
  var $historie = array();

  /**
  * Constructor
  * @author onma
  *
  * return cislo verze
  */
  function EedVersion(){
    $filepath = GetAgendaPath('POSTA',false,false)."/.admin/changelog/EED_changelog.csv";    
    $file = fopen($filepath, "r");
    if (!$file) return false;
    $found = false;
    while (!feof($file)&&!$found) {
      $line_of_text = fgets($file);
      $items = explode('|', $line_of_text);
      if (strlen($items[0])>0) {
        $found = true;
        $this->verze = str_replace('~', '', $items[0]);
        $this->datum = $items[1];
      }
    }
    fclose($file);
    if (!$found) return false;
    return true;
  }

  /**
  * WriteGitLog
  * @author onma
  * zapise verzi z Gitu
  *
  * return cislo verze
  */
  function WriteGitLog($data) {
    $sql = "select id from posta_version where git_hash like '" . $data['HASH'] . "' ";
    $this->_sql_query($sql);
    if ($this->db->Num_Rows() == 0) {
      //neni, zapiseme
      $sql = "insert into posta_version (git_hash,git_autor,datum,popis,last_date,last_time,last_user_id,owner_id) VALUES ('%s','%s','%s','%s','%s','%s',%s,%s)";
      if (!$USER_INFO) {
        $USER_INFO =  $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
      }
      $data['MESSAGE'] = str_replace('  ','', $data['MESSAGE']);
      $data['MESSAGE'] = str_replace("'", "", $data['MESSAGE']);
      $data['MESSAGE'] = substr($data['MESSAGE'],0,99);

      $data['ENG_DATE'] = $data['ENG_DATE'] ? $data['ENG_DATE'] : Date('Y-m-d H:i:s');
      $sql = sprintf($sql,
                       $data['HASH'],
                       $data['AUTHOR'],
                       $data['ENG_DATE'],
                       $data['MESSAGE'],
                       Date('Y-m-d'),
                       Date('H:i:s'),
                       $USER_INFO['ID'],
                       $USER_INFO['ID']
                     );
//echo $sql.'<br/>';
      $this->_sql_query($sql);

    }
  }

}