<?php
include_once(FileUp2('.admin/db/db_default.inc'));
include_once(FileUp2('.admin/db/db_posta.inc'));

// **********************************************************
// Nastavení základních hodnot pro czech point
// **********************************************************

$GLOBALS['CONFIG_POSTA_CP']=array(
  'ZALOZIT_SPIS' => true,
  'UZAVRIT_SPIS' => true,
  'DRUH_ZADOSTI' => array(
    '1' => array('TYP_DOC'=>'37', 'NAZEV'=>'Výpis z obchodního rejstříku'),
    '2' => array('TYP_DOC'=>'38', 'NAZEV'=>'Výpis z živnostenského rejstříku'),
    '3' => array('TYP_DOC'=>'60', 'NAZEV'=>'Výpis z katastru nemovitostí'),
    '4' => array('TYP_DOC'=>'59', 'NAZEV'=>'Výpis z rejsříku trestů'),
    '5' => array('TYP_DOC'=>'68', 'NAZEV'=>'Výpis z trestního rejstříku pro vnitřní potřebu rejstříku (podle
z. 124/2008'),
    '6' => array('TYP_DOC'=>'38', 'NAZEV'=>'Živnostenské podání FO'),
    '7' => array('TYP_DOC'=>'63', 'NAZEV'=>'Živnostenské podání PO'),
    '8' => array('TYP_DOC'=>'65', 'NAZEV'=>'Výpis bodového hodnocení řidičů z centrálního registru řidičů'),
    '9' => array('TYP_DOC'=>'66', 'NAZEV'=>'Výpis ze seznamu kvalifikovaných dodavatelů'),
    '10' => array('TYP_DOC'=>'67','NAZEV'=>'Registr účastníků provozu modulu autovraků ISOH'),
    '11' => array('TYP_DOC'=>'0', 'NAZEV'=>'Výpis z insolvenčního rejstříku'),
    '201' => array('TYP_DOC'=>'0', 'NAZEV'=>'Autorizovaná konverze z listinné do elektronické podoby dokumentu z moci úřední'),
    '202' => array('TYP_DOC'=>'0', 'NAZEV'=>'Autorizovaná konverze z elektronické do listinné podoby dokumentu z moci úřední'),
  ),
  'SKARTACE_ID' => 688, //0 - neprirazovat skartacni kod
  'LAST_USER_ID' => 12, //ID uzivatele, pod kterym budou zapsany zaznamy
);

$qq=new DB_POSTA;
$sql='select * from posta_czechpoint';
$qq->query($sql);
while ($qq->Next_Record()) {
  $login = $qq->Record['LOGIN'];
  $passwd = $qq->Record['PASSWD'];
  $user_id = $qq->Record['USER_ID'];
  $GLOBALS['CONFIG_POSTA_CP']['VALID_USERS'][$login]= array(
    'password'=>$passwd,
    'id'=>$user_id
  );
}
