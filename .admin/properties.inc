<?php
 include_once(FileUp2(".admin/config.inc"));
 include_once(FileUp2(".admin/oth_funkce_2D.inc")); //prepsat do trid a smazat
 require_once(FileUp2(".admin/db/db_posta.inc"));

if ($GLOBALS['CONFIG']['UPLOAD_ELO'])
  include_once(FileUp2("plugins/elo/aktualizace.php"));

$PROPERTIES = array(
  'AGENDA_NAME' => 'Elektronická evidence dokumentů',
  'AGENDA_TABLE' => 'posta',
  'AGENDA_ID' => 'ID',
  'AGENDA_IDENT' => 'POSTA',
  'AGENDA_DESCRIPTION' => '',

//  'AGENDA_VERSION' => '5.2',
//  'AGENDA_ROADMAP_IDENT' => 'posta',

  'SECURITY_REGISTRATION' => true,
  'DB_NAME' => 'DB_POSTA',
  
  'DEFAULT_LANG'=>'cz_utf-8',
  
  //'BROW_SELECT'=>'SELECT k.*, o.sloupec1, o.sloupec2 FROM tabulka1 k '
  //             . 'LEFT JOIN tabulka2 o ON (k.sloupec1 = o.sloupec3)',
  "BROW_SELECT" => "SELECT p.* from posta p

      ",
/*      LEFT JOIN security_user u ON p.referent=u.id
      LEFT JOIN cis_posta_odbory o ON p.odbor=o.id
      LEFT JOIN security_group g ON g.id=o.id_odbor
*/
  "BROW_FIELD_PREFIX" => "p.",
//  "BROW_ORDER_BY"=>"ID DESC, ROK DESC, EV_CISLO DESC",
  "BROW_ORDER_BY"=>"ID DESC",
  //'BROW_FIELD_PREFIX'=>'k.',

  'EDIT_LEFT' => 100,
  'EDIT_TOP' => 10,
  'EDIT_HEIGHT' => 300,
  'EDIT_WIDTH' => 500,

  'DELETE_HEIGHT' => 260,
  'DELETE_WIDTH' => 600,
  'DELETE_LEFT' => 0,
  'DELETE_TOP' => 0,

  'HISTORY_HEIGHT' => 400,
  'HISTORY_WIDTH' => 920,

  'UPLOAD_HEIGHT' => 800,
  'UPLOAD_WIDTH' => 920,

  'INSERT_REFRESH' => true,

  //ARES CONFIG
	"CONFIG_ARES"=>array(
    "PROXY_HOSTNAME"=>"", //pouzit proxy server
    "PROXY_HOSTNAME_PORT"=>"",
    "FRM_NAME"=>"frm_edit", //nazev formu, default je frm_edit
    "TEXT_PRED"=>"TEXT_ARES", //ukecany skript, vraci pres innerhtml text, co dela...
    "OBCHODNI_NAZEV"=>"ODESL_PRIJMENI_FIRMA",  //nazvy poli, ktere se budou vyplnovat.Pokud nechcete vyplnovat nektere udaje, nechte hodnotu prazdnou.
    "OBCHODNI_NAZEV2"=>"ODESL_PRIJMENI",  //nazvy poli, ktere se budou vyplnovat.Pokud nechcete vyplnovat nektere udaje, nechte hodnotu prazdnou.
    "ICO"=>"ODESL_ICO",
    "ULICE"=>"ODESL_ULICE",
    "CP"=>"ODESL_CP",
    "COR_CISLO"=>"ODESL_COR",
    "COR_PISMENO"=>"",
    "DS"=>"ODESL_DATSCHRANKA",
    "MESTO"=>"ODESL_POSTA",
    "PSC"=>"ODESL_PSC",
    "ADRESA_KOD"=>"ODESL_ADRKOD",
    "OBEC_KOD"=>"",
    "REJSTRIK"=>"", //z ktereho rejstriku jsou data
    "ENCODING" => "ISO-8859-2",
  ),

);

$PROPERTIES['UPLOAD_CONFIG']=array(
  'MODULES' => array(
    'table' => array(
      'DIR'=>'posta',
      'SUBDIRS'=>array(
        'ROK'=>array('min_dir_cif'=>4),
        'ID'=>array(),
      ),
      //'PREVIEW_SIZE_RATIO' => array(120),
      //'ONLY_FILE_TYPES'    => array('image'),
    ),
  ),
  'USE_ANONYM_ACCESS'=>true,
  'USE_PRIVATE_ACCESS'=>false,
);


//projdeme, jestli neprislo nejake setrideni sloupcu, kdy musime opravit select
foreach($_GET as $key => $val) {

  if ($val == 'status_text' || $val == 'status_text desc')
    $PROPERTIES['BROW_SELECT'] = str_replace('p.*', 'p.*,posta_sort_status(status) as status_text', $PROPERTIES['BROW_SELECT']);

  if ($val == 'lname asc,fname asc' || $val == 'lname desc,fname desc')
    $PROPERTIES['BROW_SELECT'] = str_replace('p.* from posta p', 'p.* from posta p left join security_user u ON p.referent=u.id', $PROPERTIES['BROW_SELECT']);

  if ($val == 'o.zkratka asc' || $val == 'o.zkratka desc')
    $PROPERTIES['BROW_SELECT'] = str_replace('p.* from posta p', 'p.* from posta p left join cis_posta_odbory o ON p.odbor=o.id', $PROPERTIES['BROW_SELECT']);

  if ($val == 'o.zkratka asc,lname asc,fname asc' || $val == 'o.zkratka desc,lname desc,fname desc')
    $PROPERTIES['BROW_SELECT'] = str_replace('p.* from posta p', 'p.* from posta p left join security_user u ON p.referent=u.id left join cis_posta_odbory o ON p.odbor=o.id', $PROPERTIES['BROW_SELECT']);
  if (!is_array($val))
    if ((strpos($val,'vs.') !== false)&&(strpos($PROPERTIES['BROW_SELECT'],'left join cis_posta_skartace')===false))
    $PROPERTIES['BROW_SELECT'] = str_replace('p.* from posta p', 'p.* from posta p left join cis_posta_skartace vs ON p.skartace=vs.id', $PROPERTIES['BROW_SELECT']);

}
