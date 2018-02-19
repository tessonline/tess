<table width="100%" border=0>
<tr>
<td width="100%" border=0 align=center><br/>
Předávací protokol odchozí pošty odbor <b><?php echo $odbor ?></b><br/><br/><br/><br/>
</td>
</tr>

<tr><table>
<tr>
<td class=tema width="15%" align="center"><b><i>Číslo podací</b></i></td>
<td class=tema width="15%" align="center"><b><i>Číslo jednací</b></i></td>
<td class=tema width="50%" align="center"><b><i>Odesílatel</b></i></td>
<td class=tema width="10%" align="center"><b><i>Odeslat doporučeně</b></i></td>
</tr>
<?php
$where.=" (DATUM_PODATELNA_PRIJETI) > ('".$GLOBALS["DATUM_OD"].")";
$where.=" AND (DATUM_PODATELNA_PRIJETI) < ('".$GLOBALS["DATUM_DO"].")";
$where.=" AND odbor IN (".$GLOBALS["ODBOR"].") and ODESLANA_POSTA='t' order by ev_cislo";

$q=new DB_POSTA;
$sql="select * from posta where".$where;
$q->query ($sql);
while($q->next_record())
{
  $PODACI_CISLO=$q->Record["EV_CISLO"]."/".$q->Record["ROK"];
  If ($q->Record["CISLO_SPISU1"]<>'') 
  {
   $CISLO_JEDNACI=$q->Record["CISLO_SPISU1"]."/".$q->Record["CISLO_SPISU2"]."/".$q->Record["PODCISLO_SPISU"];
  }
  else
  { $CISLO_JEDNACI="&nbsp;";}
  
  If (($q->Record["ODES_TYP"]<>"A") and ($q->Record["ODES_TYP"]<>"P")) 
  {$ODESILATEL=$q->Record["ODESL_PRIJMENI"]." ".$q->Record["ODESL_JMENO"]." ".$q->Record["ODESL_TITUL"].", ".$q->Record["ODESL_ULICE"]." ".$q->Record["ODESL_CP"].", ".$q->Record["ODESL_PSC"]." ".$q->Record["ODESL_POSTA"];}
  If (($q->Record["ODES_TYP"]=="P")) 
  {$ODESILATEL=$q->Record["ODESL_PRIJMENI"]."  ";
   If ($q->Record["ODESL_ICO"]<>"") {$ODESILATEL.=",IČO ".$q->Record["ODESL_ICO"];}
   $ODESILATEL.=", ".$q->Record["ODESL_ULICE"]." ".$q->Record["ODESL_CP"].", ".$q->Record["ODESL_PSC"]." ".$q->Record["ODESL_POSTA"];
  }
  If ($q->Record["ODES_TYP"]=="A")
  {$ODESILATEL="anonym";}
  If ($q->Record["ODES_TYP"]=="V")
  {$ODESILATEL="Veřejnost";}
 
  If ($q->Record["DOPORUCENE"]=="1") {$DOPORUCENE="ANO";} else {$DOPORUCENE="NE";}
?>  
<tr>
<td><?php echo $PODACI_CISLO ?></td>
<td><?php echo $CISLO_JEDNACI ?></td>
<td><?php echo $ODESILATEL ?></td>
<td><?php echo $DOPORUCENE ?></td>
</tr>
<?php  
}    
?>   
</table>
</tr>
<tr>
<table width="100%">
<tr>
  <td colspan=2><br/>&nbsp;<br/>&nbsp;<br/>&nbsp;<br/>
Datum předání ...........................................
  <br/>&nbsp;</td>
</tr>
<tr>
  <td width="50%">
Předal...................................
  <br/>&nbsp;</td>
  <td width="50%">
Podpis...................................
  <br/>&nbsp;</td>
</tr>
<tr>
  <td width="50%">
Převzal..................................
  <br/>&nbsp;</td>
  <td width="50%">
Podpis...................................
  <br/>&nbsp;</td>
</tr>
</table>
 
</table>
