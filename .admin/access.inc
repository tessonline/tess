<?php

$config = TW_AppConfig::getInstance('ders-uk-test');

$PROPERTIES_ACCESS['POSTA'] = array(
  'desc'=>'Přístup k evidenci dokumentů.',
  'jasperrights' => array(
    'folders' => $config['JASPER']['folders']),
  'rights'=>array(
    "all_read"         => array('desc'=>"přístup do ESS pro čtení", 'ceu_invisible'=>true),
    "all_insert"       => array('desc'=>"vkládat nové odchozí záznamy", 'ceu_invisible'=>true),
    'all_update'       => array('desc'=>'editovat záznamy', 'ceu_invisible'=>true),
    'all_delete'       => array('desc'=>'mazat záznamy', 'ceu_invisible'=>true),
	'export'           => array('desc'=>'exportovat záznamy', 'ceu_invisible'=>false),
    
    "condition_update_dokument" => array('desc'=>"aktualizovat vytvořené dokumenty",
      'conditions'=>array(
        'POSTA'=>array('condition'=>' AND status>1 '),
        '*'=>array('condition'=>'')),
      'ceu_invisible'=>true,
    ),
    "condition_delete_dokument" => array('desc'=>"stornovat vytvořené dokumenty",
      'conditions'=>array(
      'POSTA'=>array('condition'=>' AND status>1 '),
      //'POSTA_HROMADNY_IMPORT'=>array('condition'=>' AND (zamceno>-1 OR zamceno is null) '),
      //pro boxy povolime mazani
      'POSTA_SPISOVNA_BOXY_VLOZENI'=>array('condition'=>' AND 1=1'),
      'POSTA_CPOST'=>array('condition'=>' AND DATUM_VYTISTENI is null'),
      '*'=>array('condition'=>'')),
      'ceu_invisible'=>true,
    ),
    
 /*   "condition_update_dz" => array('desc'=>"aktualizovat dz",
      'conditions'=>array(
        "POSTA"=>array("condition"=>" OR vlastnich_rukou='9'"),
        '*'=>array('condition'=>'')),
      'ceu_invisible'=>true,
    ),*/
    "condition_delete_prichozi_dokument" => array('desc'=>"stornovat příchozí dokumenty",
      'conditions'=>array(
        'POSTA'=>array('condition'=>' AND status>1'),
        //'POSTA'=>array('condition'=>' AND status>1 AND odeslana_posta is false'),
        //pro boxy povolime mazani
        'POSTA_SPISOVNA_BOXY_VLOZENI'=>array('condition'=>' AND 1=1'),
        '*'=>array('condition'=>'')),
      'ceu_invisible'=>true,
    ),
    "condition_delete_odchozi_dokument" => array('desc'=>"stornovat odchozí dokumenty",
      'conditions'=>array(
        'POSTA'=>array('condition'=>' AND status>1'),
        //'POSTA'=>array('condition'=>' AND status>1 AND odeslana_posta is true'),
        //pro boxy povolime mazani
        'POSTA_SPISOVNA_BOXY_VLOZENI'=>array('condition'=>' AND 1=1'),
        '*'=>array('condition'=>'')),
      'ceu_invisible'=>true,
    ),
    "condition_delete_ostatni" => array('desc'=>"stornovat v některých app",
      'conditions'=>array(
        'POSTA_USER_FILTRY'=>array('condition'=>''),
        'POSTA_PRISTUPY'=>array('condition'=>''),
        'POSTA_PRIDANI_SPISU'=>array('condition'=>''),

      ),
      'ceu_invisible'=>true,
    ),
    "condition_read_odeprit_dz" => array('desc'=>"zamezí příchozí DZ",
      'conditions'=>array(
        "POSTA"=>array("condition"=>" AND ((odeslana_posta is true) OR (vlastnich_rukou<>'9'))"),        
      ),
      'ceu_invisible'=>true,
    ),
    
    "condition_read_zobrazit_dz" => array('desc'=>"zobrazí všechny DZ",
      'conditions'=>array(
        "POSTA"=>array("condition"=>" OR ((odeslana_posta is true) OR (vlastnich_rukou<>'9'))"),
      ),
      'ceu_invisible'=>true,
    ),    
  ),

  'rightgroups' => array(

    'pristup' => array(
      'desc' => "Povolí přístup do ESS",
      'contains' => array('all_read')
    ),

    'cteni_zpracovatel' => array(
      'desc' => "Povolí čtení vlastních záznamů",
      'contains' => array('all_read')
    ),

    'cteni_uzel' => array(
      'desc' => "Povolí čtení záznamů vlastního spisového uzlu",
      'contains' => array('all_read')
    ),

    'cteni_vse_pracoviste' => array(
      'desc' => "Povolí čtení všech záznamů pracoviště",
      'contains' => array('all_read')
    ),

    'cteni_admin' => array(
      'desc' => "Povolí čtení všech záznamů ESS",
      'contains' => array('all_read')
    ),

    'zpracovat-odbor' => array(
      'desc'=>"Vedoucím v oddělení umožní vidět(pracovat) s dokumenty v odboru.",
      'contains' => array('all_read')
    ),


    'editace_zpracovatel' => array(
      'desc' => "Povolí editaci záznamů zpracovatele",
      'contains' => array('all_insert', 'condition_update_dokument')
    ),

    'editace_uzel' => array(
      'desc' => "Povolí editaci záznamů vlastního spisového uzlu",
      'contains' => array('all_insert', 'condition_update_dokument')
    ),

  	'editace_vse_pracoviste' => array(
      'desc' => "Povolí editaci všech záznamů pracoviště",
      'contains' => array('condition_update_dokument')
    ),

    'editace_admin' => array(
      'desc' => "Povolí editaci všech záznamů ESS",
      'contains' => array('all_insert', 'condition_update_dokument')
    ),

 /*   'storno_zpracovatel' => array(
      'desc' => "Povolí storno záznamů zpracovatele",
      'contains' => array('condition_delete_dokument')
    ),

    'storno_uzel' => array(
      'desc' => "Povolí storno záznamů vlastního spisového uzlu",
      'contains' => array('condition_delete_dokument')
    ),

    'storno_vse_pracoviste' => array(
      'desc' => "Povolí storno všech záznamů pracoviště",
      'contains' => array('condition_delete_dokument')
    ),

    'storno_admin' => array(
      'desc' => "Povolí storno všech záznamů ESS",
      'contains' => array('condition_delete_dokument')
    ),*/
    
    
    'storno_prichozi_zpracovatel' => array(
      'contains' => array('condition_delete_prichozi_dokument')
    ),
    
    'storno_prichozi_uzel' => array(
      'desc' => "Povolí storno příchozích záznamů vlastního spisového uzlu",
      'contains' => array('condition_delete_prichozi_dokument')
    ),
    
    'storno_prichozi_vse_pracoviste' => array(
      'desc' => "Povolí storno všech příchozích záznamů pracoviště",
      'contains' => array('condition_delete_prichozi_dokument')
    ),
    
    'storno_prichozi_admin' => array(
      'desc' => "Povolí storno všech příchozích záznamů ESS",
      'contains' => array('condition_delete_prichozi_dokument')
    ),
    
    'storno_odchozi_zpracovatel' => array(
      'desc' => "Povolí storno odchozích záznamů zpracovatele",
      'contains' => array('condition_delete_odchozi_dokument')
    ),
    
    'storno_odchozi_uzel' => array(
      'desc' => "Povolí storno odchozích záznamů vlastního spisového uzlu",
      'contains' => array('condition_delete_odchozi_dokument')
    ),
    
    'storno_odchozi_vse_pracoviste' => array(
      'desc' => "Povolí storno všech odchozích záznamů pracoviště",
      'contains' => array('condition_delete_odchozi_dokument')
    ),
    
    'storno_odchozi_admin' => array(
      'desc' => "Povolí storno všech odchozích záznamů ESS",
      'contains' => array('condition_delete_odchozi_dokument')
    ),
    
    'vloz_prichozi' => array(
      'desc' => "Povolí vložení příchozích dokumentů",
      'contains' => array('all_insert')
    ),

    'vloz_odchozi' => array(
      'desc' => "Povolí vložení odchozích dokumentů",
      'contains' => array('all_insert')
    ),

    'zmena-pracoviste' => array(
      'desc'=>"Možnost editace přiděleného pracoviště",
      'contains' => array('condition_update_dokument')
    ),

    'zmena-spisoveho-uzlu' => array(
      'desc'=>"Možnost editace spisového uzlu, pouze podřízené uzly",
      'contains' => array('condition_update_dokument')
    ),

    'zmena-spisoveho-uzlu-nahoru' => array(
      'desc'=>"Možnost editace spisového uzlu i v org. struktuře výše",
      'contains' => array('zmena-spisoveho-uzlu','condition_update_dokument')
    ),

    'edit-datum-prijeti' => array(
      'desc'=>"Možnost editace datumu přijetí",
      'contains' => array('condition_update_dokument')
    ),
  	'edit-datum-vypraveni' => array(
		'desc'=>"Možnost editace datumu vypravení",
  		'contains' => array('condition_update_dokument')
  		),
    
    'vypraveni-ds' => array(
      'desc'=>"Vypravení datové zprávy",
      'contains' => array('all_read')
    ),
    
    'vypraveni-email' => array(
      'desc'=>"Vypravení emailu",
      'contains' => array('all_read')
    ),
    
    'vypraveni-int-posta' => array(
      'desc'=>"Vypravení interní pošty",
      'contains' => array('all_read')
    ),

    'prevzit-z-podatelny' => array(
      'desc'=>"Převzít dokumenty z podatelny",
      'contains' => array('all_read')
    ),
    
    'vypraveni-predani' => array(
      'desc'=>"Vypravení listinného pošty ČP (předání na podatelnu)",
      'contains' => array('all_read')
    ),
    
    'odeprit-odchozi-dz' => array(
      'desc'=>"Odepření všech odchozích datových zpráv kromě vypravených zpracovatelem",
      'contains' => array('all_read')
    ),
    
    'odeprit-dz' => array(
      'desc'=>"Odepření všech příchozích datových zpráv",
      'contains' => array('all_read')
    ),

   /* 'zobrazit-dz' => array(
      'desc'=>"Zobrazení všech příchozích datových zpráv",
      'contains' => array('condition_read_zobrazit_dz')
    ),*/
    'dz-zpracovatel' => array(
      'desc'=>"Příchozí DZ (zpracovatel)",
      'contains' => array('all_read')
      //    'contains' => array('condition_update_dz')
    ),
    'dz-odbor' => array(
      'desc'=>"Příchozí DZ (odbor)",
      'contains' => array('all_read')
     //   'contains' => array('condition_update_dz')
    ),
    'dz-soucast' => array(
      'desc'=>"Příchozí DZ (soucast)",
      'contains' => array('all_read')
//      'contains' => array('condition_update_dz')
    ),
    'dz-uk' => array(
      'desc'=>"Příchozí DZ (UK)",
      'contains' => array('all_read')
//      'contains' => array('condition_update_dz')
      
    ),
    
    
    
    'admin-typspis' => array(
      'desc'=>"Právo pro administraci typového spisu",
      'contains' => array('all_read')
    ),
    
    
    
  		
    'muze-kopii-podcislo' => array(
      'desc'=>"Právo pro vkládání kopie s novým podčíslem SA",
      'contains' => array('all_read')
    ),

    'muze-razitko' => array(
      'desc'=>"Právo pro vkládání časového razítka",
      'contains' => array('all_read')
    ),

    'hromadna-editace' => array(
      'desc'=>"Právo pro hromadnou editaci",
      'contains' => array('all_read')
    ),

    'admin-typspis' => array(
      'desc'=>"Právo pro administraci typového spisu",
      'contains' => array('all_read')
    ),

//     'pristup-k-ZR' => array(
//       'desc'=>"MoĹžnost pracovat s ISZR",
//       'contains' => array('pristup_k_ZR')
//     )



    'podatelna' => array(
      'desc'=>"SKUPINA-Přístup k editaci všech dokumentů jako podatelna.",
      'contains' => array('export','pristup','all_read','all_insert','cteni_vse_pracoviste','editace_vse_pracoviste','vloz_prichozi','vloz_odchozi','zmena-spisoveho-uzlu','edit-datum-prijeti','edit-datum-vypraveni','condition_update_dokument','condition_delete_dokument','storno_vse_pracoviste')
//      'contains' => array('export','pristup','all_read','all_insert','cteni_admin','editace_admin','vloz_prichozi','vloz_odchozi','zmena-spisoveho-uzlu','edit-datum-prijeti','edit-datum-vypraveni','condition_update_dokument','condition_delete_dokument','storno_admin')
    ),
    'podatelna-odbor' => array(
      'desc'=>"SKUPINA-Přístup k editaci všech dokumentů jako podatelna spisového uzlu.",
//      'contains' => array('export','pristup','all_read','all_insert','cteni_uzel','editace_uzel','vloz_prichozi','vloz_odchozi','zmena-spisoveho-uzlu','edit-datum-prijeti','edit-datum-vypraveni','condition_update_dokument','condition_delete_dokument','storno_uzel')
      'contains' => array('export','pristup','all_read','all_insert','cteni_uzel','editace_uzel','vloz_prichozi','vloz_odchozi','zmena-spisoveho-uzlu','edit-datum-prijeti','edit-datum-vypraveni','condition_update_dokument','storno_uzel')
    ),

    'vedouci-odbor' => array(
      'desc'=>"SKUPINA-Přístup k editaci všech dokumentů jako vedoucí spisového uzlu.",
//      'contains' => array('export','pristup','all_read','all_insert','cteni_uzel','editace_uzel','vloz_odchozi','zmena-spisoveho-uzlu','condition_update_dokument','condition_delete_dokument')
      'contains' => array('export','pristup','all_read','all_insert','cteni_uzel','editace_uzel','vloz_odchozi','zmena-spisoveho-uzlu','condition_update_dokument','condition_delete_ostatni')
    ),
    'zpracovatel' => array(
      'desc'=>"SKUPINA-Přístup k editaci všech dokumentů jako zpracovatel (referent).",
//      'contains' => array('export','pristup','all_read','all_insert','cteni_zpracovatel','editace_zpracovatel','vloz_odchozi','condition_update_dokument','condition_delete_dokument')
      'contains' => array('export','pristup','all_read','all_insert','cteni_zpracovatel','editace_zpracovatel','vloz_odchozi','condition_update_dokument','condition_delete_ostatni')
    ),
    'omezeni-zpracovatele' => array(
      'desc'=>"SKUPINA-Omezení pouze na své nebo nepřiřazené dokumenty.",
//      'contains' => array('export','pristup','all_read','all_insert','cteni_zpracovatel','editace_zpracovatel','vloz_odchozi','condition_update_dokument','condition_delete_dokument')
      'contains' => array('export','pristup','all_read','all_insert','cteni_zpracovatel','editace_zpracovatel','vloz_odchozi','condition_update_dokument','condition_delete_ostatni')
    ),
    'spravce' => array(
      'desc'=>"SKUPINA-<b>Správce aplikace</b>",
      'contains' => array('export','pristup','all_read','all_insert','condition_update_dokument','condition_delete_dokument','cteni_admin','editace_admin','edit-datum-vypraveni','vloz_prichozi','vloz_odchozi','zmena-spisoveho-uzlu','edit-datum-prijeti','storno_admin','admin-typspis', 'hromadna-editace','zmena-pracoviste','condition_delete_ostatni','muze-kopii-podcislo'),
//      'conditions' => array(),
    ),
    'lokalni-spravce' => array(
      'desc'=>"SKUPINA-<b>Správce aplikace za pracoviště</b>",
      'contains' => array('export','pristup','all_read','all_insert','condition_update_dokument','condition_delete_dokument','cteni_vse_pracoviste','editace_vse_pracoviste','edit-datum-vypraveni','vloz_prichozi','vloz_odchozi','zmena-spisoveho-uzlu','edit-datum-prijeti','storno_vse_pracoviste','admin-typspis', 'hromadna-editace','condition_delete_ostatni'),
//      'conditions' => array(),
    ),
  )
);

