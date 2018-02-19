<?php
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2(".admin/upload_.inc"));
include_once(FileUp2(".admin/has_access.inc"));
include_once(FileUp2("plugins/schvalovani/.admin/schvalovani.inc"));
include_once(FileUp2("interface/.admin/upload_funkce.inc"));

$GLOBALS['USER_INFO'] = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();


Function Ukaz($STAV) {
  switch($GLOBALS['STATUS']) {
    case '1':
      $color = 'silver';
      break;
    case '2':
      $color = 'green';
      break;
    case '3':
      $color = 'blue';
      break;
    case '4':
      $color = 'black';
      break;
    case '5':
      $color = '-moz-linear-gradient(right, yellow, #CCCCCC); background: -webkit-linear-gradient(right, yellow, #CCCCCC); background-image:-ms-linear-gradient(right, yellow, #CCCCCC);';
      break;
    case '6':
      $color = 'red';
      break;
    case '7':
      $color = 'orange';
      break;
    case '8':
      $color = 'violet';
      break;
    case '11':
      $color = 'black';
      break;
    case '12':
      $color = 'violet';
      break;
    default:
      $color = 'silver';
      break;

  }
  If ($STAV=='t')
  {$res = "<img src=\"" . FileUpImage('images/back') . "\" title=\"Odchozí dokument\" style=\"background:".$color.";\" width=\"40\">";}
  else {
    $t = FileUpImage('images/forward');
    $res = "<img src=\"" . FileUpImage('images/forward') . "\" title=\"Příchozí dokument\" style=\"background:".$color.";\" width=\"40\">";
  }
  If ($GLOBALS[ODES_TYP]=='Z') {
    $res = "<img src=\"" . FileUpImage('images/radiobtn-checked') . "\" title=\"Vlastní záznam\" style=\"background:".$color.";\" width=\"40\">";
  }
  return $res;

}

Function Ukaz2($UZIVATEL,$zpusob=0,$doruceni=0) {
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
  case "M":
       $soubor='images/email.gif';$text='E-mail';
       break;
  }
  if ($GLOBALS[CISLO_SPISU1]<0 || !$GLOBALS[CISLO_SPISU1]) $url="<a href='brow.php?show_id=".$GLOBALS[ID]."'>";
   if (($zpusob==3 && $GLOBALS['ODESLANA_POSTA']=='f')  || $doruceni==5  || $GLOBALS['ODES_TYP']=='S')
    	//$res="<img src='/ost/posta/" . FileUpImage('images/email') ." ' title='zpracováno elektronicky' border=\"0\">";
    	$res="<img src=\"/ost/posta/images/email.gif\" title='zpracováno elektronicky' border=\"0\">";
    	if ($doruceni==9 )
		$res="<img src='/ost/posta/" . FileUpImage('images/dz') ." ' title='datová zpráva' height=\"16\" border=\"0\">";
 		//$res="<img src=\"/ost/posta/images/dz.gif\" title='datová zpráva' height=\"16\" border=\"0\">";
		
    
  if ($GLOBALS['ODES_TYP']=='S')
    $res="<img src=\"/ost/posta/images/chain.gif\" title='Interní dokument' border=\"0\">";
  //$res="<img src='/ost/posta/" . FileUpUrl('images/chain.gif') ." ' title='Interní dokument' border=\"0\">";
    //    $res="<img src='".FileUpUrl('images/email.gif')."' title='zpracováno elektronicky' border=\"0\">&nbsp;".$url."<img src=\"".FileUp2($soubor)."\" title=\"$text\" border=\"0\"></a>";
//    $res=$url."<img src=\"".GetAgendaPath('POSTA',true,false).'/'.$soubor."\" title=\"$text\" border=\"0\"></a>";
  //if ($soubor) $res .= "<img src=\"".GetAgendaPath('POSTA',true,false).'/'.$soubor."\" title=\"$text\" border=\"0\"></a>";

  if ($soubor) $res .= "<img src=\"/ost/posta/".$soubor."\" title=\"$text\" border=\"0\"></a>";
  return $res;
}

