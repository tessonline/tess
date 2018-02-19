<?php

/*echo "Puvodni ".$GUIDE_NAME."<br/>";
echo "Nove ".$GUIDE_NAME_MOJE;
*/
include_once(FileUp2('.admin/config.inc'));

$is_filter = In_Array($form_params["formtype"], array($f_filter, $f_filter_all));
$is_filter_all = In_Array($form_params["formtype"], array($f_filter_all));
$is_filter_simple = In_Array($form_params["formtype"], array($f_filter));
$is_insert = In_Array($form_params["formtype"], array($f_insert));
$is_update = In_Array($form_params["formtype"], array($f_insert, $f_edit));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
$is_info = In_Array($form_params["formtype"], array($f_info));
$is_new = In_Array($form_params["formtype"], array($f_insertfrom)); 


If ($GLOBALS["CONFIG"]["KONTROLA_UIR"]) $KONTROLA_UIR="<input type='button' class='button btn' onclick=\"javascript:UirAdr(3714)\" value='UIRADR-okres'>&nbsp;&nbsp;&nbsp;<input type='button' class='button btn' onclick=\"javascript:UirAdr(0)\" value='UIRADR-ČR'>";
else
{
  $KONTROLNI_PANEL="";	
  $KONTROLNI_PANEL_ROB="<input type='button' class='button btn' onclick=\"javascript:Rob()\" value='R'>";	
}

If (!$is_filter)
{
  include(FileUp2('.admin/javascript.inc'));
}

If ($is_filter)
{
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"ODESL_PRIJMENI","size"=>"40")),   
						"label"=>"Příjmení/Název firmy:");		

}
else
{
  
  
  include(FileUp2('/.admin/form_schema_adresat.inc'));

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"hidden", "name"=>"ODESL_ADRESAT","value"=>$GLOBALS["ODESL_ADRESAT"]),
            array( "type"=>"hidden", "name"=>"ODESL_ADRKOD"),
            array( "type"=>"hidden", "name"=>"OBJEKT_KOD"),
            array( "type"=>"hidden", "name"=>"ODESL_RC"),
            array( "type"=>"hidden", "name"=>"OBYVATEL_KOD"),
            array( "type"=>"hidden", "name"=>"FROZEN"),
            ),
            "label"=>"");		

}


?>
