<?php
Include_once(FileUp2(".admin/table_funkce.inc"));
include_once(FileUp2(".admin/oth_funkce.inc"));

//echo "ID".$GLOBALS["PUVODNI_PRIJEMCE"];
function UkazAdr($id)
{
  if (eregi('X_',$id))
  {
    $res=str_replace('x_','',$id);
    $res=UkazAdresu(str_replace('X_','',$res),', ','posta');
  }
  else
    $res=UkazAdresu($id,', ','cis_posta_prijemci');
  return $res;
}

$TABLE_CONFIG = array(

  "schema" => array( 

 array( field=>"Ukaz2(ODES_TYP,ZPUSOB_PODANI,VLASTNICH_RUKOU)...'&nbsp;'...UkazAdr(ID)", label=>"Odesílatel/Adresát","order_by"=>"odesl_prijmeni asc, odesl_jmeno asc", width=>"80%"),
 array( field=>"ODESL_DATSCHRANKA", label=>"DS","order_by"=>"odesl_datschranka asc", width=>"20%"),
// array( field=>"ODESL_ULICE...'&nbsp;'...ODESL_PSC...'&nbsp;'...ODESL_POSTA", label=>"Adresa"),
));

echo "
<script>
<!--
  function del_adr(id) {
  newwindow = window.open('./services/spisovka/prijemci/del_adr.php?&PUVODNI_PRIJEMCE=".$GLOBALS["PUVODNI_PRIJEMCE"]."&DEL_ID='+id, 'agenda_nova', 'height=100,width=100,scrollbars=0,resizable=0');
  newwindow.focus();
  }
//-->
</script>
";
 
?>