Function UkazOdpoved($id) {
  global $USER_INFO;
  If ( $GLOBALS["STAV"]<>"2" && $GLOBALS["SPIS_VYRIZEN"]=="" && $GLOBALS[ODBOR]<>'' && $GLOBALS[REFERENT]>0) {
    if ($GLOBALS["ODESLANA_POSTA"]<>"t")
    $res.="<a href=\"javascript:newfrom(".$id.",'f')\"><img src=\"" .  FileUpImage('images/file') . "\" border=\"0\" title=\"Odpovědět\"></a>";

  }
  else
    {$res="";}

  if ($GLOBALS["ODESLANA_POSTA"]=="t" && $GLOBALS['STATUS']>1) {
    $res = "<a href=\"javascript:newfrom(".$id.",'f&add_adresat=1')\"><img src=\"".FileUpImage('images/whatever')."\" border=\"0\" title=\"Přidat další vypravení dokumentu\"></a>";
  }

  //sice jsme to nadefinovali, ale ted to zase budeme muset vypnout, pokud neni zapnut parametr v configu...
  $REFERENT = $USER_INFO["ID"];
  If (!HasRole('spravce')&&!$GLOBALS["CONFIG"]["VEDOUCI_ODPOVED"]&&$REFERENT<>$GLOBALS["REFERENT"])
    $res='';

  //pokud je zapnuta volba pro nutny spis, musime tlacitka opet vypnout, pokud dokument neni ve spisu
  If ($GLOBALS["CONFIG"]["ODPOVED_SPIS"] && !$GLOBALS["CISLO_SPISU1"]) $res='';
  if (!MaPristupKDokumentu_table($GLOBALS['REFERENT'],$record_id)) $res='&nbsp;';

  If ($GLOBALS[STORNOVANO] || $GLOBALS[SKARTOVANO]) $res='&nbsp;';
  if ($GLOBALS['KOPIE'] == 1) $res = '';
  IF ($GLOBALS['STATUS']<2) $res = '&nbsp;';

  return $res;
}

Function UkazVnitrniPostu($id) {
  global $USER_INFO;
  If ( $GLOBALS["STAV"]<>"2" && $GLOBALS["SPIS_VYRIZEN"]=="" && $GLOBALS[ODBOR]<>'' && $GLOBALS[REFERENT]>0) {
    If ($GLOBALS["CONFIG"]["VNITRNI_POSTA"])
      $res="<a href=\"javascript:newfrom(".$id.",'t')\"><img src=\"" .  FileUpImage('images/people-2') . "\" border=\"0\" title=\"Poslat jako vnitřní poštu\"></a>";

    If ($GLOBALS["CONFIG"]["PREDANI_KOLEGOVI"])
      $res="<a href=\"javascript:newfrom(".$id.",'t')\"><img src=\"" .  FileUpImage('images/people-2') . "\" border=\"0\" title=\"Předat kopii kolegovi\"></a>";
  }
  else
    {$res="";}

  //sice jsme to nadefinovali, ale ted to zase budeme muset vypnout, pokud neni zapnut parametr v configu...
  $REFERENT = $USER_INFO["ID"];
  If (!HasRole('spravce')&&!$GLOBALS["CONFIG"]["VEDOUCI_ODPOVED"]&&$REFERENT<>$GLOBALS["REFERENT"])
    $res='';

  //pokud je zapnuta volba pro nutny spis, musime tlacitka opet vypnout, pokud dokument neni ve spisu
  If ($GLOBALS["CONFIG"]["ODPOVED_SPIS"] && !$GLOBALS["CISLO_SPISU1"]) $res='';

  if (!MaPristupKDokumentu_table($GLOBALS['REFERENT'],$record_id)) $res='&nbsp;';

  If ($GLOBALS[STORNOVANO] || $GLOBALS[SKARTOVANO]) $res='&nbsp;';

  return $res;
}

Function DalsiPrijemci2($id,$prijemci) {
  If ($GLOBALS["ODESLANA_POSTA"]<>"t") {

  If ($prijemci=="") {
    $res="<a href=\"brow.php?ID=(".$id.")\"><img src=\"".FileUp2('images/group_people_gr2.gif')."\" border=\"0\" title=\"Přidat další odesílatele\"></a>";
  }
  else {
    $pocetprijemcu=count(explode(",",$prijemci))-2;
    $res="<a href=\"brow.php?ID=(".$id.")\"><img src=\"".FileUp2('images/group_people.gif')."\" border=\"0\" title=\"Počet dalších odesílatelů: $pocetprijemcu \"></a>";}
  }
  else {
    $res="";
  }
  
  return $res;
}


