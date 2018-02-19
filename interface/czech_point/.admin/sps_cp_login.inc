<?php
//Login czechpointu do serveru 
Function Login($Name, $Password = '') {
  $username= $Name;
  $userpasswd = $Password;
  $software_id = 'CP';
  If ($GLOBALS["CONFIG_POSTA_CP"]["VALID_USERS"][$username]["password"]==$userpasswd) {
    $q=new DB_POSTA;
    //login probehl
    $session=$username."*".md5(Date('Ymdhis'));
    $timestamp=time();
    $sql="insert into posta_interface_login (cas,sw,session_id) values ($timestamp,'$software_id','$session')";
    $q->query($sql);
//    VymazSessions();         
    $text='(LOGIN) - Přihlášen uživatel sw '.$software_id.' - session nr. '.$session;
    WriteLog($software_id,$text,$session);
 
    $return='<ns1:LoginResponse xmlns:ns1="http://www.software602.cz/webservices/602xml">
        <ns1:LoginResult>1</ns1:LoginResult> 
        <ns1:LogToken>'.$session.'</ns1:LogToken> 
        <ns1:Exception></ns1:Exception> 
      </ns1:LoginResponse>
    ';
/*
    $return='<LoginResponse>
        <LoginResult>1</LoginResult> 
        <LogToken>'.$session.'</LogToken> 
      </LoginResponse>
    ';
*/
    return $return;
    
  }
  else
  {
    $text='(LOGIN) - zadané uživ. jméno a heslo není správné';
    WriteLog($software_id,$text,$session_id,1); 
    
    $return='
     <ns1:LoginResponse ret="Exception" code="-2" xmlns:ns1="http://www.software602.cz/webservices/602xml">
        <ns1:LoginResult>-2</ns1:LoginResult> 
        <ns1:Exception>InvalidUserName</ns1:Exception> 
     </ns1:LoginResponse>
  ';
    return $return;
  }
}
?>
