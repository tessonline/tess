<?php
//require_once(FileUp2('.admin/el/of_select_workflow.inc'));
require_once('table_func.inc');
require_once('javascript.inc');

$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
$is_new = In_Array($form_params["formtype"], array($f_insertfrom));

$FORM_CONFIG["schema"][] = array("elements" => array(
  array(
    "type" => "select_typ_posty",
    "name" => "ID_TYP",
    "agendacount"=>1,
    "frozen" => true,
    "selectfull" => true,
  ),
),
  "label" => "Druh dokumentu:"
);

$FORM_CONFIG["schema"][] = array("elements" => array(
  array(
    "type" => "select_workflow",
    "name" => "ID_WORKFLOW",
    "typ_posty" => ukazTyp($GLOBALS['ID_TYP']),
    "add"=>"onChange=\"WorkflowChange('PROMENNA')\"",
    "required" => false,
  ),
),
  "label" => "Workflow:"
);

$FORM_CONFIG["schema"][] = array( "elements"=>array(
  array( 
    "type"=>"select_dokument", 
    "name"=>"DOKUMENT",
    "insertnull"=>true, 
    "selectfull" => true,
    "add"=>"onChange=\"WorkflowChange('PROMENNA')\"",
  )),
  "label"=>"Dokument:");
  
$var = json_encode($select_var);

$FORM_CONFIG["schema"][] = array("elements" => array(
  array(
    "type" => "select_promenna",
    "name" => "PROMENNA",
    "workflow" => $GLOBALS["ID_WORKFLOW"],
    "dokument" => $GLOBALS["DOKUMENT"],
    "add"=>"onChange=\"promennaChange(PROMENNA,".htmlentities($var).")\"",
  ),
),
  "label" => "Proměnná:"
);



if (array_key_exists($GLOBALS["PROMENNA"],$select_var)) {
  $FORM_CONFIG["schema"][] = array("elements" => array(
    array(
      "type" => $select_var[$GLOBALS['PROMENNA']],
      "name" => "HODNOTA",
      "fullselect" => ($GLOBALS["PROMENNA"]=="ODESL_PRAC2") ? true : false,
    ),
  ),
    "label" => "Hodnota:"
  );
  
} else {
$FORM_CONFIG["schema"][] = array("elements" => array(
  array(
    "type" => "text",
    "name" => "HODNOTA",
    "size" => 90,
  ),
),
  "label" => "Hodnota:"
);

}

if ($GLOBALS['ID_WORKFLOW'] == 2) {
  $ref = getSelectDataEed(new of_select_referent(array('fullselect'=>true)));
  $GLOBALS['SCHVALUJICI_ID'] = $GLOBALS['HODNOTA'];
  $GLOBALS['SCHVALUJICI_TEXT'] = $ref[$GLOBALS['HODNOTA']];
  $GLOBALS['TYP_SCHVALENI'] = $GLOBALS['PROMENNA'];  
}

if ($GLOBALS['ID_WORKFLOW'] == 3) {
  $GLOBALS['NOVA_POLOZKA'] = $GLOBALS['PROMENNA'];
  $GLOBALS['DATOVY_TYP'] = $GLOBALS['HODNOTA'];
  
}


  
  

$FORM_CONFIG['schema'][] = array('elements'=>array(
  array( 'type'=>'select_referent', 'name'=>'SCHVALUJICI_ID','insertnull'=>true,'fullselect'=>true,'label'=>'Předvybraní:'),
  //array( 'type' => 'button', 'name' => 'Adresar', 'value' => 'Nade mnou', 'onclick' => 'ZmenReferenty(1);', 'label' => 'Nade mnou', 'tooltip' => 'test'),
  //array( 'type' => 'button', 'name' => 'Adresar2', 'value' => 'Všichni', 'onclick' => 'ZmenReferenty(2);', 'label' => 'Všichni', 'tooltip' => 'test'),
),
  //            "visible"=>$is_edit or $is_info or $is_insert ,
  "label"=>"Schvalující:",
  'visible' => true,
  
);

$FORM_CONFIG['schema'][] = array('elements'=>array(
  array( "type"=>"text", "name"=>"SCHVALUJICI_TEXT", 'size'=>50, 'add'=>'id="txtAuto""','label'=>'Vyhledání jménem',),
),
  "label"=>"Schvalující:",
  'visible' => true,
  
);


$FORM_CONFIG['schema'][] = array('elements'=>array(
  array(
    'type'=>'select_zadost_schvaleni',
    'name'=>'TYPSCHVALENI',
  ),
),
  'label'=>'Žádám o:',
  'visible' => true,
);



$FORM_CONFIG["schema"][] = array("elements" => array(
  array(
    "type" => "text",
    "name" => "NOVA_POLOZKA",
  ),
),
  "label" => "Název pole:"
);

/*
$fce = "

$.ajax({
  url: 'existuje_pole.php',
  context: document.body
}).done(function() {
  return(false);
return(true);  

});  ";

*/
/*
$FORM_CONFIG["schema"][] = array("elements"=>array(
  array("type"=>"valid_fce","name_fce"=>$fce)),
  "visible"=>($is_insert or $is_new or $is_edit),
);*/



$FORM_CONFIG['schema'][] = array('elements'=>array(
  array(
    'type'=>'select_datovy_typ',
    'name'=>'DATOVY_TYP',
  ),
),
  'label'=>'Datový typ:',
  'visible' => true,
);	


/*echo " 
<script type='text/javascript'>
jQuery(window).load(function () {
schvalovaciProces_visibility('hide');
});
</script>	
";*/



