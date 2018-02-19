<?php
//include(FileUp2(".admin/form_.inc"));
function onlineEdit($uplo,$ext,$directory) {
  /*$url = "";
   if ($GLOBALS['CONFIG']['USE_CUL_ONLINE_EDIT'] && ($ext=="docx")) {
   $url = $upl['table']->stg_obj->onlineEdit($directory);
   header('Location: '.$url);
   die();
   }*/ 
  $url = "";
   if ($GLOBALS['CONFIG']['USE_CUL_ONLINE_EDIT'] && ($ext=="docx")) {
   $url = $uplo->stg_obj->onlineEdit($directory);
   header('Location: '.$url);
   die();
   }
}

function getUplDir($upload_records,$file) {
  $directory = false;
  foreach ($upload_records as $upload_record) {
    $up_name = pathinfo($upload_record["NAME"], PATHINFO_FILENAME);
    $file = pathinfo($file, PATHINFO_FILENAME);
    if ($up_name == $file) {
       $directory = $upload_record["DIRECTORY"];
    }
  }
  return $directory;
}


If ($sablona=='odpoved')
{
  require_once(FileUp2('.admin/upload_.inc'));

//ulozime pripadne posledni pozici obalky
  If ($GLOBALS["CONFIG"]["POUZIVAT_COOKIES"]) setcookie("TWIST_POSTA_VybranaSablona",$id_sablony,time()+86400*300, "/"); //30 dnu
  
  //$nazev='odpoved_'.$w->Record["ID"];
  
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA_SABLONY','noshowheader'=>true));
  $cesta=$uplobj['table']->main_dir;
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id_sablony);
  $upload_records=end($upload_records);
  $sablona=$uplobj['table']->GetUploadFiles($upload_records); 
  $nazev=current(explode(".", $upload_records['NAME'])).'_'.$w->Record["ID"];
  
  //overeni, zda jiz upload obsahuje vygenerovanou sablonu
  $vygenerovan = false;
  $upl=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $cesta=$upl['table']->main_dir;
  $upload_records2 = $upl['table']->GetRecordsUploadForAgenda($w->Record["ID"]);
  $directory = getUplDir($upload_records2,$nazev);
  if ($directory!=false) $vygenerovan = true;
  
/*  foreach ($upload_records as $upload_record) {
    $up_name = pathinfo($upload_record["NAME"], PATHINFO_FILENAME);
    if ($up_name == $nazev) {
      $vygenerovan = true;
      $directory = $upload_record["DIRECTORY"];
    }
  }*/
  
  

 /* $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA_SABLONY','noshowheader'=>true));
  $cesta=$uplobj['table']->main_dir;
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id_sablony);   
  $upload_records=end($upload_records);
  $sablona=$uplobj['table']->GetUploadFiles($upload_records);*/ 
  
  $ext = pathinfo($upload_records["NAME"], PATHINFO_EXTENSION);
  $nazev.=".".$ext;
  
  if ($ext == "docx") {
    include_once(FileUp2('.admin/classes/dokument/Docx.php'));
    $docx = new Docx($sablona);
    $docx->setDocumentPath($upload_records["NAME"]);
    $sablona = $docx->getFileContent();
  }

