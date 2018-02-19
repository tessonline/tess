<?php
include_once(FileUp2('.admin/oth_funkce.inc'));
function InfoPosta($id) {
  $doc = LoadClass('EedDokument', $id);
  $res=$doc->cislo_jednaci." - ".UkazAdresu($id,', ');
  return $res;
}

if (!$GLOBALS['REFERENT']) $GLOBALS['REFERENT'] = $_GET['REFERENT'] ? $_GET['REFERENT'] : 0;
$FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"hidden", "name"=>"REFERENT","value"=>$GLOBALS["REFERENT"])),
				"label"=>"");		

$sql="select * from posta where odeslana_posta='t' and referent in (".$GLOBALS["REFERENT"].")
and datum_vypraveni is null and datum_doruceni is null and vlastnich_rukou
like '".$GLOBALS["CONFIG"]["HROMADNA_OBALKA"]."' and ID NOT IN (select dokument_id from posta_hromadnaobalka) and status>1";

$q->query($sql);
$hromadne_obalky=array();
while ($q->Next_Record())
  $hromadne_obalky[]=$q->Record["ID"];
  
$sql='select * from posta_hromadnaobalka where obalka_id='.$GLOBALS["EDIT_ID"].' ';
//echo $sql;
$q->query($sql);
$adresat=array();
//$adresat[]=0;
while ($q->Next_Record())
  $adresat[]=$q->Record["DOKUMENT_ID"];



$FORM_CONFIG["schema"][] = array("label"=>"Nezařazené dokumenty");
		
//$FORM_CONFIG["schema"][] = array("elements"=>array(),"format"=>"'<i>vypisuji všechny dokumenty, které nejsou <br/>vypraveny a mají status hromadné obálky. <br/>Zašrtněte ty, které chcete vložit do obálky <br/> k tomuto dokumentu<br/>&nbsp;</i>'");

while (list($key,$val)=each($hromadne_obalky)) {
  if (!in_array($val,$adresat)) {
    $text=InfoPosta($val);
    //  If (in_array($kod,$kody)) {$checked='CHECKED';} else  {$checked='';}
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"checkbox", "multiple"=>1,"name"=>"KOD","array_val"=>$val,"value"=>true, "add"=>$checked)),
  						"format"=>"KOD...'$text'",		
  					"label"=>"");		
  }
}
//$FORM_CONFIG["schema"][] = array("elements"=>array(),"format"=>"'<br/><i>pokud zde není uveden dokument, pak buď nemá status hromadné obálky nebo je již přiřazen k jiné obálce nebo byl již odeslán<br/>&nbsp;</i>'");


$FORM_CONFIG["schema"][] = array("label"=>"Dokumenty v této obálce");		
//$FORM_CONFIG["schema"][] = array("elements"=>array(),"format"=>"'<i>Nže uvedené dokumenty již v této obálce máte. V případě, že je chcete vyjmout z této obálky, zaškrtněte je. Jinak ponechejte tento výběr beze změn.<br/>&nbsp;</i>'");
while (list($key,$val)=each($adresat))
{
  //if (!in_array($val,$adresat))
  {
    $text=InfoPosta($val);
    //  If (in_array($kod,$kody)) {$checked='CHECKED';} else  {$checked='';}
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"checkbox", "multiple"=>1,"name"=>"KOD","array_val"=>$val,"value"=>true, "add"=>$checked)),
  						"format"=>"KOD...'$text'",		
  					"label"=>"");		
  }
}
