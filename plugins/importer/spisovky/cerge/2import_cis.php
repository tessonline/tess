<?php
echo "<h1>CIS hodnoty</h1>";

$cis['s3_zpusob_doruceni'] = array(
  1 => array('label' =>	'emailem', 'tess_id' => 5),
  2 => array('label' =>	'datovou schr�nkou', 'tess_id' => 9),
  3 => array('label' =>	'datov�m nosi�em', 'tess_id' => 3),
  4 => array('label' =>	'faxem', 'tess_id' => 5),
  5 => array('label' =>	'v listinn� podob�', 'tess_id' => 1),
);

$cis['s3_zpusob_odeslani'] = array(
  1 => array('label' =>	'emailem', 'tess_id' => 5, 'doporucene'=>'E'),
  2 => array('label' =>	'datovou schr�nkou', 'tess_id' => 9),
  3 => array('label' =>	'po�tou', 'tess_id' => 1),
  4 => array('label' =>	'	faxem', 'tess_id' => 5, 'doporucene'=>'F'),
  5 => array('label' =>	'telefonicky', 'tess_id' => 5, 'doporucene'=>'F'),
  6 => array('label' =>	'osobn�', 'tess_id' => 3),
);


$cis['s3_zpusob_vyrizeni'] = array(
  1 => array('label' =>	'vy��zen� dokumentem', 'tess_id' => 'vy��zen� dokumentem'),
  2 => array('label' =>	'postoupen�', 'tess_id' => 'postoupen�'),
  3 => array('label' =>	'vzet� na v�dom�', 'tess_id' => 'vzato na v�dom�'),
  4 => array('label' =>	'jin� zp�sob', 'tess_id' => 'jin� zp�sob'),
  5 => array('label' =>	'storno', 'tess_id' => 'storno'),
  6 => array('label' =>	'email', 'tess_id' => 'email'),
  7 => array('label' =>	'telefonicky', 'tess_id' => 'telefonicky'),
  8 => array('label' =>	'datov� schr�nka', 'tess_id' => 'datov� schr�nka'),
);


$cis['s3_druh_zasilky'] = array(
  1 => array('label' =>	'oby�ejn�', 'tess_id' => 1),
  2 => array('label' =>	'doporu�en�', 'tess_id' => 2),
  3 => array('label' =>	'bal�k', 'tess_id' => -1),
  4 => array('label' =>	'do vlastn�ch rukou', 'tess_id' => 5),
  5 => array('label' =>	'dodejka', 'tess_id' => 4),
  6 => array('label' =>	'cenn� psan�', 'tess_id' => 'C'),
  7 => array('label' =>	'cizina', 'tess_id' => 'Z'),
  8 => array('label' =>	'EMS', 'tess_id' => -1),
  9 => array('label' =>	'dob�rka', 'tess_id' => -1),
);


$cis['s3_dokument_typ'] = array(
  1 => array('label' =>	'prichozi', 'tess_id' => 'f'),
  2 => array('label' =>	'odchozi', 'tess_id' => 't'),
);


$cis['org_jednotka'] = array(
  1 => array('label' =>	'NHU', 'tess_id' => 102148),
  2 => array('label' =>	'CERGE', 'tess_id' => 126),
);

$cis['s3_typ_odesl'] = array(
  'OVM_NOTAR'=> array('label' =>	'not��i', 'tess_id' => 'N'), //'not��i',
  'OVM_EXEKUT'=> array('label' =>	'exekuto�i', 'tess_id' => 'E'),//'exekuto�i',
  'OVM_PFO' => array('label' =>	'OVM PFO', 'tess_id' =>  'E'),
  'OVM_REQ'=> array('label' =>	'urad v zastoupeni', 'tess_id' => 'U'),//'urad v zastoupeni',
  'OVM_PO' => array('label' =>	'norm�ln� OVM', 'tess_id' => 'O'),
  'OVM'=> array('label' =>	'norm�ln� OVM', 'tess_id' => 'U'), //norm�ln� OVM ',
  'PO'=> array('label' =>	'DS norm�ln� PO', 'tess_id' => 'P'), //'DS norm�ln� PO (z obchodn�ho rejst��ku)',
  'PO_ZAK'=> array('label' =>	'DS jin� PO vznikl� ze z�kona', 'tess_id' => 'P'), //'DS jin� PO vznikl� ze z�kona',
  'PO_REQ'=> array('label' =>	'DS jin� PO vznikl� na ��dost', 'tess_id' => 'P'), //'DS jin� PO vznikl� na ��dost',
  'PFO'=> array('label' =>	'norm�ln� PFO', 'tess_id' => 'F'),//'DS norm�ln� PFO',
  'PFO_ADVOK'=> array('label' =>	'da�ov� poradc', 'tess_id' => 'B'),//'advok�ti',
  'PFO_DANPOR'=> array('label' =>	'da�ov� poradc', 'tess_id' => 'F'),//'da�ov� poradci',
  'PFO_INSSPR'=> array('label' =>	'insolven�n� spr�vci', 'tess_id' => 'F'),//'insolven�n� spr�vci',
  'OVM_FO'=> array('label' =>	'OVM FO', 'tess_id' => 'O'),//'norm�ln� FO',
  'FO'=> array('label' =>	'norm�ln� FO', 'tess_id' => 'O')
);

foreach($cis as $key => $val)
  echo "P�ipraven ��seln�k <font color='green'>$key</font><br/>";
