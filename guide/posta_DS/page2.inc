<?php
//session_start();
$sel = $_GET['SELECT_IDDS'];
include_once('tmapy_config.inc');
include_once(FileUp2('.admin/convert.inc'));
include_once(FileUp2('.admin/config.inc'));
require(FileUp2(".admin/isds_.inc"));
include(FileUp2("interface/.admin/soap_funkce.inc"));
//include_once(FileUp2(".admin/form_func_ev.inc"));
include(FileUp2('interface/DS/.admin/nastaveni.inc'));
include(FileUp2("interface/.admin/certifikat_funkce.inc"));
require(FileUp2("html_header_full.inc"));
//print_r($sel);
echo '<div id="upl_wait_message" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="nahrávám ..." alt="nahrávám ..."><br>Čekejte prosím, kontaktuji DS ...</div>';
Flush();
if ($GLOBALS[CONFIG_POSTA][DS][ds_cert_id]) $certifikat=VratCestukCertifikatu(0,$GLOBALS[CONFIG_POSTA][DS][ds_cert_id],1); else $certifikat='';
$schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);
$dbOwnerInfo=array('dbID' => $sel);

//if (!$only_test)
{
  $hodnoty=$schranka->FindDataBox($dbOwnerInfo);
  $hodnoty=$hodnoty[0];
  $prijmeni=TxtEncodingFromSoap($hodnoty[pnLastName]);
  $jmeno=TxtEncodingFromSoap($hodnoty[pnFirstName]." ".$hodnoty[pnMiddleName]);
  if ($hodnoty[dbType]=='PO') $typ='P';
  if ($hodnoty[dbType]=='OVM') $typ='U';
  if ($hodnoty[dbType]=='OVM_NOTAR' || $hodnoty[dbType]=='OVM_EXEKUT') $prijmeni=TxtEncodingFromSoap($hodnoty[firmName]);
  $ds=$hodnoty[dbID];
  $ico=$hodnoty[ic];
//  $datnar=CZDate($hodnoty[biDate]);
  $firma=TxtEncodingFromSoap($hodnoty[firmName]);
  $ulice=TxtEncodingFromSoap($hodnoty[adStreet]);
  $cor=TxtEncodingFromSoap($hodnoty[adNumberInStreet]);
  $cp=TxtEncodingFromSoap($hodnoty[adNumberInMunicipality]);
  $psc=str_replace(' ','',$hodnoty[adZipCode]);
  $mesto=TxtEncodingFromSoap($hodnoty[adCity]);
}
//print_r($dbOwnerInfo);
//$vysl=$schranka->CheckDataBox($dbOwnerInfo);
$vysl = 1;
//Die(print_r($vysl));
echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
if ($vysl<>1)
//if (1 == 2)
{
echo "<font color=red><b>".$CheckDataBoxResponse[$vysl]."</b></font><br/>";
echo '
<script language="JavaScript" type="text/javascript">
<!--
  if (window.opener.document.frm_edit)
  {
      window.opener.document.frm_edit.VLASTNICH_RUKOU.value = 1;
      window.opener.document.frm_edit.ODESL_DATSCHRANKA.style.color = "red";
  }
  if (window.opener.document.frm_edit)
  {
      window.opener.document.frm_edit.VLASTNICH_RUKOU.value = 1;
      window.opener.document.frm_edit.ODESL_DATSCHRANKA.style.color = "red";
  
  }
  window.close();
  </script>
  ';
  require(FileUp2('html_footer.inc')); Die("");
}
if ($schranka->StatusCode<>'0000') {require(FileUp2('html_footer.inc')); Die("<h1 color=red>".TxtEncodingFromSoap($schranka->StatusMessage)."</h1>");}
echo '
<script language="JavaScript" type="text/javascript">
<!--
  if (window.opener.document.frm_edit)
  {
';
if ($only_test=='1AAA')
echo "
      window.opener.document.frm_edit.VLASTNICH_RUKOU.value = 9;
      window.opener.document.frm_edit.ODESL_DATSCHRANKA.style.color = 'green';
  }
  if (window.opener.document.frm_edit.VLASTNICH_RUKOU)
  {
      window.opener.document.frm_edit.VLASTNICH_RUKOU.value = 9;
      window.opener.document.frm_edit.ODESL_DATSCHRANKA.style.color = 'green';
  
  }

  window.close();
//-->
</script>
  
