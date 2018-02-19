<?php

Function UkazUlici($id)
{
 $res=$id;
 
 $q=new DB_POSTA;
 $sql='SELECT u.nazev from ui_adresa a,ui_ulice u WHERE a.ulice_kod=u.ulice_kod AND a.adresa_kod='.$id;
 $q->query($sql);
 $q->Next_Record();
 $res=$q->Record["NAZEV"];
// $res=$sql;
 return $res;
}

$t->formmethod = 'POST';

$TABLE_CONFIG["callback"]="ChangeClassMy";
//$TABLE_CONFIG["map"]=$CONFIG["SHOW_MAP"];

$TABLE_CONFIG["schema"][] = array( field=>"ADRESA_KOD", label=>"Kód", add=>"left", "order_by"=>"ADRESA_KOD");
$TABLE_CONFIG["schema"][] = array( field=>"'&nbsp;'...COBCE", label=>"Část obce", add=>"left", "order_by"=>"COBCE");
$TABLE_CONFIG["schema"][] = array( field=>"UkazUlici(ADRESA_KOD)", label=>"Ulice", add=>"left", "order_by"=>"ULICE");
$TABLE_CONFIG["schema"][] = array( field=>"Domcislo(CISDOM_TYP,CISDOM_HOD)", label=>"Č. domovní", add=>"align=\"right\"", "order_by"=>"CISDOM_HOD");
$TABLE_CONFIG["schema"][] = array( field=>"Ocislo(CISOR_HOD,CISOR_PIS)", label=>"Č. orientační", add=>"align=\"right\"", "order_by"=>"CISOR_PIS");
$TABLE_CONFIG["schema"][] = array( field=>"PSC...'&nbsp;'", label=>"PSČ", add=>"align=\"center\"", "order_by"=>"PSC");

?>
