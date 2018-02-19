<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/funkce.inc"));
/*
*/

echo Date('H:i:s')." Otevírám ".$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["imap_adresa"]."<br/>";
Flush();
$mbox_eed = imap_open($GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["imap_adresa"], $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["username"], $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["passwd"]);
echo Date('H:i:s')." Načítám údaje z ".$GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["imap_adresa"]."<br/>";
echo '<h1>Hlavní složka</h1>';
//imap_status neni podporovan exchange serverem
//$status = imap_status($mbox_eed, $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["imap_adresa"] , SA_ALL);
$status = imap_mailboxmsginfo($mbox_eed);

if ($status) {
  echo "Počet zpráv:   " . $status->Nmsgs    . "<br />\n";
  echo "Odstraněné:     " . $status->Deleted      . "<br />\n";
  echo "Nepřečteno:     " . $status->Unread      . "<br />\n";
  
     /* echo "Počet zpráv:   " . $status->messages    . "<br />\n";
      echo "Odstraněné:     " . $status->recent      . "<br />\n";
      echo "Nepřečteno:     " . $status->unseen      . "<br />\n";
      echo "UIDnext:    " . $status->uidnext     . "<br />\n";
      echo "UIDvalidity:" . $status->uidvalidity . "<br />\n";*/
} else {
    //sice jsem zalozil slozku, ale nedostal jsem info od ni... volat tmapy
    echo "imap_status on new mailbox failed: " . imap_last_error() . "<br />\n";
}

echo Date('H:i:s')." <hr/>Slozky<br/>";
$list = imap_list($mbox_eed, $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["imap_adresa"], "*");
if (is_array($list)) {
    foreach ($list as $val) {
        echo imap_utf7_decode($val) . "<br/>";
    }
} else {
    echo "imap_list failed: " . imap_last_error() . "\n";
}

echo Date('H:i:s')." <hr/>";


echo '<h1>EED složka</h1>';
echo Date('H:i:s')." Otevírám ".$eed_folder."<br/>";
$mbox_eed = imap_open("".$eed_folder."", $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["username"], $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["passwd"]);


//$status = imap_status($mbox_eed, $eed_folder, SA_ALL);

$status = imap_mailboxmsginfo($mbox_eed);

if ($status) {
      echo "Počet zpráv:   " . $status->Nmsgs    . "<br />\n";
      echo "Odstraněné:     " . $status->Deleted      . "<br />\n";
      echo "Nepřečteno:     " . $status->Unread      . "<br />\n";
  
     /* echo "Počet zpráv:   " . $status->messages    . "<br />\n";
      echo "Odstraněné:     " . $status->recent      . "<br />\n";
      echo "Nepřečteno:     " . $status->unseen      . "<br />\n";
      echo "UIDnext:    " . $status->uidnext     . "<br />\n";
      echo "UIDvalidity:" . $status->uidvalidity . "<br />\n";*/
} else {
    //sice jsem zalozil slozku, ale nedostal jsem info od ni... volat tmapy
    echo "imap_status on new mailbox failed: " . imap_last_error() . "<br />\n";
}

if (strlen($eed_folder_karantena)>5) {
  echo '<h1>EED složka s karantenou</h1>';
  echo Date('H:i:s')." Otevírám ".$eed_folder_karantena."<br/>";
  $mbox_eed = imap_open("".$eed_folder_karantena."", $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["username"], $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["passwd"]);


  //$status = imap_status($mbox_eed, $eed_folder_karantena, SA_ALL);
$status = imap_mailboxmsginfo($mbox_eed);

if ($status) {
        echo "Počet zpráv:   " . $status->Nmsgs    . "<br />\n";
        echo "Odstraněné:     " . $status->Deleted      . "<br />\n";
        echo "Nepřečteno:     " . $status->Unread      . "<br />\n";
  
        /*echo "Počet zpráv:   " . $status->messages    . "<br />\n";
        echo "Odstraněné:     " . $status->recent      . "<br />\n";
        echo "Nepřečteno:     " . $status->unseen      . "<br />\n";
        echo "UIDnext:    " . $status->uidnext     . "<br />\n";
        echo "UIDvalidity:" . $status->uidvalidity . "<br />\n";*/
  } else {
      //sice jsem zalozil slozku, ale nedostal jsem info od ni... volat tmapy
      echo "imap_status on new mailbox failed: " . imap_last_error() . "<br />\n";
  }
}

/*
$sorted = @imap_sort($mbox_eed, SORTARRIVAL, 1); // setridime zpravy
//$headers = imap_headers($mbox_eed);
$count = count($headers);


//print_r($sorted);

/*while (list($key,$val)=each($headers))
  if ($key>$posledniid) $emaily[]=$val;
if (is_array($emaily))
*/
//while (list($key,$val)=each($emaily))

//$email=VratEmailPole($mbox_eed,7);
//print_r($email);
//Die();
/*
while (list($key,$val)=each($sorted))
{
  unset($email);
  $email=VratEmailPole($mbox_eed,$val);
  if (!in_array($email[message_id],$jiz_nactene))
  {
//    print_r($email);
    $href="<a title='Uloľit dokument do EED' href='receive.php?ID_DOSLE=".$val."'><img src='".FileUp2('images/ok_check.gif')."' border='0'></a>";
    $EMAIL_DATA[]=array("ID"=>$val,"datum"=>$email[datum],"from"=>$email[from],"vec"=>$email[vec],"odkaz"=>$href);
  }
}
//print_r($EMAIL_DATA);

include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
$db_arr = new DB_Sql_Array;
$db_arr->Data=$EMAIL_DATA;


if (count($EMAIL_DATA)>0)
  Table(array("db_connector" => &$db_arr,"showaccess" => true,"appendwhere"=>$where2,"showedit"=>false,"showdelete"=>false,"showselect"=>true,"multipleselect"=>true,"showinfo"=>true,"multipleselectsupport"=>true));  
//  Table(array("db_connector" => &$db_arr,"showaccess" => true,"appendwhere"=>$where2,"showedit"=>false,"showdelete"=>false,"showselect"=>true,"multipleselect"=>true));  
else
  echo "<span class='caption'>Příchozí emaily</span><span class='text'><br/>V dané sloľce není ľádný email k načtení.</span>";
*/
require(FileUp2("html_footer.inc"));
