
<?php
session_start();
//If ($odeslana=="t") {$GLOBALS["ODESLANA_POSTA"]="t";}

unset($_SESSION['WORKFLOW']);

require("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/brow_.inc"));

$smer=($GLOBALS['ODESLANA_POSTA']=="t") ? "O" : (($GLOBALS['ODES_TYP']!="Z") ? "P" : "");

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/edit_start.php');
    
    if (File_Exists($file)) include($file);
  }
}

//die('---'.$co.'---');
// pokud je to info okno, neukayujeme tlacitko ZAVRIT, generujeme si ho sami.
$co=StrTok($GLOBALS["QUERY_STRING"], '&');
require(FileUp2("html_header_title.inc"));

NewWindow(array("fname" => "Sablona", "name" => "Sablona", "header" => true, "cache" => false, "window" => "edit"));

$form_method = "GET";

if (isset($GLOBALS['type_content'])) {
  $tc = $GLOBALS['type_content'];
  if ($tc =="msg") {
    $GLOBALS['SHOW_MESSAGE'] = true;
  }
  if ($tc=="eml"||$tc =="msg") {
    $GLOBALS['ZPUSOB_PODANI']=3;
    $form_method = "POST";
    //if ($tc == "eml") $tc = "ImapEml";
    $tc = ucfirst($tc);
    require_once(FileUp2(".admin/classes/dokument/".$tc.".php"));
    $doc_ff = new $tc();
    $doc_ff->setDocumentPath($GLOBALS['path_content']);
    try {
      $doc_ff->process();
    }
    catch(Exception $e)  {
      echo "<p>".$e->getMessage().": ".$GLOBALS['path_content']."</p>";
      echo '<button class="button btn" onclick="window.opener.parent.$.fancybox.close()">Zavřít</a>';
      $doc_ff->delTempDir();
      require(FileUp2("html_footer.inc"));
      die();
    }
  }
  
  
  /*switch ($GLOBALS['type_content']) {
    case "msg":      
      require_once(FileUp2(".admin/classes/dokument/Msg.php"));
      $doc_ff = new Msg();
      break;
    case "eml":
      require_once(FileUp2(".admin/classes/dokument/Eml.php"));
      $doc_ff = new Eml();
      break;
  }
  
  if (isset($doc_ff)) {
    $doc_ff->setDocumentPath($GLOBALS['path_content']);
    $doc_ff->process();
  }*/
}

NewWindow(array("fname" => "AgendaGuide", "name" => "AgendaGuide", "header" => true, "cache" => false, "window" => "edit"));
NewWindow(array("fname" => "Guide", "name" => "Guide", "header" => true, "cache" => false, "window" => "edit"));

//prikaz na vymazani session z vyberu
if ($GLOBALS["NULL_SESSION"]) $_SESSION["POSTA_SESSION_FILTER"]="";

//nacteme data ze session, podle ceho se naposledy vyhledavalo, to zadame do vyhledavani jako predvyplnene hodnoty
If ($co=='filter' || $co=='filterall') {
  if (is_array($_SESSION["POSTA_SESSION_FILTER"])) while (list($key,$val)=each($_SESSION["POSTA_SESSION_FILTER"])) {
    if (strpos($val, ',') !== false) {
      $val = explode(',',$val);
      foreach ($val as $v)
        if ($v!="") $GLOBALS[$key][] = $v;
    } else
      $GLOBALS[$key] = $val;
  }
    //$GLOBALS[$key]=$val;
  UNSET($GLOBALS["EDIT_ID"]);
}


//zkontrolujeme, zda se muze editovat pisemnost. pokud ne, tak edit prepiseme na info
include_once('services/spisovka/uzavreni_spisu/funkce.inc');



If ($datum_uzavreni=JeUzavrenSpis($GLOBALS["EDIT_ID"],'ID',0) && $co=='edit') {
  $GLOBALS["QUERY_STRING"]=Str_Replace('edit','info',$GLOBALS["QUERY_STRING"]);
  $GLOBALS["CAPTION_ERROR"]='Spis je uzavřen, editace není povolena!';
// Die ($GLOBALS["QUERY_STRING"]);
}

