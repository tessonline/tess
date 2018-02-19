<?php
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2(".admin/upload_.inc"));
include_once(FileUp2("interface/.admin/upload_funkce.inc"));

Function ChangeClassBarva($t)
// staci pustit to zaremovany a barvi se cely radek....
{
$datumpodatelnaprijeti=$GLOBALS["DATUM_PODATELNA_PRIJETI"];
$datumreferentrijeti=$GLOBALS["DATUM_REFERENT_PRIJETI"];
$datumvyrizeni=$GLOBALS["DATUM_VYRIZENI"];
$vyrizeno=$GLOBALS["VYRIZENO"];
$referent=trim($GLOBALS["REFERENT"]);
$lhuta=$GLOBALS["LHUTA"];
$stav=$GLOBALS["STAV"];
If ($lhuta==0) {$lhuta=99999999999999;}
$ODESLANA=$GLOBALS["ODESLANA_POSTA"];

$color="";
  
If ($ODESLANA=="f") 
{
$prefixsipky='prichozi';
$color="_black";
  
  If ($ODESLANA):
      $color = "_violet";
    endif;
  
  If ($datumpodatelnaprijeti<>""):
      $color = "_green";
    endif;
  
  If ($referent<>"" && $referent<>0):
      $color = "_blue";
    endif;
  
  If ($datumreferentrijeti<>"" || $GLOBALS["DATUM_VYRIZENI"]<>""):
      $color = "_black";
    endif;
  
  If (($referent=="" || $referent==0) && ($GLOBALS[ODBOR]=="" || $GLOBALS[ODBOR]==0)):
//     echo "<TR class=brow><td colspan=8 align=center><b>POZOR: Existuje písemnost, která není přiřazená nějakému odboru</b></td></tr>";
      $color = "_ruzova";
    endif;

  If ($datumvyrizeni<>"" && $GLOBALS["VYRIZENO"]<>""):
      $color = "_gray";
    endif;

  If ($stav=='2') $color="_yellow";
    $date1 =strtotime (czdate2eng($datumpodatelnaprijeti));
    $dif = floor((strtotime("now") - $date1)/86400);
    $lhuta2=$lhuta-5;

    if ($dif>$lhuta2 && !$GLOBALS["DATUM_VYRIZENI"]): $color_radek = "_red"; endif;

    if ($dif>$lhuta && !$GLOBALS["DATUM_VYRIZENI"]): $color_radek = "_red2"; endif;

    if ($GLOBALS['STATUS']==6): $color_radek = "_red2"; endif;
  //nastavime, ze pokud je to vita, tak nehlidame.... asi.
  If ($GLOBALS["CONFIG"]["VITA_VYPNOUT_TERMINY"] && ($GLOBALS["STAV"]=='2')) $color_radek="_yellow";

}
else
{
// barvy pro odeslanou postu
  $color = "_brown"; $prefixsipky='odchozi';
  $sedive=false;
   reset($GLOBALS["CONFIG"]["TYP_ODESLANI"]);  
   while (list($key,$val)=each($GLOBALS["CONFIG"]["TYP_ODESLANI"]))
   {
      If ($val['VALUE']==$GLOBALS['DOPORUCENE'] && $val['DORUCENKA']==0) $sedive=true;
   }    
   If ($GLOBALS["ODESLANA_POSTA"]=='t' && $GLOBALS["ODES_TYP"]=='X') $sedive=true;
//dsdssds

  if ($GLOBALS[VLASTNICH_RUKOU]==$GLOBALS[CONFIG][HROMADNA_OBALKA]) $sedive=true;
      
  If (($GLOBALS["DATUM_DORUCENI"]<>"") or ($sedive)):
      $color = "_gray";
    endif;

    If ($GLOBALS["STATUS"]=="11") {$color = "_black";}
}
  If ($GLOBALS["SKARTOVANO"]<>"") {$color="gray";} // skrtnute pismo.
  If ($GLOBALS["STORNOVANO"]<>"") {$color="gray";} // skrtnute pismo.

  $GLOBALS["barva_sipky"]="posta_brow".$color;
  If ($color<>'_red2' && $color<>'_red') {$color='';}
  $GLOBALS["BARVA_SIPKY"]=$prefixsipky;

  static $i=1;
  if ($i):
    $t->classname = "posta_brow".$color_radek;
    $i = 0;
  else:
    $t->classname = "posta_browdark".$color_radek;
    $i = 1;
  endif;

  If ($stav=='2') $t->classname="yellow_line";

  If ($GLOBALS["SKARTOVANO"]<>"") {$t->classname="gray_line";} // skrtnute pismo.
  If ($GLOBALS["STORNOVANO"]<>"") {$t->classname="gray_line";} // skrtnute pismo.
  If ($GLOBALS["SPISOVNA_ID"]>0) {$t->classname="posta_brow_gray";} // sedive pismo.
  $t->schema[0]['class']=$GLOBALS["barva_sipky"];
  


}


Function Ukaz($STAV)
{
  If ($STAV=='t') 
  {$res="<img src=\"".GetAgendaPath('POSTA',true,false)."/images/odchozi.gif\" alt=\"Odchozí dokument\">";}
  else {$res="<img src=\"".GetAgendaPath('POSTA',true,false)."/images/prichozi.gif\" alt=\"Příchozí dokument\">";}
  If ($GLOBALS[ODES_TYP]=='Z') {$res="<img src=\"".GetAgendaPath('POSTA',true,false)."/images/bod.gif\" alt=\"Vlastní záznam\">";}
  return $res;
}

