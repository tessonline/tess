<?php
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

if (!$action) $action = 'brow.php';
echo '<p><form method="get" action="'.$action.'" name="frm_change2">
<div class="form darkest-color"> <div class="form-body"> <div class="form-row">
';
$prac =  getSelectDataEed(new of_select_superodbor(array()));
echo $GLOBALS['CONFIG']['NAZEV_SUPERODBOR'] . ":&nbsp;<select name='omez_zarizeni' onchange='document.frm_change2.submit();'><option value=''></option>";
while (list($key,$val)=each($prac)) {
  echo "<option value='".$key."' ".($key==$GLOBALS['omez_zarizeni']?'SELECTED':'').">".$val."</option>";
}
echo "</select>";

echo '</div> </div> </div>';
echo '</div> </div> </div>';

echo "</form></p>";
