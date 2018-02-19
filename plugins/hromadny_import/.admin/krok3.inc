<?php
require('tmapy_config.inc');
include_once(FileUp2('.admin/classes/dokument/Rtf.php'));
include_once(FileUp2('.admin/classes/dokument/Docx.php'));
include_once(FileUp2('.admin/classes/dokument/Temp.php'));
include_once(FileUp2('.admin/classes/transformace/Datum.php'));
include_once(FileUp2('.admin/status.inc'));

$sql = 'update ' . $table .' set stav=2,last_date=\''.$LAST_DATE.'\',last_time=\''.$LAST_TIME.'\',last_user_id='.$LAST_USER_ID.' where tid=' . intval($id);
$q->query($sql);

$restart = EedImport::isRestart($id);

$doporucene = $GLOBALS['DOPORUCENE'];
$vlastnich_rukou = $GLOBALS['VLASTNICH_RUKOU'];
//$agenda_dokumentu = $GLOBALS['AGENDA_DOKUMENTU'];
$typ_posty = $GLOBALS['TYP_POSTY'];
$referent = $GLOBALS['REFERENT'];
$vec = $GLOBALS['VEC'];
$skartace = $GLOBALS['SKARTACE'];
$pdf_set = $GLOBALS['PDF'];
$ds = $GLOBALS['DS'];
$nevracet = $GLOBALS['OBALKA_NEVRACET'];
$jen10dni = $GLOBALS['OBALKA_10DNI'];
$poznamka = $GLOBALS['POZNAMKA'];
$odes_typ = $GLOBALS['ODES_TYP'];
$odesl_otocit = $GLOBALS['ODESL_OTOCIT'];


EedImport::glob2db(array('VEC','DOPORUCENE','VLASTNICH_RUKOU','SKARTACE','TYP_POSTY','PDF','DS','DAT_VYP','DAT_DOR','POZNAMKA','ODES_TYP','ODESL_OTOCIT'),$id);

if (!$referent) {
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $GLOBALS['REFERENT'] = $USER_INFO['ID'];
}
$user_obj = LoadClass('EedUser', $referent);
$odbor = $user_obj->VratSpisovyUzelPracovnika($referent);
$so = $user_obj->zarizeni_id;

//echo '<p><span class="caption">'.$GLOBALS['RSTR_IMPORT']['import_prubeh'].'</span></p>';
$log = 'Probíhá import';
ZapisLog($log);
$table = $GLOBALS['PROPERTIES']['AGENDA_TABLE'];
$tid = $id;


if (!$restart) {
  
  $sql = 'DELETE FROM ' . $table .'_POSTA WHERE id_import = ' . $tid;
  $log = 'SQL: ' . $sql;
  ZapisLog($log);
  $q->query($sql);
}

$uplobj = Upload(array(
  'create_only_objects' => true,
  'agenda' => $GLOBALS['PROPERTIES']['AGENDA_IDENT'],
  'noshowheader' => true,
));

$importFiles = array();
$upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);
while (list($key, $val) = each($upload_records)) {
  if (strpos($val['NAME'], 'import_log') === false) {
    $importFiles[] = $val;
  }
}

$filesCount = count($importFiles);
$csv_only = ($filesCount == 1) ? true : false;

$rtf_template = array();
$rtf_template_data = array();
$DOC = array();

