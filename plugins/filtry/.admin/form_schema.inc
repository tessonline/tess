<?php
if ($GLOBALS['NASTAVENI']) {
  $temp = explode('|', $GLOBALS['NASTAVENI']);
  foreach($temp as $tempX) {
    list($key, $val) = explode('=', $tempX);
    if (strpos($val, ',') !== false) {
      $val = explode(',',$val);
      foreach ($val as $v)
        if ($v!="") $GLOBALS[$key][] = $v;
    } else {
      $GLOBALS[$key] = $val;
          
    }
  }
}


$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"text", "name"=>"NAZEV", "size"=>90,"required"=>"true"),
  ),
  "label"=>"Název:");


$FORM_CONFIG['schema'][] = array(
  'label' => 'Výběr',
  'visible' => true,
);

$GLOBALS["CONFIG_POSTA"]["PLUGINS"] = array(); //vypneme filtry
include_once(FileUp2('.admin/form_schema_filter_all.inc'));
$form = $FORM_CONFIG['schema'];

$FORM_CONFIG = array(
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'columns' => false
      ),
    )
  )
);


$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"text", "name"=>"NAZEV", "size"=>90,"required"=>"true"),
  ),
  "label"=>"Název:");

if (HasRole('spravce'))
$FORM_CONFIG["schema"][] = array("elements"=>array(
  array( "type"=>"select_referent", "name"=>"OWNER_ID", "required"=>"true","fullselect"=>true),
  ),
  "label"=>"Zpracovatel:");


$FORM_CONFIG['schema'][] = array(
  'label' => 'Výběr',
  'visible' => true,
);


foreach($form as $formX) {
  $FORM_CONFIG['schema'][] = $formX;
}