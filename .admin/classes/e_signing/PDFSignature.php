<?php

/**
 * Library for verification of signature in a PDF document.
 *
 * @author mabu
 * @version 1.4.0
 */
class PDFSignature{
  const MAGIC = 38;
  const FILTER_PKKLITE = "Adobe.PPKLite";
  const FILTER_PPKMS = "Adobe.PPKMS";
  const SUBFILTER_PKCS7_DETACHED = "adbe.pkcs7.detached";
  const SUBFILTER_PKCS7_SHA1 = "adbe.pkcs7.sha1";
  const ENABLE_CLEANING = true;

  private $tmpDir;

  /**
   * Constructor
   *
   * @param string $tmpDir
   * @throws \Exception
   */
  public function __construct($tmpDir){
  	$tmpDir = '/tmp/';
    $this->setTmpDir($tmpDir);
  }

  /**
   * Set temporary directory.
   *
   * @param string $tmpDir
   * @throws \Exception
   */
  public function setTmpDir($tmpDir){
    if (! file_exists($tmpDir) || ! is_writable($tmpDir)){
      throw new Exception("Tmp dir does not exist or is not writable.");
    }

    $this->tmpDir = $tmpDir;
  }

  /**
   * Verify a signature of pdf file by given file name.
   *
   * @param string $fileName
   *          file name of pdf to be verified
   * @throws \Exception
   * @return array
   */
  public function verifyFile($fileName){
    if (empty($fileName)){
      throw new Exception("Filename can not be empty.");
    }
    return $this->verify($fileName, null);
  }

  /**
   * Verify a signature of pdf file in loaded string.
   *
   * @param string $fileContent
   *          file content of pdf to be verified
   * @throws \Exception
   * @return array
   */
  public function verifyString($fileContent){
    if (empty($fileContent)){
      throw new Exception("Filecontent can not be empty.");
    }
    return $this->verify(null, $fileContent);
  }

