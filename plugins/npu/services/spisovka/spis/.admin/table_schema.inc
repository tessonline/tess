<?php
$TABLE_CONFIG = array(
//  "callback"=> "ChangeClassBarva",
  "schema" => array( 
    array( field=>"REJSTC", label=>"Číslo rejstříku"),
    array( field=>"NAZOK", label=>"Okres"),
    array( field=>"NAZSIDUTV", label=>"Město/ves"),
    array( field=>"NAZCOB", label=>"Část obce"),
    array( field=>"CDOM", label=>"Čp."),
    array( field=>"PAMATKA", label=>"Památka"),
//    array( field=>"DATUMARCHIVACE(DATUM_ARCHIVACE,DATUM_ARCHIVACE_ODHAD)", label=>"Datum archivace","width"=>"20%"),
    array( field=>"ShowOdkaz('1',IDREG)", label=>"systém","class"=>"image"),
    array( field=>"ShowOdkaz('2',IDREG)", label=>"mapa","class"=>"image"),
    
  )
 );
//}

