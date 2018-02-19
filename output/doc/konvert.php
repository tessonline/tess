<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));
//print_r($_POST);
//Die();

require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
include_once($GLOBALS['TMAPY_LIB'].'/upload/functions/SOAP_602_print2pdf.php');

$eed_konektor=$GLOBALS["KONEKTOR"]["SOAP_SERVER"];
$client = new tw_soapclient($eed_konektor, false);
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

$cesta=$GLOBALS["TMAPY_DIR"]."/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_VNITRNI"];
$cela_cesta=$cesta."/".$cj2."/".$cj1;
$nazev_souboru=md5($cj2.$cj1);


//$nazev_souboru='soubor.htm';
//$celeunc=$cela_cesta."/".$nazev_souboru;

//do ostre verze odremovat
$celeunc=$cela_cesta."/".$nazev_souboru.".rtf";

$fp=fopen($celeunc,'r');
$data=fread($fp,filesize($celeunc));
fclose($fp);

$a=new SOAP_602_print2pdf($SERVER_CONFIG["UPLOAD_CONFIG"]["MODULES"]["table"]["STORAGE"]["Print2PDF_SERVICE"]);
list($file_name,$file_data)=$a->ConvertStream(basename($celeunc),$data);
//list($file_name,$file_data)=$a->ConvertFile($celeunc,basename($celeunc));
//echo "$file_name $file_data";

$soubory[0]['FILE_ID']='';
$soubory[0]['FILE_NAME']='odpoved_'.$cj1.'-'.$cj2.'.pdf';
$soubory[0]['FILE_DESC']='automaticka konverze';
//$soubory[0]['BIND_TYPE']='application/pdf';
$soubory[0]['FILE_DATA']=base64_encode($file_data);
echo "<span class=caption>Ukládám přílohy... <br/></span>"; Flush();
//print_r($soubory);
//Die();

    //echo "data jsou ".$soubor['FILE_DATA'];
    $result = $client->call('send_files', array(
      'session_id'=>$session_id,
      'dokument_id'=>$ID,
      'soubory'=>$soubory
      )
    );
//echo '<pre>' . htmlspecialchars($client->request, ENT_QUOTES) . '</pre>';      

if ($result[RESULT]=='OK') echo '<script>window.opener.document.location.reload(); window.close();</script>';
else
echo '<span class="caption">Chyba: ';
print_r($result);
require_once(Fileup2("html_footer.inc"));  
//echo '<pre>' . htmlspecialchars($client->response, ENT_QUOTES) . '</pre>';Die();
//Die();