Function Ukaz2($UZIVATEL,$zpusob=0,$doruceni=0)
{
switch ($UZIVATEL) {
  case "P": 
       $soubor='images/fabrika.gif';$text='Právnická osoba';
       break;
  case "U": 
       $soubor='images/fabrika.gif';$text='Úřad';
       break;
  case "F": 
       $soubor='images/house.gif';$text='Fyzická osoba-podnikatel';
       break;
  case "N": 
       $soubor='images/house.gif';$text='Notář';
       break;
  case "B": 
       $soubor='images/house.gif';$text='Advokát';
       break;
  case "E": 
       $soubor='images/house.gif';$text='Exekutor';
       break;
  case "T": 
       $soubor='images/house.gif';$text='Patentový zástupce';
       break;
  case "D": 
       $soubor='images/house.gif';$text='Daňový poradce';
       break;
  case "O": 
       $soubor='images/people.gif';$text='Fyzická osoba-občan';
       break;
  case "A": 
       $soubor='images/people_no.gif';$text='Anonym';
       break;
  case "V": 
       $soubor='images/rodina.gif';$text='Veřejnost';
       break;
  case "Z": 
       $soubor='images/select.gif';$text='Vlastní záznam';
       break;
  case "X": 
       $soubor='images/two_people.gif';$text='Vnitřní pošta';
       break;
  case "S": 
       $soubor='images/reload.gif';$text='Vnitřní pošta';
       break;
  case "M": 
       $soubor='images/email.gif';$text='E-mail';
       break;
  }
  if ($GLOBALS[CISLO_SPISU1]<0 || !$GLOBALS[CISLO_SPISU1]) $url="<a href='brow.php?show_id=".$GLOBALS[ID]."'>";
  if ($zpusob==3 || $doruceni==9 || $doruceni==5)
    $res="<img src='".FileUpUrl('images/email.gif')."' title='zpracováno elektronicky' border=\"0\">&nbsp;".$url."<img src=\"".FileUp2($soubor)."\" title=\"$text\" border=\"0\"></a>";
  else
    $res=$url."<img src=\"".GetAgendaPath('POSTA',true,false).'/'.$soubor."\" title=\"$text\" border=\"0\"></a>";
  return $res;    
}

Function UkazOdpoved($id)
{
  If ( $GLOBALS["STAV"]<>"2" && $GLOBALS["SPIS_VYRIZEN"]=="" && $GLOBALS[ODBOR]<>'' && $GLOBALS[REFERENT]>0)
  {
    If ($GLOBALS["CONFIG"]["VNITRNI_POSTA"])
      $res="<a href=\"javascript:newfrom(".$id.",'t')\"><img src=\"".FileUp2('images/two_people.gif')."\" border=\"0\" title=\"Poslat jako vnitřní poštu\"></a>&nbsp;";

    If ($GLOBALS["CONFIG"]["PREDANI_KOLEGOVI"])
      $res="<a href=\"javascript:newfrom(".$id.",'t')\"><img src=\"".FileUp2('images/two_people.gif')."\" border=\"0\" title=\"Předat kopii kolegovi\"></a>&nbsp;";
    if ($GLOBALS["ODESLANA_POSTA"]<>"t")
    $res.="<a href=\"javascript:newfrom(".$id.",'f')\"><img src=\"".FileUp2('images/nova_z1.gif')."\" border=\"0\" title=\"Odpovědět mimo vnitřní poštu\"></a>";
    
  }
  else
    {$res="";}

  //sice jsme to nadefinovali, ale ted to zase budeme muset vypnout, pokud neni zapnut parametr v configu...
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
  $REFERENT = $USER_INFO["ID"]; 
  If (!HasRole('spravce')&&!$GLOBALS["CONFIG"]["VEDOUCI_ODPOVED"]&&$REFERENT<>$GLOBALS["REFERENT"])
    $res='';

  //pokud je zapnuta volba pro nutny spis, musime tlacitka opet vypnout, pokud dokument neni ve spisu
  If ($GLOBALS["CONFIG"]["ODPOVED_SPIS"] && !$GLOBALS["CISLO_SPISU1"]) $res='';

  If ($GLOBALS[STORNOVANO] || $GLOBALS[SKARTOVANO]) $res='&nbsp;';

  if (!MaPristupKDokumentu_table($GLOBALS['REFERENT'],$record_id)) $res='&nbsp;';

  return $res;
}

Function DalsiPrijemci2($id,$prijemci)
{
  If ($GLOBALS["ODESLANA_POSTA"]<>"t") {

  If ($prijemci=="") 
  {$res="<a href=\"brow.php?ID=(".$id.")\"><img src=\"".FileUp2('images/group_people_gr2.gif')."\" border=\"0\" title=\"Přidat další odesílatele\"></a>";}
      else
    {
    $pocetprijemcu=count(explode(",",$prijemci))-2;
    $res="<a href=\"brow.php?ID=(".$id.")\"><img src=\"".FileUp2('images/group_people.gif')."\" border=\"0\" title=\"Počet dalších odesílatelů: $pocetprijemcu \"></a>";}
  }
  else
    {$res="";}
//  $res=$GLOBALS["ID"];
//  $res=$GLOBALS["DALSI_PRIJEMCI"];
  
  return $res;
}


