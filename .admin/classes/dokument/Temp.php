<?php

class Temp {

  //cesta k temp adresari
  private $temp_dir_path;
     
  /*
   * Contructor
   * @author luma
   * Vytvori docasny adresar
   * @path cesta na ktere ma byt docasny adresar vytvoren
   */
  function __construct($path,$not_create = false) {
    if ($not_create) {
      $this->temp_dir_path = $path;
    } else
    {
      $this->temp_dir_path = $path.uniqid();
      mkdir($this->temp_dir_path);
      chmod($this->temp_dir_path, 0777);
    }
   }

  /*
   * Vraci cestu k temp adresari, pokud je zadano $file tak cestu k souboru v temp adresari
   * @return cesta k temp adresari
   */
  public function getTempDir($file = "") {
    if ($file<>"") 
      return $this->temp_dir_path."/".$file;
    else
      return $this->temp_dir_path;
  }
  
  public function getTempDirContent($dir = "") {
    $dir_content = array();
    $dir_content = scandir($this->temp_dir_path.$dir);
    return $dir_content;
  }
  
  /*
   * Smaze vsechny slozky a soubory na dane ceste
   */
  private function rmdir($dir) {
    if (is_dir($dir)) {
      $objects = scandir($dir);
      foreach ($objects as $object) {
        if ($object != "." && $object != "..") {
          if (filetype($dir."/".$object) == "dir")
            $this->rmdir($dir."/".$object);
            else unlink   ($dir."/".$object);
        }
      }
      reset($objects);
      rmdir($dir);
    }
  }

  /*
   * Smaze temp adresar vcetne vsech souboru a slozek
   */  
  public function delTempDir() {
    $this->rmdir($this->temp_dir_path);    
  }

}
