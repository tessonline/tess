<?php
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 

$user_obj = LoadClass('EedUser',$USER_INFO['ID']);
$EedSql = LoadClass('EedSql');

$unit_id = $user_obj->odbor_id;
$user_id = $user_obj->id_user;

//$nadrizene_unity = $user_obj->VratNadrizeneUnity($unit_id);
//$podrizene_unity = $user_obj->VratPodrizeneUnity($unit_id);


if (!$GLOBALS['omez_zarizeni']) $GLOBALS['omez_zarizeni'] = VratSuperOdbor();
if (!$GLOBALS['omez_rok']) $GLOBALS['omez_rok'] = Date('Y');

// fuknce pro upravu prav....
if (!(HasRole('spravce') || HasRole('podatelna')|| HasRole('spisovna')))
// tak ukazeme pouze jeden odbor.
{
  $odbor=VratOdbor();
  if (!$GLOBALS['omez_uzel'] && $GLOBALS['omez_zarizeni'] == VratSuperOdbor()) $GLOBALS['omez_uzel'] = $odbor;

  If ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"]) $where_prichozi=" AND (datum_predani is not null and odeslana_posta='f')"; 
  If ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"]) $where_odchozi=" AND (datum_predani_ven is null and odeslana_posta='t')"; 

}

$q=new DB_POSTA;
$pristupy=array();
//zjistime zastupy
$sql='select zastoupena from posta_zastupy where zpracovatel in ('.$USER_INFO["ID"].')';
$q->query($sql);
while ($q->Next_Record()) $pristupy[]=$q->Record["ZASTOUPENA"];



// Pokud nejsem ani vedouci odboru, ani vedouci oddeleni,ani spravce,ani podatelna,ale jsem pouze referent, pak se mi ukaze pouze moje posta...
If (!(HasRole('spravce')||HasRole('podatelna')||HasRole('spisovna')||HasRole('podatelna-odbor')||HasRole('vedouci-odbor')||HasRole('vedouci-odd')) && (HasRole('zpracovatel')))
{
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
  $pristupy[] = $USER_INFO["ID"]; 
 
  $GLOBALS['omez_prac'] = $USER_INFO["ID"];
}


if ($GLOBALS['POSTA_VYHLEDAVANI'] && $GLOBALS['CONFIG']['VYHLEDAVANI_NAPRIC_DB']) {
  $where = "  ";
  $omez_rok = '';
  $omez_zarizeni = '';
  $omez_odbor = '';
  $omez_prac = '';
  $omez_stav = '';

} //vyhledavat lze za celou databazi bez omezeni prav...

If (($GLOBALS["ZADANO_CISLO_SPISU1"]) && ($GLOBALS["ZADANO_CISLO_SPISU2"])) {
//sakra, co to je za funkci? to je neco pro nmnm, ale nevim co.
   $w=new DB_POSTA;
   $cislo_spisu1=$GLOBALS["ZADANO_CISLO_SPISU1"];
   $cislo_spisu2=$GLOBALS["ZADANO_CISLO_SPISU2"];
   $w->query ("SELECT PODCISLO_SPISU FROM POSTA where (CISLO_SPISU1='$cislo_spisu1') and (CISLO_SPISU2='$cislo_spisu2')");
   $pocetspisu=$w->num_rows();
   If ($pocetspisu>0) 
     $where.=" AND CISLO_SPISU1='".$cislo_spisu1."' and CISLO_SPISU2='".$cislo_spisu2."'";
   else
     $where.=" AND EV_CISLO='".$cislo_spisu1."' and ROK='".$cislo_spisu2."'";
}
$_SESSION["WHERE_PODMINKA"]=$where;

If ($GLOBALS["ODESL_PRIJMENI"]) 
 {
  // uzivatel chce vyhledavat podle prijmeni ci nazvu firmy, musime proto prohledat i posta_cis_prijemci
  If ($GLOBALS[CONFIG][DB]=='psql')
    $sql="select * from cis_posta_prijemci where odesl_prijmeni ilike '%".$GLOBALS["ODESL_PRIJMENI"]."%'";
 
  If ($GLOBALS[CONFIG][DB]=='mssql')
    $sql="select * from cis_posta_prijemci where odesl_prijmeni like '%".$GLOBALS["ODESL_PRIJMENI"]."%'";
  $q->query ($sql);
  $where2="";
  while($q->next_record())
  {
   $IDcka=$q->Record["ID"];
   $where2.=" or DALSI_PRIJEMCI like ('%,".$IDcka.",%')";
  }
  If ($IDcka<>"") {$where.=" AND (1=1 ".$where2.")";}
  $GLOBALS["ODESL_PRIJMENI"]="*".$GLOBALS["ODESL_PRIJMENI"]."*";

 }


if ($GLOBALS["CISLO_SPISU1_TEXT"]) 
{
  $GLOBALS['CISLO_SPISU1']=$GLOBALS["CISLO_SPISU1_TEXT"];
  //nejdriv pridelime cj k roku
  if (ereg('/',$GLOBALS["CISLO_SPISU1_TEXT"])) list($GLOBALS["CISLO_SPISU1"],$GLOBALS["CISLO_SPISU2"])=explode('/',$GLOBALS["CISLO_SPISU1_TEXT"]);
  //a pak ho zkusime parsovat na poradove cislo a podcislo
  if (ereg('-',$GLOBALS["CISLO_SPISU1_TEXT"])) list($GLOBALS["CISLO_SPISU1"],$GLOBALS["PODCISLO_SPISU"])=explode('-',$GLOBALS["CISLO_SPISU1_TEXT"]);
  if (!ereg('/',$GLOBALS["CISLO_SPISU1_TEXT"]) && !ereg('-',$GLOBALS["CISLO_SPISU1_TEXT"])) {$GLOBALS['CISLO_SPISU1']=$GLOBALS["CISLO_SPISU1_TEXT"]; $GLOBALS['CISLO_SPISU2']=Date('Y');}
}

if ($GLOBALS['CISLO_SPISU1']<>'') $GLOBALS['CISLO_SPISU1']=(int)$GLOBALS['CISLO_SPISU1']; 


if ($GLOBALS['CISLO_SPISU1']>0)
{   
   $sql='select * from posta where cislo_spisu1='.$GLOBALS['CISLO_SPISU1'].' and stornovano is null';
     //echo $sql;
   $q->query($sql);
   $pocet=$q->Num_Rows();
   if ($pocet==0)
   {
     $sql='select distinct(id) from posta_h where cislo_spisu1='.$GLOBALS['CISLO_SPISU1'];
     //echo $sql;
     $caption="Původní čj.".$GLOBALS['CISLO_SPISU1']." bylo přeevidováno";   
     UNSET($GLOBALS['CISLO_SPISU1']);
     $q->query($sql);
     while ($q->Next_Record()) $GLOBALS['ID'][]=$q->Record['ID'];
   }
}

if ($GLOBALS['JEJICH_CJ']) $GLOBALS['JEJICH_CJ'] = "*".$GLOBALS['JEJICH_CJ']."*";
if ($GLOBALS['VEC']) $GLOBALS['VEC'] = "*".$GLOBALS['VEC']."*";
 

