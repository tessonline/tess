<?php
echo "<h1>CIS hodnoty</h1>";

$cis['s3_zpusob_doruceni'] = array(
  1 => array('label' =>	'emailem', 'tess_id' => 5),
  2 => array('label' =>	'datovou schránkou', 'tess_id' => 9),
  3 => array('label' =>	'datovým nosièem', 'tess_id' => 3),
  4 => array('label' =>	'faxem', 'tess_id' => 5),
  5 => array('label' =>	'v listinné podobì', 'tess_id' => 1),
);

$cis['s3_zpusob_odeslani'] = array(
  1 => array('label' =>	'emailem', 'tess_id' => 5, 'doporucene'=>'E'),
  2 => array('label' =>	'datovou schránkou', 'tess_id' => 9),
  3 => array('label' =>	'po¹tou', 'tess_id' => 1),
  4 => array('label' =>	'	faxem', 'tess_id' => 5, 'doporucene'=>'F'),
  5 => array('label' =>	'telefonicky', 'tess_id' => 5, 'doporucene'=>'F'),
  6 => array('label' =>	'osobnì', 'tess_id' => 3),
);


$cis['s3_zpusob_vyrizeni'] = array(
  1 => array('label' =>	'vyøízení dokumentem', 'tess_id' => 'vyøízení dokumentem'),
  2 => array('label' =>	'postoupení', 'tess_id' => 'postoupení'),
  3 => array('label' =>	'vzetí na vìdomí', 'tess_id' => 'vzato na vìdomí'),
  4 => array('label' =>	'jiný zpùsob', 'tess_id' => 'jiný zpùsob'),
  5 => array('label' =>	'storno', 'tess_id' => 'storno'),
  6 => array('label' =>	'email', 'tess_id' => 'email'),
  7 => array('label' =>	'telefonicky', 'tess_id' => 'telefonicky'),
  8 => array('label' =>	'datová schránka', 'tess_id' => 'datová schránka'),
);


$cis['s3_druh_zasilky'] = array(
  1 => array('label' =>	'obyèejné', 'tess_id' => 1),
  2 => array('label' =>	'doporuèené', 'tess_id' => 2),
  3 => array('label' =>	'balík', 'tess_id' => -1),
  4 => array('label' =>	'do vlastních rukou', 'tess_id' => 5),
  5 => array('label' =>	'dodejka', 'tess_id' => 4),
  6 => array('label' =>	'cenné psaní', 'tess_id' => 'C'),
  7 => array('label' =>	'cizina', 'tess_id' => 'Z'),
  8 => array('label' =>	'EMS', 'tess_id' => -1),
  9 => array('label' =>	'dobírka', 'tess_id' => -1),
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
  'OVM_NOTAR'=> array('label' =>	'notáøi', 'tess_id' => 'N'), //'notáøi',
  'OVM_EXEKUT'=> array('label' =>	'exekutoøi', 'tess_id' => 'E'),//'exekutoøi',
  'OVM_PFO' => array('label' =>	'OVM PFO', 'tess_id' =>  'E'),
  'OVM_REQ'=> array('label' =>	'urad v zastoupeni', 'tess_id' => 'U'),//'urad v zastoupeni',
  'OVM_PO' => array('label' =>	'normální OVM', 'tess_id' => 'O'),
  'OVM'=> array('label' =>	'normální OVM', 'tess_id' => 'U'), //normální OVM ',
  'PO'=> array('label' =>	'DS normální PO', 'tess_id' => 'P'), //'DS normální PO (z obchodního rejstøíku)',
  'PO_ZAK'=> array('label' =>	'DS jiné PO vzniklé ze zákona', 'tess_id' => 'P'), //'DS jiné PO vzniklé ze zákona',
  'PO_REQ'=> array('label' =>	'DS jiné PO vzniklé na ¾ádost', 'tess_id' => 'P'), //'DS jiné PO vzniklé na ¾ádost',
  'PFO'=> array('label' =>	'normální PFO', 'tess_id' => 'F'),//'DS normální PFO',
  'PFO_ADVOK'=> array('label' =>	'daòoví poradc', 'tess_id' => 'B'),//'advokáti',
  'PFO_DANPOR'=> array('label' =>	'daòoví poradc', 'tess_id' => 'F'),//'daòoví poradci',
  'PFO_INSSPR'=> array('label' =>	'insolvenèní správci', 'tess_id' => 'F'),//'insolvenèní správci',
  'OVM_FO'=> array('label' =>	'OVM FO', 'tess_id' => 'O'),//'normální FO',
  'FO'=> array('label' =>	'normální FO', 'tess_id' => 'O')
);

foreach($cis as $key => $val)
  echo "Pøipraven èíselník <font color='green'>$key</font><br/>";
