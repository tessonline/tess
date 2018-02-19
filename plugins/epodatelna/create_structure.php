<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
//require_once(FileUp2(".admin/form_func.inc"));
require_once(FileUp2("html_header_posta.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/soap_funkce.inc"));

echo "<h1>Mailboxes</h1>\n";
$folders = imap_list($mbox, "".$mail."", "*");
//print_r($folders);  
//existuje folder pro predavani dokumentu do EED?
if (in_array($eed_folder,$folders))
{
  //ok, existuje
  //vypsat info, ze existuje folder, do ktereho maji presouvat emaily
  
  $status = @imap_status($mbox, $eed_folder, SA_ALL);
  if ($status) {
      echo "your new mailbox '$eed_folder' has the following status:<br />\n";
      echo "Messages:   " . $status->messages    . "<br />\n";
      echo "Recent:     " . $status->recent      . "<br />\n";
      echo "Unseen:     " . $status->unseen      . "<br />\n";
      echo "UIDnext:    " . $status->uidnext     . "<br />\n";
      echo "UIDvalidity:" . $status->uidvalidity . "<br />\n";

  } else {
      //sice jsem zalozil slozku, ale nedostal jsem info od ni... volat tmapy
      echo "imap_status on new mailbox failed: " . imap_last_error() . "<br />\n";
  }

  

}
else
{
  //sakra neni, jdeme vytvorit
  if (@imap_createmailbox($mbox, imap_utf7_encode($eed_folder))) {
      $status = @imap_status($mbox, $eed_folder, SA_ALL);
      if ($status) {
          echo "your new mailbox '$eed_folder' has the following status:<br />\n";
          echo "Messages:   " . $status->messages    . "<br />\n";
          echo "Recent:     " . $status->recent      . "<br />\n";
          echo "Unseen:     " . $status->unseen      . "<br />\n";
          echo "UIDnext:    " . $status->uidnext     . "<br />\n";
          echo "UIDvalidity:" . $status->uidvalidity . "<br />\n";
  
      } else {
          //sice jsem zalozil slozku, ale nedostal jsem info od ni... volat tmapy
          echo "imap_status on new mailbox failed: " . imap_last_error() . "<br />\n";
      }
  
  } else {
      //nepodarilo se vytvorit, kontaktujte tmapy
      echo "could not create new mailbox: " . implode("<br />\n", imap_errors()) . "<br />\n";
  }
}

print_r($folders);