  /**
   * Verify a signature in pdf file.
   *
   * @param string $fileName
   *          file name of pdf to be verified
   * @param string $fileContent
   *          file content of pdf to be verified
   * @throws \Exception
   * @return array
   */
  private function verify($fileName = "", $fileContent = ""){
    if (empty($fileName) && empty($fileContent)){
      throw new Exception("Filename and fileContent can not be empty simultaneously.");
    }
    if (!empty($fileName) && !empty($fileContent)){
      throw new Exception("Filename and fileContent can not be passed simultaneously.");
    }
    if (!empty($fileName) && !file_exists($fileName)){
      throw new Exception("File with given filename does not exist.");
    }
    if (! file_exists($this->tmpDir) || ! is_writable($this->tmpDir)){
      throw new Exception("Tmp dir does not exist or is not writable.");
    }

    $randomId = uniqid();
    if (!empty($fileContent)){
      $fileName = sprintf("%s/%s.pdf", $this->tmpDir, $randomId);
      file_put_contents($fileName, $fileContent);
    }

    $file = file_get_contents($fileName);

    $filters = $this->getFilters($file);
    if (empty($filters)){
      throw new Exception("Filter section in given file was not found.");
    }

    $byteRange = $this->getByteRange($file);
    if (empty($byteRange)){
      throw new Exception("ByteRange section in given file was not found.");
    }

    $binarySignature = $this->getBinarySignature($file);
    if (empty($binarySignature)){
      throw new Exception("Signature section in given file was not found.");
    }

    $extFile = sprintf("%s/%s.ext.pdf", $this->tmpDir, $randomId);
    if (! $this->removeSigatureFromPdf($fileName, $extFile, $byteRange)){
      throw new Exception("Extracting a signature from given file was not successfull.");
    }

    $certPem = sprintf("%s/%s.pem", $this->tmpDir, $randomId);
    $certPkcs7 = sprintf("%s/%s.pkcs7", $this->tmpDir, $randomId);
    if (! $this->createPKCS7FromSignature($binarySignature, $certPem, $certPkcs7)){
      throw new Exception("Creating a certificate from signature was not successfull.");
    }

    $certDer = sprintf("%s/%s.der", $this->tmpDir, $randomId);
    if (! $this->convertPKCS7ToDER($certPkcs7, $certDer)){
      throw new Exception("Conversion of a certificate from PKCS7 to DER was not successfull.");
    }

    $countCertsSignature = $this->convertPKCS7ToPEM($certPkcs7, $certPem);
    if ($countCertsSignature <= 0){
      throw new Exception("Conversion of a certificate from PKCS7 to PEM was not successfull.");
    }

//    if($countCertsSignature>1) $countCertsSignature = 1; //onma, je problem s vice certifikaty, v PDF je vetsinou hned prvni soukromy klic
    for ($pocet=0; $pocet<$countCertsSignature; $pocet++ ) {
      $parsedCert = $this->parseCert(sprintf("%s.%d", $certPem, $pocet));
      $cislo = $parsedCert['subject']['serial'];
      if ($cislo<>'') $pocet = 999999; //vyskocime
    }
//    $parsedCert = $this->parseCert(sprintf("%s.%d", $certPem, $countCertsSignature - 1));


    $digest = sprintf("%s/%s.dig.bin", $this->tmpDir, $randomId);
    $digests = $this->extractSignedDigest($certDer, $digest);
    if (empty($digests) || (empty($digests["rsaEncoded"]) && empty($digests["messageDigest"]) && empty($digests["PKCS7Data"]))){
      throw new Exception("Extracting of a signed digest from certificate was not successfull.");
    }

    $publicKey = sprintf("%s/%s.pubkey.pem", $this->tmpDir, $randomId);

    $fileHashes = array(
      "sha256" => hash_file("sha256", $extFile),
      "sha1" => hash_file("sha1", $extFile),
      "md5" => hash_file("md5", $extFile)
    );
    $signedHashes = array();

    if(!empty($digests["rsaEncoded"])){
      if (! $this->createPublicKeyFromPEM($certPem, $publicKey)){
        throw new Exception("Creating of a public key from certificate was not successfull.");
      }

      foreach($digests["rsaEncoded"] as $dg){
        if(!empty($dg)){
          $decDigest = sprintf("%s.dec", $dg);
          if (! $this->decryptBinaryDigest($dg, $decDigest, $publicKey)){
            throw new Exception("Decryption of a signed digest from certificate was not successfull.");
          }
          if(file_exists($decDigest)){
            $signedHashes[] = strtolower(substr(bin2hex(file_get_contents($decDigest)), self::MAGIC));
          }
        }
      }
    }

    if(!empty($digests["messageDigest"])){
      foreach($digests["messageDigest"] as $md){
        $signedHashes[] = strtolower($md);
      }
    }

    if(!empty($digests["PKCS7Data"])){
      foreach($digests["PKCS7Data"] as $md){
        $signedHashes[] = strtolower($md);
      }
    }

    if(self::ENABLE_CLEANING){
      $this->rm($extFile);
      $this->rm($certPem);
      $this->rm($certPkcs7);
      $this->rm($certDer);
      $this->rm($publicKey);
      $this->rm($digest);
      if($countCertsSignature > 0){
        for($i = 0; $i < $countCertsSignature; $i++){
          $this->rm(sprintf("%s.%d", $certPem, $i));
        }
      }
      if(!empty($digests["rsaEncoded"])){
        foreach($digests["rsaEncoded"] as $rsa){
          $this->rm(sprintf("%s", $rsa));
          $this->rm(sprintf("%s.dec", $rsa));
        }
      }
      if(!empty($fileContent)){
        $this->rm($fileName);
      }
    }

    foreach ($fileHashes as $algo => $hash) {
      if(in_array($hash, $signedHashes)){
        $r = array(
          "result" => true,
          "alg" => $algo,
          "hash" => $hash
        );
        return array_merge($r, $parsedCert);
      }
    }

    return array(
      "result" => false,
      "fileHashes" => $fileHashes,
      "signedHashes" => $signedHashes
    );
  }

  /**
   * @deprecated
   */
  private function getMessageDigest($subFilter, $pdfVersion){
    throw new Exception("Method is not implemented yet.");
  }

