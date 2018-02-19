<?php
session_start();
require("tmapy_config.inc");
require_once(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedCj.inc');

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');
$ID = $GLOBALS['SELECT_ID'];
$soucast_id = $ID;
$GLOBALS['SPIS_ID'] = $GLOBALS['spis_idcko'] ;
//$spis_idcko v tom je ulozeno IDcko, ktere se ma vloziy
$q = new DB_POSTA;
if (count($IDs)>0) {
	foreach($IDs as $ID) {

		if (!$ID) continue;
		//  $cj_info = $cj_obj->show_debug_sql = true;
		//  $cj_info = $cj_obj->show_debug_work = true;
		$cj_obj = new EedCj($ID);
		$cj_info = $cj_obj->GetCjInfo($ID);
		$spis_id = $cj_info['SPIS_ID'];
		$soucast_array = $cj_obj->GetSoucast($soucast_id);

		$soucast = $soucast_array['SOUCAST'];
		$typovy_spis_mainID = $cj_info['TYPOVY_SPIS_MAINID'];
    $typovy_spis = $cj_info['TYPOVY_SPIS_ID'];
		$dil = EedTools::VratOtevrenyDil($typovy_spis_mainID, $soucast);

		//testneme, jeslti je dil prazdn
		$dil_id = EedTools::JeDilPrazdny($typovy_spis_mainID, $soucast, $dil);
		If ($dil_id == 0) {
            $spis_id = $GLOBALS['spis_idcko'];
            $datum_otevreni = Date('Y-m-d');
			$dalsi_spis_id = 0;		
		}	
		else {
			$spis_id = $dil_id;
			$datum_otevreni = Date('Y-m-d');
			$dalsi_spis_id = $GLOBALS['spis_idcko'];
		}
		$cj_obj = new EedCj($spis_id);
		$cj_info = $cj_obj->GetCjInfo($spis_id);
		$spis_id = $cj_info['SPIS_ID'];
       $ps = $cj_info['CELE_CISLO'];
		$ns = '';
        if ($dalsi_spis_id>0) {
        	$cj_obj = new EedCj($dalsi_spis_id);
        	$cj_info = $cj_obj->GetCjInfo($dalsi_spis_id);
        	$ns = $cj_info['CELE_CISLO'];
        	 
        }
		
		$sql = "INSERT INTO CIS_POSTA_SPISY (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID,SOUCAST,DIL,TYPOVY_SPIS,TYPOVY_SPIS_ID,DATUM_OTEVRENI) VALUES ".
				"('$ps', '$ns',  $spis_id,$dalsi_spis_id, '$LAST_DATE','$LAST_TIME',$OWNER_ID,$LAST_USER_ID,$soucast,$dil,$typovy_spis,$typovy_spis_mainID,'$datum_otevreni')";

		$q->query($sql);
		$text = 'dokument (<b>'.$ID.'</b>) '.$ns.' byl vložen do dílu typového spisu <b>' . $ps . '</b>';
		EedTransakce::ZapisLog($ID, $text, 'DOC', $id_user);
		EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'SPIS', $id_user);

	}
}
echo '
<script language="JavaScript" type="text/javascript">
window.opener.document.location.reload();
window.close();
</script>
';