if ($filesCount > 0) {
  foreach ($importFiles  as $val) {
    $ext = pathinfo($val['NAME'], PATHINFO_EXTENSION);
    if ($val['TYPEFILE'] == 'text/csv') {
      $datafile = $uplobj['table']->GetUploadFiles($val);
    }
    if ($val['TYPEFILE'] == 'application/rtf') {
      $rtf_template_data[] = $uplobj['table']->GetUploadFiles($val);
      $rtf_template[] = $val['NAME'];
      $DOC[] = "Rtf";
    }
    if (strtolower ($ext) == 'docx') {
      $rtf_template_data[] = $uplobj['table']->GetUploadFiles($val);
      $rtf_template[] = $val['NAME'];
      $DOC[] = "Docx";
    }
  }

  $data = explode(chr(10), $datafile);

  $l = 0;
  $var_array = array();
  $data_array = array();
  foreach($data as $line) {
    if ((strlen($line)>1)&&(substr_count($line,';')<(strlen($line)-1))) {
      $l++;
      $var = false;
      if ($l ==1) $var = true;
          foreach (str_getcsv($line,";") as $cell) {
             if ($var) $var_array[] = $cell; 
             else 
                 $data_array[$l][] = iconv('CP1250', 'UTF-8', $cell);
          }
    }
  }

  $table = $GLOBALS['PROPERTIES']['AGENDA_TABLE'];
  
  if ($restart==false) {
    $sql = 'DELETE FROM ' . $table .'_POSTA WHERE id_import=' . intval($id);
    $log = 'SQL: ' . $sql;
    ZapisLog($log);
    $q->query($sql);
  }
  
  $uplobj2 = Upload(array(
    'create_only_objects' => true,
    'agenda' => 'POSTA',
    'noshowheader'=>true)
      );
   
  //vytvorit docasny adresar, kde se budou vytvaret rtf soubory
  $temp = new Temp($GLOBALS['CONFIG_POSTA']['HLAVNI']['tmp_adresar']);
  
  $rtf = array();
  $path_parts = array();
  
  if (sizeof($DOC)==0) {
    $DOC[] = "Rtf";
  }
  
  for ($ii=0;$ii<sizeof($DOC);$ii++){
    
    //for ($i=0;$i<sizeof($data_array);$i++) {
    
    $rtf[] = new $DOC[$ii]($rtf_template_data[$ii],$var_array);
  
    if ($DOC[$ii]=="Docx") $rtf[$ii]->setEncoding("UTF-8");
    $rtf[$ii]->setDb(new DB_POSTA);
    $path_parts[] = pathinfo($rtf_template[$ii]);
  
    $rtf[$ii]->addVars(array('DOPORUCENE','TYP_POSTY','REFERENT','ODBOR','VEC','SKARTACE','OBALKA_NEVRACET','OBALKA_10DNI','POZNAMKA','ODES_TYP','ODESL_OTOCIT','VLASTNICH_RUKOU'));
     if ($ds==1) {
       $rtf[$ii]->addVars(array('ODESL_DATSCHRANKA'));
       require(FileUp2(".admin/isds_.inc"));
     }
     /*if ($GLOBALS['DAT_VYP']==1)
       $rtf->addVars(array('DATUM_VYPRAVENI'));
     if ($GLOBALS['DAT_DOR']==1)
       $rtf->addVars(array('DATUM_DORUCENI'));*/
     $rtf[$ii]->addVars(array('CISLO_JEDNACI'));
   // }
     
  }
     
   if ($restart==true) {
     $records = EedImport::countDocuments($tid,$table);
     if (($l-1)!= $records) {
       echo '<br /><p class="caption">' . $GLOBALS['RSTR_IMPORT']['import_chybny_pocet_csv'] .$records .'</p>';
       die();
     }
     $eed_import = new EedImport($tid,$table);
   }
       
  $nalezeno_vice_ds_val = "";
   
  //uzamknuti tabulky 
  $q->query("BEGIN WORK");
  $q->query("LOCK TABLE posta IN ROW EXCLUSIVE MODE");
  // pouze zalozeni metadat
  try {
    $pdf = array();
   
    // pouze zalozeni metadat
    $doc_id_array = array();
    $i = 0;
    foreach ($data_array as &$data_item) {
      $nalezeno_vice_ds = false;
      $data_item[] = $doporucene;
      $data_item[] = $typ_posty;
      $data_item[] = $referent;
      $data_item[] = $odbor;
      $data_item[] = $vec;
      $data_item[] = $skartace;
      $data_item[] = $nevracet;
      $data_item[] = $jen10dni;
      $data_item[] = $poznamka;
      $data_item[] = $odes_typ;
      $data_item[] = $odesl_otocit;
      if ($ds!=1) $data_item[] = $vlastnich_rukou;
      
      for ($ii=0;$ii<sizeof($rtf);$ii++)  {
        $rtf[$ii]->setGlobals($data_item);
      }
      
      if ($ds==1) {
        $dbOwnerInfo = array(
          'dbType'=>'FO',
          'pnLastName' => $GLOBALS['ODESL_PRIJMENI'],
          'pnFirstName' => $GLOBALS['ODESL_JMENO'],
          //'biDate' => $GLOBALS['ODESL_DATNAR']
          'biDate' => posta\transformace\Datum::ifDateToUSformat($GLOBALS['ODESL_DATNAR']  )
        );
        if ($GLOBALS[CONFIG_POSTA][DS][ds_cert_id]) $certifikat=VratCestukCertifikatu(0,$GLOBALS[CONFIG_POSTA][DS][ds_cert_id],1); else $certifikat='';
        $schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);
        $hodnoty=$schranka->FindPersonalDataBox($dbOwnerInfo);
        if ((count($hodnoty) == 1)&&!empty($hodnoty))
        {
          $data_item[] = 9;
          $data_item[] = $hodnoty[0]['dbID'];
          $pdf[] = 1;
        }
        elseif (count($hodnoty) > 1) {
          $data_item[] = 9;
          $data_item[] ="";
          $nalezeno_vice_ds = true;
          $pdf[] = 0;
        } else {
          $data_item[] = $vlastnich_rukou;
          $data_item[] ="";
          $pdf[] = 0;
        }
        for ($ii=0;$ii<count($rtf);$ii++)  {
          $rtf[$ii]->setGlobals($data_item);
        }
      } else 
        $pdf[] = $pdf_set;
     // if ($pdf_set) $pdf[sizeof($pdf-1)] = $pdf_set;
       //Run_ vlozeni
       unset($GLOBALS['ID']);
       unset($GLOBALS['PRIVATE']);
       $GLOBALS['ODESLANA_POSTA'] = 't';
       $GLOBALS['SUPERODBOR'] = $so;
       if ($GLOBALS['DAT_VYP']==1)
         $GLOBALS['DATUM_VYPRAVENI'] = date('Y-m-d H:i:s');
         if ($GLOBALS['DAT_DOR']==1)
           $GLOBALS['DATUM_DORUCENI'] = date('Y-m-d H:i:s');
           
       if ($restart)
        $GLOBALS['EDIT_ID'] = $eed_import->getNextId();
       $doc_id = Run_(array("agenda" => "POSTA", "outputtype" => 1 ,"to_history" => false));
             
       if ($nalezeno_vice_ds) $nalezeno_vice_ds_val.=",".$doc_id;
       NastavStatus($doc_id, $user_obj->id);
       $doc_id_array[] = $doc_id;
    }
    //odemknuti tabulky
    $q->query("COMMIT WORK");
    $sql = 'update posta_hromadny_import set zamceno=-1 where tid=' . $tid;
    $q->query($sql);
  
  }
  catch (Exception $e) {
    $q->query("ROLLBACK");
    
  } 
  
  //pouze upload souboru
  
