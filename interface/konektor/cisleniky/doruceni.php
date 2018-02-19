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
  
    echo "<zpusob_doruceni>\n";

    while (list($k,$o) = each($GLOBALS[CONFIG][DRUH_ODESLANI])) 
    {
/*      echo "  <doruceni>\n";
      echo "    <id>".$o['VALUE']."</id>\n"; 
      echo "    <value>".$o['LABEL']."</value>\n"; 
      echo "  </doruceni>\n";
    */
       echo "  <doruceni id=\"".$o['VALUE']."\">".$o['LABEL']."</doruceni>\n"; 

    }
    echo "</zpusob_doruceni>\n";
}
else
{
  die ("chyba - nedostatečná přístupová práva");
}

?>
