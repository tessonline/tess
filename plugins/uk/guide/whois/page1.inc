<?php

if(!$GLOBALS['TMAPY_SECURITY_WHOIS']) { ///TODO: kdyz nebude, tak ho vytvorit
  $sec_file = $GLOBALS["TMAPY_LIB"] . "/security/whois.inc";
  include($sec_file);
  $GLOBALS["TMAPY_SECURITY_WHOIS"] = new Security_Obj_WhoIS();
}

if ($typ == 'G') {
  include('page2.inc');
}
else
{

$ID = (integer) $GLOBALS['Ident'];
$IDstudia = (integer) $GLOBALS['StudID'];
if ($_GET['SELECT_IDedit']) $IDstudia = (integer) $_GET['SELECT_IDedit'];
$jmeno = $GLOBALS['jmeno'];
$prijmeni = $GLOBALS['prijmeni'];
if ($ID == 0 && !$jmeno && !$prijmeni && !$IDstudia) Die('Zadejte parametr pro vyhledávání');

if (($ID || $jmeno && $prijmeni) && $IDstudia == 0) {

  if (!HasRole('spravce')) {
     $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
     $fakulta = $USER_INFO['PRACOVISTE'];
  }
  if ($fakulta == 126) $fakulta = 118;
  $students = $GLOBALS["TMAPY_SECURITY_WHOIS"]->FindStudents($ID, $jmeno, $prijmeni, $IDstudia, $fakulta);
  if (count($students) == 0) Die('Nic nenalezeno');
  if (count($students)>1) {

    include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
    $db_arr = new DB_Sql_Array;
    $db_arr->Data=$students;
  	$caption = 'Vyberte odpovídající osobu';

    $GLOBALS['GUIDE_DIRECTION'] = 1;


    Table(array(
      "db_connector" => &$db_arr,
      "schema_file" => FileUp2('plugins/uk/.admin/table_schema_student.inc'),
      "tablename" => "edit",
      "showaccess" => true,
      "caption" => $caption,
      "showselect" => true,
 			"formvars"=>array('GUIDE_DIRECTION'),
      "select_id" => "STUD_ID",
       "appendwhere"=>$where2,
      "showedit"=>false,
      "showdelete"=>false,
      "showselect"=>true,
      "showinfo"=>false,
    ));

    //jdeme vyhledat
  }
  if (count($students) == 1) {
    $IDstudia = key($students);
  }

}
if ($IDstudia>0) {
  $student = $GLOBALS["TMAPY_SECURITY_WHOIS"]->GetStudent(0, array('IDStudia' => $IDstudia));

  if (!$student['KONKTATNI_ADRESA'][POID]) $adresa = $student['TRVALA_ADRESA'];
  else
    $adresa = $student['KONKTATNI_ADRESA'];
  //print_r($student); Die();
  if (!$student['CISLO_UK']) Die('Dané číslo ' . $ID . ' nebylo nalezeno ve WhoIS');

  $cislo = $adresa['CPORI'];
  if (strpos($cislo, '/')) list($cp,$cor) = explode('/', $cislo);
  else
    $cp = $cislo;

  echo "
  <script language=\"JavaScript\" type=\"text/javascript\">
  <!--

    window.opener.document.frm_edit.WHOIS_NUMBER.value = '" . $student[CISLO_UK] . "';
    window.opener.document.frm_edit.WHOIS_NUMBER.style.color='green';
    window.opener.document.frm_edit.WHOIS_IDSTUDIA.value = '" . $student[STUD_ID] . "';
    window.opener.document.frm_edit.WHOIS_IDSTUDIA.style.color='red';

    window.opener.document.frm_edit.ODESL_PRIJMENI.value = '" . $student[PRIJMENI] . "';
    window.opener.document.frm_edit.ODESL_PRIJMENI.style.color='red';
    window.opener.document.frm_edit.ODESL_JMENO.value = '" . $student[JMENO] . "';
    window.opener.document.frm_edit.ODESL_JMENO.style.color='red';
    window.opener.document.frm_edit.ODESL_TITUL.value = '" . $student[TITULY_PRED] . "';
    window.opener.document.frm_edit.ODESL_TITUL.style.color='red';
    window.opener.document.frm_edit.ODESL_TITUL_ZA.value = '" . $student[TITULY_ZA] . "';
    window.opener.document.frm_edit.ODESL_TITUL_ZA.style.color='red';
    window.opener.document.frm_edit.ODESL_EMAIL.value = '" . $student[EMAIL] . "';
    window.opener.document.frm_edit.ODESL_EMAIL.style.color='red';
    window.opener.document.frm_edit.ODESL_DATNAR.value = '" . $student[DATUM_NAROZENI] . "';
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
      window.opener.document.frm_edit.ODESL_STAT.value = '" . $adresa[STAT_NAZEV_CS] . "';
      window.opener.document.frm_edit.ODESL_STAT.style.color='red';
    }

    parent.$.fancybox.close();
  //-->
  </script>
  ";
}

}