if (!$csv_only) {
  //rtf[$ii][$i] $ii - poradi souboru v dokumentu, $i - poradi dokumentu 
  for ($ii=0;$ii<sizeof($rtf);$ii++) {
    $i = 0;
    foreach ($data_array as &$data_item) {
      $doc_id = $doc_id_array[$i];
      
      $rtf[$ii]->setGlobals($data_item);
      if ($restart&&!$csv_only) {
        $files = EedImport::getFiles($tid,$table);
        //overeni zda se nejedna o stav kdy byla zalozena nejdrive metadata, pak pridana sablona a pri restartu generovan poprve i dokument ze sablony
        $f_index = $i*(sizeof($rtf))+$ii;
        if (isset($files[$f_index])) {
        $GLOBALS['COSTIM']='archiv_a'; //archivuj puvodni
          $GLOBALS['show_typ']=2;
          $GLOBALS['archiv_file_system']=true;
          $GLOBALS['EDIT_ID']=$files[$f_index]['FILEID'];
          $doc_id = $files[$f_index]['ID'];
        } else {
           unset($GLOBALS['EDIT_ID']);
        }
      }
      
      if (!$csv_only) {
        $GLOBALS['DESCRIPTION'] = "Šablona:  ".basename($rtf_template[$ii])." Soubor: ".$doc_id.".".$path_parts[$ii]['extension'];
      
        $cjObj = LoadClass('EedCj', $doc_id_array[$i]);
        $data_item[] = $cjObj->cislo_jednaci;
  
        //nahrazeni promennych v RTF a vytvoreni prislusnych souboru 
       // $dest = $temp->getTempDir()."/".$doc_id.(sizeof($rtf)>1 ? "_".$ii : "").".".$path_parts[$ii]['extension'];
        $dest = $temp->getTempDir()."/".$doc_id."_".$path_parts[$ii]['basename'];
        $rtf[$ii]->process($dest,$data_item,$doc_id);          
      
        //upload rtf k prislusne polozce 
        $ret = $uplobj2['table']->SaveFileToAgendaRecord($dest, $doc_id);
  /*      if ($pdf[$i]==1) {
          UNSET($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['ONLY_FILE_TYPES']);  
          $eed_obj = LoadClass('EedUpload', $doc_id);
          $eed_obj->ConvertFile(basename($dest));
        }*/
      }
 /*     if (($restart==false)&&($ii==0)) {
        $sql = 'INSERT INTO ' . $table .'_POSTA VALUES(' . $tid.','.$doc_id.')';
        $log = 'SQL: ' . $sql;
        ZapisLog($log);
        $q->query($sql);
      }*/
      $i++;
    }
  }
  
    
  //konverze do PDF
  for ($ii=0;$ii<sizeof($rtf);$ii++) {
    $i = 0;
    foreach ($data_array as &$data_item) {
      $doc_id = $doc_id_array[$i];
      if (!$csv_only) {
        if ($pdf[$i]==1) {
          $dest = $temp->getTempDir()."/".$doc_id."_".$path_parts[$ii]['basename'];
          UNSET($GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['ONLY_FILE_TYPES']);
          $eed_obj = LoadClass('EedUpload', $doc_id);
          $c = 0;
          $pdf_file = false;
          while ($pdf_file!==true) {
            $pdf_file = $eed_obj->ConvertFile(basename($dest));;
            sleep(1);
            $c++;
            if ($c>2) $pdf_file = true;
          }
        }
      }
      if (($restart==false)&&($ii==0)) {
        $sql = 'INSERT INTO ' . $table .'_POSTA VALUES(' . $tid.','.$doc_id.')';
        $log = 'SQL: ' . $sql;
        ZapisLog($log);
        $q->query($sql);
      }
      $i++;
    }
  }
  
  
  
}
  
  
  
  $temp->delTempDir();
  
}
$csv_only = ($filesCount == 1) ? true : false;

