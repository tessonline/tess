<?php

$GLOBALS['ODBOR'] = VratOdbor();
if (!$GLOBALS['smer']) $GLOBALS['smer'] = 1;

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>true,"required"=>true),
            array( "type"=>"hidden", "name"=>"SMER","value"=>$GLOBALS["smer"]),
            ),
            "label"=>"Spisový uzel:");
            
            

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$GLOBALS['REFERENT'] = $USER_INFO['ID'];
$GLOBALS['CONFIG']['VYHLEDAVANI_NAPRIC_DB'] = true;

 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_referent", "name"=>"REFERENT","fullselect"=>true),
            ),
            "label"=>"Přebírající/předávající:");
 
 $FORM_CONFIG['schema'][] = '&nbsp;';
            
            
 $FORM_CONFIG["schema"][] = array("elements"=>array(
          array( "type"=>"button", "name" => "btn_dalsi", "value"=>"Další","onclick"=>"document.frm_edit.submit();"),
       //   array( "type"=>"button", "name" => "btn_close", "value"=>"Zavřít","onclick"=>"parent.$.fancybox.close();"),
        ),
        'format' => 'btn_dalsi...\'&nbsp;&nbsp;&nbsp;\'...btn_close',
     );
?>
