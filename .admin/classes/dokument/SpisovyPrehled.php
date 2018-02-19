<?php 

class SpisovyPrehled {
  
  /*
   * Contructor
   * @author luma
   */
  
  
  private $db;
  private $typovy_spis_mainid;
  public $cj;
  public $sql;
  private $min_id;
  public $text_ref;
  
  private $poznamky;
  public $text;
  private $poradi_referenta;
  
   function __construct($db, $typovy_spis_mainid) {
     $this->db = $db;
     $this->typovy_spis_mainid = $typovy_spis_mainid;
     $this->cj = LoadClass('EedCj', $typovy_spis_mainid);
     $this->text_ref ="";
     $this->poradi_referenta = 0;
     
   }
  
   public function getDilList($soucast) {
     $result = array();
     $dily = $this->cj->SeznamDiluvTypovemSpisuSoucasti($this->typovy_spis_mainid, $soucast);
     foreach($dily as $idckoDilu => $dil) {
       $dalsi_id = $this->cj->SeznamCJvTypovemSpisu($this->typovy_spis_mainid, $soucast,  $idckoDilu);
       foreach($dalsi_id as $key => $val) {
         $cj_typdil = LoadClass('EedCj', $val);
         $result[] = $val;
         $predchozi = $cj_typdil->GetPredchoziCJ($val);
         foreach($predchozi as $key2 => $val2) {
           $result[] = $val2;
         }
       }
     }
     return $result;
   }
   
   
   public function getSql($dil_id) {
     $dalsi_dokumenty = $this->cj->GetDocsInCj($dil_id);
     //$cj_info = $this->cj->GetCjInfo($dil_id);
     
     $cs = $this->cj->getCisloSpisu($dil_id);
     
     $cislo_spisu1 = $cs['CISLO_JEDNACI1'];
     $cislo_spisu2 = $cs['CISLO_JEDNACI2'];
     
     
     
     $where_spis = "and id in (" . $dil_id . "," . implode(',',$dalsi_dokumenty).")";
     $so_where = '';
     
     $this->sql['1'] = 'select * from posta where (1=1 '.$where_spis.')  and stornovano is null '.$so_where.' order by id asc ';
     
     $this->sql['2'] ='select * from posta_spisprehled_zaznamy where  1=1 '.$where_spis.' order by id asc ';
     
     $this->sql['3'] = "
     select p.referent, p.datum_referent_prijeti
     from posta p
     where p.cislo_spisu1 = $cislo_spisu1
     and p.cislo_spisu2 = $cislo_spisu2
     $so_where
     and stornovano is null
     order by p.ID ASC
     limit 1
     ";
     $this->sql['3a'] = "
     select count(*) as pocet
     from cis_posta_predani pp
     where pp.cislo_spisu1 = $cislo_spisu1
     and pp.cislo_spisu2 = $cislo_spisu2
     ";
     $this->sql['3b'] = "
     select distinct pp.old_referent, pp.referent, pp.datum
     from cis_posta_predani pp
     where pp.cislo_spisu1 = $cislo_spisu1
     and pp.cislo_spisu2 = $cislo_spisu2
     $so_where
     order by pp.datum
     ";
     $this->sql['3c'] = "
     select min(id) as id
     from posta p
     where p.cislo_spisu1 = $cislo_spisu1
     and p.cislo_spisu2 = $cislo_spisu2
     $so_where
     and stornovano is null
     ";     
   }
   
   public function getMinId() {
     $this->db->query($this->sql['3c']);
     while ($this->db->Next_Record()) $this->min_id = $this->db->Record["ID"];     
   }
   
   public function getPrvniDatum() {
     $this->sql['3d']= "
     select datum_referent_prijeti, datum_podatelna_prijeti, odeslana_posta,datum_vyrizeni,spis_vyrizen
     from posta
     where id = $this->min_id
     ";
     $this->db->query($this->sql['3d']);
     while ($this->db->Next_Record()) {
       $odp = $this->db->Record["ODESLANA_POSTA"];
       if ($odp) $prvni_datum = $this->db->Record["DATUM_PODATELNA_PRIJETI"];
       else $prvni_datum = $this->db->Record["DATUM_REFERENT_PRIJETI"];
     }
     return $prvni_datum;
   }
   
