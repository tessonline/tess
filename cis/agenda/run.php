<?php
require ("tmapy_config.inc");
require (FileUp2(".admin/run2_.inc"));
require_once (Fileup2("html_header_title.inc"));

$kopie_agendy = $GLOBALS['KOPIE_AGENDY'];
$id_agendy = $GLOBALS['ID_AGENDY'];

if (isset($GLOBALS['ID_DOKUMENTU'])){
  $db = new DB_POSTA();
  $sql = "INSERT INTO posta_agenda_typ VALUES (".$GLOBALS['ID_AGENDY'].",".$GLOBALS['ID_DOKUMENTU'].")";
  $db->query($sql);
  echo "
<script language=\"JavaScript\" type=\"text/javascript\">
window.opener.document.location.reload();
window.close();
</script>
";
  
} else
  
  $inserted_agenda_id = Run_(array(
    "showaccess" => true,
    "outputtype" => 1
  ));
  
  
  if ($kopie_agendy==1) {
    $db = new DB_POSTA();
    $sql = "select id,nazev, odbor, skartace_id, lhuta,kpam,faze, poradi, neaktivni, neaktivni_agenda, 99999 as id_agendy, popis from cis_posta_typ where id_agendy =".$id_agendy;
    $db->query($sql);
    while ($db->Next_Record()) {
      //insert do cis_posta_typ RETURNIND id
      $skartace_id = ($db->Record["SKARTACE_ID"]=='' ? 'null' : $db->Record["SKARTACE_ID"]);
      $odbor = ($db->Record["ODBOR"]=='' ? 'null' : $db->Record["ODBOR"]);
      $lhuta = ($db->Record["LHUTA"]=='' ? 'null' : $db->Record["LHUTA"]);
      $neaktivni = $db->Record["NEAKTIVNI"] ? $db->Record["NEAKTIVNI"] : 'false';
      $neaktivni_agenda = $db->Record["NEAKTIVNI_AGENDA"] ? $db->Record["NEAKTIVNI_AGENDA"] : 'false';
      $sql = "INSERT INTO cis_posta_typ (nazev,odbor,skartace_id,lhuta,kpam,faze, poradi, id_agendy, popis, neaktivni, neaktivni_agenda) VALUES ('"
          .$db->Record["NAZEV"]."',".$odbor.",".$skartace_id.",".$lhuta.",'".$db->Record["KPAM"]."','"
              .$db->Record["FAZE"]."','".$db->Record["PORADI"]."',".$inserted_agenda_id.",'".$db->Record["POPIS"]."','".$neaktivni."','"
                  .$neaktivni_agenda."') RETURNING id";
          $q = new DB_POSTA();
          $q->query($sql);
          $q->Next_Record();
          $sql = "insert into posta_workflow (id_workflow,id_typ,promenna,hodnota,dokument) (select id_workflow, "
              .$q->Record['ID']." as id_typ,promenna,hodnota,dokument from posta_workflow where id_typ = ".$db->Record['ID'].")";
          $q->query($sql);
    }
  }
  if ($inserted_agenda_id) {
    $q = new DB_POSTA();
    $sql = "update cis_posta_typ set neaktivni_agenda =".(($GLOBALS['NEAKTIVNI']==1) ? 'true' : 'false')." WHERE id_agendy =".$inserted_agenda_id;
    $q->query($sql);
  }
  echo "
<script language=\"JavaScript\" type=\"text/javascript\">
window.opener.document.location.reload();
window.close();
</script>
";
  
  
  require_once(Fileup2("html_footer.inc"));
  
  ?>

