<?php
$GetListOfMessagesResponse=array(
  '1'=>'zpráva byla podána',                                        
  '2'=>'DZ dostala časovou značku',                               
  '3'=>'DZ NEprošla antivirovou kontrolou',                                
  '4'=>'DZ dodána do ISDS', 
  '5'=>'DZ byla doručena náhradně, fikcí (vypršením 10 dnů)',                        
  '6'=>'DZ byla doručena přihlášením',
  '7'=>'DZ byla prectena (na portále nebo akcí ESS)',                                             
  '8'=>'DZ označena jako nedoručitelná (DS byla zpětně znepřístupněna)',           
  '9'=>'DZ byla smazána (v současné verzi takovouto DZ nelze normálně získat, v seznamu není)',    
);  

$TypDS=array(
  'OVM_NOTAR'=>'N', //'notáři',
  'OVM_EXEKUT'=>'E',//'exekutoři',
  'OVM_PFO' => 'E',
  'OVM_REQ'=>'U',//'urad v zastoupeni',

  'OVM_PO' => 'O',
  'OVM'=>'U', //normální OVM ',

  'PO'=>'P', //'DS normální PO (z obchodního rejstříku)',
  'PO_ZAK'=>'P', //'DS jiné PO vzniklé ze zákona',
  'PO_REQ'=>'P', //'DS jiné PO vzniklé na žádost',
  'PFO'=>'F',//'DS normální PFO',
  'PFO_ADVOK'=>'B',//'advokáti',
  'PFO_DANPOR'=>'F',//'daňoví poradci',
  'PFO_INSSPR'=>'F',//'insolvenční správci',

  'OVM_FO'=>'O',//'normální FO',
  'FO'=>'O',//'normální FO',
);

$TypDSRev=array_flip ($TypDS);
