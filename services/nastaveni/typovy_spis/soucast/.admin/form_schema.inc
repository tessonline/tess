<?php
$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_update = In_Array($form_params["formtype"], array($f_insert, $f_edit));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
$is_info = In_Array($form_params["formtype"], array($f_info));


//include(FileUp2('.admin/javascript.inc'));
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"text", "name"=>"NAZEV","required"=>true, size=>60),
                   ),
                  "label"=>"Název součásti:");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array(
                    "type"=>"select_skartace",
                    "name"=>"SKARTACE_ID",
                    "insertnull" => true,
                    "add"=>'onChange="UkazSkartacniRezim(this);"',
                  ),
                  array( "type"=>"hidden", "name"=>"SKARTACE_ID_PUV"),
                   ),
                  "visible"=>$is_edit || $is_insert,
                  "label"=>$GLOBALS["CONFIG"]["NAZEV_SKARTACE"].":");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                    array(
                      "type"=>"select_skartacni_rezim",
                      "name"=>"REZIM_ID",
                      "tooltip" => "Vyberte odpovídající skartační režim. Pokud není skartační režim vybrán, bude skartační režim převzat z spisového znaku",
                      "insertnull"=>true),
                   ),
                  "visible"=>$is_edit || $is_insert,
                  "label"=>"Skartační režim:");


  $blank_line = false;
  if ($is_edit || $is_info) {
                 
    include_once(FileUp2('.admin/classes/form/Multiple.php'));
    
    $db = new DB_POSTA();
    $mul = new Multiple ($db,"posta_typovy_spis_typ_posty","id_typovy_spis","id_typ_posty");
    
    //$column_names = array('id','nazev','a.agenda');
    //$join = "left join cis_posta_agenda a on a.id=aa.id_agendy ";
    
    $column_names = array('id','id_agendy');
    
    $values = $mul->loadFormValues($GLOBALS['EDIT_ID'],"cis_posta_typ",$column_names,$join);
    
    if (count($values) == 0) $blank_line = true; 
      
    $editItems = '';
    foreach ($values as $value) {
    
      $agendaName = 'AGENDA-' . $value['ID'];
      $typPostyName = 'TYP_POSTY-' . $value['ID'];
      
      $editItems .= $typPostyName.','; 
                   
      $FORM_CONFIG["schema"][] = array(
                         "elements"=>array(
                           array(
                             "type"=>"select_agenda_dokumentu",
                             "name"=> $agendaName,
                             'value'=> $value['ID_AGENDY'],
                             "insertnull"=>"true",
                              "add" => "data-multiple-item=\"true\"
                                    data-required=\"AGENDA\"
                                    style=\"width: 350px;\"
                                    onChange=\"UkazTypPosty(this,multipleName(this,'TYP_POSTY'),'');\""
                           ),
                           array(
                             "type"=>"select_typ_posty",
                             "name"=> $typPostyName,
                             'value'=> $value['ID'],
                             'agenda_id' => $value['ID_AGENDY'],
                             "insertnull"=>"true",
                             'add' => ' data-multiple-item="true"',
                             'label' => 'Druh dokumentu:',
                           )
                         ),
                         "format"=>$agendaName."...'&nbsp;Druh dokumentu:'...".$typPostyName,
                         "label"=> 'Agenda:',
                         // zruseni format pro tema square
                         'theme_config' => array(
                           'square' => array(
                             'format' => '',
                           )
                         )
                       );
                   
                     }
                     
                     $FORM_CONFIG["schema"][] = array( "elements"=>array(
                       array( "type"=>"hidden", "name"=>"EDIT_ITEMS", "value"=>$editItems),
                     ),);
                      
                     
                     
                   }
                   else {
                     $blank_line = true;
                   }
  if ($blank_line) {
                   $FORM_CONFIG["schema"][] = array(
                     "elements"=>array(
                       array(
                         "type"=>"select_agenda_dokumentu",
                         "name"=> 'AGENDA',
                         "insertnull"=>"true",
                         "add" => "data-multiple-item=\"true\"
                                    data-required=\"AGENDA\"
                                    style=\"width: 350px;\"
                                    onChange=\"UkazTypPosty(this,multipleName(this,'TYP_POSTY'),'');\""
                       ),                     
                       array(
                         "type"=>"select_typ_posty",
                         "name"=> 'TYP_POSTY',
                         "insertnull"=>"true",
                         'add' => ' data-multiple-item="true"
                                    data-required="TYP_POSTY"',
                         'label' => 'Druh dokumentu:',
                         'fullselect' => true
                       )
                     ),
                     "format"=>"AGENDA...'&nbsp;Druh dokumentu:'...NAZEV",
                     "label"=> 'Agenda:',
                     // zruseni format pro tema square
                     'theme_config' => array(
                       'square' => array(
                         'format' => '',
                       )
                     )
                   );
  }

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"hidden", "name"=>"SPIS_ID"),
                   ),
                  "label"=>"");
   
                  
?>

<style>
  /* Tlacitka pro duplikovani polozek ve formulari */
form a.button {
  display: inline-block;
  width: 22px;
  height: 22px;
  vertical-align: middle;
  cursor: pointer;
}

form a.button.add {
  background: url('./../../../../images/add.png');
}

form a.button.remove {
  background: url('./../../../../images/delete.png');
}
</style>

<script defer src="<?php echo fileUpUrl('js/multiple_items.js'); ?>" type="text/javascript"></script>
