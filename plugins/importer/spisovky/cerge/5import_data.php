<?php
include_once(FileUp2('.admin/run2_.inc'));
include_once(FileUp2('.admin/status.inc'));
/*
echo "<h1>Data</h1>";


echo "<p>";
$sql = 'select d.*, c.rok,c.poradove_cislo,c.urad_zkratka,c.urad_poradi,c.orgjednotka_id,c.org_poradi,c.user_id
 from s3_dokument d LEFT JOIN s3_cislo_jednaci c ON d.cislo_jednaci_id=c.id where cislo_jednaci_id>0 order by d.id asc';
$db_from -> query($sql);
$save = array();
$a = 0;
$nl2br = chr(10);
while ($db_from->Next_Record()) {
  $spisovka3_id = $db_from->Record['ID'];

  $save[$a]['EV_CISLO'] = $db_from->Record['ID'];

  $vec = iconv('iso-8859-2', 'UTF-8', $db_from->Record['NAZEV']);
  $save[$a]['DALSI_ID_AGENDA'] = 'SPISOVKA3CERGE:' . $db_from->Record['ID'];

  $org_jednotka = $db_from->Record['ORGJEDNOTKA_ID'];

  $save[$a]['REFERENT'] = getCiselnik($db_from->Record['USER_ID'], 'users_' . $org_jednotka);
  if ($save[$a]['REFERENT']>0) {
    $pole = OdborPrac($save[$a]['REFERENT']);
    $save[$a]['ODBOR'] = $pole['odbor'];
  }

  $save[$a]['SUPERODBOR'] = getCiselnik($org_jednotka, 'org_jednotka');

  $save[$a]['ODESLANA_POSTA'] = getCiselnik($db_from->Record['DOKUMENT_TYP_ID'], 's3_dokument_typ');
  $save[$a]['ZPUSOB_PODANI'] = getCiselnik($db_from->Record['ZPUSOB_DORUCENI_ID'], 's3_zpusob_doruceni');
  $save[$a]['CISLO_SPISU1'] = $db_from->Record['PODACI_DENIK_PORADI'];
  $save[$a]['CISLO_SPISU2'] = $db_from->Record['PODACI_DENIK_ROK'];
  $save[$a]['CISLO_JEDNACI1'] = $db_from->Record['PODACI_DENIK_PORADI'];
  $save[$a]['CISLO_JEDNACI2'] = $db_from->Record['PODACI_DENIK_ROK'];
  $save[$a]['ROK'] = $db_from->Record['PODACI_DENIK_ROK'];
  $save[$a]['TEXT_CJ'] = $db_from->Record['CISLO_JEDNACI'];
  $save[$a]['VYRIZENO'] = getCiselnik($db_from->Record['ZPUSOB_VYRIZENI_ID'], 's3_zpusob_vyrizeni');
  $save[$a]['VEC'] = $db_from->Record['NAZEV'];
  $save[$a]['POZNAMKA'] = 'Popis:' . $db_from->Record['POPIS'];
  $save[$a]['JEJICH_CJ'] = $db_from->Record['CISLO_JEDNACI_ODESILATELE'];
  $save[$a]['SKARTACE'] = getCiselnik($db_from->Record['SPISOVY_ZNAK_ID'], 'skartace');
  $save[$a]['POZNAMKA'] .= $nl2br.'Poznamka:' . $db_from->Record['POZNAMKA'];
  $save[$a]['LHUTA'] = $db_from->Record['LHUTA'];
  $save[$a]['OWNER_ID'] = $db_from->Record['USER_CREATED'];
  $save[$a]['LAST_DATE'] = $db_from->Record['DATE_MODIFIED'];
  $save[$a]['LAST_USER_ID'] = $db_from->Record['USER_MODIFIED'];
  $save[$a]['DATUM_PODATELNA_PRIJETI'] = $db_from->Record['DATUM_VZNIKU'];
  $save[$a]['POCET_LISTU'] = $db_from->Record['POCET_LISTU'];
  $save[$a][''] = $db_from->Record['POCET_PRILOH'];
  $save[$a]['DRUH_PRILOH'] = $db_from->Record['DRUH_PRILOH'];

  if ($save[$a]['ODESLANA_POSTA'] == 'f')
    $save[$a]['DATUM_VYRIZENI'] = $db_from->Record['DATUM_VYRIZENI'];
  else
    $save[$a]['DATUM_VYPRAVENI'] = $db_from->Record['DATUM_VYRIZENI'];

  $save[$a]['POZNAMKA'] .= $nl2br.'Vyrizeni:' . $db_from->Record['POZNAMKA_VYRIZENI'];
  $save[$a]['ODESL_REKOMANDO'] = $db_from->Record['REKOMANDO'];

  if ($save[$a]['SKARTACE']>0) $save[$a]['SPIS_VYRIZEN'] = $save[$a]['DATUM_VYRIZENI'] ? $save[$a]['DATUM_VYRIZENI'] : $save[$a]['DATUM_PODATELNA_PRIJETI'];


  $sql = 'SELECT * FROM  s3_dokument_to_subjekt d LEFT JOIN s3_subjekt s ON d.subjekt_id = s.id where dokument_id=' . $spisovka3_id;
  $db_from2->query($sql);
  if ($db_from2->Num_Rows() == 0 && $db_from->Record['DOKUMENT_TYP_ID'] == 2) {
    echo 'vlastni zaznam<br/>'; //jedna se o odchozi zaznam, ktery nema vypraveni
  }
  else {
    $db_from2->Next_Record();

    $save[$a]['ODES_TYP'] = getCiselnik($db_from2->Record['TYPE'], 's3_typ_odesl');
    if ($save[$a]['ODES_TYP'] == 0) $save[$a]['ODES_TYP'] = 'U';
    if ($db_from2->Record['TYPE'] == '') $save[$a]['ODES_TYP'] = 'U';
    if ($db_from2->Record['TYPE'] == 'NULL') $save[$a]['ODES_TYP'] = 'U';
    if (!$db_from2->Record['TYPE']) $save[$a]['ODES_TYP'] = 'U';


    $save[$a]['ODESL_PRIJMENI'] = substr($db_from2->Record['NAZEV_SUBJEKTU'], 0, 149);
    if ($save[$a]['ODES_TYP'] == 'P' || $save[$a]['ODES_TYP'] == 'U' ) {
      $save[$a]['ODESL_ICO'] = $db_from2->Record['IC'];

      if ($db_from2->Record['PRIJMENI']) {
        $save[$a]['ODESL_OSOBA'] = ($db_from2->Record['TITUL_PRED'] ? $db_from2->Record['TITUL_PRED'] .' ' : '');
        $save[$a]['ODESL_OSOBA'] .= ($db_from2->Record['JMENO'] ? $db_from2->Record['JMENO'] .' ' : '');
        $save[$a]['ODESL_OSOBA'] .= ($db_from2->Record['PRIJMENI'] ? $db_from2->Record['JMPRIJMENIENO'] .' ' : '');
        $save[$a]['ODESL_OSOBA'] .= $db_from2->Record['TITUL_ZA'];
      }

    }
    else {
      $save[$a]['ODESL_JMENO'] = $db_from2->Record['JMENO'];
      $save[$a]['ODESL_PRIJMENI'] = $db_from2->Record['PRIJMENI'];
      $save[$a]['ODES__TITUL'] = $db_from2->Record['TITUL_PRED'];
      $save[$a]['ODESL_TITUL_ZA'] = $db_from2->Record['TITUL_ZA'];
      $save[$a]['ODESL_DATNAR'] = $db_from2->Record['DATUM_NAROZENI'];
    }

    $save[$a]['ODESL_POSTA'] = $db_from2->Record['ADRESA_MESTO'];
    $save[$a]['ODESL_ULICE'] = $db_from2->Record['ADRESA_ULICE'];
    $save[$a]['ODESL_CP'] = $db_from2->Record['ADRESA_CP'];
    $save[$a]['ODESL_COR'] = $db_from2->Record['ADRESA_CO'];
    $save[$a]['ODESL_PSC'] = substr(trim($db_from2->Record['ADRESA_PSC']), 0, 6);
    $save[$a]['ODES_STAT'] = ($db_from2->Record['ADRESA_STAT']<>'CZE' ? $db_from2->Record['ADRESA_STAT'] : '');
    $save[$a]['ODES_EMAIL'] = $db_from2->Record['EMAIL'];
    $save[$a]['ODESL_DATSCHRANKA'] = $db_from2->Record['ID_ISDS'];
    if ($db_from2->Record['POZNAMKA']) $save[$a]['POZNAMKA'] .= $nl2br . 'Subjekt:' . $db_from2->Record['POZNAMKA'] ;


  }
  $save[$a]['STATUS'] = 9;
  if ($vec == 'STORNO') {
    $save[$a]['STATUS'] = -1;
    $save[$a]['STORNOVANO'] = 'Stornovano v Spisovka3';
  }
  $save[$a]['ODESL_ADRKOD'] = 0;


  $sql = 'SELECT * FROM  s3_dokument_odeslani where dokument_id=' . $spisovka3_id;
  $db_from2->query($sql);
  if ($db_from2->Num_Rows() == 0) {
    //nevypraveno
    $save[$a]['VLASTNICH_RUKOU'] = 0;
    $save[$a]['DATUM_VYPRAVENI'] = '';
  }
  else {
    $db_from2->Next_Record();
    $save[$a]['VLASTNICH_RUKOU'] = getCiselnik($db_from2->Record['ZPUSOB_ODESLANI_ID'], 's3_zpusob_odeslani');
    $save[$a]['DATUM_VYPRAVENI'] = $db_from2->Record['DATUM_ODESLANI'];

  }

     //u udchozich dopiseme datum vypraveni, pokud neni
  if ($save[$a]['DATUM_VYPRAVENI'] == '' && $db_from->Record['DOKUMENT_TYP_ID'] == 2) $save[$a]['DATUM_VYPRAVENI'] = $save[$a]['DATUM_PODATELNA_PRIJETI'];

  if ($db_from->Record['DOKUMENT_TYP_ID'] == 2) $save[$a]['DATUM_DORUCENI'] = $save[$a]['DATUM_VYPRAVENI'];

  //zjistime, jestli uz je zalozeno ve spisovce
  $sql = "select id from posta where dalsi_id_agenda like '" . $save[$a]['DALSI_ID_AGENDA'] . "'";
  $db_to->query($sql);
  $db_to->Next_Record();
  if ($db_to->Record['ID']>0) $save[$a]['EDIT_ID'] = $db_to->Record['ID'];
  if ($db_to->Record['ID']>0) $save[$a]['STATUS'] = $db_to->Record['STATUS'];

  $a++;
}

$pole = $db_to->metadata('posta');
foreach($pole as $key => $val) {
  if ($val['name']<>'ID') $unset_pole[] = $val['name'];
}

echo "</p>";
echo "Nacteno, jdeme ulozit";

foreach($save as $val) {

  foreach($unset_pole as $sett) $GLOBALS[$sett] = iconv('iso-8859-2', 'UTF-8', $val[$sett]);
  if ($val['EDIT_ID']>0) {$GLOBALS['EDIT_ID'] = $val['EDIT_ID']; $GLOBALS['ID'] = $val['EDIT_ID'];}

  if (!$GLOBALS['ODES_TYP']) $GLOBALS['ODES_TYP'] = 'U';

//   if ($val['EDIT_ID']>0) {
//   }
//   else {


    //if ($GLOBALS['STATUS']>0)
    {
      echo "aktualiyuji ".$GLOBALS['EDIT_ID']." ".$GLOBALS['ODESLANA_POSTA']."<br/>";

      Access(array('agenda' => 'POSTA'));

      $id = Run_(array("noaccesscondition"=>true,"outputtype"=>1, 'noaccessrefresh' => false));
      NastavStatus($id, $val['LAST_USER_ID']);
    }
//   }

  UNSET($GLOBALS['EDIT_ID']);
  UNSET($GLOBALS['ID']);
  foreach($unset_pole as $sett) UNSET($GLOBALS[$sett]);
}
*/


