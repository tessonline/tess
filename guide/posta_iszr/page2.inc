<?php
/*[16.9.2013 13:55:09] Lucie Leistnerová: tak se posila command=getdiff
a bud se vysledek ulozi do promennych 
$GLOBALS['ISZR_DIFF_OBJ'] a $GLOBALS['ISZR_DATA_OBJ'] nebo si jeste parametry muzes rict, jak se maji jmenovat
[16.9.2013 13:57:48] Lucie Leistnerová: pouziti:
*/
require('tmapy_config.inc'); 
require_once(FileUp2('.admin/agenda_func.inc'));
require_once($GLOBALS['TMAPY_LIB'].'/iszr/lib/IszrConfig.inc');
require_once($GLOBALS['TMAPY_LIB'].'/iszr/lib/IszrInterface.inc');

$datnar = $GLOBALS['DATNAR'];
$datum = explode('.', $GLOBALS['DATNAR']);
$GLOBALS['DATNAR'] = $datum[2] . '-' . $datum[1] . '-' . $datum[0];
$PROPERTIES = loadProperties(null, GetAgendaPath('POSTA', 0, 0) . '/.admin/properties.inc');
$GLOBALS['ODESL_ICO'] = $GLOBALS['ICO'];
$GLOBALS['ODESL_JMENO'] = $GLOBALS['JMENO'];
$GLOBALS['ODESL_PRIJMENI'] = $GLOBALS['PRIJMENI'];
$GLOBALS['ODESL_DATNAR'] = $GLOBALS['DATNAR'];
//$_REQUEST['AGENDA'] = 'A1023';
//$_REQUEST['ROLE'] = 'CR5823';
//$_REQUEST['UCEL'] = 'test aplikace';

//$GLOBALS['EDIT_ID'] = 4541945;

//$GLOBALS['ISZR_APP_ID'] = $GLOBALS['EDIT_ID'];
$conf = IszrConfig::getModulInstance('IszrDirect');
$appConf = $conf->getAppAll();
//print_r($appConf);
//Die();
$GLOBALS['EDIT_ID'] = 4474847;

$iszr = new IszrInterface(
  $PROPERTIES,
  $appConf,
  array(
//    'ISZR_APP_ID' => ($GLOBALS['EDIT_ID'] ? $GLOBALS['EDIT_ID'] : -1),
    'ISZR_APP_ID' => $GLOBALS['EDIT_ID'],
    'command' => 'getdiff',
    'AGENDA' => $_REQUEST['AGENDA'],
    'ROLE' => $_REQUEST['ROLE'],
    'UCEL' => $_REQUEST['UCEL'],
  )
);
$iszr->process();


if ($GLOBALS['TYP'] == 'PO') {
  $osoba = $GLOBALS['ISZR_DATA_OBJ']->osoba[0];
  $ds_obj = $GLOBALS['ISZR_DATA_OBJ']->ds;
  
  foreach($ds_obj as $ds_test) {
    if ($ds_test->stav == 'platna') $ds = $ds_test->dsId;
  }
  
  $ico = $GLOBALS['ICO'];
  
  $prijmeni = $osoba->nazev;
  $adresa = $osoba->adresa;
}
else {
  $jmeno = $GLOBALS['ISZR_DATA_OBJ']->jmeno;
  $prijmeni = $GLOBALS['ISZR_DATA_OBJ']->prijmeni;
  $adresa = $GLOBALS['ISZR_DATA_OBJ']->adresaPobytu;
}

IF ($GLOBALS['ISZR_DATA_OBJ']->adresaDorucovaci->text <> '') {
  include_once(FileUp2('html_header_full.inc'));
   echo '<h1>Nalezena doručovací adresa!</h1>';
   echo '<p><span class="text"> ' . $jmeno .' ' . $prijmeni . ' má uvedenu doručovací adresu<br/>';
   echo '<b>' . $GLOBALS['ISZR_DATA_OBJ']->adresaDorucovaci->text . '</b></p>';
   echo '<p>Adresu bohužel musíte překopírovat ručně, neboť nejde elektronicky rozdělit. Děkuji.</p>';
   echo '<p><input type="button" value="   Zavřít okno   " class="btn" onclick="window.close();"></p>';
  include_once(FileUp2('html_footer.inc'));
  Die();
}


$ulice = $adresa->uliceNazev ? $adresa->uliceNazev : $adresa->castObceNazev;
$cp = $adresa->cisloDomovni;
$cor = $adresa->cisloOrientacni;
$mesto = $adresa->obecNazev;
$psc = $adresa->postaKod;

echo "
<script language=\"JavaScript\" type=\"text/javascript\">
<!--
  window.opener.document.frm_edit.ODESL_ADRKOD.value = '".$kod."';

";

if ($GLOBALS['TYP'] == 'PO')
echo "
  window.opener.document.frm_edit.ODESL_PRIJMENI_FIRMA.value = '".$prijmeni."';
  window.opener.document.frm_edit.ODESL_PRIJMENI_FIRMA.style.color='red';
";
else
echo "
  window.opener.document.frm_edit.ODESL_OSLOVENI.value = '".$osloveni."';
  window.opener.document.frm_edit.ODESL_OSLOVENI.style.color='red';
  window.opener.document.frm_edit.ODESL_PRIJMENI.value = '".$prijmeni."';
  window.opener.document.frm_edit.ODESL_PRIJMENI.style.color='red';
  window.opener.document.frm_edit.ODESL_JMENO.value = '".$jmeno."';
  window.opener.document.frm_edit.ODESL_JMENO.style.color='red';
//  window.opener.document.frm_edit.ODESL_TITUL.value = '".$titul."';
//  window.opener.document.frm_edit.ODESL_TITUL.style.color='red';
      window.opener.document.frm_edit.ODESL_DATNAR.value = '".$datnar."';
      window.opener.document.frm_edit.ODESL_DATNAR.style.color='red';
";

echo "
  window.opener.document.frm_edit.ODESL_ICO.value = '".$ico."';
  window.opener.document.frm_edit.ODESL_ICO.style.color='red';
  
  
  window.opener.document.frm_edit.ODESL_ULICE.value = '".$ulice."';
  window.opener.document.frm_edit.ODESL_ULICE.style.color='red';

  window.opener.document.frm_edit.ODESL_CP.value = '".$cp."';
  window.opener.document.frm_edit.ODESL_CP.style.color='red';

  window.opener.document.frm_edit.ODESL_COR.value = '".$cor."';
  window.opener.document.frm_edit.ODESL_COR.style.color='red';

  window.opener.document.frm_edit.ODESL_POSTA.value = '".$mesto."';
  window.opener.document.frm_edit.ODESL_POSTA.style.color='red';

  window.opener.document.frm_edit.ODESL_PSC.value = '".$psc."';
  window.opener.document.frm_edit.ODESL_PSC.style.color='red';

  window.opener.document.frm_edit.ODESL_DATSCHRANKA.value = '".$ds."';
  window.opener.document.frm_edit.ODESL_DATSCHRANKA.style.color='red';

  window.opener.document.frm_edit.FROZEN.value = 'N';

  window.close();
//-->
</script>
";
