<?php


class EedLog {

  
   /** zapise udaj do logu
   */  
  function writeLog($text, $params = array()) {
    static $USER_INFO, $db;
    $sql = "insert into posta_log (agenda_id,text,chyba,last_date,last_time,last_user_id,owner_id) VALUES (%s,'%s',%s,'%s','%s',%s,%s)";
    if (!$USER_INFO) {
      $USER_INFO =  $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    }
    if (!$db) {
      $db = new DB_POSTA;
    }
    
    $id = $params['ID'] ? $params['ID'] : $GLOBALS['ID']; 
    $id = (int) $id;
    $chyba = $params['chyba'] ? 1 : 0;
    //if ($id<1) return false;
    $sql = sprintf($sql,
                     $id,
                     $text,
                     $chyba,
                     Date('Y-m-d'),
                     Date('H:i:s'),
                     $USER_INFO['ID'],
                     $USER_INFO['ID']
                     );
    $db->query($sql);
  }
}