Function FormatSpis($id,$link=true,$globals=1)
{
 if ($globals<>1)
  {
    $qqq=new DB_POSTA;
    $sql='select * from posta where id='.$id;
    $qqq->query($sql);
    $pocet=$qqq->Next_Record();
    if ($pocet>0)
    {

      $GLOBALS[CISLO_SPISU1]=$qqq->Record["CISLO_SPISU1"];
      $GLOBALS[CISLO_SPISU2]=$qqq->Record["CISLO_SPISU2"];
      $GLOBALS["NAZEV_SPISU"]=$qqq->Record["NAZEV_SPISU"];
      $GLOBALS[PODCISLO_SPISU]=$qqq->Record["PODCISLO_SPISU"];
      $GLOBALS[ODBOR]=$qqq->Record["ODBOR"];
      $GLOBALS[SUPERODBOR]=$qqq->Record["SUPERODBOR"];
    
    }
  }
  $text_cislo_jednaci='&nbsp;';
  If ($GLOBALS[CISLO_SPISU1]<>0) 
  {
    $text_cisla=$GLOBALS[CISLO_SPISU1]."/".$GLOBALS[CISLO_SPISU2];
    $referent=$GLOBALS["REFERENT"]?"/".UkazUsera($GLOBALS["REFERENT"],true):'/--';
    $odbor=UkazOdbor($GLOBALS[ODBOR],true);
    $odd=UkazOdbor($GLOBALS[ODDELENI],true);
    $nadodbor_id=VratOdbor($GLOBALS["SUPERODBOR"]);
    $nadodbor=UkazOdbor($nadodbor_id,true);
/*
    if ($GLOBALS[ODES_TYP]=='X')
    {
      //je nutno zjistit puvodni odbor
      $qqq=new DB_POSTA;
      $sql='select id,superodbor,odbor,referent from posta where cislo_spisu1='.$GLOBALS[CISLO_SPISU1].' and cislo_spisu2='.$GLOBALS[CISLO_SPISU2].' order by id asc';
      $qqq->query($sql);
      $qqq->next_Record();
      $odbor=UkazOdbor($qqq->Record[ODBOR],true);
      $nadodbor=UkazOdbor(VratOdbor($qqq->Record[SUPERODBOR]),true);
    }
*/
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU1"]) $text_cislo_jednaci=$text_cisla;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU2"]) $text_cislo_jednaci=$odbor."/".$text_cisla;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU3"]) $text_cislo_jednaci=$odbor."/".$GLOBALS[CISLO_SPISU1]."/".substr($GLOBALS[CISLO_SPISU2],-2);
    
    If ($GLOBALS[PODCISLO_SPISU]<>0 && $GLOBALS[CISLO_SPISU1]<>'' && $GLOBALS[CISLO_SPISU1]<>0 && $GLOBALS[CONFIG][PODCISLO]) 
        $text_cislo_jednaci.="/".$GLOBALS[PODCISLO_SPISU];    
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU4"]) 
    {
      $text_cislo_jednaci=$GLOBALS[CISLO_SPISU1];
      if ($GLOBALS[PODCISLO_SPISU]<>0) $text_cislo_jednaci.='-'.$GLOBALS[PODCISLO_SPISU];
      $text_cislo_jednaci.='/'.$GLOBALS[CISLO_SPISU2].'-'.$GLOBALS["CONFIG"]["OZNACENI_SPIS"].'/'.$nadodbor.'/'.$odbor;
    }

    If ($GLOBALS["CONFIG"]["TVAR_CISLO_SPISU5"]) 
    {
      $text_cislo_jednaci=$GLOBALS[CISLO_SPISU1];
      //if ($GLOBALS[PODCISLO_SPISU]<>0) $text_cislo_jednaci.='-'.$GLOBALS[PODCISLO_SPISU];
      $text_cislo_jednaci=$GLOBALS["CONFIG"]["OZNACENI_SPIS"].$nadodbor.'/'.$text_cislo_jednaci.'/'.$GLOBALS[CISLO_SPISU2];
    }

    If ($GLOBALS["NAZEV_SPISU"] && !$GLOBALS["CONFIG"]["ZALOMIT_NAZEV_SPISU"]) $text_cislo_jednaci.="-".$GLOBALS["NAZEV_SPISU"];
    If ($GLOBALS["NAZEV_SPISU"] && $GLOBALS["CONFIG"]["ZALOMIT_NAZEV_SPISU"]) $text_cislo_jednaci.="<br/>".$GLOBALS["NAZEV_SPISU"];
    if ($link)
      $res="<b><a class='pages' href='".GetAgendaPath("POSTA",true,false)."/brow.php?cislo_spisu1=".$GLOBALS[CISLO_SPISU1]."&cislo_spisu2=".$GLOBALS[CISLO_SPISU2]."&doc_id=".$id."&referent=".$GLOBALS[REFERENT]."'>".$text_cislo_jednaci."</a></b>";
    else
      $res="<b>".$text_cislo_jednaci."</b>";
  }
  else  
    $res='&nbsp;';
/*
  If (($GLOBALS[PODCISLO_SPISU]<>0) and ($GLOBALS[CISLO_SPISU1]<>'') and ($GLOBALS[CISLO_SPISU1]<>0)) 
    {$res='<a class="pages" href="brow.php?cislo_spisu1='.$GLOBALS[CISLO_SPISU1].'&cislo_spisu2='.$GLOBALS[CISLO_SPISU2].'"><b>'.$GLOBALS[CISLO_SPISU1]."/".$GLOBALS[CISLO_SPISU2]."/".$GLOBALS[PODCISLO_SPISU]."</b></a> ";}
  If (($GLOBALS[PODCISLO_SPISU]==0) and ($GLOBALS[CISLO_SPISU1]<>'') and ($GLOBALS[CISLO_SPISU1]<>0))
    {$res='<a class="pages" href="brow.php?cislo_spisu1='.$GLOBALS[CISLO_SPISU1].'&cislo_spisu2='.$GLOBALS[CISLO_SPISU2].'"><b>'.$GLOBALS[CISLO_SPISU1]."/".$GLOBALS[CISLO_SPISU2]."</b></a> ";}
  If (($GLOBALS["CONFIG"]["ODBOR_SPISU"]) and ($GLOBALS[CISLO_SPISU1]<>'') and ($GLOBALS[CISLO_SPISU1]<>0)) 
    {$res='<a class="pages" href="brow.php?cislo_spisu1='.$GLOBALS[CISLO_SPISU1].'&cislo_spisu2='.$GLOBALS[CISLO_SPISU2].'&odbor_spisu='.$GLOBALS[ODBOR_SPISU].'"><b>'.$GLOBALS[CISLO_SPISU1]."/".$GLOBALS[CISLO_SPISU2]."/".$GLOBALS[ODBOR_SPISU]."</b></a> ";}
 */
  if ($GLOBALS['EXPORT_ALL_step']) $res=strip_tags($res);
  return $res;
}

