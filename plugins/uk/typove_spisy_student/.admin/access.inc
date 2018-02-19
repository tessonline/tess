<?php

$PROPERTIES_ACCESS['POSTA_PLUGINS_UK_STUDENT'] = array(
  'desc'=>'SYNCHRONIZACE typ.spisů studentů.',
		'rights' => array(
				"all_read"         => array('desc'=>"číst všechny záznamy", 'ceu_invisible'=>true),
				"all_insert"       => array('desc'=>"vkládat nové záznamy", 'ceu_invisible'=>true),
				'all_update'       => array('desc'=>'upravovat záznamy', 'ceu_invisible'=>true),
				'all_delete'       => array('desc'=>'mazat záznamy', 'ceu_invisible'=>true),


		),
		'rightgroups' => array(
				'spravce' => array(
						'desc'=>"Správce všeho",
						'contains' => array('all_read','all_insert','all_update','all_delete')
				),
				'lokalni-spravce' => array(
						'desc'=>"Správce pouze za součást",
						'contains' => array('all_read','all_insert','all_update','all_delete')
				),
		)
);


$spravce = HasRole('spravce')||HasRole('super_spravce');
if (!$spravce) {
  foreach ($PROPERTIES_ACCESS as $key => $value) {
    unset($PROPERTIES_ACCESS[$key]['rightgroups']['spravce']);
  }
}