Function UkazJmeno() {
  If (trim($GLOBALS["ODESL_CP"])<>'') $cislo=$GLOBALS["ODESL_CP"];
  If (trim($GLOBALS["ODESL_COR"])<>'') $cislo=$GLOBALS["ODESL_COR"];
  If (trim($GLOBALS["ODESL_COR"])<>'' && trim($GLOBALS["ODESL_CP"])<>'') $cislo=$GLOBALS["ODESL_CP"]."/".$GLOBALS["ODESL_COR"];

  If ($GLOBALS["ODES_TYP"]=="P") {
    $res=$GLOBALS["ODESL_PRIJMENI"].', ';
    If ($GLOBALS["ODESL_ICO"]<>'') {$res.='IČO <a class="pages" href="http://wwwinfo.mfcr.cz/cgi-bin/ares/ares_es.cgi?jazyk=cz&xml=1&ico='.$GLOBALS["ODESL_ICO"].'" target="ico">'.$GLOBALS["ODESL_ICO"].'</a>, ';}
    $res.=$GLOBALS["ODESL_ULICE"].' '.$cislo.', '.$GLOBALS["ODESL_PSC"].' '.$GLOBALS["ODESL_POSTA"];
  }
  else {
    $res = '';
    If ($GLOBALS["ODESL_TITUL"]) $res .= $GLOBALS["ODESL_TITUL"]." ";
    $res .= $GLOBALS["ODESL_PRIJMENI"].' '.$GLOBALS["ODESL_JMENO"];
    If ($GLOBALS["ODESL_TITUL_ZA"]) $res .= " ".$GLOBALS["ODESL_TITUL_ZA"];
    $res .= ', ';
    //    If (strlen($GLOBALS["ODESL_ICO"])>2 && $GLOBALS["ODES_TYP"]=="O") {$res.=' '.$GLOBALS["ODESL_ICO"].', ';}
    $res .= $GLOBALS["ODESL_ULICE"].' '.$cislo.', '.$GLOBALS["ODESL_PSC"].' '.$GLOBALS["ODESL_POSTA"];
  }
//  If ($GLOBALS["ODES_TYP"]=="O") {$res=$GLOBALS["PRIJMENI"].' '.$GLOBALS["JMENO"].', '.$GLOBALS["ULICE"].' '.$GLOBALS["CP"].', '.$GLOBALS["PSC"].' '.$GLOBALS["MESTO"];}
  If ($GLOBALS["ODESL_STAT"]<>'') $res.=', '.$GLOBALS["ODESL_STAT"];
  If ($GLOBALS["ODESL_JINE"]<>'') $res.=', '.$GLOBALS["ODESL_JINE"];

  If ($GLOBALS["ODES_TYP"]=="A") {$res='anonym';}
  If ($GLOBALS["ODES_TYP"]=="V") {$res='veřejnost';}
  If ($GLOBALS["ODES_TYP"]=="Z") {$res='vlastní záznam';}
  If ($GLOBALS["ODES_TYP"]=="X") {$res=$GLOBALS["ODESL_PRIJMENI"].', zprac. '.$GLOBALS["ODESL_JMENO"];}
//  If ($GLOBALS["ODES_TYP"]=="S") {$res=($GLOBALS["ODESL_TITUL"]==1?"Město ".$GLOBALS["CONFIG"]["MESTO"]:$GLOBALS["CONFIG"]["URAD"]." ".$GLOBALS["CONFIG"]["MESTO"]).", ".$GLOBALS["ODESL_PRIJMENI"].''.(trim($GLOBALS["ODESL_JMENO"])<>''?", zprac. ".$GLOBALS["ODESL_JMENO"]:'');}
  If ($GLOBALS["ODES_TYP"]=="S") {
    if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) {
      if ($GLOBALS['ODESLANA_POSTA'] == 't') {
        $res = EedTools::VratNazevSuperOdbor(EedTools::NajdiSuperOdborId($GLOBALS["ODESL_ULICE"])).', '.$GLOBALS["ODESL_PRIJMENI"].''.(trim($GLOBALS["ODESL_JMENO"])<>''?", zprac. ".$GLOBALS["ODESL_JMENO"]:'');
      }
      else
//        $res = EedTools::VratNazevSuperOdbor($GLOBALS["SUPERODBOR"]).', '.$GLOBALS["ODESL_PRIJMENI"].''.(trim($GLOBALS["ODESL_JMENO"])<>''?", zprac. ".$GLOBALS["ODESL_JMENO"]:'');
        $res = EedTools::VratNazevSuperOdbor(EedTools::NajdiSuperodborzIDPUVODNI($GLOBALS["ID_PUVODNI"])).', '.$GLOBALS["ODESL_PRIJMENI"].''.(trim($GLOBALS["ODESL_JMENO"])<>''?", zprac. ".$GLOBALS["ODESL_JMENO"]:'');

    }
    else
      $res = $GLOBALS["ODESL_PRIJMENI"].''.(trim($GLOBALS["ODESL_JMENO"])<>''?", zprac. ".$GLOBALS["ODESL_JMENO"]:'');
  }

  If ($GLOBALS["ODES_TYP"]=="M") {$res=htmlentities($GLOBALS["ODESL_EMAIL"]);}

  if ($GLOBALS['ODES_TYP']=='X' && $GLOBALS['ODESLANA_POSTA']=='t') {
   $ukaz_adresati = array();
    $vnitrObj = LoadClass('EedVnitrniPosta', $GLOBALS['ID']);

    $adresati = $vnitrObj->VratSeznamVnitrnichAdresatu($vnitrObj->adresati);
    foreach($adresati as $key => $adresat) {
      $ukaz_adresati[$key] = $adresat['ZARIZENI_NAME'];
      if ($adresat['UNIT_ID'] > 0 && $adresat['UNIT_ID'] <> $adresat['ZARIZENI_ID']) $ukaz_adresati[$key] .= ', '. $adresat['UNIT_NAME'];
      if ($adresat['ZPRACOVATEL_ID'] > 0) $ukaz_adresati[$key] .= ', zprac. ' . $adresat['ZPRACOVATEL_NAME'];

    }
    if (count($ukaz_adresati)>0) $res = implode('<hr/>',$ukaz_adresati); else $res = '&nbsp;';
  }


  $prijemci=substr($GLOBALS["DALSI_PRIJEMCI"],1,-1);
  If (($prijemci<>"") and ($GLOBALS["ODESLANA_POSTA"]=='f') and (!strstr($prijemci,':')))  {
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
  If (($GLOBALS["MAIN_DOC"]=="1") && ($GLOBALS["ODESLANA_POSTA"]=='t'))  $res=$res.'<br/><font size=1><b><i>dokument z vlastního podnětu</i></b></font>';
  if ($GLOBALS['EXPORT_ALL_step']) $res=strip_tags($res);
  if ($GLOBALS['STATUS'] == -1) $res = '<strike>' . $res  . '</strike>';
  return $res;
}

