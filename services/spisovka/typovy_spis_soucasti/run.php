<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/oth_funkce_2D.inc"));
require_once(Fileup2("html_header_title.inc"));

// print_r($GLOBALS['NOVY_SPIS']);
// print_r($GLOBALS['DALSI_SPIS_ID']);

$temp1 = explode(',',$GLOBALS['DALSI_SPIS_ID']);
$temp2 = explode(',',$GLOBALS['NOVY_SPIS']);

if ($GLOBALS['DELETE_ID']) {
  $q = new DB_POSTA;
  $q->query('select * from '.$PROPERTIES['AGENDA_TABLE'].' where '.$PROPERTIES['AGENDA_ID'].'='.$GLOBALS['DELETE_ID']);
  $q->Next_Record();
  $data = $q->Record;
}

  Run_(array("showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>true));

  if ($GLOBALS['DELETE_ID']) {
    print_r($data);
    $cj_obj = LoadClass('EedCj', $data['SPIS_ID']);
    $cj_info = $cj_obj->GetCjInfo($data['SPIS_ID']);
    $text = 'součást (<b>'.$data['SOUCAST'].'</b>) byla smazána z '.$cj_info['CELY_NAZEV'];
    EedTransakce::ZapisLog($data['SPIS_ID'], $text, 'SPIS');
  }

  else {
    $cj_obj = LoadClass('EedCj', $GLOBALS['SPIS_ID']);
    $cj_info = $cj_obj->GetCjInfo($GLOBALS['SPIS_ID']);

    $text = 'založena nová součást '.$cj_info['CELY_NAZEV'];
    EedTransakce::ZapisLog($GLOBALS['SPIS_ID'], $text, 'SPIS');
  }


require_once(Fileup2("html_footer.inc"));  
?>
<script language="JavaScript" type="text/javascript">
  window.opener.document.location.reload();
  window.close();
</script>

