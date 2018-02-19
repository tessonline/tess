<?php
session_start();
require("tmapy_config.inc");
require_once(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedCj.inc');

$ID = array();

if (is_array($GLOBALS["SELECT_ID"])) {
  $IDs = $GLOBALS['SELECT_ID'];
}
else {
  $IDs[] = $GLOBALS['SELECT_ID'];
}
$q = new DB_POSTA;
$ns = array();
$spis_id = array();

$cj_obj = new EedCj($GLOBALS['SPIS_ID']);
$cj_info = $cj_obj->GetCjInfo($GLOBALS['SPIS_ID']);
$ps = $cj_info['CELE_CISLO'];

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');

$spis_obj = LoadClass('EedCj', $GLOBALS['SPIS_ID']);
$spis_info = $spis_obj->GetCjInfo($GLOBALS['SPIS_ID']);
$spis_nazev = $spis_info['CELY_NAZEV'];
$typovy_spis = $soucast = $dil = $typovy_spis_id = 0;

if ($spis_info['JE_TYPOVY_SPIS']>0) {
	//jde o typovy spis
	$sql = 'select * from cis_posta_spisy where spis_id=' . $GLOBALS['SPIS_ID'].' and dalsi_spis_id=0 and typovy_spis>0';
	$q->query($sql);
	$q->Next_Record();
	$typovy_spis = $q->Record['TYPOVY_SPIS'];
	$soucast = $q->Record['SOUCAST'];
	$dil = $q->Record['DIL'];
	$typovy_spis_id = $q->Record['TYPOVY_SPIS_ID'];
}

if (count($IDs)>0) {
  foreach($IDs as $ID) {

    if (!$ID) continue;
    //  $cj_info = $cj_obj->show_debug_sql = true;
    //  $cj_info = $cj_obj->show_debug_work = true;
    $cj_obj = new EedCj($ID);
    $cj_info = $cj_obj->GetCjInfo($ID);
    $spis_id[] = $cj_info['SPIS_ID'];
    $ns = $cj_info['CELE_CISLO'];


    $sql = "INSERT INTO CIS_POSTA_SPISY (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID,TYPOVY_SPIS,SOUCAST,DIL,TYPOVY_SPIS_ID) VALUES ".
          "('$ps', '$ns', ".$GLOBALS['SPIS_ID'].", $ID,'$LAST_DATE','$LAST_TIME',$OWNER_ID,$LAST_USER_ID,$typovy_spis,$soucast,$dil,$typovy_spis_id)";
    $q->query($sql);

    if ($spis_info['JE_TYPOVY_SPIS']>0) 
      $text = 'dokument (<b>'.$ID.'</b>) '.$ns.' byl vložen do dílu <b>' . $spis_nazev . '</b>';
    else
      $text = 'dokument (<b>'.$ID.'</b>) '.$ns.' byl vložen do spisu <b>' . $spis_nazev . '</b>';
    EedTransakce::ZapisLog($ID, $text, 'DOC', $id_user);
    EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'SPIS', $id_user);

  }
}


?>

<script language="JavaScript" type="text/javascript">
  window.opener.document.location.reload();
  window.close();
</script>


