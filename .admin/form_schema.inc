<?php
include_once(FileUp2(".admin/config.inc"));

$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
$is_filter_all = In_Array($form_params["formtype"], array($f_filter_all));
$is_filter_simple = In_Array($form_params["formtype"], array($f_filter));
$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_update = In_Array($form_params["formtype"], array($f_insert, $f_edit));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
$is_info = In_Array($form_params["formtype"], array($f_info));
$is_history = In_Array($form_params["formtype"], array($f_history));
$is_new = In_Array($form_params["formtype"], array($f_insertfrom)); 
$is_multiedit = In_Array($form_params["formtype"], array($f_editall));


reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/form_schema_start.inc');
		if (File_Exists($file)) include($file);
  }
}
//nadefinujeme potrebne promenne...
if ($is_insert) {
  if ($GLOBALS['odeslana']<>'t') $GLOBALS['TYP_DOKUMENTU'] = 'A';

  $GLOBALS["POCET_LISTU"]=$GLOBALS["POCET_LISTU"]?$GLOBALS["POCET_LISTU"]:1;
}
if (!$is_filter)
{
//  $GLOBALS["POCET_LISTU"]=$GLOBALS["POCET_LISTU"]?$GLOBALS["POCET_LISTU"]:1;
  $GLOBALS["POCET_PRILOH"]=$GLOBALS["POCET_PRILOH"]?$GLOBALS["POCET_PRILOH"]:0;
  $GLOBALS["DRUH_PRILOH"]=$GLOBALS["DRUH_PRILOH"]?$GLOBALS["DRUH_PRILOH"]:'písemné';           
  $GLOBALS["ODESL_ADRKOD"]=$GLOBALS["ODESL_ADRKOD"]?$GLOBALS["ODESL_ADRKOD"]:0;
  $adrkod=$GLOBALS["ODESL_ADRKOD"];
if ($GLOBALS["ODES_TYP"]=='A' || $GLOBALS["ODES_TYP"]=='V' || $GLOBALS["ODES_TYP"]=='Z') $GLOBALS["ODESL_PRIJMENI_NAZEV"]=$GLOBALS["ODESL_PRIJMENI"];
if ($GLOBALS["ODES_TYP"]=='P' || $GLOBALS["ODES_TYP"]=='U') $GLOBALS["ODESL_PRIJMENI_FIRMA"]=$GLOBALS["ODESL_PRIJMENI"];

}
If ($GLOBALS["CONFIG"]["FROZEN_ADR"])
  $GLOBALS["FROZEN"]=$GLOBALS["FROZEN"]?$GLOBALS["FROZEN"]:'A';
else
  $GLOBALS["FROZEN"]=$GLOBALS["FROZEN"]?$GLOBALS["FROZEN"]:'N';

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
$REFERENT = $USER_INFO["ID"]; 

//nadefinujeme packu - bude insertovat text
  $imgc = FileUpUrl("images/arrow3l.gif");
  $packa = "<a href=\"javascript:InsertMesto(document.forms[0].ODESL_POSTA)\"><img src=\"$imgc\" alt=\"Vložit text ".$GLOBALS[CONFIG][MESTO]."\" border=\"0\"></a>";

if ($is_insert)
{
  If($GLOBALS[CONFIG][NASTAVIT_ODESILATEL]) $GLOBALS["ODES_TYP"]=$GLOBALS[CONFIG][NASTAVIT_ODESILATEL];
  $GLOBALS["EV_CISLO"]=0;
  If (HasRole('omezeni-zpracovatele"')) {$GLOBALS["REFERENT"]=$REFERENT;}
}

If ($is_insert && $GLOBALS[odeslana]<>'t' && (HasRole('podatelna')||HasRole('spravce')) && $GLOBALS['MAIN_DOC']<100) {
  $q=new DB_POSTA;
  $sql='select odbor from posta where podatelna_id='.$REFERENT.' order by id desc';
  $q->query($sql);
  $q->Next_Record();
  $GLOBALS["ODBOR"]=$q->Record["ODBOR"];  
}

