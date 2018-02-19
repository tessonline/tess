<?php
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

if(!$GLOBALS['TMAPY_SECURITY_WHOIS']) { ///TODO: kdyz nebude, tak ho vytvorit
    $sec_file = $GLOBALS["TMAPY_LIB"] . "/security/whois.inc";
    include($sec_file);
    $GLOBALS["TMAPY_SECURITY_WHOIS"] = new Security_Obj_WhoIS();
}
if (!$action) $action = 'brow.php';

echo '<p><form method="get" action="'.$action.'" name="frm_change">
<div class="form darkest-color"> <div class="form-body"> <div class="form-row">
';
echo '<input type="hidden" name="insert" >';
$prac = $GLOBALS['TMAPY_SECURITY_WHOIS']->getSeznamPracovist();

echo $GLOBALS['CONFIG']['NAZEV_SUPERODBOR'] . ":&nbsp;<select name='omez_zarizeni' onchange='document.frm_change.submit();'><option value=''></option>";
while (list($key,$val)=each($prac)) {
  echo "<option value='".$key."' ".($key==$GLOBALS['omez_zarizeni']?'SELECTED':'').">".$val."</option>";
}
echo "</select>";

foreach ($add_hidden_variables as $key => $val)
  echo '<input type="hidden" name="'. $key . '" value="' . $val . '"
';


echo '</div> </div> </div>';
echo '</div> </div> </div>';

echo "</form></p>";
