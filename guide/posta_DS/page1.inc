<?php
if (strlen($GLOBALS[DS])>4)
{
  echo "<script>";
  $url="/ost/posta/guide/posta_DS/page2.inc?SELECT_IDDS=".$GLOBALS[DS]."&only_test=1";
  echo "window.opener.NewWindowGuide('".$url."');
  </script>";
Die($url);
}

include_once(FileUp2('.admin/convert.inc'));
//include_once(FileUp2('.admin/form_func_ev.inc'));
require(FileUp2(".admin/isds_.inc"));
include(FileUp2("interface/.admin/soap_funkce.inc"));
include(FileUp2("interface/.admin/certifikat_funkce.inc"));
include('plugins/DS/.admin/nastaveni.inc');
require(FileUp2("html_header_full.inc"));

echo '<div id="upl_wait_message" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="nahrávám ..." alt="nahrávám ..."><br>Čekejte prosím, kontaktuji DS ...</div>';
Flush();
/*
  'OVM'=>'U', //normální OVM ',
  'OVM_NOTAR'=>'N', //'notáři',
  'OVM_EXEKUT'=>'E',//'exekutoři',
  'PO'=>'P', //'DS normální PO (z obchodního rejstříku)',
  'PO_ZAK'=>'P', //'DS jiné PO vzniklé ze zákona',
  'PO_REQ'=>'P', //'DS jiné PO vzniklé na ľádost',
  'PFO'=>'F',//'DS normální PFO',
  'PFO_ADVOK'=>'B',//'advokáti',
  'PFO_DANPOR'=>'F',//'daňoví poradci',
  'PFO_INSSPR'=>'F',//'insolvenční správci',
  'FO'=>'O',//'normální FO',    
*/
$a = explode('&', $QUERY_STRING);
$i = 0;
  function utf8_urldecode($str) {
    $str = preg_replace("/%u([0-9a-f]{3,4})/i","&#x\\1;",urldecode($str));
    return html_entity_decode($str,null,'UTF-8');;
  }

if ($GLOBALS[CONFIG_POSTA][DS][ds_cert_id]) $certifikat=VratCestukCertifikatu(0,$GLOBALS[CONFIG_POSTA][DS][ds_cert_id],1); else $certifikat='';
$schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);
//$jmeno = utf8_urldecode ($jmeno);
//$jmeno='Tomáš';
//$jmeno=($jmeno);
//print_r($jmeno);

$dbOwnerInfo=array('dbType'=>$TypDSRev[$odes_typ]);


if ($odes_typ=='F') $dbOwnerInfo=array('dbType'=>'PFO'); 
if ($odes_typ=='P') $dbOwnerInfo=array('dbType'=>'PO'); 


if ($odes_typ=='F' || $odes_typ=='F' )
if ($ico && $odes_typ!='O') $dbOwnerInfo[ic]=$ico;

//if ($firma && $odes_typ!='O' && $odes_typ!='F') $dbOwnerInfo[firmName]='*'.TxtEncoding4Soap($firma).'*';
//if ($prijmeni && $odes_typ!='U' && $odes_typ!='P') $dbOwnerInfo[pnLastName]='*'.TxtEncoding4Soap($prijmeni).'*';
//if ($jmeno && $odes_typ!='U' && $odes_typ!='P') $dbOwnerInfo[pnFirstName]='*'.TxtEncoding4Soap($jmeno).'*';
//if ($mesto) $dbOwnerInfo[adCity]='*'.TxtEncoding4Soap($mesto).'*';

if ($firma && $odes_typ!='O' && $odes_typ!='F') $dbOwnerInfo[firmName]='*'.$firma.'*';
if ($prijmeni && $odes_typ!='U' && $odes_typ!='P') $dbOwnerInfo[pnLastName]='*'.$prijmeni.'*';
if ($jmeno && $odes_typ!='U' && $odes_typ!='P') $dbOwnerInfo[pnFirstName]='*'.$jmeno.'*';

