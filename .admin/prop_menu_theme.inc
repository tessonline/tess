<?php

$dropdownListApp = array();
$dropdownListFunc = array();

$dropdownListApp[] = "POSTA";
//$dropdownListApp[] = "POSTA_DS";
//$dropdownListApp[] = "POSTA_EPODATELNA";
$dropdownListApp[] = "SKARTACNI_KNIHA";
$dropdownListApp[] = "POSTA_SPISOVNA_ZAPUJCKY";
$dropdownListApp[] = "POSTA_SPISOVNA_BOXY";
$dropdownListApp[] = "POSTA_TRANSAKCE";


if (HasRole('admin-typspis')) $dropdownListApp[] = "POSTA_CIS_TYPOVY_SPIS";
$dropdownListApp[] = "POSTA_INTERFACE_BP_APP";

$dropdownListFunc[] = array(
   'name' => 'Vlož příchozí ze souboru',
   'href' => GetAgendaPath('POSTA', false, true) . '/services/spisovka/vnitrni_ze_souboru/edit.php?insert',
);

$dropdownListFunc[] = array(
  'name' => 'Dokumentace',
  'href' => GetAgendaPath('POSTA', false, true) . '/doc/dokumentace_EED.pdf',
);

$dropdownListFunc[] = array(
  'name' => 'Vlastní nastavení',
  'href' => 'javascript:NewWindowAgenda(\''.GetAgendaPath('POSTA_USER_SETTINGS', false, true) . '/edit.php?edit\')',
);



if (Access(array("agenda"=>"POSTA_CISELNIKY"))) {
  if (HasRole('spravce')||HasRole('lokalni-spravce')||HasRole('spravce-obalky')) 
    $dropdownListApp[] = "POSTA_OBALKY";
  if (HasRole('spravce')||HasRole('lokalni-spravce')||HasRole('spravce-odbor-sablony'))
    $dropdownListApp[] = "POSTA_SABLONY";

}
Access(array("agenda"=>"POSTA"));
if (HasRole('spravce')) {
  $dropdownListApp[] = "POSTA_CERTIFIKATY";
}

if (HasRole('spravce') || HasRole('lokalni-spravce')) {
  $dropdownListFunc[] = array(
      'name' => 'Nastavení',
      'href' => 'services/nastaveni/menu.php'
       //'target' => '_top'
  );
}
If (HasRole('spravce')||HasRole('podatelna')) {

//     echo "<br/>";
    $dropdownListFunc[] = array(
      'name' => 'Vnitřní dokument',
      'href' => GetAgendaPath('POSTA', false, true) . '/brow_vnitrni.php'
    );

    If ($GLOBALS["CONFIG"]["TISK_RAZITKA"]) {
      $dropdownListFunc[] = array(
        'name' => 'Tisk podacích razítek',
        'href' => GetAgendaPath('POSTA', false, true) . '/services/barcode/razitko/edit.php?insert'
      );
    }

}

If (HasRole('spravce')||HasRole('podatelna')||HasRole('editace_admin')||HasRole('editace_uzel')) {
  $dropdownListFunc[] = array(
    'name' => 'Načtení doručenek pomocí ČK',
    'href' => GetAgendaPath('POSTA', false, true) . '/services/barcode/dorucenka/edit.php?insert&smer=2'
  );
}

If (HasRole('spravce')||HasRole('podatelna')||HasRole('editace_admin')||HasRole('editace_uzel')||HasRole('prevzit-z-podatelny')) {
    /*$dropdownListFunc[] = array(
      'name' => 'Načtení doručenek pomocí ČK',
      'href' => GetAgendaPath('POSTA', false, true) . '/services/barcode/dorucenka/edit.php?insert&smer=2'
    );*/

  If ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"]) {
    $dropdownListFunc[] = array(
      'name' => 'Převzetí dokumentů na odbor pomocí ČK',
      'href' => GetAgendaPath('POSTA', false, true) . '/services/barcode/prevzeti/edit.php?insert&smer=1'
    );
    $dropdownListFunc[] = array(
      'name' => 'Převzetí dokumentů na odbor pomocí seznamu',
      'href' => GetAgendaPath('POSTA', false, true) . '/services/barcode/prevzeti_old/edit.php?insert&smer=1'
    );    
  }
}

  if (HasRole('vypraveni-predani')) {
    $dropdownListFunc[] = array(
      'name' => 'Předání dokumentů na podatelnu pomocí ČK',
      'href' => GetAgendaPath('POSTA', false, true) . '/services/barcode/prevzeti/edit.php?insert&smer=2'
    );
    $dropdownListFunc[] = array(
      'name' => 'Předání dokumentů na podatelnu pomocí seznamu',
      'href' => GetAgendaPath('POSTA', false, true) . '/services/barcode/prevzeti_old/edit.php?insert&smer=2'
    );
  }



If (HasRole('spravce')||HasRole('podatelna')||HasRole('podatelna-odbor')) {
//    $odbor = VratOdbor();

    $dropdownListFunc[] = array(
      'name' => 'Předávací protokol příchozích dokumentů',
      'href' => GetAgendaPath('POSTA', false, true) . '/services/spisovka/protokoly/edit.php?insert&cacheid=&smer=prichozi&podatelna_id=' . $REFERENT . '&odbor=' . $odbor
    );

    If ($GLOBALS["CONFIG"]["PODATELNA_ODBOR_PROTOKOL"]) {
      $dropdownListFunc[] = array(
        'name' => 'Předávací protokol pro doručovatele',
        'href' => GetAgendaPath('POSTA_DORUCOVATEL', false, true) . '/brow.php?cacheid='
      );
    }

    $dropdownListFunc[] = array(
      'name' => 'Generování podacího deníku do PDF',
      'href' => GetAgendaPath('POSTA', false, true) . '/services/spisovka/protokoly/edit.php?insert&kniha=1&cacheid='
    );
}

$dropdownListFunc[] = array(
  'name' => 'Hromadný tisk obálek',
  'href' => GetAgendaPath('POSTA', false, true) . '/services/spisovka/obalky/edit.php?insert&cacheid=',
);

If (HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('vedouci-odd')||HasRole('podatelna')||HasRole('podatelna-odbor')) {
//    $odbor = VratOdbor();

    if (HasRole('vedouci-odbor')||HasRole('vedouci-odd') ) {
      $GLOBALS["ODBOR"]=$odbor;
    }
    else {
     //u posta-spravce a access_all
     $GLOBALS["ODBOR"]='';
   }

    $dropdownListFunc[] = array(
      'name' => 'Předávací protokol odchozích dokumentů',
      'href' => GetAgendaPath('POSTA', false, true) . '/services/spisovka/protokoly/edit.php?insert&cacheid=&smer=odchozi&podatelna_id=' . $REFERENT . '&odbor=' . $odbor
    );



}



reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/prop_menu_theme.inc');
		if (File_Exists($file)) include($file);
  }
}


if ($PROPERTIES['AGENDA_IDENT'] == 'POSTA') {

  // MENU_THEME
  $PROPERTIES['MENU_THEME'] = array(
    'applications' => array(
      'dropdownList' => $dropdownListApp
    ),
    'functions' => array(
      'caption' => 'nadpis',
      'icon' => '',
      'dropdownList' => $dropdownListFunc
    )
  );
}

else {
  // MENU_THEME
  $PROPERTIES['MENU_THEME'] = array(
    'applications' => array(
      'dropdownList' => $dropdownListApp
    ),
  );
}


