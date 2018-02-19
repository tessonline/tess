<?php
session_start();
//If ($odeslana=="t") {$GLOBALS["ODESLANA_POSTA"]="t";}
require("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/run2_.inc"));

//die('---'.$co.'---');
// pokud je to info okno, neukayujeme tlacitko ZAVRIT, generujeme si ho sami.
$co=StrTok($GLOBALS["QUERY_STRING"], '&');
require(FileUp2("html_header_title.inc"));

//prikaz na vymazani session z vyberu
if ($GLOBALS["NULL_SESSION"]) $_SESSION["POSTA_SESSION_FILTER"]="";

//nacteme data ze session, podle ceho se naposledy vyhledavalo, to zadame do vyhledavani jako predvyplnene hodnoty
If ($co=='filter' || $co=='filterall')
{
  if (is_array($_SESSION["POSTA_SESSION_FILTER"])) while (list($key,$val)=each($_SESSION["POSTA_SESSION_FILTER"])) $GLOBALS[$key]=$val;
  UNSET($GLOBALS["EDIT_ID"]);
}  

//zkontrolujeme, zda se muze editovat pisemnost. pokud ne, tak edit prepiseme na info
include_once(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));


//print_r($GLOBALS);
If ($datum_uzavreni=JeUzavrenSpis($GLOBALS["EDIT_ID"],'ID',0) && $co=='edit')
{
  $GLOBALS["QUERY_STRING"]=Str_Replace('edit','info',$GLOBALS["QUERY_STRING"]);
  $GLOBALS["CAPTION_ERROR"]='Spis je uzavřen, editace není povolena!';
// Die ($GLOBALS["QUERY_STRING"]);
}

If (in_array(StavPisemnosti($GLOBALS["EDIT_ID"]),array(2,5,52,72,92)) && $co=='edit')
{
  If (!(HasRole('spravce') || HasRole('podatelna') || HasRole('vedouci-odbor'))) 
  {
    $GLOBALS["QUERY_STRING"]=Str_Replace('edit','info',$GLOBALS["QUERY_STRING"]);
    $GLOBALS["CAPTION_ERROR"]='Dokument se vyřizuje v externím programu, editace není povolena!';
  }
// Die ($GLOBALS["QUERY_STRING"]);
}

If (JeSkartovan($GLOBALS["EDIT_ID"]) && $co=='edit')
{
  $GLOBALS["QUERY_STRING"]=Str_Replace('edit','info',$GLOBALS["QUERY_STRING"]);
  $GLOBALS["CAPTION_ERROR"]='Dokument byl skartován, editace není povolena!';
// Die ($GLOBALS["QUERY_STRING"]);
}
$text=JeStornovan($GLOBALS["EDIT_ID"]);
If ($text)
{
  $GLOBALS["QUERY_STRING"]=Str_Replace('edit','info',$GLOBALS["QUERY_STRING"]);
  $GLOBALS["CAPTION_ERROR"]=$text;
// Die ($GLOBALS["QUERY_STRING"]);
}

  
require_once(FileUp2(".admin/edit_.inc"));

$co=StrTok($GLOBALS["QUERY_STRING"], '&');
If ($GLOBALS["vnitrni"]=='t')
  {Form_(array("showaccess" => true,"myform_schema"=>".admin/form_schema_vnitrni.inc"));}
else
{
  If ($co<>"info") 
  {
    $method=($co=="filterall")?"GET":"POST"; 
    Form_(array("showaccess" => true,"method"=>$method,"showbuttonsup"=>($co=='filterall')?true:false));
  }
  else
  {
    Form_(array("showaccess" => true,"noshowclose"=>true,"showbuttons"=>false,"showbuttonsup"=>false));
  }
}


if ($co=='edit' || $co=='info')
  echo "<script>TypObalky(document.frm_edit.VLASTNICH_RUKOU,'0')</script>";
else
  echo "<script>TypObalky(document.frm_edit.VLASTNICH_RUKOU,'1')</script>";


//if ($co=='insert' || ($co=='edit' && $GLOBALS['ODDELENI']<1))
if ($co=='insert' || $co=='filter')
  echo "<script>
    UkazOddeleni(document.frm_edit.ODBOR,'ODDELENI');
  UkazPracovnika(document.frm_edit.ODDELENI,'REFERENT');
  </script>";

if ($GLOBALS["ODES_TYP"] && !$is_filter)
 echo "<script>DruhAdresata('".$GLOBALS[ODES_TYP]."')</script>";


If ($GLOBALS[DOPIS_DATUM]>0 && !$GLOBALS['add_adresat'])
 echo "<script>AddDay2StartDate(".$GLOBALS[DOPIS_DATUM].")</script>";

If ($co=='insertfrom' && !$GLOBALS['add_adresat'])
{
  list($datum,$cas)=explode(' ',$GLOBALS['datum_podatelna_prichozi']);
  $datum=explode('.',$datum);
  echo "<script>AddDay2StartDate(".($GLOBALS['LHUTA']-1).",".$datum[0].",".$datum[1].",".$datum[2].")</script>";
}
if (!(HasRole('spravce')||HasRole('podatelna')||HasRole('podatelna-odbor')) && ($co=='edit' || $co=='insert' || $co=='insertfrom') && $GLOBALS["ODESLANA_POSTA"]=='t') 
{
  echo "<script>Predani()</script>";
  echo "<script>Vypnout_PM()</script>";

}

if (($co=='edit' || $co=='info' || $co=='new') && $GLOBALS["ODES_TYP"]=='S') 
{
//Die($GLOBALS["CONFIG"]["ODDELENI"]);
  $oddeleni=$GLOBALS["ODESL_ULICE"];
  if ($GLOBALS["CONFIG"]["ODDELENI"])
  {
    echo '<script>
newwindow = window.open(\'services/spisovka/oddeleni/get_value_odd.php?ODBOR='.$oddeleni.'&vysledek=ODESL_ODD2&hodnota='.$GLOBALS["ODESL_ODD"].'\',\'ifrm_get_value2\',\'\');
newwindow.focus();
</script> 
';
  $oddeleni=$GLOBALS["ODESL_ODD"];
  }
   echo '<script>
newwindow = window.open(\'services/spisovka/oddeleni/get_value_prac.php?ODBOR='.$oddeleni.'&vysledek=ODESL_PRAC2&hodnota='.$GLOBALS["ODESL_OSOBA"].'\',\'ifrm_get_value\',\'\');
newwindow.focus();
</script> 
';

}

require(FileUp2("html_footer.inc"));
?>
