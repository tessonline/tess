<?php

function getOmezStavPart($os) {
  $part = "";
  if ($os && $os>7 && $os<100) {$part=" status = " . $os;}
  if ($os && $os<2) {$part=" status = " . $os;}

  if ($os==1) {$part=" (status in (1) AND (((cislo_spisu1>0 and main_doc=1 and (kopie=0 or kopie is null) and not exists (select dalsi_spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.dalsi_spis_id))) OR (cislo_spisu1=0 or cislo_spisu1 is null)))";}
  if ($os==2) {$part=" (status in (2) or (status in (5,6) and (referent is null or referent=0)))";}
  if ($os==3) {$part=" (status in (3) or (status in (5,6) and referent is not null and DATUM_REFERENT_PRIJETI is null))";}
  if ($os==4) {$part=" (status in (4) or (status in (5,6) and referent is not null and DATUM_VYRIZENI is null))";}
  if ($os==5) {$part=" status in (5)";}
  if ($os==6) {$part=" status in (6)";}
  //if ($os==7) {$part=" status in (7)";}
  if ($os==7) {$part="  ((status in (7) or (status in (5,6) and (referent is null or referent=0) and (odbor is null or odbor=0)))) ";}
  if ($os==101) {$part=" status in (101)";}
  if ($os==199) {$part=" CISLO_SPISU1=0";}
  if ($os==200) {$part=" status < 0";}
  if ($os==201) {$part=" odeslana_posta='f'"; $GLOBALS['multipleedit']=true;}
  if ($os==202) {$part=" odeslana_posta='t'"; $GLOBALS['multipleedit']=true;}
  if ($os==203) {$part=" status > 1";}
  if ($os==204) {$part=" status > 1 AND status < 20 AND status<>9 ";}
  if ($os==205) {$part=" status in (5,6)";}
  If ($os==206) {$part=" main_doc=1 and (((DATUM_VYRIZENI)>lhuta_vyrizeni and datum_vyrizeni IS NOT NULL and lhuta_vyrizeni is not null) or (lhuta_vyrizeni<CURRENT_DATE and (status in (1,9,-3,-4)) and (datum_vyrizeni is null) and lhuta_vyrizeni is not null)) ";}
  If ($os==210) {$part=" not exists ((select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id) UNION (select dalsi_spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.dalsi_spis_id))  and p.main_doc=1 ";}
  // If ($os==220) {$part=" (not exists ((select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id) UNION (select dalsi_spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.dalsi_spis_id)) ) OR
  //  (exists (select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id))  and p.main_doc=1";}
  If ($os==220) {$part=" ((exists (select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id)) OR not exists ((select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id) UNION (select dalsi_spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.dalsi_spis_id))) and p.main_doc=1 and status>1";}

  if ($part =="") return "1=1";
  return "(".$part.")";
}



//vyhledavani - unset array polozek, pokud je v SELECT vybrana prazdna hodnota
$select_array = array("ODBOR","REFERENT","TYP_DOKUMENTU","AGENDA_DOKUMENTU","TYP_POSTY","STAV_POSTY","STAV",
                      "ZPUSOB_PODANI","DOPORUCENE","VLASTNICH_RUKOU","SKARTACE","omez_stav");
foreach ($select_array as $sel) {
  if (isset($GLOBALS[$sel])) {
    if (is_array($GLOBALS[$sel])) {
      if (strlen($GLOBALS[$sel][0])==0) unset($GLOBALS[$sel]);
    }
  }
}

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 

$user_obj = LoadClass('EedUser',$USER_INFO['ID']);
$EedSql = LoadClass('EedSql');

$unit_id = $user_obj->odbor_id;
$user_id = $user_obj->id_user;

//$nadrizene_unity = $user_obj->VratNadrizeneUnity($unit_id);
//$podrizene_unity = $user_obj->VratPodrizeneUnity($unit_id);


