<?php

include_once('Signature.php');

/**
 * Soubor typu s/mime
 * @author mier
 */
class SMimeFile extends Signature {
  
  /**
   * Konstruktor
   * @param string $content Obsah el. podpisu
   */
  public function __construct($content) {
    
    $this->content      = $content;
    $this->valid        = false;
    $this->verifyOutput = '';
    $this->certificate  = $this->createCertificate();
  }
  
  /**
   * Viz abstract class Signature
   * @throws Exception Adresář s důvěryhodnými certifikáty není dostupný
   * @throws Exception Soubor S/MIME se nepodařilo vytvořit
   * @todo Overovani vuci adresari s certifiakty duveryhodnych autorit
   */
  public function isValid() {
    
    if (!is_dir(self::CA_DIR)) {
      
//      throw new Exception('Adresář (' . self::CA_DIR . ') s důvěryhodnými certifikáty není dostupný.');
    }
    else {
      
      $smimeFilePath = Utils::createFile($this->content, uniqid(), self::TEMP_DIR);
      $return = -1;
      $output = array();
      
      if (file_exists($smimeFilePath)) {
        
        $command = 'openssl smime -verify -in ' . $smimeFilePath . ' ';
        exec($command, $output, $return);
        unlink($smimeFilePath);
      }
      else {
        throw new Exception('Soubor S/MIME se nepodařilo vytvořit.');
      }
      
      $this->valid = $return == 0;
      $this->verifyOutput = $output = implode("\n", $output);
    }

    return $this->valid;
  }  
  
  /**
   * Viz abstract class Signature
   * @throws Exception Soubor PKSC7 se nepodařilo vytvořit
   * @throws Exception Soubor S/MIME se nepodařilo vytvořit
   */
  public function createPkcs7() {

    $smimeFilePath = Utils::createFile($this->content, uniqid(), self::TEMP_DIR);
    $pkcs7FilePath =  self::TEMP_DIR . uniqid();
          
    if (file_exists($smimeFilePath)) {
      
      $command = 'openssl smime -pk7out -in ' . $smimeFilePath . ' -out ' . $pkcs7FilePath;
      exec($command);
      unlink($smimeFilePath);

      if (file_exists($pkcs7FilePath)) {
        
        $pkcs7 = file_get_contents($pkcs7FilePath);
        unlink($pkcs7FilePath);
        
        return $pkcs7;
      }
      else {
        throw new Exception('Soubor PKSC7 se nepodařilo vytvořit.');
      }
    }
    else {
      throw new Exception('Soubor S/MIME se nepodařilo vytvořit.');
    }
  } 
}

?>
