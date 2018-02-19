<?php
$agendaPath = array(


//Evidence pisemnosti
"POSTA"=>"ost/posta",
"POSTA_CISELNIKY" =>"ost/posta/cis",
"CIS_POSTA_AGENDA" =>"ost/posta/cis/agenda",
"CIS_POSTA_TYP" =>"ost/posta/cis/typ_posty",
"POSTA_PLUGINS"=>"ost/posta/plugins",
// "POSTA_DENIK"=>"ost/posta",
"POSTA_OBEH"=>"ost/posta/services/spisovka/obeh",
"POSTA_SPIS"=>"ost/posta/services/spisovka/spis",
"POSTA_SPIS_SPISOVNA"=>"ost/posta/services/spisovka/spis_spisovna",
"POSTA_C_JEDNACI"=>"ost/posta/services/spisovka/c_jednaci",
"POSTA_C_JEDNACI2"=>"ost/posta/services/spisovka/c_jednaci2",
"POSTA_SEZNAMY_FIRMY"=>"ost/posta/services/spisovka/firmy",
"POSTA_PRIJEMCI"=>"ost/posta/services/spisovka/prijemci",
"POSTA_ADRESATI"=>"ost/posta/services/spisovka/adresati",
"POSTA_UIRADR"=>"ost/posta/services/spisovka/adresy",
"POSTA_PRIDANI_SPISU"=>"ost/posta/services/spisovka/dalsi_spis",
"POSTA_KRIZOVY_SPIS"=>"ost/posta/services/spisovka/kriz_spis",
"POSTA_XERTEC"=>"ost/posta/plugins/xertec",
"POSTA_NEOPOST"=>"ost/posta/plugins/neopost",
"POSTA_EVROFIN"=>"ost/posta/plugins/evrofin",
"POSTA_CPOST"=>"ost/posta/plugins/ceskaposta",
"POSTA_DORUCOVATEL"=>"ost/posta/plugins/dorucovatel",
"POSTA_DOKUMENTACE"=>"ost/posta/plugins/dokumentace",
"POSTA_WORKFLOW" => "ost/posta/plugins/workflow",
"POSTA_KONFIGURACE"=>"ost/posta/services/nastaveni/konfigurace",
"POSTA_KONFIGURACE_ODBORY"=>"ost/posta/services/nastaveni/konfigurace/odbory",

"POSTA_OBALKY"=>"ost/posta/services/nastaveni/obalky",
"POSTA_OBALKY_OBJEKTY"=>"ost/posta/services/nastaveni/obalky/objekty",
"POSTA_SABLONY"=>"ost/posta/services/nastaveni/sablony",
"POSTA_NASTAVENI_ADRESATI"=>"ost/posta/services/nastaveni/adresati",
"POSTA_NASTAVENI_VNITRNIADR"=>"ost/posta/services/nastaveni/vnitrniadr",
"POSTA_SPISPREHLED_ZAZNAMY"=>"ost/posta/services/spisovka/spisprehled",
"STARA_POSTA"=>"ost/posta/services/spisovka/historie",
"POSTA_REZERVACE"=>"ost/posta/services/spisovka/rezervace",
"POSTA_ISRZP_PRACOVNICI"=>"ost/posta/interface/rzp/referent",
"POSTA_OKNOUZE_PRACOVNICI"=>"ost/posta/interface/oknouze/referent",
"PREVOD_STARA_POSTA"=>"ost/posta/services/spisovka/historie_prevod",
"POSTA_CIS_SKARTACE"=>"ost/posta/cis/skartace",
"POSTA_TRANSAKCE"=>"ost/posta/services/nastaveni/transakce",
"POSTA_UNISPIS"=>"ost/posta/services/nastaveni/unispis",
"POSTA_USER_SETTINGS"=>"ost/posta/services/spisovka/user_set",
"POSTA_PRISTUPY" => "ost/posta/services/spisovka/pristupy",
//interface pro EED
"POSTA_INTERFACE_TWIST"=>"ost/posta/interface/twist",
//interface pro EED
"POSTA_EL_PODPIS"=>"ost/posta/interface/podepsani602",
//Skartacni kniha
"SKARTACNI_KNIHA"=>"ost/posta/services/skartace/skartacni_kniha",
"POSTA_SPISOVNA_BOXY"=>"ost/posta/services/skartace/boxy/seznam",
"POSTA_SPISOVNA_BOXY_VLOZENI"=>"ost/posta/services/skartace/boxy/vlozeni",
"POSTA_SPISOVNA_ZAPUJCKY"=>"ost/posta/services/skartace/zapujcky",
// 1click
//  "POSTA_INTERFACE_ONE_CLICK"=>"ost/posta/interface/one_click",
// Statisticke vystupy z evidence pisemnosti
"POSTA_STAT"=>"ost/posta/services/statistika/statistika",
//Epodatelna
"POSTA_EPODATELNA"=>"ost/posta/plugins/epodatelna",
//Datova schranka
"POSTA_DS"=>"ost/posta/plugins/DS",
//Hromadny imoport
"POSTA_HROMADNY_IMPORT" => "ost/posta/plugins/hromadny_import",
//Filtry pro prevod datovych zprav do EED
"POSTA_DS_FILTRY"=>"ost/posta/plugins/DS/filtry",
//Spravce certifikátů
"POSTA_CERTIFIKATY"=>"ost/posta/services/nastaveni/certifikaty",
"POSTA_CIS_TYPOVY_SPIS" =>"ost/posta/services/nastaveni/typovy_spis",
"POSTA_CIS_TYPOVY_SPIS_SOUCAST" =>"ost/posta/services/nastaveni/typovy_spis/soucast",

"POSTA_TYP_SPIS" =>"ost/posta/services/spisovka/typovy_spis_soucasti",
"POSTA_TYP_SPIS_SOUCASTIADILY" =>"ost/posta/services/spisovka/typovy_spis",
"POSTA_TYP_SPIS_SOUCASTI" =>"ost/posta/services/spisovka/typovy_spis_soucasti",

'POSTA_PLUGINS_UK_STUDENT' => 'ost/posta/plugins/uk/typove_spisy_student',
'POSTA_PLUGINS_UK_PRAC' => 'ost/posta/plugins/uk/typove_spisy_pracovnik',
'POSTA_PLUGINS_DR_APP' => 'ost/posta/plugins/DR/app',

'POSTA_PLUGINS_RADAR' => 'ost/posta/plugins/radar',

'POSTA_INTERFACE_BP' => 'ost/posta/interface/BP',
'POSTA_INTERFACE_BP_APP' => 'ost/posta/interface/BP/app',
  
);

