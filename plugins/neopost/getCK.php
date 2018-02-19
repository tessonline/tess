<?php
require("tmapy_config.inc");
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));
require_once(FileUp2(".admin/el/of_select_.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require(FileUp2("html_header_full.inc"));

$id = $GLOBALS['id'];

$error = false;

if (strlen($id)>0) {

  $idCK = PrevedCPnaID($id,'');
//  echo "onma ID kodu je $idCK ";
  if ($idCK>0) {
    $span = 'ok';
    $span = "Nalezeno " . UkazAdresu($idCK, ', ');
  }
  else {
    $error = true;
    $span = $id.'- <font color=red><b>nenalezeno!</b></font>';
  }
}
else
  $span = '&nbsp;';

$res = $span;
//echo $res;

if ($error)
  echo '<script type="text/javascript">
    window.parent.document.getElementById(\'hledamCK\').style = \'visibility:hidden\';
    window.parent.document.getElementById(\'span_text_CK\').innerHTML = \''.$res.'\';
    window.parent.document.getElementById(\'span_text_CK2\').innerHTML = \'\';
    window.parent.document.getElementById(\'carKod\').disabled = false;
    window.parent.document.getElementById(\'carKod\').value = \'\';
    window.parent.document.getElementById(\'carKod2\').value = \'\';
    window.parent.document.getElementById(\'DOC_ID\').value = \'0\';
    window.parent.document.getElementById(\'carKod2\').disabled = true;
    window.parent.document.getElementById(\'carKod\').focus();
  </script>
  ';

else
  echo '<script type="text/javascript">
    window.parent.document.getElementById(\'hledamCK\').style = \'visibility:hidden\';
    window.parent.document.getElementById(\'span_text_CK\').innerHTML = \''.$res.'\';
    window.parent.document.getElementById(\'span_text_CK2\').innerHTML = \'\';
    window.parent.document.getElementById(\'carKod\').disabled = true;
    window.parent.document.getElementById(\'carKod2\').value = \'\';
    window.parent.document.getElementById(\'DOC_ID\').value = \''.$idCK.'\';
    window.parent.document.getElementById(\'carKod2\').disabled = false;
    window.parent.document.getElementById(\'carKod2\').focus();
  </script>
  ';


require(FileUp2("html_footer.inc"));

