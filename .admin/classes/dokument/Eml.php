<?php
include_once('Dokument.php');

/*
 * @author luma
 */
class Eml extends Dokument {
  
  private $default_mail_charset;
  public $renamed_attachment_pos;
  
  /*
   * Contructor
   * @author luma
   */
  function __construct() {
    $this->addVars(array("VEC","ODESL_SUBJ","ODESL_EMAIL","DATUM_PODATELNA_PRIJETI","ODESL_BODY"));
    $this->renamed_attachment_pos = 0;
   }
   
   
   
  //zjisti zda se jedna o prilohu a vrati jmeno souboru prilohy, pokud se nejedna o prilohu, vraci false
  private function isAttachment($content_disposition) {
    if (strpos($content_disposition, "attachment")===false)
      return false;
    $test = urldecode($content_disposition);
    $filename = $this->getStringBetween($content_disposition,"filename=\"","\"");
    if ($filename=="") $filename = $this->getStringAfter($content_disposition,"filename=");
    $m = explode("?", $filename);
    if (sizeof($m)>0)
      $encoding = $m[1];
    if (sizeof($m)>2)
      $filename = urldecode(str_replace("=","%",$m[3]));   
    //if ($encoding=="") $encoding = "utf-8";
     if ($encoding=="") $encoding = $this->detectEncoding($filename);
      $fn = explode(';',$filename);
    if (is_array($fn)) $filename = $fn[0];
    /*if ($filename=="null") 
      return false;*/
      $filename = iconv($encoding, "utf-8", $filename);      
      $filename_test = str_replace(array("\x1B","\x1A","\n", "\t", "\r", "\f"), '', $filename);
      if ($filename!=$filename_test) {
        $this->renamed_attachment_pos++;
        $GLOBALS['DESCRIPTION'] = "Tato příloha byla přejmenována z důvodu nečitelných znaků v jejím názvu.";
        $filename_test = "přejmenovaná příloha ".$this->renamed_attachment_pos.".".pathinfo($filename, PATHINFO_EXTENSION);
      } 
      return $filename_test;//iconv($encoding, "utf-8", $filename);
  }
  
  private function getAttachment($start,$end,$st) 
  {
      $fp = fopen($this->doc_path, 'r');
      fseek($fp, $start, SEEK_SET);
      $len = $end - $start;
      $written = 0;
      $body = "";
      while ($written < $len) {
        $body.= fread($fp, $len);
        $written += $len;
      }
      fseek($fp, 0, SEEK_SET);
      /*fseek($fp, $st, SEEK_SET);
      $len = $start - $st;
      $written = 0;
      $headers = "";
      while ($written < $len) {
        $headers.= fread($fp, $len);
        $written += $len;
      }*/
      fclose($fp);
      return $body;
  }
  
  private function decodeAttachment($encoding,$data) {
   // $data = str_replace(' ', '+', $data);
   // $data = chunk_split(preg_replace('!\015\012|\015|\012!','',$data));
    if (strtolower($encoding)=="base64") {

      $data = base64_decode($data);
    }
    return $data;
  }
  
  private function extractSignedFileAttachments($content) {
    $content_disposition = "";
    $filename = false;
    $file = "";
    $attachments = array();
    $encoding = "base64";
    foreach(preg_split("/((\r?\n)|(\r\n?))/", $content) as $line){
      if ($filename) {
        if (strpos($line,'------=_NextPart')!==false) {
          $file = $this->decodeAttachment($encoding,$file);
          $attachments[$filename] = $file;
          $file ="";
          $filename = false;
          
        } else
        $file.=$line;  
      }
      
      if ($content_disposition!="") {
        $content_disposition.=$line;
        $filename = $this->isAttachment($content_disposition);
        $content_disposition = "";
      }
      
      if (strpos($line, 'Content-Transfer-Encoding:')) {
        $encoding = $this->getStringAfter($res,"Content-Transfer-Encoding: ");
        $q = "base64";
        if (substr($encoding, 0, strlen($q))== $q) {
          $encoding = $q;
        } else 
          $encoding = "";
      }
      if (strpos($line, 'Content-Disposition: attachment;') !== false) {
        $content_disposition = $line;
      }
    } 
    return $attachments;
    
  }
   
  /*
   * Extrahuje prilohy z emailu a ulozi je do uploadu prislusneho dokumentu
   * $param $id_posta - id vytvoreneho dokumentu
   */
  public function extractAttachments($id_posta) {
    $msg = mailparse_msg_create();
    $msg = mailparse_msg_parse_file($this->doc_path);
    $struct = mailparse_msg_get_structure($msg);

    foreach($struct as $st) {
      $section = mailparse_msg_get_part($msg, $st);
      $part = mailparse_msg_extract_part ($msg, $st);
      $info = mailparse_msg_get_part_data($section);
      
      if (isset($info['headers']['content-disposition'])) {
        $cd = $info['headers']['content-disposition'];
        $filename = $this->isAttachment($cd);
        if ($filename) {
          if ($filename =="null") {
            $file_content = $this->getAttachment($info['starting-pos-body'],$info['ending-pos-body'],$info['starting-pos']);
            $attachments = $this->extractSignedFileAttachments($file_content);
            foreach ($attachments as $filename => $file_content) {
              $this->upload($id_posta,$filename,$file_content,$info['headers']['content-transfer-encoding'] );
            }
            
            //$this->upload($id_posta,"attachment.eml",$file_content,$info['headers']['content-transfer-encoding'] );
            
          } else {
            $file_content = $this->getAttachment($info['starting-pos-body'],$info['ending-pos-body'],$info['starting-pos']);
            $this->upload($id_posta,$filename,$file_content,$info['headers']['content-transfer-encoding'] );
          }
        }
      }
    }
  }
    
