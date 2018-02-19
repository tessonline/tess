<?php
If ($sablona=='obal' )
{

  $fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/spisovy_obal.rtf");
  $fp = fopen ($fn, "r");
  $sablona = fread ($fp, filesize ($fn));

  $a=new DB_POSTA;
  $sql="select * from posta where cislo_spisu1=".$cislo_spisu1." and cislo_spisu2=".$cislo_spisu2." and odes_typ<>'X' and referent=".$referent_spis." order by id asc ";

  $a->query($sql);
  $a->Next_Record();
  //nacteme prvotniho adresata
  $id=$a->Record[ID];
  $ODESILATEL=UkazAdresu($id,', ');
  $prijemci=substr($a->Record["DALSI_PRIJEMCI"],1,-1);    
  If (($prijemci<>"") and (!strstr($prijemci,':'))) 
  {
    $sql='SELECT * FROM cis_posta_prijemci WHERE id IN ('.$prijemci.')';
    $q=new DB_POSTA;
    $q->query($sql);
    while ($q->Next_Record())
    {
      $res="\\par ";
      If ($q->Record["ODES_TYP"]=="P") 
      {
        $res.=$q->Record["ODESL_PRIJMENI"].', '; 
        $res.=$q->Record["ODESL_ULICE"].' '.$q->Record["ODESL_CP"].', '.$q->Record["ODESL_PSC"].' '.$q->Record["ODESL_POSTA"];
      }
      else
      {
        $res.=$q->Record["ODESL_PRIJMENI"].' '.$q->Record["ODESL_JMENO"].', '; 
        $res.=$q->Record["ODESL_ULICE"].' '.$q->Record["ODESL_CP"].', '.$q->Record["ODESL_PSC"].' '.$q->Record["ODESL_POSTA"];
      }
      If ($q->Record["ODES_TYP"]=="A") {$res.='anonym';}   
      If ($q->Record["ODES_TYP"]=="V") {$res.='veřejnost';}
      $ODESILATEL.=$res;
    }
  }
  $skartace=$a->Record["SKARTACE"];
  $prvotni_adresat=StrTr($ODESILATEL, $tr_from, $tr_to);
  $vec_dopisu=$a->Record["VEC"];
  $vec_dopisu=StrTr($vec_dopisu, $tr_from, $tr_to);
  $zkratka_odboru=UkazOdbor($w->Record["ODBOR"],true);
  $DALSI_ADRESATI=array();
  $DALSI_ADRESATI_JSOU=array();
  $DALSI_ADRESATI_JSOU[]=$a->Record["ODESL_PRIJMENI"];
  while ($a->Next_Record())
  {
    $ODESILATEL='';
    $psc=substr($a->Record["ODESL_PSC"],0,3)." ".substr($a->Record["ODESL_PSC"],3,2);
    If (($a->Record["ODES_TYP"]<>"A") and ($a->Record["ODES_TYP"]<>"P"))
    {
      $ODESILATEL=$a->Record["ODESL_PRIJMENI"]." ".$a->Record["ODESL_JMENO"]." ".$a->Record["ODESL_TITUL"].", ".$a->Record["ODESL_ULICE"]." ".$a->Record["ODESL_CP"]."".$a->Record["ODESL_COR"].", ".$psc." ".$a->Record["ODESL_POSTA"];
    }
    If (($a->Record["ODES_TYP"]=="P"))
    {
      $ODESILATEL=$a->Record["ODESL_PRIJMENI"].", ";
      $ODESILATEL.=$a->Record["ODESL_ULICE"]." ".$a->Record["ODESL_CP"]."".$a->Record["ODESL_COR"].", ".$psc." ".$a->Record["ODESL_POSTA"];
    }
    //pridame jenom ty, co tam jeste nejsou
    If (!in_array($ODESILATEL,$DALSI_ADRESATI_JSOU)) 
    {
      $DALSI_ADRESATI[]=$ODESILATEL;
      $DALSI_ADRESATI_JSOU[]=$ODESILATEL;
    }

  }
  //$DALSI_ADRESATI.= $ODESILATEL."\\par ";
  sort($DALSI_ADRESATI,SORT_STRING);
  $DALSI_ADRESATI=StrTr(implode("\\par ",$DALSI_ADRESATI), $tr_from, $tr_to);

  $zkratka_odboru=StrTr($zkratka_odboru, $tr_from, $tr_to);
  $DALSI_ADRESATI=StrTr($DALSI_ADRESATI, $tr_from, $tr_to);
  $prvotni_adresat=StrTr($prvotni_adresat, $tr_from, $tr_to);
  
  
  If (!$skartace) $skartace=0;
  $sql='select * from cis_posta_skartace where id='.$skartace;
  $a->query($sql);
  $a->Next_Record();
  $skartace_text=substr($a->Record["TEXT"],0,strpos($a->Record["TEXT"],' ')).", ".$a->Record["SKAR_ZNAK"]."/".$a->Record["DOBA"];
  $z=array("ODBOR_SPISU","CISLO_SPISU","VEC_DOPISU","ADRESAT","UCASTNICI","SKARTACE","ODBOR_REFERENTA","NAZEV_SPISU");
  $na=array($zkratka_odboru,$cislo_spisu,$vec_dopisu,$prvotni_adresat,$DALSI_ADRESATI,$skartace_text,$odbor,$nazev_spisu);
  $vysledny=Str_replace($z,$na,$sablona);
  
  $nazev='obal_na_spis_'.$w->Record["EV_CISLO"].'-'.$w->Record["ROK"].'.rtf';
  Header("Content-Type: application/rtf");
  Header("Content-Disposition: attachment;filename=$nazev");
//  $vysledny=StrTr($tr_from,$tr_to,$vysledny);
  echo $vysledny;   
}