  /**
   * Extract a version from pdf file.
   *
   * @param string $file
   * @throws \Exception
   * @return string
   */
  private function getPDFVersion($file){
    if (empty($file)){
      throw new Exception("Given param FILE can not be empty.");
    }

    $r = null;
    if (preg_match("/^\%\s*PDF-(\d+\.\d+)\s*\%/", $file, $matches) === 1){
      $r = $matches[1];
    }
    return $r;
  }

  /**
   * Extract a signature filters from pdf file.
   *
   * @param string $file
   * @throws \Exception
   * @return string
   */
  private function getFilters($file){
    if (empty($file)){
      throw new Exception("Given param FILE can not be empty.");
    }

    $r = array();

    $parse = explode('endobj', $file);
    foreach ($parse as $obj){
      // search for /Sig object
      if (strpos($obj, '/Sig')){

        // search for /Filter
        if (strpos($obj, '/Filter') && preg_match("/\/Filter\s*\/([a-zA-Z0-9\.]+)/", $obj, $matches) === 1){
          $r["filter"] = $matches[1];
        }

        // search for /SubFilter
        if (strpos($obj, '/SubFilter') && preg_match("/\/SubFilter\s*\/([a-zA-Z0-9\.]+)/", $obj, $matches) === 1){
          $r["subFilter"] = $matches[1];
        }
      }
    }

    return $r;
  }

  /**
   * Get ByteRange field from pdf file.
   *
   * @param string $file
   * @throws \Exception
   * @return array
   */
  private function getByteRange($file){
    if (empty($file)){
      throw new Exception("Given param FILE can not be empty.");
    }

    $r = array();

    $parse = explode('endobj', $file);
    foreach ($parse as $obj){
      // search for /Sig object
      if (strpos($obj, '/Sig')){

        // search for /ByteRange
        if (strpos($obj, '/ByteRange') && preg_match("/\/ByteRange\s*\[\s*(\d+)\s*(\d+)\s*(\d+)\s*(\d+)\s*\]/", $obj, $matches) === 1){
          $r[0] = intval($matches[1]);
          $r[1] = intval($matches[2]);
          $r[2] = intval($matches[3]);
          $r[3] = intval($matches[4]);
        }
      }
    }

    return $r;
  }

  /**
   * Extract a signature contents from pdf file.
   *
   * @param string $file
   * @throws \Exception
   * @return string
   */
  private function getBinarySignature($file){
    if (empty($file)){
      throw new Exception("Given param FILE can not be empty.");
    }

    $r = null;

    $parse = explode('endobj', $file);
    foreach ($parse as $obj){
      // search for /Sig object
      if (strpos($obj, '/Sig')){

        // search for /Contents
        $start = strpos($obj, '/Contents');
        if ($start > 0){
          $start = strpos($obj, '<', $start) + 1;
          $end = strpos($obj, '>', $start);
          $content = substr($obj, $start, ($end - $start));
          $r = pack('H*', $content);
        }
      }
    }

    return $r;
  }

  /**
   * Create PKCS#7 object from extracted signature content.
   *
   * @param string $binarySignature
   * @param string $pemFileName
   * @param string $pkcs7FileName
   * @throws \Exception
   * @return boolean
   */
  private function createPKCS7FromSignature($binarySignature, $pemFileName, $pkcs7FileName){
    if (empty($binarySignature)){
      throw new Exception("Given param BINARYSIGNATURE can not be empty.");
    }
    if (empty($pemFileName)){
      throw new Exception("Given param PEMFILENAME can not be empty.");
    }
    if (empty($pkcs7FileName)){
      throw new Exception("Given param PKCS7FILENAME can not be empty.");
    }
    $this->rm($pemFileName);

    $signature64 = base64_encode($binarySignature);
    $beginPem = "-----BEGIN CERTIFICATE-----\n";
    $endPem = "-----END CERTIFICATE----- ";

    $certificate = "";
    $lastNewLine = false;
    for($a = 1; $a <= strlen($signature64); $a ++){
      $lastNewLine = false;
      $certificate .= substr($signature64, $a - 1, 1);
      if ($a % 64 == 0){
        $certificate .= "\n";
        $lastNewLine = true;
      }
    }
    $certificate = sprintf("%s%s%s%s", $beginPem, $certificate, ($lastNewLine === false ? "\n" : ""), $endPem);
    file_put_contents($pemFileName, $certificate);

    $cmd = sprintf("openssl pkcs7 -in %s -out %s", $pemFileName, $pkcs7FileName);
    exec($cmd);

    return true;
  }

