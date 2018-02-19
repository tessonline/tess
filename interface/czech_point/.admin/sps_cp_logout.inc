<?php
//Logout czechpointu ze serveru 
Function logout($session_id)
{
  $software_id='CP';
  If (!($software_id=JeNalogovan($session_id))) 
  {
    $text='(LOGOUT) - není zadáno správně session_id';
    WriteLog('CP',$text,'',1);
    $return=
      '<ns1:LogoutResponse ret="Exception" code="-3" xmlns:ns1="http://www.software602.cz/webservices/602xml">
        <ns1:Exception>Nejste prihlaseni, nejde se odlogovat</ns1:Exception> 
     </ns1:LogoutResponse>
  ';
//       <ns1:GetReferenceNumberResult>-3</ns1:GetReferenceNumberResult> 
    return $return;
  }

  $q=new DB_POSTA;
  //login probehl
  $session=md5(Date('Ymdhis').$username);
  $timestamp=time();
  $sql="delete from posta_interface_login where session_id like '".$session_id."'";
  $q->query($sql);
  $return='
      <ns1:LogoutResponse xmlns:ns1="http://www.software602.cz/webservices/602xml">
        <ns1:LogoutResult>1</LogoutResult>
      </ns1:LogoutResponse>
  ';
  $text='(LOGOUT) - uživatel odhlášen';
  WriteLog($software_id,$text,$session_id);

return $return;
}
?>
