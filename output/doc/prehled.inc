<?php

FUnction Skartace($skartace)
{
  $res="";
  If ($skartace>0)
  {
    $a=new DB_POSTA;
    $sql='select skar_znak, doba, text from cis_posta_skartace where id='.$skartace;
    $a->query($sql);
    $a->Next_Record();
    $text_skartace=str_replace('STARE - ','',$a->Record["TEXT"]);
    $text=substr($text_skartace,0,strpos($text_skartace,' '));
//    $res=$text." ".$a->Record["SKAR_ZNAK"]."/".$a->Record["DOBA"];
    $res=array($text,$a->Record['SKAR_ZNAK'],$a->Record['DOBA']);

  }
  return $res;
}

If ($sablona=='prehled' )
{
  
  $poznamka_pole = array();
  
//echo $sablona."<br />";
  $fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/spisovy_prehled34.rtf");
  $fp = fopen ($fn, "r");
  $sablona = fread ($fp, filesize ($fn));

  //$fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek2.rtf");
  $fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek_zpracovatel.rtf");
  $fp = fopen ($fn, "r");
  $radek_uros = fread ($fp, filesize ($fn));

  //$fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek.rtf");
  $fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek_prehled.rtf");
  $fp = fopen ($fn, "r");
  $radek = fread ($fp, filesize ($fn));

  //$fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek.rtf");
  $fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek_prilohy2.rtf");
  $fp = fopen ($fn, "r");
  $radek_prilohy = fread ($fp, filesize ($fn));

  $fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek_vazba.rtf");
  $fp = fopen ($fn, "r");
  $radek_vazba = fread ($fp, filesize ($fn));

  $a=new DB_POSTA;

  $uzavreni_spisu=str_replace('&nbsp;','',$a->dbdate2str($w->Record["SPIS_VYRIZEN"]));

  $test=$cislo_spisu1.'/'.$cislo_spisu2;

  $cj= LoadClass('EedCj', $GLOBALS["ID"]);
  $cj1 = $cj->cj1;
  $cj2 = $cj->cj2;
  $dalsi_dokumenty=$cj->GetDocsInCj($GLOBALS["ID"]);
  
  $cj_info = $cj->GetCjInfo($GLOBALS["ID"]);
  if ($cj_info['JE_TYPOVY_SPIS']>0) {
    $nazev_typoveho_spisu = $cj->NazevTypovehoSpisu($cj_info['TYPOVY_SPIS_MAINID']);
  }
  
  /*
   
   
   $cj_info = $cj_obj->GetCjInfo($doc_id);
$main_doc = $cj_info['MAIN_DOC'];
$where_cj = $cj_obj->GetWhereForCJ($doc_id);
$spis_id = $cj_info['SPIS_ID'];
if ($spis_id <> $doc_id) {

  $doc_id = $spis_id;
  $cj_obj = LoadClass('EedCj',$doc_id);
  $cj_info = $cj_obj->GetCjInfo($doc_id);
  $main_doc = $cj_info['MAIN_DOC'];
  $where_cj = $cj_obj->GetWhereForCJ($doc_id);
}

if (!$cislo_spisu1) $cislo_spisu1 = $cj_info['CISLO_JEDNACI1'];
if (!$cislo_spisu2) $cislo_spisu2 = $cj_info['CISLO_JEDNACI2'];

if ($cj_info['JE_TYPOVY_SPIS']>0) {
	$nazev = $cj_obj->NazevTypovehoSpisu($cj_info['TYPOVY_SPIS_MAINID']);

	$cj_info['CELY_NAZEV'] = $nazev;
}
   
   * 
   */
  

  $where_spis = "and id in (" . $GLOBALS['ID'] . "," . implode(',',$dalsi_dokumenty).")";

  $so_where = '';
  if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) {
    $sql_so='select superodbor from posta where id in ('.$ID.')  ';
    $a->query($sql_so); $a->Next_Record();
    $so = $a->Record['SUPERODBOR'];
    if ($so>0)    $so_where = 'AND superodbor in ('. $so . ')';
  }
  $so_where = '';
  //tak vyplnime jednotlive radky tabulky
  $sql1='select * from posta where (1=1 '.$where_spis.')  and stornovano is null '.$so_where.' order by id asc ';

  $sql2='select * from posta_spisprehled_zaznamy where  1=1 '.$where_spis.' order by id asc ';
  //echo $sql1."<br />";
  //echo $sql2."<br />";
  $sql3 = "
    select p.referent, p.datum_referent_prijeti 
    from posta p
    where p.cislo_spisu1 = $cislo_spisu1
    and p.cislo_spisu2 = $cislo_spisu2
    $so_where
    and stornovano is null
    order by p.ID ASC
    limit 1
  ";
  $sql3a = "
    select count(*) as pocet
    from cis_posta_predani pp
    where pp.cislo_spisu1 = $cislo_spisu1
    and pp.cislo_spisu2 = $cislo_spisu2
  ";
  $sql3b = "
    select distinct pp.old_referent, pp.referent, pp.datum
    from cis_posta_predani pp
    where pp.cislo_spisu1 = $cislo_spisu1
    and pp.cislo_spisu2 = $cislo_spisu2
    $so_where
    order by pp.datum
  ";
  $sql3c = "
    select min(id) as id
    from posta p
    where p.cislo_spisu1 = $cislo_spisu1
    and p.cislo_spisu2 = $cislo_spisu2
    $so_where
    and stornovano is null
 ";
  //echo $sql3."<br />";
  //echo $sql3a."<br />";
  //echo $sql3b."<br />";
  //echo $sql3c."<br />";
  $a->query($sql3c);
  while ($a->Next_Record()) $min_id = $a->Record["ID"];
  $sql3d= "
    select datum_referent_prijeti, datum_podatelna_prijeti, odeslana_posta,datum_vyrizeni,spis_vyrizen
    from posta
    where id = $min_id
  ";
  //echo $sql3d."<br />";
  $a->query($sql3d);
  while ($a->Next_Record()) {
    $odp = $a->Record["ODESLANA_POSTA"];
    if ($odp) $prvni_datum = $a->Record["DATUM_PODATELNA_PRIJETI"];
    else $prvni_datum = $a->Record["DATUM_REFERENT_PRIJETI"];
//    $spis_vyrizen=$a->Record['SPIS_VYRIZEN'];
//    $datum_vyrizeni=$a->Record['DATUM_VYRIZENI'];
  }

  $j3 = 0;
  $a->query($sql3);
  while ($a->Next_Record()) {
    $pole_oprav[$j3]["referent"] = $a->Record["REFERENT"];
    $pole_oprav[$j3]["datum"] = $a->Record["DATUM_REFERENT_PRIJETI"];
    $j3++;
  }
  $a->query($sql3a);
  while ($a->Next_Record()) $pocet = $a->Record["POCET"];

  //print_r($pole_oprav);
  if ($pocet != "0") {
    $j3 = 0;
    $a->query($sql3b);
    while ($a->Next_Record()) {
      $pole_oprav[$j3]["old_referent"] = $a->Record["OLD_REFERENT"];
      $pole_oprav[$j3]["referent"] = $a->Record["REFERENT"];
      $pole_oprav[$j3]["datum"] = $a->Record["DATUM"];
      $j3++;
    }
  }
  //var_dump($pole_oprav)  ;
  /*
  else {
    while ($a->Next_Record()) {
      $pole_oprav[$j3]["referent"] = $a->Record["REFERENT"];
      $pole_oprav[$j3]["datum"] = $a->Record["DATUM_REFERENT_PRIJETI"];
      $j3++;
    }
  }
  */
  $j2 = 1;
  
  for ($i1=0; $i1<count($pole_oprav); $i1++) {
    $_poradi = 1;
    $_refer = $_od = $_do = "";
    $_refer = UkazUsera($pole_oprav[$i1]["referent"]);
    $_refer_old = UkazUsera($pole_oprav[$i1]["old_referent"]);
    if ($pole_oprav[$i1]["old_referent"]) {
      if ($i1 == 0) {
        $pole1[0]["ref"] = $pole_oprav[$i1]["old_referent"];  
        $pole1[0]["od"] = "$prvni_datum";  
        $pole1[0]["do"] = $pole_oprav[$i1]["datum"];
        $pole1[$j2]["ref"] = $pole_oprav[$i1]["referent"];  
        $pole1[$j2]["od"] = $pole_oprav[$i1]["datum"];
        $pole1[$j2]["do"] = "";
      }
      else {
        $pole1[$j2]["ref"] = $pole_oprav[$i1]["referent"];  
        $pole1[$j2]["od"] = $pole_oprav[$i1]["datum"];
        $pole1[$j2-1]["do"] = $pole_oprav[$i1]["datum"];
        $pole1[$j2]["do"] = "";
      }
      $j2++;  
    }
    else {
      $pole1[$i1]["ref"] = $pole_oprav[$i1]["referent"];  
      $pole1[$i1]["od"] = $pole_oprav[$i1]["datum"];
      $pole1[$i1]["do"] = "";
      if ($i1 == 0) $pole1[0]["od"] = "$prvni_datum"; 
    }
  }
  
  
  $text_ref = "";
  for ($i1=0; $i1<count($pole1); $i1++) {
    $_poradi = $i1+1;
    $_refer = UkazUsera($pole1[$i1]["ref"]);
    $_od = $pole1[$i1]["od"];
    $_do = $pole1[$i1]["do"];
    $_do = $_do ? $_do : $uzavreni_spisu; 
    $rp = $_poradi.". ".$_refer;
    $_poradi = " ".$_poradi.".";
    $_od = " ".$_od;
    $_do = " ".$_do;
    $_refer = " ".$_refer;
    $z = array("B0","B1","B2","B3");
    $na = array($_poradi,$_refer,$_od,$_do);
    if ($format=='rtf') {
      foreach ($na as &$n)
        $n = TxtEncodingToWin($n);
    }
    $text_ref .= Str_replace($z,$na,$radek_uros);
    $referenti[]=$na;
  }

  $a->query($sql1);
  $predchozi_ev='';
  $i=0;
  $j1 = 1;
  if ($obal==1) $j1 = 2;

  while ($a->Next_Record()) {
    if (!$zkratka_odboru_hlavni) $zkratka_odboru_hlavni = UkazOdbor($a->Record["ODBOR"],true,false);
    $pole_ssz[$j1]["id"] = $a->Record["ID"];
      $_odesilatel = "";
      $_odesilatel = UkazAdresu($pole_ssz[$j1]["id"],', ');
      $puvodce = $_odesilatel;
    $odeslana_posta = $a->Record["ODESLANA_POSTA"];
    $pole_ssz[$j1]["_referent"] = $a->Record["REFERENT"];
    $pole_ssz[$j1]["_odbor"] = $a->Record["ODBOR"];
    if ($odeslana_posta == "t") { 
      $puvodce = $CONFIG["URAD"]." ".$CONFIG["MESTO"].", ".UkazOdbor($pole_ssz[$j1]["_odbor"]).", ".UkazUsera($pole_ssz[$j1]["_referent"]);
    }
    if ($a->Record["ODES_TYP"] == "Z") $puvodce = "Vlastní záznam";
      $pole_ssz[$j1]["puvodce"] = $puvodce; 
    $pole_ssz[$j1]["datum_podatelna_prijeti"] = $a->Record["DATUM_PODATELNA_PRIJETI"];
      $pole_ssz[$j1]["trideni"] = MakeStamp($pole_ssz[$j1]["datum_podatelna_prijeti"]);
    $pole_ssz[$j1]["obsah"] = $a->Record["VEC"];
    $pole_ssz[$j1]["_cislo_jednaci1"] = $a->Record["CISLO_JEDNACI1"];
    $pole_ssz[$j1]["_cislo_jednaci2"] = $a->Record["CISLO_JEDNACI2"];
    $pole_ssz[$j1]["zkratka_odboru"] = UkazOdbor($a->Record["ODBOR"],true,false);
    if ($a->Record["TYP_DOKUMENTU"]=='D')
    {
      $pole_ssz[$j1]["pocet_listu"] = 0;
      $pole_ssz[$j1]["pocet_priloh"] = 1;
      $pole_ssz[$j1]["druh_priloh"] = 'digitální';
    }
    else
    {
      $pole_ssz[$j1]["pocet_listu"] = $a->Record["POCET_LISTU"];
      $pole_ssz[$j1]["pocet_priloh"] = $a->Record["POCET_PRILOH"];
      $pole_ssz[$j1]["druh_priloh"] = $a->Record["DRUH_PRILOH"];
    }
/*
    if ($a->Record["TYP_DOKUMENTU"]<>'D' && $a->Record["ODES_TYP"]=='X')
    {
      $pole_ssz[$j1]["pocet_listu"] = 0;
      $pole_ssz[$j1]["pocet_priloh"] = 0;
//      $pole_ssz[$j1]["druh_priloh"] = 'digitální';
    }
*/
    $pole_ssz[$j1]["predchozi_ev"] = $a->Record["EV_CISLO"];
    $pole_ssz[$j1]["datum_pm"] = $a->Record["DATUM_PM"];
    $pole_ssz[$j1]["datum_doruceni"] = $a->Record["DATUM_DORUCENI"];
    $pole_ssz[$j1]["datum_vypraveni"] = $a->Record["DATUM_VYPRAVENI"];
    $pole_ssz[$j1]["cislo_spisu1"] = $a->Record["CISLO_SPISU1"];
    $pole_ssz[$j1]["cislo_spisu2"] = $a->Record["CISLO_SPISU2"];
    $pole_ssz[$j1]["podcislo_spisu"] = $a->Record["PODCISLO_SPISU"];
    $pole_ssz[$j1]["skartace"] = $a->Record["SKARTACE"];
    $pole_ssz[$j1]["poznamka"] = $a->Record["POZNAMKA"];
    $j1++;
  }
  //print_r($pole_ssz);
  //unset($pole_ssz);
  $a->query($sql2);
  //$j1 = 0;
  while ($a->Next_Record()) {
    $pole_ssz[$j1]["id"] = $a->Record["ID"];
      $_odesilatel = "";
      $_odesilatel = UkazAdresu($pole_ssz[$j1]["id"],', ','posta_spisprehled_zaznamy');
      $puvodce = $_odesilatel;
      $pole_ssz[$j1]["puvodce"] = $puvodce; 
    $pole_ssz[$j1]["datum_podatelna_prijeti"] = $a->Record["DATUM_PODATELNA_PRIJETI"];
      $pole_ssz[$j1]["trideni"] = MakeStamp($pole_ssz[$j1]["datum_podatelna_prijeti"]);
    $pole_ssz[$j1]["obsah"] = $a->Record["VEC"];
    $pole_ssz[$j1]["_cislo_jednaci1"] = $a->Record["CISLO_JEDNACI1"];
    $pole_ssz[$j1]["_cislo_jednaci2"] = $a->Record["CISLO_JEDNACI2"];
    $pole_ssz[$j1]["_referent"] = $a->Record["REFERENT"];
    $pole_ssz[$j1]["_odbor"] = $a->Record["ODBOR"];
    $pole_ssz[$j1]["zkratka_odboru"] = UkazOdbor($a->Record["ODBOR"],true,false);
    $pole_ssz[$j1]["pocet_listu"] = ($a->Record["TYP_DOKUMENTU"]=='D'?0:$a->Record["POCET_LISTU"]);
    $pole_ssz[$j1]["pocet_priloh"] = ($a->Record["TYP_DOKUMENTU"]=='D'?1:$a->Record["POCET_PRILOH"]);
    $pole_ssz[$j1]["druh_priloh"] = ($a->Record["TYP_DOKUMENTU"]=='D'?'digitální':$a->Record["DRUH_PRILOH"]);
    $pole_ssz[$j1]["predchozi_ev"] = $a->Record["EV_CISLO"];
    $pole_ssz[$j1]["datum_pm"] = $a->Record["DATUM_PM"];
    $pole_ssz[$j1]["datum_doruceni"] = $a->Record["DATUM_DORUCENI"];
    $pole_ssz[$j1]["datum_vypraveni"] = $a->Record["DATUM_VYPRAVENI"];
    $pole_ssz[$j1]["cislo_spisu1"] = $a->Record["CISLO_SPISU1"];
    $pole_ssz[$j1]["cislo_spisu2"] = $a->Record["CISLO_SPISU2"];
    $pole_ssz[$j1]["podcislo_spisu"] = $a->Record["PODCISLO_SPISU"];
    $pole_ssz[$j1]["poznamka"] = $a->Record["POZNAMKA"];
    //$pole_ssz[$j1]["puvodce"] = $puvodce; 
    $j1++;
  }

    $pole_ssz[0]["puvodce"] = '';
    $pole_ssz[0]["datum_podatelna_prijeti"] = $a->Record["DATUM_PODATELNA_PRIJETI"];
    $pole_ssz[0]["trideni"] = MakeStamp($pole_ssz[$j1]["datum_podatelna_prijeti"]);
    $pole_ssz[0]["obsah"] = 'Spisový přehled';
    $pole_ssz[0]["_cislo_jednaci1"] = $a->Record["CISLO_JEDNACI1"];
    $pole_ssz[0]["_cislo_jednaci2"] = $a->Record["CISLO_JEDNACI2"];
    $pole_ssz[0]["_referent"] = $a->Record["REFERENT"];
    $pole_ssz[0]["_odbor"] = $a->Record["ODBOR"];
    $pole_ssz[0]["zkratka_odboru"] = UkazOdbor($a->Record["ODBOR"],true,false);
    $pole_ssz[0]["pocet_listu"] = '{nb}';
    $pole_ssz[0]["pocet_priloh"] = 0;
    $pole_ssz[0]["druh_priloh"] = '';
    $pole_ssz[0]["predchozi_ev"] = $a->Record["EV_CISLO"];
    $pole_ssz[0]["datum_pm"] = $a->Record["DATUM_PM"];
    $pole_ssz[0]["datum_doruceni"] = $a->Record["DATUM_DORUCENI"];
    $pole_ssz[0]["datum_vypraveni"] = $a->Record["DATUM_VYPRAVENI"];
    $pole_ssz[0]["cislo_spisu1"] = $a->Record["CISLO_SPISU1"];
    $pole_ssz[0]["cislo_spisu2"] = $a->Record["CISLO_SPISU2"];
    $pole_ssz[0]["podcislo_spisu"] = $a->Record["PODCISLO_SPISU"];

  if ($obal==1)
  {
    $pole_ssz[1]["puvodce"] = '';
    $pole_ssz[1]["datum_podatelna_prijeti"] = $a->Record["DATUM_PODATELNA_PRIJETI"];
    $pole_ssz[1]["trideni"] = MakeStamp($pole_ssz[$j1]["datum_podatelna_prijeti"]);
    $pole_ssz[1]["obsah"] = 'Spisový přebal';
    $pole_ssz[1]["_cislo_jednaci1"] = $a->Record["CISLO_JEDNACI1"];
    $pole_ssz[1]["_cislo_jednaci2"] = $a->Record["CISLO_JEDNACI2"];
    $pole_ssz[1]["_referent"] = $a->Record["REFERENT"];
    $pole_ssz[1]["_odbor"] = $a->Record["ODBOR"];
    $pole_ssz[1]["zkratka_odboru"] = UkazOdbor($a->Record["ODBOR"],true,false);
    $pole_ssz[1]["pocet_listu"] = 1;
    $pole_ssz[1]["pocet_priloh"] = 0;
    $pole_ssz[1]["druh_priloh"] = '';
    $pole_ssz[1]["predchozi_ev"] = $a->Record["EV_CISLO"];
    $pole_ssz[1]["datum_pm"] = $a->Record["DATUM_PM"];
    $pole_ssz[1]["datum_doruceni"] = $a->Record["DATUM_DORUCENI"];
    $pole_ssz[1]["datum_vypraveni"] = $a->Record["DATUM_VYPRAVENI"];
    $pole_ssz[1]["cislo_spisu1"] = $a->Record["CISLO_SPISU1"];
    $pole_ssz[1]["cislo_spisu2"] = $a->Record["CISLO_SPISU2"];
    $pole_ssz[1]["podcislo_spisu"] = $a->Record["PODCISLO_SPISU"];
  }
  //while ($a->Next_Record()) {