  /**
   * Convert PKCS#7 to DER.
   *
   * @param string $pkcs7FileName
   * @param string $derFileName
   * @throws \Exception
   * @return boolean
   */
  private function convertPKCS7ToDER($pkcs7FileName, $derFileName){
    if (empty($pkcs7FileName)){
      throw new Exception("Given param PKCS7FILENAME can not be empty.");
    }
    if (empty($derFileName)){
      throw new Exception("Given param DERFILENAME can not be empty.");
    }

    $cmd = sprintf("openssl pkcs7 -in %s -out %s -outform DER", $pkcs7FileName, $derFileName);
    exec($cmd);

    return true;
  }

  /**
   * Convert PKCS#7 to PEM.
   *
   * @param string $pkcs7FileName
   * @param string $pemFileName
   * @throws \Exception
   * @return boolean
   */
  private function convertPKCS7ToPEM($pkcs7FileName, $pemFileName){
    if (empty($pkcs7FileName)){
      throw new Exception("Given param PKCS7FILENAME can not be empty.");
    }
    if (empty($pemFileName)){
      throw new Exception("Given param PEMFILENAME can not be empty.");
    }

    $cmd = sprintf("openssl pkcs7 -in %s -out %s -outform PEM -print_certs", $pkcs7FileName, $pemFileName);
    exec($cmd);

    $content = preg_replace("/subject=[\s\d\w\.,\=\-\/\\\[\]\(\)]*-----BEGIN CERTIFICATE-----/", "-----BEGIN CERTIFICATE-----", file_get_contents($pemFileName));
    if (!empty($content)){
      file_put_contents($pemFileName, $content);
    }

    $count = preg_match_all("/(-----BEGIN CERTIFICATE-----[\s\d\w\.,\=\+\/\\\[\]\(\)]+-----END CERTIFICATE-----)/", $content, $matches, PREG_PATTERN_ORDER);
    for($i = 0; $i<$count; $i++){
      if(isset($matches[0][$i])){
        file_put_contents(sprintf("%s.%d", $pemFileName, $i), $matches[0][$i]);
      }
    }
    return $count;
  }

  /**
   * Create a public key from PEM encoded certificate.
   *
   * @param string $certificateFileName
   * @param string $publicKeyFileName
   * @throws \Exception
   * @return boolean
   */
  private function createPublicKeyFromPEM($certificateFileName, $publicKeyFileName){
    if (empty($certificateFileName)){
      throw new Exception("Given param CERTIFICATEFILENAME can not be empty.");
    }
    if (empty($publicKeyFileName)){
      throw new Exception("Given param PUBLICKEYFILENAME can not be empty.");
    }

    $cmd = sprintf("openssl x509 -pubkey -noout -in %s > %s", $certificateFileName, $publicKeyFileName);
    exec($cmd);

    return true;
  }

