<?php
Include_once(FileUp2(".admin/table_funkce_denik.inc"));
Include_once(FileUp2(".admin/oth_funkce_2D.inc"));
//Include_once(FileUp2(".admin/db/db_posta.inc"));
//require_once(FileUp2(".admin/security_obj.inc"));

Function Zakazat($id,$frozen) {
  if (!$id) $id=$GLOBALS["ID"];
  $url=GetAgendaPath('POSTA');
//  echo $url;
  If ($frozen=="A") {
	 $res="<a href='#' title='Kliknutím nastavit jako aktivní adresu' onclick=\"window.open('".$url."/services/spisovka/firmy/frozen.php?idaa=".$id."&frozen=N', 'FROZEN','height=100,width=100,scrollbars=0,resizable=0,toolbar=0,status=0,menubar=0,titlebar=0')\"><img src='".FileUpUrl('images/ko_check.gif')."' border=0></a>";
	}
	else {
	 $res="<a href='#' title='Kliknutím nastavit jako neaktivní adresu' onclick=\"window.open('".$url."/services/spisovka/firmy/frozen.php?idaa=".$id."&frozen=A', 'FROZEN','height=100,width=100,scrollbars=0,resizable=0,toolbar=0,status=0,menubar=0,titlebar=0')\"><img src='".FileUpUrl('images/ok_check.gif')."' border=0></a>";
	}
  If ($frozen=="D") {
   $res = 'Smazaná adresa:<br/>';
	 $res.="<a href='#' title='Kliknutím nastavit jako aktivní adresu' onclick=\"window.open('".$url."/services/spisovka/firmy/frozen.php?idaa=".$id."&frozen=N', 'FROZEN','height=100,width=100,scrollbars=0,resizable=0,toolbar=0,status=0,menubar=0,titlebar=0')\"><img src='".FileUpUrl('images/ko_check.gif')."' border=0></a>";
	 $res.="&nbsp;<a href='#'title='Kliknutím nastavit jako neaktivní adresu'  onclick=\"window.open('".$url."/services/spisovka/firmy/frozen.php?idaa=".$id."&frozen=A', 'FROZEN','height=100,width=100,scrollbars=0,resizable=0,toolbar=0,status=0,menubar=0,titlebar=0')\"><img src='".FileUpUrl('images/ok_check.gif')."' border=0></a>";

	}

        UNSET($GLOBALS["ID"]);
	return $res;
}

function Pridat($id) {
	 $res = "<a href='#'title='Kliknutím přidejte adresu do ručně vložených adresátů'  onclick=\"NewWindowEditadresati('edit.php?insert&INSERT_ID=".$id."&cacheid=')\"><img src='".FileUpImage('images/add')."' border=0></a>";
   return $res;
}

Function Smazat($id,$frozen) {
  if (!$id) $id=$GLOBALS["ID"];
  $url=GetAgendaPath('POSTA');
	 $res="<a href='#' title='Vyřadit adresu' onclick=\"window.open('".$url."/services/spisovka/firmy/frozen.php?idaa=".$id."&frozen=D', 'FROZEN','height=100,width=100,scrollbars=0,resizable=0,toolbar=0,status=0,menubar=0,titlebar=0')\"><img src='".FileUpImage('images/delete')."' border=0></a>";
        UNSET($GLOBALS["ID"]);
  if ($frozen=='D') $res="&nbsp;";
	return $res;
}

Function Adresat($ID) {
  $tabulka=$GLOBALS["CONFIG_POSTA"]["ADRESATI"]["TABULKA"];
  return UkazAdresu($ID,', ',$tabulka);
}


$tabulka=$GLOBALS["CONFIG_POSTA"]["ADRESATI"]["TABULKA"];
//echo "A".$tabulka;

//    array( field=>"ODESL_PRIJMENI...'&nbsp;'...ODESL_JMENO...' '...ODESL_ICO...' ,'...ODESL_ULICE...'&nbsp;'...ODESL_C..','...ODESL_PSC...'&nbsp;'...ODESL_POSTA", label=>"Adresa"),
$TABLE_CONFIG = array(
//  "callback"=> "ChangeClassBarva",
  "schema" => array( 
//    array( field=>"Ukaz2(ODES_TYP)", label=>"&nbsp;"),
//    array( field=>"Adresat(ID)", label=>"Adresa"),
    array( field=>"UkazJmeno(ID)...UkazRucne(ID)", label=>"Adresa"),
//    array( field=>"UkazJmeno(ID)", label=>"Adresa"),
//    array( field=>"UkazOdbor(ODBOR,'true')", label=>"Odbor"),
    array( field=>"ODESL_DATSCHRANKA", label=>"Dat.schránka"),
    array( field=>"ODESL_OSOBA", label=>"Osoba"),
    array( field=>"ODESL_ODD", label=>"Odbor"),
    array( field=>"Zakazat(ID,FROZEN)", label=>"Ukazovat","add"=>"align='center'"),
    array( field=>"Pridat(ID)", label=>"&nbsp;","class"=>"image","width"=>"1%","add"=>"align='center'"),
    array( field=>"Smazat(ID,FROZEN)", label=>"&nbsp;","class"=>"image","width"=>"1%","add"=>"align='center'"),

  )
 );

