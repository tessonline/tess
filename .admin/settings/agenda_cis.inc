<?php
$agenda_cis = array(
  'POSTA' => array(
    'CIS_POSTA_AGENDA',
  //  'CIS_POSTA_TYP',
    'POSTA_CIS_VYRIZENO',
//    'CIS_POSTA_JINE',
//    'CIS_POSTA_SKARTACE',
    'POSTA_CIS_SKARTACE_MAIN',
    'CIS_POSTA_ODBORY',
    'POSTA_CIS_OSLOVENI',
    'POSTA_CIS_SKARTACNI_REZIMY',
    'POSTA_CIS_SPISOVNA',
    'POSTA_CIS_ADRESATI',
    'POSTA_SPISOVNA_CIS_LOKACE',
//    'CIS_POSTA_ULOZENO',
  )


);


reset ($GLOBALS['CONFIG_POSTA']['PLUGINS']);
foreach($GLOBALS['CONFIG_POSTA']['PLUGINS'] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/settings/agenda_cis_end.inc');
		if (File_Exists($file)) include($file);
  }
}



if (!Access(array("agenda"=>"POSTA_CISELNIKY"))) {
  $agenda_cis = array();
} else {
  if (HasRole('lokalni-spravce')&&!HasRole('spravce')&&!HasRole('access_all')) {
    $agenda_cis = array(
      'POSTA' => array(
        'CIS_POSTA_AGENDA',
        'POSTA_CIS_SPISOVNA',
        'CIS_POSTA_ODBORY',
      )
    );
  }
}

if (Access(array("agenda"=>"POSTA_CISELNIKY"))) {
  if (!HasRole('lokalni-spravce')&&!HasRole('spravce')&&!HasRole('access_all')) 
  $agenda_cis = array();
}

Access(array("agenda"=>"SKARTACNI_KNIHA"));
if (HasRole('spisovna')) {
  if (!in_array("POSTA_CIS_SPISOVNA", $agenda_cis['POSTA']))
    $agenda_cis['POSTA'][] = "POSTA_CIS_SPISOVNA";
  if (!in_array("POSTA_SPISOVNA_CIS_LOKACE", $agenda_cis['POSTA']))
    $agenda_cis['POSTA'][] = "POSTA_SPISOVNA_CIS_LOKACE";
}