$PROPERTIES_ACCESS['POSTA_DOKUMENTACE'] = array(
		'desc'=>'Dokumentace - modul pro správu více dokumentací',
		'rights' => array(
				"all_read"         => array('desc'=>"číst všechny záznamy", 'ceu_invisible'=>true),
				"all_insert"       => array('desc'=>"vkládat nové záznamy", 'ceu_invisible'=>true),
				'all_update'       => array('desc'=>'upravovat záznamy', 'ceu_invisible'=>true),
				'all_delete'       => array('desc'=>'mazat záznamy', 'ceu_invisible'=>true),


		),
		'rightgroups' => array(
				'ctenar' => array(
						'desc'=>'čtení a stažení dokumentací',
						'contains' => array('all_read')
				),
				'spravce' => array(
						'desc'=>"Správce dokumentací vše",
						'contains' => array('all_read','all_insert','all_update','all_delete')
				),
				'lokalni-spravce' => array(
						'desc'=>"Správce dokumentací za pracoviště",
						'contains' => array('all_read','all_insert','all_update','all_delete')
				),
		)
);

$PROPERTIES_ACCESS['POSTA_CISELNIKY'] = array(
  'desc'=>'správa číselníků, obálek a šablon',
  'rights' => array(
    "all_read"         => array('desc'=>"číst všechny záznamy", 'ceu_invisible'=>false),
    "all_insert"       => array('desc'=>"vkládat nové záznamy", 'ceu_invisible'=>false),
    'all_update'       => array('desc'=>'upravovat záznamy', 'ceu_invisible'=>false),
    'all_delete'       => array('desc'=>'mazat záznamy', 'ceu_invisible'=>true),
    "condition_delete_podminka" => array('desc'=>"stornovat vytvořené záznamy, které ještě nejsou přiděleny",
      'conditions'=>array(
      'CIS_POSTA_AGENDA'=>array('condition'=>' AND not exists (select * from cis_posta_typ where cis_posta_typ.id_agendy=cis_posta_agenda.id) '),        
      'CIS_POSTA_TYP'=>array('condition'=>' AND not exists (select * from posta where posta.typ_posty=cis_posta_typ.id) '),
      'POSTA_CIS_SPISOVNA'=>array('condition'=>'  AND not exists (select * from posta_spisovna where posta_spisovna.spisovna_id=posta_cis_spisovna.id) '),
      'POSTA_CIS_VYRIZENO'=>array('condition'=>'  AND not exists (select * from posta where posta.vyrizeno=posta_cis_vyrizeno.nazev)'),
      'POSTA_CIS_SKARTACE_MAIN'=>array('condition'=>' AND 1=1 '),
      'POSTA_CIS_SKARTACE'=>array('condition'=>'  AND not exists (select * from posta where posta.skartace=cis_posta_skartace.id)'),
      'CIS_POSTA_ODBORY'=>array('condition'=>'  AND not exists (select * from posta where posta.odbor=cis_posta_odbory.id) '),
      'POSTA_CIS_OSLOVENI'=>array('condition'=>'  AND not exists (select * from posta where cast(posta.odesl_osloveni as integer)=posta_cis_osloveni.id) '),
      'POSTA_SPISOVNA_CIS_LOKACE'=>array('condition'=>'  AND not exists (select * from posta_spisovna where posta_spisovna.lokace_id=POSTA_SPISOVNA_CIS_LOKACE.id)'),
       '*'=>array('condition'=>''),
      ),
    'ceu_invisible'=>false,
    ),


  ),  
  'rightgroups' => array(
    'access_all' => array(
      'desc'=>"Plný přístup k číselníkům",
      'contains' => array('all_read','all_insert','all_update','condition_delete_podminka')
    ),
			'lokalni-spravce' => array(
					'desc'=>"Správce lokálních číselníků za pracoviště",
      'contains' => array('all_read','all_insert','all_update','condition_delete_podminka')
			),
    'spravce' => array(
      'desc'=>"Správce číselníků",
      'contains' => array('all_read','all_insert','all_update','condition_delete_podminka')
    ),
    'spravce-odbor-sablony' => array(
      'desc'=>"Správce šablon",
      'contains' => array('all_read','all_insert','all_update','condition_delete_podminka')
    ),
    'spravce-obalky' => array(
      'desc'=>"Správce obálek",
      'contains' => array('all_read','all_insert','all_update','condition_delete_podminka')
    ),
  )
); 

