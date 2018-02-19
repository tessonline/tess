<?php

include_once('Certificate.php');
include_once('Utils.php');

/**
 * Elektronicky podpis
 * @author mier
 */
abstract class Signature {
  
  /** @var string - Obsah el. podpisu */
  protected $content;
  
  /** @var bool - Zda je el. podpis platny */
  protected $valid;
  
  /** @var string - Textovy vystup verifikacni funkce */
  protected $verifyOutput;
  
  /** @var Certificate - Certifikat osoby, ktera soubor podepsala */
  protected $certificate;

  /** @const string - Odkladaci adresar pro praci se soubory */
  const TEMP_DIR  = '/tmp/';
  
  /** @const string - Adresar s certifikaty duveryhodnych autorit */
  const CA_DIR    = '/etc/pki/tls/certs/';
  
  /**
   * Funkce overi platnost el. podpisu
   * Pozor neresi konzistenci el. podepsaneho dokumentu
   * @return bool Pokud je el. podpis platny pak true, jinak false
   */  
  public abstract function isValid();
  
  /**
   * Funkce vytori z daneho certifikatu certifikat ve formatu PKCS7
   * @return string Certifikat ve formatu PKCS7
   */
  protected abstract function createPkcs7();
  

  /**
   * Settery
   */
  public function __set($name, $value) {
    $this->$name = $value;
  } 

  /**
   * Gettery
   */
  public function __get($name) {
    return $this->$name;
  }

  /**
   * Funkce vytahne z tohoto el. podpisu certifikat tvurce podpisu
   * @return Certificate Certifikat tvurce podpisu, toho el. podpisu
   */
  protected function createCertificate() {
    
    $pkcs7 = $this->createPkcs7();      
    $pem = $this->createPem($pkcs7);
    $pemArray = openssl_x509_parse($pem);

    return new Certificate($pemArray);
  }
  
  /**
   * Funkce vytvori certifikat ve formatu PEM na zaklade certifikatu ve formatu PKCS7
   * @param string $pkcs7 Certifikat ve formatu PKCS7
   * @return string Certifikat ve formatu PEM
   * @throws Exception Soubor PEM se nepodařilo vytvořit
   * @throws Exception Soubor PKCS7 se nepodařilo vytvořit
   * @throws Exception Adresář pro ulození souboru neexistuje
   */
  private function createPem($pkcs7) {
    
    if (is_dir(self::TEMP_DIR)) {

      $pkcs7FilePath = Utils::createFile($pkcs7, uniqid(), self::TEMP_DIR);
      $pemFilePath = self::TEMP_DIR . uniqid();
      
      if (file_exists($pkcs7FilePath)) {

        $command = 'openssl pkcs7 -print_certs -in ' . $pkcs7FilePath . ' -out ' . $pemFilePath;
        exec($command);        
        unlink($pkcs7FilePath);
        
        if (file_exists($pemFilePath)) {
          
          $pem = trim(file_get_contents($pemFilePath));
          unlink($pemFilePath);

          $pole = explode('subject', $pem);
          foreach($pole as $udaj) {
            if (stripos($udaj, 'serialNumber')) $pem = 'subject' . $udaj;
          }
          return $pem;
        }
        else {
          throw new Exception('Soubor PEM se nepodařilo vytvořit.');
        }
      }
      else {
        throw new Exception('Soubor PKCS7 se nepodařilo vytvořit.');
      }
    }
    else {
      throw new Exception('Adresář (' . self::TEMP_DIR . ') pro uložení souboru neexistuje.');
    }
  }
}

?>
