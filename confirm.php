<?php
require("tmapy_config.inc");
if ($_GET['msg'] == 'ok') {
  if ($_GET['url']!="") 
    header('Location: '.$_GET['url']);
  else
    require_once("ug_file.php");
  //header('Location: /ost/posta/ug_file.php?EDIT_ID=',$GET['id']);
  //echo '<p>Šablona byla vygenerována a uložena do složky upload tohoto dokumentu.</p>';
}

else {
  require(FileUp2("html_header_full.inc"));
  echo '<p>Generování šablony selhalo.</p>';
  echo '<button class="button btn" onclick="parent.$.fancybox.close()">Zavřít</a>';
  require(FileUp2("html_footer.inc"));
}

?>