//if (!$GLOBALS['omez_zarizeni']) $GLOBALS['omez_zarizeni'] = EedTools::VratSuperOdbor();
// fuknce pro upravu prav....
if (!(HasRole('spravce') || HasRole('podatelna') || HasRole('podatelna-odbor')|| HasRole('spisovna')))
// tak ukazeme pouze jeden odbor.
{
  $odbor=VratOdbor();
  if (!$GLOBALS['omez_uzel'] && $GLOBALS['omez_zarizeni'] == EedTools::VratSuperOdbor()) $GLOBALS['omez_uzel'] = $odbor;

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
   $where2.=" or DALSI_PRIJEMCI ilike ('%,".$IDcka.",%')";
  }
  If ($IDcka<>"") {$where.=" AND (1=1 ".$where2.")";}
  $GLOBALS["ODESL_PRIJMENI"]="*".$GLOBALS["ODESL_PRIJMENI"]."*";

 }


if ($GLOBALS["CISLO_SPISU1_TEXT"]) {
  $GLOBALS['CISLO_SPISU1']=$GLOBALS["CISLO_SPISU1_TEXT"];
  //nejdriv pridelime cj k roku
  $count = substr_count($GLOBALS["CISLO_SPISU1"], '/');
  if (substr_count($GLOBALS["CISLO_SPISU1"], '/')==2)
    list($unused_var,$GLOBALS["CISLO_SPISU1"],$GLOBALS["CISLO_SPISU2"])=explode('/',$GLOBALS["CISLO_SPISU1"]);
    else
      list($GLOBALS["CISLO_SPISU1"],$GLOBALS["CISLO_SPISU2"])=explode('/',$GLOBALS["CISLO_SPISU1"]);
      //pokud je i podcislo spisu
      list($GLOBALS["CISLO_SPISU2"])=explode('-',$GLOBALS["CISLO_SPISU2"]);
  
  
  //if (strpos($GLOBALS["CISLO_SPISU1_TEXT"], '/')) list($GLOBALS["CISLO_SPISU1"],$GLOBALS["CISLO_SPISU2"])=explode('/',$GLOBALS["CISLO_SPISU1_TEXT"]);
  
  //a pak ho zkusime parsovat na poradove cislo a podcislo
  if (strpos($GLOBALS["CISLO_SPISU1_TEXT"], '-')) list($GLOBALS["CISLO_SPISU1"],$GLOBALS["PODCISLO_SPISU"])=explode('-',$GLOBALS["CISLO_SPISU1_TEXT"]);
  if (!strpos($GLOBALS["CISLO_SPISU1_TEXT"], '/') && !strpos($GLOBALS["CISLO_SPISU1_TEXT"], '-')) {
    $GLOBALS['CISLO_SPISU1']=$GLOBALS["CISLO_SPISU1_TEXT"];
    if (!$GLOBALS['CISLO_SPISU2']) {
      if ($GLOBALS['ROK'])
        $GLOBALS['CISLO_SPISU2']=$GLOBALS['ROK'];
      elseif ($GLOBALS['omez_rok'])
        $GLOBALS['CISLO_SPISU2']=$GLOBALS['omez_rok'];
      else
        $GLOBALS['CISLO_SPISU2']=Date('Y');
    }
  }

//  $where .= " AND (1=1 or (text_cj ilike '%".$GLOBALS["CISLO_SPISU1_TEXT"]."%' and main_doc>1))";

   $sql='select distinct(id) from posta_h where cislo_spisu1='.$GLOBALS['CISLO_SPISU1'];
   if ($GLOBALS['CISLO_SPISU2']) $sql .= "and cislo_spisu2=".$GLOBALS['CISLO_SPISU2'];
   //echo $sql;
   $puvodni_spis=$GLOBALS['CISLO_SPISU1'];
   UNSET($GLOBALS['CISLO_SPISU1']);
   $q->query($sql); $pocet=$q->Num_Rows();
   while ($q->Next_Record())
   {
     $GLOBALS['ID'][]=$q->Record['ID'];
//      $sql='select cislo_spisu1 from posta where id='.$q->Record['ID'];
//      $qqq->query($sql); $qqq->Next_Record();
//      if ($qqq->Record['CISLO_SPISU1']<>$puvodni_spis)
//        $caption="Původní čj. ".$puvodni_spis." bylo přeevidováno";
   }

}


if ($GLOBALS['CISLO_SPISU1']<>'') $GLOBALS['CISLO_SPISU1']=(int)$GLOBALS['CISLO_SPISU1']; 


