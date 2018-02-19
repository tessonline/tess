<?php
require_once(FileUp2('plugins/npu/.config/config_pam_katalog.inc'));

/*if ($form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info || $form_params["formtype"] == $f_filterall)             
   $visible=true; else $visible=false;
*/   
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"hidden", "name"=>"SPIS_ID"),
                   ),
                  );
    $FORM_CONFIG["schema"][] = array("label"=>"Přiřazení bez specifikace v PK:");
    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                array( "type"=>"select_typ_pam_katalog", "name"=>"TYP_PK","insertnull"=>true,'only_prirazeni' => true),
                array( "type"=>"hidden", "name"=>"SPIS_ID")
                ),
//                "format"=>"ZNACKA_ID_AUTOCOMPLETE...' <small>(nutno zadat min. 3 písmena a zobrazí max. 1000 záznamů)</small>'",
                "label"=>"Vyberte \"bez rozlišení\" v památkovém katalogu:"
                );


    $FORM_CONFIG["schema"][] = array("label"=>"nebo přiřazení konkrétního záznamu v PK:");

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
//                array('type' => 'valid_fce', 'name_fce' => 'if(f.ZNACKA_ID.value == 0) { alert(\'Vyberte správnou hodnotu!\'); f.ZNACKA_ID_AUTOCOMPLETE.focus(); return false;}'),
                array( "type"=>"text", "name"=>"PK_TEXT", 'size'=>80),
                array( "type"=>"hidden", "name"=>"SPIS_ID")
                ),
//                "format"=>"ZNACKA_ID_AUTOCOMPLETE...' <small>(nutno zadat min. 3 písmena a zobrazí max. 1000 záznamů)</small>'",
                "label"=>"Označení objektu soupisu nebo záznamu ústředního seznamu:"
                );

  
//f ($form_params["formtype"] == $f_edit  include(FileUp2(".admin/el/owner_user_date_form_add.inc"));  

