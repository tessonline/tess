<?php
function getDatum($date) {
  if ($date=='03.03.3333') $ret = 'trvá';
  else $ret = $date;
  return $ret;
}


$TABLE_CONFIG["schema"][] = array("field"=>"STUD_ID", "label"=>"ID Studia",  "width"=>"1%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"CISLO_UK", "label"=>"WHOIS",  "width"=>"1%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"PRIJMENI...' ' ...JMENO", "label"=>"příjmení jméno",  "width"=>"60%","add"=>"align=left NOWRAP");
if (HasRole('spravce')) $TABLE_CONFIG["schema"][] = array("field"=>"ID_ORG", "label"=>"fakulta",  "width"=>"40%","add"=>"align=left NOWRAP");

$TABLE_CONFIG["schema"][] = array("field"=>"STUD_TYP", "label"=>"Typ studia",  "width"=>"40%","add"=>"align=left NOWRAP");
$TABLE_CONFIG["schema"][] = array("field"=>"STUD_PROGRAM", "label"=>"Stud. program",  "width"=>"40%","add"=>"align=left NOWRAP");
$TABLE_CONFIG["schema"][] = array("field"=>"getDatum(DATUM_OD)", "label"=>"Studium OD",  "width"=>"40%","add"=>"align=left NOWRAP");
$TABLE_CONFIG["schema"][] = array("field"=>"getDatum(DATUM_DO)", "label"=>"Studium DO",  "width"=>"40%","add"=>"align=left NOWRAP");

