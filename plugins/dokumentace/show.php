<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require_once(Fileup2("html_header_title.inc"));

$ID = (int) $ID;
if (!$ID || $ID == 0) {
  echo "Neni ID";
  require_once(Fileup2("html_footer.inc"));
  Die();
}

$q = new DB_POSTA;
$sql = 'select * from ' . $GLOBALS['PROPERTIES']['AGENDA_TABLE'] . ' where id=' . $ID;
$q->query($sql);
$q->Next_Record();

echo '<h1>' . $q->Record['NAZEV'] . '</h1>';
echo '<p>' . $q->Record['TEXT'] . '</h1>';

echo "<p><a href='#' class='btn' onclick='window.close(); '>Zavřít</a></p>";
require_once(Fileup2("html_footer.inc"));  

