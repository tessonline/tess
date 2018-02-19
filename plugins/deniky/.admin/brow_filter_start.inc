<?php

$deniky = getSelectDataEed(new of_select_deniky(array('short'=>true)));

echo '<div class="form-item"> <label class="form-label" for="select">Deník:</label> <div class="form-field-wrapper"> <div class="form-field">';
echo "<select name = 'omez_denik' class='select' onchange='document.frm_change.submit();'><option value=''></option>";
while (list($key,$val)=each($deniky))
  echo "<option value='".$key."' ".($key==$GLOBALS['omez_denik']?'SELECTED':'').">".$val."</option>";
echo "</select>";
echo '</div> </div> </div>';
