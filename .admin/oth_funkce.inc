<?php
include_once(FileUp2('.admin/config.inc'));
include_once(FileUp2('.admin/security_.inc'));
include_once(FileUp2('.admin/security_name.inc'));
include_once(FileUp2('.admin/db/db_posta.inc'));


if (!( function_exists('FormatSpis')))
{
Function FormatSpis($cs1,$cs2=0,$user=0,$odbor=0,$nazev_spisu=false,$podcislo=false,$nadodbor_id=false)
{
  $text_cislo_jednaci='';
  if ($cs1>0 && $cs2<1)
  {
    $qqq=new DB_POSTA;
    //nemame cj2, tak zrejme v cj1 je id dokumentu
    $sql='select * from posta where id='.$cs1;
    $qqq->query($sql);
    $pocet=$qqq->Next_Record();
    if ($pocet>0)
    {

      $cs1=$qqq->Record["CISLO_SPISU1"];
      $cs2=$qqq->Record["CISLO_SPISU2"];
      $nazev_spisu=$qqq->Record["NAZEV_SPISU"];
      $podcislo=$qqq->Record["PODCISLO_SPISU"];
      $odbor=$qqq->Record["ODBOR"];
      $nadodbor=$qqq->Record["SUPERODBOR"];
      $text_cj = $qqq->Record['TEXT_CJ'];
    
    }
  }
  If ($cs1<>0) 
  {
    $text_cisla=$cs1."/".$cs2;
    $referent=$user?"/".UkazUsera($user,true):'/--';
    $odbor=UkazOdbor($odbor,true);
    if (!$nadodbor_id)
      $nadodbor_id=VratOdbor(VratSuperOdbor());
    else
      $nadodbor_id=VratOdbor($nadodbor_id);
    if ($nadodbor>0)
    {
      $nadodbor=UkazOdbor(VratOdbor($nadodbor),true); 
    }
    else
      $nadodbor=UkazOdbor($nadodbor_id,true);
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU1"]) $text_cislo_jednaci=$text_cisla;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU2"]) $text_cislo_jednaci=$odbor."/".$text_cisla;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU3"]) $text_cislo_jednaci=$odbor."/".$cs1."/".substr($cs2,-2);

      If ($podcislo<>0 && $cs1<>'' && $cs1<>0 && $GLOBALS["CONFIG"]["PODCISLO"]) $text_cislo_jednaci.="/".$GLOBALS[PODCISLO_SPISU];    

    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU4"]) 
    {
      $text_cislo_jednaci=$cs1;
      if ($podcislo<>0) $text_cislo_jednaci.='-'.$podcislo;
      $text_cislo_jednaci.='/'.$cs2.'-'.$GLOBALS["CONFIG"]["OZNACENI_SPIS"].'/'.$nadodbor.'/'.$odbor;
    }
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU5"]) 
    {
      $text_cislo_jednaci=$cs1;
      //if ($GLOBALS[PODCISLO_SPISU]<>0) $text_cislo_jednaci.='-'.$GLOBALS[PODCISLO_SPISU];
      $text_cislo_jednaci=$GLOBALS["CONFIG"]["OZNACENI_SPIS"].$nadodbor.'/'.$cs1.'/'.$cs2;
    }


    If ($nazev_spisu) $text_cislo_jednaci.="-".$nazev_spisu;
    if ($text_cj) $text_cislo_jednaci=$text_cj;
    $res=$text_cislo_jednaci;
  }
  else  
    $res=' ';
