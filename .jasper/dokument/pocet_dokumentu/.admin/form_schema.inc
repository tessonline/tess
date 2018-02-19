<?php
include_once(FileUp2(".admin/el/of_select_.inc"));


$FORM_CONFIG["schema"][] = array(
  "elements" => array(
    array(
      "type" => "select_typ_dokumentu",
      "name" => "P_TYP_DOKUMENTU",
      "required" => true,
    )
  ),
  "visible" => true,
  "label" => "Typ dokumentu:"
);

return $FORM_CONFIG;