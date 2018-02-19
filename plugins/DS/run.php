<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/funkce.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
require(FileUp2("plugins/schvalovani/.admin/schvalovani.inc"));
// include(FileUp2(".admin/upload_fce_.inc"));
include(FileUp2("interface/.admin/upload_funkce.inc"));
include_once(FileUp2(".admin/javascript.inc"));
include(FileUp2(".admin/oth_funkce.inc"));
$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));

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
NewWindow(array("fname" => "Agenda", "name" => "Agenda", "header" => true, "cache" => false, "window" => "edit"));
$q=new DB_POSTA;
$where="";
If ($GLOBALS["CONFIG"]["DB"]=='psql')
{
  $where.=" (DATUM_PODATELNA_PRIJETI) >= ('".$GLOBALS["DATUM_OD"]."')";
  $where.=" AND (DATUM_PODATELNA_PRIJETI) <= ('".$GLOBALS["DATUM_DO"]."')";
}
If ($GLOBALS["CONFIG"]["DB"]=='mssql')
{
  $where.=" CONVERT(datetime,datum_podatelna_prijeti,104) >= CONVERT(datetime,'".$GLOBALS["DATUM_OD"]."',104)";
  $where.=" AND CONVERT(datetime,datum_podatelna_prijeti,104) <= CONVERT(datetime,'".$GLOBALS["DATUM_DO"]."',104)";
}
If ($GLOBALS[ODBOR]<>'')
    $where.=" AND odbor IN (".$GLOBALS[ODBOR].")";

$sql = "select * from posta where  ".$where." AND odeslana_posta='t' and vlastnich_rukou like '9'
and (datum_vypraveni is null) and stornovano is null";

if (!isset($GLOBALS['HAS_DATA_BOX_ID'])) {
  $sql .=  " and odesl_datschranka <> ''";
}
//$sql .=  " and superodbor in (".EedTools::VratSuperOdbor().")";
$q->query($sql);
 while ($q->Next_Record())
{
  $soubory=array();
  $zpravaDS=GetPoleProDS($q->Record['ID'],$client,$session_id);
//print_r($zpravaDS);
  if ($zpravaDS->StatusCode<>'0000') {
 //   echo "Odpověd z ISDS: <b>".TxtEncodingFromSoap($zpravaDS->StatusMessage)."</b>";
//    require(FileUp2("html_footer.inc"));
//    Die();
  }
  $val=$zpravaDS['dmEnvelope'];
  //print_r($val);
  $neni_podepsan=false;
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($q->Record['ID']); 
  while (list($key,$valX)=each($upload_records))
  {
    if (eregi('.pdf',$valX['NAME']) && !JePodepsanyDokument($valX)) 
    {
       $soubory[$key]="<img src=\"".FileUp2('images/alert.gif')."\" border=\"0\" title=\"PDF dokument není podepsán\">".$soubory[$a]['FILE_NAME'];
       $neni_podepsan=true;
    }
    $soubory[$key].='<a href=# onclick="return EditShowAtt(event,'.$valX[ID].',\'ifrm_doc\');" target="ifrm_doc" class="pages">';
    $soubory[$key].=$valX[NAME]."</a><br/>";
  }
  
  if ($q->Record['ODESL_DATSCHRANKA']) {
    $href="<a title='Odeslat dokument do DS' href='javascript:NewWindowAgenda(\"send.php?ID_ODCHOZI=".$q->Record[ID]."\");'><img src='".FileUp2('images/ok_check.gif')."' border='0' target='send_DS'></a>";
  }
  else {
    $href = ' ';
  }
//  if ($neni_podepsan==true || JeVeSchvaleni($q->Record['ID'])) $href= ' ';
  if ($GLOBALS['CONFIG']['BEZ_APROBACE_NELZE_ODESLAT'] && !SchvalenoKladne($q->Record['ID'])) $href = false;
  $schval_proces='<span class="background:black"><a href="javascript:newVedouci('.$q->Record['ID'].')">'.VratImgKeSchvalovani($q->Record['ID']).'</a></span>';
//echo GetDocs($q->Record[ID]);
  $DS_DATA[]=array(
    "id"=>$q->Record[ID],
    "jejich_cj"=>TxtEncodingFromSoap($val[dmRecipientRefNumber].'<br/>'.$val[dmRecipientIdent].'&nbsp;'),
    "nase_cj"=>TxtEncodingFromSoap($val['dmSenderRefNumber'].'<br/>'.$val[dmSenderIdent].'&nbsp;'),
    "datum"=>$q->Record['DATUM_PODATELNA_PRIJETI'],
    "from"=>'<b>'.$q->Record['ODESL_DATSCHRANKA'].'</b><br/>'.UkazAdresu($q->Record['ID'],', '),
    "vec"=>($val[dmAnnotation]),
    "soubory"=>@implode('<br />',$soubory).($neni_podepsan==true?'<br/><font color=red><b>POZOR! Některý z pdf dokumentů není podepsán!</b></font>':''),
    "schvaleni"=>$schval_proces,
    "doruceni"=>'<i>...zatím neodesláno</i>',
    "odkaz"=>$href
  );
}

include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
$db_arr = new DB_Sql_Array;
$db_arr->Data=$DS_DATA;

$caption="Dokumenty určené k odeslání do DS";

if (count($DS_DATA)>0)
  Table(array("db_connector" => &$db_arr,"caption"=>$caption, "showaccess" => true,"appendwhere"=>$where2,"showinfo"=>false,"showediturl"=>"'/ost/posta/edit.php?edit&EDIT_ID='+id","showdelete"=>false,"showedit"=>false,"showselect"=>true,"multipleselect"=>true,"multipleselectsupport"=>true));  
else
  echo "<h1>Odchozí datové zprávy</h1><span class='text'><br/>Žádný dokument není určen k odeslání.</span>";

echo "<script>\n";
echo "<!--\n";
echo "  function newVedouci(id) {\n";
echo "  newwindow = window.open('../../services/spisovka/schvaleni/edit.php?insert&POSTA_ID='+id, 'schvaleni', 'height=500,width=650,scrollbars,resizable');\n";
echo "  newwindow.focus();\n";
echo "  }\n";
echo "//-->\n";
echo "</script>\n";

require(FileUp2("html_footer.inc"));
