<?php
require("tmapy_config.inc");

/**
//zpusob volani ares.php?ICO=
Musi se volat do noveho okna, fce vraci data pomoci window.opener
Napr:
window.open("./ares.php?ICO="+document.forms[0].ODESL_ICO.value+"&"+d.getTime(), "", "height=50px,width=150px,left=200,top=200");
*/

require(FileUp2(".admin/ares_.inc"));


if ($_GET['typ'] == 'F')
echo "<script>
  alert('Údaj o jménu a příjmení podnikající fyzické osoby je z ARES vrácen jako jeden text. Proveďte prosím úpravu na jméno a příjmení ručně.');
</script>
";

echo "<script>
  parent.$.fancybox.close();
</script>
";