$PROPERTIES_ACCESS['SKARTACNI_KNIHA'] = array(
  'desc'=>'Spisová a skartační kniha',
  'rights' => array(
    "all_read"         => array('desc'=>"číst všechny záznamy", 'ceu_invisible'=>true),
    "all_insert"       => array('desc'=>"vkládat nové záznamy", 'ceu_invisible'=>true),
    'all_update'       => array('desc'=>'upravovat záznamy', 'ceu_invisible'=>true),
    'all_delete'       => array('desc'=>'mazat záznamy', 'ceu_invisible'=>true),
    'export'       => array('desc'=>'exportovat záznamy', 'ceu_invisible'=>false),

    "condition_delete_dokument" => array('desc'=>"stornovat vytvořené dokumenty",
      'conditions' => array(
        'SKARTACNI_KNIHA' => array('condition'=>' AND registratura like \'-1\' '),
      ),
    ),
  ),
  'rightgroups' => array(
    'pristup' => array(
      'desc' => "Povolí přístup do SSK",
      'contains' => array('all_read')
    ),
  		
  	'access_all' => array(
      'desc'=>"Plný přístup k aplikaci",
      'contains' => array('pristup','all_read','all_insert','all_update','condition_delete_dokument','export')
    ),
    'zpracovatel' => array(
      'desc'=>"Zpracovatel může číst ve skartační knize",
      'contains' => array('pristup','all_read','export')
    ),

  	'spisovna' => array(
      'desc'=>"Přístup k ukládání do spisové a skartační knihy do všech spisoven",
      'contains' => array('pristup','all_read','all_insert','all_update','condition_delete_dokument','export')
    ),

  	'spisovna-odbor' => array(
      'desc'=>"Přístup k ukládání do spisové a skartační knihy, ale pouze do své spisovny",
      'contains' => array('pristup','all_read','all_insert','all_update','condition_delete_dokument','export')
    ),
  )
);