if ($prijmeni && ($odes_typ=='N' || $odes_typ=='E')) $dbOwnerInfo[firmName]='*'.$prijmeni.'*';

if ($mesto) $dbOwnerInfo[adCity]='*'.$mesto.'*';

if ($datnar && $odes_typ!='U' && $odes_typ!='P') $dbOwnerInfo[biDate]=EedTools::czdate2eng($datnar." ");

if ($odes_typ == 'O') {
  $hodnoty=$schranka->FindPersonalDataBox($dbOwnerInfo);
} else {
  $hodnoty=$schranka->FindDataBox($dbOwnerInfo);
}

if ($schranka->StatusCode<>'0000') echo "Odpověd z ISDS: <b>".TxtEncodingFromSoap($schranka->StatusMessage)."</b>";
else
{
  
    include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
    $db_arr = new DB_Sql_Array;
//  print_r($hodnoty);
  while (list($key,$val)=each($hodnoty))
  {
//print_r($val);
    $adresa=$val[adStreet];
    if ($val[adNumberInStreet] && $val[adNumberInMunicipality]) $adresa.=" ".$val[adNumberInMunicipality]."/".$val[adNumberInStreet];
    if ($val[adNumberInStreet] && !$val[adNumberInMunicipality]) $adresa.=" ".$val[adNumberInStreet];
    if (!$val[adNumberInStreet] && $val[adNumberInMunicipality]) $adresa.=" ".$val[adNumberInMunicipality];
    $adresa.=", ".$val[adZipCode]." ".$val[adCity];
    $stav=$val[dbState];
    $majitel=TxtEncodingFromSoap(trim($val[firmName])<>''?$val[firmName]:($val[pnLastName]." ".$val[pnFirstName]));
//     if ($stav<>1) $text='<a title="'.$CheckDataBoxResponse[$stav].'"><font color=red><b>neplatná</b></font></a>';
//     else $text='<font color=green><b>platná</b></font>';
    if ($stav<>1) $text='neplatná - '.$CheckDataBoxResponse[$stav].'';
    else $text='platná';

      $DS_DATA[]=array(
//      "ID"=>"&nbsp;<b>".$val[dbID]."</b>&nbsp;",
//      "ID"=>base64_encode($val[dbID]),
      "ID"=>$val[dbID],
//      "IDDZ"=>$val[dbID],
      "majitel"=>$majitel,
//      "ico"=>TxtEncodingFromSoap(trim($val[ic])?$val[ic]:CZDate($val[biDate])),
      "ico"=>TxtEncodingFromSoap(trim($val[ic])?$val[ic]:$val[biDate]),
      "adresa"=>TxtEncodingFromSoap($adresa),
      "narodnost"=>TxtEncodingFromSoap($val[nationality]),
      "stav"=>$text,
    );
  }
  $db_arr->Data=$DS_DATA;
  if (count($DS_DATA)>0)
  {
    $GLOBALS['TABLENAME'] = 'DS';
//  unset($DS_DATA);
    Table(array("schema_file"=>"plugins/DS/.admin/table_schema_DS.inc",
                "showaccess" => true,
                "tablename"=>"DS",
                "showedit"=>false,
                "formvars"=>array("GUIDE_DIRECTION"=>0,"GUIDE_ID"=>0),
                "showdelete"=>false,
                "showselect"=>true,
                "showinfo"=>false,
                "nopaging"=>true,
                "setvars"=>true,
                "nocaption"=>true,
                "select_id"=>"ID",
                "agenda"=>"POSTA_DS",
//                "action"=>"./guide/posta_DS/page2.inc",
                "db_connector" => &$db_arr,
              ));  
  }
  else
    echo "<span class='caption'>Danému filtru neopdovídá žádná datová schránka.</span>";
    
}




echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
require(FileUp2("html_footer.inc"));