/*
  If (($GLOBALS[PODCISLO_SPISU]<>0) and ($cs1<>'') and ($cs1<>0)) 
    {$res='<a class="pages" href="brow.php?cislo_spisu1='.$cs1.'&cislo_spisu2='.$cs2.'"><b>'.$cs1."/".$cs2."/".$GLOBALS[PODCISLO_SPISU]."</b></a> ";}
  If (($GLOBALS[PODCISLO_SPISU]==0) and ($cs1<>'') and ($cs1<>0))
    {$res='<a class="pages" href="brow.php?cislo_spisu1='.$cs1.'&cislo_spisu2='.$cs2.'"><b>'.$cs1."/".$cs2."</b></a> ";}
  If (($GLOBALS["CONFIG"]["ODBOR_SPISU"]) and ($cs1<>'') and ($cs1<>0)) 
    {$res='<a class="pages" href="brow.php?cislo_spisu1='.$cs1.'&cislo_spisu2='.$cs2.'&odbor_spisu='.$GLOBALS[ODBOR_SPISU].'"><b>'.$cs1."/".$cs2."/".$GLOBALS[ODBOR_SPISU]."</b></a> ";}
 */
  return $res;
}
}

if (!( function_exists('FormatCJednaci')))
{
Function FormatCJednaci($cj1,$cj2=0,$user=0,$odbor=0,$id=0)
{
  //funkce rozsirena o moznost zaslat pouze ID
  $res='';
  
  If ($cj1<>0 || $id<>0) 
  {
    $qqq=new DB_POSTA;
    if ($cj2<1 && $user<1)
    {
      //nemame cj2, tak zrejme v cj1 je id dokumentu
      $sql='select * from posta where id='.$cj1;
      $qqq->query($sql);
      $pocet=$qqq->Next_Record();
      if ($pocet>0)
      {

        $cj1=$qqq->Record["CISLO_JEDNACI1"];
        $cj2=$qqq->Record["CISLO_JEDNACI2"];
        $user=$qqq->Record["REFERENT"];
        $odbor=$qqq->Record["ODBOR"];
      
      }
    }
    if ($id>0)
    {
      $sql='select * from posta where id='.$id;
      $qqq->query($sql);
      $pocet=$qqq->Next_Record();
      $text_cj=$qqq->Record["TEXT_CJ"];
 
    }
    $text_cisla=$cj1."/".$cj2;
    $referent=$user?"/".UkazUsera($user,true):'/--';
    $odbor=UkazOdbor($odbor,true);
/*
    if ($GLOBALS[ODES_TYP]=='X')
    {
      //je nutno zjistit puvodni odbor
      $qqq=new DB_POSTA;
      $sql='select id,odbor,referent from posta where cislo_jednaci1='.$cj1.' and cislo_jednaci2='.$cj2.' order by id asc';
      $qqq->query($sql);
      $qqq->next_Record();
      $referent="/".UkazUsera($qqq->Record[REFERENT],true);
      $odbor=UkazOdbor($qqq->Record[ODBOR],true);
    }
*/
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI1"]) $text_cislo_jednaci=$text_cisla;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI2"]) $text_cislo_jednaci=$odbor."/".$text_cisla.$referent;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI3"]) $text_cislo_jednaci=$odbor."/".$cj1."/".substr($cj2,-2).$referent;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI4"]) $text_cislo_jednaci=$odbor."/".$text_cisla.$referent;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI4"]&&$GLOBALS["CISLO_SPISU1"]>0) $text_cislo_jednaci=$odbor."/".$text_cisla.$referent."-".$cs1."/".$cs2;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI5"]) $text_cislo_jednaci=$odbor."/".$text_cisla;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI6"]) $text_cislo_jednaci=$text_cisla."/".$odbor.$referent;

    If ($GLOBALS["CONFIG"]["CISLO_JEDNACI_PREFIX"]) $text_cislo_jednaci=$GLOBALS["CONFIG"]["CISLO_JEDNACI_PREFIX"].$text_cislo_jednaci;
    
    if ($text_cj<>'') $text_cislo_jednaci=$text_cj;
  
    If ($url) $res="<b><a class='pages' href='".GetAgendaPath("POSTA",true,false)."/brow.php?cislo_jednaci1=".$cj1."&cislo_jednaci2=".$cj2."'>".$text_cislo_jednaci."</a></b>";
    else
      $res=$text_cislo_jednaci;
   }
  return $res;
}
}
Function OdeberMezery($text)
{
  $res=false;
  $text=trim($text);
  $text=str_replace(" ","",$text);
  If ($text<>"") $res=$text; else $res=false;
  return $res;
}

