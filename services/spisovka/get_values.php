<?php
require("tmapy_config.inc");
require(FileUp2(".admin/properties.inc"));
//$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]="utf-8";
require(FileUp2("html_header.inc"));
require_once(FileUp2(".admin/db/db_default.inc"));
require(FileUp2(".admin/convert.inc"));
echo "<h1>Pracuji...</h1>";Flush();
$proxy_hostname=$GLOBALS["CONFIG"]["PROXY_HOSTNAME"]?$GLOBALS["CONFIG"]["PROXY_HOSTNAME"]:false;
$proxy_port=$GLOBALS["CONFIG"]["PROXY_HOSTNAME_PORT"];
$url = "http://wwwinfo.mfcr.cz";
$page = "/cgi-bin/ares/darv_res.cgi?ICO=".$ICO."&odp=txt&xslt=server&jazyk=cz";
$url.=$page;
//echo $url;  
$header="";
$headers = Array("User-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0) ");
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL,$url);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_TIMEOUT, 4); 
curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
curl_setopt($ch, CURLOPT_COOKIEJAR, '-');
 if ($proxy_hostname) curl_setopt($ch, CURLOPT_PROXY, $proxy_hostname.':'.$proxy_port);
$data = curl_exec($ch);
$html=$data;
If (!trim($html)) $neni=true;
//    echo(Win2Iso($html));

/*	$poziceod=strpos($html,'Adresa místa podnikání:');
$pozicedo=strpos($html,'<br>',$poziceod);
 $adresa=trim(substr($html,$poziceod,$pozicedo-$poziceod));
 */
$html=iconv('UTF8','ISO-8859-2',$html);   
//echo $html;
$pole=explode('<br>',$html);
$cislo=strpos($pole[11],':');  

$obchod_nazev=substr($pole[7],16);
$adresa=substr(trim($pole[11]),$cislo+1);

//nekdy se vraci na pocatku mezera, nekdy ne
If (substr($adresa,0,1)==" ") $adresa=substr($adresa,1,strlen($adresa));

//echo "<br /><br />VSTUP:".$adresa."<br />";

$ulice_new=array();

If (strpos($adresa,','))
{
	$psc=substr($adresa,0,5);
  $mesto2=substr($adresa,6,(strpos($adresa,',')-6));
  $ulice=substr($adresa,strpos($adresa,',')+2);
  $arr_ulice_cp=explode(' ',trim($ulice));
  $cp = trim(end($arr_ulice_cp));
  if(ereg('([0-9]+)/?([0-9]*)(.?)',$cp,$reg)){
    //die(print_r($reg));
    $cp = $reg[1];
    $cor = $reg[2];
    $cor_pis = $reg[3];
  }   
  unset($arr_ulice_cp[count($arr_ulice_cp)-1]);
  $ulice = implode(' ',$arr_ulice_cp); 
}
else
{
	$psc=substr($adresa,0,5);
  $mesto2=substr($adresa,6,(strpos($adresa,',')-4));
  $arr_ulice_cp=explode(' ',trim($adresa));
  $cp = trim(end($arr_ulice_cp));
  if(ereg('([0-9]+)/?([0-9]*)(.?)',$cp,$reg)){
    //die(print_r($reg));
    $cp = $reg[1];
    $cor = $reg[2];
    $cor_pis = $reg[3];
  }   



}
echo "|".$mesto2."|".$ulice."|".$psc."|".$cp."|".$cor;

/*
$adresa=str_replace("PSČ:","|",$adresa);
$adresa=str_replace("ulice a číslo: ","|",$adresa);
$adresa=str_replace("obec:","|",$adresa);

$arr_adr=explode("|",$adresa);
$arr_ulice_cp=explode(' ',trim($arr_adr[1]));
$cp = trim(end($arr_ulice_cp));
if(ereg('([0-9]+)/?([0-9]*)(.?)',$cp,$reg)){
  //die(print_r($reg));
  $cp = $reg[1];
  $cor = $reg[2];
  $cor_pis = $reg[3];
}   
unset($arr_ulice_cp[count($arr_ulice_cp)-1]);
$ulice = implode(' ',$arr_ulice_cp); 
$psc=str_replace(" ","",$arr_adr[3]);	
$mesto2 = trim($arr_adr[2]); 
*/
//$value = $obchod_nazev."|".($mesto2?$mesto2:$mesto1)."|".$ulice."|".$cp."|".$psc."|".$cor."|";
$value = strtr($obchod_nazev."|".($mesto2?$mesto2:$mesto1)."|".$ulice."|".$cp."|".$psc."|".$cor."|".$cor_pis,$tr_to,$tr_from);

  //die("<br /><br />".$value);
If ($neni)
{
echo '
<script type="text/javascript">
  alert("Server neodpověděl, zkuste to znovu");
  window.close();
</script>
';
}


?>
<script type="text/javascript">
       window.opener.document.frm_edit.ODESL_PRIJMENI.value = '<?php echo $obchod_nazev;?>';
       window.opener.document.frm_edit.ODESL_POSTA.value = '<?php echo StrTr(($mesto2?$mesto2:$mesto1),$tr_to,$tr_from);?>';
       window.opener.document.frm_edit.ODESL_ULICE.value = '<?php echo StrTr($ulice,$tr_to,$tr_from);?>';
       window.opener.document.frm_edit.ODESL_CP.value = '<?php echo StrTr($cp,$tr_to,$tr_from);?>';
       window.opener.document.frm_edit.ODESL_COR.value = '<?php echo StrTr($cor,$tr_to,$tr_from);?>';
       window.opener.document.frm_edit.ODESL_PSC.value = '<?php echo StrTr($psc,$tr_to,$tr_from);?>';
       window.opener.document.frm_edit.ODESL_PRIJMENI.style.color='red';
       window.opener.document.frm_edit.ODESL_POSTA.style.color='red';
       window.opener.document.frm_edit.ODESL_ULICE.style.color='red';
       window.opener.document.frm_edit.ODESL_CP.style.color='red';
       window.opener.document.frm_edit.ODESL_COR.style.color='red';
       window.opener.document.frm_edit.ODESL_PSC.style.color='red';
//window.returnValue = '<?php echo $value;?>';
  window.close();
</script>
<?php
require(FileUp2("html_footer.inc"));
?>
