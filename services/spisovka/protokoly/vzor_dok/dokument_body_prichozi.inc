<table width="100%" border=0>
<tr>
<td width="100%" border=0 align=center>
Předávací protokol došlé pošty odbor <b><?php echo $odbor ?></b><br/><br/><br/><br/>
</td>
</tr>

<tr><table>
<tr>
<td class=tema width="20%" align="center"><b><i>Číslo podací</b></i></td>
<td class=tema width="50%" align="center"><b><i>Odesílatel</b></i></td>
<td class=tema width="30%" align="center"><b><i>Věc</b></i></td>
</tr>
<?php
$where.=" (DATUM_PODATELNA_PRIJETI) > ('".$GLOBALS["DATUM_OD"].")";
$where.=" AND (DATUM_PODATELNA_PRIJETI) < ('".$GLOBALS["DATUM_DO"].")";
$where.=" AND odbor IN (".$GLOBALS["ODBOR"].")  and ODESLANA_POSTA='f'";

$q=new DB_POSTA;
$sql="select * from posta where".$where;
//echo $sql;
$q->query ($sql);
while($q->next_record())
{
  $PODACI_CISLO=$q->Record["EV_CISLO"]."/".$q->Record["ROK"];
  If ($q->Record["ODES_TYP"]=="V")
  {$ODESILATEL="veřejnost";}
  If ($q->Record["ODES_TYP"]=="A")
  {$ODESILATEL="anonym";}
  If (($q->Record["ODES_TYP"]<>"A") and ($q->Record["ODES_TYP"]<>"P")) 
  {$ODESILATEL=$q->Record["ODESL_PRIJMENI"]." ".$q->Record["ODESL_JMENO"].", ".$q->Record["ODESL_ULICE"]." ".$q->Record["ODESL_CP"].", ".$q->Record["ODESL_PSC"]." ".$q->Record["ODESL_POSTA"];}
  If (($q->Record["ODES_TYP"]=="P")) 
  {$ODESILATEL=$q->Record["ODESL_PRIJMENI"]."  ";
   If ($q->Record["ODESL_ICO"]<>"") {$ODESILATEL.=",IČO ".$q->Record["ODESL_ICO"];}
   $ODESILATEL.=", ".$q->Record["ODESL_ULICE"]." ".$q->Record["ODESL_CP"].", ".$q->Record["ODESL_PSC"]." ".$q->Record["ODESL_POSTA"];
  }
  $VEC=$q->Record["VEC"];
?>  
<tr>
<td><?php echo $PODACI_CISLO ?></td>
<td><?php echo $ODESILATEL ?></td>
<td><?php echo $VEC ?></td>
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