";

    if ($typ=='U' || $typ=='P')  
    echo "
      window.opener.document.frm_edit.ODESL_PRIJMENI_FIRMA.value = '".$firma."';
      window.opener.document.frm_edit.ODESL_PRIJMENI_FIRMA.style.color='red';
    ";
    else
    echo "
      window.opener.document.frm_edit.ODESL_OSLOVENI.value = '".$osloveni."';
      window.opener.document.frm_edit.ODESL_OSLOVENI.style.color='red';
      window.opener.document.frm_edit.ODESL_DATNAR.value = '".$datnar."';
      window.opener.document.frm_edit.ODESL_DATNAR.style.color='red';
      window.opener.document.frm_edit.ODESL_PRIJMENI.value = '".$prijmeni."';
      window.opener.document.frm_edit.ODESL_PRIJMENI.style.color='red';
      window.opener.document.frm_edit.ODESL_JMENO.value = '".$jmeno."';
      window.opener.document.frm_edit.ODESL_JMENO.style.color='red';
    ";
    
    echo "
      window.opener.document.frm_edit.ODESL_ICO.value = '".$ico."';
      window.opener.document.frm_edit.ODESL_ICO.style.color='red';
      window.opener.document.frm_edit.ODESL_ODD.value = '".$odd."';
      window.opener.document.frm_edit.ODESL_ODD.style.color='red';
      window.opener.document.frm_edit.ODESL_OSOBA.value = '".$osoba."';
      window.opener.document.frm_edit.ODESL_OSOBA.style.color='red';
      
      
      window.opener.document.frm_edit.ODESL_ULICE.value = '".$ulice."';
      window.opener.document.frm_edit.ODESL_ULICE.style.color='red';
    
      window.opener.document.frm_edit.ODESL_CP.value = '".$cp."';
      window.opener.document.frm_edit.ODESL_CP.style.color='red';
    
      window.opener.document.frm_edit.ODESL_COR.value = '".$cor."';
      window.opener.document.frm_edit.ODESL_COR.style.color='red';
    
      window.opener.document.frm_edit.ODESL_POSTA.value = '".$mesto."';
      window.opener.document.frm_edit.ODESL_POSTA.style.color='red';
    
      window.opener.document.frm_edit.ODESL_PSC.value = '".$psc."';
      window.opener.document.frm_edit.ODESL_PSC.style.color='red';

      if (window.opener.document.frm_edit.VLASTNICH_RUKOU)
      {
        window.opener.document.frm_edit.DOPORUCENE.value = 5;
        window.opener.TypObalky(window.opener.document.frm_edit.VLASTNICH_RUKOU,'0')
  
        window.opener.document.frm_edit.VLASTNICH_RUKOU.value = 9;
      }
      
      window.opener.document.frm_edit.ODESL_DATSCHRANKA.value = '".$ds."';
      window.opener.document.frm_edit.ODESL_DATSCHRANKA.style.color = 'green';
      window.opener.document.frm_edit.TYP_DOKUMENTU.value = 'D';      
  }
  else
  {
    ";
    if ($typ=='U' || $typ=='P')  
    echo "
      window.opener.document.frm_edit.ODESL_PRIJMENI_FIRMA.value = '".$firma."';
      window.opener.document.frm_edit.ODESL_PRIJMENI_FIRMA.style.color='red';
    ";
    else
    echo "
      window.opener.document.frm_edit.ODESL_OSLOVENI.value = '".$osloveni."';
      window.opener.document.frm_edit.ODESL_OSLOVENI.style.color='red';
      window.opener.document.frm_edit.ODESL_PRIJMENI.value = '".$prijmeni."';
      window.opener.document.frm_edit.ODESL_PRIJMENI.style.color='red';
      window.opener.document.frm_edit.ODESL_JMENO.value = '".$jmeno."';
      window.opener.document.frm_edit.ODESL_JMENO.style.color='red';
    ";
    
    echo "
      window.opener.document.frm_edit.ODESL_ICO.value = '".$ico."';
      window.opener.document.frm_edit.ODESL_ICO.style.color='red';
      window.opener.document.frm_edit.ODESL_ODD.value = '".$odd."';
      window.opener.document.frm_edit.ODESL_ODD.style.color='red';
      window.opener.document.frm_edit.ODESL_OSOBA.value = '".$osoba."';
      window.opener.document.frm_edit.ODESL_OSOBA.style.color='red';
      
      
      window.opener.document.frm_edit.ODESL_ULICE.value = '".$ulice."';
      window.opener.document.frm_edit.ODESL_ULICE.style.color='red';
    
      window.opener.document.frm_edit.ODESL_CP.value = '".$cp."';
      window.opener.document.frm_edit.ODESL_CP.style.color='red';
    
      window.opener.document.frm_edit.ODESL_COR.value = '".$cor."';
      window.opener.document.frm_edit.ODESL_COR.style.color='red';
    
      window.opener.document.frm_edit.ODESL_POSTA.value = '".$mesto."';
      window.opener.document.frm_edit.ODESL_POSTA.style.color='red';
    
      window.opener.document.frm_edit.ODESL_PSC.value = '".$psc."';
      window.opener.document.frm_edit.ODESL_PSC.style.color='red';

      window.opener.document.frm_edit.TYP_DOKUMENTU.value = 'D';

      if (window.opener.document.frm_edit.VLASTNICH_RUKOU)
      {
        window.opener.document.frm_edit.VLASTNICH_RUKOU.value = 9;

        window.opener.TypObalky(window.opener.document.frm_edit.VLASTNICH_RUKOU,'0')
        window.opener.document.frm_edit.DOPORUCENE.value = 5;
      }
      window.opener.document.frm_edit.ODESL_DATSCHRANKA.value = '".$ds."';
      window.opener.document.frm_edit.ODESL_DATSCHRANKA.style.color='green';
  }

  parent.$.fancybox.close();
//-->
</script>
    ";
