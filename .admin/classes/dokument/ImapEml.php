<?php
include_once('Dokument.php');


/*
 * @author luma
 */
class ImapEml extends Dokument {
  
  
  /*
   * Contructor
   * @author luma
   */
  function __construct() {
    $this->addVars(array("VEC","ODESL_SUBJ","ODESL_EMAIL","DATUM_PODATELNA_PRIJETI","ODESL_BODY"));
   }
   
   
   private function toImap() {
     
/*     $mail=$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["imap_adresa"];
     if (strlen($GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["name_of_eed_folder"])>2)
       $eed_folder=$mail."/".$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["name_of_eed_folder"];
       else
         $eed_folder=$mail;
  */
     include_once(FileUp2('plugins/epodatelna/.admin/nastaveni.inc'));
     
     if (strlen($eed_folder) < 5 ) {
       throw new Exception('Jméno emailové složky pro import do imap není zadáno správně: '.$eed_folder);
     }
     
     if (!$mbox_eed = @imap_open($eed_folder, $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["username"], $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["passwd"])) {
       throw new Exception('Import imap - nepodařilo se připojit k emailové schránce: '.$eed_folder);
     }
     
     $message = file_get_contents($this->doc_path);
     $res = imap_append($mbox_eed, $eed_folder,$message);     
     
     include_once(FileUp2('plugins/epodatelna/.admin/funkce.inc'));
     $msgnos = imap_search($mbox_eed, 'ALL');
     $msgno = end($msgnos);
     $eml = VratEmailPole($mbox_eed,$msgno);
     imap_delete($mbox_eed, $msgno);
     imap_close($mbox_eed);
     die();
     
   }
   
   public function process() {
     $this->toImap();
     
     /*//$this->extractAttachments(122);
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
             $data_item[] = "" ;//end($data_item); //ODESL_SUBJ
             if (isset($info['headers']['from']))
               $data_item[] = $this->emailFromHeaders($info['headers']['from']);
               else
                 $data_item[] ="";
                 $data_item[] = date('Y-m-d H:i:s');
                 
                 $data_item[] = $this->getBody($info); // ODESL_BODY
                 
                 $this->setGlobals($data_item);*/
   }
   
}