$PROPERTIES_ACCESS['POSTA_SPISOVNA_ZAPUJCKY'] = array(
  'desc'=>'Výpujční kniha',
  'rights' => array(
    "all_read"         => array('desc'=>"číst všechny záznamy", 'ceu_invisible'=>true),
    "all_insert"       => array('desc'=>"vkládat nové záznamy", 'ceu_invisible'=>true),
    'all_update'       => array('desc'=>'upravovat záznamy', 'ceu_invisible'=>true),
    'all_delete'       => array('desc'=>'mazat záznamy', 'ceu_invisible'=>true),

  ),
  'rightgroups' => array(
    'pristup' => array(
      'desc' => "Povolí přístup do SSK",
      'contains' => array('all_read')
    ),
  		
  	'access_all' => array(
      'desc'=>"Zakládání výpujček",
      'contains' => array('all_read','all_insert','all_update','all_delete')
    ),
  )
);

$PROPERTIES_ACCESS['POSTA_EPODATELNA'] = array(
		'desc'=>'Modul ePodatelna',
		'rights' => array(
				"all_read"         => array('desc'=>"číst všechny záznamy", 'ceu_invisible'=>true),
				"all_insert"       => array('desc'=>"vkládat nové záznamy", 'ceu_invisible'=>true),
				'all_update'       => array('desc'=>'upravovat záznamy', 'ceu_invisible'=>true),
				'all_delete'       => array('desc'=>'mazat záznamy', 'ceu_invisible'=>true),


		),
		'rightgroups' => array(
				'access_all' => array(
						'desc'=>"Plný přístup k aplikaci",
						'contains' => array('all_read','all_insert','all_update','all_delete')
				),
		)
);


