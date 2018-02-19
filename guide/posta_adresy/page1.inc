<?php
//echo "Jsme tam";
$pocetparametru=0;
If ($okrkod<>'0') {$where.=' AND o.okres_kod='.$okrkod.'';}


If ($psc<>"") 
{
  $q=new DB_POSTA;
  $sql="SELECT psc FROM ui_adresa where psc in (".$psc.")";
  $q->Query($sql);

  $pocet=$q->Num_rows();
//  echo $pocet;
  If ($pocet>0)
  { $where.=" and a.psc IN (".$psc.")";$pocetparametru++;}
  else
  { $where.=" and a.psc >=".substr($psc,0,3)."00 and a.psc<=".substr($psc,0,3)."99 ";$pocetparametru++;}
  

}
$mesto=str_replace('*','%',$mesto);
$ULICE=str_replace('*','%',$ULICE);

If ($ULICE<>"") {$where.=" and UPPER(u.nazev) like '%".strtoupper($ULICE)."%' AND u.ulice_kod = a.ulice_kod"; $pocetparametru++;}
If (($mesto<>"")and(($psc=="")or($psc==" "))) {$where.=" AND UPPER(o.nazev) like '%".strtoupper($mesto)."%'"; $pocetparametru++;}

If ($cp<>"") {$where.=" and (j.CISDOM_HOD IN (".$cp.") or CISOR_HOD IN (".$cp."))";

  If ($co=='') {$pocetparametru++;}

}

If (($co<>"")and($co<>0)) {$where.=" and (j.CISDOM_HOD IN (".$co.") or CISOR_HOD IN (".$co."))";$pocetparametru++;}
//If ($co<>"") {$where.=" and (a.CISOR_HOD IN (".$co.") or (a.CISOR_HOD IN (".$cp."))";$pocetparametru++;}

$where.=" AND o.obec_kod = c.obec_kod";
$where.=" AND j.cobce_kod = c.cobce_kod";
//$where.=" AND u.ulice_kod = a.ulice_kod";
$where.=" AND a.objekt_kod = j.objekt_kod";

//echo $where;

//If ($okrkod<>'') {$where.=' AND a.psc='.$okrkod.'';}

//If ($okrkod=='') {$where.='okres r,kraj k WHERE 

If ($pocetparametru>=2) {
  $pocet=Table(array(
   "agenda" => "POSTA_UIRADR", 
   "showselect"=>true, 
   "showedit"=>false, 
   "appendwhere"=>$where,
   "showdelete"=>false, 
   "showguide"=>true, 
   "showinfo"=>false,
   "setvars"=>true,
   "select_id"=>"ADRESA_KOD",
   "nopaging"=>true,
   "action"=>"guide/posta_adresy/page2.inc"
  ));

}

else
{
?>
<script language="JavaScript" type="text/javascript">
<!--
  window.alert('Je nutno zadat minimálně dvě podmínky!');
  window.close();
//-->
</script>
<?php
}

?>
