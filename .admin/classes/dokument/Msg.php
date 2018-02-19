<?php
include_once('Eml.php');

/*
 * @author luma
 */
class Msg extends Eml {
  
  /*
   * Contructor
   * @author luma
   */
  
  /*
   * Precte z emailu metadata a nastavi je do globals
   */
  public function process() {
    $res = $this->msgToEml();
    parent::process();
  }
  
  public function extractAttachments($id_posta) {
    $dir = dirname($this->doc_path);
    $this->doc_path = $dir.'/'.basename($this->doc_path,".msg").".eml";
    parent::extractAttachments($id_posta);
  }
  
  /*
   * konvertuje msg na eml
   */
  private function msgToEml() {
    $dir = dirname($this->doc_path);
    $file = $dir."/".basename($this->doc_path);
    chmod($dir, 0777);
    chmod($file, 0777);
    
    //$res_c = copy("./lib/msgconvert/msgconvert.pl",$dir."/msgconvert.pl");
    $d = getcwd();    
    chdir($dir);
    //exec("/usr/bin/perl msgconvert.pl ".$file);
    if (!file_exists($file))
      throw new Exception('Konverze MSG selhala, zdrojový soubor neexistuje');
    $output = array();
    $locale='cs_CZ.UTF-8';
    setlocale(LC_ALL,$locale);
    putenv('LC_ALL='.$locale);
    //$ex = "/var/www/cgi-bin/msg2eml \"".$file."\" > /dev/null";
    $res = exec("/var/www/cgi-bin/msg2eml \"".$file."\" > /dev/null",$output); 
    //$res = exec("/var/www/cgi-bin/msg2eml \"".$file."\"",$output);
    chdir($d);
    $dest = $dir.'/'.basename($this->doc_path,".msg").".eml";
    $this->doc_path = $dest;
    if (!file_exists($dest))
      throw new Exception('Konverze MSG selhala');
  }
}  
  
  