Function FormatCJednaci($id,$url=true)
{
  $res='&nbsp;';
  
  If ($GLOBALS[CISLO_JEDNACI1]<>0) 
  {
    $text_cisla=$GLOBALS[CISLO_JEDNACI1]."/".$GLOBALS[CISLO_JEDNACI2];
    $referent=$GLOBALS["REFERENT"]?"/".UkazUsera($GLOBALS["REFERENT"],true):'/--';
    $odbor=UkazOdbor($GLOBALS[ODBOR],true);
    $nadodbor=UkazOdbor(VratSuperOdbor(),true);
    if ($GLOBALS[ODES_TYP]=='X')
    {
      //je nutno zjistit puvodni odbor
      $qqq=new DB_POSTA;
      $sql='select id,odbor,referent from posta where cislo_jednaci1='.$GLOBALS[CISLO_JEDNACI1].' and cislo_jednaci2='.$GLOBALS[CISLO_JEDNACI2].' order by id asc';
      $qqq->query($sql);
      $qqq->next_Record();
      $referent="/".UkazUsera($qqq->Record[REFERENT],true);
      $odbor=UkazOdbor($qqq->Record[ODBOR],true);
    }
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI1"]) $text_cislo_jednaci=$text_cisla;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI2"]) $text_cislo_jednaci=$odbor."/".$text_cisla.$referent;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI3"]) $text_cislo_jednaci=$odbor."/".$GLOBALS[CISLO_JEDNACI1]."/".substr($GLOBALS[CISLO_JEDNACI2],-2).$referent;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI4"]) $text_cislo_jednaci=$odbor."/".$text_cisla.$referent;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI4"]&&$GLOBALS["CISLO_SPISU1"]>0) $text_cislo_jednaci=$odbor."/".$text_cisla.$referent."-".$GLOBALS[CISLO_SPISU1]."/".$GLOBALS[CISLO_SPISU2];
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI5"]) $text_cislo_jednaci=$odbor."/".$text_cisla;
    If ($GLOBALS["CONFIG"]["TVAR_CISLO_JEDNACI6"]) $text_cislo_jednaci=$text_cisla."/".$odbor.$referent;

    If ($GLOBALS["CONFIG"]["CISLO_JEDNACI_PREFIX"]) $text_cislo_jednaci=$GLOBALS["CONFIG"]["CISLO_JEDNACI_PREFIX"].$text_cislo_jednaci;
    if ($GLOBALS[TEXT_CJ]) $text_cislo_jednaci=$GLOBALS[TEXT_CJ];
//    if ($GLOBALS["REFERENT"]>0 && $GLOBALS[TEXT_CJ]=='' && $GLOBALS["PROPERTIES"]["AGENDA_TABLE"]=="POSTA") ZapisCJ($GLOBALS[ID],$text_cislo_jednaci);
  
    If ($url) $res="<b><a class='pages' href='".GetAgendaPath("POSTA",true,false)."/brow.php?cislo_jednaci1=".$GLOBALS[CISLO_JEDNACI1]."&cislo_jednaci2=".$GLOBALS[CISLO_JEDNACI2]."'>".$text_cislo_jednaci."</a></b>";
    else
      $res="<b>".$text_cislo_jednaci."</b>";
   }
  if ($GLOBALS['EXPORT_ALL_step']) $res=strip_tags($res);
  return $res;
}

