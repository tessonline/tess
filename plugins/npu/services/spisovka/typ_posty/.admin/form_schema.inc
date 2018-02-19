<?php
/*if ($form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info || $form_params["formtype"] == $f_filterall)             
   $visible=true; else $visible=false;
*/   
    $FORM_CONFIG["schema"][] = array("elements"=>array(
//              array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY", "width"=>10,"required"=>($insert||$GLOBALS['MAIN_DOC']==1),"frozen"=>!($insert||$GLOBALS['MAIN_DOC']==1),"add"=>"onChange=\"ZmenaTypuDokumentu(this)\""),
              array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY", "width"=>10,"required"=>true),
              ),
              "label"=>"Věcná klasifikace:");										 

    $FORM_CONFIG["schema"][] = array("elements"=>array(
//              array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY", "width"=>10,"required"=>($insert||$GLOBALS['MAIN_DOC']==1),"frozen"=>!($insert||$GLOBALS['MAIN_DOC']==1),"add"=>"onChange=\"ZmenaTypuDokumentu(this)\""),
              array( "type"=>"hidden", "name"=>"ODESLANA_POSTA"),
              ),
              "label"=>"");										 

    If ($GLOBALS["CONFIG"]["UKAZ_JINE"])
       $FORM_CONFIG["schema"][] = array("elements"=>array(
                  array( "type"=>"select_jine", "name"=>"JINE","insertnull"=>true,"frozen"=>!(HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('vedouci-odd')||HasRole('zpracovatel'))),   
       ),
       "visible"=>!$is_filter,
       "label"=>"Věcná fáze:");		

  
//f ($form_params["formtype"] == $f_edit  include(FileUp2(".admin/el/owner_user_date_form_add.inc"));  

