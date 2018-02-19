<?php
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
/*if ($form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info || $form_params["formtype"] == $f_filterall)             
   $visible=true; else $visible=false;
*/   


if ($is_info && !$GLOBALS['DOKUMENT_ID']) $GLOBALS['DOKUMENT_ID']=$GLOBALS['EDIT_ID'];
if ($edit || $is_insert || $is_info) {
  $q=new DB_POSTA;
  $sql='select * from posta where id='.$GLOBALS['DOKUMENT_ID'];
  $q->query($sql); $q->Next_Record();
  $GLOBALS['SKARTACE_ID']=$q->Record['SKARTACE'];
  $GLOBALS['SKARTACE_ID_PUV']=$q->Record['SKARTACE'];

  $spis = LoadClass('EedCj', $GLOBALS['DOKUMENT_ID']);
  $GLOBALS['ULOZENI'] = $spis->GetCjTypUlozeni($GLOBALS['DOKUMENT_ID']);  
  //echo "onma ".$hybrid;
}


    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array(
                    "type"=>"select_skartace",
                    "name"=>"SKARTACE_ID",
                    "add"=>'onChange="UkazSkartacniRezim(this);"',
                  ),
                  array( "type"=>"hidden", "name"=>"SKARTACE_ID_PUV"),
                   ),
                  "visible"=>$is_edit || $is_insert,
                  "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"select_dostupnost_souboru", "name"=>"VYHRAZENO"),
                   ),
                  "visible"=>$is_edit || $is_insert,
                  "label"=>"Dostupnost spisu:");


    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                     array( "type"=>"select_typ_spisu", "name"=>"ULOZENI","frozen"=>true),
                   ),
                  "visible"=>$is_edit || $is_insert,
                  "label"=>"Uložení ve spisovně:");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"hidden", "name"=>"DOKUMENT_ID"),
                  array( "type"=>"text_number", "name"=>"LISTU"),
                   ),
                  "visible"=>$is_edit || $is_insert,
                  "label"=>"Počet listů:");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"PRILOHY", size=>80),
                   ),
                  "visible"=>$is_edit || $is_insert,
                  "label"=>"Přílohy:");

  
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                    array(
                      "type"=>"text_number",
                      "name"=>"ROK_PREDANI",
                      "label" => "Rok začátku archivace",
                      "tooltip" => "Pokud nebude rok zadán, bude lhůta archivace/skartace počítána od následujícího roku od uzavření čj./spisu. Pokud bude zadán rok, lhůta se bude počítat od zadaného roku",
                    ),
                    array(
                      "type"=>"checkbox",
                      "name"=>"DATUM_ARCHIVACE_ODHAD",
                      "label" => "Jde o odhad",
                    ),
                   ),
                  //"format"=>"ROK_PREDANI...'&nbsp;&nbsp;&nbsp;Jde&nbsp;o&nbsp;odhad:'...DATUM_ARCHIVACE_ODHAD",
                  "visible"=>$is_edit || $is_insert,
                  "label"=>"Rok začátku archivace:");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                    array(
                      "type"=>"select_skartacni_rezim",
                      "name"=>"REZIM_ID",
                      "tooltip" => "Vyberte odpovídající skartační režim. Pokud není skartační režim vybrán, bude skartační režim převzat z spisového znaku",
                      "insertnull"=>true),
                   ),
                  "visible"=>$is_edit || $is_insert,
                  "label"=>"Skartační režim:");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"textarea", "name"=>"POZNAMKA","cols"=>80, "rows"=>2 ),
                   ),
                  "visible"=>$is_edit || $is_insert || $is_info,
                  "label"=>"Poznámka pro uložení:");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"textarea", "name"=>"REGISTRATURA","cols"=>80, "rows"=>2 ),
                   ),
                  "visible"=>($is_edit || $is_insert) && $GLOBALS['CONFIG']['POUZIVAT_REGISTRATURU'],
                  "label"=>"Místo uložení (registratura):");
/*
if ($is_info)
{
  require(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedCj.inc');
  require(GetAgendaPath('POSTA',false,false).'/services/spisovka/uzavreni_spisu/funkce.inc');
  require(FileUp2(".admin/brow_.inc"));
  $cj_obj = new EedCj($doc_id);
  $dalsi_cj=$cj_obj->SeznamCJvSpisu($GLOBALS['EDIT_ID']);
$table_schema=array(
  "showaccess"=>0,
  "showupload"=>0,
  "modaldialogs"=>false,
  "setvars"=>true,
  "showhistory"=>true,
  "showedit"=>false,
  "showdelete"=>0,
);
  UkazSpis_Obj($GLOBALS['EDIT_ID'],0,$table_schema);
  $GLOBALS["ukaz_ovladaci_prvky"] = false; 
  if (count($dalsi_cj)>0)
  while (list ($key, $val) = each ($dalsi_cj))
  {
    $cj_obj_temp = new EedCj($val);
    $cj_obj_info = $cj_obj_temp->GetCjInfo($val,1);
    $spis_vazba = $cj_obj_temp ->SpisVazba($val);
    UkazSpis_Obj($val,$spis_vazba['OWNER_ID'],$table_schema);
    $idcko=$spis_vazba['ID'];
  }

}  
*/
//f ($form_params["formtype"] == $f_edit  include(FileUp2(".admin/el/owner_user_date_form_add.inc"));  


