<?php

include_once('Zip.php');
include_once('Rtf.php');

/*
 * @author luma
 */
class Docx extends Rtf{
  
  /*
   * Contructor
   * @author luma
   */
  
  public $temp;
  private $zip;
  private $xml_file;
  private $extracted = false;
  
  /*// do source prijde nacteny
  function __construct($source = null,$var_array = null) {
    parent::__construct($source,$var_array);
  }*/
  
  //rozbali docx soubor do adresare temp
  private function extractFileToTemp() {
    $this->extracted = true;
    $filename = basename($this->doc_path);
    $this->temp = new Temp($GLOBALS['CONFIG_POSTA']['HLAVNI']['tmp_adresar']);
    $tmp_file =  $this->temp->getTempDir($filename);
    file_put_contents($tmp_file, $this->source);
    $this->doc_path = $tmp_file;
    $this->zip = new Zip($this->doc_path);
    $this->zip->extractTo($this->temp->getTempDir());
  }
  
  //vrati retezec textove casti docx souboru
  public function getFileContent($xml_file = "") {
    if (!$this->extracted)
      $this->extractFileToTemp();
    if ($xml_file=="")
      $xml_file = "document.xml";
    $this->xml_file = $this->temp->getTempDir("word/".$xml_file);
    $content = file_get_contents($this->xml_file);
    return $content;
  }
  
  /*
   * nastavi retezec textove casi docx souboru, 
   * zabali obsah docx na puvodni cestu, smaze temp adresar
   * @return docx string
   */
/*  public function setFileContent($content) {
    //file_put_contents($this->xml_file,$content);
    $this->zip->deleteFromArchive("word/document.xml");
    $this->zip->addFromString( "word/document.xml",$content);
    $this->zip->close();
    $res = file_get_contents($this->doc_path);
    $this->temp->delTempDir(); 
    return $res;
  }*/
  
  
  public function setFileContent($content,$file) {
    $file_name = basename($file);
    $this->zip->deleteFromArchive("word/".$file_name);
    $this->zip->addFromString( "word/".$file_name,$content);
 }
  
   
  public function returnCreatedDoc() {
    $this->zip->close();
    $res = file_get_contents($this->doc_path);
    $this->temp->delTempDir();
    return $res;    
  }
  
  
  private function getFileRelation($file_name,$file) {
    //$file_path = $this->temp->getTempDir("word/document.xml");
    $file_path = $this->temp->getTempDir("word/".$file);
    $content = file_get_contents($file_path);
    $content = str_replace(":","",$content);
    $xml = simplexml_load_string($content);
    $xml = new SimpleXMLElement($content);
    $ids = $xml->xpath('//@rembed');
    $names = $xml->xpath('//piccNvPr/@name');
   // $query = "count(//piccNvPr[@name='".$file_name."']//preceding-sibling::*)+1";
   // $position = $xml->xpath ($query);
    $pos = 0;
    foreach ($names as $name) {
      $pos++;
      $sname = $name->__toString();
      if ($sname == $file_name) 
        $position = $pos; 
    }
    if ((sizeof($ids)==0)||!isset($position))
      return false;
    /*  $arr = $ids[$position-1];
      reset($arr);
      $test = array_shift(array_slice($arr, 0, 1)); 
      $test = $ids[$position-1]->attributes;*/
    $id = $ids[$position-1]->__toString();    
    $file_path = $this->temp->getTempDir("word/_rels/".$file.".rels");
    //$file_path = $this->temp->getTempDir("word/_rels/document.xml.rels");
    if (file_exists($file_path)) {
      $content = file_get_contents($file_path);
      $xml = simplexml_load_string($content);
      $q = "////*[@Id='".$id."']//@Target";
      $rel = $xml->xpath($q);
      $res = "word/".$rel[0]->__toString();
      return $res;
    } else 
      return false;
  }
  
  //vrati pole vsech xml souboru v adresari word
  private function getDocumentContent() {
    $res = array();
    foreach ($this->temp->getTempDirContent('/word') as $file) {
      $file_path = $this->temp->getTempDir("word/".$file);
      if (is_file($file_path)) {
        $res[] = $file;
      }
    }
    return $res;
  }
  
  //nahradi media soubor
  public function replaceMediaFile($file_name,$file_content) {
    $document_content = $this->getDocumentContent();
    foreach ($document_content as $file) {
      $file_path = $this->getFileRelation($file_name,$file);
      if ($file_path) {
        $this->zip->deleteFromArchive($file_path);
        $this->zip->addFromString($file_path,$file_content);
      }
    }
  }
  
  //nahradi promenne ve vsech xml souborech v adresari word
  public function replaceVars($z, $na) {
    $document_content = $this->getDocumentContent();
    foreach ($document_content as $file) {
      $file_path = $this->temp->getTempDir("word/".$file);
      $sablona = file_get_contents($file_path);
      $file_content=Str_replace($z,$na,$sablona);
      $this->setFileContent($file_content,$file);
    }
  }
   
  /*public function process($destination,$data_item,$id=0) {   
    $this->doc_path = basename($destination);
    
    $source_bak = $this->source;
    $this->source = $this->getFileContent();
    
    $replaced_xml = parent::process($destination,$data_item,$id,false);
    $this->source = $source_bak;
    $data = $this->setFileContent($replaced_xml);
    //na $destination nahrat vytvoreny docx
    file_put_contents($destination, $data);
  }*/
  
  
  public function process($destination,$data_item,$id=0) {
    $this->doc_path = basename($destination);
    $this->extractFileToTemp();
    $document_content = $this->getDocumentContent();
    foreach ($document_content as $file) {
      $source_bak = $this->source;
      $this->source = $this->getFileContent($file);    
      $replaced_xml = parent::process($destination,$data_item,$id,false);
      $this->source = $source_bak;
      $this->setFileContent($replaced_xml,$file);
    }
      $data = $this->returnCreatedDoc();
    //na $destination nahrat vytvoreny docx
    file_put_contents($destination, $data);
  }
  
  
}
 
