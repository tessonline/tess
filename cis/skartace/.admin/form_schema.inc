<?php
$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
include_once(FileUp2('.admin/javascript.inc'));

$FORM_CONFIG["schema"][] = array( "elements"=>array(
		array( 
				"type"=>"select_skartace_typ", 
				"name"=>"TYP",    
				'add' => 'onChange=\'DruhSkartaceFilter(this.value)\';onFocus=\'DruhSkartaceFilter(this.value)\'\'',
		)),
		"label"=>"Typ:");

		$FORM_CONFIG["schema"][] = array( "elements"=>array(
				array( 
					"type"=>"select_vecna_skupina", 
						"name"=>"NADRAZENE_ID",
						"insertnull" => true
				)),
				"label"=>"Nadřazená entita:");

				
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"KOD")),
                   "label"=>"Kod:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"TEXT","size"=>"80","maxlength"=>"300")),
                   "label"=>"Text:");
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_skartacni_pismeno", "name"=>"SKAR_ZNAK",'label'=>'Skar.znak'),
                   array( "type"=>"text_number", "name"=>"DOBA","size"=>"10",'label' => 'Lhůta'),
                   ),
                   "label"=>"Skar.znak:");
$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"checkbox", "name"=>"AKTIVNI","value"=>"1")),
                   "label"=>"Aktivní:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   		array( "type"=>"checkbox", "name"=>"SHOW_VS","value"=>"1")),
                   		"label"=>"Viditelné:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   		array( "type"=>"text_number", "name"=>"PRIORITA")),
                   		"label"=>"Priorita:");


$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"hidden", "name"=>"MAIN_ID")),
                   "label"=>"");

                   
                   	 