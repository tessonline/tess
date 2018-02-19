<?php
include_once($GLOBALS['TMAPY_LIB'].'/of_textareaeditor.inc');

$GLOBALS['URL'] = 'https://' . $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI'];
$GLOBALS['URL'] = str_replace('edit', 'show', $GLOBALS['URL']);

$FORM_CONFIG["schema"][] = array(
  "elements" => array(
    array(
      "type" => "text",
      "name" => "NAZEV",
      "size" => 80
    )
  ),
  "label" => "Název dokumentace:"
);

$FORM_CONFIG["schema"][] = array(
  "elements" => array(
    array(
      "type" => "text",
      "name" => "POPIS",
      "size" => 80
    )
  ),
  "label" => "Stručný popis dokumentace:"
);

if (HasRole('lokalni-spravce')) $GLOBALS['SUPERODBOR'] = EedTools::VratSuperOdbor();

$FORM_CONFIG["schema"][] = array("elements"=>array(
          array(
            "type"=>"select_superodbor",
            "name"=>"SUPERODBOR",
            "insertnull"=>true,
            "frozen" => !HasRole('spravce')),
          ),
          "visible" => ($GLOBALS['CONFIG']['USE_SUPERODBOR'] ? true : false),
          "label"=>$GLOBALS["CONFIG"]["NAZEV_SUPERODBOR"].":");

$FORM_CONFIG['schema'][] = array(
  'elements' => array(
    array('type' => 'textareaeditor', 'name' => 'TEXT', 'cols' => 1024, 'rows' => 600)
  ),
  'label' => 'HTML text:'
);

$FORM_CONFIG["schema"][] = array(
  "elements" => array(
    array(
      "type" => "text",
      "name" => "URL",
      "frozen" => true
    )
  ),
  "label" => "URL odkaz:"
);