/*  //najdeme cestu z TOHUova uploadu, ktera to je sablona...
  $sql="select * from upload_files where record_id=$id_sablony and agenda_ident='POSTA_SABLONY' ORDER BY ID DESC";
  //echo $sql;
  $w->query($sql);
  $w->Next_Record();


  //cesta k rootu souboru se sablonama ...      
  $cesta=$SERVER_CONFIG["AGENDA_PATH"]["UPLOAD_SERVER_DIR"];
  //+vlastni soubor
  $cesta=$GLOBALS["TMAPY_DIR"]."/data".$w->Record["DIRECTORY"].$w->Record["NAME"];
  $fn = $cesta;
  $fp = fopen ($fn, "r");
  $sablona = fread ($fp, filesize ($fn));
  fclose ($fp);
*/
  $z=array("%CAROVY_KOD%","%CISLO_SPISU%","%DATUM_PRIJETI%","%ODBOR_REFERENTA%","%ADRESA_OSLOVENI%","%ADRESA_ODESILATELE%","%ADRESA_JMENO%","%ADRESA_ULICE%","%ADRESA_MESTO%",
  "%ADRESA_ODD%","%ADRESA_KONTOSOBA%","%CISLO_JEDNACI%","%UREDNIK_JMENO%","%UREDNIK_TELEFON%","%DNESNI_DATUM%","%VEC_DOPISU%","%UREDNIK_EMAIL%","%JEJICH_CJ%","%JEJICH_CJ_DNE%","%UREDNIK_FAX%","%ROZDELOVNIK%","%UREDNIK_JEN_PRIJMENI%",
  "%SPIS_ZNAK%","%DATUM_NAROZENI%","%SU_ADRESA%", "%SU_TELEFON%","%SU_MOBIL%","%SU_EMAIL%","%AGENDA_DOKUMENTU%","%ODESL_PRIJMENI_FIRMA%","%SU_WEB%","%DEN_PRIJETI%");
  
  /*var_dump($z);
  var_dump($default_from);*/
  
  $z = array_merge($z,$default_from);

  $jejich_cj_dne = str_replace('&nbsp;','', $jejich_cj_dne);
  $today = Date('d.m.Y');
  $skartace_kod = $skartace[kod];
  
  
  if ($ext!="docx") {
    $barcode = TxtEncodingToWin($barcode);
    $cislo_spisu = TxtEncodingToWin($cislo_spisu);
    $datum_prijeti = TxtEncodingToWin($datum_prijeti);
    $odbor = TxtEncodingToWin($odbor);
    $ADRESA_OSLOVENI = TxtEncodingToWin($ADRESA_OSLOVENI);
    $ODESILATEL = TxtEncodingToWin($ODESILATEL);
    $ADRESA_JMENO = TxtEncodingToWin($ADRESA_JMENO);
    $ADRESA_ULICE = TxtEncodingToWin($ADRESA_ULICE);
    $ADRESA_MESTO = TxtEncodingToWin($ADRESA_MESTO);
    $ADRESA_ODD = TxtEncodingToWin($ADRESA_ODD);
    $ADRESA_KONTOSOBA = TxtEncodingToWin($ADRESA_KONTOSOBA);
    $c_jednaci = TxtEncodingToWin($c_jednaci);
    $REFERENT_JMENO = TxtEncodingToWin($REFERENT_JMENO);
    $REFERENT_TELEFON = TxtEncodingToWin($REFERENT_TELEFON);
    $vec = TxtEncodingToWin($vec);
    $urednik_email = TxtEncodingToWin($urednik_email);
    $jejich_cj = TxtEncodingToWin($jejich_cj);
    $urednik_fax = TxtEncodingToWin($urednik_fax);
    $dalsi_osoby = TxtEncodingToWin($dalsi_osoby);
    $REFERENT_JEN_PRIJMENI = TxtEncodingToWin($REFERENT_JEN_PRIJMENI);
    $jejich_cj_dne = TxtEncodingToWin($jejich_cj_dne);
    $datum_narozeni = TxtEncodingToWin($datum_narozeni);
    $today = TxtEncodingToWin($today);
    $su_adresa = TxtEncodingToWin($su_adresa);
    $su_telefon= TxtEncodingToWin($su_telefon);
    $su_mobil = TxtEncodingToWin($su_mobil);
    $su_mail = TxtEncodingToWin($su_mail);
    $su_web = TxtEncodingToWin($su_web);    
    $skartace_kod = TxtEncodingToWin($skartace_kod);
  } else {
    $ODESILATEL = str_replace('\\par','<w:br/>', $ODESILATEL);
  }

  $na=array($barcode,$cislo_spisu,$datum_prijeti,$odbor,$ADRESA_OSLOVENI,$ODESILATEL,$ADRESA_JMENO,$ADRESA_ULICE,$ADRESA_MESTO,
  $ADRESA_ODD,$ADRESA_KONTOSOBA,$c_jednaci,$REFERENT_JMENO,$REFERENT_TELEFON,$today,$vec,$urednik_email,$jejich_cj,$jejich_cj_dne,$urednik_fax,
    $dalsi_osoby, $REFERENT_JEN_PRIJMENI, $skartace_kod,$datum_narozeni,$su_adresa, $su_telefon, $su_mobil, $su_mail,$agenda_dokumentu,$odesl_firma,$su_web, $den_prijeti );
  
 
  $na = array_merge($na,$default_to);
  
  $vysledny=Str_replace($z,$na,$sablona);

  
  if ($GLOBALS['save_to_upload']==1) {
    $id_posta = $GLOBALS['ID'];    
    if ($vygenerovan) {     
      onlineEdit($upl['table'],$ext,$directory);
      echo "<script>parent.NewWindowSablona('./confirm.php?msg=".'ok&RECORD_ID='.$id_posta."');</script>";
    } else {
    
      if ($ext == "docx") {
//        require(GetAgendaPath('POSTA',false,false).'/lib/tcpdf/tcpdf_barcodes_1d.php');
//         $barcodeobj = new TCPDFBarcode($podaci_cislo, 'C128');
//         $image = $barcodeobj->getBarcodePngData(6,3);
//        $image = Code39Pic_bin($podaci_cislo);
        $image = Code128Pic($podaci_cislo);

        $docx->replaceMediaFile('barcode.png',$image);
        $docx->replaceVars($z,$na);
        //$vysledny = $docx->setFileContent($vysledny);
        $vysledny = $docx->returnCreatedDoc();
     }
     include_once(FileUp2(".admin/classes/EedUpload.inc"));
      $eu = new EedUpload($GLOBALS['ID']);
      $res = $eu->saveFile($nazev,$vysledny,$USER_INFO['ID']);
      $eu->refreshUploadRecords();
      $directory = getUplDir($eu->uplobj_records,$nazev);
      if (($res['err_no'] == 0)||($res['err_no'] == 1)){
        onlineEdit($upl['table'],$ext,$directory);
        //upload
        echo "<script>parent.NewWindowSablona('./confirm.php?msg=".'ok&RECORD_ID='.$id_posta."');</script>";        
      } else {
        //vyskakovaci okno upload failed
        echo "<script>parent.NewWindowSablona('./confirm.php?msg=".'err'."');</script>";
      }
    }
    
  } else {
    if ($ext = "docx") {
//        require(GetAgendaPath('POSTA',false,false).'/lib/tcpdf/tcpdf_barcodes_1d.php');
//         $barcodeobj = new TCPDFBarcode($podaci_cislo, 'C128');
//         $image = $barcodeobj->getBarcodePngData(6,3);
//        $image = Code39Pic_bin($podaci_cislo);
        $image = Code128Pic($podaci_cislo);
        $docx->replaceMediaFile('barcode.png',$image);
        $docx->replaceVars($z,$na);
        //$vysledny = $docx->setFileContent($vysledny);
        $vysledny = $docx->returnCreatedDoc();
      $ext = "msword";
    }
    
    Header("Content-Type: application/".$ext);
    Header("Content-Disposition: attachment;filename=$nazev");

    Header("Pragma: cache");
    Header("Cache-Control: public");

    echo $vysledny;
  }
}

