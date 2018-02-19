<?php

include_once('Signature.php');

/**
 * Soubor typu zfo
 * @author mier
 */
class ZfoFile extends Signature {
  
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
   * @throws Exception Method not yet implemented
   */
  public function isValid() {
      
    throw new Exception('Method not yet implemented.');
  }  
  
  /**
   * Viz abstract class Signature
   */
  public function createPkcs7() {
    
    $headerLine = '-----BEGIN PKCS7-----';
    $footerLine = '-----END PKCS7-----';    
    $pkcs7 =  $headerLine . "\n" . $this->content . $footerLine . "\n"; 
    
    return $pkcs7;    
  }
}

?>
