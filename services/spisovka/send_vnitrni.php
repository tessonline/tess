<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
include(FileUp2('.admin/upload_fce_.inc'));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2(".admin/zaloz.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
//include_once(FileUp2('.admin/db/db_upload.inc'));
include_once(FileUp2("/interface/.admin/soap_funkce.inc"));
require_once(FileUp2("/interface/.admin/upload_funkce.inc"));
include_once(FileUp2("html_header_full.inc"));

$EDIT_ID_puv = $GLOBALS['EDIT_ID'];
echo '<div id="upl_wait_message2" class="text" style="display:block"><img src="'.FileUpUrl('images/progress.gif').'" title="pracuji ..." alt="pracuji ..."></div>';
Flush();

If ($send_vnitrni == 1) {
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user = $USER_INFO["ID"];
  $jmeno = $USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
  $LAST_USER_ID = $id_user;
  $OWNER_ID = $id_user;
  $LAST_TIME = Date('H:i:s');
  $LAST_DATE = Date('Y-m-d');
  $lastid = $GLOBALS['EDIT_ID'];
  If ($GLOBALS["CONFIG"]["PODCISLO"] && !$GLOBALS["CONFIG"]["NEPRIRAZOVAT_PODCISLO_U_KOPIE"]) { PriradPodcislo($lastid);}

  $q = new DB_POSTA;
  $a = new DB_POSTA;
  $sql = 'select * from posta where id = '.$lastid;
  $q->query($sql);
  $q->Next_Record();
  $datum = $q->Record['DATUM_VYPRAVENI'];
  if (strlen($datum)>2) 
  {
    //uz je odeslano
    echo '
    <script language="JavaScript" type="text/javascript">
    <!--
      window.opener.document.location.reload();
      window.close();
    //-->
    </script>
    ';
    Die();
  }
  $CISLO_JEDNACI1 = $q->Record["CISLO_JEDNACI1"]?$q->Record["CISLO_JEDNACI1"]:0;
  $CISLO_JEDNACI2 = $q->Record["CISLO_JEDNACI2"]?$q->Record["CISLO_JEDNACI2"]:0;
  $CISLO_SPISU1 = $q->Record["CISLO_SPISU1"]?$q->Record["CISLO_SPISU1"]:0;
  $CISLO_SPISU2 = $q->Record["CISLO_SPISU2"]?$q->Record["CISLO_SPISU2"]:0;
  $GLOBALS['NAZEV_SPISU'] = $q->Record["NAZEV_SPISU"];
  $nowd = EReg_Replace("[.]0",".", date('d.m.Y H:i'));
  $nowd = EReg_Replace("^0","", $nowd);
  $datum_podatelna = $nowd;
  $skartace = $q->Record["SKARTACE"]?$q->Record["SKARTACE"]:0;
//echo "odd je $superod";
  $odd = 0;
//  print_r($pole2);
//  print_r($pole);
//  Die('STOP');
  $POZNAMKA = $q->Record["POZNAMKA"];
  $CISLO_SPISU1 = $CISLO_SPISU1 ? $CISLO_SPISU1 : 0;
  $CISLO_SPISU2 = $CISLO_SPISU2 ? $CISLO_SPISU2 : 0;
  //$referent = $GLOBALS["REFERENT2"]?$GLOBALS["REFERENT2"]:0;
  $GLOBALS["ID_PUVODNI"] = $q->Record["ID_PUVODNI"] ? $q->Record["ID_PUVODNI"] : $lastid;
  $GLOBALS["TYP_POSTY"] = $q->Record["TYP_POSTY"] ? $q->Record["TYP_POSTY"] : 0;
  $lhuta = $q->Record["LHUTA"] ? $q->Record["LHUTA"] : 30;
//    echo "odbor je $odbor <br/>";

//  $odesl_prijmeni_zal = $q->Record["ODESL_PRIJMENI"];
//  $odesl_jmeno_zal = $q->Record["ODESL_JMENO"];

///  $GLOBALS["ODESL_PRIJMENI"] = VratSNazevSkupiny($GLOBALS['SUPERODBOR']).", ".RawURLDecode($odesl_prijmeni_zal);
//  $GLOBALS["ODESL_JMENO"] = RawURLDecode($odesl_jmeno_zal);

  $GLOBALS["ODESL_PRIJMENI"] = VratSNazevSkupiny($q->Record['SUPERODBOR']).", ".UkazOdbor($q->Record['ODBOR']);
  $GLOBALS["ODESL_JMENO"] = UkazUsera($q->Record["REFERENT"]);

  $ev_cislo = $GLOBALS[EV_CISLO]?$q->Record[EV_CISLO]:0;
  $GLOBALS["VEC"] = str_replace("'","",$q->Record["VEC"]);
  $GLOBALS["ODESLANA_POSTA"] = 'f';
  $GLOBALS["ROK"] = $q->Record["ROK"];
  $GLOBALS["PODCISLO_SPISU"] = $q->Record["PODCISLO_SPISU"]?$q->Record["PODCISLO_SPISU"]:0;
  $odbor_spisu = $q->Record["ODBOR_SPISU"]?$q->Record["ODBOR_SPISU"]:0;
  
  $ukaz_adresati = array();
  $vnitrObj = LoadClass('EedVnitrniPosta', $GLOBALS['EDIT_ID']);

  $adresati = $vnitrObj->VratSeznamVnitrnichAdresatu($vnitrObj->adresati);
  foreach($adresati as $key  => $adresat) {
   $superod = $adresat['ZARIZENI_ID'] ? $adresat['ZARIZENI_ID'] : 0;
   $odbor = $adresat['UZEL_ID'] ? $adresat['UZEL_ID'] : 0;
   $referent = $adresat['ZPRACOVATEL_ID'] ? $adresat['ZPRACOVATEL_ID'] : 0;

      //echo "odbor je $odbor <br/>";
    $sql = "insert into posta
    (ev_cislo,rok,odbor,oddeleni,superodbor,typ_posty,odes_typ,vec,odesl_prijmeni,odesl_jmeno,datum_podatelna_prijeti,referent,odeslana_posta,doporucene,vlastnich_rukou,dorucenka,id_puvodni,odesl_odd, odesl_osoba,last_date,last_time,last_user_id,owner_id,skartace,dalsi_prijemci,odbor_spisu,cislo_jednaci1,cislo_jednaci2,
    cislo_spisu1,cislo_spisu2,podcislo_spisu,poznamka,lhuta,nazev_spisu,datum_predani,typ_dokumentu)
    values (".$ev_cislo.",".$GLOBALS["ROK"].",".$odbor.",".$odd.",".$superod.",".$GLOBALS["TYP_POSTY"].",'X','".$GLOBALS["VEC"]."','".$GLOBALS["ODESL_PRIJMENI"]."','".$GLOBALS["ODESL_JMENO"]."','".$datum_podatelna."',
    ".$referent.",'f','0','0','0',".$q->Record["ID"].",'".$q->Record["ODESL_ODD"]."','".$q->Record["ODESL_OSOBA"]."','".$LAST_DATE."','".$LAST_TIME."',".$LAST_USER_ID.",".$OWNER_ID.",'".$skartace."','".$q->Record["DALSI_PRIJEMCI"]."','".$odbor_spisu."',".$CISLO_JEDNACI1.",".$CISLO_JEDNACI2.",".$CISLO_SPISU1.",".$CISLO_SPISU2.",".$GLOBALS["PODCISLO_SPISU"].",'".$q->Record["POZNAMKA"]."','".$lhuta."','".$GLOBALS["NAZEV_SPISU"]."','".$datum_podatelna."','".$q->Record['TYP_DOKUMENTU']."')";
//  echo $sql."<br/>";
     $a->query($sql);
     $posle_id = $a->getlastid('posta', 'id');
     NastavStatus($posle_id, $LAST_USER_ID);
     CopyFilesDokument('EED',$GLOBALS['EDIT_ID'],$posle_id);    
  }

  $sql = "update posta set datum_vypraveni = '".Date('d.m.Y H:i')."',last_time = '".$LAST_TIME."',last_date = '".$LAST_DATE."',last_user_id = $LAST_USER_ID where id = ".$EDIT_ID_puv;
  $q->query($sql);
  NastavStatus($EDIT_ID_puv);  
}

echo "<script>document.getElementById('upl_wait_message2').style.display = 'none'</script>"; Flush();

echo '
<script language = "JavaScript" type = "text/javascript">
<!--
  window.opener.document.location.reload();
  window.close();
//-->
</script>
';
include_once(FileUp2("html_footer.inc"));