Function DatumPrijeti($datum) {
  $res=substr($datum,0,strpos($datum," "));
  If ($res=='') $res=$datum;  
  $res = Czdate($res);
  if ($GLOBALS['STATUS'] == -1) $res = '<strike>' . $res  . '</strike>';
  return $res;
}
Function DatumVyrizeni($datum) {
//  $res=substr($datum,0,strpos($datum," "));
//  If ($res=='') $res=$datum;  
  $res.="<b>".Czdate($datum)."</b>";
  return $res;
}

Function Precteno($id,$cislo_referenta) {
  global $USER_INFO;
  $REFERENT = $USER_INFO["ID"];
  $OWNER_ID=$GLOBALS{'OWNER_ID'};

//  $res="&nbsp;";
  If (($GLOBALS["ODESLANA_POSTA"]=="f") and ($GLOBALS["DATUM_REFERENT_PRIJETI"]=="") and ($GLOBALS["DATUM_VYRIZENI"]=="") and ($GLOBALS["ODBOR"]<>''))
    $res="<a title=\"Označit jako přečtené\" href=\"javascript:newfromPrecteno(".$id.")\"><img src=\"" . FileUpImage('images/ok') . "\" border=\"0\" alt=\"Označit jako přečtené\"></a>";

  //pokud neni referent, nebo pokud zaznam nezalozil...
  If (!($REFERENT==$cislo_referenta || $GLOBALS['OWNER_ID']==$REFERENT)) $res="";
  if (!MaPristupKDokumentu_table($GLOBALS['REFERENT'],$GLOBALS['ID'])) $res='&nbsp;';

  return $res;
}