/** onma původní
  while ($a->Next_Record())
  {
//    If ($predchozi_ev<>$a->Record["EV_CISLO"])
    {
      $i++;
//
      $id=$a->Record[ID];
      $ODESILATEL="";
      $ODESILATEL=UkazAdresu($id,', ');
//      echo $ODESILATEL."<br/>";
      $puvodce=StrTr($ODESILATEL, $tr_from, $tr_to);
  
      $vlozeno=substr($a->Record["DATUM_PODATELNA_PRIJETI"],0,strpos($a->Record["DATUM_PODATELNA_PRIJETI"],' '));
      $obsah=$a->Record["VEC"];
      $obsah=StrTr($obsah, $tr_from, $tr_to);
  
      $zkratka_odboru=UkazOdbor($a->Record["ODBOR"],true,false);

      $cislo_jednaci=strip_tags(FormatCJednaci($a->Record["CISLO_JEDNACI1"],$a->Record["CISLO_JEDNACI2"],$a->Record["REFERENT"],$a->Record["ODBOR"]));
      $cislo_jednaci.=" - ".$i;
//      echo "$cislo_jednaci - $i<br/>";
      $pocet_listu=$a->Record["POCET_LISTU"];
      $pocet_priloh=$a->Record["POCET_PRILOH"];
      $druh_priloh=$a->Record["DRUH_PRILOH"];
  
      $predchozi_ev=$a->Record["EV_CISLO"];
      //$puvodce=
      $cislo=$i.".";
      $cislo_jednaci=StrTr($cislo_jednaci,$tr_from,$tr_to);
      $z=array("A0","A1","A2","A3","A4","A5","A6","A7");
      $na=array($cislo,$vlozeno,$puvodce,$obsah,$cislo_jednaci,$pocet_listu,$pocet_priloh,$druh_priloh);
      $text.=Str_replace($z,$na,$radek);

    }
  }
  $podaci_cislo_bar='*'.$podaci_cislo.$code39[$kontrola].'*';
  fclose ($fp);
  
  $uzavreni_spisu=$w->Record["SPIS_VYRIZEN"];

  $vec=StrTr($vec,$tr_from,$tr_to);
  $REFERENT_JMENO=StrTr($REFERENT_JMENO,$tr_from,$tr_to);
  $nazev_spisu=StrTr($nazev_spisu,$tr_from,$tr_to);
  $odbor=UkazOdbor($w->Record["ODBOR"]);
  $odbor=StrTr($odbor,$tr_from,$tr_to);
*/ 
?>
