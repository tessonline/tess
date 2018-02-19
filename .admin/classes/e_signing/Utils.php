<?php

/**
 * Description of Utils
 * @author mier
 */
class Utils {
  
  /**
   * Vytvori certifikat ve formatu PKCS7, z retece v base64
   * @param string $base64 Base64 retezec (bez mezer a odradkovani)
   * @return string Certifikat ve formatu PKCS7 
   */
  public static function createPkcs7Format($base64) {
  
    $lineLength = 72;
    $content = '';
  
    // Format PKCS musi mit maximalne dlouhe radky 72 znaku
    for ($i = 0; $i < strlen($base64); $i += $lineLength) {
      $content .= substr($base64, $i, $lineLength) . "\n";
    }

    $headerLine = '-----BEGIN PKCS7-----';
    $footerLine = '-----END PKCS7-----';
    
    return $headerLine . "\n" . $content . $footerLine . "\n";    
  }
  
  /**
   * Funkce vytvori soubor na disku
   * @param string $content obsah souboru
   * @param string $filename Nazev souboru
   * @param string $destination Umisteni souboru
   * @return string Cesta k vytvorenemu souboru
   * @throws Exception Soubor se nepodařilo vytvořit
   * @throws Exception Adresář pro ulození souboru neexistuje
   */
  public static function createFile($content, $filename, $destination) {
    
    if (is_dir($destination)) {

      $filepath = $destination . $filename;
      $file = fopen($filepath, 'w+');

      if ($file) {

        fwrite($file, $content);
        fclose($file);

        return $filepath;
      }
      else {
        throw new Exception('Soubor ' . $filepath . ' se nepodařilo vytvořit.');
      }
    }
    else {
      throw new Exception('Adresář (' . $destination . ') pro uložení souboru neexistuje.');
    } 
  }
}

?>
