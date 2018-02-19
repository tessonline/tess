<?php
$dbname='./log/'.Date(dmY).'.txt';

Function ZapisText($file,$text)
{
  
  If (file_exists($file)) $params='a'; else $params='w';
  $fp=@FOpen($file,$params);
	$a=Date('H:i:s')." - ".$text;
  @FWrite($fp,$a);
  @FClose($fp);
  
}
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/security_name.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2(".admin/oth_funkce_2D.inc"));
require_once(FileUp2(".admin/config.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/soap_funkce.inc"));
include_once(FileUp2(".admin/status.inc"));

Header("Pragma: no-cache");
Header("Cache-Control: no-cache");

Header("Content-Type: text/xml");

$session_id=Date('dmYHms');
$software_id='VITA';

    echo "<?xml version=\"1.0\" encoding=\"iso-8859-2\" \n?>";
      echo "  <pisemnost>\n";

//kontrola na dosle parametry
/*
If (!$GLOBALS["a_prac"] && !$GLOBALS["a_vec"] && !$GLOBALS["a_TypAdr"] && !$GLOBALS["a_prijobyv"] &&
!$GLOBALS["a_jmobyv"] && !$GLOBALS["a_cobce"] && !$GLOBALS["a_obec"] && !$GLOBALS["a_psc"]
 && !$GLOBALS["a_Typodesl"] && !$GLOBALS["a_ze_dne"])

//nebyly predany veskere parametry
{

  echo "  <pisemnost>\n";
  echo "    <b_error>Nebyly předány potřebné hodnoty</b_error>\n";
  echo "  </pisemnost>\n";


  $text='(ZALOZ_PISEMNOST) - Nebyly předány potřebné hodnoty)';
  WriteLog($software_id,$text,$session_id);


}
else
{

*/
  //jdeme tam vlozit hodnoty
  
$rok=date('Y');

$text='(ZALOZ_PISEMNOST) - query: '.str_replace('&',', ',urldecode($_SERVER['QUERY_STRING'])).'';
WriteLog($software_id,$text,$session_id);

If ($GLOBALS["a_cp"]) list($EV_CISLO,$ROK)=explode("/",$GLOBALS["a_cp"]);

If ($GLOBALS["a_cp"] && !strpos('/', $GLOBALS["a_cp"])) {
  //zjistime z caroveho kodu
  $GLOBALS['a_id'] = PrevedCPnaID($GLOBALS["a_cp"]);
}

If ($GLOBALS["a_cp"] || $GLOBALS["a_id"]) {

  If (!$GLOBALS["a_id"]) {
    // jdeme zjistit id zaznamu z cp
    $sql='select id from posta where EV_CISLO='.$EV_CISLO.' and ROK='.$ROK.'';
    $a=new DB_POSTA;
    $a->query($sql);
    $a->Next_Record(); $GLOBALS["a_id"]=$a->Record["ID"];
  }

  $id_user=$GLOBALS[a_prac]?$GLOBALS[a_prac]:$GLOBALS["CONFIG"]["VITA_ID"];
  $LAST_USER_ID=$id_user;
  $OWNER_ID=$id_user;
  $LAST_TIME=Date('H:m');
  $LAST_DATE=Date('Y-m-d');

  $add_info="last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=".$LAST_USER_ID;

  // aktualizace zaznamu...
  $sql=array();
  If ($GLOBALS[a_datdoruceni]) $sql[]="update posta set datum_doruceni='$GLOBALS[a_datdoruceni]',$add_info where id=".$GLOBALS["a_id"];
  If ($GLOBALS[a_datpm]) $sql[]="update posta set datum_pm='$GLOBALS[a_datpm]',$add_info where id=".$GLOBALS["a_id"];

//stav doruceni - neni zatim implementovano
/*
1 - 'doručeno'
2 - 'odmítnutá zásilka'
3 - 'neposkytnuta součinnost'
4 - 'adresát se odstěhoval bez udání adresy'
5 - 'adresát neznámý'
6 - 'adresa je nedostatečná'
7 - 'jiný důvod'
8 - 'zásilka nebyla vyzvednuta ve lhůtě'
*/
//  If ($GLOBALS[a_stavdoruceni]) $sql[]="update posta set datum_doruceni=$GLOBALS[a_datdoruceni] where id=".$GLOBALS["a_id"];
//    print_r($sql);


  $a=new DB_POSTA;
  while(list($key,$val)=each($sql))
  {
    $chyba=false;
    If (!$a->query($val))
      $chyba=true;
   
     If ($chyba)
     {
        echo "    <b_error>SQL error:".$val."</b_error>\n";
        $text='(ZALOZ_PISEMNOST) - query: '.$val;
        WriteLog($software_id,$text,$session_id,1);
     }

   }
   If (!$chyba)
   { 
      echo "    <b_error>0</b_error>\n";
      echo "    <b_id>".$GLOBALS[a_id]."</b_id>\n";
      $text='(DORUCENKY) - dorucenka pro ID: '.$GLOBALS[a_id];
      WriteLog($software_id,$text,$session_id);
      NastavStatus($GLOBALS[a_id]);
   }

}
    
echo "  </pisemnost>\n";
?>
