<?php
//Login czechpointu do serveru 
Function login($software_id,$username,$userpasswd) {
  If (!is_array($GLOBALS["KONEKTOR"][$software_id])) 
  {
    $text='(LOGIN) - není zadáno existující software_id';
    WriteLog($software_id,$text);
    $value = array('RESULT'=>'ERROR','DESCRIPTION'=>TxtEncoding4Soap($text));
    return VratVysledek($value);
  }
  If ($GLOBALS["KONEKTOR"][$software_id]["VALID_USERS"][$username]==$userpasswd)
  {
    //login probehl
    $q=new DB_POSTA;
    $session=md5(Date('Ymdhis').$username.$software_id);
    $timestamp=time();
    $sql="insert into posta_interface_login (cas,sw,session_id) values ($timestamp,'$software_id','$session')";
    //echo $sql;
    $q->query($sql);
    $text='(LOGIN) - Přihlášen uživatel sw '.$software_id.' - session nr. '.$session;
    WriteLog($software_id,$text,$session);
    $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
    $vysledek = array(
      'return'=>new soapval('Result', 'tns:Result', $value),
      'session_id'=>new soapval('session_id', 'xsd:string', $session)
    );
    return VratVysledek($vysledek);
  }
  else
  {
    $text='(LOGIN) - zadané uživ. jméno a heslo není správné';
    WriteLog($software_id,$text,$session_id);
    $value = array('RESULT'=>'ERROR','DESCRIPTION'=>TxtEncoding4Soap($text));
    return VratVysledek($value);

  }
}
?>
