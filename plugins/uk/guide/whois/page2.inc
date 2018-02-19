<?php

//hledame pracovniky

if(!$GLOBALS['TMAPY_SECURITY_WHOIS']) { ///TODO: kdyz nebude, tak ho vytvorit
  $sec_file = $GLOBALS["TMAPY_LIB"] . "/security/whois.inc";
  include($sec_file);
  $GLOBALS["TMAPY_SECURITY_WHOIS"] = new Security_Obj_WhoIS();
}

$ID = (integer) $GLOBALS['SELECT_IDedit'];
if ($_GET['SELECT_IDedit']) $IDstudia = (integer) $_GET['SELECT_IDedit'];
$jmeno = $GLOBALS['jmeno'];
$prijmeni = $GLOBALS['prijmeni'];
if (!$ID && $Ident) $ID = $Ident;
if ($ID == 0 && !$jmeno && !$prijmeni ) Die('Zadejte parametr pro vyhledávání');

if (($jmeno && $prijmeni) && $ID == 0) {

  if (!HasRole('spravce')) {
     $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
     $fakulta = $USER_INFO['PRACOVISTE'];
  }
  $pracovnici = $GLOBALS["TMAPY_SECURITY_WHOIS"]->Findpracovnik($ID, $jmeno, $prijmeni, $fakulta);
  if (count($pracovnici) == 0) Die('Nic nenalezeno');
  if (count($pracovnici)>0) {

     $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
     $fakulta = $USER_INFO['PRACOVISTE'];

    $pracovnici_moji = array();
    $pracovnici_ostatni = array();
    foreach($pracovnici as $key => $val) {
      if ($val['ID_ORG'] == $fakulta) $pracovnici_moji[]  = $val;
      else $pracovnici_ostatni[]  = $val;
    }



    include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
    $db_arr = new DB_Sql_Array;
    $db_arr->Data=$pracovnici_moji;
  	$caption = 'Vyberte odpovídající osobu';

    $GLOBALS['GUIDE_DIRECTION'] = 1;


  	$caption = 'Osoby z mého pracoviště';
    Table(array(
      "db_connector" => &$db_arr,
      "schema_file" => FileUp2('plugins/uk/.admin/table_schema_pracovnik.inc'),
      "tablename" => "edit",
      "showaccess" => true,
      "caption" => $caption,
      "showselect" => true,
 			"formvars"=>array('GUIDE_DIRECTION'),
      "select_id" => "CISLO_UK",
       "appendwhere"=>$where2,
      "showedit"=>false,
      "showdelete"=>false,
      "showselect"=>true,
      "showinfo"=>false,
    ));


    $db_arr2 = new DB_Sql_Array;
    $db_arr2->Data=$pracovnici_ostatni;

    $GLOBALS['SHOW_FAKULTA'] = true;
  	$caption = 'Osoby z ostatních pracovišť';
    Table(array(
      "db_connector" => &$db_arr2,
      "schema_file" => FileUp2('plugins/uk/.admin/table_schema_pracovnik.inc'),
      "tablename" => "edit_ostatni",
      "showaccess" => true,
      "caption" => $caption,
      "showselect" => true,
 			"formvars"=>array('GUIDE_DIRECTION'),
      "select_id" => "CISLO_UK",
       "appendwhere"=>$where2,
      "showedit"=>false,
      "showdelete"=>false,
      "showselect"=>true,
      "showinfo"=>false,
    ));

    //jdeme vyhledat
  }
  if (count($pracovnici) == 1) {
    $IDstudia = key($pracovnici);
  }

}
if ($ID>0) {
  $pracovnik = $GLOBALS["TMAPY_SECURITY_WHOIS"]->Getpracovnik($ID);

//   if (!$pracovnik['KONKTATNI_ADRESA'][POID]) $adresa = $pracovnik['TRVALA_ADRESA'];
//   else
//     $adresa = $pracovnik['KONKTATNI_ADRESA'];

  $adresa = $pracovnik;

  if (!$pracovnik['CISLO_UK']) Die('Dané číslo ' . $ID . ' nebylo nalezeno ve WhoIS');

  $cislo = $adresa['CPORI'];
  if (strpos($cislo, '/')) list($cp,$cor) = explode('/', $cislo);
  else
    $cp = $cislo;

  echo "
  <script language=\"JavaScript\" type=\"text/javascript\">
  <!--

    window.opener.document.frm_edit.WHOIS_NUMBER.value = '" . $pracovnik[CISLO_UK] . "';
    window.opener.document.frm_edit.WHOIS_NUMBER.style.color='green';
    window.opener.document.frm_edit.WHOIS_IDSTUDIA.value = '" . $pracovnik[STUD_ID] . "';
    window.opener.document.frm_edit.WHOIS_IDSTUDIA.style.color='red';

    window.opener.document.frm_edit.ODESL_PRIJMENI.value = '" . $pracovnik[PRIJMENI] . "';
    window.opener.document.frm_edit.ODESL_PRIJMENI.style.color='red';
    window.opener.document.frm_edit.ODESL_JMENO.value = '" . $pracovnik[JMENO] . "';
    window.opener.document.frm_edit.ODESL_JMENO.style.color='red';
    window.opener.document.frm_edit.ODESL_TITUL.value = '" . $pracovnik[TITULY_PRED] . "';
    window.opener.document.frm_edit.ODESL_TITUL.style.color='red';
    window.opener.document.frm_edit.ODESL_TITUL_ZA.value = '" . $pracovnik[TITULY_ZA] . "';
    window.opener.document.frm_edit.ODESL_TITUL_ZA.style.color='red';
    window.opener.document.frm_edit.ODESL_EMAIL.value = '" . $pracovnik[EMAIL] . "';
    window.opener.document.frm_edit.ODESL_EMAIL.style.color='red';
    window.opener.document.frm_edit.ODESL_DATNAR.value = '" . $pracovnik[DATUM_NAROZENI] . "';
    window.opener.document.frm_edit.ODESL_DATNAR.style.color='red';

    window.opener.document.frm_edit.ODESL_ADRKOD.value = '" . $adresa[ADRESA_KOD] . "';

    window.opener.document.frm_edit.ODESL_ULICE.value = '" . $adresa[ULICE] . "';
    window.opener.document.frm_edit.ODESL_ULICE.style.color='red';

    window.opener.document.frm_edit.ODESL_CP.value = '" . $cp . "';
    window.opener.document.frm_edit.ODESL_CP.style.color='red';

    window.opener.document.frm_edit.ODESL_COR.value = '" . $cor . "';
    window.opener.document.frm_edit.ODESL_COR.style.color='red';

    window.opener.document.frm_edit.ODESL_POSTA.value = '" . $adresa[OBEC] . "';
    window.opener.document.frm_edit.ODESL_POSTA.style.color='red';

    if ('".$adresa[STAT_KOD]."'==203) {
      window.opener.document.frm_edit.ODESL_PSC.value = '" . $adresa[POSTOVNI_CISLO] . "';
      window.opener.document.frm_edit.ODESL_PSC.style.color='red';
    } else {
      window.opener.document.frm_edit.ODESL_JINE.value = '" . $adresa[POSTOVNI_CISLO] . "';
      window.opener.document.frm_edit.ODESL_JINE.style.color='red';
      window.opener.document.frm_edit.ODESL_STAT.value = '" . $adresa[STAT] . "';
      window.opener.document.frm_edit.ODESL_STAT.style.color='red';
    }

    parent.$.fancybox.close();
  //-->
  </script>
  ";
}

