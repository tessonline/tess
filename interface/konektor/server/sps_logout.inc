<?php
//Logout konektoru ze serveru 
Function logout($session_id)
{
  If (!($software_id=JeNalogovan($session_id))) 
  {
    $text='(LOGOUT) - není zadáno správné session_id';
    WriteLog($software_id,$text);
    $value = array('RESULT'=>'ERROR','DESCRIPTION'=>TxtEncoding4Soap($text));
    return VratVysledek($value);
  }

  $q=new DB_POSTA;
  //login probehl
  $sql="delete from posta_interface_login where session_id like '".$session_id."'";
//  echo $sql;
  $q->query($sql);

  $text='(LOGOUT) - uživatel odhlášen';
  WriteLog($software_id,$text,$session_id);
  $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
  return VratVysledek($value);
}
?>