/*
$sql = 'select d.*, c.rok,c.poradove_cislo,c.urad_zkratka,c.urad_poradi,c.orgjednotka_id,c.org_poradi,c.user_id
 from s3_dokument d LEFT JOIN s3_cislo_jednaci c ON d.cislo_jednaci_id=c.id where cislo_jednaci_id>0 order by d.id asc';
$db_from -> query($sql);
$save = array();
$a = 0;
$nl2br = chr(10);
while ($db_from->Next_Record()) {
  $spisovka3_id = $db_from->Record['ID'];

  $sql = 'SELECT * FROM  s3_dokument_to_subjekt d LEFT JOIN s3_subjekt s ON d.subjekt_id = s.id where dokument_id=' . $spisovka3_id;
  $db_from2->query($sql);
  if ($db_from2->Num_Rows() == 0 && $db_from->Record['DOKUMENT_TYP_ID'] == 2) {
    echo 'vlastni zaznam<br/>'; //jedna se o odchozi zaznam, ktery nema vypraveni
  }
  else {
    $db_from2->Next_Record();

    $save[$a]['ODES_TYP'] = getCiselnik($db_from2->Record['TYPE'], 's3_typ_odesl');
    if ($save[$a]['ODES_TYP'] == 0) $save[$a]['ODES_TYP'] = 'U';
    if ($db_from2->Record['TYPE'] == '') $save[$a]['ODES_TYP'] = 'U';
    if ($db_from2->Record['TYPE'] == 'NULL') $save[$a]['ODES_TYP'] = 'U';
    if (!$db_from2->Record['TYPE']) $save[$a]['ODES_TYP'] = 'U';


    $save[$a]['ODESL_PRIJMENI'] = substr($db_from2->Record['NAZEV_SUBJEKTU'], 0, 149);
    if ($save[$a]['ODES_TYP'] == 'P' || $save[$a]['ODES_TYP'] == 'U' ) {
      $save[$a]['ODESL_ICO'] = $db_from2->Record['IC'];

      if ($db_from2->Record['PRIJMENI']) {
        $save[$a]['ODESL_OSOBA'] = ($db_from2->Record['TITUL_PRED'] ? $db_from2->Record['TITUL_PRED'] .' ' : '');
        $save[$a]['ODESL_OSOBA'] .= ($db_from2->Record['JMENO'] ? $db_from2->Record['JMENO'] .' ' : '');
        $save[$a]['ODESL_OSOBA'] .= ($db_from2->Record['PRIJMENI'] ? $db_from2->Record['PRIJMENI'] .' ' : '');
        $save[$a]['ODESL_OSOBA'] .= $db_from2->Record['TITUL_ZA'];
      }

    }
    else {
      $save[$a]['ODESL_JMENO'] = $db_from2->Record['JMENO'];
      $save[$a]['ODESL_PRIJMENI'] = $db_from2->Record['PRIJMENI'];
      $save[$a]['ODES__TITUL'] = $db_from2->Record['TITUL_PRED'];
      $save[$a]['ODESL_TITUL_ZA'] = $db_from2->Record['TITUL_ZA'];
      $save[$a]['ODESL_DATNAR'] = $db_from2->Record['DATUM_NAROZENI'];
    }


  }
  $save[$a]['DALSI_ID_AGENDA'] = 'SPISOVKA3CERGE:' . $db_from->Record['ID'];

  if ($save[$a]['ODESL_OSOBA']<> '') {
  //zjistime, jestli uz je zalozeno ve spisovce
    $sql = "select id from posta where dalsi_id_agenda like '" . $save[$a]['DALSI_ID_AGENDA'] . "'";
    $db_to->query($sql);
    $db_to->Next_Record();
    if ($db_to->Record['ID']>0) {
      $sql = "update posta set odesl_osoba='".$save[$a]['ODESL_OSOBA']."' where id=" . $db_to->Record['ID'];
      echo $sql.'<br/>';
      $db_to->query(iconv('iso-8859-2', 'UTF-8', $sql));

    }
  }

  $a++;
}
*/

