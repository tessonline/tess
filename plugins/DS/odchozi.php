<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/funkce.inc"));
require(FileUp2(".admin/soap_funkce.inc"));
include(FileUp2(".admin/upload_fce_.inc"));
include(FileUp2(".admin/oth_funkce.inc"));

require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
$eed_konektor=$GLOBALS["KONEKTOR"]["SOAP_SERVER"];
$client = new TW_soapclient($eed_konektor, false);
$client->soap_defencoding='UTF-8';
$client->decodeUTF8(false);
$err = $client->getError();
if ($err) {
    echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
    echo $button_back;
    Die('Konektor EED není dostupný');
}
$result = $client->call('login', array(
    'software_id'=>'DS',
    'login'=>'AUTORIZOVANY_PRISTUP',
    'userpasswd'=>'11'
  )
);
$session_id=$result['session_id'];

$GLOBALS["ODCHOZI_DS"]=true;
$q=new DB_POSTA;
$sql="select * from posta where odeslana_posta='t' and vlastnich_rukou like '9'
and (datum_vypraveni is null) and stornovano is null and ODESL_DATSCHRANKA is not null";
// echo $sql;
$q->query($sql);
while ($q->Next_Record())
{
  $zpravaDS=GetPoleProDS($q->Record[ID],$client,$session_id);
  if ($zpravaDS->StatusCode<>'0000') {
 //   echo "Odpověd z ISDS: <b>".TxtEncodingFromSoap($zpravaDS->StatusMessage)."</b>";
//    require(FileUp2("html_footer.inc"));
//    Die();
  }
  $val=$zpravaDS[dmEnvelope];
//  print_r($val);
    $href="<a title='Odeslat dokument do DS' href='send.php?ID_ODCHOZI=".$q->Record[ID]."'><img src='".FileUp2('images/ok_check.gif')."' border='0'></a>";
      $DS_DATA[]=array(
      "id"=>$q->Record[ID],
      "jejich_cj"=>TxtEncodingFromSoap($val[dmRecipientRefNumber].'<br/>'.$val[dmRecipientIdent].'&nbsp;'),
      "nase_cj"=>TxtEncodingFromSoap($val[dmSenderRefNumber].'<br/>'.$val[dmSenderIdent].'&nbsp;'),
      "datum"=>$q->Record[DATUM_PODATELNA_PRIJETI],
      "from"=>'<b>'.$q->Record[ODESL_DATSCHRANKA].'</b><br/>'.UkazAdresu($q->Record[ID],', '),
      "vec"=>TxtEncodingFromSoap($val[dmAnnotation]),
      "soubory"=>GetDocs($q->Record[ID],'POSTA'),
      "doruceni"=>'<i>...zatím neodesláno</i>',
      "odkaz"=>$href
    );

}
//      "soubory"=>//TxtEncodingFromSoap(implode('<br/>',$odkaz_soubor)),
include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
$db_arr = new DB_Sql_Array;
$db_arr->Data=$DS_DATA;

if (count($DS_DATA)>0)
  Table(array("db_connector" => &$db_arr,"showaccess" => true,"appendwhere"=>$where2,"showinfo"=>false,"showediturl"=>"'/ost/posta/edit.php?edit&EDIT_ID='+id","showdelete"=>false,"showselect"=>true,"multipleselect"=>true));  
else
  echo "<span class='caption'>Odchozí datové zprávy</span><span class='text'><br/>Žádný dokument není určen k odeslání.</span>";
require(FileUp2("html_footer.inc"));