If (in_array(StavPisemnosti($GLOBALS["EDIT_ID"]),array(2,5,52,72,92)) && $co=='edit') {
  If (!(HasRole('spravce') || HasRole('podatelna') || HasRole('vedouci-odbor'))) {
    $GLOBALS["QUERY_STRING"]=Str_Replace('edit','info',$GLOBALS["QUERY_STRING"]);
    $GLOBALS["CAPTION_ERROR"]='Dokument se vyřizuje v externím programu, editace není povolena!';
  }
// Die ($GLOBALS["QUERY_STRING"]);
}

If (JeSkartovan($GLOBALS["EDIT_ID"]) && $co=='edit') {
  $GLOBALS["QUERY_STRING"]=Str_Replace('edit','info',$GLOBALS["QUERY_STRING"]);
  $GLOBALS["CAPTION_ERROR"]='Dokument byl skartován, editace není povolena!';
// Die ($GLOBALS["QUERY_STRING"]);
}
$text=JeStornovan($GLOBALS["EDIT_ID"]);

If ($text) {
  $GLOBALS["QUERY_STRING"]=Str_Replace('edit','info',$GLOBALS["QUERY_STRING"]);
  $GLOBALS["CAPTION_ERROR"]=$text;
// Die ($GLOBALS["QUERY_STRING"]);
}

require_once(FileUp2(".admin/edit_.inc"));

if ($co=="info") {
  require_once(FileUp2(".admin/brow_.inc"));
}

$co=StrTok($GLOBALS["QUERY_STRING"], '&');


If ($GLOBALS["vnitrni"]=='t')
  {
    Form_(array("showaccess" => true,"myform_schema"=>".admin/form_schema_vnitrni.inc"));
  }
else
{
  if ($co == "filter") {
//     require(FileUp2('.admin/form_schema_tabs_js.inc'));
//     print '<div id="tabs">' . "\n";
//     print '<ul>' . "\n";
//     print '<li><a href="#tabs-1" onclick=\'$( "#tabs" ).tabs( "disable" ); $( ".tabs" ).tabs( "enable", 1 );\'>Jednoduchý výběr</a></li>';
//     print '<li><a href="#tabs-2" onclick=\'$( "#tabs" ).tabs( "disable" );$( ".tabs" ).tabs( "enable", 2 );\'>Podrobný výběr</a></li>';
//     print '</ul>' . "\n";
//     print '<div id="tabs-2">' . "\n";
//     Form_(array(
//       'showaccess' => false,
//       'nocaption' => true,
//       'myform_schema' => '.admin/form_schema_filter_simple.inc',
//       'formname' => '',
//       'showbuttons' => true,
//     ));
//     print '</div>' . "\n";
//     print '<div id="tabs-1">' . "\n";
    Form_(array(
      'showaccess' => false,
      'nocaption' => true,
      'myform_schema' => '.admin/form_schema_filter_all.inc',
      'formname' => '',
      'showbuttons' => true,
    ));
//     print '</div>' . "\n";
//     print '</div>' . "\n";
/*
  print '<form name="frm_all" id="frm_all" method="POST" style="visibility: hidden; position:absolute; display: none;"></form>
    <table width="100%">
      <tr><td colspan=2 class=right>
        <input name="__" value="  ' . $GLOBALS['RESOURCE_STRING']['button_filter'] . '" class="button" type="button" onclick="sendFormAll()" />
      </td></tr>
    </table>';    
*/
  }
  else {
    if ($GLOBALS['EDIT_ID']) {
      $cj_obj = LoadClass('EedCj',$GLOBALS['EDIT_ID']);
      $caption = $cj_obj->cislo_jednaci;
      echo '<h1>'.$caption.'</h1>';
    }
    Form_(array("showaccess" => ($co=="info"),    "method" => $form_method   ));
  }
}

if (isset($GLOBALS['ID_PUVODNI']))
  $puvodni = "true"; 
else
  $puvodni = "false";

  
  
$agenda_filter = true;

