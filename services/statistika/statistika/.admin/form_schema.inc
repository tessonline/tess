<?php

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_mesic", "name"=>"MESIC","insertnull"=>true,label=>"Měsíc"),
                   array( "type"=>"select_rok", "name"=>"ROK","insertnull"=>true,label=>"Rok")),
                   "label"=>"Datum:");


  If (!HasRole('spravce'))        
  {
    //$odbor=VratOdbor();
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","frozen"=>true),
              ),
              "label"=>"Spisový uzel:");

  }
  else
  {
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>true),
              ),
              "label"=>"Spisový uzel:");
  }
  

      $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"select_prava", "name"=>"PRAVA","insertnull"=>true,"frozen"=>!(HasRole('spravce')||HasRole('vedouci-odbor'))),
                ),
                "visible"=>$is_filter,										 
                "label"=>"Dle role:");										 
  
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"checkbox", "name"=>"HISTORIE"),
              ),
              "label"=>"Včetně historie:");										 

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"checkbox", "name"=>"STORNOVANE"),
              ),
              "label"=>"Včetně stornovaných:");										 

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"checkbox", "name"=>"PRIRAVIT_PRO_TISK"),
              ),
              "label"=>"Připravit pro tisk:");										 

  if (!(HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('vedouci-odd')))
  {
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
    $REFERENT = $USER_INFO["ID"]; 
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"hidden", "name"=>"REFERENT","value"=>$REFERENT),
              ),
              "label"=>"");										 
  }
                   
?>
