<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/config.inc"));
include(FileUp2(".admin/security_obj.inc"));
include_once(FileUp2('.admin/oth_funkce.inc'));
include_once(FileUp2(".admin/security_name.inc"));
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
require_once(GetAgendaPath("UPLOAD-ELO",false,false)."/.admin/properties.inc"); 
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
include_once(FileUp2(".admin/upload_.inc"));
set_time_limit(0);

echo '<h1>Vytvoření meta záznamů v ELO</h1>';
require(FileUp2("html_header_full.inc"));

 //zkusime si vytvorit SOAP klienta a nakonektit do ELO


$elo_dms_ip_port = $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['STORAGE']['Elo_Service']['wsdl'];
$elo_dms_login = $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['STORAGE']['Elo_Service']['ELO_DMS_LOGIN'];
$elo_dms_passwd = $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['STORAGE']['Elo_Service']['ELO_DMS_PASSWD'];
$elo_dms_archiv = $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['STORAGE']['Elo_Service']['ELO_DMS_ARCHIV'];

$client = new tw_soapclient($elo_dms_ip_port, true);
  if ($GLOBALS["PROPERTIES"]["ELO_DMS_ENDPOINT"])
    $client->setEndpoint($GLOBALS["PROPERTIES"]["ELO_DMS_ENDPOINT"]);
$err = $client->getError();
if ($err) {
    require(FileUp2("html_footer.inc"));
    Die('<font color="red"><b>CHYBA: ELO systém není dostupný</b></font>');
}
//Connect do ELO
$result = $client->call('Login', array(
  new soapval('','Login',array(
    'lstrUSRName'=>$elo_dms_login,
    'lstrUSRPsw'=>$elo_dms_passwd,
    'lstrArchivName'=>$elo_dms_archiv,
  ),false,'http://tempuri.org/ELO/ELOHTTP')
));
//print_r($result);
If (strlen($result['LoginResult'])>3) echo "Connect OK<br/>"; else 
{ 
  echo "zkusime pripojit znova<br/>";
  $result = $client->call('Login', array(
    new soapval('','Login',array(
    'lstrUSRName'=>$elo_dms_login,
    'lstrUSRPsw'=>$elo_dms_passwd,
    'lstrArchivName'=>$elo_dms_archiv,
    ),false,'http://tempuri.org/ELO/ELOHTTP')
  ));
//  print_r($result2);
  If (($result['LoginResult'])>3) echo "Connect 2 - OK<br/>"; else  Die("Nepripojeno ani podruhe<br/>");
} 
$session=$result['LoginResult'];
//Jsme nakonekteny...

//pripravime SQL
If (!$GLOBALS["DATUM_OD"]) $GLOBALS["DATUM_OD"]=Date('d.m.Y');
If (!$GLOBALS["DATUM_DO"]) $GLOBALS["DATUM_DO"]=Date('d.m.Y');

If ($GLOBALS["CONFIG"]["DB"]=='psql')
{
  $where.=" (DATUM_PODATELNA_PRIJETI) >= ('".$GLOBALS["DATUM_OD"]."',)";
  $where.=" AND (DATUM_PODATELNA_PRIJETI) <= ('".$GLOBALS["DATUM_DO"]."',)";
}
If ($GLOBALS["CONFIG"]["DB"]=='mssql')
{
  $where.=" CONVERT(datetime,datum_podatelna_prijeti,104)>CONVERT(datetime,'".$GLOBALS["DATUM_OD"]." 00:00',104)";
  $where.=" AND CONVERT(datetime,datum_podatelna_prijeti,104)<CONVERT(datetime,'".$GLOBALS["DATUM_DO"]." 23:59',104)";
}
$where.=" AND stornovano is null";
If ($GLOBALS[EV_CISLO_OD]) $where.=" AND ev_cislo >= ".$GLOBALS[EV_CISLO_OD]."";
If ($GLOBALS[EV_CISLO_DO]) $where.=" AND ev_cislo <= ".$GLOBALS[EV_CISLO_DO]."";
If ($GLOBALS[CISLO_JEDNACI1_OD]) $where.=" AND cislo_jednaci1 >= ".$GLOBALS[CISLO_JEDNACI1_OD]."";
If ($GLOBALS[CISLO_JEDNACI1_DO]) $where.=" AND cislo_jednaci1 <= ".$GLOBALS[CISLO_JEDNACI1_DO]."";
//If ($GLOBALS[PODATELNA_ID]) $where.=" AND podatelna_id IN (".$GLOBALS[PODATELNA_ID].")";
If ($GLOBALS[ODBOR]) $where.=" AND odbor IN (".$GLOBALS["ODBOR"].")"; 
$where.=" AND odes_typ<>'X' and ODESLANA_POSTA='f' and zpusob_podani='1'";
If ($GLOBALS["ID"]) $where =" id in (".$GLOBALS["ID"].")";
$sql="select id,ev_cislo,rok from posta where".$where." order by ev_cislo DESC";
$q=new DB_POSTA;
$u=new DB_POSTA;
//Die($sql);
$q->query($sql);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y H:m');

echo "<font size=2 color=red>";
while ($q->Next_Record())
{
  $podaci_cislo=$q->Record["ID"];
  $id_pisemnost=$q->Record["ID"];
  $sql="select id from files where record_id=".$id_pisemnost." and agenda_ident like 'POSTA' and name like 'scan.tif'";
  $u->query($sql);
  $pocet=$u->Num_Rows();
  if ($pocet==0)
  {
    $result = $client->call('CreateBCDoc', array(
      new soapval('','CreateBCDoc',array(
        'lnExternalID'=>$GLOBALS['CONFIG']['ID_PREFIX'].$id_pisemnost,
        'lstrTicketId'=>$session, 
      ),false,'http://tempuri.org/ELO/ELOHTTP')
    ));
    //  print_r($result);
    $id=$result['CreateBCDocResult'];
    If ($id=="-2") echo "Zaznam ".$id_pisemnost." je jiz vytvoren - vraceno id ".$id."<br/>";
    elseIf ($id<1) echo "Zaznam ".$id_pisemnost." nebyl vytvořen - nelze oskenovat! - vraceno id ".$id."<br/>";
    else
    {
      $sql="insert into files (directory,agenda_ident,record_id,private,last_date,last_user_id,name,typefile) 
      values (".$id.",'POSTA',".$id_pisemnost.",'f','".$LAST_DATE."',$OWNER_ID,'scan.tif','image/tiff')";
      $u->query($sql);
    }
   }
   else
    If ($id=="-2") echo "Zaznam ".$id_pisemnost." je jiz vytvoren <br/>";
   
}

  $result = $client->call('LogOut', array(
    new soapval('','LogOut',array(
    ),false,'http://tempuri.org/ELO/ELOHTTP')
  ));

echo "</font>";
echo "<span class='caption'>Skončeno.</span>";
echo "<span class='caption'>Pokračujte kliknutím na Přehled.</span>";


require(FileUp2("html_footer.inc"));

?> 
