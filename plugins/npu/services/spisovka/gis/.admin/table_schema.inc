<?php
$TABLE_CONFIG = array(
//  'callback'=> 'ChangeClassBarva',
  'schema' => array( 
    array( field=>'GIS_ID', label=>'GIS ID'),
    array( field=>'ShowName(TYP, GIS_ID)', label=>'Název'),
//    array( field=>'DATUMARCHIVACE(DATUM_ARCHIVACE,DATUM_ARCHIVACE_ODHAD)', label=>'Datum archivace','width'=>'20%'),
    array( field=>"ShowOdkazGIS('1',GIS_ID)", label=>'systém','class'=>'image'),
    array( field=>"ShowOdkazGIS('2',GIS_ID)", label=>'mapa','class'=>'image'),
    
  )
 );
