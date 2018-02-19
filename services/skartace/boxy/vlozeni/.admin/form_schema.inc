<?php
if (!$GLOBALS['ROK']) $GLOBALS['ROK'] = Date('Y');


    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","frozen"=>!(HasRole('spravce')||HasRole('podatelna')||HasRole('zmena_spisového uzlu')),"add"=>"id=\"ODBOR\" onChange=\"UkazPracovnika(this,'REFERENT');\"","insertnull"=>!HasRole('zmena_spisového uzlu')),
              ),
//              "visible"=>$is_edit or $is_info or $is_insert ,
              "label"=>'' . $GLOBALS["CONFIG"]["NAZEV_ODBOR"] . ':');


    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"text", "name"=>"NAZEV", "size"=>80,"required"=>"true"),
              array( "type"=>"hidden", "name"=>"ROK","value"=>$rok),
              ),
              "label"=>"Název:");

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"textarea", "name"=>"POPIS","cols"=>"80","rows"=>3,"disabled_onoff"=>$is_multiedit),
  ),
              "label"=>"Popis:");

   $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"textarea", "name"=>"UMISTENI","cols"=>"80","rows"=>3,"disabled_onoff"=>$is_multiedit),
  ),
              "label"=>"Fyzické umístění:");
