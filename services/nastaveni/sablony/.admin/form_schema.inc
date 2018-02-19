<?php
include(FileUp2('.admin/javascript.inc'));

include_once(FileUp2(".admin/table_func.inc"));

$is_insert = In_Array($form_params["formtype"], array($f_insert));

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"NAZEV")),
                   "label"=>"Název šablony:");

if (!HasRole('spravce')) $GLOBALS['ID_SUPERODBOR'] = EedTools::VratSuperOdbor();

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>true,"selectfull"=>false,"enable_disabled"=>true)),"label"=>"Spisový uzel:");

$FORM_CONFIG["schema"][] = array("elements"=>array(
                     array(
                       "type"=>"select_superodbor",
                       "name"=>"ID_SUPERODBOR",
                       "insertnull"=>true,
                       "add"=>"onChange=\"AgendaFiltr(this,'AGENDA_DOKUMENTU');\"",
                       "frozen" => !HasRole('spravce')
                     ),
                   ),
                     "visible" => ($GLOBALS['CONFIG']['USE_SUPERODBOR'] ? true : false),
                     "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");

if (!$is_insert)

//  $GLOBALS['AGENDA_DOKUMENTU'] =  agendaDokumentu($GLOBALS['TYP_POSTY']);
  
$GLOBALS['AGENDA_DOKUMENTU'] =  selectedAgenda($GLOBALS['TYP_POSTY'],false);            
 

$FORM_CONFIG["schema"][] = array("elements"=>array(
                     array( 
                       "type"=>"select_agenda_dokumentu", 
                       "name"=>"AGENDA_DOKUMENTU",
                       "superodbor" => $GLOBALS['ID_SUPERODBOR'],
                       "jen_odbor" => !HasRole('spravce')&&!HasRole('lokalni-spravce')&&HasRole('spravce-odbor-sablony'),
                       "insertnull"=>false,
                       "add"=>"onChange=\"UkazTypPosty(this,'TYP_POSTY','','',1);\"","label"=>"Agenda"),
  ),
  );

if ($GLOBALS['AGENDA_DOKUMENTU']==null) $is_insert = true;
  
  $FORM_CONFIG["schema"][] = array("elements"=>array(
  
                     array(
                       "type"=>"select_typ_posty",
                       "name"=>"TYP_POSTY",
                       "default_agenda" => $is_insert,
                       "agenda_id" => $GLOBALS['AGENDA_DOKUMENTU'],
                       "insertnull"=>false,
                       "label"=>"Druh dokumentu",
                    //   "add"=>"onChange=\"ZmenaTypuDokumentu(this); AgendaDocOnChange(this,'AGENDA_DOKUMENTU','".$GLOBALS['odeslana']."');\" onfocus=\"this.selectedIndex = -1;\"",
                       //                "lhuta"=>getLhutaDleKlasifikace()
                     ),                  
                   ),
                   );                     
                  
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text_number", "name"=>"ID_DOKUMENTU","size"=>20,'maxlength'=>15)),
                   "label"=>"ID dokumentu pro test:");


                    
?>
