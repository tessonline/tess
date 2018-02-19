<?php
Include_once(FileUp2(".admin/table_func.inc"));
Include_once(FileUp2(".admin/oth_funkce.inc"));
Include_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/security_obj.inc"));

Function Zakazat($id,$frozen)
{
  if (!$id) $id=$GLOBALS["ID"];
  If ($frozen=="A")
	{
	 $res="<a href='#' onclick=\"window.open('./services/spisovka/firmy/frozen.php?idaa=".$id."&frozen=N', 'FROZEN','height=100,width=100,scrollbars=0,resizable=0,toolbar=0,status=0,menubar=0,titlebar=0')\"><img src='".FileUpUrl('images/ko_check.gif')."' border=0></a>";
	}
	else
	{
	 $res="<a href='#' onclick=\"window.open('./services/spisovka/firmy/frozen.php?idaa=".$id."&frozen=A', 'FROZEN','height=100,width=100,scrollbars=0,resizable=0,toolbar=0,status=0,menubar=0,titlebar=0')\"><img src='".FileUpUrl('images/ok_check.gif')."' border=0></a>";
	}
        UNSET($GLOBALS["ID"]);
	return $res;
}
Function Adresat($adresar,$ID)
{
  if ($adresar == 'A')
    $tabulka="posta_adresati";
  else
    $tabulka="posta";
//echo $adresar.$tabulka;
//  echo $ID;
  return UkazAdresu(abs($ID),', ',$tabulka);
}
$tabulka=$GLOBALS["CONFIG_POSTA"]["ADRESATI"]["TABULKA"];
//    array( field=>"ODESL_PRIJMENI...'&nbsp;'...ODESL_JMENO...' '...ODESL_ICO...' ,'...ODESL_ULICE...'&nbsp;'...ODESL_CP...','...ODESL_PSC...'&nbsp;'...ODESL_POSTA", label=>"Adresa"),
$TABLE_CONFIG = array(
//  "callback"=> "ChangeClassBarva",
  "schema" => array( 
    array( field=>"Adresat(ADRESAR,ID)", label=>"Adresa"),
    array( field=>"ODESL_DATSCHRANKA", label=>"Dat.schránka"),
    array( field=>"ODESL_OSOBA", label=>"Osoba"),
    array( field=>"ODESL_ODD", label=>"Odbor"),
//    array( field=>"Zakazat(ID,FROZEN)", label=>"Ukazovat","add"=>"align='center'"),
    
  )
 );
//}

?>
