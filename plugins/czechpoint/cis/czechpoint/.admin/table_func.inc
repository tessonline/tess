<?php
require_once(FileUp2('.admin/oth_funkce_2D.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

$GLOBALS['CONFIG']['VYHLEDAVANI_NAPRIC_DB'] = true;
$GLOBALS['referent_id'] = getSelectDataEed(new of_select_referent(array('fullselect'=>true)));

Function ShowUser($ref_id) {
  $ret = $GLOBALS['referent_id'][$ref_id];
  if (!$ret) $ret = $ref_id;
  return $ret;
}


