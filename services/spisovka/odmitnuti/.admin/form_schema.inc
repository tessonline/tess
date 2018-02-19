<?php
/*if ($form_params["formtype"] == $f_edit || $form_params["formtype"] == $f_insert || $form_params["formtype"] == $f_info || $form_params["formtype"] == $f_filterall)             
   $visible=true; else $visible=false;
*/   
$doc = LoadClass('EedDokument', $GLOBALS['POSTA_ID']);
$settSO = 0;
if (in_array($doc->status, array(5,6,7))) {
  $puvSO = EedTools::VratPuvodniSUperodbor($GLOBALS['POSTA_ID']);
  if ($puvSO <> $doc->zarizeni) {
    $settSO = $puvSO;
    $FORM_CONFIG["schema"][] = array(
                  "label"=>"Vrácení na původní " . mb_strtolower($GLOBALS['CONFIG']['NAZEV_SUPERODBOR']));

  }


}

    $FORM_CONFIG["schema"][] = array( "elements"=>array(
                  array( "type"=>"textarea", "name"=>"DUVOD","rows"=>10,"cols"=>50,"required"=>true),
                  array( "type"=>"hidden", "name"=>"POSTA_ID"),
                  array( "type"=>"hidden", "name"=>"PUVODNI_SUPERODBOR","value"=>$settSO),
                  array( "type"=>"hidden", "name"=>"PODATELNA","value"=>$GLOBALS['podatelna']),
      ),
                  "label"=>"Důvod odmítnutí:");
    
      

/*      $FORM_CONFIG["schema"][] = array("elements"=>array(
        array( "type"=>"button", "name" => "btn_dalsi", "value"=>"Další","onclick"=>"document.frm_edit.submit();"),
        array( "type"=>"button", "name" => "btn_close", "value"=>"Zavřít","onclick"=>"parent.$.fancybox.close();"),
      ),
        'format' => 'btn_dalsi...\'&nbsp;\'...btn_close',
        
      );*/
  
//f ($form_params["formtype"] == $f_edit  include(FileUp2(".admin/el/owner_user_date_form_add.inc"));  

