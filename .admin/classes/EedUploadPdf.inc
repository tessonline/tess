<?php
require_once ('EedUpload.inc');


class EedUploadPdf extends EedUpload {
  var $pdfContent;
  
  public $pem;
  public $signature;
  public $signatureExt; // signature with "<" and ">"
  public $signatureBin;
  
  public function EedUploadPdf($record_id) {
    parent::EedUpload($record_id);
  }
  
  public function readPDF($content) {
    
    /*
     * To extract data and signature, you can use numbers in /ByteRange field of PDF.
     * It has 4 numbers as /ByteRange[a b c d]. The signature is from b(th) byte to c(th)
     * byte and remaining is data. In PHP, you can use stream_get_contents() function
     * to get content by stream.
     */
    
    $parse = explode('endobj', $content);
    foreach($parse as $obj) {
      if (strpos($obj, '/Sig')) {
        $start = strpos($obj, '/Contents');
        if ($start>0) {
          $start = strpos($obj, '<', $start)+1;
    //      $konec = strpos($obj,'000', $start)-3;
          $konec = strpos($obj,'>', $start);
          $cert = substr($obj, $start, ($konec-$start));
        }
      }
    }
    
    $this->signature = $cert; //bytes from /ByteRange[a b c d] "b-to-c"
    $this->signatureExt = '<' . $cert . '>'; //bytes from /ByteRange[a b c d] "b-to-c"
    //var_dump(strlen($cert));die;
    $cert_uprav = pack('H*', $cert);

    $this->signatureBin = $cert_uprav; 
//     $cert_uprav = unpack('H*', $cert);
//     $cert_uprav = pack('H*', $cert);
// var_dump($cert_uprav);die;
//     $this->pdfContent = trim($cert_uprav);
    $this->pdfContent = $cert_uprav;
  }
  
  public function isPDF($name) {
    if (strpos(strtolower($name), '.pdf')) return true;
    else return false;

  }
  public function isTimeStampInPDF($content) {
    $this->readPDF($content);
    if (strpos(strtolower($this->pdfContent), 'time stamping authorit')) return true;
    return false;
  }

  public function getCertFromPDF($content) {
    if (!$this->pdfContent) $this->readPDF($content);
    $id = UniqId();
    $pemID = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar] . $id . '.pem';
    $pkcs7ID = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar] . $id . '.pkcs7';
    $cert_uprav = base64_encode($this->pdfContent);
    $begin_pem = "-----BEGIN CERTIFICATE-----\n";
    $end_pem = "-----END CERTIFICATE----- ";


    $cert2 = '';
    for($a=1; $a<=strlen($cert_uprav); $a++) {
      $cert2 .= substr($cert_uprav, $a-1, 1);
      if ($a % 64 == 0) {
        $cert2 .= "\n";
      }
    }
    $cert = trim($begin_pem . $cert2 . "\n" . $end_pem);
//     var_dump($cert);die;
    file_put_contents($pemID, $cert);
    $this->pem = $cert;
//     $fp = fopen($pkcs7ID,'w');
//     fwrite($fp, $cert);
//     fclose($fp);

    $cmd = 'openssl pkcs7 -print_certs -in '.$pemID.' -out '.$pkcs7ID;
//     $cmd = 'openssl pkcs7 -print_certs -in '.$pkcs7ID.' -out '.$pkcs7ID . "-2";
    exec($cmd);

    $cert = file_get_contents($pkcs7ID);
