<?php

/**
 * trida pro obsluhu jednoho souboru
 *
 * @author onma
 * @package dokument.main 
 */
 
class soubor {
  /** nazev souboru */
  var $filename;
  /** velikost souboru */
  var $filesize;
  /** metatyp souboru*/
  var $filetype;
  /** obsah souboru v base64*/
  var $filedata;
  /** identifikator ve spisovce */
  var $uid;
  
  /**
  * konstruktor 
  *
  * @param array $adresaDS pole pro naplneni 
  */ 
  public function __construct($file) {  
    $this->filename = $file['filename'];
    $this->filesize = strlen(base64_decode($file['filedata']));
    $this->filetype = $file['filetype'];
    $this->filedata = $file['filedata'];
    $this->uid = $file['uid'];
  }

}