$PROPERTIES_ACCESS['POSTA_DS'] = array(
		'desc'=>'Modul datová schránka',
		'rights' => array(
				"all_read"         => array('desc'=>"číst všechny záznamy", 'ceu_invisible'=>true),
				"all_insert"       => array('desc'=>"vkládat nové záznamy", 'ceu_invisible'=>true),
				'all_update'       => array('desc'=>'upravovat záznamy', 'ceu_invisible'=>true),
				'all_delete'       => array('desc'=>'mazat záznamy', 'ceu_invisible'=>true),


		),
		'rightgroups' => array(
				'access_all' => array(
						'desc'=>"Plný přístup k aplikaci",
						'contains' => array('all_read','all_insert','all_update','all_delete')
				),
				'cist_prichozi_DZ' => array(
						'desc'=>'čtení příchozích datových zpráv',
						'contains' => array('all_read')
				),
		)
);



$PROPERTIES_ACCESS['POSTA_KONEKTOR'] = array(
  'desc'=>'Konektory na EED',
  'rights' => array(
    "all_read"         => array('desc'=>"přístup na konektory", 'ceu_invisible'=>false),
    "all_insert"         => array('desc'=>"přístup na konektory", 'ceu_invisible'=>false),
    "all_update"         => array('desc'=>"přístup na konektory", 'ceu_invisible'=>false),
    "all_delete"         => array('desc'=>"přístup na konektory", 'ceu_invisible'=>false),
  ),
);

