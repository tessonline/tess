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
/*
//  If ($prijemci<>"")
  {

    $prijemci=substr($prijemci,1,-1);
    $sql='SELECT * FROM cis_posta_prijemci WHERE id IN ('.$prijemci.')';
    $q=new DB_POSTA;
    $q->query($sql);
    $i=1;
    while($q->next_record())
    {  
      $prijmeni=$q->Record["ODESL_PRIJMENI"];
      $jmeno=$q->Record["ODESL_JMENO"];
      $psc=$q->Record["ODESL_PSC"];
      $posta=$q->Record["ODESL_POSTA"];
      $id=$q->Record["ID"];
      $co='v';
      If ($del=='a') {$res.="<a href=\'javascript:DelPrijemci($id,\"$co\")\'><img src=\"".FileUp2('images/undo2.gif')."\" border=0 alt=\"Odebrat odesílatele\"></a> ";}
      $res.="$prijmeni $jmeno,&nbsp;$psc&nbsp;$posta";

      $i++;		
    } 

  }
  */
  
  return $res;
}


//Die($GLOBALS["ODBOR2"]);
//Die($GLOBALS["REFERENT2"]);

If ($GLOBALS["PRIJEMCI"])
  $prijemcak=$GLOBALS["PRIJEMCI"].",".$GLOBALS["ODBOR2"].":".($GLOBALS["REFERENT2"]?$GLOBALS["REFERENT2"]:"0");
  else
  $prijemcak=$GLOBALS["ODBOR2"].":".($GLOBALS["REFERENT2"]?$GLOBALS["REFERENT2"]:"0");
  
$textprijemci=UkazAdresaty($prijemcak,'a');
//Die($textprijemci);
?>
<script language="JavaScript" type="text/javascript">
<!--
  window.opener.document.getElementById('PRIJEMCI_SPAN').innerHTML = '<?php echo $textprijemci; ?>';
  window.opener.document.frm_edit.DALSI_PRIJEMCI.value = '<?php echo $prijemcak;?>';
  window.close();
//-->
</script>
 


?>


