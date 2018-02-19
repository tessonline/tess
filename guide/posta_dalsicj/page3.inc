<?php
//session_start();
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

$spis_obj = LoadClass('EedCj', $GLOBALS['SPIS_ID']);
$spis_info = $spis_obj->GetCjInfo($GLOBALS['SPIS_ID']);

$spis_nazev = $spis_info['CELY_NAZEV'];
$cj_obj = new EedCj($IDs[0]);
$cj_info = $cj_obj->GetCjInfo($IDs[0]);
$spis_id[] = $cj_info['SPIS_ID'];
$spis_idcko = $GLOBALS['SPIS_ID'];
$ns = $cj_info['CELY_NAZEV'];
if ($cj_info['JE_TYPOVY_SPIS']) {
	$ns = $cj_obj->NazevTypovehoSpisu($cj_info['TYPOVY_SPIS_MAINID']);
	echo '<h1>' . $ns . '</h1>';
	$caption = 'Vyberte součást, do které bude čj. vloženo';
	$GLOBALS['TYPSPIS'] = $IDs['0'];

	UNSET($SPIS_ID);
	$where = ' AND typovy_spis_id=' . $cj_info['TYPOVY_SPIS_MAINID'] . ' and dalsi_spis_id=-1 and dil=1 and datum_uzavreni is NULL';
	unset($ID);
//	$soucasti = EedTools::GetSoucastiTypovehoSpisu($cj_info['TYPOVY_SPIS_MAINID']);
//	print_r($soucasti);
	$count = Table(array(
			"agenda" => "POSTA_TYP_SPIS_SOUCASTIADILY",
			"showselect"=>true,
			"showedit"=>false,
			"appendwhere"=>$where,
			multipleselect=>false,
			"formvars"=>array('spis_idcko','IDs','SPIS_ID'),
			'caption'=>$caption,
			"showinfo"=>false,
			"showdelete"=>false,
			'setvars'=>true
	));
	

} else {

  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  $jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
  $LAST_USER_ID=$id_user;
  $OWNER_ID=$id_user;
  $LAST_TIME=Date('H:i:s');
  $LAST_DATE=Date('Y-m-d');


  if (count($IDs)>0) {
    foreach($IDs as $ID) {

      if (!$ID) continue;
      //  $cj_info = $cj_obj->show_debug_sql = true;
      //  $cj_info = $cj_obj->show_debug_work = true;
      $cj_obj = new EedCj($ID);
      $cj_info = $cj_obj->GetCjInfo($ID);
      $spis_id[] = $cj_info['SPIS_ID'];
      $ns = $cj_info['CELE_CISLO'];


      $sql = "INSERT INTO CIS_POSTA_SPISY (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID) VALUES ".
            "('$ns', '$ps',  $ID,".$GLOBALS['SPIS_ID'].", '$LAST_DATE','$LAST_TIME',$OWNER_ID,$LAST_USER_ID)";

      $q->query($sql);

      $text = 'dokument (<b>'.$GLOBALS['SPIS_ID'].'</b>) '.$ps.' byl vložen do spisu <b>' . $ns . '</b>';
      EedTransakce::ZapisLog($ID, $text, 'DOC', $id_user);
      EedTransakce::ZapisLog($ID, $text, 'SPIS', $id_user);
      EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'DOC', $id_user);

    }
  }

  ?>

  <script language="JavaScript" type="text/javascript">
    window.opener.document.location.reload();
    window.close();
  </script>

  <?php
}