$PROPERTIES_ACCESS['POSTA_INTERFACE_BP'] = array(
  'desc' => 'Modul Best-Practices rozhraní',
  'rights' => array(
    'all_read'       => array('desc' => $GLOBALS['RESOURCE_STRING']['all_read'], 'ceu_invisible'  =>  true),
    'all_insert'     => array('desc' => $GLOBALS['RESOURCE_STRING']['all_insert'], 'ceu_invisible'  =>  true),
    'all_update'     => array('desc' => $GLOBALS['RESOURCE_STRING']['all_update'], 'ceu_invisible'  =>  true),
    'all_delete'     => array('desc' => $GLOBALS['RESOURCE_STRING']['all_delete'], 'ceu_invisible'  =>  true),
  ),
  'rightgroups' => array(
    'spravce' => array(
      'desc' => 'přístup pro nastavení rozhraní',
      'contains' => array('all_read','all_insert','all_update','all_delete')
    ),
  )
);


$spravce = HasRole('spravce')||HasRole('super_spravce');
if (!$spravce) {
  foreach ($PROPERTIES_ACCESS as $key => $value) {
    unset($PROPERTIES_ACCESS[$key]['rightgroups']['spravce']);    
    unset($PROPERTIES_ACCESS[$key]['rightgroups']['dz-uk']);
  }
}


