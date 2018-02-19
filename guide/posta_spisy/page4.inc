<?php
session_start();
require("tmapy_config.inc");
require_once(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedCj.inc');

$ID = $GLOBALS['SELECT_ID'];

//$doc = $_GET['vybrany_doc'];
$doc = 32528976;
$cj_obj = new EedCj($doc);
$cj_info = $cj_obj->GetCjInfo($doc);
$spis_id[] = $cj_info['SPIS_ID'];
$ns = $cj_info['CELY_NAZEV'];

  //if ($GLOBALS['spis'] == 1)
  echo '
  <script language="JavaScript" type="text/javascript">
    window.opener.document.frm_edit.DOSPISU.value = "'.$doc.'";
    window.opener.document.frm_edit.TYPSPIS_SOUCAST.value = "'.$ID.'";
    window.opener.$( "input[name=\'SpisButton\']" ).attr(\'value\' ,\''.$ns.'\');
    window.opener.$( "input[name=\'SbernyArch\']" ).css( "display", "none" );
    window.opener.$( "input[name=\'SpisCreateButton\']" ).css( "display", "none" );
    window.close();
  </script>
  ';
Die();