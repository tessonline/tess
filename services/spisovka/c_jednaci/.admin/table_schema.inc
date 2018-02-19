<?php
Include_once(FileUp2(".admin/table_funkce.inc"));
  
//return $stav;
/*
Function prava($ID,$PRAVO)
{
$res="<a href=\"javascript:NewWindowEdit2('/ost/posta/edit.php?edit&EDIT_ID=$ID&PRAVA=$PRAVO')\">A</a>";

return $res;
}
*/


$TABLE_CONFIG["schema"][]=    array( field=>"Ukaz(ODESLANA_POSTA)", label=>"");
$TABLE_CONFIG["schema"][]=    array( field=>"'<i><font size=1>'...EV_CISLO...'/'...ROK...'</font></i>", label=>"Č.&nbsp;podací");

If ($GLOBALS["CONFIG"]["SHOW_TABLE_C_JEDNACI"])
$TABLE_CONFIG["schema"][]= array( field=>"FormatCJednaci(ID)", "label"=>$GLOBALS["CONFIG"]["JEDNACI_CISLO"], "order_by"=>"cislo_jednaci2,cislo_jednaci1", width=>"4%","add"=>"NOWRAP align=center");
$TABLE_CONFIG["schema"][]= array( field=>"FormatSpis(ID)", label=>$GLOBALS["CONFIG"]["CISLO_SPISU"],"add"=>"NOWRAP");
$TABLE_CONFIG["schema"][]= array( field=>"DatumPrijeti(DATUM_PODATELNA_PRIJETI)", label=>"Přijetí");
$TABLE_CONFIG["schema"][]= array( field=>"Ukaz2(ODES_TYP,ZPUSOB_PODANI,VLASTNICH_RUKOU)...'&nbsp;'...UkazJmeno()", label=>"Adresa");
$TABLE_CONFIG["schema"][]= array( field=>"VEC", label=>"Věc");

//    array( field=>"NAME", label=>"Odbor","add"=>"align=center"),
//    array( field=>"LNAME", label=>"Referent","add"=>"align=center"),
//    array( field=>"$GLOBALS["DALSI_PRIJEMCI"]", "label"=>"", "add"=>"align=center"),
    
/*
echo "<script>
<!--
  function NewWindowEdit2(script) {
    newwindow = window.open(script, 'Edit','height=400,width=790,left=10,top=50,scrollbars,resizable');
    newwindow.focus();
  }
//-->
</script>
";
*/

?>
