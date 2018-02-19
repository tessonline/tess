<?php
require_once(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedZnacka.inc');
$GLOBALS['znacka_obj'] = new EedZnacka($GLOBALS['SPIS_ID']);

$TABLE_CONFIG = array(
//  "callback"=> "ChangeClassBarva",
  "schema" => array( 
    array( field=>"JmenoZnacky(ZNACKA_ID)", label=>"<font color=black>Ukládací značka</font>","width"=>"100%"),
//    array( field=>"ZNACKA_ID", label=>"Ukládací značka","width"=>"100%"),
    
  )
 );
//}

$TABLE_CONFIG['syscolumns'] = array(
 'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);


