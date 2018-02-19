<?php

require_once(FileUp2('.admin/classes/dokument/SpisovyPrehled.php'));


If ($sablona=='prehled_dilu')
{
  $poznamka_pole = array();
  
//echo $sablona."<br />";
  $fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/prehled_dilu2.rtf");
  $fp = fopen ($fn, "r");
  $sablona = fread ($fp, filesize ($fn));

  //$fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek2.rtf");ulti
  $fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek_zpracovatel.rtf");
  $fp = fopen ($fn, "r");
  $radek_uros = fread ($fp, filesize ($fn));
  
  $fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/prehled_dilu_tabulka2.rtf");
  $fp = fopen ($fn, "r");
  $tabulka = fread ($fp, filesize ($fn));
  

  //$fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek.rtf");
  $fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek_prehled.rtf");
  $fp = fopen ($fn, "r");
  $radek = fread ($fp, filesize ($fn));

  //$fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek.rtf");
  $fn = FileUpUrl("./".$GLOBALS["CONFIG"]["PREFIX"]."/radek_prilohy2.rtf");
  $fp = fopen ($fn, "r");
  $radek_prilohy = fread ($fp, filesize ($fn));
  
  $a=new DB_POSTA;

  $uzavreni_spisu=str_replace('&nbsp;','',$a->dbdate2str($w->Record["SPIS_VYRIZEN"]));

  

  $sp = new SpisovyPrehled($a, $GLOBALS["ID"]);
  
  //$cj= $sp->cj;
  
/*  $dalsi_dokumenty=$sp->cj->GetDocsInCj($GLOBALS["ID"]);
  
  $cj_info = $cj->GetCjInfo($GLOBALS["ID"]);
  if ($cj_info['JE_TYPOVY_SPIS']>0) {
    $nazev_typoveho_spisu = $cj->NazevTypovehoSpisu($cj_info['TYPOVY_SPIS_MAINID']);
  }*/
  $nazev_typoveho_spisu = $sp->cj->NazevTypovehoSpisu($GLOBALS["ID"]);
  
  

  $casti = EedTools::GetSoucastiTypovehoSpisu($GLOBALS["ID"]);
  
  $text_ref = "";
  $soucasti_text = "";  

  
 /* $sql = $sp->getSql($GLOBALS["ID"],$cislo_spisu1,$cislo_spisu2);
  $pole_oprav['o'] = $sp->getPoleOprav();
  $pole1 = $sp->getPole1($pole_oprav);
      $referenti = $sp->vratReferenty($pole1,$format);
      $text_ref.= $sp->vratTextRef();*/
  
      
  while (list($idSoucast, $soucast) = each($casti)) {
    
    $dil_list = $sp->getDilList( $soucast['SOUCAST']);
    //pro kazdou soucast vytvorit nadpis
    $text = "";
    
    
    foreach ($dil_list as $dil_id) {
      $sql = $sp->getSql($dil_id);
      $min_id = $sp->getMinId();
      $prvni_datum = $sp->getPrvniDatum();
      $pole_oprav[$dil_id] = $sp->getPoleOprav();
      $pole1[$dil_id] = $sp->getPole1($pole_oprav[$dil_id],$prvni_datum);
      if (is_array($referenti))
      $referenti = array_merge($referenti,$sp->vratReferenty($pole1[$dil_id],$format,$radek_uros));
      else
        $referenti = $sp->vratReferenty($pole1[$dil_id],$format,$radek_uros);
      $text_ref.= $sp->vratTextRef();
      $pole_ssz[$dil_id] = $sp->getPoleSsz();
/*      $hodnoty[$dil_id]= $sp->vratHodnoty($pole_ssz[$dil_id]);
      $poznamka_pole[$dil_id] = $sp->vratPoznamky();
      $text[$dil_id] = $sp->vratText();*/
      if (is_array($hodnoty[$idSoucast]))
        $hodnoty[$idSoucast]= array_merge($hodnoty[$idSoucast],$sp->vratHodnoty($pole_ssz[$dil_id],$radek));
      else 
        $hodnoty[$idSoucast]= $sp->vratHodnoty($pole_ssz[$dil_id],$radek);       
        
      if (is_array($poznamka_pole[$idSoucast]))
        $poznamka_pole[$idSoucast] = array_merge($poznamka_pole[$idSoucast],$sp->vratPoznamky());
      else
        $poznamka_pole[$idSoucast] = $sp->vratPoznamky();
      
      if (is_array($text[$idSoucast]))
        $text[$idSoucast] = array_merge($text[$idSoucast],$sp->vratText());
      else
        $text[$idSoucast] = $sp->vratText();
     
        $soucast_text[$idSoucast][] = $sp->text;
        
              
    }
        
    
    if (sizeof($dil_list)==0) {
      $hodnoty[$idSoucast] = "";
      $soucast_text[$idSoucast][] = "";
    }

  }
  
  
  //priprava radku pro editovatelnou cast
  $n_soucast = 0;
  foreach ($soucast_text as $ids => $st){
    $n_soucast++;
    $radky = "";
    foreach ($st as $line) {
      $radky.=$line;
    }
    $soucast_cislo = "Součást číslo: ".$n_soucast;
    $z=array("SOUCAST_CISLO","VLOZ_RADKY","VLOZ_SOUCAST");
    $na=array($soucast_cislo,$radky,"");
    foreach ($na as &$n) 
      $n = TxtEncodingToWin($n);
    
    $soucasti_text.=Str_replace($z,$na,$tabulka);
    
  }


/*  $so_where = '';
  if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) {
    $sql_so='select superodbor from posta where id in ('.$ID.')  ';
    $a->query($sql_so); $a->Next_Record();
    $so = $a->Record['SUPERODBOR'];
    if ($so>0)    $so_where = 'AND superodbor in ('. $so . ')';
  }
  $so_where = '';*/
  //tak vyplnime jednotlive radky tabulky



 

 
  //while ($a->Next_Record()) {
//  $pole_ssz = Array_sort_key($pole_ssz,"trideni","asc");
//  print_r($pole_ssz);Die();
  //print_r($pole_ssz);
 
  //echo $text;
  //die();
  
//  }

  $podaci_cislo_bar='*'.$podaci_cislo.$code39[$kontrola].'*';
  fclose ($fp);
  

  $REFERENT_JMENO = iconv("utf-8", "cp1250", $REFERENT_JMENO);
  $odbor = UkazOdbor($w->Record["ODBOR"]);
  $skartace=$w->Record["SKARTACE"];
  $spis_vyrizen=$w->Record['SPIS_VYRIZEN'];
  $datum_vyrizeni=$w->Record['DATUM_VYRIZENI'];

  If (!$skartace) $skartace=0;
  

 /* $sql='select * from posta_spisobal where posta_id='.$min_id;
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
*/


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
    include('../pdf/spisprehled_dilu.php');   
  } else 
  if ($format=='doc') {
    include('doc.php');
  }
  else
  {
    $urad = $GLOBALS['CONFIG']['URAD'].' '.$GLOBALS['CONFIG']['MESTO'];
    $datum_predani = Date('d.m.Y');
    $cas = Date('H:i');
 /*   while (list($key,$val)=each($pocet_priloh_celkem)) {
      if ($val>0) {
        $z=array("TYP","POCET");
        $na=array($key,$val,$pz);
        $prilohy_celkem.=Str_replace($z,$na,$radek_prilohy);
      }
    }*/
    $prilohy_celkem = "";
    
    $prilohy_celkem = TxtEncodingToWin($prilohy_celkem);
    $text_ref = $sp->text_ref;
    $vec = ($GLOBALS['DIL_ID']!="")? TxtEncodingToWin($nazev_typoveho_spisu) : TxtEncodingToWin($vec);
    $zkratka_odboru_hlavni = iconv("utf-8", "cp1250", $zkratka_odboru_hlavni);
    $pz = ($GLOBALS['DIL_ID']!="")? "Název typového spisu" : "Předmět řízení";
    $pz = iconv("utf-8", "cp1250", $pz);
    $z=array("CAS","DATUM_PREDANI","VLOZ_POCET_PRILOH","POCET_LISTU_CELKEM","SKARTACE_TEXT","ZKRATKA_ODBORU_H","URAD","CISLO_SPISU","DATUM_PRIJETI","VEC_DOPISU","REFERENT_JMENO","VLOZ_UREDNI_OSOBY","NAZEV_SPISU","CISLO_PODACI_TEXT","ODBOR_REFERENTA","ADRESA_ODESILATELE","ADRESA_URADU","CISLO_JEDNACI","DO_VLASTNICH_RUKOU","JEN_ADRESATOVI","JEJICH_CJ","VLOZ_RADKY","UZAVRENI_SPISU","LINE_2_CAPTION","VLOZ_SOUC");
    //$na=array($cislo_spisu,$datum_prijeti,$vec,$REFERENT_JMENO,$text_ref, $nazev_spisu,$podaci_cislo,$odbor,$ODESILATEL,$adresa_uradu,$c_jednaci,$vlastni_rukou,$jen_adresatovi,$jejich_cj,$text,$uzavreni_spisu);
    $na=array($cas,$datum_predani,$prilohy_celkem,$pocet_listu_celkem,$skartace_text,$zkratka_odboru_hlavni,$urad,$cislo_spisu,$datum_prijeti,$vec,$REFERENT_JMENO,$text_ref, $nazev_spisu,$podaci_cislo,$odbor,$ODESILATEL,$adresa_uradu,$c_jednaci,$vlastni_rukou,$jen_adresatovi,$jejich_cj,$text,$uzavreni_spisu,$pz,$soucasti_text);
    
    
    
    $vysledny=Str_replace($z,$na,$sablona);
  
    $vysledny=Str_replace("&nbsp;"," ",$vysledny);  
    $nazev='spisovy_prehled_'.$w->Record["EV_CISLO"].'-'.$w->Record["ROK"].'.rtf';
    Header("Content-Type: application/rtf");
    Header("Content-Disposition: attachment;filename=$nazev");
    echo $vysledny;   
  }
}
?>
