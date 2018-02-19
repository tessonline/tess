<?php
    $is_insert = In_Array($form_params["formtype"], array($f_insert));

    include_once(FileUp2(".admin/javascript.inc"));

      $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( 'type'=>'hidden', 'name'=>'SPIS','value'=>"1"),
                array( 'type'=>'hidden', 'name'=>'POSTA_ID'),
                array( 'type'=>'hidden', 'name'=>'PREV_REFERENT', 'value'=> $GLOBALS['REFERENT']),
                array( 'type'=>'hidden', 'name'=>'PREV_ODBOR', 'value'=> $GLOBALS['ODBOR']),
      ),
      );

   $FORM_CONFIG["schema"][] = array("elements"=>array(
     array( "type"=>"select_nastaveni_pristupy_rozsah", "name"=>"RANGE", "add"=>"onChange=\"JenVybrane(this);\""),
    ),
      "label"=>'Rozsah:');
      
    $FORM_CONFIG["schema"][] = array("elements"=>array(
      //array( "type"=>"select_nastaveni_pristupy", "name"=>"ACCESS", "add"=>"onChange=\"pristupyZmena();\""),
      array( "type"=>"select_nastaveni_pristupy", "name"=>"ACCESS", "add"=>"onChange=\"\""),
    ),
              "label"=>'Přístup:');


    $FORM_CONFIG["schema"][] = array("elements"=>array(
            //  array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","selectfull"=>true, "add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT'); pristupyZmena();\""),
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","selectfull"=>true, "add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT'); \""),
    ),
              "label"=>'' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':');

  if ($is_insert) {
      $a = array ("selectfull"=>true);
      $spisuzly = new of_select_vsechny_spisuzly($a);
      $GLOBALS['ODBOR'] = $spisuzly->options[0]["value"];
  }
    
    
    
    $FORM_CONFIG["schema"][] = array("elements"=>array(
    //  array( "type"=>"select_referent", "set_odbor"=>$GLOBALS['ODBOR'], "name"=>"REFERENT", "add"=>"onChange=\"pristupyZmena();\"", "fullselect"=>false,"insertnull"=>true,"label"=>"Zpracovatel"),
      array( "type"=>"select_referent",  "name"=>"REFERENT", "add"=>"onChange=\"\"", "fullselect"=>false,"insertnull"=>true,"label"=>"Zpracovatel"),
    ),
              "label"=>'Zpracovatel:');
