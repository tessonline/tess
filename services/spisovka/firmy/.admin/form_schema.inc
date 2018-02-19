<script language="JavaScript" type="text/javascript">
<!--
   var ChObj = false;
//-->
</script>
<?php
/*if ($form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info || $form_params["formtype"] == $f_filterall)             
   $visible=true; else $visible=false;
*/   
if ($form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_info):
 $qq = new $GLOBALS["CONFIG"]["DB_NAME"];
 $qq->query("SELECT cobce_kod,cisdom_typ,cisdom_hod FROM ".$GLOBALS["CONFIG"]["TABLE_PREFIX"]."objekt WHERE objekt_kod=".$GLOBALS["OBJEKT_KOD"]);
 $qq->next_record();
 $cobce_kod = $qq->Record["COBCE_KOD"];
 $cisdom_typ = $qq->Record["CISDOM_TYP"];
 $cisdom_hod = $qq->Record["CISDOM_HOD"];
endif;
if ($form_params["formtype"] == $f_edit):
 $qq->query("SELECT count(adresa_kod) as pocet FROM ".$GLOBALS["CONFIG"]["TABLE_PREFIX"]."adresa WHERE objekt_kod=".$GLOBALS["OBJEKT_KOD"]." AND stav in (1,11)");
 $qq->next_record();
 $pocet=$qq->Record["POCET"];
// echo $pocet;
 if ($pocet > 1) {
   $fce  = "var msg = 'Na číslo domovní - ".$cisdom_hod." v této části obce, jsou vázány další adresy. Opravdu chcete provést změnu u všech adres?'\n";
   $fce .= "if (ChObj == true) return(confirm(msg));\n";
 } else $fce=""; 
endif;