  private function decode_mimeheader($text) {
    $elements = imap_mime_header_decode($text);
    $charset = $elements[0]->charset;
    if ($charset=="default") $charset = $this->defautl_mail_charset;
    $res = iconv($elements[0]->charset,"utf-8",$elements[0]->text);
    if ($res == false) $res = $elements[0]->text;
    return $res;
  }
  
  private function getBody($info) {
    $res = $this->getAttachment($info['starting-pos-body'],$info['ending-pos-body'],$info['starting-pos']);
    $result = $res;
    $res = $this->getStringAfter($res,"Content-Type: text/plain; charset=");
    if ($res) {
      list($charset) = explode(PHP_EOL, $res);
      //$res = iconv($charset,"utf-8",$res);
      $res = $this->getStringAfter($res,"Content-Transfer-Encoding: ");
      list($encoding) = explode(PHP_EOL, $res);
      $res = $this->getStringAfter($res,$encoding);
      $q = "quoted-printable";
      if (substr($encoding, 0, strlen($q))== $q) {
        //str_replace("=","%",$res);
        $res = quoted_printable_decode($res);
      }
 
      list($result) = explode("------=_Part", $res);
      
      $q = "base64";
      if (substr($encoding, 0, strlen($q))== $q) {
        $result = base64_decode($result);
      }
      
    }      
  //  $body = $this->decodeContentTransfer($res, $this->default_mail_charset);
  //  $body = $this->charset->decodeCharset($body, $this->getPartCharset($part));
   // Content-Type: text/plain; charset=
    //------=_Part
    

    /*foreach($struct as $st) {
      $section = mailparse_msg_get_part($msg, $st);
      $info = mailparse_msg_get_part_data($section);
      if (isset($info['headers']['content-disposition'])) {
        $cd = $info['headers']['content-disposition'];
        $filename = $this->isAttachment($cd);
    }*/
    if (strlen($result)>1000)
      $result = "Text emailu uveden v příloze.";
    return $result;
  }
  
  /*
   * Precte z email metadata a nastavi je do globals
   */
  public function process() {   
    //$this->extractAttachments(122);
    $msg = mailparse_msg_create();
    $msg = mailparse_msg_parse_file($this->doc_path);
    
    $struct = mailparse_msg_get_structure($msg);
    $section = mailparse_msg_get_part($msg, $struct[0]);
    $info = mailparse_msg_get_part_data($section);

    $data_item = array();
    
    if (isset($info['charset']))  
      $this->defautl_mail_charset = $info['charset'];
    else
      $this->defautl_mail_charset ="utf-8";
    if (isset($info['headers']['subject']))  
      $data_item[] = $this->decode_mimeheader($info['headers']['subject']);    
    else 
        $data_item[] ="";
        $data_item[] = $this->decode_mimeheader($info['headers']['subject']);//end($data_item); //ODESL_SUBJ
    if (isset($info['headers']['from'])) 
      $data_item[] = $this->emailFromHeaders($info['headers']['from']);
    else
        $data_item[] ="";
    $data_item[] = date('Y-m-d H:i:s');
    
    $data_item[] = $this->getBody($info); // ODESL_BODY
    
    $this->setGlobals($data_item);
  }
  
  private function b64_decode($tmp_file,$data) {
    $tmp_file_b64 = $tmp_file.".b64";    
    file_put_contents($tmp_file_b64,$data);
    $d = getcwd();
    $dir = dirname($tmp_file);
    chdir($dir);
    exec("/usr/bin/base64 \"".$tmp_file_b64."\" --decode -i >  \"".$tmp_file."\"");
    chdir($d);    
  }
  
  
  public function upload($id,$filename,$data,$encoding = '') {
    $temp = new Temp($GLOBALS['CONFIG_POSTA']['HLAVNI']['tmp_adresar']);
    $tmp_file =  $temp->getTempDir().'/'.$filename;
    
    if ($encoding=="base64") {
      $this->b64_decode($tmp_file,$data);
    } else   
    file_put_contents($tmp_file,$data);
    
    $res = parent::upload($id,$tmp_file);
    $temp->delTempDir();
    return $res;
  }
  
  private function emailFromHeaders($string) {
    preg_match('~<(.*?)>~', $string, $email);
    return $email[1]; 
  }
   
   
}