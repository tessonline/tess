<?php
If (HasRole("vloz_prichozi")) {

  $PROPERTIES["MENU2L"]["filterall"] = array(
   '0' => "Vlož příchozí",
   '1' => "javascript:NewWindow('/ost/posta/plugins/deniky/brow.php?cacheid=');",
   '2' => '_self',
   'icon' => InsertImage('images/forward', '', '', array('img_sizes'=>false)),

   );

}