  /**
   * Extract signed digest from DER certificate.
   *
   * @param string $derCertificateFileName
   * @param string $digestFileName
   * @throws \Exception
   * @return boolean
   */
  private function extractSignedDigest($derCertificateFileName, $digestFileName){
    if (empty($derCertificateFileName)){
      throw new Exception("Given param DERCERTIFICATEFILENAME can not be empty.");
    }
    if (empty($digestFileName)){
      throw new Exception("Given param DIGESTFILENAME can not be empty.");
    }

    $r = array(
        "rsaEncoded" => array(),
        "messageDigest" => array(),
        "PKCS7Data" => array()
    );

    $cmd = sprintf("openssl asn1parse -inform DER -in %s", $derCertificateFileName);
    $output = exec($cmd, $fullOutput);

    $patternRSA = "/\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*OBJECT\s*:rsaEncryption\s*\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*NULL\s*\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*OCTET STRING\s*\[HEX DUMP\]:([A-Z0-9]*)/";
    $countRSA = preg_match_all($patternRSA, implode("", $fullOutput), $matches);
    if($countRSA > 0){
      for($i = 0; $i < $countRSA; $i++){
        $filename = sprintf("%s.rsa.%d", $digestFileName, $i);
        $r["rsaEncoded"][] = $filename;
        file_put_contents($filename, pack("H*", $matches[1][$i]));
      }
    }

    $patternMessageDigest = "/\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*OBJECT\s*:messageDigest\s*\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*cons:\s*SET\s*\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*OCTET STRING\s*\[HEX DUMP\]:([A-Z0-9]*)/";
    $countMessageDigest = preg_match_all($patternMessageDigest, implode("", $fullOutput), $matches);
    if($countMessageDigest > 0){
      for($i = 0; $i < $countMessageDigest; $i++){
        $r["messageDigest"][] = $matches[1][$i];
      }
    }

    $patternPKCS7Data = "/\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*OBJECT\s*:pkcs7-data\s*\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*cons:\s*cont\s*\[\s*0\s*\]\s*\s*\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*OCTET STRING\s*\[HEX DUMP\]:([A-Z0-9]*)/";
    $countPKCS7Data = preg_match_all($patternPKCS7Data, implode("", $fullOutput), $matches);
    if($countPKCS7Data > 0){
      for($i = 0; $i < $countPKCS7Data; $i++){
        $r["PKCS7Data"][] = $matches[1][$i];
      }
    }

    return $r;
  }

  /**
   * Decrypt binary digest.
   *
   * @param string $encryptedDigestFileName
   * @param string $decryptedDigestFileName
   * @param string $publicKeyFileName
   * @throws \Exception
   * @return boolean
   */
  private function decryptBinaryDigest($encryptedDigestFileName, $decryptedDigestFileName, $publicKeyFileName){
    if (empty($encryptedDigestFileName)){
      throw new Exception("Given param ENCRYPTEDDIGESTFILENAME can not be empty.");
    }
    if (empty($decryptedDigestFileName)){
      throw new Exception("Given param DECRYPTEDDIGESTFILENAME can not be empty.");
    }
    if (empty($publicKeyFileName)){
      throw new Exception("Given param PUBLICKEYFILENAME can not be empty.");
    }

    $cmd = sprintf("openssl rsautl -verify -inkey %s -in %s -out %s -pubin", $publicKeyFileName, $encryptedDigestFileName, $decryptedDigestFileName);
    exec($cmd);

    return true;
  }