if ($GLOBALS['SKARTACE']>0) {
  $w=new DB_POSTA;
	$sql = "select * from cis_posta_skartace where id=".$GLOBALS['SKARTACE']; // nacteme cislo skartacniho planu
  $w->query($sql);
  $w->Next_Record();
  $GLOBALS['SKARTACEKOD'] = $w->Record['KOD'];
}

//pokud jsem pouze podatelna-odbor, tak se mi automaticky vyplni datum predani na odbor...
If ($is_insert && $GLOBALS[odeslana]<>'t' && (HasRole('podatelna') || HasRole('spravce')))
{
  $GLOBALS["DATUM_PREDANI"]=Date('d.m.Y H:m:i');  
}
//napiseme do promenny, jak se bude jmenovat cislo spisu
If ($GLOBALS["CISLO_SPISU1"]<>'' and $GLOBALS["CISLO_SPISU1"]<>0) {
  $doc_id = $_GET['doc_id'];
  $GLOBALS["cislo_spisu"]=$cj_info['CELY_NAZEV'];

}
else
  $GLOBALS["cislo_spisu"].='&nbsp;&nbsp;';


//if (($is_edit||($is_new&&$GLOBALS['REFERENT']<>$REFERENT)) && !(HasRole('spravce') || HasRole('podatelna') || HasRole('podatelna-odbor') || HasRole('vedouci-odbor') || HasRole('vedouci-odd')))
if (($is_edit||($is_new&&$GLOBALS['REFERENT']<>$REFERENT))) {
	EedTools::MaPristupKDokumentu($GLOBALS['EDIT_ID'], 'editace');
}

if ($is_info) {
	EedTools::MaPristupKCteniDokumentu($GLOBALS['EDIT_ID'], 'cteni');
}



If ($GLOBALS["CAPTION_ERROR"])
{
  //prislo chybovy hlaseni, vypisem error
  echo "<br><font size=3 face=verdana color=red><b>".$GLOBALS["CAPTION_ERROR"]."</b></font><br/>";
}

$path_posta = GetAgendaPath("POSTA",0,1);
If ($GLOBALS["ODES_TYP"]=='X' && !$GLOBALS["vnitrni"]=='f') {
  //jde o vnitrni postu, dame form schema vnitrni
  //include('.admin/form_schema_vnitrni.inc');
  include(FileUp2("$path_posta/.admin/form_schema_vnitrni.inc"));
}
else {
  //include('.admin/form_schema_vnejsi.inc');
  if ($is_filter) {
//    include(FileUp2("$path_posta/.admin/form_schema_filter_buttons.inc"));
//    include(FileUp2("$path_posta/.admin/form_schema_tabs_js.inc"));
    include(FileUp2("$path_posta/.admin/form_schema_filter_simple.inc"));
//    include(FileUp2("$path_posta/.admin/form_schema_filter_all.inc"));
  }
  else
    include(FileUp2("$path_posta/.admin/form_schema_vnejsi.inc"));
  If ($GLOBALS["ODESLANA_POSTA"]=='t' && $is_insert && ($GLOBALS["CONFIG"]["PRIDAT_X_DNI"]>0)) $GLOBALS[DOPIS_DATUM]=$GLOBALS[CONFIG][PRIDAT_X_DNI]; else $GLOBALS[DOPIS_DATUM]=0;
}

