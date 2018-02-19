<?php
  require_once(FileUp2('.admin/upload_.inc'));

function VyberCertifikat($smer)
{
  //funkce pro vyber odpovidajiciho certifikatu
  
}
function NactiCertifikat($val,$cesta)
{
  $soubor=$cesta.$val[DIRECTORY].$val[NAME];
  $soubor=FileSystemConvertFNToFS($soubor);
  if(Is_File($soubor))
  {
    $fp=fopen($soubor,'r');
    $data=fread($fp,filesize($soubor));
    $val[CONTENT]=$data;
    fclose($fp);
  } 
  return $val;
}

function VratCertifikat($osoba,$id,$smer)
{

  $q=new DB_POSTA;
  if ($osoba>0) $sql='select id from posta_certifikaty where osoba in ('.$osoba.')';
  else $sql='select id from posta_certifikaty where id in ('.$id.')';
  $q->query($sql);
  $q->Next_Record();
  $id=$q->Record["ID"];
  if (!$id)
  {
    VyberCertifikat($smer);
    return false;
  }
  //nacteme pem klic z uploadu.
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA_CERTIFIKATY','noshowheader'=>true));
  $cesta=$uplobj['table']->main_dir;
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);   
  $upload_records=end($upload_records);
  $cert=$uplobj['table']->GetUploadFiles($upload_records); 
//  $cert=NactiCertifikat($upload_records,$cesta);
  return $cert;
}

function VratCestukCertifikatu($osoba,$id,$smer)
{

  $q=new DB_POSTA;
  if ($osoba>0) $sql='select id from posta_certifikaty where osoba in ('.$osoba.')';
  else $sql='select id from posta_certifikaty where id in ('.$id.')';
  $q->query($sql);
  $q->Next_Record();
  $id=$q->Record["ID"];
  if (!$id)
  {
    VyberCertifikat($smer);
    return false;
  }
  //nacteme pem klic z uploadu.
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA_CERTIFIKATY','noshowheader'=>true));
  $cesta=$uplobj['table']->main_dir;
  if (!$cesta)
  {
    $MAIN_DIR = $GLOBALS["TMAPY_DIR"].'/';
    $MAIN_DIR.= $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['UPLOAD_DIR']?$GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['UPLOAD_DIR']:'data'; 
    $cesta=$MAIN_DIR;
  } 
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);   
  $upload_records=end($upload_records);
  $data=$uplobj['table']->GetUploadFiles($upload_records);
  $soubor=$cesta.$upload_records[DIRECTORY].$upload_records[NAME]."2";
  $soubor=FileSystemConvertFNToFS($soubor);
  $fp=fopen($soubor,'w');
  fwrite($fp,$data);
  fclose($fp);
  //$cert=NactiCertifikat($upload_records,$cesta);
  return $soubor;
}