Function UkazJmeno()
{
  If (trim($GLOBALS["ODESL_CP"])<>'') $cislo=$GLOBALS["ODESL_CP"];
  If (trim($GLOBALS["ODESL_COR"])<>'') $cislo=$GLOBALS["ODESL_COR"];
  If (trim($GLOBALS["ODESL_COR"])<>'' && trim($GLOBALS["ODESL_CP"])<>'') $cislo=$GLOBALS["ODESL_CP"]."/".$GLOBALS["ODESL_COR"];

  If ($GLOBALS["ODES_TYP"]=="P") 
  {
    $res=$GLOBALS["ODESL_PRIJMENI"].', '; 
    If ($GLOBALS["ODESL_ICO"]<>'') {$res.='IČO <a class="pages" href="http://wwwinfo.mfcr.cz/cgi-bin/ares/ares_es.cgi?jazyk=cz&xml=1&ico='.$GLOBALS["ODESL_ICO"].'" target="ico">'.$GLOBALS["ODESL_ICO"].'</a>, ';} 
    $res.=$GLOBALS["ODESL_ULICE"].' '.$cislo.', '.$GLOBALS["ODESL_PSC"].' '.$GLOBALS["ODESL_POSTA"];
  }
  else
  {
    $res=$GLOBALS["ODESL_PRIJMENI"].' '.$GLOBALS["ODESL_JMENO"].', '; 
    If (strlen($GLOBALS["ODESL_ICO"])>2 && $GLOBALS["ODES_TYP"]=="O") {$res.='RČ '.$GLOBALS["ODESL_ICO"].', ';} 
    $res.=$GLOBALS["ODESL_ULICE"].' '.$cislo.', '.$GLOBALS["ODESL_PSC"].' '.$GLOBALS["ODESL_POSTA"];
  }
//  If ($GLOBALS["ODES_TYP"]=="O") {$res=$GLOBALS["PRIJMENI"].' '.$GLOBALS["JMENO"].', '.$GLOBALS["ULICE"].' '.$GLOBALS["CP"].', '.$GLOBALS["PSC"].' '.$GLOBALS["MESTO"];}
  If ($GLOBALS["ODES_TYP"]=="A") {$res='anonym';}
  If ($GLOBALS["ODES_TYP"]=="V") {$res='veřejnost';}
  If ($GLOBALS["ODES_TYP"]=="Z") {$res='vlastní záznam';}
  If ($GLOBALS["ODES_TYP"]=="X") {$res=$GLOBALS["ODESL_PRIJMENI"].', zprac. '.$GLOBALS["ODESL_JMENO"];}
  If ($GLOBALS["ODES_TYP"]=="S") {$res=($GLOBALS["ODESL_TITUL"]==1?"Město ".$GLOBALS["CONFIG"]["MESTO"]:$GLOBALS["CONFIG"]["URAD"]." ".$GLOBALS["CONFIG"]["MESTO"]).", ".$GLOBALS["ODESL_PRIJMENI"].''.(trim($GLOBALS["ODESL_JMENO"])<>''?", zprac. ".$GLOBALS["ODESL_JMENO"]:'');}

  If ($GLOBALS["ODES_TYP"]=="M") {$res=$GLOBALS["ODESL_EMAIL"];}

  if ($GLOBALS['ODES_TYP']=='X' && $GLOBALS['ODESLANA_POSTA']=='t')
  {
//    echo $pole."<br/>";
    $pole=explode(',',$GLOBALS["DALSI_PRIJEMCI"]);
    $ukaz_adresati=array();
    while (list($key,$val)= each($pole))
    {
//echo $val;
      list($superod,$odbor,$odd,$referent)=explode(':',$val);
      if ($superod<1)
      {
          if ($superod==-1) {$ukaz_adresati[$key]='všem ředitelům';}
          if ($superod==-2) {$ukaz_adresati[$key]='všem POI';}
      }
      else
      {
        $ukaz_adresati[$key]=VratSNazevSkupiny($superod);
        if ($odbor>0) $ukaz_adresati[$key].=", ".UkazOdbor($odbor);
        if ($odd>0) $ukaz_adresati[$key].=", ".UkazOdbor($odd);
        if ($referent>0) $ukaz_adresati[$key].=", zprac. ".UkazUsera($referent);
      }
    }
//echo "Tadz".$GLOBALS['ODES_TYP']." x ".$GLOBALS['ODESLANA_POSTA']."<br/>";
    $res=implode('<hr/>',$ukaz_adresati);
  }
  
  
  $prijemci=substr($GLOBALS["DALSI_PRIJEMCI"],1,-1);
  If (($prijemci<>"") and ($GLOBALS["ODESLANA_POSTA"]=='f') and (!strstr($prijemci,':'))) 
  {
    If ($prijemci=="Array") {$prijemci="";}
    $prijemci=substr($prijemci,1,-1);
    if ($prijemci<>'')
    $prijemci_pole=explode(',',$prijemci);
    if (count($prijemci_pole)>0)
     while (list($key_prijemce,$val_prijemce)=each($prijemci_pole))
    {
      // Dalsi odesilatele posty
  
      $res.="<hr>";
      if (eregi('X_',$val_prijemce))
        {$table_prijemci='posta'; $val_prijemce=str_replace('X_','',$val_prijemce); }
      else
        $table_prijemci='cis_posta_prijemci';
      $val_prijemce=str_replace('_','',$val_prijemce);
      $sql='select odes_typ from '.$table_prijemci.' where id='.$val_prijemce;
      $q=new DB_DEFAULT;
      $q->query($sql); $q->Next_Record();
      $res.=Ukaz2($q->Record["ODES_TYP"])." ";
            
      $res.=UkazAdresu($val_prijemce,',',$table_prijemci); 
       /*
      If (trim($q->Record["ODESL_CP"])<>'') $cislo=$q->Record["ODESL_CP"];
      If (trim($q->Record["ODESL_COR"])<>'') $cislo=$q->Record["ODESL_COR"];
      If (trim($q->Record["ODESL_COR"])<>'' && trim($q->Record["ODESL_CP"])<>'') $cislo=$q->Record["ODESL_CP"]."/".$q->Record["ODESL_COR"];
      If ($q->Record["ODES_TYP"]=="P") {$res.=$q->Record["ODESL_PRIJMENI"].', '; If ($q->Record["ODESL_ICO"]<>'') {$res.='IČO <a class="pages" href="http://wwwinfo.mfcr.cz/ares/ares_fr.html.cz?JS=1&jazyk=cz&cestina=cestina&ico='.$q->Record["ODESL_ICO"].'" target="ico">'.$q->Record["ODESL_ICO"].'</a>, ';} $res.=$q->Record["ODESL_ULICE"].' '.$cislo.', '.$q->Record["ODESL_PSC"].' '.$q->Record["ODESL_POSTA"];}
      else
      {
        $res.=$q->Record["ODESL_PRIJMENI"].' '.$q->Record["ODESL_JMENO"].', '; 
        If ($q->Record["ODESL_ICO"]<>'') {$res.='IČO <a class="pages" href="http://wwwinfo.mfcr.cz/ares/ares_fr.html.cz?JS=1&jazyk=cz&cestina=cestina&ico='.$q->Record["ODESL_ICO"].'" target="ico">'.$q->Record["ODESL_ICO"].'</a>, ';} $res.=$q->Record["ODESL_ULICE"].' '.$cislo.', '.$q->Record["ODESL_PSC"].' '.$q->Record["ODESL_POSTA"];}
        If ($q->Record["ODES_TYP"]=="A") {$res.='anonym';}   
        If ($q->Record["ODES_TYP"]=="V") {$res.='veřejnost';}
        */
    }
  }
  If (($GLOBALS["ID_PUVODNI"]=="") && ($GLOBALS["ODESLANA_POSTA"]=='t'))  $res=$res.'<br/><font size=1><b><i>dokument z vlastního podnětu</i></b></font>';
  if ($GLOBALS['EXPORT_ALL_step']) $res=strip_tags($res);
  return $res;
}

Function DatumPrijeti($datum)
{
  $res=substr($datum,0,strpos($datum," "));
  If ($res=='') $res=$datum;  
  return $res;
}
Function DatumVyrizeni($datum)
{
//  $res=substr($datum,0,strpos($datum," "));
//  If ($res=='') $res=$datum;  
  $res.="<b>".Czdate($datum)."</b>";
  return $res;
}