if ($is_info)
{
  $GLOBALS['POSTA_ID']=$GLOBALS['EDIT_ID'];
  $GLOBALS['POZN']=$GLOBALS['POZNAMKA']; //cestou se nam smaze
//  $params = array("agenda"=>"POSTA_SCHVALOVANI",  "tablename"=>"SCHVALOVANI","showedit"=>false,"showdelete"=>false,"showinfo"=>false,"sql"=>"select * from posta_schvalovani where posta_id=".$GLOBALS['EDIT_ID'],"emptyoutput"=>true);
//  Table($params);

  $cj_obj = LoadClass('EedCj',$GLOBALS['EDIT_ID']);
  $cj_info = $cj_obj->GetCjInfo($GLOBALS['EDIT_ID']);
  $spis_id = $cj_info['SPIS_ID'];
  if ($cj_info['STATUS']==-3)
  {
    $params = array("agenda"=>"SKARTACNI_KNIHA",  "tablename"=>"SPISOVNA","showedit"=>false,"showdelete"=>false,"showinfo"=>false,"sql"=>"select * from posta_spisovna where dokument_id=".$spis_id,"emptyoutput"=>false,"unsetvars"=>true);
    Table($params);

  
    $params = array("agenda"=>"POSTA_SPIS_SPISOVNA",  "tablename"=>"posta_spis_spisovna","showedit"=>false,"showdelete"=>false,"showinfo"=>false,"sql"=>"select * from posta_spisovna where dokument_id=".$spis_id,"emptyoutput"=>false,"caption"=>"Uloženo ve spisovně");
    Table($params);

  }
  $GLOBALS['POZNAMKA']=$GLOBALS['POZN']; //cestou se nam smaze

}

//parametry pro to, aby se spravne vyplnovaly informace v historii  
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"SPIS_VYRIZEN","label"=>"Datum uzavření/otevření spisu"),
              array( "type"=>"text", "name"=>"PODCISLO_SPISU","label"=>"Přiřazené podčíslo v spisovém archu"),
              array( "type"=>"text", "name"=>"CISLO_SPISU1","label"=>"Číslo spisu"),
              array( "type"=>"text", "name"=>"CISLO_SPISU2","label"=>"Rok spisu"),
              array( "type"=>"text", "name"=>"NAZEV_SPISU","label"=>"Název spisu"),
              array( "type"=>"text", "name"=>"ODBOR_SPISU","label"=>"Odbor spisu"),
              array( "type"=>"text", "name"=>"DATUM_PREDANI","label"=>"Předání podatelna -> odbor"),
              array( "type"=>"text", "name"=>"DATUM_PREDANI_VEN","label"=>"Předání odbor -> podatelna"),
              array( "type"=>"text", "name"=>"FROZEN","label"=>"Zneplatnění této adresy"),
              array( "type"=>"select_druh_prijeti", "name"=>"ZPUSOB_PODANI","label"=>"Způsob podání"),
              array( "type"=>"select_typ_odeslani", "name"=>"DOPORUCENE","label"=>"Obálka"),
              array( "type"=>"select_druh_odeslani", "name"=>"VLASTNICH_RUKOU","label"=>"Způsob vypravení"),
              array( "type"=>"select_status", "name"=>"STATUS","label"=>"Stav dokumentu"),
              array( "type"=>"select_superodbor", "name"=>"SUPERODBOR","label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"]),
              array( "type"=>"select_odbor", "name"=>"ODBOR","label"=>"Odbor"),
              array( "type"=>"select_spisovna", "name"=>"SPISOVNA_ID","label"=>"Spisovna")),
              "visible"=>$is_history and !$is_filter,
              "label"=>"");										 

if ($is_filter) {
    $FORM_CONFIG["schema"][] = array(
    "visible"=>$is_filter_all,
    "label"=>"Historie:"
  );
  if ($GLOBALS["CONFIG"]["HLEDAT_I_V_HISTORICKYCH"]) $checked_historie = " checked='checked'";
  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array( "type"=>"checkbox","name"=>"VCETNE_HISTORIE","multiple"=>1,"add"=>$checked_historie)),
    "visible"=>$is_filter_all,
    "label"=>"Včetně historických záznamů:"
  );
  
  
}

//cesta k dokumentu, typ dokumentu - vnitrni ze souboru
$FORM_CONFIG['schema'][] = array("elements"=>array(
  array("type"=>"hidden","name"=>"PATH_CONTENT", "value"=>$GLOBALS['path_content']),
  array("type"=>"hidden","name"=>"TYPE_CONTENT", "value"=>$GLOBALS['type_content'])
  
));
?>