if ($GLOBALS['CISLO_SPISU1']>0)
{   
   $sql='select * from posta where cislo_spisu1='.$GLOBALS['CISLO_SPISU1'].' and stornovano is null';
     //echo $sql;
   $q->query($sql);
   $pocet=$q->Num_Rows();
   if ($pocet==0) {
     $sql='select distinct(id) from posta_h where cislo_spisu1='.$GLOBALS['CISLO_SPISU1'];
     //echo $sql;
     UNSET($GLOBALS['CISLO_SPISU1']);
     $q->query($sql);
     $pocet = $q->Num_Rows();
     if ($pocet == 0) {
       $GLOBALS['ID'] = -1;
     }
     else {
       $caption="Původní čj.".$GLOBALS['CISLO_SPISU1']." bylo přeevidováno";
       while ($q->Next_Record()) {
         $GLOBALS['ID'][]=$q->Record['ID'];
       }
     }
   }
}


if ($GLOBALS['JEJICH_CJ']) $GLOBALS['JEJICH_CJ'] = "*".$GLOBALS['JEJICH_CJ']."*";
if ($GLOBALS['VEC']) $GLOBALS['VEC'] = "*".$GLOBALS['VEC']."*";
if ($GLOBALS['POZNAMKA']) $GLOBALS['POZNAMKA'] = "*".$GLOBALS['POZNAMKA']."*";