  /**
   * Parse PEM certificate and returns columns from certificate.
   *
   * @param string $pemCertificateFileName
   * @throws \Exception
   * @return array
   */
  private function parseCert($pemCertificateFileName){
    if (empty($pemCertificateFileName)){
      throw new Exception("Given param PEMCERTIFICATEFILENAME can not be empty.");
    }

    $r = array(
      "serial" => "",
      "version" => "",
      "valid_from" => "",
      "valid_to" => "",
      "subject" => array(
        "serial" => "",
        "ou" => "",
        "o" => "",
        "cn" => "",
        "c" => "",
        "st" => "",
        "l" => "",
      ),
      "issuer" => array(
        "ou" => "",
        "o" => "",
        "cn" => "",
        "c" => "",
      )
    );

    $cmd = sprintf("openssl asn1parse -inform PEM -in %s", $pemCertificateFileName);
    $output = exec($cmd, $fullOutput);

    $patternOrganizationName= "/\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*OBJECT\s*:organizationName\s*<>\s*\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*(UTF8STRING|PRINTABLESTRING)\s*:([^<>]*)\s*<>/";
    $countOrganizationName = preg_match_all($patternOrganizationName, implode("<>", $fullOutput), $matches);
    if($countOrganizationName == 1){
      $r["subject"]["o"] = $matches[2][0];
    } else if($countOrganizationName == 2){
      $r["issuer"]["o"] = $matches[2][0];
      $r["subject"]["o"] = $matches[2][1];
    }

    $patternCountryName= "/\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*OBJECT\s*:countryName\s*<>\s*\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*(UTF8STRING|PRINTABLESTRING)\s*:([^<>]*)\s*<>/";
    $countCountryName = preg_match_all($patternCountryName, implode("<>", $fullOutput), $matches);
    if($countCountryName == 1){
      $r["subject"]["c"] = $matches[2][0];
    } else if($countCountryName == 2){
      $r["issuer"]["c"] = $matches[2][0];
      $r["subject"]["c"] = $matches[2][1];
    }

    $patternCommonName= "/\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*OBJECT\s*:commonName\s*<>\s*\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*(UTF8STRING|PRINTABLESTRING)\s*:([^<>]*)\s*<>/";
    $countCommonName = preg_match_all($patternCommonName, implode("<>", $fullOutput), $matches);
    if($countCommonName == 1){
      $r["subject"]["cn"] = $matches[2][0];
    } else if($countCommonName == 2){
      $r["issuer"]["cn"] = $matches[2][0];
      $r["subject"]["cn"] = $matches[2][1];
    }

    $patternSerial= "/\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*OBJECT\s*:serialNumber\s*<>\s*\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*(UTF8STRING|PRINTABLESTRING)\s*:([^<>]*)\s*<>/";
    $countSerial = preg_match_all($patternSerial, implode("<>", $fullOutput), $matches);
    if($countSerial == 1){
      $r["subject"]["serial"] = $matches[2][0];
    }

    $patternVersion= "/\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*INTEGER\s*:([^<>]*)\s*<>/";
    $countVersion = preg_match_all($patternVersion, implode("<>", $fullOutput), $matches);
    if($countVersion == 1){
      $r["version"] = $matches[1][0];
    }
    if($countVersion == 2){
      $r["version"] = $matches[1][0];
      $r["serial"] = $matches[1][1];
    }

    $patternTime= "/\d+:d=\d+\s*hl=\d+\s*l=\s*\d+\s*prim:\s*UTCTIME\s*:([^<>]*)\s*<>/";
    $countTime = preg_match_all($patternTime, implode("<>", $fullOutput), $matches);
    if($countTime == 2){
      $r["valid_from"] = $this->parseUTCTime($matches[1][0]);
      $r["valid_to"] = $this->parseUTCTime($matches[1][1]);
    }

    return $r;
  }

  /**
   * Convert UTC time to human readable time.
   *
   * @param string $time
   * @return string
   */
  private function parseUTCTime($time){
    $r = "";
    $pattern = "/^([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})([0-9]{2})Z$/";
    if (preg_match($pattern, $time, $matches) === 1){
      $year = intval($matches[1]);
      $year = ($year >= 70 && $year <= 99) ? sprintf("19%02d", $year) : sprintf("20%02d", $year);
      $t = sprintf("%04d-%02d-%02d %02d:%02d:%02d", $year, $matches[2], $matches[3], $matches[4], $matches[5], $matches[6]);
      $r = date("d.m.Y h:m:s", strtotime($t));
    }
    return $r;
  }

  /**
   * Remove signature content from given file.
   *
   * @param string $srcFileName
   * @param string $dstFileName
   * @param string $byteRange
   * @throws \Exception
   * @return boolean
   */
  private function removeSigatureFromPdf($srcFileName, $dstFileName, $byteRange){
    if (empty($srcFileName)){
      throw new Exception("Given param SRCFILENAME can not be empty.");
    }
    if (empty($dstFileName)){
      throw new Exception("Given param DSTFILENAME can not be empty.");
    }
    if (empty($byteRange)){
      throw new Exception("Given param BYTERANGE can not be empty.");
    }

    $src = fopen($srcFileName, "r");
    fseek($src, 0);
    $beforeSignature = fread($src, $byteRange[1]);
    fseek($src, $byteRange[2]);
    $afterSignature = fread($src, $byteRange[3]);

    if (file_exists($dstFileName)){
      unlink($dstFileName);
    }
    $dst = fopen($dstFileName, "a+");
    fwrite($dst, $beforeSignature);
    fwrite($dst, $afterSignature);

    fclose($dst);
    fclose($src);

    return true;
  }

  /**
   * Delete a file.
   *
   * @param string $file
   */
  private function rm($file){
    if (file_exists($file)){
      unlink($file);
    }
  }
}
