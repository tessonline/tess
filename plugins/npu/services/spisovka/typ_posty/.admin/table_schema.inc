<?php
include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select.inc");
require_once(FileUp2(".admin/el/of_select_.inc"));
//require_once(GetAgendaPath('POSTA',false,false).'/.admin/table_funkce_obj.inc');

$GLOBALS['status'] = getSelectDataEed(new of_select_status(array()));
$GLOBALS['jine'] = getSelectDataEed(new of_select_jine(array()));
$GLOBALS['typ_posty'] = getSelectDataEed(new of_select_typ_posty(array('selectfull'=>true)));

$TABLE_CONFIG = array(
//  "callback"=> "ChangeClassBarva",
  "schema" => array( 
    array( field=>"KlasifikaceAFaze(TYP_POSTY, JINE)", label=>"<font color=black>Klasifikace/fáze</font>","width"=>"100%"),
   
  )
 );
//}


$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);