Function Odmitnout($id,$cislo_referenta) {
  global $USER_INFO;
  $REFERENT = $USER_INFO["ID"];
  $OWNER_ID=$GLOBALS{'OWNER_ID'};

  If (($GLOBALS["ODESLANA_POSTA"]=="f") and ($GLOBALS["DATUM_REFERENT_PRIJETI"]=="") and ($GLOBALS["DATUM_VYRIZENI"]=="") and ($GLOBALS["REFERENT"]==$REFERENT) && $GLOBALS['CONFIG']['ODMITNUTI_DOKUMENTU'])
    $res.="<a title=\"Odmítnout\" href=\"javascript:newOdmitnuti(".$id.",0)\"><img src=\"".FileUpImage('images/whatnever')."\" border=\"0\" alt=\"Odmítnout\"></a>";

  //pokud neni referent, nebo pokud zaznam nezalozil...
  If (!($REFERENT==$cislo_referenta || $GLOBALS['OWNER_ID']==$REFERENT)) $res="";
  if (!MaPristupKDokumentu_table($GLOBALS['REFERENT'],$GLOBALS['ID'])) $res='&nbsp;';

  return $res;
}

Function VraceniPodatelna($id) {
//  If ((HasRole('vedouci-odbor')||HasRole('spravce')) && $GLOBALS["ODESLANA_POSTA"]=="f" && $GLOBALS[ODBOR]<>'' && $GLOBALS["ID_PUVODNI"]=='' && $GLOBALS["DATUM_VYRIZENI"]=='') $res.="<a href=\"javascript:newfromPrecteno('".$id."&podatelna=1')\"><img src=\"".FileUpImage('images/back')."\" border=\"0\" title=\"Vrátit na podatelnu\"></a>";
  If ((HasRole('vedouci-odbor')||HasRole('spravce')||HasRole('podatelna')) && $GLOBALS["ODESLANA_POSTA"]=="f" && $GLOBALS[ODBOR]<>'' && $GLOBALS["ID_PUVODNI"]=='' && $GLOBALS["DATUM_VYRIZENI"]=='') $res.="<a href=\"javascript:newOdmitnuti('".$id."',1)\"><img src=\"".FileUpImage('images/back')."\" border=\"0\" title=\"Vrátit na podatelnu\"></a>";
  If ((HasRole('vedouci-odbor')||HasRole('spravce')||HasRole('podatelna')) && $GLOBALS["ODESLANA_POSTA"]=="f" && $GLOBALS[ODBOR]=='' && $GLOBALS["ID_PUVODNI"]=='' && $GLOBALS["DATUM_VYRIZENI"]=='') $res.="<a href=\"javascript:newOdmitnuti('".$id."',1)\"><img src=\"".FileUpImage('images/back')."\" border=\"0\" title=\"Vrátit na podatelnu\"></a>";
  if (!MaPristupKDokumentu_old($GLOBALS['ID'])) $res='&nbsp;';
  IF ($GLOBALS['STATUS']<2) $res = '&nbsp;';
  if ($GLOBALS['KOPIE'] == 1) $res = '';
  return $res;
}

Function KopieDokumentu($id) {
  If ((HasRole('editace_zpracovatel')||HasRole('editace_uzel')||HasRole('editace_vse_pracoviste')||HasRole('editace_admin')) && $GLOBALS["CONFIG"]["KOPIROVANI_DOKUMENTU"] && $GLOBALS["ODESLANA_POSTA"]=="f" && $GLOBALS["ODES_TYP"]<>"X") $res.='<a href="javascript:newZaloz(\''.$id.'\',\'3\')"><img src="' .  FileUpImage('images/add') . '" border="0" title="Zkopírovat dokument"></a>';
  IF ($GLOBALS['STATUS']<2) $res = '&nbsp;';
  if (!MaPristupKDokumentu_old($GLOBALS['ID'])) $res='&nbsp;';
  if ($GLOBALS['KOPIE'] == 1) $res = '';
  return $res;
}

Function KopieDokumentu2($id) {
  If ($GLOBALS["CONFIG"]["KOPIROVANI_DOKUMENTU"] && $GLOBALS["ODESLANA_POSTA"]=="f" && $GLOBALS["ODES_TYP"]<>"X") $res.='<a href="javascript:newZaloz(\''.$id.'\',\'4\')"><img src="' .  FileUpImage('images/eye-add') . '" border="0" title="Zkopírovat dokument s novým pořadovým číslem"></a>';
  IF ($GLOBALS['STATUS']<2) $res = '&nbsp;';
  if ($GLOBALS['KOPIE'] == 1) $res = '';
  return $res;
}




