<?php
require_once("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/run2_.inc"));

include_once('funkce.inc');
If ($GLOBALS["spis_id"]) {
  UzavritSpis($GLOBALS["spis_id"]);

  $cj_obj = LoadClass('EedCj', $GLOBALS['spis_id']);
  $cj_info = $cj_obj->GetCjInfo($GLOBALS['spis_id']);

  $text = $cj_info['CELY_NAZEV'] . ' byl uzavřen.';
  EedTransakce::ZapisLog($GLOBALS['spis_id'], $text, 'SPIS');
}

If ($GLOBALS["CONFIG"]["ZAPNOUT_VLASTNI_UPLOAD"])
{
  $cesta=$GLOBALS["TMAPY_DIR"]."/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_VNITRNI"];
  $q=new DB_POSTA;
  $sql="select cislo_jednaci1,cislo_jednaci2 from posta where cislo_spisu1=$GLOBALS[cislo_spisu1] and cislo_spisu2=$GLOBALS[cislo_spisu2] ";
  $q->query($sql);
  while ($q->Next_Record())
  {
    $cela_cesta=$cesta."/".$q->Record["CISLO_JEDNACI2"]."/".$q->Record["CISLO_JEDNACI1"];
    chmod($cela_cesta,0510);
  }
}
  
?>
<script language="JavaScript" type="text/javascript">
//  parent.window.document.location.reload();
//  window.close();
    parent.location.reload(true);
    window.close();

</script>
