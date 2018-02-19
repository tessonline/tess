<?php
include_once(FileUp2(".admin/security_name.inc"));
  If ($GLOBALS["CONFIG"]["ODDELENI"]) {
    $jaky_odbor=UkazOdbor(VratOdbor(),0,0,1);
    If (GetParentGroup($jaky_odbor)==0)
    {
      //jsem v odboru, nejsem v oddeleni
      $GLOBALS["ODBOR"]=VratOdbor();
      $GLOBALS["ODDELENI"]=''; 
    }
    else
    {
      //jsem v odboru, a jsem v oddeleni
      $GLOBALS["ODBOR"]=VratOdbor(GetParentGroup($jaky_odbor));
      $GLOBALS["ODDELENI"]=VratOdbor(); 

    }
    
  }
  else
  {
    //nepouzivame oddeleni  
    $GLOBALS["ODBOR"]=VratOdbor();
    $GLOBALS["ODDELENI"]=''; 
  }

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_mesic", "name"=>"MESIC","insertnull"=>true)),
                   "label"=>"Měsíc:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_rok", "name"=>"ROK","insertnull"=>true)),
                   "label"=>"Rok:");
/*
  If (!HasRole('spravce'))        
  {
    //$odbor=VratOdbor();
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_odbor", "name"=>"ODBOR","frozen"=>true),
              ),
              "label"=>"Odbor:");										 

  }
  else
  {
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_odbor", "name"=>"ODBOR","insertnull"=>true),
              ),
              "label"=>"Odbor:");										 
  }
  

  IF ($GLOBALS[CONFIG][ODDELENI])
  {
      $FORM_CONFIG["schema"][] = array("elements"=>array(
                array( "type"=>"select_oddeleni", "name"=>"ODDELENI","insertnull"=>true,"frozen"=>!(HasRole('spravce')||HasRole('vedouci-odbor'))),
                ),
                "visible"=>$is_filter,										 
                "label"=>"Oddělení:");										 
  }
  */
  
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"checkbox", "name"=>"HISTORIE"),
              ),
              "label"=>"Včetně historie:");										 

    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_typ_posty", "name"=>"TYP_POSTY","multiple"=>true, size=>10),
              ),
              "label"=>"Druh dokumentu:");

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