if (strpos($_SERVER['SCRIPT_NAME'], 'posta/ug_file.php') && $GLOBALS['RECORD_ID']>1) {
  $q=new DB_POSTA;
  $sql='select * from posta where id='.$GLOBALS['RECORD_ID'];
  $q->query($sql); $q->Next_Record(); $data=$q->Record;
  $file_read_only = false;

  if ($GLOBALS['CONFIG_POSTA']['PLUGINS']['schvalovani']['enabled']) {
    include_once(FileUp2('plugins/schvalovani/.admin/schvalovani.inc'));
    if (SchvalenoKladne($GLOBALS['RECORD_ID'])) {
      $file_read_only = true;
    }
  }
 //pokud jde o prichozidokument prijaty elektronicky, pak zamezime moznosti smazani dokumentu
  if ($data['ODESLANA_POSTA']=='f' && $data['ZPUSOB_PODANI']=='3') $file_read_only=true;
 //pokud jde o prichozidokument prijaty elektronicky, pak zamezime moznosti smazani dokumentu
  if ($data['ODESLANA_POSTA']=='f' && $data['TYP_DOKUMENTU']=='D') $file_read_only=true;

  if (!$file_read_only) {
    //pokud jde o prichozi dokument, zamezime jeho editaci, pokud na nej nemam prava
    include_once(FileUp2('.admin/has_access.inc'));
    if (!MaPristupKDokumentu_old($GLOBALS['RECORD_ID'])) {
      $file_read_only = true;
    }
  }

  //pokud jde o odchozi dokument a je uz odeslan, pak zamezime moznosti smazani dokumentu
  if ($data['ODESLANA_POSTA']=='t' && $data['DATUM_VYPRAVENI']<>'') $file_read_only=true;
  //pokud je vyrizen spis
  if ($data['SPIS_VYRIZEN']<>'') $file_read_only=true;
  //pokud jsou nejak vyrizene dokumenty
  if ($data['STATUS']<2) $file_read_only=true;
  //prichozi vnitrni posta - nejde menit
  if ($data['ODESLANA_POSTA']=='f' && $data['ODES_TYP']=='X') $file_read_only=true;
//   //prichozi vnitrni posta - nejde menit
//   if ($data['ODESLANA_POSTA']=='f' && $data['ODES_TYP']=='Z') $file_read_only=true;

  if ($GLOBALS['NEMA_PRISTUP_DO_UPLOADU']) $file_read_only = true;
  if ($file_read_only) {
    $PROPERTIES_ACCESS['POSTA']['rights']['all_read']=true;
    $PROPERTIES_ACCESS['POSTA']['rights']['all_insert']=false;
    $PROPERTIES_ACCESS['POSTA']['rights']['all_update']=false;
    $PROPERTIES_ACCESS['POSTA']['rights']['all_delete']=false;
    $PROPERTIES_ACCESS['POSTA']['rights']['condition_update_STATUS']=false;
    $PROPERTIES_ACCESS['POSTA']['rights']['condition_delete_STATUS']=false;
     foreach($PROPERTIES_ACCESS['POSTA']['rightgroups'] as $key => $val)
        $PROPERTIES_ACCESS['POSTA']['rightgroups'][$key]['contains'] = array('all_read','cteni_admin');
    //print_r($PROPERTIES_ACCESS['POSTA']['rightgroups']);
  }
}