//     $fp = fopen($pkcs7ID, 'r');
//     $cert = fread($fp, filesize($pkcs7ID));
//     fclose($fp);
//     var_dump($pkcs7ID);
//     var_dump($pemID);
    if(file_exists($pkcs7ID)){
      unlink($pkcs7ID);
    }
    if(file_exists($pemID)){
      unlink($pemID);
    }

    return $cert;
  }


  function testPDF() {
    if (!$GLOBALS['CONFIG']['ELEKTRONICKA_ARCHIVACE']) return false;
    $ret = array();
    foreach($this->uplobj_records as $file) {
      $content = $this->getContent($file);
      //testneme, jestli obsahuje casove razitko
      if ($this->isTimeStampInPDF($content)) {
        if (!$this->services602) $this->set602_services();
        try {
          $temp = $this->services602->ltvAnalyze($content,  $file['ID'], $file['RECORD_ID'], 'POSTA');
          $ret[$file['ID']] = array('FILE_ID' => $file['ID'], 'DOC_ID' => $file['RECORD_ID'], 'NAME' => $file['NAME'], 'EXPIRATION' => $temp[2]);
        }
        catch (Exception $e) {
          echo 'nepovedla se analyza souboru ' . $file['NAME'] . ' (' . $file['FILE_ID'] . ') - chyba: ' . $e;
        }
      }
    }
    return $ret;

  }

  function registerPDF() {
    if (!$GLOBALS['CONFIG']['ELEKTRONICKA_ARCHIVACE']) return false;
    $ret = array();
    foreach($this->uplobj_records as $file) {
      $content = $this->getContent($file);
      //testneme, jestli obsahuje casove razitko
      if ($this->isTimeStampInPDF($content)) {
        if (!$this->services602) $this->set602_services();
        try {
          $temp = $this->services602->ltvRegister($content,  $file['ID'], $file['RECORD_ID'], 'POSTA');
          $data_save = base64_decode($temp[3]);

          //ulozime soubor s novy m casovym razitkem
          $tmp_soubor_x = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$file['NAME'];
          $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$file['NAME'];

          if (is_file($tmp_soubor_x)) unlink($tmp_soubor_x);
          if (strlen($data_save)<1) echo 'Není k dispozici obsah souboru ';
          if (!$fp = fopen($tmp_soubor_x, 'w')) echo 'Chyba pri ulozeni tmp souboru ' . $tmp_soubor;
          fwrite($fp, $data_save);
          fclose($fp);
          chmod($tmp_soubor_x, 0777);

          $GLOBALS['ID'] = $file[ID];
          $GLOBALS['FILE_ID'] = $file[ID];
          $GLOBALS['COSTIM'] = 'archiv_a'; //archivuj puvodni
          $GLOBALS['show_typ']=2;
          $GLOBALS['EDIT_ID'] = $file[ID];
          $GLOBALS['UPL_FILE'] = $res[0];
          $GLOBALS['LAST_DATE'] = Date('Y-m-d');
          $GLOBALS['OWNER_ID'] = $file[LAST_USER_ID];

          if (!$this->uplobj) {
            $this->uplobj = Upload(array(
                      'create_only_objects' => true,
                      'agenda' => 'POSTA',
                      'noshowheader'=>true)
                    );          }
          $ret = $this->uplobj['table']->SaveFileToAgendaRecord($tmp_soubor, $file['RECORD_ID']);
//          print_r($ret);
//          if ($ret['err_msg']<>'') return $ret['err_msg'];

          $ret[$file['ID']] = array('FILE_ID' => $file['ID'], 'DOC_ID' => $file['RECORD_ID'], 'NAME' => $file['NAME'], 'EXPIRATION' => $temp[2]);
        }
        catch (Exception $e) {
          echo 'nepovedla se registrace souboru ' . $file['NAME'] . ' (' . $file['FILE_ID'] . ') - chyba: ' . $e;
        }
      }
    }
    return $ret;

  }

  function UpdatePDF ($file) {
    if (!$GLOBALS['CONFIG']['ELEKTRONICKA_ARCHIVACE']) return false;
    $ret = array();
    $content = $this->getContent($file);
      //testneme, jestli obsahuje casove razitko
    if (!$this->services602) $this->set602_services();
    try {
      $temp = $this->services602->ltvUpdate($content,  $file['ID'], $file['RECORD_ID'], 'POSTA');
      $data_save = base64_decode($temp[3]);

      //ulozime soubor s novy m casovym razitkem
      $tmp_soubor_x = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$file['NAME'];
      $tmp_soubor = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar].$file['NAME'];

      if (is_file($tmp_soubor_x)) unlink($tmp_soubor_x);
      if (strlen($data_save)<1) echo 'Není k dispozici obsah souboru ';
      if (!$fp = fopen($tmp_soubor_x, 'w')) echo 'Chyba pri ulozeni tmp souboru ' . $tmp_soubor;
      fwrite($fp, $data_save);
      fclose($fp);
      chmod($tmp_soubor_x, 0777);

      $GLOBALS['ID'] = $file[ID];
      $GLOBALS['FILE_ID'] = $file[ID];
      $GLOBALS['COSTIM'] = 'archiv_a'; //archivuj puvodni
      $GLOBALS['show_typ']=2;
      $GLOBALS['EDIT_ID'] = $file[ID];
      $GLOBALS['UPL_FILE'] = $res[0];
      $GLOBALS['LAST_DATE'] = Date('Y-m-d');
      $GLOBALS['OWNER_ID'] = $file[LAST_USER_ID];

      if (!$this->uplobj) {
        $this->uplobj = Upload(array(
                  'create_only_objects' => true,
                  'agenda' => 'POSTA',
                  'noshowheader'=>true)
                );          }
      $ret = $this->uplobj['table']->SaveFileToAgendaRecord($tmp_soubor, $file['RECORD_ID']);
//          print_r($ret);
//          if ($ret['err_msg']<>'') return $ret['err_msg'];

      $ret[$file['ID']] = array('FILE_ID' => $file['ID'], 'DOC_ID' => $file['RECORD_ID'], 'NAME' => $file['NAME'], 'EXPIRATION' => $temp[2]);
    }
    catch (Exception $e) {
      echo 'nepovedl se update souboru ' . $file['NAME'] . ' (' . $file['FILE_ID'] . ') - chyba: ' . $e;
    }
    return $ret;

  }

  function unregisterPDF() {
    if (!$GLOBALS['CONFIG']['ELEKTRONICKA_ARCHIVACE']) return false;
    $ret = array();
    if (!$this->services602) $this->set602_services();
    foreach($this->uplobj_records as $file) {
      $temp = $this->services602->ltvUnregister($file['ID']);
    }
    return $ret;

  }

}