Function Dalsi_Precteno($id,$cislo_referenta) {
  global $uplobj;
  If ($GLOBALS["ODESLANA_POSTA"]=="t" && $GLOBALS["ODES_TYP"]=="X" && $GLOBALS["DATUM_VYPRAVENI"]=="" && !JeVeSchvaleni($GLOBALS['ID'])&& !JeKPodpisu($GLOBALS['ID']))
    $res="<a title=\"Odeslat vnitřní poštu\" href=\"javascript:newOdesliVnitrni(".$id.")\"><img src=\"".FileUpImage('images/mail-send')."\" border=\"0\"  style=\"background:blue;\" alt=\"Odeslat vnitřní poštu\"></a>";

    
    If ($GLOBALS["ODESLANA_POSTA"]=="t" && $GLOBALS["ODES_TYP"]=="S"  && $GLOBALS["DATUM_VYPRAVENI"]=="" && HasRole('vypraveni-int-posta'))
    $res="<a title=\"Odeslat interní poštu\" href=\"javascript:newOdesliInterni(".$id.")\"><img src=\"".FileUpImage('images/mail-send')."\"  style=\"background:blue;\" border=\"0\" alt=\"Odeslat interní poštu\"></a>";

    If ($GLOBALS["CONFIG"]["INTERNI_EPODATELNA"]  && $GLOBALS["ODESLANA_POSTA"]=="t" && $GLOBALS["DATUM_VYPRAVENI"]=='' && $GLOBALS["ODES_TYP"]=='M'  && $GLOBALS["VLASTNICH_RUKOU"]=='5' && HasRole('vypraveni-email'))
    $res.="<a href=\"javascript:newEmail('".$id."','epodatelna')\"><img src=\"".FileUpImage('images/mail-send')."\" border=\"0\"  style=\"background:blue;\" title=\"Odeslat email okamžitě\"></a>";

  If (($GLOBALS["ODESLANA_POSTA"]=="t") and ($GLOBALS["STATUS"]=="13") and ($GLOBALS["VLASTNICH_RUKOU"]=="1") && HasRole('edit-datum-vypraveni'))
    $res="<a title=\"Vrátit zpět na spisový uzel\" href=\"javascript:newVratitUzel(".$id.")\"><img src=\"" . FileUpImage('images/import') . "\" border=\"0\" alt=\"Vrátit zpět na spisový uzel\"></a>";


  if ($GLOBALS[ODESLANA_POSTA]=='t' && !$GLOBALS[DATUM_VYPRAVENI]  && $GLOBALS["VLASTNICH_RUKOU"]=='9') {
    $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
    $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($GLOBALS[ID]);
    if (count($upload_records)>0) $odeslat=true;
    if ($GLOBALS["KONEKTOR"]["DS"]["UREDNIK_MUZE_ODESLAT"] && $odeslat && $GLOBALS['ODESL_DATSCHRANKA'] && HasRole('vypraveni-ds')) $res.='<a href="javascript:newDS('.$id.')" title="Odeslat datovou zprávu okamžitě"><img src="'.FileUpImage('images/mail-send').'" style="background:blue;" border=0></a>';
  }

//  if (($GLOBALS['VLASTNICH_RUKOU']==9 || $GLOBALS[CONFIG][INTERNI_POSTA]==$GLOBALS['VLASTNICH_RUKOU']) && $GLOBALS[ODESLANA_POSTA]=='t' && !$GLOBALS[DATUM_VYPRAVENI])
  IF ($GLOBALS['STATUS']<2) $res = '&nbsp;';
  if (!MaPristupKDokumentu_old($GLOBALS['ID'])) $res='&nbsp;';
  if ($GLOBALS['KOPIE'] == 1) $res = '';
  return $res;
}

function Razitko($id) {
  If ($GLOBALS["CONFIG"]["TISK_RAZITKA"] && $GLOBALS["STATUS"]>1 && $GLOBALS["ODES_TYP"]<>"X")
    $res.="<a href=\"javascript:newRazitko('".$id."','".$GLOBALS["ODESLANA_POSTA"]."')\"><img src=\"" .  FileUpImage('images/pdf') . "\" border=\"0\" title=\"Tisk podacího razítka\"></a>";
  if (!MaPristupKDokumentu_old($GLOBALS['ID'])) $res='&nbsp;';
  if ($GLOBALS['KOPIE'] == 1) $res = '';
  return $res;

}