if ($GLOBALS['STAV_POSTY']<>'' && !is_array($GLOBALS['STAV_POSTY'])) $GLOBALS['STAV_POSTY'] = array(0 => $GLOBALS['STAV_POSTY']);
if (is_array($GLOBALS["STAV_POSTY"]))
  foreach($GLOBALS['STAV_POSTY'] as $stav) {
    // vyhledavani dle stavu pisemnosti (defakto vyhledavani dle barvy :-) )

    //pokud hledame napric, musime vypnout podminku z brow_access, proto u where neni .
  //  If ($stav=="SO") {$where = " AND EXISTS (select p.id from posta p LEFT JOIN posta_h h ON p.id=h.id where p.superodbor>0 and h.superodbor>0 and p.superodbor<>h.superodbor)"; UNSET($GLOBALS[SUPERODBOR]); }
      If ($stav=="SO") {$where = " AND id in (select h.id from (select distinct on (id) id,superodbor from posta_h where superodbor>0 order by id, id_h) as h  LEFT JOIN posta p ON p.id=h.id where p.superodbor>0 and p.superodbor<>h.superodbor)"; UNSET($GLOBALS[SUPERODBOR]); }
    
    If ($stav=="R") {$where.= " AND ODBOR IS NULL AND referent IS NULL";}
    If ($stav=="Z") {$where.= " AND odeslana_posta='f' AND datum_podatelna_prijeti IS NOT NULL AND (referent IS NULL or referent<1) and (ODDELENI is NULL or ODDELENI=0)";}
    If ($stav=="O") {$where.= " AND odeslana_posta='f' AND datum_podatelna_prijeti IS NOT NULL AND (referent IS NULL or referent<1) and (ODDELENI is NOT NULL)";}
    If ($stav=="M") {$where.= " AND odeslana_posta='f' AND referent IS NOT NULL AND datum_referent_prijeti IS NULL AND datum_vyrizeni IS NULL";}
    If ($stav=="C") {$where.= " AND odeslana_posta='f' AND datum_vyrizeni IS NULL AND (DATUM_PODATELNA_PRIJETI)+CAST( LHUTA || ' days' AS interval ) < CURRENT_DATE";}

    If ($stav=="RR") {$where.= " AND odeslana_posta='f' AND odesl_rekomando is not null ";}


    If ($stav=="P") {$where.= " AND odeslana_posta='f' AND datum_vyrizeni IS NULL AND  (DATUM_PODATELNA_PRIJETI)+CAST( LHUTA-5 || ' days' AS interval ) < CURRENT_DATE  AND  (DATUM_PODATELNA_PRIJETI)+CAST( LHUTA || ' days' AS interval ) >= CURRENT_DATE";}
    If ($stav=="H") {$where.= " AND odeslana_posta='t' AND (doporucene='3' or doporucene='4' or doporucene='5' or doporucene='O' or doporucene='Y' or doporucene='Z') AND datum_doruceni IS NULL";}
    If ($stav=="S") {$where.= " AND skartace IS NULL AND MAIN_DOC>0 AND stornovano is null";}
    If ($stav=="SS") {$where.= " AND stornovano is not null";}

    If ($stav=="CJ" && $GLOBALS["CONFIG"]["SHOW_C_JEDNACI"]) {$where.= " AND p.ID in select p.id from posta_h h LEFT JOIN posta p ON p.id=h.id where h.cislo_jednaci1>0 and p.cislo_jednaci1<>h.cislo_jednaci1)";}
    If ($stav=="CJ" && !$GLOBALS["CONFIG"]["SHOW_C_JEDNACI"]) {$where.= " AND p.ID in (select p.id from posta_h h LEFT JOIN posta p ON p.id=h.id where h.cislo_spisu1>0 and p.cislo_spisu1<>h.cislo_spisu1)";}
//    If ($stav=="SO") {$where.= " AND p.ID in (select p.id from posta_h h LEFT JOIN posta p ON p.id=h.id where p.superodbor<>h.superodbor)"; UNSET($GLOBALS[SUPERODBOR]); echo "ONMA, OK";}
  //  If ($stav=="U") {$where.= " AND p.ID not in (select spis_id from cis_posta_spisy UNION select dalsi_spis_id from cis_posta_spisy)";}
    If ($stav=="V") {$where.= " AND odeslana_posta='f' AND vyrizeno IS NULL";}
  //  If ($stav=="PV") {$where.= " AND main_doc=1 and (((DATUM_VYRIZENI)>lhuta_vyrizeni and datum_vyrizeni<>'' and lhuta_vyrizeni is not null) or (lhuta_vyrizeni<CURRENT_DATE and status>1 and lhuta_vyrizeni is not null))";}
    If ($stav=="PV") {$where.= " AND main_doc=1 and (((DATUM_VYRIZENI)>lhuta_vyrizeni and datum_vyrizeni is NOT NULL and lhuta_vyrizeni is not null) or (lhuta_vyrizeni<CURRENT_DATE and (status>1 and status<9) and lhuta_vyrizeni is not null))";}
  }

  //Uprava datumu
  If ($GLOBALS["DATUM_OD"])
    $where.=" AND (DATUM_PODATELNA_PRIJETI) >= ('".$GLOBALS["DATUM_OD"]."')";

  If ($GLOBALS["DATUM_DO"])
    $where.=" AND (DATUM_PODATELNA_PRIJETI) <= ('".$GLOBALS["DATUM_DO"]."')";

//zjednodusime urednikum zivot, at to maji prehledne
If ($GLOBALS["VEC"]) {$GLOBALS["VEC"]='*'.$GLOBALS["VEC"].'*';}
If ($GLOBALS["JEJICH_CJ"]) {$GLOBALS["JEJICH_CJ"]='*'.$GLOBALS["JEJICH_CJ"].'*';}
If ($GLOBALS["ODESL_PRIJMENI"]) {$GLOBALS["ODESL_PRIJMENI"]='*'.$GLOBALS["ODESL_PRIJMENI"].'*';}
If ($GLOBALS["ODESL_JMENO"]) {$GLOBALS["ODESL_JMENO"]='*'.$GLOBALS["ODESL_JMENO"].'*';}
If ($GLOBALS["ODESL_ODD"]) {$GLOBALS["ODESL_ODD"]='*'.$GLOBALS["ODESL_ODD"].'*';}
If ($GLOBALS["ODESL_OSOBA"]) {$GLOBALS["ODESL_OSOBA"]='*'.$GLOBALS["ODESL_OSOBA"].'*';}
If ($GLOBALS["ODESL_ULICE"]) {$GLOBALS["ODESL_ULICE"]='*'.$GLOBALS["ODESL_ULICE"].'*';}
If ($GLOBALS["ODESL_POSTA"]) {$GLOBALS["ODESL_POSTA"]='*'.$GLOBALS["ODESL_POSTA"].'*';}
//If ($GLOBALS["DATUM_PODATELNA_PRIJETI"]) {$GLOBALS["DATUM_PODATELNA_PRIJETI"]=$GLOBALS["DATUM_PODATELNA_PRIJETI"]."*";}
//If ($GLOBALS["DATUM_DORUCENI"]) {$GLOBALS["DATUM_DORUCENI"]=$GLOBALS["DATUM_DORUCENI"]."*";}
//If ($GLOBALS["DATUM_VYRIZENI"]) {$GLOBALS["DATUM_VYRIZENI"]=$GLOBALS["DATUM_VYRIZENI"]."*";}
//If ($GLOBALS["DATUM_REFERENT_PRIJETI"]) {$GLOBALS["DATUM_REFERENT_PRIJETI"]=$GLOBALS["DATUM_REFERENT_PRIJETI"]."*";}
//If ($GLOBALS["DATUM_PM"]) {$GLOBALS["DATUM_PM"]=$GLOBALS["DATUM_PM"]."*";}
If ($GLOBALS["POZNAMKA"]) {$GLOBALS["POZNAMKA"]='%'.$GLOBALS["POZNAMKA"].'%';}

