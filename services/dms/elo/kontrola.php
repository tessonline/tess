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

require(FileUp2("html_header_posta.inc"));

$w=new DB_POSTA;
$sql="select id,directory from files where agenda like 'POSTA' and filesize is null or filesize=0";
$q->query($sql);
while ($q->Next_Record())
{
  $id=$q->Record[ID];
  $client = new soapclient($GLOBALS["PROPERTIES"]["ELO_DMS_IP_PORT"], true);
  if ($GLOBALS["PROPERTIES"]["ELO_DMS_ENDPOINT"])
    $client->setEndpoint($GLOBALS["PROPERTIES"]["ELO_DMS_ENDPOINT"]);
  
  if ($debug) {echo "Connect to ".$GLOBALS["PROPERTIES"]["ELO_DMS_IP_PORT"];Flush();}
  $client->soap_defencoding='UTF-8';
  $client->decodeUTF8(false);
  $client->decode_utf8 = false; 
  $err = $client->getError();
  if ($err) {
      Die('ELO systém není dostupný');
  }
  $result = $client->call('Login', array(
    new soapval('','Login',array(
      'lstrUSRName'=>$GLOBALS["PROPERTIES"]["ELO_DMS_LOGIN"],
      'lstrUSRPsw'=>$GLOBALS["PROPERTIES"]["ELO_DMS_PASSWD"],
      'lstrArchivName'=>$GLOBALS["PROPERTIES"]["ELO_DMS_ARCHIV"],
    ),false,'http://tempuri.org/ELO/ELOHTTP')
  ));
   echo '<pre>' . htmlspecialchars($client->request, ENT_QUOTES) . '</pre>';
  If ($result['LoginResult']<>'true')  
  { 
    //echo "zkusime pripojit znova<br/>";
    $result = $client->call('Login', array(
      new soapval('','Login',array(
        'lstrUSRName'=>$GLOBALS["PROPERTIES"]["ELO_DMS_LOGIN"],
        'lstrUSRPsw'=>$GLOBALS["PROPERTIES"]["ELO_DMS_PASSWD"],
        'lstrArchivName'=>$GLOBALS["PROPERTIES"]["ELO_DMS_ARCHIV"],
      ),false,'http://tempuri.org/ELO/ELOHTTP')
    ));
    if ($debug) print_r($result);
    If ($result['LoginResult']<>'true') {echo "<script>alert('ELO DMS není dostupné!');</script>";return $name; }
  } 
  $result = $client->call('getVersions', array(
    new soapval('','getVersions',array(
      'lint32ID'=>$q->Record[DIRECTORY],
    ),false,'http://tempuri.org/ELO/ELOHTTP')
  ));
  if ($debug) print_r($result);
  If (trim ($result['getVersionsResult']))
  {
    $data=explode(',',$result['getVersionsResult']);
    if ($DEBUG) print_r($data);
//     $result="mesto.rtf/application/rtf/39449/1/7.6.2007 11:12:0";
//    $data=explode('/',$result['getVersionsResult']);
    If (strlen(trim($name))<1)
    {
      //musime dopsat nazev a typ souboru
      $name=$data[1]?$data[1]:'scan.tif';
      if ($debug) print_r($data);
      $name=iconv('UTF-8','ISO-8859-2',$name); 
      $typ=$data[2]?$data[2]:'image/tiff';
      $velikost=$data[3]?$data[3]:0;
/*      if (!is_numeric($velikost))
      {$velikost=$data[3]; $typ.="/".$data[2];}
  */
      $datum=Date('Y-m-d');
      $db = $GLOBALS["PROPERTIES"]["DB_NAME"]?$GLOBALS["PROPERTIES"]["DB_NAME"]:"DB_DEFAULT";
      $u = new $db;
      $sql="update files set name='".$name."',filesize=".$velikost.",typefile='".$typ."',last_date='".$datum."',description='scan' where id=".$id;
      //echo $sql;
   //   $u->query($sql);
   }
//    print_r($result);
  $href = "get_file.php?idf=".$id;
  $ret = "<a href='$href' target='_blank' class='pages'>$name</a>";

}
