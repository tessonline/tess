<?php
session_start();
//print_r($_SESSION);
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/oth_funkce.inc"));
require(FileUp2("html_header_full.inc"));
$IDx=$_SESSION["IDP2"];
$prijemci=$PRIJEMCI2;

//include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
//include(FileUp2('.admin/el/of_select_.inc'));
include(FileUp2('.admin/form_func.inc'));

//$ID=$GLOBALS["SELECT_ID"];
/*
Function UkazAdresaty($prijemci,$del)
{
  $res="";
  If ($prijemci=="Array") {$prijemci="";}
  If ($prijemci<>"")
  {
    $prijemci=substr($prijemci,1,-1);
    $sql='SELECT * FROM cis_posta_prijemci WHERE id IN ('.$prijemci.')';
//    echo $sql;
    $q=new DB_POSTA;
    $q->query($sql);
    $i=1;
    while($q->next_record())
    {  
      $prijmeni=$q->Record["ODESL_PRIJMENI"];
      $jmeno=$q->Record["ODESL_JMENO"];
      $psc=$q->Record["ODESL_PSC"];
      $cp=$q->Record["ODESL_CP"];
      $ulice=$q->Record["ODESL_ULICE"];
      $cor=$q->Record["ODESL_COR"];
      $ulice.=($cp)?$cp:$cor;      
      $posta=$q->Record["ODESL_POSTA"];
      $id=$q->Record["ID"];
      $co='a';
      $res.="<table><tr><td><b>".($i+1).".</b></td><td colspan=2>";
      If ($del=='a') {$res.="<a href=javascript:DelPrijemci($id,'".$co."')><img src=\"".FileUp2('images/undo2.gif')."\" border=0 alt=\"Odebrat odesílatele\"></a> ";}
      $res.="<b>$prijmeni $jmeno,&nbsp;$ulice,&nbsp;$psc&nbsp;$posta</b>";
      If ($del=='a') 
      {
        $res.="</td></tr><tr><td></td><td><select name=\"jakodeslat[".$id."]\" size=1>";
        $odeslani=new of_radio_typ_odeslani(1);
        while (list($k,$o) = each($odeslani->options)) {$res.="<option value=\"".$o[value]."\">".$o[label]."</option>"; }
         
      }
      If ($del=='a') 
      {
        $res.="</td><td>&nbsp;&nbsp;&nbsp;<select name=\"kymdeslat[".$id."]\" size=1>";
        $odeslani=new of_radio_druh_odeslani(1);
        while (list($k,$o) = each($odeslani->options)) {$res.="<option value=\"".$o[value]."\">".$o[label]."</option>"; }
        $res.="</select>";
      }
      $res.="</td></tr></table>";
      $i++;		
    } 

  }

//  die ($res);
  return $res;
}
*/

If ($GLOBALS["SELECT_ID"]<>"") 
{ 
   If ($prijemci=="") {$prijemci=",";}
  
   while (list ($key, $val) = each ($GLOBALS["SELECT_ID"])) {
    $ID=$val;
    $retezec=','.$ID.','; 
    
     If (!strstr($prijemci,$retezec)) 
     {
      $prijemci.=$ID.",";
     }
   }
  $textprijemci="<table><tr><td>".UkazAdresaty($prijemci,'a')."</td></tr></table>";
}
//print_r($odeslani->option);

//echo $textprijemci;

//print_r($_COOKIE);
?>


<script language="JavaScript" type="text/javascript">
<!--
  window.opener.document.getElementById('PRIJEMCI_SPAN').innerHTML = '<?php echo $textprijemci; ?>';
  window.opener.document.frm_edit.DALSI_PRIJEMCI.value = '<?php echo $prijemci;?>';
  window.close();
//-->
</script>
<?php

?>
