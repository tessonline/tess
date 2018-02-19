<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));

Function UkazAdresaty($prijemci,$del)
{
  $res="";
  If ($prijemci=="Array") {$prijemci="";}
  If ($prijemci<>"")
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
      $co='a';
      If ($del=='a') {$res.="<a href=\'javascript:DelPrijemci($id,\"$co\")\'><img src=\"".FileUp2('images/undo2.gif')."\" border=0 alt=\"Odebrat odesílatele\"></a> ";}
      $res.="$prijmeni $jmeno,&nbsp;$psc&nbsp;$posta";
      If ($del=='a') {$res.="&nbsp;&nbsp;<select name=\"jakodeslat[".$id."]\" size=1><option value=\"1\">Obyčejně</option><option value=\"2\">Doporučeně</option><option value=\"3\">Doporučeně s dodejkou</option><option value=\"4\">Do vlastních rukou adresáta</option><option value=\"5\">Do vlastních rukou zástupců</option><option value=\"F\">Faxem</option><option value=\"E\">E-mail</option><option value=\"V\">Vnitřní pošta</option><option value=\"O\">Osobní převzetí</option><option value=\"P\">Převzetí podatelnou</option><option value=\"Y\">Doručení veřejnou vyhláškou</option><option value=\"C\">Cenné psaní</option><option value=\"Z\">Pošta do zahraničí</option></select><br/>";}

      $i++;		
    } 

  }
  return $res;
}



  $sql='SELECT * FROM posta WHERE id IN ('.$ID.')';
//    die($sql);
  $q=new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
  $prijemcak=$q->Record["DALSI_PRIJEMCI"];
  $textprijemci=UkazAdresaty($prijemcak,'a');
?>
<script language="JavaScript" type="text/javascript">
<!--
  window.opener.document.getElementById('PRIJEMCI_SPAN').innerHTML = '<?php echo $textprijemci; ?>';
  window.opener.document.frm_edit.DALSI_PRIJEMCI.value = '<?php echo $prijemcak;?>';
  window.close();
//-->
</script>
