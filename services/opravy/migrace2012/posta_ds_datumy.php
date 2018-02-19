<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2("html_header_full.inc"));
$q=new DB_POSTA;
$c=new DB_POSTA;
$a=new DB_POSTA;

$q->query('SET LOCAL synchronous_commit TO OFF');
$c->query('SET LOCAL synchronous_commit TO OFF');
$a->query('SET LOCAL synchronous_commit TO OFF');

set_time_limit(0);

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');


//print_r($result);

echo '<div id="upl_wait_message" class="text" style="display:block"></div>';
echo "<script>document.getElementById('upl_wait_message').innerHTML = ''</script>";Flush();

$add_info="last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=".$LAST_USER_ID;


$sql="select * from posta_DS order by id desc";
//echo $sql;
$q->query($sql);
$pocet_zprav=$q->Num_Rows();

$sloupce = array('DATUM_ODESLANI','DATUM_DORUCENI','DATUM_PRECTENI');
while ($q->Next_Record())
{
  $pocitadlo++;
  $posta_id = $q->Record['ID'];
  
  $opravy = array();
  
  foreach($sloupce as $sloupec) {
    if (strlen($q->Record[$sloupec]) > 10 && strlen($q->Record[$sloupec]) < 18) $opravy[] = $sloupec . "='" . $q->Record[$sloupec] . ":00'";
  }

  if (count($opravy)>0) {
    $sql = 'update posta_DS set ' . implode(', ', $opravy) . ' where id=' . $posta_id;
//    echo $sql . '<br/>';
    $c->query($sql);
  } 
}

echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Hotovo'</script>";Flush();



require(FileUp2("html_footer.inc"));
