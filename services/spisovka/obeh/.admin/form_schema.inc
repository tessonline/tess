<?php
/*if ($form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info || $form_params["formtype"] == $f_filterall)             
   $visible=true; else $visible=false;
*/   
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"hidden", "name"=>"POSTA_ID"),
                  array( "type"=>"textarea", "name"=>"OBEH_PRED","rows"=>10,"cols"=>50),
                   ),
                  "label"=>"Oběh spisu před:");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"textarea", "name"=>"OBEH_PO","rows"=>10,"cols"=>50),
                   ),
                  "label"=>"Oběh spisu po:");

  
//f ($form_params["formtype"] == $f_edit  include(FileUp2(".admin/el/owner_user_date_form_add.inc"));  

