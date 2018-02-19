<?php

if ($GLOBALS['ODESLANA_POSTA'] == 'f' && $GLOBALS['ZPUSOB_PODANI'] == 3) {
echo "
<script>document.frm_edit.ZPUSOB_PODANI.disabled = true;</script>
";

}

if ($GLOBALS["ODES_TYP"] && !$is_filter)
 echo "<script>DruhAdresataWhoIS('".$GLOBALS[ODES_TYP]."')</script>";