function SouborPodpis($id,$cislo_referenta) {
  if ($GLOBALS[ODESLANA_POSTA]=='t' && !$GLOBALS[DATUM_VYPRAVENI]) {
    $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
    $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($GLOBALS[ID]);
    $vykricnik=true;
    while (list($key,$val)=each($upload_records)) {
      if (strpos($val[NAME],'.pdf') || strpos($val[NAME],'.PDF')) {
        $podpis=true;
        if ($GLOBALS['CONFIG']['KONTROLA_EL_PODPISU_ONLINE']) {
          if (JePodepsanyDokument($val)) $vykricnik=false; //zkontrolujeme podpis online primo v souboru
        }
        else {
          if (eregi('el. podepsano',$val['DESCRIPTION'])) $vykricnik=false; //pseudo kontrola, jestli je v description text o el. podpisu
        }
      }
    }
    if (count($upload_records)>0) $odeslat=true;

    if ($podpis)  $res.="<a title=\"Podepsat " . ($vykricnik?"-některý z PDF vyžaduje podpis":"") . "\" href=\"javascript:newPodepsani(".$id.")\"><img src=\"".FileUpImage('images/layers')."\" border=\"0\"" . ($vykricnik ? 'style="background:red;" ':'') . " alt=\"Podepsat dokument\"></a>";
//    if ($podpis && $vykricnik)  $res.="<img src=\"".FileUp2('images/alert.gif')."\" border=\"0\" title=\"ani jeden PDF dokument není podepsán\">";

    //$res.='<a href="javascript:newDS('.$id.')" title="Odeslat datovou zprávu okamžitě"><img src="'.FileUp2('images/office/mail.gif').'" border=0></a>';
//    if ($GLOBALS["KONEKTOR"]["DS"]["UREDNIK_MUZE_ODESLAT"] && $odeslat && $GLOBALS['ODESL_DATSCHRANKA']) $res.='<a href="javascript:newDS('.$id.')" title="Odeslat datovou zprávu okamžitě"><img src="'.FileUpImage('images/mail-send').'" border=0></a>';
  }
  If ($GLOBALS[STORNOVANO] || $GLOBALS[SKARTOVANO]) $res='&nbsp;';
  If ($GLOBALS[SPIS_VYRIZEN]) $res='&nbsp;';
  return $res;
}
/*
function Odeslani($id,$cislo_referenta) {
  if ($GLOBALS[ODESLANA_POSTA]=='t' && !$GLOBALS[DATUM_VYPRAVENI]) {
    $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
    $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($GLOBALS[ID]);
    if (count($upload_records)>0) $odeslat=true;
    if ($GLOBALS["KONEKTOR"]["DS"]["UREDNIK_MUZE_ODESLAT"] && $odeslat && $GLOBALS['ODESL_DATSCHRANKA']) $res.='<a href="javascript:newDS('.$id.')" title="Odeslat datovou zprávu okamžitě"><img src="'.FileUpImage('images/mail-send').'" style="background:blue;" border=0></a>';
  }
  If ($GLOBALS[STORNOVANO] || $GLOBALS[SKARTOVANO]) $res='&nbsp;';
  If ($GLOBALS[SPIS_VYRIZEN]) $res='&nbsp;';
  return $res;
}
*/
/*
function PluginsTable($id,$cislo_referenta) {
    reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
    foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
      if ($plug['enabled']){
        $file = FileUp2('plugins/'.$plug['dir'].'/.admin/table_funkce_precteno.inc');
    		if (File_Exists($file)) include($file);
      }
    }
  If ($GLOBALS[STORNOVANO] || $GLOBALS[SKARTOVANO]) $res='&nbsp;';
  If ($GLOBALS[SPIS_VYRIZEN]) $res='&nbsp;';
    return $res;
}
*/
Function ExistujeSoubor($id,$cj1,$cj2) {
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

function FormatujVec($vec) {
  return str_replace(",",", ",$vec);
}

Function GetDocs_UPLOAD($id)
{
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id); 
  while (list($key,$val)=each($upload_records)) {
    $pos = strpos($val[NAME], 'dorucenka');
    if ($val[NAME] == 'prichozi_datova_zprava.zfo' || $pos !== false) continue;
    $res .= '<a href=# onclick="return EditShowAtt(event,'.$val[ID].',\'ifrm_doc\');" target="ifrm_doc" class="pages">';
    $res .= $val[NAME]."</a><br/>";
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

Function ShowUploadPosta($record_id=0) {
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true));
  if ($record_id<0 || $record_id=='') return '&nbsp;';
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($record_id);
  $pocet=count($upload_records);
  if ($pocet==0) $img='folder-empty'; else $img='folder';
//  $res='<a href="javascript:upload_KVP_AKCE('.$id_akce.')" class="image" title="('.$pocet.')"><img src="'.FileUp2('images/'.$img.'.gif').'" border="0"></a>';
  $res='<a href="#" onclick="upload_('.$record_id.')" class="image" title="('.$pocet.')"><img src="/'.FileUpImage('images/'.$img).'" border="0"></a>';

//  if (!MaPristupKDokumentu_table($GLOBALS['REFERENT'],$record_id)) $res='&nbsp;';
  return $res;
} 

