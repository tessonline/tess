<?php
require_once(FileUp2('.admin/config.inc'));
Include_once(FileUp2('.admin/table_func.inc'));
Include_once(FileUp2('.admin/table_funkce_denik.inc'));

/*seznam moznych formatu vystupu s nastavenim*/
$EXPORT_CONFIG['format'] = array(
  'csv'    => array('label'=>'Excel (CSV)', 'footer' => false),
//  'tabbed' => array('label'=>'Excel (Tabbed)', 'default'=>true ),
  'xml'    => array('label'=>'XML'),
  'pdf'    =>   array(
    'label'=>'PDF',
    'title'=>'Elektronická evidence dokumentů - export',
    'header'=>'<div>Tisk dne '.Date('d.m.Y H:i').'</div>',
    'footer'=>'',
  ),
  'xhtml'  => array(
    'label'=>'XHTML',
    'css' => FileUpURL('xhtml.css'),
    'title'=>'Elektronická evidence dokumentů - export',
    'header'=>'<div>Tisk dne '.Date('d.m.Y H:i').'</div>',
    'footer'=>'',
  ),
);
$EXPORT_CONFIG['charset'] = array(
    'utf-8' => array('label' => 'UTF-8', 'default' => false),
    'WINDOWS-1250' => array('label' => 'WINDOWS-1250', 'default' => true),
  );

$EXPORT_CONFIG['schema'][] = array(
  field => 'exportSmer(ID)',
  label => 'Směr',
);

$EXPORT_CONFIG['schema'][] = array(
//    field => ''<i><font size = 1>'...tableBarcode(ID)...'</font></i>'',
  field => 'tableBarcode(ID)',
  label => ' JID',
);


$EXPORT_CONFIG['schema'][] = array(
  field => 'exportFormatCJednaci(ID)',
  label => $GLOBALS['CONFIG']['CISLO_SPISU'] .', evidenční',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'exportFormatSpis(ID)',
  label => 'Spis',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'exportFormatSpis(ID, 1)',
  label => 'Název spisu',
);

$EXPORT_CONFIG['schema'][] = array(
  'field' => 'ShowTypPosty(TYP_POSTY)',
  label => $GLOBALS['CONFIG']['NAZEV_TYP_POSTY'],
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'DatumPrijeti(DATUM_PODATELNA_PRIJETI)',
  label => 'Datum přijetí',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'LHUTA',
  label => 'Lhůta',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'DatumPrijeti(DATUM_REFERENT_PRIJETI)',
  label => 'Datum přečtení',
);

// $EXPORT_CONFIG['schema'][] = array(
//   field => 'DatumVyrizeni(LHUTA_VYRIZENI)',
//   label => 'Datum vyřízení'
// );

$EXPORT_CONFIG['schema'][] = array(
  field => 'ShowOdesTyp(ODES_TYP)',
  label => 'Typ subjektu',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'UkazJmeno()',
  label => 'Odesílatel, Adresát',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_TITUL',
  label => 'Titul',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_JMENO',
  label => 'Jméno',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_PRIJMENI',
  label => 'Příjmení',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_DATNAR',
  label => 'Datum narození',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_ICO',
  label => 'IČ',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_ULICE',
  label => 'Ulice',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_CP',
  label => 'číslo popisné',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_COR',
  label => 'číslo orientační',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_PSC',
  label => 'PSČ',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_POSTA',
  label => 'Město',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_DATSCHRANKA',
  label => 'Datová schránka',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_REKOMANDO',
  label => 'Rekomando',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ODESL_POSTAODESL',
  label => 'Odesílací pošta',
  checked => 0
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'JEJICH_CJ',
  label => 'Jejich čj',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'JEJICH_CJ_DNE',
  label => 'ze dne',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'tableVec(ID)',
  label => 'Věc',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'TYP_DOKUMENTU',
  label => 'Typ dokumentu',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'tableSpisUzel(ID)',
  label => 'Odbor',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'exportZpracovatel(ID)',
  label => 'Zpracovatel',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'VYRIZENO',
  label => 'Způsob vyřízení',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'DatumPrijeti(DATUM_VYRIZENI)',
  label => 'Datum vyřízení',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'exportSpisovaZnacka(ID)',
  label => 'Spisový znak',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'ShowStatus(STATUS)',
  label => 'Stav',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'UlozenoVeSpisovne(ID)',
  label => 'Uloženo ve spisovně',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'spisForma(ID)',
  label => 'Uložení ve spisovně',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'KrizVazba(ID)',
  label => 'Křížová vazba',
);

$EXPORT_CONFIG['schema'][] = array(
  field => 'POZNAMKA',
  label => 'Poznámka',
);