$SERVER_CONFIG['UPLOAD_CONFIG'] = array(
  'MODULES' => array(
    'table'=> array(
      'TABLE'=>'files',
      'DB_NAME'=>'DB_DEFAULT',
      'PREVIEW_SIZE_RATIO'=>array(80,200), // v pixlech velikost stran ctverce
      'UPLOAD_DIR' => 'data/upload',
      'ONLY_FILE_TYPES' => array('msg','xml','pdf','png','tiff','tif','mpg','mpg2','avi','mp3','wav','pcm','xnkm','zfo','fo','htm','html','odt','ods','odp','txt','rtf','doc','docx','gif','xls','xlsx','ppt','pptx','jpg','jpeg','png','tif','tiff',
        'mpg','mpeg','mp2','mp3','isdoc','isdocx','edi','dwg','shp','dbf','shx','prj','qix','sbn','sbx','dgn','gml','gfs','xsd','eml','csv'),
      'CONVERT_TYPES' => array('odt','ods','odp','txt','doc','docx','xls','xlsx','ppt','pptx','pdf','htm','html','eml'),
      /*  'STORAGE' => array(
       'TYPE' => 'filesystem',
       'Print2PDF_SERVICE' => true, //prevod do pdf
       ),*/
      
      'STORAGE'=> array(
        
        'TYPE' => 'cul',
        'Print2PDF_SERVICE' => true, //prevod do pdf
        'CUL_Service' => array(
          'wsdl'           => (($GLOBALS['SERVER_ADDR'] == '192.168.110.222') ? 'https://cul-demo.ders.cz/CULWS/services/DigitalniDokumentService?wsdl' : 'https://libera.is.cuni.cz/CULWS/services/DigitalniDokumentService?wsdl'),
          'rest'           => (($GLOBALS['SERVER_ADDR'] == '192.168.110.222') ? 'https://cul-demo.ders.cz/CULWS/services/rest/v1' : 'https://libera.is.cuni.cz/CULWS/services/rest/v1'),
          'login'  => 'ess',
          'passwd' => 'S59QXSI2',
          'onlineEdit' => array( //ktere metatype souboru lze online editovat
            'application/msword',
            'application/vnd.openxmlformats-officedocument.wordprocessingml.document',
            'application/vnd.openxmlformats-officedocument.wordprocessingml.template',
            'application/vnd.ms-word.document.macroEnabled.12',
            'application/vnd.ms-word.template.macroEnabled.12',
            'application/vnd.ms-excel',
            'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet',
            'application/vnd.openxmlformats-officedocument.spreadsheetml.template',
            'application/vnd.ms-excel.sheet.macroEnabled.12',
            'application/vnd.ms-excel.template.macroEnabled.12',
            'application/vnd.ms-excel.addin.macroEnabled.12',
            'application/vnd.ms-excel.sheet.binary.macroEnabled.12',
            'application/vnd.ms-excel.addin.macroEnabled.12',
            'application/vnd.ms-powerpoint',
            'application/vnd.openxmlformats-officedocument.presentationml.presentation',
            'application/vnd.openxmlformats-officedocument.presentationml.template',
            'application/vnd.openxmlformats-officedocument.presentationml.slideshow',
            'application/vnd.ms-powerpoint.addin.macroEnabled.12',
            'application/vnd.ms-powerpoint.presentation.macroEnabled.12',
            'application/vnd.ms-powerpoint.template.macroEnabled.12',
            'application/vnd.ms-powerpoint.slideshow.macroEnabled.12',
          ),
        ),
      ),
      
    ),
  ),
  'TMP_UNZIP_DIR'=>'/tmp',
  'USE_ANONYM_ACCESS'=>false,
  'use_private_access'=>false,
  'MAX_FILE_SIZE_UPLOAD' => 20480848,
);

return $agendaPath;