   public function getPoleOprav() {
     $j3 = 0;
     $this->db->query($this->sql['3']);
     while ($this->db->Next_Record()) {
       $pole_oprav[$j3]["referent"] = $this->db->Record["REFERENT"];
       $pole_oprav[$j3]["datum"] = $this->db->Record["DATUM_REFERENT_PRIJETI"];
       $j3++;
     }
     $this->db->query($this->sql['3a']);
     while ($this->db->Next_Record()) $pocet = $this->db->Record["POCET"];
     
     //print_r($pole_oprav);
     if ($pocet != "0") {
       $j3 = 0;
       $this->db->query($this->sql['3b']);
       while ($this->db->Next_Record()) {
         $pole_oprav[$j3]["old_referent"] = $this->db->Record["OLD_REFERENT"];
         $pole_oprav[$j3]["referent"] = $this->db->Record["REFERENT"];
         $pole_oprav[$j3]["datum"] = $this->db->Record["DATUM"];
         $j3++;
       }
     }
     return $pole_oprav;
   }
   
   public function getPole1($pole_oprav,$prvni_datum) {
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
     return $pole1;

   }
   
   public function vratReferenty($pole1,$format,$radek_uros = "") {
     //$this->text_ref ="";
     for ($i1=0; $i1<count($pole1); $i1++) {
       $_poradi = $i1+$this->poradi_referenta+1;
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
       $this->text_ref.= Str_replace($z,$na,$radek_uros);
       $referenti[]=$na;
     }
     $this->poradi_referenta = $_poradi;
     return $referenti;
   }
   
   public function vratTextRef() {
     return $this->text_ref;
   }
   