$FORM_CONFIG = array(
  "schema"=>array(
/*
    array(
      "label"=>$PROPERTIES["AGENDA_NAME"]
    ),
*/
    array(
      "elements"=>array(
         array("type"=>"valid_fce","name_fce"=>$fce),      
         array("type"=>"hidden","name"=>"POCET_ADR","value"=>$pocet),
         array("type"=>"hidden","name"=>"OBJEKT_KOD"),
         array("type"=>"hidden","name"=>"STAV","value"=>11)),
    ),
    array(
      "elements"=>array(array("type"=>"hidden","name"=>"FROM_OBYVATELE","value"=>true)),
      "visible"=>isset($form_params["from_obyvatele"]) && $form_params["from_obyvatele"],
    ),
    array(
      "elements"=>array(array("type"=>"select_ulice","name"=>"ULICE_KOD","frozen"=>isset($GLOBALS["ukonceni"]),"value"=>$GLOBALS["ULICE_KOD"],"required"=>true,"insertnull"=>true)),
			"visible"=>$form_params["formtype"] != $f_insert,
      "label"=>"Ulice:"
    ),
    array(
      "elements"=>array(array("type"=>"select_ulice","name"=>"ULICE_KOD","frozen"=>isset($GLOBALS["ukonceni"]),"required"=>true,"insertnull"=>true)),
			"visible"=>$form_params["formtype"] == $f_insert,
      "label"=>"Ulice:"
    ),
    array(
      "elements"=>array(
          array("type"=>"text_number","name"=>"CISOR_HOD","size"=>3,"maxlength"=>3,"frozen"=>isset($GLOBALS["ukonceni"]),"value"=>$GLOBALS["COR"]),
          array("type"=>"text","name"=>"CISOR_PIS","frozen"=>isset($GLOBALS["ukonceni"]))),
			"visible"=>true,
      "format"=>"CISOR_HOD...'&nbsp;písmeno: '...CISOR_PIS",
      "label"=>"Číslo orientační:",
    ),
    array(
      "elements"=>array(
          array("type"=>"select_cisdom_typ","name"=>"OB_CISDOM_TYP","required"=>true),
          array("type"=>"text_number","name"=>"OB_CISDOM_HOD","size"=>5,"maxlength"=>5,"required"=>true,"value"=>$GLOBALS["CDOM"])),
			"visible"=>$form_params["formtype"] == $f_insert,
      "format"=>"OB_CISDOM_TYP...'&nbsp;&nbsp;&nbsp;'...OB_CISDOM_HOD",
      "label"=>"Číslo domovní:",
    ),
    array(
      "elements"=>array(
          array("type"=>"select_cisdom_typ","name"=>"OB_CISDOM_TYP","value"=>$cisdom_typ,"required"=>true,"frozen"=>isset($GLOBALS["ukonceni"]),"add"=>"onchange='ChObj = true;'"),
          array("type"=>"text_number","name"=>"OB_CISDOM_HOD","value"=>$cisdom_hod,"size"=>5,"maxlength"=>5,"required"=>true,"frozen"=>isset($GLOBALS["ukonceni"]),"add"=>"onchange='ChObj = true;'")),
			"visible"=>$form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_info,
      "format"=>"OB_CISDOM_TYP...'&nbsp;&nbsp;&nbsp;'...OB_CISDOM_HOD",
      "label"=>"Číslo domovní:",
    ),
    array(
      "elements"=>array(array("type"=>"text_number","name"=>"PSC","size"=>5,"maxlength"=>5,"frozen"=>isset($GLOBALS["ukonceni"]))),
			"visible"=>true,
      "label"=>"PSČ:"
    ),
    array(
      "elements"=>array(array("type"=>"select_cobce","name"=>"OB_COBCE_KOD","value"=>$GLOBALS["COBCE_KOD"],"insertnull"=>true,"required"=>true)),
			"visible"=>$form_params["formtype"] == $f_insert,
      "label"=>"Část obce"
    ),
    array(
      "elements"=>array(array("type"=>"select_cobce","name"=>"OB_COBCE_KOD","value"=>$cobce_kod,"required"=>true,"frozen"=>isset($GLOBALS["ukonceni"]),"add"=>"onchange='ChObj = true;'")),
			"visible"=>$form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_info,
      "label"=>"Část obce"
    ),
		
	
/*
    array(
      "elements"=>array(
         array("type"=>"select_volokrsek","name"=>"VOL_OKRSEK","start_num"=>1,"end_num"=>48,"insertnull"=>true,"required"=>true,"frozen"=>isset($GLOBALS["ukonceni"])),
         array("type"=>"text","name"=>"INDEX_DUM","frozen"=>isset($GLOBALS["ukonceni"]))),
			"visible"=>true,
      "format"=>"VOL_OKRSEK...'&nbsp;&nbsp;&nbsp;Index domu:&nbsp;'...INDEX_DUM",
      "label"=>"Volební okrsek:"
    ),
    array(
      "elements"=>array(array("type"=>"textarea","name"=>"POZNAMKA","rows"=>3,"cols"=>50,"frozen"=>isset($GLOBALS["ukonceni"]))),
			"visible"=>true,
      "label"=>"Poznámka:"
    ),
    
 
    array(
      "label"=>"Informace o vzniku, zániku a editaci"
    ),
    array(
      "elements"=>array(array("type"=>"date_db","name"=>"VZNIK_DNE","insertdatebutton"=>true)),
			"visible"=>$form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info,
      "label"=>"Vznik dne:"
    ),
    array(
      "elements"=>array(array("type"=>"textarea","name"=>"VZNIK_INFO","rows"=>2,"cols"=>50)),
			"visible"=>$form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info,
      "label"=>"Poznámka o vzniku:"
    ),
    array(
      "elements"=>array(array("type"=>"date_db","name"=>"ZANIK_DNE","insertdatebutton"=>true)),
			"visible"=>$form_params["formtype"] == $f_edit,
      "label"=>"Změna dne:"
    ),
    array(
      "elements"=>array(array("type"=>"textarea","name"=>"ZANIK_INFO","rows"=>2,"cols"=>50)),
			"visible"=>$form_params["formtype"] == $f_edit,
      "label"=>"Poznámka ke změně:"
    ),
    array(
      "elements"=>array(
         array("type"=>"hidden","name"=>"UKONCENI","value"=>"12"),
         array("type"=>"hidden","name"=>"VZNIK_DNE"),
         array("type"=>"hidden","name"=>"VZNIK_INFO")),
      "visible"=>isset($GLOBALS["ukonceni"]),
    ),
    
    array(
      "elements"=>array(array("type"=>"textarea","name"=>"ZANIK_INFO","rows"=>3,"cols"=>50)),
			"visible"=>true,
      "label"=>"Zánik INFO:"
    ),

    array(
      "label"=>"Objekt"
    ),
    array(
      "elements"=>array(array("type"=>"select_cobce","name"=>"OB_COBCE_KOD","value"=>$cobce,"add"=>"class='required'")),
			"visible"=>true,
      "label"=>"Část obce"
    ),
    array(
      "elements"=>array(
          array("type"=>"text_number","name"=>"OB_CISDOM_TYP","value"=>$cisdom_typ,"add"=>"class='required'"),
          array("type"=>"text_number","name"=>"OB_CISDOM_HOD","value"=>$cisdom_hod,"add"=>"class='required'")),
			"visible"=>true,
      "format"=>"'&nbsp;&nbsp;typ: '...OB_CISDOM_TYP...'&nbsp;hodnota: '...OB_CISDOM_HOD",
      "label"=>"Číslo domovní:",
    ),
    array(
      "elements"=>array(array("type"=>"text_number","name"=>"OB_STAV","value"=>$stav,"add"=>"class='required'")),
			"visible"=>true,
      "label"=>"Stav:"
    ),
    array(
      "elements"=>array(
         array("type"=>"date_db","name"=>"OB_VZNIK_DNE","value"=>$vznik_dne),
         array("type"=>"date_db","name"=>"OB_ZANIK_DNE","value"=>$zanik_dne)),
			"visible"=>true,
      "format"=>"'vzniku: '...OB_VZNIK_DNE...'&nbsp;&nbsp;zániku: '...OB_ZANIK_DNE",
      "label"=>"Den:"
    ),
    array(
      "elements"=>array(array("type"=>"textarea","name"=>"OB_VZNIK_INFO","rows"=>3,"cols"=>50,"value"=>$vznik_info)),
			"visible"=>true,
      "label"=>"Vznik INFO:"
    ),
    array(
      "elements"=>array(array("type"=>"textarea","name"=>"OB_ZANIK_INFO","rows"=>3,"cols"=>50,"value"=>$zanik_info)),
			"visible"=>true,
      "label"=>"Zánik INFO:"
    ),

*/

  ) 
);    

/*
$text = $GLOBALS["TEXT_ZAP"];
$FORM_CONFIG["schema"][] = array(
      "elements"=>array(array("type"=>"text","name"=>"ADRESA_KOD","value"=>$text)),
			"visible"=>true,
      "label"=>"Záplavová území při Q100:"
		
	
);
*/
		
//if ($form_params["formtype"] == $f_info) include(FileUp2(".admin/el/urednik_id_zmena_dat_cas.inc"));    
?>
