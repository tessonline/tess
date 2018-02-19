<?php

// SKRIPT RESI FULLTEXTOVE VYHLEDAVANI NAD TABULKOU POSTA_ADRESATI
// Dle obsahu promene $_GET['term'] vyhleda a vrati vysledky ve formatu JSON

require('tmapy_config.inc');
include_once(FileUp2('.admin/brow_.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
include_once(FileUp2('.admin/el/of_select_.inc'));
include_once(FileUp2('lib/json/json.inc'));

access();

if (!hasSubRole('read')) {
  die();
}

$searchText = prepareQuery(iconv('UTF-8', 'ISO-8859-2', $_GET['term']));
$adresati = array();

$dbConnector = new DB_POSTA;
$sql = 'SELECT ts_rank(tsv, q.q) AS rank, p.*
          FROM posta_adresati p, (SELECT to_tsquery(\'cs\', \'' . $searchText . '\') as q) q
          WHERE p.tsv @@ q.q
          ORDER BY rank DESC';
//echo $sql;
$dbConnector->query($sql);

while ($dbConnector->next_record()) {
  
  $adresat = array();
  $adresat['id'] = iconv('ISO-8859-2', 'UTF-8', $dbConnector->Record['ID']);
  $adresat['value'] = iconv('ISO-8859-2', 'UTF-8', $dbConnector->Record['ODESL_PRIJMENI']);
  $adresat['preview'] = iconv('ISO-8859-2', 'UTF-8', formatPreview($dbConnector->Record));
  
  $adresati[] = $adresat;
}

header('Content-Type: application/json; charset=UTF-8');

if (version_compare(PHP_VERSION, '5.2', '>=')) {
  $json = json_encode($adresati);
}
else {
  $jsonService = new Services_JSON();
  $json = $jsonService->encode($adresati);
}

echo $json;

/**
 * Funkce pripravi retezezec pro fulltextove vyhledavani:
 *  orizne bile znaky,
 *  mezi jednotliva slova vlozi ' & ' (AND shoda),
 *  za kazde slovo prida ':*' (vyhleda podretezec).
 * @param string $term Jednoduchy retezec zadany uzivatelem.
 * @return string Upraveny retezec urceny pro fulltextove vyhledavani. 
 */
function prepareQuery($term) {
  
  $count = 1;
  $term = trim($term);
  
  while ($count > 0) {
    $term = str_replace('  ', ' ', $term, $count);
  }
  
  $term = str_replace(' ', ':* & ', $term);
  $term .= $term ? ':*' : '';
  
  return $term;
}

/**
 * Funkce naformatuje hodnoty adresata.
 * @param array $record Pole s hodnotami o adresatovi.
 * @return string Zformatovany retezec adresata. 
 */
function formatPreview($record) {
  
  $preview = '';
  
  $preview .= $record['ODESL_TITUL']        ? $record['ODESL_TITUL']        . ', ' : '';
  $preview .= $record['ODESL_PRIJMENI']     ? $record['ODESL_PRIJMENI']     . ', ' : '';
  $preview .= $record['ODESL_JMENO']        ? $record['ODESL_JMENO']        . ', ' : '';
  $preview .= $record['ODESL_ODD']          ? $record['ODESL_ODD']          . ', ' : '';
  $preview .= $record['ODESL_OSOBA']        ? $record['ODESL_OSOBA']        . ', ' : '';
  $preview .= $record['ODESL_ULICE']        ? $record['ODESL_ULICE']        . ', ' : '';
  $preview .= $record['ODESL_CP']           ? $record['ODESL_CP']           . ', ' : '';
  $preview .= $record['ODESL_COR']          ? $record['ODESL_COR']          . ', ' : '';
  $preview .= $record['ODESL_ICO']          ? $record['ODESL_ICO']          . ', ' : '';
  $preview .= $record['ODESL_PSC']          ? $record['ODESL_PSC']          . ', ' : '';
  $preview .= $record['ODESL_POSTA']        ? $record['ODESL_POSTA']        . ', ' : '';
  $preview .= $record['ODESL_RC']           ? $record['ODESL_RC']           . ', ' : '';
  $preview .= $record['ODESL_EMAIL']        ? $record['ODESL_EMAIL']        . ', ' : '';
  $preview .= $record['ODESL_DATSCHRANKA']  ? $record['ODESL_DATSCHRANKA']  . ', ' : '';
  $preview .= $record['ODESL_DATNAR']       ? $record['ODESL_DATNAR']       . ', ' : '';
  
  return substr($preview, 0, strlen($preview) - 2);
}