   public function getPoleSsz() {
     $this->db->query($this->sql['1']);
     $predchozi_ev='';
     $i=0;
     $j1 = 1;
     if ($obal==1) $j1 = 2;
     
     while ($this->db->Next_Record()) {
       if (!$zkratka_odboru_hlavni) $zkratka_odboru_hlavni = UkazOdbor($this->db->Record["ODBOR"],true,false);
       $pole_ssz[$j1]["id"] = $this->db->Record["ID"];
       $_odesilatel = "";
       $_odesilatel = UkazAdresu($pole_ssz[$j1]["id"],', ');
       $puvodce = $_odesilatel;
       $odeslana_posta = $this->db->Record["ODESLANA_POSTA"];
       $pole_ssz[$j1]["_referent"] = $this->db->Record["REFERENT"];
       $pole_ssz[$j1]["_odbor"] = $this->db->Record["ODBOR"];
       if ($odeslana_posta == "t") {
         $puvodce = $CONFIG["URAD"]." ".$CONFIG["MESTO"].", ".UkazOdbor($pole_ssz[$j1]["_odbor"]).", ".UkazUsera($pole_ssz[$j1]["_referent"]);
       }
       if ($this->db->Record["ODES_TYP"] == "Z") $puvodce = "Vlastní záznam";
       $pole_ssz[$j1]["puvodce"] = $puvodce;
       $pole_ssz[$j1]["datum_podatelna_prijeti"] = $this->db->Record["DATUM_PODATELNA_PRIJETI"];
       $pole_ssz[$j1]["trideni"] = MakeStamp($pole_ssz[$j1]["datum_podatelna_prijeti"]);
       $pole_ssz[$j1]["obsah"] = $this->db->Record["VEC"];
       $pole_ssz[$j1]["_cislo_jednaci1"] = $this->db->Record["CISLO_JEDNACI1"];
       $pole_ssz[$j1]["_cislo_jednaci2"] = $this->db->Record["CISLO_JEDNACI2"];
       $pole_ssz[$j1]["zkratka_odboru"] = UkazOdbor($this->db->Record["ODBOR"],true,false);
       if ($this->db->Record["TYP_DOKUMENTU"]=='D')
       {
         $pole_ssz[$j1]["pocet_listu"] = 0;
         $pole_ssz[$j1]["pocet_priloh"] = 1;
         $pole_ssz[$j1]["druh_priloh"] = 'digitální';
       }
       else
       {
         $pole_ssz[$j1]["pocet_listu"] = $this->db->Record["POCET_LISTU"];
         $pole_ssz[$j1]["pocet_priloh"] = $this->db->Record["POCET_PRILOH"];
         $pole_ssz[$j1]["druh_priloh"] = $this->db->Record["DRUH_PRILOH"];
       }
       /*
        if ($this->db->Record["TYP_DOKUMENTU"]<>'D' && $this->db->Record["ODES_TYP"]=='X')
        {
        $pole_ssz[$j1]["pocet_listu"] = 0;
        $pole_ssz[$j1]["pocet_priloh"] = 0;
        //      $pole_ssz[$j1]["druh_priloh"] = 'digitální';
        }
        */
       $pole_ssz[$j1]["predchozi_ev"] = $this->db->Record["EV_CISLO"];
       $pole_ssz[$j1]["datum_pm"] = $this->db->Record["DATUM_PM"];
       $pole_ssz[$j1]["datum_doruceni"] = $this->db->Record["DATUM_DORUCENI"];
       $pole_ssz[$j1]["datum_vypraveni"] = $this->db->Record["DATUM_VYPRAVENI"];
       $pole_ssz[$j1]["cislo_spisu1"] = $this->db->Record["CISLO_SPISU1"];
       $pole_ssz[$j1]["cislo_spisu2"] = $this->db->Record["CISLO_SPISU2"];
       $pole_ssz[$j1]["podcislo_spisu"] = $this->db->Record["PODCISLO_SPISU"];
       $pole_ssz[$j1]["skartace"] = $this->db->Record["SKARTACE"];
       $pole_ssz[$j1]["poznamka"] = $this->db->Record["POZNAMKA"];
       $j1++;
     }
     //print_r($pole_ssz);
     //unset($pole_ssz);
     $this->db->query($this->sql['2']);
     //$j1 = 0;
     while ($this->db->Next_Record()) {
       $pole_ssz[$j1]["id"] = $this->db->Record["ID"];
       $_odesilatel = "";
       $_odesilatel = UkazAdresu($pole_ssz[$j1]["id"],', ','posta_spisprehled_zaznamy');
       $puvodce = $_odesilatel;
       $pole_ssz[$j1]["puvodce"] = $puvodce;
       $pole_ssz[$j1]["datum_podatelna_prijeti"] = $this->db->Record["DATUM_PODATELNA_PRIJETI"];
       $pole_ssz[$j1]["trideni"] = MakeStamp($pole_ssz[$j1]["datum_podatelna_prijeti"]);
       $pole_ssz[$j1]["obsah"] = $this->db->Record["VEC"];
       $pole_ssz[$j1]["_cislo_jednaci1"] = $this->db->Record["CISLO_JEDNACI1"];
       $pole_ssz[$j1]["_cislo_jednaci2"] = $this->db->Record["CISLO_JEDNACI2"];
       $pole_ssz[$j1]["_referent"] = $this->db->Record["REFERENT"];
       $pole_ssz[$j1]["_odbor"] = $this->db->Record["ODBOR"];
       $pole_ssz[$j1]["zkratka_odboru"] = UkazOdbor($this->db->Record["ODBOR"],true,false);
       $pole_ssz[$j1]["pocet_listu"] = ($this->db->Record["TYP_DOKUMENTU"]=='D'?0:$this->db->Record["POCET_LISTU"]);
       $pole_ssz[$j1]["pocet_priloh"] = ($this->db->Record["TYP_DOKUMENTU"]=='D'?1:$this->db->Record["POCET_PRILOH"]);
       $pole_ssz[$j1]["druh_priloh"] = ($this->db->Record["TYP_DOKUMENTU"]=='D'?'digitální':$this->db->Record["DRUH_PRILOH"]);
       $pole_ssz[$j1]["predchozi_ev"] = $this->db->Record["EV_CISLO"];
       $pole_ssz[$j1]["datum_pm"] = $this->db->Record["DATUM_PM"];
       $pole_ssz[$j1]["datum_doruceni"] = $this->db->Record["DATUM_DORUCENI"];
       $pole_ssz[$j1]["datum_vypraveni"] = $this->db->Record["DATUM_VYPRAVENI"];
       $pole_ssz[$j1]["cislo_spisu1"] = $this->db->Record["CISLO_SPISU1"];
       $pole_ssz[$j1]["cislo_spisu2"] = $this->db->Record["CISLO_SPISU2"];
       $pole_ssz[$j1]["podcislo_spisu"] = $this->db->Record["PODCISLO_SPISU"];
       $pole_ssz[$j1]["poznamka"] = $this->db->Record["POZNAMKA"];
       //$pole_ssz[$j1]["puvodce"] = $puvodce;
       $j1++;
     }
     
     $pole_ssz[0]["puvodce"] = '';
     $pole_ssz[0]["datum_podatelna_prijeti"] = $this->db->Record["DATUM_PODATELNA_PRIJETI"];
     $pole_ssz[0]["trideni"] = MakeStamp($pole_ssz[$j1]["datum_podatelna_prijeti"]);
     $pole_ssz[0]["obsah"] = 'Spisový přehled';
     $pole_ssz[0]["_cislo_jednaci1"] = $this->db->Record["CISLO_JEDNACI1"];
     $pole_ssz[0]["_cislo_jednaci2"] = $this->db->Record["CISLO_JEDNACI2"];
     $pole_ssz[0]["_referent"] = $this->db->Record["REFERENT"];
     $pole_ssz[0]["_odbor"] = $this->db->Record["ODBOR"];
     $pole_ssz[0]["zkratka_odboru"] = UkazOdbor($this->db->Record["ODBOR"],true,false);
     $pole_ssz[0]["pocet_listu"] = '{nb}';
     $pole_ssz[0]["pocet_priloh"] = 0;
     $pole_ssz[0]["druh_priloh"] = '';
     $pole_ssz[0]["predchozi_ev"] = $this->db->Record["EV_CISLO"];
     $pole_ssz[0]["datum_pm"] = $this->db->Record["DATUM_PM"];
     $pole_ssz[0]["datum_doruceni"] = $this->db->Record["DATUM_DORUCENI"];
     $pole_ssz[0]["datum_vypraveni"] = $this->db->Record["DATUM_VYPRAVENI"];
     $pole_ssz[0]["cislo_spisu1"] = $this->db->Record["CISLO_SPISU1"];
     $pole_ssz[0]["cislo_spisu2"] = $this->db->Record["CISLO_SPISU2"];
     $pole_ssz[0]["podcislo_spisu"] = $this->db->Record["PODCISLO_SPISU"];
     
     if ($obal==1)
     {
       $pole_ssz[1]["puvodce"] = '';
       $pole_ssz[1]["datum_podatelna_prijeti"] = $this->db->Record["DATUM_PODATELNA_PRIJETI"];
       $pole_ssz[1]["trideni"] = MakeStamp($pole_ssz[$j1]["datum_podatelna_prijeti"]);
       $pole_ssz[1]["obsah"] = 'Spisový přebal';
       $pole_ssz[1]["_cislo_jednaci1"] = $this->db->Record["CISLO_JEDNACI1"];
       $pole_ssz[1]["_cislo_jednaci2"] = $this->db->Record["CISLO_JEDNACI2"];
       $pole_ssz[1]["_referent"] = $this->db->Record["REFERENT"];
       $pole_ssz[1]["_odbor"] = $this->db->Record["ODBOR"];
       $pole_ssz[1]["zkratka_odboru"] = UkazOdbor($this->db->Record["ODBOR"],true,false);
       $pole_ssz[1]["pocet_listu"] = 1;
       $pole_ssz[1]["pocet_priloh"] = 0;
       $pole_ssz[1]["druh_priloh"] = '';
       $pole_ssz[1]["predchozi_ev"] = $this->db->Record["EV_CISLO"];
       $pole_ssz[1]["datum_pm"] = $this->db->Record["DATUM_PM"];
       $pole_ssz[1]["datum_doruceni"] = $this->db->Record["DATUM_DORUCENI"];
       $pole_ssz[1]["datum_vypraveni"] = $this->db->Record["DATUM_VYPRAVENI"];
       $pole_ssz[1]["cislo_spisu1"] = $this->db->Record["CISLO_SPISU1"];
       $pole_ssz[1]["cislo_spisu2"] = $this->db->Record["CISLO_SPISU2"];
       $pole_ssz[1]["podcislo_spisu"] = $this->db->Record["PODCISLO_SPISU"];
     }
     
     return $pole_ssz;
   }
   
   public function vratHodnoty($pole_ssz,$radek) {
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
     $this->poznamky = $poznamka_pole;
     $this->text = $text;
     if (!is_array($hodnoty)) $hodnoty = "N/A";
     return $hodnoty;
     
   }
   
   public function vratPoznamky() {
     return $this->poznamky;
   }
   
   public function vratText() {
     return $this->text;
   }
    
}

?>