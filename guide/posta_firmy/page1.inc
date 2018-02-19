<?php
//echo $jmeno;
if ($SELECT_ID) Die('OK');
$GLOBALS["frozen"]=$GLOBALS["frozen"]?$GLOBALS["frozen"]:'A';
// echo "<font color='#000000' face='arial'><b>Filtr: </b>";
// // If ($GLOBALS["frozen"]=='A') echo "<a class=\"pages\" href='guide.php?G_NAME=posta_firmy&jmeno=".$jmeno."&odes_typ=".$odes_typ."&frozen=N'>"; echo "Jen aktivn�</a>&nbsp;&nbsp;";
// // If ($GLOBALS["frozen"]=='N') echo "<a class=\"pages\" href='guide.php?G_NAME=posta_firmy&jmeno=".$jmeno."&odes_typ=".$odes_typ."&frozen=A'>"; echo "v�echny</font></a>&nbsp;&nbsp;";
//
// If ($GLOBALS["frozen"]<>'A') echo "<a class=\"pages\" href='guide.php?G_NAME=posta_firmy&jmeno=".$jmeno."&odes_typ=".$odes_typ."&frozen=A'>"; echo "Jen aktivn�</a>&nbsp;&nbsp;";
// If ($GLOBALS["frozen"]<>'N') echo "<a class=\"pages\" href='guide.php?G_NAME=posta_firmy&jmeno=".$jmeno."&odes_typ=".$odes_typ."&frozen=N'>"; echo "v�echny</a>&nbsp;&nbsp;";
// echo "&nbsp;-&nbsp;&nbsp;&nbsp;";
// If ($GLOBALS["frozen"]<>'H') echo "<a class=\"pages\" href='guide.php?G_NAME=posta_firmy&jmeno=".$jmeno."&odes_typ=".$odes_typ."&frozen=H'>"; echo "historick�</font></a>&nbsp;&nbsp;";


//if ($GLOBALS["CONFIG"]["GUIDE_VYHLEDAVANI_CELE"])
$jmeno="%".$jmeno."%";

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
if (!(HasRole('spravce')||HasRole('podatelna')||HasRole('podatelna-odbor'))) 
{
//  $REFERENT = $USER_INFO["ID"]; //aby vsichni videli vsechno
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
//    $GLOBALS["ODDELENI"]=VratOdbor(); 
  }
} 


If ($GLOBALS["CONFIG"]["DB"]=='psql') 
{
  $where=" AND (ODESL_PRIJMENI ILIKE '".$jmeno."%')";
  //$where.=" AND u.ulice_kod = a.ulice_kod";
  //$where.=" AND (odesl_adrkod<>'')";
If ($GLOBALS["frozen"]=='N') $where.=" AND (1=1) ";
If ($GLOBALS["frozen"]=='A' && !HasRole('podatelna') && !HasRole('spravce')) $where.=" AND (frozen like 'N' or frozen IS NULL  or (frozen like 'A' and (referent in (".$USER_INFO['ID'].") OR owner_id in (".$USER_INFO['ID'].") )  )) ";
If ($GLOBALS["frozen"]=='H') {$where.=" AND (1=1) "; $GLOBALS["CONFIG_POSTA"]["ADRESATI"]["TABULKA"]="posta_stare_zaznamy";}
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


if ($email) {
  $email = str_replace('<', '', $email);
  $email = str_replace('>', '', $email);
  $where=" AND (ODESL_EMAIL ILIKE '%".$email."%')";
}
$sql = "SELECT * FROM
    (SELECT DISTINCT ON (odesl_prijmeni,odes_typ,odesl_jmeno,odesl_ulice,odesl_cp,odesl_posta,frozen,odbor) id,odes_typ,odesl_adrkod,odesl_titul,odesl_prijmeni,odesl_jmeno,odesl_odd,odesl_osoba,odesl_ulice,odesl_cp,odesl_cor,odesl_ico,odesl_psc,odesl_posta,odesl_rc,odesl_email,odesl_datschranka,odesl_datnar,frozen,'N' as adresar,referent,owner_id from posta
    WHERE (frozen like 'N' or frozen IS NULL or (frozen like 'A' and (referent in (".$USER_INFO['ID'].") or owner_id in (".$USER_INFO['ID']."))  )
    )
    UNION
    SELECT -id as id,odes_typ,odesl_adrkod,odesl_titul,odesl_prijmeni,odesl_jmeno,odesl_odd,odesl_osoba,odesl_ulice,odesl_cp,odesl_cor,odesl_ico,odesl_psc,odesl_posta,odesl_rc,odesl_email,odesl_datschranka,odesl_datnar, 'N' as frozen,'A' as adresar,'0' as referent,'0' as owner_id from posta_adresati) as foo WHERE 1=1";


//echo $where;
$count = Table(array(
// "agenda" => "POSTA_SEZNAMY_FIRMY",
 "schema_file" =>"ost/posta/services/spisovka/firmy/.admin/table_schema.inc",
 "sql"=> $sql . $where,
 "showselect"=>true, 
 "showedit"=>false, 
// "appendwhere"=>$where,
 "showdelete"=>false, 
 "showguide"=>true, 
 "showinfo"=>false,
 "showhistory"=>false,
 "setvars"=>true,
 "maxnumrows"=>100,
 "page_size"=>100,
//"select_id"=>"ID",
 "unsetvars"=>true,
 //"nopaging"=>true,
 //"action"=>"guide/posta_firmy/page2.inc"
));

//}

if ($count == 0) {
  echo '<p><div class="alert alert-info darkest-color"> <img class="alert-img" src="'.FileUpImage('images/info').'"> 
  		<h4 class="alert-title">Upozornění:</h4> <p class="info-msg">Vyhledávacím kritériím neodpovídá žádná adresa. 
  		Proveďte vyhledání znovu podle jiných kritérií.</div></p>';
  echo '<input type="button" value="Zpět na vyhledávání" onclick=" parent.$.fancybox.close();" class="btn">';
  Die();
}