Function Precteno($id,$cislo_referenta)
{
  global $uplobj;
//  $res="&nbsp;";
  If (($GLOBALS["ODESLANA_POSTA"]=="f") and ($GLOBALS["DATUM_REFERENT_PRIJETI"]=="") and ($GLOBALS["DATUM_VYRIZENI"]=="") and ($GLOBALS["ODBOR"]<>''))
    $res="<a title=\"Označit jako přečtené\" href=\"javascript:newfromPrecteno(".$id.")\"><img src=\"".FileUp2('images/ok_check.gif')."\" border=\"0\" alt=\"Označit jako přečtené\"></a>";

 If ($GLOBALS["ODESLANA_POSTA"]=="t" && $GLOBALS["ODES_TYP"]=="X" && $GLOBALS["DATUM_VYPRAVENI"]=="" && !JeVeSchvaleni($GLOBALS['ID']))
    $res="<a title=\"Odeslat vnitřní poštu\" href=\"javascript:newOdesliVnitrni(".$id.")\"><img src=\"".FileUp2('images/office/mail.gif')."\" border=\"0\" alt=\"Odeslat vnitřní poštu\"></a>";
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
  $REFERENT = $USER_INFO["ID"]; 
  $OWNER_ID=$GLOBALS{'OWNER_ID'};

  //pokud neni referent, nebo pokud zaznam nezalozil...
  If (!($REFERENT==$cislo_referenta || $GLOBALS['OWNER_ID']==$REFERENT)) $res="";

/*  If ($GLOBALS["ODESLANA_POSTA"]=="t" && $GLOBALS["ODES_TYP"]=="S"  && $GLOBALS["DATUM_VYPRAVENI"]=="")
    $res="<a title=\"Odeslat interní poštu\" href=\"javascript:newOdesliInterni(".$id.")\"><img src=\"".FileUp2('images/ok_check.gif')."\" border=\"0\" alt=\"Odeslat interní poštu\"></a>";
*/
  If ($GLOBALS["CONFIG"]["VRACENI_NA_PODATELNU"] && $GLOBALS["ODESLANA_POSTA"]=="f" && $GLOBALS[ODBOR]<>'' && $GLOBALS["ID_PUVODNI"]=='' && $GLOBALS["DATUM_VYRIZENI"]=='') $res.="&nbsp;<a href=\"javascript:newfromPrecteno('".$id."&podatelna=1')\"><img src=\"".FileUp2('images/office/kniha4.gif')."\" border=\"0\" title=\"Vrátit na podatelnu\"></a>";

  If ((HasRole('podatelna')||HasRole('spravce')) && $GLOBALS["CONFIG"]["KOPIROVANI_DOKUMENTU"] && $GLOBALS["ODESLANA_POSTA"]=="f" && $GLOBALS["ODES_TYP"]<>"X") $res.='&nbsp;<a href="javascript:newZaloz(\''.$id.'\',\'2\')"><img src="'.FileUp2('images/nova_z.gif').'" border="0" title="Zkopírovat dokument s novým číslem jednacím a založit spis"></a>';

  If ($GLOBALS["CONFIG"]["TISK_RAZITKA"]  && $GLOBALS["ODESLANA_POSTA"]=="f" && $GLOBALS["DATUM_VYRIZENI"]=='' && $GLOBALS["ODES_TYP"]<>"X") $res.="&nbsp;<a href=\"javascript:newRazitko('".$id."','".$GLOBALS["ODESLANA_POSTA"]."')\">&nbsp;<img src=\"".FileUp2('images/barcode.gif')."\" border=\"0\" title=\"Tisk podacího razítka\"></a>&nbsp;";

  If ($GLOBALS["CONFIG"]["JE_EPODATELNA_AEC"]  && $GLOBALS["ODESLANA_POSTA"]=="t" && $GLOBALS["DATUM_VYPRAVENI"]=='' && $GLOBALS["ODES_TYP"]=='M'  && $GLOBALS["VLASTNICH_RUKOU"]=='5') $res.="&nbsp;<a href=\"javascript:newEmail('".$id."','aec')\"><img src=\"".FileUp2('images/email.gif')."\" border=\"0\" title=\"Odeslat email okamžitě\"></a>";
  If ($GLOBALS["CONFIG"]["INTERNI_EPODATELNA"]  && $GLOBALS["ODESLANA_POSTA"]=="t" && $GLOBALS["DATUM_VYPRAVENI"]=='' && $GLOBALS["ODES_TYP"]=='M'  && $GLOBALS["VLASTNICH_RUKOU"]=='5') $res.="&nbsp;<a href=\"javascript:newEmail('".$id."','epodatelna')\"><img src=\"".FileUp2('images/email.gif')."\" border=\"0\" title=\"Odeslat email okamžitě\"></a>";

//  if (($GLOBALS['VLASTNICH_RUKOU']==9 || $GLOBALS[CONFIG][INTERNI_POSTA]==$GLOBALS['VLASTNICH_RUKOU']) && $GLOBALS[ODESLANA_POSTA]=='t' && !$GLOBALS[DATUM_VYPRAVENI])
  if ($GLOBALS[ODESLANA_POSTA]=='t' && !$GLOBALS[DATUM_VYPRAVENI])
  {
    $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
    $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($GLOBALS[ID]); 
    $vykricnik=true;
    while (list($key,$val)=each($upload_records))
    {
      if (strpos($val[NAME],'.pdf') || strpos($val[NAME],'.PDF')) 
      {
        $podpis=true;
        if ($GLOBALS['CONFIG']['KONTROLA_EL_PODPISU_ONLINE'])
        {
          if (JePodepsanyDokument($val)) $vykricnik=false; //zkontrolujeme podpis online primo v souboru
        }
        else
        {
          if (eregi('el. podepsano',$val['DESCRIPTION'])) $vykricnik=false; //pseudo kontrola, jestli je v description text o el. podpisu
        }
      }
    }
    if (count($upload_records)>0) $odeslat=true;
    if ($podpis)  $res.="<a title=\"Podepsat\" href=\"javascript:newPodepsani(".$id.")\"><img src=\"".FileUp2('images/access3.gif')."\" border=\"0\" alt=\"Podepsat dokument\"></a>";
    if ($podpis && $vykricnik)  $res.="<img src=\"".FileUp2('images/alert.gif')."\" border=\"0\" title=\"ani jeden PDF dokument není podepsán\">";
    //$res.='&nbsp;&nbsp;&nbsp;<a href="javascript:newDS('.$id.')" title="Odeslat datovou zprávu okamžitě"><img src="'.FileUp2('images/office/mail.gif').'" border=0></a>';
    if ($GLOBALS["KONEKTOR"]["DS"]["UREDNIK_MUZE_ODESLAT"] && $odeslat && $GLOBALS['ODESL_DATSCHRANKA']) $res.='&nbsp;&nbsp;&nbsp;<a href="javascript:newDS('.$id.')" title="Odeslat datovou zprávu okamžitě"><img src="'.FileUp2('images/office/mail.gif').'" border=0></a>';
    $res.='&nbsp;&nbsp;&nbsp;<a href="javascript:newVedouci('.$id.')">'.VratImgKeSchvalovani($GLOBALS['ID']).'</a>';
//    $res.='&nbsp;&nbsp;&nbsp;<a href="javascript:newVedouci('.$id.')"><img src="images/externist.gif" title="Schvalovací proces"></a>';
  }

/*
  If ($GLOBALS['cislo_spisu1']) 

  {
    //tak jsme v prehledu dokumentu ve spisu, tak vyhodime tlacitko, aby se zmenil parametr...
    If ($GLOBALS[PREHLED_SPIS]==1) $href="<a href=\"javascript:newfromPrecteno('".$id."&spis=1&stav=0')\"><img src=\"".FileUp2('images/spis_ok.gif')."\" border=\"0\" alt=\"Dokument je ve spisovém přehledu. Kliknutím nastavíte, že nebude v přehledu\"></a>"; 
    If ($GLOBALS[PREHLED_SPIS]==0) $href="<a href=\"javascript:newfromPrecteno('".$id."&spis=1&stav=1')\"><img src=\"".FileUp2('images/spis_ko.gif')."\" border=\"0\" alt=\"Dokument není ve spisovém přehledu. Kliknutím nastavíte, že bude v přehledu\"></a>"; 
    $res=$href;

  }
*/
  If ($GLOBALS[STORNOVANO] || $GLOBALS[SKARTOVANO]) $res='&nbsp;';
  If ($GLOBALS[SPIS_VYRIZEN]) $res='&nbsp;';
//  if (!MaPristupKDokumentu_table($GLOBALS['REFERENT'],$record_id) && !in_array($GLOBALS['ID'],explode(',',SeznamKeSchvaleni($REFERENT)))) $res='&nbsp;';
  return $res;
}

