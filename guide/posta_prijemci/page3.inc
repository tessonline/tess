<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
$IDx=$_SESSION["IDP2"];
$prijemci=$PRIJEMCI2;
//$ID=$GLOBALS["SELECT_ID"];

Function UkazOdesilatele($prijemci)
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
    $res="<table>";
    while($q->next_record())
    {  
      $prijmeni=$q->Record["ODESL_PRIJMENI"];
      $jmeno=$q->Record["ODESL_JMENO"];
      $psc=$q->Record["ODESL_PSC"];
      $posta=$q->Record["ODESL_POSTA"];
      $id=$q->Record["ID"];
      $co='p';
      $res.="<tr><td><a href=\'javascript:DelPrijemci($id,\"$co\")\'><img src=\"".FileUp2('images/undo2.gif')."\" border=0 alt=\"Odebrat odesílatele\"></a> $prijmeni $jmeno,&nbsp;$psc&nbsp;$posta</td></tr>";
      $i++;		
    } 
    $res.="</table>";

  }
//  die ($res);
  return $res;
}


If ($GLOBALS["SELECT_ID"]<>"") 
{ 

 If ($prijemci=="") {$prijemci=",";}
 while (list ($key, $val) = each ($GLOBALS["SELECT_ID"])) {
 // probehneme pole, zda uz tam prijemce neni...
  $ID=$val;
  $retezec=','.$ID.','; 
  
   If (!strstr($prijemci,$retezec)) 
   {
    $prijemci.=$ID.",";
   }
 }
  $textprijemci=UkazOdesilatele($prijemci);
//Die($textprijemci);
}
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
