<?php

/**
 * Certifikat elktronickeho podpisu *
 * @author mier
 */
class Certificate {
  
  private $subject;
  private $serialNumber;
  private $version;
  private $validFrom;
  private $validTo;
  private $issuer;
  
  // Settery
  public function __set($name, $value) {
    $this->$name = $value;
  } 

  // Gettery
  public function __get($name) {
    return $this->$name;
  }
  
  /**
   * Konstruktor
   * @param array $pemCertificate Pole obsahujici data ziskane z certifikatu typu PEM
   */
  public function __construct($pemCertificate) {  
    $this->subject = $this->decode($pemCertificate['subject']);
    $this->serialNumber = $this->decode($pemCertificate['serialNumber']);
    $this->version = $this->decode($pemCertificate['version']);
    $this->validFrom = $this->decode($pemCertificate['validFrom_time_t']);
    $this->validTo = $this->decode($pemCertificate['validTo_time_t']);
    $this->issuer = $this->decode($pemCertificate['issuer']);
  }
  
  /**
   * Konvertuje retezec nebo polozky pole z UTF-8 do ISO-8859-2
   * @param string|array $input Retezec nebo polozky pole v kodovani UTF-8
   * @return string|array Retezec nebo polozky pole v kodovani ISO-8859-2
   */
  private function decode($input) {
        
    if (is_array($input)) {
      foreach ($input as $key => $value) {
//        $output[$key] = iconv('UTF-8', 'ISO-8859-2', $value);
        $output[$key] = $value;
      }
    }
    else {
//      $output = iconv('UTF-8', 'ISO-8859-2', $input);
      $output = $input;
    }
    return $output;
  }
}

?>
