<?php
include_once(FileUp2('.admin/security_name.inc'));
$TABLE_CONFIG["schema"][] = array( field=>"DATUM", label=>"Dne", add=>"left", "order_by"=>"datum");
$TABLE_CONFIG["schema"][] = array( field=>"UkazUsera(ZPRACOVATEL)", label=>"Zástupce", add=>"left", "order_by"=>"zpracovatel");
$TABLE_CONFIG["schema"][] = array( field=>"UkazUsera(ZASTOUPENA)", label=>"Zastoupená osoba", add=>"left", "order_by"=>"zastoupena");

?>