Function UkazAdresu($id,$oddelovac='',$tabulka='posta',$podminky = array()) {
  static $xxx;
  If (!$xxx) $xxx=new DB_POSTA; 

  $sql='select * from '.$tabulka.' where id='.$id;
  $xxx->query($sql);
  $xxx->Next_Record();

  if ($xxx->Record['ID']<1) {
    $sqla='select * from posta_stare_zaznamy where id=' . $id;
    $xxx->query($sqla); $xxx->Next_Record();
  }


  if ($xxx->Record['ADRESAT_ID']>0) {
    $res = UkazAdresu($xxx->Record['ADRESAT_ID'], ', ', 'posta_adresati');
    return $res;
  }
  
  if (is_numeric($xxx->Record["ODESL_ULICE"])) {
    $class = LoadClass('EedUser', 0);
    $odbor_id = EedTools::VratIdOdbor($xxx->Record["ODESL_ULICE"]);
    $unity = $class->VratNadrizeneUnity($odbor_id);
    $so = html_entity_decode(end($unity),null,'utf-8');
    $so = ltrim($so," ");
  }

  $psc=substr($xxx->Record["ODESL_PSC"],0,3)." ".substr($xxx->Record["ODESL_PSC"],3,2);
  $ODESILATEL="";
  If (OdeberMezery($xxx->Record["ODESL_CP"])) $cislo=OdeberMezery($xxx->Record["ODESL_CP"]);
  If (OdeberMezery($xxx->Record["ODESL_COR"])) $cislo=OdeberMezery($xxx->Record["ODESL_COR"]);
  If (OdeberMezery($xxx->Record["ODESL_COR"]) && OdeberMezery($xxx->Record["ODESL_CP"])) $cislo=$xxx->Record["ODESL_CP"]."/".$xxx->Record["ODESL_COR"];

  If (($xxx->Record["ODES_TYP"]<>"A") and ($xxx->Record["ODES_TYP"]<>"P") and ($xxx->Record["ODES_TYP"]<>"U") and ($xxx->Record["ODES_TYP"]<>"X"))
  {
    $ODESILATEL="";
    If ($xxx->Record["ODESL_OSLOVENI"]) 
    {
      $yyy=new DB_POSTA;
      $yyy->query('select nazev from posta_cis_osloveni where id='.$xxx->Record["ODESL_OSLOVENI"]); $yyy->Next_Record();
      $ODESILATEL.=$yyy->Record["NAZEV"].$oddelovac;
    }
    If ($xxx->Record["ODESL_TITUL"]) $ODESILATEL.=$xxx->Record["ODESL_TITUL"]." ";

    If ($xxx->Record["ODESL_DATNAR"] && !$podminky['nedavat_rok_narozeni'])
    {
      $roknar=explode('-',$xxx->Record["ODESL_DATNAR"]);
      $rocnik=", nar. ".$roknar[0];
    }

    if ($GLOBALS["CONFIG"]["OTOCIT_JMENO_PRIJMENI"])
      $ODESILATEL.=$xxx->Record["ODESL_PRIJMENI"].$rocnik." ".$xxx->Record["ODESL_JMENO"]."";
    else
      $ODESILATEL.=$xxx->Record["ODESL_JMENO"]." ".$xxx->Record["ODESL_PRIJMENI"].$rocnik."";

    If ($xxx->Record["ODESL_TITUL_ZA"]) $ODESILATEL.=" ".$xxx->Record["ODESL_TITUL_ZA"];
      
    If ($xxx->Record["ODES_TYP"]=="N") $ODESILATEL.=" - notář";     
    If ($xxx->Record["ODES_TYP"]=="F") $ODESILATEL.=" - podnikatel";     
    If ($xxx->Record["ODES_TYP"]=="B") $ODESILATEL.=" - advokát";     
    If ($xxx->Record["ODES_TYP"]=="E") $ODESILATEL.=" - exekutor";     
    If ($xxx->Record["ODES_TYP"]=="T") $ODESILATEL.=" - patentový zástupce";     
    If ($xxx->Record["ODES_TYP"]=="D") $ODESILATEL.=" - daňový poradce";     
//    If (OdeberMezery($xxx->Record["ODESL_ICO"])) {$ODESILATEL.=$oddelovac."IČO: ".$xxx->Record["ODESL_ICO"];}
    If (OdeberMezery($xxx->Record["ODESL_ULICE"]) || $cislo)
      $ODESILATEL.=$oddelovac.trim($xxx->Record["ODESL_ULICE"])." ".$cislo;
    $ODESILATEL.=$oddelovac.$psc."  ".mb_strtoupper($xxx->Record["ODESL_POSTA"], 'UTF-8');
  }
  If (($xxx->Record["ODES_TYP"]=="P" || $xxx->Record["ODES_TYP"]=="U"))
  {
    
    $ODESILATEL="";
    if ($xxx->Record["ODESL_OTOCIT"]>0)
    {
      If (OdeberMezery($xxx->Record["ODESL_ODD"])) {$ODESILATEL.=$oddelovac.$xxx->Record["ODESL_ODD"];}
      If (OdeberMezery($xxx->Record["ODESL_OSOBA"])) {$ODESILATEL.=$oddelovac.$xxx->Record["ODESL_OSOBA"];}
      If (OdeberMezery($xxx->Record["ODESL_JMENO"])) {$ODESILATEL.=$oddelovac.$xxx->Record["ODESL_JMENO"];}
      $ODESILATEL.=$oddelovac.$xxx->Record["ODESL_PRIJMENI"]."";
      If (OdeberMezery($xxx->Record["ODESL_ICO"])  && !$podminky['nedavat_ico']) {$ODESILATEL.=$oddelovac."IČO: ".$xxx->Record["ODESL_ICO"];}
    
    }
    else
    {
      
      $ODESILATEL.=$xxx->Record["ODESL_PRIJMENI"]."";
      If (OdeberMezery($xxx->Record["ODESL_JMENO"])) {$ODESILATEL.=$oddelovac.$xxx->Record["ODESL_JMENO"];}
      If (OdeberMezery($xxx->Record["ODESL_ODD"])) {$ODESILATEL.=$oddelovac.$xxx->Record["ODESL_ODD"];}
      If (OdeberMezery($xxx->Record["ODESL_OSOBA"])) {$ODESILATEL.=$oddelovac.$xxx->Record["ODESL_OSOBA"];}
      If (OdeberMezery($xxx->Record["ODESL_ICO"])  && !$podminky['nedavat_ico']) {$ODESILATEL.=$oddelovac."IČO: ".$xxx->Record["ODESL_ICO"];}
    
    }
    //$ODESILATEL.="aaaa";
//    If (OdeberMezery($xxx->Record["ODESL_ULICE"]) && !$cislo)
    If (OdeberMezery($xxx->Record["ODESL_ULICE"]) || $cislo)
      $ODESILATEL.=$oddelovac.trim($xxx->Record["ODESL_ULICE"])." ".$cislo;
    $ODESILATEL.=$oddelovac.$psc."  ".mb_strtoupper($xxx->Record["ODESL_POSTA"], 'UTF-8');
  }
  If ($xxx->Record["ODESL_STAT"]<>'') $ODESILATEL.=$oddelovac.$xxx->Record["ODESL_STAT"];
  If ($xxx->Record["ODESL_JINE"]<>'') $ODESILATEL.=$oddelovac.$xxx->Record["ODESL_JINE"];
  If ($xxx->Record["ODES_TYP"]=="S") {
    $ODESILATEL=($xxx->Record["ODESL_TITUL"]==1?"Město ".$GLOBALS["CONFIG"]["MESTO"]:$GLOBALS["CONFIG"]["URAD"]." ".$GLOBALS["CONFIG"]["MESTO"]);
    if (is_numeric($xxx->Record["ODESL_ULICE"])) {
      $ODESILATEL.=  $oddelovac.$so;
    }
    $ODESILATEL.= $oddelovac.$xxx->Record["ODESL_PRIJMENI"].''.(trim($xxx->Record["ODESL_JMENO"])<>''?", zprac. ".$xxx->Record["ODESL_JMENO"]:'');
  }

  If (($xxx->Record["ODES_TYP"]=="X"))
  {
    $ODESILATEL="Vnitřní dokument úřadu ".$oddelovac."odbor ".$xxx->Record["ODESL_PRIJMENI"].", zpracovatel ".$xxx->Record["ODESL_JMENO"];
   // If ($xxx->Record["JEJICH_CJ"]) $ODESILATEL=', ČJ: '.$xxx->Record["JEJICH_CJ"]." ";
  }
  If ($xxx->Record["ODES_TYP"]=="M") {$ODESILATEL=htmlentities($xxx->Record["ODESL_EMAIL"]);}


  return $ODESILATEL;
}

