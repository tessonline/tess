<?php
require("tmapy_config.inc");
require(FileUp2(".admin/isds_.inc"));
require(FileUp2(".admin/config.inc"));

$q = new DB_POSTA;
$sql = "select * from posta where odes_typ='C'";
$q->query($sql);

while ($q->Next_Record()) {
  $doc_id = $q->Record['ID'];
  $skartace_id = $q->Record['SKARTACE_ID'];
  $studium_id = $q->Record['WHOIS_IDSTUDIA']

  if ($skartace_id>0) {
    $skartace_pole = EedTools::Skartace_Pole($skartace_id);
    $znak = $skartace_pole['znak'];
  }

  if ($znak<>'' && $studium_id<>'' && $doc_id>0) {
    $vysl = VlozDokumentDoTypSpisu($doc_id, $studium_id, $znak);
    echo $vysl;
  }
}
