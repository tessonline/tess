<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
include(FileUp2(".admin/security_name.inc"));

Function UkazAdresaty($prijemci,$del)
{
  $res="";
  $pole=explode(',',$prijemci);
  $co='v';
  while (list($key,$val)= each($pole))
  {
    list($odbor,$referent)=explode(':',$val);
    
    If ($del=='a') {$res.="<a href=\'javascript:DelPrijemci(\"$val\",\"$co\")\'><img src=\"".FileUp2('images/undo2.gif')."\" border=0 alt=\"Odebrat adresáta\"></a> ";}
    $res.= "</b>Odbor: <b>".UkazOdbor($odbor)."</b> ";
    If ($referent<>0) $res.= ", referent: <b>".UkazUsera($referent)."</b>";
    $res.="<br />";
  }
  
  return $res;
}


//Die($GLOBALS["ODBOR2"]);
//Die($GLOBALS["REFERENT2"]);

$pole=explode(',',$prijemci);
$prijemci2=array();
while (list($key,$val)= each($pole))
{
  If ($val<>$GLOBALS["DEL_ID"])
    $prijemci2[]=$val;
}
$prijemcak=implode(',',$prijemci2);
  
$textprijemci=UkazAdresaty($prijemcak,'a');

echo $textprijemci;
//Die($textprijemci);
?>
<script language="JavaScript" type="text/javascript">
<!--
  window.opener.document.getElementById('PRIJEMCI_SPAN').innerHTML = '<?php echo $textprijemci; ?>';
  window.opener.document.frm_edit.DALSI_PRIJEMCI.value = '<?php echo $prijemcak;?>';
  window.close();
//-->
</script>
 