function Array_sort_key($pole,$klic,$smer="asc") {
  for ($i1=0; $i1<count($pole); $i1++) {
    if ($klic) $pole2[] = $pole[$i1]["$klic"];
    else $pole2[] = $pole[$i1];
  }
  sort($pole2,SORT_STRING);
  if ($smer == "desc") {
    for ($i1=count($pole2)-1; $i1>=0; $i1--) {
      $pole3[] = $pole2[$i1];
    }
    $pole2 = $pole3;
  }
  $pouzite = array();
  for ($i1=0; $i1<count($pole2); $i1++) {
    for ($i2=0; $i2<count($pole); $i2++) {
      if ($klic) {
        if ($pole[$i2]["$klic"] == $pole2[$i1]) {
          if (!in_array($i2,$pouzite)) { 
            $pole_ret[] = $pole[$i2];
            $pouzite[] = $i2;
          }
          //$pole[$i2] = false;
        }
      }
      else {
        if ($pole[$i2] == $pole2[$i1]) {
          $pole_ret[] = $pole[$i2];
          //$pole[$i2] = false;
        }
      }
      $ids[] = $pole[$i2]["id"]; 
    }
  }
  return $pole_ret;
}

function MakeStamp($val) {
  //24.08.2006 10:08:36
  $c1 = explode(" ",$val);
  $c2 =  explode(".",$c1[0]);
  $c3 =  explode(":",$c1[1]);
  //echo $c1[1]."<br />";
  if (strlen($c2[2]) == 1) $c2[2] = "0".$c2[2];
  if (strlen($c2[1]) == 1) $c2[1] = "0".$c2[1];
  if (strlen($c2[0]) == 1) $c2[0] = "0".$c2[0];
  if (strlen($c3[2]) == 1) $c3[2] = "0".$c3[2];
  if (strlen($c3[1]) == 1) $c3[1] = "0".$c3[1];
  if (strlen($c3[0]) == 1) $c3[0] = "0".$c3[0];
  $c4 = $c2[2]."".$c2[1]."".$c2[0]."".$c3[0]."".$c3[1]."".$c3[2];
  //echo $c4."<br />";
  return $c4;
}

function VratCarovyKod($id=0)
{
//  $q=new DB_POSTA;
//  $sql='select * from posta where id='.$id;
//  $q->query($sql); $q->Next_Record();
//  $res=$q->Record['SUPERODBOR']."-".str_pad($q->Record["EV_CISLO"],4,'0', STR_PAD_LEFT)."-".$q->Record["ROK"];
  $res=str_pad($id,11,'0', STR_PAD_LEFT);
  return $res;
}

?>
