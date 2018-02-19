<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
include_once(FileUp2('.admin/form_func.inc'));
include_once(FileUp2('.admin/oth_funkce.inc'));
$IDx=$_SESSION["IDP2"];
$prijemci=$PRIJEMCI2;

while (list($key,$val)=@each($_GET['jakodeslat']))
  $jakodeslat_text[]=$key.':'.$val;
while (list($key,$val)=@each($_GET['kymdeslat']))
  $kymodeslat_text[]=$key.':'.$val;

$GLOBALS['jakodeslat']=@implode(',',$jakodeslat_text); 
$GLOBALS['kymdeslat']=@implode(',',$kymodeslat_text); 

$prijemci=substr($prijemci,1,-1);
$prijemci_pole=explode(',',$prijemci);

if (is_array($GLOBALS["SELECT_ID"]))
  while (list($key,$val)=each($GLOBALS["SELECT_ID"])) $prijemci_pole[]=$val;
elseif ($GLOBALS["SELECT_ID"]<>'') $prijemci_pole[]=$GLOBALS["SELECT_ID"];

$prijemci_pole = array_unique($prijemci_pole);

$ukaz_prijemce=array();
$jakodeslat_pole_pomocne=explode(',',$GLOBALS['jakodeslat']);
while (list($key,$val)=each($jakodeslat_pole_pomocne))
{
  list($a,$b)=explode(':',$val);  
  $jakodeslat_pole[$a]=$b;
}

$kymdeslat_pole_pomocne=explode(',',$GLOBALS['kymdeslat']);
while (list($key,$val)=each($kymdeslat_pole_pomocne))
{
  list($a,$b)=explode(':',$val);  
  $kymdeslat_pole[$a]=$b;
}


//print_r($prijemci_pole);
while(list($key,$val)=each($prijemci_pole))
{
//  $ukaz_prijemce[$key]['ID']=$key;
//  $ukaz_prijemce[$key]['JAKODESLAT']=$jakodeslat_pole[$val];
//  $ukaz_prijemce[$key]['KYMDESLAT']=$kymdeslat_pole[$val];
  $prijemce_celkem[]=$val.':'.$jakodeslat_pole[$val].':'.$kymdeslat_pole[$val];
  
}
$prijemce_celkem_text=implode(',',$prijemce_celkem);
//print_r($prijemce_celkem_text);

  $textprijemci="<table><tr><td>".UkazAdresaty($prijemce_celkem_text,'a')."</td></tr></table>";

//print_r($odeslani->option);

echo $textprijemci;
//Die();

?>


<script language="JavaScript" type="text/javascript">
<!--
  window.opener.document.getElementById('PRIJEMCI_SPAN').innerHTML = '<?php echo $textprijemci; ?>';
  window.opener.document.frm_edit.DALSI_PRIJEMCI.value = '<?php echo $prijemce_celkem_text;?>';
  window.close();
//-->
</script>