$sql = 'select d.*, c.rok,c.poradove_cislo,c.urad_zkratka,c.urad_poradi,c.orgjednotka_id,c.org_poradi,c.user_id
 from s3_dokument d LEFT JOIN s3_cislo_jednaci c ON d.cislo_jednaci_id=c.id where cislo_jednaci_id>0 and ulozeni_dokumentu is not null order by d.id asc';
$db_from -> query($sql);
$save = array();
$a = 0;
$nl2br = chr(10);
while ($db_from->Next_Record()) {
  $spisovka3_id = $db_from->Record['ID'];

  $save[$a]['DALSI_ID_AGENDA'] = 'SPISOVKA3CERGE:' . $db_from->Record['ID'];

  $ulozeni = $db_from->Record['ULOZENI_DOKUMENTU'];
  if ($ulozeni<> '') {
  //zjistime, jestli uz je zalozeno ve spisovce
    $sql = "select id from posta where dalsi_id_agenda like '" . $save[$a]['DALSI_ID_AGENDA'] . "'";
    $db_to->query($sql);
    $db_to->Next_Record();
    if ($db_to->Record['ID']>0) {
      $sql = "update posta set poznamka=poznamka||'
Ulozeni: ".$ulozeni."' where id=" . $db_to->Record['ID'];
      echo $sql.'<br/>';
      //$db_to->query(iconv('iso-8859-2', 'UTF-8', $sql));

    }
  }

  $a++;
}

