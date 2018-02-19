<?php
 
Function send_files($session_id,$dokument_id,$files)
{
//  If (!$software_id=JeNalogovan($session_id)) return VratChybu($session_id,'send_files','Neprovedena identifikace');
  if (!$dokument_id) return VratChybu($session_id,'send_files','Není zadán dokument_id');
  $stav=$GLOBALS["KONEKTOR"][$software_id]["STAV"]+2; //stav+1 = pozaduje se k vyrizeni v ext. programu
  $q=new DB_POSTA;
  if ($dokument_id) $sql="SELECT * FROM posta WHERE id = '".$dokument_id."'";
//  $sql.=" AND stav in (".$stav.")";
  $q->query($sql);
  $pocet=$q->Num_Rows();
  if ($pocet<1) return VratChybu($session_id,'send_files','Nenalezen odpovídající dokument_id');
  $q->Next_Record();
//  if ($q->Record["STAV"]<>$stav) return VratChybu($session_id,'send_files','Nemáte přístup k tomuto souboru (stav není 2)');

  $counter=0;
  $counter2=0;
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true,'skip_access'=>true));

  //if (is_array($files[soubor][0])) $soubory=$files[soubor];
  //else 
  if ($files['item']['FILE_NAME']) $soubory['item'][0]=$files['item']; else $soubory['item']=$files;

  //print_r($soubory);
  //$soubory=$files[soubor];
  while (list($key,$val)=each($soubory['item']))
  {
    if (!$val["FILE_NAME"]) return VratChybu($session_id,'send_files','Není zadán název souboru');
    $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($q->Record["ID"]);
    $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$val["FILE_NAME"]; 
    $GLOBALS['DESCRIPTION'] = TxtEncodingFromSoap($val[FILE_DESC]);
    $update=false;
    while (list($key1,$val1)=each($upload_records))
    {
      if ($val[FILE_ID]==$val1[ID]) 
      {
//print_r($val1);
        $val[FILE_NAME]=$val1[NAME];
        $update=true;
        $GLOBALS["ID"]=$val1[ID];
        $GLOBALS["FILE_ID"]=$val1[ID];
        $GLOBALS["UPL_FILE"]=$val[FILE_NAME];
        $GLOBALS["LAST_DATE"]=Date('Y-m-d');
        $GLOBALS["OWNER_ID"]=$val1[LAST_USER_ID];
        $GLOBALS["UPL_DIR"]='.';
        $GLOBALS['archiv_file_system']=true;
        $tmp_soubor='/tmp/upload/'.$val[FILE_NAME];
        $tmp_soubor=TxtEncoding4Soap($tmp_soubor);
        $GLOBALS['COSTIM']='archiv_a'; //archivuj puvodni
        $GLOBALS['show_typ']=2;
        $GLOBALS['EDIT_ID']=$val[FILE_ID];

      }
    }

    $GLOBALS['LAST_USER_ID'] = $GLOBALS["LAST_USER_ID"]?$GLOBALS["LAST_USER_ID"]:$GLOBALS["KONEKTOR"][$software_id]["LAST_USER_ID"];

    //$tmp_soubor=TxtEcondingFromSoap(FileSystemConvertFNToFS($tmp_soubor));
    if (is_file($tmp_soubor)) unlink($tmp_soubor);
    $data=base64_decode($val["FILE_DATA"]);
    if (strlen($data)<1) return VratChybu($session_id,'send_files','Není k dispozici obsah souboru '.$val["FILE_NAME"]);
    if (!$fp=fopen($tmp_soubor,'w')) return VratChybu($session_id,'send_files','Chyba pri ulozeni tmp souboru '.$tmp_soubor);
    fwrite($fp,$data);
    fclose($fp);
    if (JePodepsanyDokument($data, 0)) {
      $GLOBALS['DESCRIPTION'] = 'el. podepsano';
    }
    $tmp_soubor_2=TxtEncodingFromSoap($tmp_soubor);
    //$tmp_soubor_2=$tmp_soubor;
    //echo $tmp_soubor_2; 
    $ret = $uplobj['table']->SaveFileToAgendaRecord($tmp_soubor_2, $dokument_id);
    if ($ret[err_msg]>0) return VratChybu($session_id,'send_files','Chyba pri ulozeni souboru '.$val["FILE_NAME"].': '.$ret[err_msg]);
// if ($ret[err_no]>0) Die('stopm,soubor uy existuje');
    $file_ident=$ret[file_id];
    $text='(SEND_FILES) - k dokumentu ('.$dokument_id.') byl vložen soubor '.$val["FILE_NAME"].' - ID: ('.$file_ident.')';
    WriteLog($software_id,$text,$session_id);
    if ($update) $val['FILE_NAME']=TxtEncoding4Soap($val['FILE_NAME']);
    $file[$counter2][FILE_ID]=$file_ident;
    $file[$counter2][FILE_NAME]=$val["FILE_NAME"];
    $file[$counter2][FILE_DESC]=TxtEncoding4Soap($GLOBALS['DESCRIPTION']);
    $file[$counter2][FILE_SIZE]=' ';
    $file[$counter2][BIND_TYPE]=' ';
    $file[$counter2][FILE_DATA]=' ';
    if (is_file($tmp_soubor)) unlink($tmp_soubor);

    $counter2++;
    
  }

//  print_r($file);
  $text='Operace proběhla v pořádku';
  $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
  $vysledek = array(
    'return'=>new soapval('Result', 'tns:Result', $value),
    'soubory'=>new soapval('soubory', 'tns:soubory',$file),
  );
  return VratVysledek($vysledek);
}


