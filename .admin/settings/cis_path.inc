<?php
$cis_path = array(
  'CIS_POSTA_TYP' => 'ost/posta/cis/typ_posty',
  'CIS_POSTA_AGENDA' => 'ost/posta/cis/agenda',
//  'CIS_POSTA_SKARTACE' => 'ost/posta/cis/skartace',
  'POSTA_CIS_SKARTACE_MAIN' => 'ost/posta/cis/skartace_main',
  'CIS_POSTA_PRIJEMCI' => 'ost/posta/cis/prijemci',
  'CIS_POSTA_ODBORY' => 'ost/posta/cis/odbory',
  'CIS_POSTA_ODDELENI' => 'ost/posta/cis/oddeleni',
  'CIS_POSTA_ULOZENO' => 'ost/posta/cis/ulozeno',
  'CIS_POSTA_JINE' => 'ost/posta/cis/jine',
  'POSTA_CIS_OSLOVENI' => 'ost/posta/cis/osloveni',
  'POSTA_CIS_SKARTACNI_REZIMY' => 'ost/posta/cis/skartacni_rezimy',
  'POSTA_CIS_SPISOVNA' => 'ost/posta/cis/spisovna',
  'POSTA_CIS_VYRIZENO' => 'ost/posta/cis/vyrizeno',
  'POSTA_CIS_ADRESATI' => 'ost/posta/cis/adresati',
  'POSTA_SPISOVNA_CIS_LOKACE' => 'ost/posta/cis/lokace',
  'CIS_POSTA_PROMENNE' => 'ost/posta/cis/promenne',
);

reset ($GLOBALS['CONFIG_POSTA']['PLUGINS']);
foreach($GLOBALS['CONFIG_POSTA']['PLUGINS'] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/settings/cis_path_end.inc');
		if (File_Exists($file)) include($file);
  }
}