if ($co <> 'filter') {
  if (($co=='edit' || $co=='info')&&isset($GLOBALS['TYP_POSTY'])) {
    echo "<script>TypObalky(document.frm_edit.VLASTNICH_RUKOU,'0')</script>";
    $GLOBALS['AGENDA_DOKUMENTU'] = VratAgenduDokumentu($GLOBALS['TYP_POSTY']);
      echo "<script>AgendaDok(document.frm_edit.AGENDA_DOKUMENTU,".$GLOBALS['AGENDA_DOKUMENTU'].",".$GLOBALS['TYP_POSTY'].",false,'false','".$smer."')</script>";
      if ($puvodni) $agenda_filter = false;
  }
  elseif ($co == 'insertfrom') {
    $GLOBALS['AGENDA_DOKUMENTU'] = VratAgenduDokumentu($GLOBALS['TYP_POSTY']);
    echo "<script>AgendaDok(document.frm_edit.AGENDA_DOKUMENTU,".$GLOBALS['AGENDA_DOKUMENTU'].",".$GLOBALS['TYP_POSTY'].",false,'','".$smer."')</script>";
  }
  elseif ($co == 'insert') {
    echo "<script>UkazTypPosty(document.frm_edit.AGENDA_DOKUMENTU,'TYP_POSTY','','',0,'".$GLOBALS['TYP_POSTY']."','','".$smer."');</script>";
    echo "<script>ZmenaTypuDokumentu(document.frm_edit.TYP_POSTY)</script>";
  }
  else
    echo "<script>TypObalky(document.frm_edit.VLASTNICH_RUKOU,'1')</script>";
}

//if ($co=='insert' || ($co=='edit' && $GLOBALS['ODDELENI']<1))
// if ($co=='insert')
//   echo "<script>
//   UkazPracovnika(document.frm_edit.ODDELENI,'REFERENT');
//   </script>";

if ($GLOBALS["ODES_TYP"] && !$is_filter)
 echo "<script>DruhAdresata('".$GLOBALS[ODES_TYP]."')</script>";


if ($co=='filter') {
 echo "<script>DruhAdresataFilter('')</script>";
}




If ($GLOBALS[DOPIS_DATUM]>0 && !$GLOBALS['add_adresat'])
 echo "<script>AddDay2StartDate(".$GLOBALS[DOPIS_DATUM].")</script>";

If ($co=='insertfrom' && !$GLOBALS['add_adresat'] && $GLOBALS['CONFIG']['DOPOCITAT_DATUM_ODPOVEDI']) {
  list($datum,$cas)=explode(' ',$GLOBALS['datum_podatelna_prichozi']);
  $datum=explode('.',$datum);
  if ($datum[0]>1) {
    echo "<script>AddDay2StartDate(".($GLOBALS['LHUTA']-1).",".$datum[0].",".$datum[1].",".$datum[2].")</script>";
  }
}
if (!(HasRole('spravce')||HasRole('podatelna')||HasRole('podatelna-odbor')) && ($co=='edit' || $co=='insert' || $co=='insertfrom') && $GLOBALS["ODESLANA_POSTA"]=='t')  {
if (!(HasRole('edit-datum-vypraveni')))  echo "<script>Predani()</script>";
  echo "<script>Vypnout_PM()</script>";

}

if (($co=='edit' || $co=='insert') && ($GLOBALS["ODESLANA_POSTA"]=='f' || $GLOBALS[odeslana]<>'t')) {
//Die($GLOBALS["CONFIG"]["ODDELENI"]);
  $odbor=$GLOBALS["ODBOR"];
  if ($oddeleni>0) $odbor = $oddeleni;
  $referent = $GLOBALS['REFERENT'];

}
if (($co=='edit' || $co=='info') && $GLOBALS["ODES_TYP"]=='S') {
  $GLOBALS['ODESL_OSOBA'] = $GLOBALS['ODESL_OSOBA'] ? $GLOBALS['ODESL_OSOBA'] : 0;
  //pri interni poste donacteme spravny vyber zpracovatelu do pole ODESL_PRAC2
  echo "<script>UkazPracovnika(document.frm_edit.ODESL_ODBOR,'ODESL_PRAC2',".$GLOBALS['ODESL_OSOBA'].");</script>";

}

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/edit_end.php');

		if (File_Exists($file)) include($file);
  }
}


require(FileUp2("html_footer.inc"));
