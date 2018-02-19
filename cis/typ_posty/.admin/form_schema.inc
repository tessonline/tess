<?php
include_once(FileUp2('.admin/config.inc'));
include_once($GLOBALS["TMAPY_LIB"]."/of_textareaeditor.inc");
require_once(Fileup2(".admin/odbory.inc"));

$is_info = In_Array($form_params["formtype"], array($f_info));
$is_edit = In_Array($form_params["formtype"], array($f_edit));
//Access();

$GLOBALS['TYP_POSTY_EDITACE'] = true;

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text", "name"=>"NAZEV")),
                   "label"=>"Druh dokumentu:");

Access(array("agenda"=>"POSTA"));
/*$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>true,"enable_disabled"=>true)),
                   "label"=>"Spisový uzel:");*/

                   
                   // MULTI ITEMS SUPPORT - BEGIN
                   
                  $odbory = array();

                  if ($is_edit || $is_info)
                  $odbory = getOdbory(intval($GLOBALS['EDIT_ID']));


                   if (($is_edit || $is_info) && sizeof($odbory)>0) {
                      
                     
                     foreach ($odbory as $id => $odbor) {
                         
                       $odborName= 'ODBOR-' . $id;
                       
                       
                       
                       $FORM_CONFIG["schema"][] = array(
                         "elements"=>array(
                           array(
                             "type"=>"select_vsechny_spisuzly",
                             "name"=> $odborName,
                             'value'=> $odbor,
                             "insertnull"=>"true",
                             "enable_disabled"=>true,
                             //"frozen"=>$is_send,
                             'add' => 'data-multiple-item="true"
                        data-required="ODBOR"
                        class="required"
                        style="width: 350px;"'
                           ),
                        
                         ),
                       //  "format"=>"$organizacniVyborName...'&nbsp;Zpracovatel:'...$zpracovatelName",
                         "label"=> 'Spisový uzel:',
                         // zruseni format pro tema square
                         'theme_config' => array(
                           'square' => array(
                             'format' => '',
                           )
                         )
                       );
                       
                       
                       
                     }
                   }
                   else {
                     
                     $FORM_CONFIG["schema"][] = array(
                       "elements"=>array(
                         array(
                           "type"=>"select_vsechny_spisuzly",
                           "name"=> 'ODBOR',
                           "insertnull"=>"true",
                           "enable_disabled"=>true,
                           'add' => 'data-multiple-item="true"
                      data-required="ODBOR"
                      class="required"
                      style="width: 350px;"'
                         ),
                      ),
                   //    "visible"=>$is_update,
                       "label"=>'Spisový uzel:',
                       // zruseni format pro tema square
                       'theme_config' => array(
                         'square' => array(
                           'format' => '',
                         )
                       )
                      
                     );
                   }
                   
                   // MULTI ITEMS SUPPORT - END
                 

Access(array("agenda"=>"POSTA_CISELNIKY"));

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"text_number", "name"=>"LHUTA")),
                   "label"=>"Lhůta pro vyřízení:");


$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"select_skartace", "name"=>"SKARTACE_ID","insertnull"=>true)),
                   "label"=>"Spisový znak:");

$FORM_CONFIG["schema"][] = array( "elements"=>array(
                   array( "type"=>"hidden", "name"=>"ID_AGENDY", "value"=>$GLOBALS['doc'])),
            );
  $FORM_CONFIG["schema"][] = array( "elements"=>array(
    array( "type"=>"text", "name"=>"EXTERNAL_ID")),
    "label"=>"Externí ID pro konektor:");


$FORM_CONFIG["schema"][] = array( "elements"=>array(
  array( "type"=>"checkbox", "name"=>"NEAKTIVNI")),
  "label"=>"Neaktivní:");
  
  

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array('type' => 'textareaeditor', 'name' => 'POPIS', 'cols' => 800, 'rows' => 300)
  ),
  'label' => 'Popis workflow:'
);

?>

<style>
  /* Tlacitka pro duplikovani polozek ve formulari */
form a.button {
  display: inline-block;
  width: 22px;
  height: 22px;
  vertical-align: middle;
  cursor: pointer;
}

form a.button.add {
  background: url('./../../images/add.png');
}

form a.button.remove {
  background: url('./../../images/delete.png');
}
</style>


<script defer src="<?php echo fileUpUrl('js/multiple_items.js'); ?>" type="text/javascript"></script>
 