Function Ukazvmape($id)
{
  $res="&nbsp;";
  If (($GLOBALS["OKRES_KOD"]=="3714") and ($id<>""))
  $res="<a href=\"https://mapy.nmnm.cz/tms/munmnm_cp/index.php?client_type=map_resize&strange_opener=0&interface=tmv&Values=".$id."&Theme=staveb_objekty&client_lang=cz_utf-8&cacheID=1079938337250\" target='munmnm_cp'><img src=\"".FileUp2('images/globe.gif')."\" border=\"0\" alt=\"Ukázat v mapě\"></a>";
  return $res;
}

function ShowMapADR($objekt_kod,$typ=1) {
  if ($typ == 2) return "&nbsp;";
  static $img;
  if (!$img)
    $img = FileUp_Main("images/globe.gif","OBYVATELE");
  If ($objekt_kod)
  $res = "<a href=\"map.php?Values=".$objekt_kod."\" target=\"map_link\"><img alt=\"Mapa\" src=\"".$img."\" border=\"0\"></a>";
	else
	$res="";
  return $res;
}

Function ExistujeSoubor($id,$cj1,$cj2)
{
  $cesta=$GLOBALS["TMAPY_DIR"]."/".$GLOBALS["CONFIG"]["VLASTNI_UPLOAD_VNITRNI"];
  $cela_cesta=$cesta."/".$cj2."/".$cj1;
  $nazev_souboru=md5($cj2.$cj1);
  $celeunc=$cela_cesta."/".$nazev_souboru.".rtf";

  $cesta="output/doc/send_to_word.php?ID=$id&sablona=odpoved";
  $cesta2="output/doc/konvert.php?ID=$id&cj1=$cj1&cj2=$cj2";
  if (file_exists($celeunc))  
  {
    $res="<a href=\"$cesta\" target=\"ifrm_get_value\"><img src=\"".FileUp2('images/wordicon.gif')."\" border=0 alt='Otevřít existující dokument'></a>&nbsp;";
    $res.="<a onclick='javascript:window.open(\"$cesta2\")' href='#' target=\"ifrm_get_value\"><img src=\"".FileUp2('images/automat.gif')."\" border=0 alt='Převést existující dokument do PDF a uložit do uploadu'></a>";
  }
  else
    $res="&nbsp;";
  return $res;
}
 
function DatumCZ($val) {
  //24.08.2006 10:08:36
  $c2 = explode("-",$val);
  $c2[0] *= 1;
  $c2[1] *= 1;
  $c2[2] *= 1;
  $c4 = $c2[2].".".$c2[1].".".$c2[0];
  //echo $c4."<br />";
  return $c4;
}

function Ukol($id)
{
  // pro evidenci ukolu
/*  $q=new DB_DEFAULT;
  $sql='select (CURRENT_DATE - (datum_vznik+termin_dny)) as termin,stav from ukoly where dokument_id='.$id;
  $q->query($sql);
  $pocet=$q->Num_Rows();
*/  
  If ($pocet==0) $res='<a href="'.GetAgendaPath('UKOLY',true,false).'/edit.php?insert&DOKUMENT_ID='.$id.'&TERMIN_DNY='.($GLOBALS["LHUTA"]?$GLOBALS["LHUTA"]:30).'" target="ukoly"><img src="'.$img=GetAgendaPath('UKOLY',true,false).'/../images/ukol_cerny.gif" border=0 alt="Založit nový úkol"></a>';
  else
  {
    //neni uz nahodou ukol vyresen?
    $q->Next_Record();
    If ($q->Record["STAV"]==2) 
    {
      $img='<img src="'.$img=GetAgendaPath('UKOLY',true,false).'/../images/ukol_sedy.gif" border=0 alt="Úkol je již vyřešen!">';
    }
    else
    {
       //neni, tak jdeme zjistit stav ukolu
      $zbyva=$q->Record["TERMIN"];
      $img='';
      If ($zbyva<(-5)) $img='<img src="'.$img=GetAgendaPath('UKOLY',true,false).'/../images/ukol_zeleny.gif" border=0 alt="Úkol je v řešení">'; 
      If ($zbyva>(-6) && ($zbyva<0)) $img='<img src="'.$img=GetAgendaPath('UKOLY',true,false).'/../images/ukol_zluty.gif" border=0 alt="Úkol je v řešení,ale zbývá pouze 5 dnů do konce lhůty!">';
      If ($zbyva>=0) $img='<img src="'.$img=GetAgendaPath('UKOLY',true,false).'/../images/ukol_cerveny.gif" border=0 alt="Úkol je v řešení,ale JE PŘEKROČENA LHŮTA!">';
    }
    
    $res='<a title="Evidence úkolů" href="'.GetAgendaPath('UKOLY',true,false).'/brow.php?filter&DOKUMENT_ID='.$id.'" target="ukoly">'.$img.'</a>';
  }
  return $res;
}

function FormatujVec($vec)
{
  return str_replace(",",", ",$vec);
}

Function GetDocs_UPLOAD($id)
{
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id); 
  while (list($key,$val)=each($upload_records))
  {
    $res.='<a href=# onclick="return EditShowAtt(event,'.$val[ID].',\'ifrm_doc\');" target="ifrm_doc" class="pages">';
    $res.=$val[NAME]."</a><br/>";
//    if (strpos($val[NAME],'.pdf')) $podpis=true; 
//    if (!JePodepsanyDokument($val)) $vykricnik=true;
  }
  return $res;

}

