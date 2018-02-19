<?php
// ukazka volani funkce s parametry:
// https://a_login:a_heslo@project.tmapserver.cz/ost/posta/connect/dosle_pisemnosti.php?a_agenda=AGENDA&a_odbor=ODBOR&a_prac=PRAC

require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/security_obj.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
// pouze pro ucely testovani
  $conn_r = true;
  $conn_w = true;
  
// test, zda ma uzivatel pristupova prava
if ($conn_w)
{
// hlavicka XML
    Header("Pragma: no-cache");
    Header("Cache-Control: no-cache");
    Header("Content-Type: text/xml");
  
    echo "<?xml version=\"1.0\" encoding=\"iso-8859-2\" ?>\n";
  
    echo "<druhy_obalek>\n";

    while (list($k,$o) = each($GLOBALS[CONFIG][TYP_ODESLANI])) 
    {
      echo "  <obalka id=\"".$o['VALUE']."\">".$o['LABEL']."</obalka>\n";
    }
    echo "  <obalka id=\"11\">Obálka jen 10dní</obalka>\n";
    echo "  <obalka id=\"12\">Obálka nevhazovat do schranky</obalka>\n";
    echo "  <obalka id=\"13\">Obálka jen 10 dní a nevhazovat do schranky</obalka>\n";
    echo "</druhy_obalek>\n";
}
else
{
  die ("chyba - nedostatečná přístupová práva");
}

?>