If ($GLOBALS["NAZEV_SPISU_TEXT"]) {
  $GLOBALS["NAZEV_SPISU_TEXT"] = str_replace("*","%",$GLOBALS["NAZEV_SPISU_TEXT"]);
  $where .= " AND p.id in (select spis_id from cis_posta_spisy where nazev_spisu ilike '%".$GLOBALS["NAZEV_SPISU_TEXT"]."%') ";
}


If ($GLOBALS["SEZNAM_SPISU"]) {
  $where .= " AND p.id in (select DISTINCT(spis_id) from cis_posta_spisy) ";
}

If ($GLOBALS["JEN_CISLO_SPISU1"]) {
  
  //v pripade ze promenna jen_cislo_spisu1 neni jen cislo ale cely pid
  if (strpos($GLOBALS["JEN_CISLO_SPISU1"], '/')) {
    $count = substr_count($GLOBALS["JEN_CISLO_SPISU1"], '/');
    if (substr_count($GLOBALS["JEN_CISLO_SPISU1"], '/')==2)
      list($unused_var,$GLOBALS["JEN_CISLO_SPISU1"],$GLOBALS["JEN_CISLO_SPISU2"])=explode('/',$GLOBALS["JEN_CISLO_SPISU1"]);
      else
    list($GLOBALS["JEN_CISLO_SPISU1"],$GLOBALS["JEN_CISLO_SPISU2"])=explode('/',$GLOBALS["JEN_CISLO_SPISU1"]);
    //pokud je i podcislo spisu
    list($GLOBALS["JEN_CISLO_SPISU2"])=explode('-',$GLOBALS["JEN_CISLO_SPISU2"]);
    
  }
  $where .= " AND p.CISLO_SPISU1 IN (".$GLOBALS["JEN_CISLO_SPISU1"].") AND p.id in (select DISTINCT(spis_id) from cis_posta_spisy) ";
}

If ($GLOBALS["JEN_CISLO_SPISU2"]) {
  $where .= " AND p.CISLO_SPISU2 IN (".$GLOBALS["JEN_CISLO_SPISU2"].") AND p.id in (select DISTINCT(spis_id) from cis_posta_spisy) ";
}


If ($GLOBALS["CISLO_SPISU1"]) {
//  $where .= " AND p.CISLO_SPISU1 IN (".$GLOBALS["CISLO_SPISU1"].") AND MAIN_DOC=1 ";
}

If ($GLOBALS["CISLO_SPISU2"]) {
//  $where .= " AND p.CISLO_SPISU2 IN (".$GLOBALS["CISLO_SPISU2"].") AND MAIN_DOC=1 ";
}


If ($GLOBALS["ID_DZ"]) {
  $sql='select posta_id from posta_DS where ds_id='.$GLOBALS[ID_DZ];
  $q->query($sql);
  while ($q->Next_Record()) $GLOBALS["ID"][]=$q->Record[POSTA_ID];
}

