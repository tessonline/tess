<?php

require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/upload_.inc"));
require_once(Fileup2("posta/.admin/properties.inc"));
require_once(Fileup2(".admin/status.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 

//if (strlen($_POST[file_data])<10) echo '<script>window.close();</script>';


$uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true,'skip_access'=>true));

$data=base64_decode($_POST[file_data]);


list($a, $data) = explode(',', $data);

$data = base64_decode($data);

$val['FILE_ID']=$_POST[file_id];

$upload_records = $uplobj['table']->GetRecordsUploadForAgenda($_POST["dokument_id"]);
$update=false;
while (list($key1,$val1)=each($upload_records)) {
  if ($val[FILE_ID]==$val1[ID]) {
    $file_name = $val1[NAME];
    $GLOBALS['RENAME'] = $file_name;
    $update=true;
    $GLOBALS["ID"]=$val1[ID];
    $GLOBALS["FILE_ID"]=$val1[ID];
    $GLOBALS["UPL_FILE"]=$val[FILE_NAME];
    $GLOBALS["LAST_DATE"]=Date('Y-m-d');
    $GLOBALS["OWNER_ID"]=$val1[LAST_USER_ID];
    $GLOBALS["UPL_DIR"]='.';
    $GLOBALS['archiv_file_system']=true;
    $GLOBALS['COSTIM']='archiv_a'; //archivuj puvodni
    $GLOBALS['show_typ']=2;
    $GLOBALS['EDIT_ID']=$val[FILE_ID];
  }
}

$GLOBALS['LAST_USER_ID'] = $GLOBALS["LAST_USER_ID"]?$GLOBALS["LAST_USER_ID"]:$GLOBALS["KONEKTOR"][$software_id]["LAST_USER_ID"];

$tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].uniqId().'.pdf';
if (is_file($tmp_soubor)) unlink($tmp_soubor);
//$data = str_replace("\xEF\xBB\xBF",'',$data);
//$data=base64_decode($data);
//$data = str_replace("\xEF\xBB\xBF",'',$data);
//zbavime
if (strlen($data)<1) Die('Není k dispozici obsah souboru '.$val["FILE_NAME"]);
if (!$fp=fopen($tmp_soubor,'w')) Die('Chyba pri ulozeni tmp souboru '.$tmp_soubor);
fwrite($fp,$data);
fclose($fp);
$GLOBALS['DESCRIPTION'] = 'el. podepsano';
$GLOBALS['RENAME'] = $file_name;
UNSET($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['ONLY_FILE_TYPES']);
$ret = $uplobj['table']->SaveFileToAgendaRecord($tmp_soubor, $dokument_id);


//print_r($ret);

if ($_POST[SCHVALENO]) {
  $q=new DB_POSTA;
  $sql="update posta_schvalovani set schvaleno=".$_POST[SCHVALENO].",datum_podpisu='".Date('d.m.Y H:i:s')."',
  LAST_DATE='".Date('Y-m-d')."',LAST_TIME='".Date('H:i:s')."',LAST_USER_ID=".$USER_INFO["ID"]." where 
  schvalujici_id=".$USER_INFO["ID"]." and posta_id=".$_POST[dokument_id];
  //echo $sql;
  $q->query($sql);
  NastavStatus($_POST[dokument_id]);
 // echo $sql;
//    Die($sql);
}
if ($_POST[SCHVALUJICI_ID]) {
  $q=new DB_POSTA;
  $sql="insert into posta_schvalovani (POSTA_ID,SCHVALUJICI_ID,DATUM_ZALOZENI,POZNAMKA,LAST_DATE,LAST_TIME,LAST_USER_ID,OWNER_ID)
  VALUES (".$_POST[dokument_id].",".$_POST[SCHVALUJICI_ID].",'".Date('d.m.Y H:i:s')."','".$_POST[POZNAMKA]."','".Date('Y-m-d')."',
  '".Date('H:i:s')."',".$USER_INFO["ID"].",".$USER_INFO["ID"].")";
  //echo $sql;
  $q->query($sql);
  NastavStatus($_POST[dokument_id]);
//   echo $sql;
//    Die($sql);
}


//  echo '<script>window.opener.document.location.reload(); window.close();</script>';
echo '
Uloženo, aktualizuji stránku...
';
Die();
/*
<script language="JavaScript" type="text/javascript">
  if (window.opener.document) {
    window.opener.document.location.reload();
  }
//  window.close();
</script>
';
*/