$stav = ($csv_only) ? 5 : 3;
    
 $sql = 'update ' . $table .' set stav='.$stav.',last_date=\''.$LAST_DATE.'\',last_time=\''.$LAST_TIME.'\',last_user_id='.$LAST_USER_ID.' where tid=' . intval($tid);
 $log = 'SQL: ' . $sql;
 ZapisLog($log);
 $q->query($sql);
/*echo '<tr><td align="center">';
echo '<input type="button" class="button btn" onclick="window.location.href=\'import2.php?id='.$tid.'&dalsi_krok=1\'" value="' . $GLOBALS['RSTR_IMPORT']['import_pokracovat'] . '4 "> ';
echo '</td></tr>';
echo '</table>';*/

$csv_only_link = ($csv_only) ? '&csv_only=1' : '';
//$nalezeno_vice_ds_val = ",111,222,333";
$ds_link = (($ds==1)&&($nalezeno_vice_ds_val!='')) ? '&DS='.$nalezeno_vice_ds_val : "";
if ($csv_only) {
 ?>
<script language="JavaScript" type="text/javascript">
  window.location.href='import2.php?id=<?php echo $tid;?>&restart=6<?php echo $csv_only_link;?>';
</script>
<?php 
  
} else {
 
?>
<script language="JavaScript" type="text/javascript">
  window.location.href='import2.php?id=<?php echo $tid;?>&dalsi_krok=1<?php echo $csv_only_link.$ds_link;?>';
</script>
<?php 
}


