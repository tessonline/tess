<?php
$dbname='./log/'.Date(dmY).'.txt';

Function ZapisText($file,$text)
{
  
  If (file_exists($file)) $params='a'; else $params='w';
  $fp=FOpen($file,$params);
	$a=Date('H:i:s')." - ".$text;
  FWrite($fp,$a);
  FClose($fp);
  
}
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/security_name.inc"));
require_once(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/status.inc"));

Header("Pragma: no-cache");
Header("Cache-Control: no-cache");

Header("Content-Type: text/xml");

echo "<?xml version=\"1.0\" encoding=\"iso-8859-2\"?> \n";

//kontrola na dosle parametry
If (!$GLOBALS["a_prac"] || !$GLOBALS["a_duvod"] || !$GLOBALS["a_id"])
{
  //nebyly predany veskere parametry
  echo "  <pisemnost>\n";
  echo "    <b_error>Nebyly předány potřebné hodnoty</b_error>\n";
  echo "  </pisemnost>\n";
}
else
{
  $sql=array();
  echo "  <pisemnost>\n";
  $id_user=$GLOBALS[a_prac]?$GLOBALS[a_prac]:$GLOBALS[CONFIG][VITA_ID];
  $LAST_TIME=Date('H:m:i');
  $LAST_DATE=Date('Y-m-d');
  $LAST_USER_ID=$GLOBALS[CONFIG][VITA_ID];
  $dnes=Date('d.m.Y');
  $jmeno=UkazUsera($id_user);
  $text='Dne <b>'.$dnes.'</b> v <b>'.$LAST_TIME.'</b> uživatel <b>'.$jmeno.'</b> stornoval tento záznam. Důvod: <b>'.$GLOBALS[a_duvod].'</b>';
  $sql[]="UPDATE posta SET STORNOVANO='$text',status=-3,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$GLOBALS[a_id];
  //echo $sql;
  //vymazeme i odpovedi
  If ($GLOBALS[a_full]==1)
    $sql[]="UPDATE posta SET STORNOVANO='$text',status=-3,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id_puvodni=".$GLOBALS[a_id];
    
  $a=new DB_POSTA;
  while(list($key,$val)=each($sql))
  {
    $chyba=false;
    If (!$a->query($val)) $chyba=true;
    If ($chyba) echo "    <b_error>SQL error:".$val."</b_error>\n";
  }
  If (!$chyba)
  { 
    echo "    <b_error>0</b_error>\n";
    NastavStatus($GLOBALS[a_id]);
  }
  
  echo "  </pisemnost>\n";
}

?>
