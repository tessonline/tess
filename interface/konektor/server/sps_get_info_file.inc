<?php
 
Function get_info_file($session_id,$dokument_id,$file_id)
{
  If (!$software_id=JeNalogovan($session_id)) return VratChybu($session_id,'get_info_file','Neprovedena identifikace');
  if (!$dokument_id) return VratChybu($session_id,'get_info_file','Není zadán dokument_id');
  $stav=$GLOBALS["KONEKTOR"][$software_id]["STAV"]; //stav+1 = pozaduje se k vyrizeni v ext. programu
  $q=new DB_POSTA;
  if ($dokument_id) $sql="SELECT * FROM posta WHERE id = '".$dokument_id."'";
  $q->query($sql);
  $pocet=$q->Num_Rows();
  if ($pocet<1) return VratChybu($session_id,'get_info_files','Nenalezen odpovídající dokument_id');
  $q->Next_Record();
  $stav_x=$q->Record["STAV"]-$stav;
//  if ($stav_x<1 || $stav_x>3) return VratChybu($session_id,'get_files','Nemáte přístup k tomuto souboru (stav není 2)');
//  echo $stav_x;

  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($dokument_id);
//  print_r($upload_records);
  $seznam_souboru=array();
  
  while (list($key,$val)=each($upload_records))
  {
    $data=$uplobj['table']->GetUploadFiles($val);
    $file[$counter2][FILE_ID]=$val[ID];
    $file[$counter2][FILE_NAME]=TxtEncoding4Soap($val[NAME]);
    $file[$counter2][FILE_DESC]=TxtEncoding4Soap($val[DESCRIPTION]);
    $file[$counter2][FILE_SIZE]=$val[FILESIZE];
    $file[$counter2][BIND_TYPE]=$val[TYPEFILE];
    // v pripade, pokud prijde i file_id, pak vratime obsah daneho souboru
    if ($file_id==$val[ID]) $file[$counter2][FILE_DATA]=base64_encode($data);
    else $file[$counter2][FILE_DATA]='';
    
    fclose($fp);
    $counter2++;
    $text='(get_info_file) - k dokumentu ('.$dokument_id.') byl ukázán soubor '.$val["NAME"].' - ID: ('.$file_ident.')';
    WriteLog($software_id,$text,$session_id);
  }
  $text='Operace proběhla v pořádku';
  $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
  $vysledek = array(
    'return'=>new soapval('Result', 'tns:Result', $value),
    'soubory'=>new soapval('soubory', 'tns:soubory',$file),
  );
  return VratVysledek($vysledek);
}