function AnoNe($cislo)
{
  $res='&nbsp;';
  if ($cislo==1) $res='Ano';
  if ($cislo==2) $res='<b>Ne</b>';
  if ($cislo==3) $res='Podepsáno';
  return $res;
}

Function ShowUploadPosta($record_id=0)
{
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  if ($record_id<0 || $record_id=='') return '&nbsp;';
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($record_id);
  $pocet=count($upload_records);
  if ($pocet==0) $img='folder_empty'; else $img='folder_full'; 
//  $res='<a href="javascript:upload_KVP_AKCE('.$id_akce.')" class="image" title="('.$pocet.')"><img src="'.FileUp2('images/'.$img.'.gif').'" border="0"></a>';
  $res='<a href="#" onclick="upload_('.$record_id.')" class="image" title="('.$pocet.')"><img src="/'.FileUp2('images/'.$img.'.gif').'" border="0"></a>';

//  if (!MaPristupKDokumentu_table($GLOBALS['REFERENT'],$record_id)) $res='&nbsp;';
  return $res;
} 

Function UkazTableOdbor($odbor)
{

  //$res="ACC".UkazOdbor($odbor,'true')."AAB";
  $res=UkazOdbor($odbor,'true');
  return $res;
}

Function UkazZpracovatele($user)
{
  if ($user > 0) {
    $res=UkazUsera($user);
  
    $qq = new DB_POSTA;
    $sql = "select * from posta where odeslana_posta ='f' and id_puvodni = ".$GLOBALS['ID'];
    $qq->query($sql);
    while ($qq->next_Record()) {
      $res.="<br/>".UkazUsera($qq->Record[REFERENT]);
     }
  } else {
    $res = '&nbsp;';
  }
  
  return $res;
}

if (!$GLOBALS['EXPORT_ALL_step']) 
{
  echo "<script>\n";
  echo "<!--\n";
  echo "  function newfrom(id,vnitrni) {\n";
  echo "  newwindow = window.open('edit.php?insertfrom&EDIT_ID='+id+'&vnitrni='+vnitrni, 'agenda_nova', 'height=650,width=860,scrollbars,resizable');\n";
  echo "  newwindow.focus();\n";
  echo "  }\n";
  echo "  function newPodepsani(id) {\n";
  echo "  newwindow = window.open('./interface/podepsani602/edit.php?edit&EDIT_ID='+id+'&cacheid=', 'agenda_nova', 'height=500,width=650,scrollbars,resizable');\n";
  echo "  newwindow.focus();\n";
  echo "  }\n";
  echo "  function newfromPrecteno(id) {\n";
  echo "  newwindow = window.open('./services/spisovka/precteno.php?ID='+id, 'agenda_nova', 'height=5,width=5,scrollbars=0,resizable=0');\n";
  echo "  newwindow.focus();\n";
  echo "  }\n";
  echo "  function newOdesliInterni(id) {\n";
  echo "  newwindow = window.open('./services/spisovka/odesli.php?ID='+id, 'agenda_nova', 'height=5,width=5,scrollbars=0,resizable=0');\n";
  echo "  newwindow.focus();\n";
  echo "  }\n";
  echo "  function newOdesliVnitrni(id) {\n";
  echo "  newwindow = window.open('./services/spisovka/send_vnitrni.php?EDIT_ID='+id+'&send_vnitrni=1', 'agenda_nova', 'height=5,width=5,scrollbars=0,resizable=0');\n";
  echo "  newwindow.focus();\n";
  echo "  }\n";
  echo "  function newRazitko(id,typ) {\n";
  echo "  newwindow = window.open('services/barcode/razitko/edit.php?insert&ID='+id+'&ODESLANA='+typ, 'razitko', 'height=500,width=500,scrollbars,resizable');\n";
  echo "  newwindow.focus();\n";
  echo "  }\n";
  echo "  function newDS(id) {\n";
  echo "  if (confirm('Chcete skutečně danou zprávu odeslat do datové schránky příjemce?\\n\\nPokračovat?')){ "; 
  echo "  newwindow = window.open('interface/DS/send.php?user=1&ID_ODCHOZI='+id, 'email', 'height=500,width=500,scrollbars,resizable');\n";
  echo "  newwindow.focus(); }\n";
  echo "  }\n";
  echo "  function newZaloz(id,zalozeni) {\n";
  echo "  if (confirm('Chcete skutečně založit nové číslo jednací a sloučit ho do spisu s tímto číslem jednacím?\\n\\nPokračovat?')){ "; 
  echo "  newwindow = window.open('zaloz.php?ID='+id+'&zalozeni='+zalozeni, 'ifrm_get_value', 'height=500,width=500,scrollbars,resizable');\n";
  echo "  newwindow.focus(); }\n";
  echo "  }\n";
  echo "  function newVedouci(id) {\n";
  echo "  newwindow = window.open('services/spisovka/schvaleni/edit.php?insert&POSTA_ID='+id, 'schvaleni', 'height=500,width=650,scrollbars,resizable');\n";
  echo "  newwindow.focus();\n";
  echo "  }\n";
  echo "  function newEmail(id,typ) {\n";
  echo "  if (!confirm('Chcete skutečně daný email odeslat?\\n\\nPokračovat?')){return(false)}; "; 
  echo "  newwindow = window.open('interface/'+typ+'/odeslat.php?ID='+id, 'email', 'height=500,width=500,scrollbars,resizable');\n";
  echo "  newwindow.focus();\n";
  echo "  }\n";
  echo "
    function NewWindowUpload(script) {
      if (window.name == 'upload') {
        window.location.href = script;
      } else {
        newwindow = window.open(script, 'upload','height=500,width=760,left=20,top=20,scrollbars,resizable');
        newwindow.focus();
      }
    }
    function upload_(id) {
      NewWindowUpload('/ost/posta/ug_file.php?FULLTEXT_UPLOAD=&RECORD_ID='+id+'&cacheid=');
    }
  ";
  echo "//-->\n";
  echo "</script>\n";

}
?>
