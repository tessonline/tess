<?php
include_once(FileUp2('.admin/security_name.inc'));
function UkazTlacitka($id)
{
  If ($id==1 && !$GLOBALS[DATUM_VYTISTENI]) {$res="<a href='funkce.php?typ=1&ID=$GLOBALS[ID]&DATUM_OD=$GLOBALS[DATUM_OD]&DATUM_DO=$GLOBALS[DATUM_DO]&ODBOR=$GLOBALS[ODBOR]'>znovu načíst dokumenty</a>";}
  If ($id==1 && $GLOBALS[DATUM_VYTISTENI]&& !$GLOBALS[DATUM_VRACENI]) {$res="<i>zapište datum převzetí doručovatele...</i>";}
  If ($id==2 && !$GLOBALS[DATUM_VYTISTENI]) {$res="<a href='dorucovatelpdf.php?ID=$GLOBALS[ID]&PROTOKOL=$GLOBALS[PROTOKOL]&c1=$GLOBALS[CISLO_OD]&c2=$GLOBALS[CISLO_DO]&c3=$GLOBALS[CISLO2_OD]' target='_blank'>vytisknout PROTOKOL</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='protokol.php?ID=$GLOBALS[ID]&PROTOKOL=$GLOBALS[PROTOKOL]&c1=$GLOBALS[CISLO_OD]&c2=$GLOBALS[CISLO_DO]&c3=$GLOBALS[CISLO2_OD]' target='_blank'>vytisknout ČP</a>";}
  If ($id==2 && $GLOBALS[DATUM_VYTISTENI]) {$res="<a href='dorucovatelpdf.php?ID=$GLOBALS[ID]&PROTOKOL=$GLOBALS[PROTOKOL]&c1=$GLOBALS[CISLO_OD]&c2=$GLOBALS[CISLO_DO]&c3=$GLOBALS[CISLO2_OD]' target='_blank'>ukázat PROTOKOL</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href='protokol.php?PROTOKOL=$GLOBALS[PROTOKOL]&c1=$GLOBALS[CISLO_OD]&c2=$GLOBALS[CISLO_DO]&c3=$GLOBALS[CISLO2_OD]' target='_blank'>ukázat ČP</a>";}
  If ($id==3 && !$GLOBALS[DATUM_VYTISTENI]) {$res="<a href='funkce.php?typ=2&ID=$GLOBALS[ID]'><img src='".FileUpUrl('images/ok_check.gif')."' BORDER=0 alt='Označit, že protokol byl již vytištěn'></a>";}
  If ($id==3 && $GLOBALS[DATUM_VYTISTENI]) {$res="Protokol vytištěn dne ".$GLOBALS[DATUM_VYTISTENI];}
  return $res;
}

  
//return $stav;
//$TABLE_CONFIG["callback"]="ChangeClassBarva";

//Die($CONFIG["CISLO_SPISU"]);
//$TABLE_CONFIG["schema"][]= array( field=>"Ukaz(ODESLANA_POSTA)", width=>"1%", label=>"","class"=>$GLOBALS["barva_sipky"]);

$TABLE_CONFIG["schema"][]= array( field=>"'<b>'...PROTOKOL...'&nbsp;/&nbsp;'...ROK...'</b>'", label=>"Číslo protokolu", width=>"10%","add"=>"align=center");
$TABLE_CONFIG["schema"][]= array( field=>"DATUM_OD", label=>"Datum od", width=>"10%","add"=>"align=center");
$TABLE_CONFIG["schema"][]= array( field=>"DATUM_DO", label=>"Datum do", width=>"10%","add"=>"align=center");
$TABLE_CONFIG['schema'][] = array(
  field => 'UkazOdbor(ODBOR, true)',
  label => $GLOBALS['CONFIG']['NAZEV_TABLE_ODBOR'],
  width => '4%',
  );

		
$TABLE_CONFIG["schema"][]= array( field=>"UkazTlacitka('1')", label=>"Načíst", width=>"20%","add"=>"align=center");
$TABLE_CONFIG["schema"][]= array( field=>"UkazTlacitka('2')", label=>"Vytisknout", width=>"30%","add"=>"align=center");
$TABLE_CONFIG["schema"][]= array( field=>"UkazTlacitka('3')", label=>"Bylo vytištěno?", width=>"10%","add"=>"align=center");


//$TABLE_CONFIG["schema"][]= array( field=>"Precteno(ID,REFERENT)", "label"=>"", "add"=>"align=center");
//$TABLE_CONFIG["schema"][]= array( field=>"UkazOdpoved(ID)", "label"=>"", "add"=>"align=center", width=>"1%");





?>
