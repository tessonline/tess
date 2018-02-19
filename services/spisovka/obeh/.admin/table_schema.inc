<?php

//    array( field=>"ODESL_PRIJMENI...'&nbsp;'...ODESL_JMENO...' '...ODESL_ICO...' ,'...ODESL_ULICE...'&nbsp;'...ODESL_CP...','...ODESL_PSC...'&nbsp;'...ODESL_POSTA", label=>"Adresa"),
$TABLE_CONFIG = array(
//  "callback"=> "ChangeClassBarva",
  "schema" => array( 
    array( field=>"nl2br(OBEH_PRED)", label=>"<font color='black'>Oběh před</font>","width"=>"50%","add"=>" valign='top'"),
    array( field=>"nl2br(OBEH_PO)", label=>"<font color='black'>Oběh po</font>","width"=>"50%","add"=>" valign='top'"),
    
  )
 );
//}

$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);