Function UkazTableOdbor($odbor) {
  //$res="ACC".UkazOdbor($odbor,'true')."AAB";
  $res=UkazOdbor($odbor,'true');
  return $res;
}

Function ZalozVnitrni($id) {
  return '<a href="zaloz.php?ID='.$id.'&prefix=_vnitrni"><img src="' . FileUpImage('images/ok_check') . '" alt="Označit jako příchozí" border=0></a>';
}

Function UkazZpracovatele($user) {
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

if (!$GLOBALS['EXPORT_ALL_step'])  {

    NewWindow(array("fname" => "Agenda", "name" => "Agenda", "header" => true, "cache" => false, "window" => "edit"));
echo "
  <script>
  <!--
  function newfrom(id,vnitrni) {
    NewWindowAgenda('edit.php?insertfrom&EDIT_ID='+id+'&vnitrni='+vnitrni);
  }

  function newPodepsani(id) {
//    NewWindowAgenda('./interface/podepsani602/edit.php?edit&EDIT_ID='+id+'&cacheid=');
    NewWindowAgenda('./interface/podepsaniDERS/edit.php?edit&EDIT_ID='+id+'&cacheid=');
  }

  function newfromPrecteno(id) {
    NewWindowAgenda('./services/spisovka/precteno.php?ID='+id);
  }


  function newOdesliInterni(id) {
    NewWindowAgenda('./services/spisovka/odesli.php?ID='+id);
  }


  function newOdesliVnitrni(id) {
    NewWindowAgenda('./services/spisovka/send_vnitrni.php?EDIT_ID='+id+'&send_vnitrni=1');
  }

  function newOdmitnuti(id,podatelna) {
    NewWindowAgenda('./services/spisovka/odmitnuti/edit.php?insert&POSTA_ID='+id+'&podatelna='+podatelna);
  }

  function newRazitko(id,typ) {
    NewWindowAgenda('services/barcode/razitko/edit.php?insert&ID='+id+'&ODESLANA='+typ);
  }

  function newDS(id) {
    if (confirm('Chcete skutečně danou zprávu odeslat do datové schránky příjemce?\\n\\nPokračovat?')){
    NewWindowAgenda('plugins/DS/send.php?user=1&ID_ODCHOZI='+id);
    }
  }

  function newZaloz(id,zalozeni) {
    if (confirm('Chcete skutečně vytvořit kopii dokumentu?\\n\\nPokračovat?')){
      NewWindowAgenda('services/spisovka/zalozKopii.php?ID='+id+'&zalozeni='+zalozeni);
    }
  }

  function newEmail(id,typ) {
    if (confirm('Chcete skutečně daný email odeslat?\\n\\nPokračovat?')) {
      NewWindowAgenda('plugins/'+typ+'/odeslat.php?ID='+id);
    }
  }

  function newVratitUzel(id) {
    if (confirm('Chcete skutečně vrátit daný dokument zpět na spisový uzel?\\n\\nPokračovat?')) {
      NewWindowAgenda('services/spisovka/vratitUzel.php?ID='+id);
    }
  }

 //-->
</script>
";
}

Function CZdate($engdatum)
{
  if(strpos($engdatum, 'T')) {
    $rozdelDatum = explode('T',$engdatum);
    $date = explode('-', $rozdelDatum[0]);
    $time = $rozdelDatum[1];
    $nowd = $date[2].'.'.$date[1].'.'.$date[0].' '.$time;
  }
  else {
    $datumkod=explode("-",$engdatum);
    $czdatum=$datumkod[2].".".$datumkod[1].".".$datumkod[0];
  	$nowd=$czdatum; 
  //  $nowd = EReg_Replace("[. ]0"," ", $czdatum);
  //  $nowd = EReg_Replace("^0","", $nowd);
    If ($engdatum=="") {$nowd="";}
  }
  return $nowd;
}

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/table_func_end.inc');
		if (File_Exists($file)) include($file);
  }
}


