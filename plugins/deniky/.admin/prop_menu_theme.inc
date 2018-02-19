<?php

If (HasRole('spravce')||HasRole('podatelna')||HasRole('podatelna-odbor')) {

  $PROPERTIES["MENU2L"]["new"] = array("Vlož příchozí", "javascript:NewWindow('/ost/posta/plugins/deniky/brow.php?cacheid=');");

}
