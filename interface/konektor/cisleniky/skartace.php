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

    $q=new DB_POSTA;
    $sql = "SELECT * FROM cis_posta_skartace ";
    if ($a_odbor) {
      $sql = "SELECT prava from cis_posta_odbory where id=".$a_odbor."";
      $q->query($sql);
      $q->Next_Record();
      $sql = "SELECT * FROM cis_posta_skartace WHERE KOD IN (".substr(str_replace(":",",",$q->Record["PRAVA"]),0,-1).")";
    }
/*    if ($a_id) $sql.=" AND id = '".$a_prac."'";
    if ($a_idod) $sql.=" AND id > '".$a_idod."'";*/
    $sql.=" order by id;";
    $q->query($sql);
  
    echo "<?xml version=\"1.0\" encoding=\"iso-8859-2\" ?>\n";
  
    echo "<skartacni_kod>\n";

    while($q->next_record())
    {
/*      echo "  <kod>\n";
      echo "    <id>".$q->Record["ID"]."</id>\n"; 
      echo "    <value>".$q->Record["TEXT"]."</value>\n"; 
      echo "  </kod>\n";
      */
      echo "  <kod id=\"".$q->Record["ID"]."\">".$q->Record["TEXT"]."</kod>\n"; 
      
    }
    echo "</skartacni_kod>\n";
}
else
{
  die ("chyba - nedostatečná přístupová práva");
}

?>