If ($GLOBALS["ID_pole"])
{
  $prac=nl2br(trim($GLOBALS["ID_pole"]));
  $GLOBALS[ID]=explode('<br />',$prac);
}

$where = $where . ' ';

if ($GLOBALS['ID_X']) {
  $temp = PrevedCPnaID($GLOBALS['ID_X']);
  if ($temp == 0) $GLOBALS['ID'] = -1;
  if ($temp>0) $GLOBALS['ID'] = $temp;
}

$je_spis = strpos($GLOBALS['ID_X'], $GLOBALS['CONFIG']['ID_PREFIX'].'SP');
if ($GLOBALS['ID_X'] && $je_spis !== false) {
  //jde o identifikator spisu
  $id_spis = str_replace($GLOBALS['CONFIG']['ID_PREFIX'].'SP', '', $GLOBALS['ID_X']);
  $GLOBALS['ID'] = $id_spis;
}

$je_VS = strpos($GLOBALS['ID_X'], $GLOBALS['CONFIG']['ID_PREFIX'].'VS');
if ($GLOBALS['ID_X'] && $je_VS !== false) {
	//jde o identifikator spisu
	$idVS = str_replace($GLOBALS['CONFIG']['ID_PREFIX'].'VS', '', $GLOBALS['ID_X']);
	$GLOBALS['SKARTACE'] = array_keys(VratVecneSkupiny($idVS));
	$GLOBALS['SKARTACE'][] = $idVS;
	$GLOBALS['ID'] = '';
}

$je_PLAN = strpos($GLOBALS['ID_X'], $GLOBALS['CONFIG']['ID_PREFIX'].'SPISPLAN');
if ($GLOBALS['ID_X'] && $je_PLAN !== false) {
	//jde o identifikator spisu
	$idPLAN = str_replace($GLOBALS['CONFIG']['ID_PREFIX'].'SPISPLAN', '', $GLOBALS['ID_X']);
	$GLOBALS['SKARTACE'] = array_keys(VratVecneSkupiny($idVS, 0, array(), array('jen_main_id' => $idPLAN)));
	$GLOBALS['ID'] = '';
}

if (is_array($GLOBALS['SKARTACE'])&&($GLOBALS['VYHLEDAVANI']!=1))
	$GLOBALS['SKARTACE'] = array_keys(VratVecneSkupiny($GLOBALS['SKARTACE'][0], 0, array(), array('jen_main_id' => 1)));

$je_file = strpos($GLOBALS['ID_X'], $GLOBALS['CONFIG']['ID_PREFIX'].'F');
if ($GLOBALS['ID_X'] && $je_file !== false) {
  $aa = new DB_POSTA;
	$idFILE = str_replace($GLOBALS['CONFIG']['ID_PREFIX'].'F', '', $GLOBALS['ID_X']);
  $sql = "select * from files where id= " . $idFILE;
  $aa->query($sql);
  while ($aa->Next_Record()) {
  	$GLOBALS['ID'] = $aa->Record['RECORD_ID'];
  }
}

if ($GLOBALS['ID_X'] && $GLOBALS['ID'] == -1) {
  $aa = new DB_POSTA;
  $sql = "select * from files where directory like '" . $GLOBALS['ID_X'] . "' and agenda_ident like 'POSTA'";
  $aa->query($sql);
  while ($aa->Next_Record()) {
  	$GLOBALS['ID'] = $aa->Record['RECORD_ID'];
  }
}



//if (!$GLOBALS['omez_rok']) $GLOBALS['omez_rok'] = Date('Y');
if ($GLOBALS['ROK']) $GLOBALS['omez_rok'] = $GLOBALS['ROK'];
if ($GLOBALS['CISLO_SPISU2']) $GLOBALS['omez_rok'] = $GLOBALS['CISLO_SPISU2'];

if ($GLOBALS['CISLO_SPISU2']) $GLOBALS['omez_rok'] = $GLOBALS['CISLO_SPISU2'];
if ($GLOBALS['ODESL_PRIJMENI_FIRMA']) $GLOBALS['ODESL_PRIJMENI'] = $GLOBALS['ODESL_PRIJMENI_FIRMA'];

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/brow_func_end.inc');
		if (File_Exists($file)) include($file);
  }
}
