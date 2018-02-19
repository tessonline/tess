<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));
//$SOUBOR_ID=9458;
require_once(FileUp2(".admin/upload_.inc"));
require_once(FileUp2(".admin/status.inc"));

if ($SCHVALENO==2)
{
  //dokument neni schvalen
  //pouze ulozime stanovisko

  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 

  $q=new DB_POSTA;
  $sql="update posta_schvalovani set schvaleno=".$SCHVALENO.",datum_podpisu='".Date('d.m.Y H:i:s')."',
  LAST_DATE='".Date('Y-m-d')."',LAST_TIME='".Date('H:i:s')."',LAST_USER_ID=".$USER_INFO["ID"]." where 
  schvalujici_id=".$USER_INFO["ID"]." and posta_id=".$GLOBALS[EDIT_ID];
//  echo $sql;
//  Die('STOP');  
  $q->query($sql);
  NastavStatus($GLOBALS[EDIT_ID]);

  echo '<script>window.opener.document.location.reload(); window.close();</script>';
  
}
if (!$SOUBOR_ID)
{
  require_once(Fileup2("html_footer.inc"));
  Die('CHYBA: Nebyl vybrán soubor');
}

if (!$GLOBALS['TIMESTAMP']) $GLOBALS['TIMESTAMP']=0;
if (!$GLOBALS['VIDITELNY']) $GLOBALS['VIDITELNY']=0;
$viditelnost = 0;
if ($GLOBALS['VIDITELNY']>0)  {
  $viditelnost=2;
  $poz = $GLOBALS['POZICE_VIDITELNY']; 
  $x = $GLOBALS['CONFIG']['VIDITELNY_PODPIS'][$poz]['X'];
  $y = $GLOBALS['CONFIG']['VIDITELNY_PODPIS'][$poz]['Y'];
} 
if (!$x) $x = 150;
if (!$y) $y = -10;

$ts_url=$GLOBALS["CONFIG_POSTA"]["HLAVNI"]["Print2PDF_TS_URL"];
if ($GLOBALS['TIMESTAMP']>0 && strlen($ts_url)<5) 
{
  require_once(Fileup2("html_footer.inc"));
  Die('CHYBA: Není zadána webová služba pro přidělení Časového razítka');
}
$soubory=array();
$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
$upload_records = $uplobj['table']->GetRecordsUploadForAgenda($GLOBALS['EDIT_ID']); 

$SOUBOR_ID = $SOUBOR_ID[0];
while (list($key,$val)=each($upload_records))
  if ($val[ID]==$SOUBOR_ID)
{
      $data=$uplobj['table']->GetUploadFiles($val);
      $base64=$data;
}
if (strlen($data)<1) 
{
  require_once(Fileup2("html_footer.inc"));
  Die('Není k dispozici obsah souboru');
}
//print_r($data);
//Die();
echo '
<span class=caption>Podepsání souboru</span><br/>
Nyní se Vám otevře okno s vašimi elektronickými podpisy. Vyberte prosím odpovídající podpis a vyčkejte na zpracování souboru.
Okno se poté samo zavře.
';
echo '
<form name="frm_edit" action="save.php" method="POST">
<input type="hidden" name="dokument_id" value="'.$GLOBALS[EDIT_ID].'">
<input type="hidden" name="file_data" id="file_data">
<input type="hidden" name="file_id" value="'.$SOUBOR_ID.'">
<input type="hidden" name="SCHVALUJICI_ID" value="'.$SCHVALUJICI_ID.'">
<input type="hidden" name="POZNAMKA" value="'.$POZNAMKA.'">
<input type="hidden" name="SCHVALENO" value="'.$SCHVALENO.'">
</form>
';
require_once(Fileup2("html_footer.inc"));  
echo '
      <OBJECT ID="PDFSigner" type="application/x-firefoxsigner" VIEWASTEXT>
        <font color=red>Chyba inicializace ActiveX komponenty PDFSigner!<br/>
        Je nutno používat Mozilla Firefox a nainstalovat si tento doplněk
        <a href="PDFSigner.msi">PDFSigner.msi</a><br/><br/></font>
      </OBJECT>

 <!-- CLASSID="CLSID:CC503770-F4F5-4A8D-8B5C-4CBAF8343583" -->
<script language="javascript">
	
	function SignFile()
	{
		PDFSigner.PdfFile = "'.base64_encode($base64).'";
		PDFSigner.AddTimeStamp = '.($GLOBALS['TIMESTAMP']?'true':'false').';
    PDFSigner.TSProxyURL = "'.$ts_url.'";
		PDFSigner.ShowErrorMessages = true;
		PDFSigner.Reason = "'.$GLOBALS[DUVOD_PODEPSANI].'";
		PDFSigner.Location = "'.$GLOBALS[MISTO_PODEPSANI].'";
		PDFSigner.Contact = "'.$GLOBALS[KONTAKTNI_INFO].'";
';
if ($viditelnost>0) echo '		PDFSigner.ApperanceFlags = '.$viditelnost.';
		PDFSigner.ApperanceImagePath = "D:\Signature.png";
		PDFSigner.ApperanceText = "[SigningCertSubject_CN]\n[DateTime]\n ";
		PDFSigner.ApperancePosX = '.$x.';
		PDFSigner.ApperancePosY = '.$y.';
		PDFSigner.ApperanceSizeX = 130;
		PDFSigner.ApperanceSizeY = 30;
		PDFSigner.ApperancePage = 1;
		PDFSigner.AppearanceTransparency = true;
';
echo '

		var ret = PDFSigner.Sign();
		//alert("Sign vrátilo " + ret + " (" + PDFSigner.LastError + ")");
    if (ret==0) {
    		document.frm_edit.file_data.value=PDFSigner.PdfFile;
        //alert("hotovo");
        var frm = document.forms[\'frm_edit\'];
        frm.submit();
      }
      else
      {
        alert("Vznikla chyba při podepsani. Chyba: "+PDFSigner.LastError);
        window.close();
      }  
    return false;

	}
  SignFile();
</script>

';



//Run_(array("showaccess"=>true,"outputtype"=>3));

?>