//  $pole_ssz = Array_sort_key($pole_ssz,"trideni","asc");
//  print_r($pole_ssz);Die();
  //print_r($pole_ssz);
  $cpole = array();
  for ($i1=0; $i1<count($pole_ssz); $i1++) {
  }

  for ($i1=0; $i1<count($pole_ssz); $i1++) {
    //echo $pole_ssz[$i1]["trideni"]."<br />";
    $id = $pole_ssz[$i1]["id"];
    $datum_podatelna_prijeti = $pole_ssz[$i1]["datum_podatelna_prijeti"];
    $obsah = $pole_ssz[$i1]["obsah"];
    $_cislo_jednaci1 = $pole_ssz[$i1]["_cislo_jednaci1"];
    $_cislo_jednaci2 = $pole_ssz[$i1]["_cislo_jednaci2"];
    $_referent = $pole_ssz[$i1]["_referent"];
    $_odbor = $pole_ssz[$i1]["_odbor"];
    $zkratka_odboru = $pole_ssz[$i1]["zkratka_odboru"];
    $pocet_listu = $pole_ssz[$i1]["pocet_listu"];
    $pocet_priloh = $pole_ssz[$i1]["pocet_priloh"];
    $druh_priloh = $pole_ssz[$i1]["druh_priloh"];
    $predchozi_ev = $pole_ssz[$i1]["predchozi_ev"];
    $puvodce = $pole_ssz[$i1]["puvodce"];
    $datum_pm = $pole_ssz[$i1]["datum_pm"];
    $datum_doruceni = $pole_ssz[$i1]["datum_doruceni"];
    $datum_vypraveni = $pole_ssz[$i1]["datum_vypraveni"];
    $cs1 = $pole_ssz[$i1]["cislo_spisu1"];
    $cs2 = $pole_ssz[$i1]["cislo_spisu2"];
    $podcislo = $pole_ssz[$i1]["podcislo_spisu"];
    $skartace = $pole_ssz[$i1]["skartace"];
    $poznamka = $pole_ssz[$i1]["poznamka"];
    $vlozeno=substr($datum_podatelna_prijeti,0,strpos($datum_podatelna_prijeti,' '));

/*
    If ($GLOBALS["CONFIG"]["SHOW_C_JEDNACI"])
      $cislo_jednaci=strip_tags(FormatCJednaci($_cislo_jednaci1,$_cislo_jednaci2,$_referent,$_odbor));
    else
//      $cislo_jednaci=strip_tags(FormatSpis($cs1,$cs2,$_referent,$_odbor,'',$podcislo));
      $cislo_jednaci=strip_tags(FormatSpis($id));
*/
    $doc = LoadSingleton('EedDokument', $id);
    $cislo_jednaci = $doc->cislo_jednaci;
//    if (strpos($cislo_jednaci, '//')) $cislo_jednaci = '';
    $cpole[] = $cislo_jednaci;
    $hod = array_count_values($cpole);
    $pp = 1;
    for ($i2=0; $i2<count($hod); $i2++) {
      if ($hod["$cislo_jednaci"]) {
        $pp = $hod["$cislo_jednaci"];
        break;
      } 
    }
    If ($GLOBALS["CONFIG"]["SHOW_C_JEDNACI"])
      $cislo_jednaci.=" - ".$pp;
    //echo $pp."<br>";
    list($znak,$pismeno,$lhuta)=Skartace($skartace);
 //  $znak=Skartace($q->Record["SKARTACE"]);

    if ($pismeno=='X' ) {$pocet_listu=0; $pocet_priloh=0;}//neni urceno ke skartaci

    $pocet_listu_celkem=$pocet_listu_celkem+$pocet_listu;
    $pocet_priloh_celkem[$druh_priloh]=$pocet_priloh_celkem[$druh_priloh]+$pocet_priloh;
    $cislo=$i1+1 .".";
    if (($pocet_listu==="{nb}")&&($format=='rtf')) 
      $pocet_listu = '{\\field{\\*\\fldinst {\\insrsid2691151  NUMPAGES }}{\\fldrslt {\\insrsid11226526 2}}}';

    $z=array("A0","A1","A2","A3","A4","A5","A6","A7","A8","A9","AA");
    $na=array($cislo,$cislo_jednaci,$vlozeno,$puvodce,$obsah,$pocet_listu,$pocet_priloh,$druh_priloh,$datum_vypraveni,$datum_doruceni,$datum_pm);
    if ($format=='rtf') {
    
      foreach ($na as &$n) 
        $n = TxtEncodingToWin($n);  
    }
    $hodnoty[$i1]=array($cislo,$cislo_jednaci,$vlozeno,$puvodce,$obsah,$pocet_listu,$pocet_priloh,$druh_priloh,$datum_vypraveni,$datum_doruceni,$datum_pm);
    $poznamka_pole[$i1]=$poznamka;
   $text.=Str_replace($z,$na,$radek);
    //$text.=$radek;
  }
   
  //echo $text;

  $podaci_cislo_bar='*'.$podaci_cislo.$code39[$kontrola].'*';
  fclose ($fp);
  

  $REFERENT_JMENO = iconv("utf-8", "cp1250", $REFERENT_JMENO);
  $odbor = UkazOdbor($w->Record["ODBOR"]);
  $skartace=$w->Record["SKARTACE"];
  $spis_vyrizen=$w->Record['SPIS_VYRIZEN'];
  $datum_vyrizeni=$w->Record['DATUM_VYRIZENI'];

  If (!$skartace) $skartace=0;
  

  $sql='select * from posta_spisobal where posta_id='.$min_id;
  $a->query($sql);
  $pocet=$a->Num_Rows();
  if ($pocet==0)
  {
    $sql='insert into posta_spisobal (POSTA_ID,LISTU) VALUES ('.$min_id.',0)';
    $a->query($sql);
  }
  if ($obal==1)
  {
    $sql='update posta_spisobal set listu=1 where posta_id='.$min_id;
    $a->query($sql);
  }
  else
  {
    $sql='update posta_spisobal set listu=0 where posta_id='.$min_id;
    $a->query($sql);
  }

  $spisZnak = $cj->SpisZnak($ID);
  $a->query($sql);
  $a->Next_Record();
  $skartace_text=$spisZnak['kod'] .' - ' . $spisZnak['znak'] . '/' . $spisZnak['doba'];

  if (!$spis_vyrizen) 
  { 
    $datum=$datum_vyrizeni;
    $date1 = substr($datum,0,strpos($datum," "));
    $datumkod=explode(".",$date1);
    $rok=$datumkod[2];
  }
  else
  {
    $date1=explode("-",$spis_vyrizen);
    $rok=$date1[0];
  }
  $rok=$rok+$spisZnak['doba']+1;
  if ($rok>1900)
    $skartace_text.=', '.$rok;

  if ($spisZnak['doba']==0) $skartace_text="";

  if ($format=='pdf')
  {

//Die(print_r($hodnoty));
    include('../pdf/spisprehled.php');   
  } else 
  if ($format=='doc') {
    include('doc.php');
  }
  else
  {

    $cj = LoadClass('EedCj', $ID);
    $cj_predchozi_text=array();
    $nasledujici_cj_text=array();
    $predchozi_cj = $cj->GetPredchoziCJ($ID);

    $nasledujici_cj = $cj->GetNasledujiciCJ($ID);

    if (count($predchozi_cj)>0 || count($nasledujici_cj)>0 ) {
      $kriz_vazba = 'Křížová vazba\par';
      $cj_temp = array();
      foreach($predchozi_cj as $val) {
        $cj_temp = LoadClass('EedDokument', $val);
        $cj_text[] = $cj_temp->FormatCisloJednaci($val);
        unset($cj_temp);
      }
      if (count($cj_text)>0) {
        $kriz_vazba .= ' Předcházející čj.: \par';
        $z = array("B0");
        $na = array(implode(', ', $cj_text));
        if ($format=='rtf') {
          foreach ($na as &$n)
            $n = TxtEncodingToWin($n);
        }
        $kriz_vazba .= Str_replace($z,$na,$radek_vazba);
      }

      $cj_text = array();
      foreach($nasledujici_cj as $val) {
        $cj_temp = LoadClass('EedDokument', $val);
        $cj_text[] = $cj_temp->FormatCisloJednaci($val);
        unset($cj_temp);
      }
      if (count($cj_text)>0) {
        $kriz_vazba .= ' Následující čj.: \par';
        $z = array("B0");
        $na = array(implode(', ', $cj_text));
        if ($format=='rtf') {
          foreach ($na as &$n)
            $n = TxtEncodingToWin($n);
        }
        $kriz_vazba .= Str_replace($z,$na,$radek_vazba);
      }


    }
    else
      $kriz_vazba = '';


    $urad = $GLOBALS['CONFIG']['URAD'].' '.$GLOBALS['CONFIG']['MESTO'];
    $datum_predani = Date('d.m.Y');
    $cas = Date('H:i');
    while (list($key,$val)=each($pocet_priloh_celkem)) {
      if ($val>0) {
        $z=array("TYP","POCET");
        $na=array($key,$val,$pz);
        $prilohy_celkem.=Str_replace($z,$na,$radek_prilohy);
      }
    }
    //$prilohy_celkem = "";
    
    $prilohy_celkem = TxtEncodingToWin($prilohy_celkem);
    
    $vec = ($GLOBALS['DIL_ID']!="")? TxtEncodingToWin($nazev_typoveho_spisu) : TxtEncodingToWin($vec);
    $zkratka_odboru_hlavni = iconv("utf-8", "cp1250", $zkratka_odboru_hlavni);
    $kriz_vazba = iconv("utf-8", "cp1250", $kriz_vazba);
    $pz = ($GLOBALS['DIL_ID']!="")? "Název typového spisu" : "Předmět řízení";
    $pz = iconv("utf-8", "cp1250", $pz);
    $z=array("CAS","DATUM_PREDANI","VLOZ_POCET_PRILOH","POCET_LISTU_CELKEM","SKARTACE_TEXT","ZKRATKA_ODBORU_H","URAD","CISLO_SPISU","DATUM_PRIJETI","VEC_DOPISU","REFERENT_JMENO","VLOZ_UREDNI_OSOBY","NAZEV_SPISU","CISLO_PODACI_TEXT","ODBOR_REFERENTA","ADRESA_ODESILATELE","ADRESA_URADU","CISLO_JEDNACI","DO_VLASTNICH_RUKOU","JEN_ADRESATOVI","JEJICH_CJ","VLOZ_RADKY","UZAVRENI_SPISU","LINE_2_CAPTION","KRIZ_VAZBA");
    //$na=array($cislo_spisu,$datum_prijeti,$vec,$REFERENT_JMENO,$text_ref, $nazev_spisu,$podaci_cislo,$odbor,$ODESILATEL,$adresa_uradu,$c_jednaci,$vlastni_rukou,$jen_adresatovi,$jejich_cj,$text,$uzavreni_spisu);
    $na=array($cas,$datum_predani,$prilohy_celkem,$pocet_listu_celkem,$skartace_text,$zkratka_odboru_hlavni,$urad,$cislo_spisu,$datum_prijeti,$vec,$REFERENT_JMENO,$text_ref, $nazev_spisu,$podaci_cislo,$odbor,$ODESILATEL,$adresa_uradu,$c_jednaci,$vlastni_rukou,$jen_adresatovi,$jejich_cj,$text,$uzavreni_spisu,$pz,$kriz_vazba);

    
    $vysledny=Str_replace($z,$na,$sablona);
  
    $vysledny=Str_replace("&nbsp;"," ",$vysledny);  
    $nazev='spisovy_prehled_'.$w->Record["EV_CISLO"].'-'.$w->Record["ROK"].'.rtf';
    Header("Content-Type: application/rtf");
    Header("Content-Disposition: attachment;filename=$nazev");
    echo $vysledny;   
  }
}
?>
