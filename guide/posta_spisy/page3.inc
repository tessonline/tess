<?php
echo "krok š";
session_start();
require("tmapy_config.inc");
require_once(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedCj.inc');

$ID = $GLOBALS['SELECT_ID'];

// $q = new DB_POSTA;
// $ns = array();
// $spis_id = array();
//
// $cj_obj = new EedCj($GLOBALS['SPIS_ID']);
// $cj_info = $cj_obj->GetCjInfo($GLOBALS['SPIS_ID']);
// $ps = $cj_info['CELE_CISLO'];
//
// $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
// $id_user=$USER_INFO["ID"];
// $jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
// $LAST_USER_ID=$id_user;
// $OWNER_ID=$id_user;
// $LAST_TIME=Date('H:i:s');
// $LAST_DATE=Date('Y-m-d');
//
// $spis_obj = LoadClass('EedCj', $GLOBALS['SPIS_ID']);
// $spis_info = $spis_obj->GetCjInfo($GLOBALS['SPIS_ID']);
//
// $spis_nazev = $spis_info['CELY_NAZEV'];



$cj_obj = new EedCj($ID);
$cj_info = $cj_obj->GetCjInfo($ID);
$spis_id[] = $cj_info['SPIS_ID'];
$ns = $cj_info['CELY_NAZEV'];
if ($cj_info['JE_TYPOVY_SPIS']) {
	echo '<h1>' . $ns . '</h1>';
	$caption = 'Vyberte součást, do které bude čj. vloženo';
	$GLOBALS['TYPSPIS'] = $ID;
	$where = 'spis_id=' . $cj_info['TYPOVY_SPIS_ID'];
	unset($ID);
	$count = Table(array("agenda" => "POSTA_TYP_SPIS_SOUCASTI", "showselect"=>true, "showedit"=>false,"appendwhere"=>$where,multipleselect=>false,
	"formvars"=>array('TYPSPIS'),'caption'=>$caption,"showinfo"=>false,"showdelete"=>false,"showguide"=>true,'setvars'=>true
	));

} else {
if ($GLOBALS['arch'] == 1)
echo '
<script language="JavaScript" type="text/javascript">
//  window.opener.document.frm_edit.DOSBERNEHOARCHU.value = "'.$ID.'";
  window.opener.$( "input[name=\'SbernyArch\']" ).attr(\'value\' ,\''.$ns.'\');
  window.opener.$( "input[name=\'SpisButton\']" ).css( "display", "none" );
  window.opener.document.frm_edit.CISLO_SPISU1.value = "'.$cj_obj->cj1.'";
  window.opener.document.frm_edit.CISLO_SPISU2.value = "'.$cj_obj->cj2.'";
  window.opener.document.frm_edit.EXEMPLAR.value = "0";
  window.opener.document.frm_edit.PODCISLO_SPISU.value = "0";
//  window.opener.document.frm_edit.OLD_CISLO_SPISU1.value = "'.$cj_obj->cj1.'";
//  window.opener.document.frm_edit.OLD_CISLO_SPISU2.value = "'.$cj_obj->cj2.'";
  window.opener.document.frm_edit.ID_PUVODNI.value = "'.$ID.'";
  window.opener.document.frm_edit.PRIRAD_PODCISLO.value = "1";
		parent.$.fancybox.close();

</script>
';
echo "OK";
Die();
}
//if ($GLOBALS['spis'] == 1)
echo '
<script language="JavaScript" type="text/javascript">
  window.opener.document.frm_edit.DOSPISU.value = "'.$ID.'";
  window.opener.$( "input[name=\'SpisButton\']" ).attr(\'value\' ,\''.$ns.'\');
  window.opener.$( "input[name=\'SbernyArch\']" ).css( "display", "none" );
  window.opener.$( "input[name=\'SpisCreateButton\']" ).css( "display", "none" );
  parent.$.fancybox.close();

</script>
';

