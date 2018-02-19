<?php
// priradime podcislo k cislu jednacimu
Function ZalozNovyDokument($ID,$otoc=0,$zalozeni=0,$odesl_array = null) {

	//zalozeni = 1 - interni posta
	//zalozeni = 3 - kopie
  $davatExemplar = true;
  if ($zalozeni == 4) {$davatExemplar = false;}

  $q=new DB_POSTA;
  $sql="SELECT * FROM posta WHERE ID IN (".$ID.")";
  $q->query($sql);
  //echo $sql;
  $q->Next_Record();
  
  $datum_prijeti = date('d.m.Y H:i:s');
  $cislo_spisu1 = $q->Record["CISLO_SPISU1"] ? $q->Record["CISLO_SPISU1"] : 0;
  $cislo_spisu2 = $q->Record["CISLO_SPISU2"] ? $q->Record["CISLO_SPISU2"] : 0;
  $nazev_spisu = $q->Record["NAZEV_SPISU"];
  $podcislo_spisu = $q->Record["PODCISLO_SPISU"] ? $q->Record["PODCISLO_SPISU"] : 0;
  $cislo_jednaci1 = $q->Record["CISLO_JEDNACI1"] ? $q->Record["CISLO_JEDNACI1"] : 0;
  $cislo_jednaci2 = $q->Record["CISLO_JEDNACI2"] ? $q->Record["CISLO_JEDNACI2"] : 0;
  $odes_typ = $q->Record["ODES_TYP"];
  $odesl_prijmeni = $q->Record["ODESL_PRIJMENI"];
  $odesl_jmeno = $q->Record["ODESL_JMENO"];
  $odesl_titul = $q->Record["ODESL_TITUL"];
  $odesl_ico = $q->Record["ODESL_ICO"];
  $odesl_odbor = $q->Record["ODESL_ODBOR"];
  $odesl_osoba = $q->Record["ODESL_OSOBA"];
  $odesl_adrkod = $q->Record["ODESL_ADRKOD"] ? $q->Record["ODESL_ADRKOD"] : 0;
  $odesl_ulice = $q->Record["ODESL_ULICE"];
  $odesl_email = $q->Record["ODESL_EMAIL"];
  $odesl_subj = $q->Record["ODESL_SUBJ"];
  $odesl_body = str_replace("'","",$q->Record["ODESL_BODY"]);
  $odesl_cp = $q->Record["ODESL_CP"];
  $odesl_cor = $q->Record["ODESL_COR"];
  $odesl_psc = $q->Record["ODESL_PSC"];
  $superodbor = $q->Record["SUPERODBOR"]  ?  $q->Record["SUPERODBOR"] : 0;
  $odesl_posta = $q->Record["ODESL_POSTA"];
  $odesl_datschranka = $q->Record["ODESL_DATSCHRANKA"];
  $odesl_odd = $q->Record["ODESL_ODD"];
  $odesl_osoba = $q->Record["ODESL_OSOBA"];
  $typ_dokumentu = $q->Record["TYP_DOKUMENTU"];
  $text_cj = $q->Record["TEXT_CJ"];
  $vlastnich_rukou = $q->Record["VLASTNICH_RUKOU"] ? $q->Record["VLASTNICH_RUKOU"] : 'NULL';
  $objekt_kod = $q->Record["OBJEKT_KOD"] ? $q->Record["OBJEKT_KOD"] : 0;
  $okres_kod = $q->Record["OKRES_KOD"] ? $q->Record["OKRES_KOD"] : 0;
  $vec = str_replace("'","",$q->Record["VEC"]);
  $main_doc = $q->Record["MAIN_DOC"] ? $q->Record["MAIN_DOC"] : 0;
  $rok = date('Y');

  $puvodni_spis = $cislo_spisu1."/".$cislo_spisu2;  
  //do cj ulozime bud cj puvodni (z dokumentu mezi vnitrni spravou a samospravou) a nebo cj firmy (u kopirovani na vice cj)
  If (!$GLOBALS[zalozeni]) {
    $doc = LoadSingleton('EedDokument', $ID);
    $jejich_cj = $doc->cislo_jednaci;
    $jejich_cj_dne = "'".Date('Y-m-d')."'";
  }
  else {
    $doc = LoadSingleton('EedDokument', $ID);
    $jejich_cj=$q->Record["JEJICH_CJ"];
    $jejich_cj_dne=$q->Record["JEJICH_CJ_DNE"] ? "'".$q->Record["JEJICH_CJ_DNE"]."'" : 'NULL';
  }
  
  $pocet_priloh=$q->Record["POCET_PRILOH"]?$q->Record["POCET_PRILOH"]:0;
  $pocet_listu=$q->Record["POCET_LISTU"]?$q->Record["POCET_LISTU"]:0;
  $druh_priloh=$q->Record["DRUH_PRILOH"];
  $zpusob_podani=$q->Record["ZPUSOB_PODANI"];
  $odbor=$q->Record["ODBOR"] ? $q->Record["ODBOR"] : 0;
  $jine=$q->Record["JINE"];
  $typ_posty=$q->Record["TYP_POSTY"]?$q->Record["TYP_POSTY"]:'NULL';
  $stav=$q->Record["STAV"]?$q->Record["STAV"]:0;
  //$dalsi_prijemci=$q->Record["DALSI_PRIJEMCI"]; 
  $dalsi_prijemci=''; //vypnuto, at se nekopiruji
  $poznamka=$q->Record["POZNAMKA"];
  $lhuta = $q->Record['LHUTA'];
  If ($lhuta=="") $lhuta=30;
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  $jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
  $LAST_USER_ID=$id_user;
  $OWNER_ID=$id_user;
  $LAST_TIME=Date('H:i:s');
  $LAST_DATE=Date('Y-m-d');
  $dnes=Date('d.m.Y H:i');
  $id_puvodni=$ID;
  
  
  $referent=0;
  $oddeleni=0;
  if ($otoc==1)
  {
    $odbor=$q->Record["ODBOR"];
    $oddeleni=$q->Record["ODDELENI"];
    $referent=$q->Record["REFERENT"];
    //jdeme otocit nektere hodnoty...
    $odbor_x=$odbor;
    $referent_x=$referent;
    $oddeleni_x=$oddeleni;
  
    $odbor=$odesl_ulice?$odesl_ulice:0;
    $referent=$odesl_osoba?$odesl_osoba:0;
    $oddeleni=$odesl_odd?$odesl_odd:0;
    
    $odesl_ulice=$odbor_x;
    $odesl_osoba=$referent_x;
    $odesl_odd=$oddeleni_x;
    
    if is_array($odesl_array) {
      $odesl_ulice = $odesl_array['odesl_ulice'];  
      $odesl_osoba = $odesl_array['odesl_osoba'];
      $odesl_odd = $odesl_array['odesl_odd'];
    }
    
    $odesl_prijmeni=UkazOdbor($odesl_ulice);
    $odesl_jmeno=UkazUsera($odesl_osoba);
  
    $zpusob_podani=3;
    $druh_priloh='elektronické';
  
    $doc = LoadSingleton('EedDokument', $ID);
    $jejich_cj = $doc->cislo_jednaci;

  }

  if ($typ_dokumentu == 'D') {
//    $druh_priloh = 'elektronické';
    $zpusob_podani = 3;
  }
  else {
//    $druh_priloh = 'písemné';
    $zpusob_podani = 1;
  }

  if ($zalozeni==2 || $zalozeni==3 || $zalozeni==4) //zalozime na stejny odbor a stejnemu referentovi
  {
    $odbor=$q->Record["ODBOR"]?$q->Record["ODBOR"]:0;
    $oddeleni=$q->Record["ODDELENI"]?$q->Record["ODDELENI"]:0;
    $referent=$q->Record["REFERENT"]?$q->Record["REFERENT"]:0;
  }
  $add_column=',ODESL_EMAIL, ODESL_BODY, ODESL_SUBJ';
  $add_value=",'$odesl_email','$odesl_body','$odesl_subj'";
  $odeslana_posta = 'f';
  if ($GLOBALS['CONFIG']['INTERNI_POSTA_VYTVARI_ARCH'] && $zalozeni  == 1) {//zalozime pod stejnzm cj.
    $add_column=',CISLO_JEDNACI1,CISLO_JEDNACI2,CISLO_SPISU1,CISLO_SPISU2,PODCISLO_SPISU';
    $add_value=",$cislo_jednaci1,$cislo_spisu2,$cislo_jednaci1,$cislo_spisu2,$podcislo_spisu";
  }

  if ($zalozeni==3) {//zalozime pod stejnzm cj.
    $add_column=',CISLO_JEDNACI1,CISLO_JEDNACI2,CISLO_SPISU1,CISLO_SPISU2,PODCISLO_SPISU,kopie';
    $add_value=",$cislo_jednaci1,$cislo_jednaci2,$cislo_spisu1,$cislo_spisu2,$podcislo_spisu,1";
  }

  if ($zalozeni==4) {//zalozime pod stejnzm cj. ale bey priznaku kopie
    $add_column=',CISLO_JEDNACI1,CISLO_JEDNACI2,CISLO_SPISU1,CISLO_SPISU2,PODCISLO_SPISU';
    $add_value=",$cislo_jednaci1,$cislo_jednaci2,$cislo_spisu1,$cislo_spisu2,$podcislo_spisu";
    $id_old_puvodni = $id_puvodni; //abychom pak prekopirovali soubory
    $id_puvodni = "NULL";
  }

  // zalozime novy radek v posta
  If (!$zalozeni)
  {$sql="INSERT INTO posta (ev_cislo,lhuta,odeslana_posta,rok,datum_podatelna_prijeti,odes_typ,odesl_prijmeni,odesl_jmeno,odesl_titul,odesl_ico,odesl_osoba,odesl_odd,odesl_ulice,odesl_cp,odesl_cor,odesl_adrkod,odesl_psc,odesl_posta,odesl_datschranka,vec,objekt_kod,okres_kod,jejich_cj,jejich_cj_dne,pocet_priloh,pocet_listu,druh_priloh,zpusob_podani,typ_posty,stav,poznamka,last_date,last_time,last_user_id,id_puvodni,typ_dokumentu,jine,superodbor,main_doc".
  ") VALUES (".
  "0,$lhuta,'f',$rok,'$datum_prijeti','$odes_typ','$odesl_prijmeni','$odesl_jmeno','$odesl_titul','$odesl_ico','$odesl_osoba','$odesl_odd','$odesl_ulice','$odesl_cp','$odesl_cor','$odesl_adrkod','$odesl_psc','$odesl_posta','$odesl_datschranka','$vec',$objekt_kod,$okres_kod,'$jejich_cj',$jejich_cj_dne,$pocet_priloh,$pocet_listu,'$druh_priloh','$zpusob_podani',$typ_posty,$stav,'$poznamka','$LAST_DATE','$LAST_TIME','$LAST_USER_ID',$id_puvodni,'$typ_dokumentu','$jine',$superodbor,$main_doc)";
  $prefix='_vnitrni';
  }
  else
  {$sql="INSERT INTO posta (ev_cislo,lhuta,referent,odeslana_posta,rok,odbor,oddeleni,datum_podatelna_prijeti,odes_typ,odesl_prijmeni,odesl_jmeno,odesl_titul,odesl_ico,odesl_osoba,odesl_odd,odesl_ulice,odesl_cp,odesl_cor,odesl_adrkod,odesl_psc,odesl_posta,odesl_datschranka,vec,objekt_kod,okres_kod,nazev_spisu,jejich_cj,jejich_cj_dne,pocet_priloh,pocet_listu,druh_priloh,zpusob_podani,typ_posty,stav,dalsi_prijemci,last_date,last_time,last_user_id,poznamka,id_puvodni,typ_dokumentu,jine,superodbor,datum_predani,main_doc,vlastnich_rukou".
  "$add_column) VALUES (".
  "0,$lhuta,$referent,'f',$rok,$odbor,$oddeleni,'$datum_prijeti','$odes_typ','$odesl_prijmeni','$odesl_jmeno','$odesl_titul','$odesl_ico','$odesl_osoba','$odesl_odd','$odesl_ulice','$odesl_cp','$odesl_cor','$odesl_adrkod','$odesl_psc','$odesl_posta','$odesl_datschranka','$vec',$objekt_kod,$okres_kod,'$nazev_spisu','$jejich_cj',$jejich_cj_dne,$pocet_priloh,$pocet_listu,'$druh_priloh','$zpusob_podani',$typ_posty,$stav,'$dalsi_prijemci','$LAST_DATE','$LAST_TIME','$LAST_USER_ID','$poznamka',$id_puvodni,'$typ_dokumentu','$jine',$superodbor,'$datum_prijeti',$main_doc,$vlastnich_rukou$add_value)";
  $prefix='';
  }

  //echo $sql;Flush();
  $q->query($sql);
  $NOVEID=$q->getlastid('posta','ID');
  
  if ($otoc==1) {
    $sql="UPDATE posta SET datum_doruceni='$datum_prijeti',datum_predani_ven='$datum_prijeti',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID  where id=".$ID;
    $q->query($sql);
    $sql="UPDATE posta SET datum_predani='$datum_prijeti',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID  where id=".$NOVEID;
    $q->query($sql);
  
  }
  
  if ($zalozeni==3 || $zalozeni==4) {
    $sql="UPDATE posta SET datum_predani='$datum_prijeti',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID  where id=".$NOVEID;
    $q->query($sql);
  }

  If (!$zalozeni)
  {
    $sql="UPDATE posta SET dalsi_id_agenda=$NOVEID,datum_vypraveni='$dnes',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id=".$ID;
    $q->query($sql);
  }
  else
  {
    if ($zalozeni<>4)
    {
      $sql="UPDATE posta SET dalsi_id_agenda=$NOVEID,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID  where id=".$ID;
      $q->query($sql); //pro kopie nedelat
    }
  }

  if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) {
//    $EedUser = LoadClass('EedUser', 0);
//    $so = $EedUser->NajdiZarizeniId($odbor);
    $so = EedTools::NajdiSuperOdborId($odbor);
    $append = '';
    $uzel = $doc->VratOdborZSpisUzlu($odbor);
    if ($so == $uzel) //pokud je dan odbor jako superodbor, tak nechame jen superodbor a vynulujeme odbor - pak to dostaneme na podateln
      $append = 'odbor=NULL,';
    if ($so>0) {
      $sql="UPDATE posta SET superodbor=$so, $append last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID  where id=".$NOVEID;
      $q->query($sql);
    }
  }
  if ($zalozeni==1 && $GLOBALS['CONFIG']['INTERNI_POSTA_VYTVARI_ARCH']) {
	EedTools::PriradPodcislo($NOVEID);
  }
  
  if ($zalozeni==3 || $zalozeni==4) {
    if ($davatExemplar) EedTools::PriradExemplar($NOVEID);
	  else EedTools::PriradPodcislo($NOVEID);
  }

  
  if ($zalozeni==1 && $GLOBALS['CONFIG']['ZALOZIT_SPIS_U_INTERNI_POSTY'])  {

    $sql="select * from posta where id=".$NOVEID;
    $q->query($sql);
    $q->Next_Record();
    $novy_spis=$q->Record['CISLO_SPISU1']."/".$q->Record['CISLO_SPISU2'];

    $cj_obj = new EedCj($ID);
  
  //  $cj_info = $cj_obj->show_debug_sql = true;
  //  $cj_info = $cj_obj->show_debug_work = true;
    $cj_info = $cj_obj->GetCjInfo($ID);
    $spis_id = $cj_info['SPIS_ID'];

    $sql="insert into cis_posta_spisy (PUVODNI_SPIS,NOVY_SPIS,SPIS_ID,DALSI_SPIS_ID,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID)
    VALUES ('$puvodni_spis','$novy_spis',$spis_id,$NOVEID,'$LAST_DATE','$LAST_TIME',$OWNER_ID,$LAST_USER_ID)";
    //Die($sql);
    $q->query($sql);



    $cj_obj = new EedCj($NOVEID);
    $cj_info = $cj_obj->GetCjInfo($NOVEID);
    $ns = $cj_info['CELE_CISLO'];

    $spis_obj = LoadSingleton('EedCj', $spis_id);
    $spis_info = $spis_obj->GetCjInfo($spis_id);

    $spis_nazev = $spis_info['CELY_NAZEV'];


//    $text = 'Vytvoření nového dokumentu';
    $text = 'Vytvoření nového dokumentu interní pošty - vytvořeno z odeslaného dokumentu (<b>' . $ID . '</b>) ' . $ns . '';
    EedTransakce::ZapisLog($NOVEID, $text, 'DOC', $id_user);

    $text = 'dokument (<b>'.$NOVEID.'</b>) '.$ns.' byl vložen do spisu: <b>' . $spis_nazev . '</b>';
    EedTransakce::ZapisLog($NOVEID, $text, 'DOC', $id_user);
    EedTransakce::ZapisLog($spis_id, $text, 'SPIS', $id_user);

    $text = 'dokument (<b>'.$ID.'</b>) byl vypraven interní poštou. Příchozí dokument založen pod (<b>'.$NOVEID.'</b>) ' . $ns;
    EedTransakce::ZapisLog($ID, $text, 'DOC', $id_user);



/*    $sql="insert into posta_krizovy_spis (PUVODNI_SPIS,NOVY_SPIS,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID)
    VALUES ($ID,$NOVEID,'$LAST_DATE','$LAST_TIME',$OWNER_ID,$LAST_USER_ID)";
    //Die($sql);
    $q->query($sql);
  */  
    
  }  
  if ($zalozeni==1 && !$GLOBALS['CONFIG']['ZALOZIT_SPIS_U_INTERNI_POSTY']) {
  	//interni posty 
  	$cj_obj = new EedCj($ID);
  	 
  	$text = 'Vytvoření nového dokumentu interní pošty - vytvořeno z odeslaného dokumentu (<b>' . $ID . '</b>) ' . $cj_obj->cislo_jednaci . '';
    EedTransakce::ZapisLog($NOVEID, $text, 'DOC', $id_user);

  	$cj_obj = new EedCj($NOVEID);
  	$cj_info = $cj_obj->GetCjInfo($NOVEID);

  	$text = 'dokument (<b>'.$ID.'</b>) byl vypraven interní poštou. Příchozí dokument založen pod (<b>'.$NOVEID.'</b>) ' . $cj_obj->cislo_jednaci;
    EedTransakce::ZapisLog($ID, $text, 'DOC', $id_user);

  }
  
  if ($zalozeni==3) {
    $text = "Vytvoření kopie dokumentu z (<b>$ID</b>) na (<b>$NOVEID</b>)";
    EedTransakce::ZapisLog($NOVEID, $text, 'DOC', $id_user);
    EedTransakce::ZapisLog($ID, $text, 'DOC', $id_user);
  }


  if ($zalozeni == 4) {
    $sql="SELECT * FROM posta_DS WHERE posta_id IN (".$ID.")";
    $q->query($sql);
    //echo $sql;
    $q->Next_Record();
    $data = $q->Record;

    $sql = "insert into posta_DS (posta_id,ds_id,odeslana_posta,datum_odeslani,last_date,last_time,last_user_id) VALUES
      ($NOVEID,".$data['DS_ID'].",'f','".$data['DATUM_ODESLANI']."','".$data['LAST_DATE']."','".$data['LAST_TIME']."','".$data['LAST_USER_ID']."')  ";
    $q->query($sql);
  }


  NastavStatus($NOVEID);
  if ($zalozeni<>4) NastavStatus($ID);
  
  if (!$id_puvodni || $id_puvodni=='NULL') $id_puvodni=$id_old_puvodni;

  $files_not_to_copy = array('dorucenka_' . $id_puvodni . '.pdf');
  //zkopirujeme soubory
  CopyFilesDokument('EED',$id_puvodni,$NOVEID, $files_not_to_copy);
  return $NOVEID;
}
