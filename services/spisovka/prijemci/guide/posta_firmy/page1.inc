<?php
//echo "Jsme tam";
//echo $jmeno;
if ($SELECT_ID) Die('OK');
$GLOBALS["frozen"]=$GLOBALS["frozen"]=='A'?'A':'N';
echo "<font color='#000000' face='arial'>Filtr: ";
If ($GLOBALS["frozen"]=='A') echo "<a class=\"pages\" href='guide.php?G_NAME=posta_firmy&jmeno=".$jmeno."&odes_typ=".$odes_typ."&frozen=N'>"; echo "Jen aktivní</a>&nbsp;&nbsp;";
If ($GLOBALS["frozen"]=='N') echo "<a class=\"pages\" href='guide.php?G_NAME=posta_firmy&jmeno=".$jmeno."&odes_typ=".$odes_typ."&frozen=A'>"; echo "všechny</font></a>&nbsp;&nbsp;";



$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
if (!(HasRole('spravce')||HasRole('podatelna'))) 
{
  $REFERENT = $USER_INFO["ID"]; 
} 
elseif(HasRole('podatelna-odbor')) 
{
  $jaky_odbor=UkazOdbor(VratOdbor(),0,0,1);
  If (GetParentGroup($jaky_odbor)==0)
  {
    //jsem v odboru, nejsem v oddeleni
    $GLOBALS["ODBOR"]=VratOdbor();
    $GLOBALS["ODDELENI"]=''; 
  }
  else
  {
    //jsem v odboru, a jsem v oddeleni
    $GLOBALS["ODBOR"]=VratOdbor(GetParentGroup($jaky_odbor));
    $GLOBALS["ODDELENI"]=VratOdbor(); 
  }
} 


If ($GLOBALS["CONFIG"]["DB"]=='psql') 
{
  $where=" AND (ODESL_PRIJMENI ILIKE '".$jmeno."%')";
  //$where.=" AND u.ulice_kod = a.ulice_kod";
  //$where.=" AND (odesl_adrkod<>'')";
If ($GLOBALS["frozen"]=='A') $where.=" AND (1=1) ";
If ($GLOBALS["frozen"]=='N') $where.=" AND (frozen like 'N' or frozen IS NULL) ";
  if ($odes_typ) $where.="AND odes_typ ='".$odes_typ."'";
}

If ($GLOBALS["CONFIG"]["DB"]=='mssql') 
{
  $where=" AND (ODESL_PRIJMENI LIKE '".$jmeno."%')";
  //$where.=" AND u.ulice_kod = a.ulice_kod";
  //$where.=" AND (odesl_adrkod<>'')";
If ($GLOBALS["frozen"]=='A') $where.=" AND (1=1) ";
If ($GLOBALS["frozen"]=='N') $where.=" AND (frozen like 'N' or frozen IS NULL) ";
  if ($odes_typ) $where.="AND odes_typ ='".$odes_typ."'";
  $where.=" GROUP BY p.odesl_prijmeni,p.odesl_adrkod,p.odes_typ,p.odesl_jmeno,odesl_posta,p.odesl_cp,p.odesl_cor,p.odesl_ulice,p.odesl_odd,p.odesl_osoba ";
}
//echo $where;
Table(array(
 "agenda" => "POSTA_SEZNAMY_FIRMY", 
 "schema_file" =>"ost/posta/services/spisovka/firmy/.admin/table_schema.inc",
 "showselect"=>true, 
 "showedit"=>false, 
 "appendwhere"=>$where,
 "showdelete"=>false, 
 "showguide"=>true, 
 "showinfo"=>false,
 "showhistory"=>false,
 "setvars"=>true,
//"select_id"=>"ID",
 "page_size"=>25,
//"select_id"=>"ID",
 "unsetvars"=>true,
 //"nopaging"=>true,
 //"action"=>"guide/posta_firmy/page2.inc"
));

//}



?>
