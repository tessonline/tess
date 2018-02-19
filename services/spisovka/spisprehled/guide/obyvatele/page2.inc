<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
/*
echo "vybrano ".$GLOBALS["SELECT_ID"];
echo $prefix;
*/

If ($typ=='O')
{
  $q=new DB_POSTA;
  If (!$GLOBALS["SELECT_ID"]) $GLOBALS["SELECT_ID"]=0;
  $sql="select * from obyvatele WHERE id=".$GLOBALS["SELECT_ID"];
  
  
  $q->query($sql);
  //echo $sql;
  $q->Next_Record();
  $rc=$q->Record["RC"];
  
  $jmeno=ucfirst($q->Record["JMENO"]);
  $rc=$q->Record["RC"];
  $prijmeni=ucfirst($q->Record["PRIJMENI"]);
  $rozeny=$q->Record["ROZENY"];
  $pohlavi=$q->Record["POHLAVI"];
  $stav=$q->Record["ROD_STAV"];
  $statobcan=$q->Record["STAT_OBCAN"];
  $titul=$q->Record["TITUL_P"];
  $bydliste_typ=$q->Record["TYP"];
  $bydliste_id=$q->Record["ADRESA_KOD"]?$q->Record["ADRESA_KOD"]:0;
  If ($bydliste_typ==1 || $bydliste_typ==3)
  {
    $sql2="SELECT a.stav,a.psc, a.adresa_kod,a.objekt_kod,a.cisor_hod, a.cisor_pis,j.cisdom_hod, u.nazev as ulice, c.nazev as cast ,o.nazev as mesto, k.nazev as okres FROM ui_adresa a".
                      " LEFT JOIN ui_ulice u ON (a.ulice_kod = u.ulice_kod)".
                      " LEFT JOIN ui_objekt j ON (a.objekt_kod = j.objekt_kod)".
                      " LEFT JOIN ui_cobce c ON (j.cobce_kod = c.cobce_kod)".
                      " LEFT JOIN ui_obec o ON (c.obec_kod = o.obec_kod)".
                      " LEFT JOIN ui_okres k ON (o.okres_kod = k.okres_kod)".
                      " WHERE a.stav<>3 and a.adresa_kod=".$bydliste_id;
    $a=new DB_POSTA;
  	$a->query($sql2);
  	$a->Next_Record();
  //  $ulice=VypisUlici($a->Record["ULICE"],$a->Record["CISDOM_HOD"],$a->Record["CISOR_HOD"],$a->Record["CISOR_PIS"]);
    $ulice=$a->Record["ULICE"]?$a->Record["ULICE"]:$a->Record["CAST"];
  	$cor=$a->Record["CISOR_HOD"].$a->Record["CISOR_PIS"];
  	$cpop=$a->Record["CISDOM_HOD"];
    $psc=$a->Record["PSC"];
    $mesto=$a->Record["MESTO"];
    $objekt_kod=$a->Record["OBJEKT_KOD"];
  //  $stat=$a->Record["STAT"];
  } 
  If ($bydliste_typ==2)  
  {
    $sql2="select * from oby_adre where id=".$bydliste_id;
    $a=new DB_POSTA;
  	$a->query($sql2);
  	$a->Next_Record();
  //  $ulice=VypisUlici($a->Record["ULICE"],$a->Record["CDOM_HOD"],$a->Record["COR"],$a->Record["COR_PIS"]);
    $ulice=$a->Record["ULICE"];
  	$cor=$a->Record["COR"].$a->Record["COR_PIS"];
  	$cpop=$a->Record["CDOM_HOD"];
    $psc=$a->Record["PSC"];
    $mesto=$a->Record["OBEC"];
  }
}

If ($typ=='P')
{
  $q=new DB_POSTA;
  $sql="select * from organizace WHERE id=".$GLOBALS["SELECT_ID"];
  
  
  $q->query($sql);
  //echo $sql;
  $q->Next_Record();
  $prijmeni=$q->Record["NAZEV"];
  $ico=$q->Record["ICO"];
  $ulice=$q->Record["ADR_ULICE"];
	$cor=$q->Record["ADR_COR"].$q->Record["ADR_COR_PIS"];
	$cpop=$q->Record["ADR_CDOM"];
  $psc=$q->Record["ADR_PSC"];
  $mesto=$q->Record["ADR_OBEC"];
  $objekt_kod=$q->Record["OBJEKT_KOD"];
}

//Die($sql2);

/*  window.opener.document.frm_edit.<?php echo $prefix; ?>STAT_OBCAN.value = '<?php echo $statobcan;?>';
  window.opener.document.frm_edit.<?php echo $prefix; ?>STAT_OBCAN.style.color='red';
*/

?>
<script language="JavaScript" type="text/javascript">
<!--
//  window.opener.document.frm_edit.<?php echo $prefix; ?>RC.value = '<?php echo $rc;?>';
//  window.opener.document.frm_edit.<?php echo $prefix; ?>RC.style.color='red';

  window.opener.document.frm_edit.ODESL_JMENO.value = '<?php echo $jmeno;?>';
  window.opener.document.frm_edit.ODESL_JMENO.style.color='red';

  window.opener.document.frm_edit.ODESL_PRIJMENI.value = '<?php echo $prijmeni;?>';
  window.opener.document.frm_edit.ODESL_PRIJMENI.style.color='red';

  window.opener.document.frm_edit.ODESL_ICO.value = '<?php echo $ico;?>';
  window.opener.document.frm_edit.ODESL_ICO.style.color='red';

  window.opener.document.frm_edit.ODESL_ULICE.value = '<?php echo $ulice;?>';
  window.opener.document.frm_edit.ODESL_ULICE.style.color='red';

  window.opener.document.frm_edit.ODESL_CP.value = '<?php echo $cpop;?>';
  window.opener.document.frm_edit.ODESL_CP.style.color='red';

  window.opener.document.frm_edit.ODESL_COR.value = '<?php echo $cor;?>';
  window.opener.document.frm_edit.ODESL_COR.style.color='red';

  window.opener.document.frm_edit.ODESL_PSC.value = '<?php echo $psc;?>';
  window.opener.document.frm_edit.ODESL_PSC.style.color='red';

  window.opener.document.frm_edit.ODESL_POSTA.value = '<?php echo $mesto;?>';
  window.opener.document.frm_edit.ODESL_POSTA.style.color='red';

  window.opener.document.frm_edit.OBJEKT_KOD.value = '<?php echo $objekt_kod;?>';
  window.opener.document.frm_edit.OBJEKT_KOD.style.color='red';

  window.opener.document.frm_edit.OBYVATEL_KOD.value = '<?php echo $GLOBALS["SELECT_ID"]; ?>';
  window.opener.document.frm_edit.ODESL_RC.value = '<?php echo $rc; ?>';

  window.close();
//-->
</script>
<?php

?>
