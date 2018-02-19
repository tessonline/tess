<?php
require('tmapy_config.inc');
require(FileUp2('.admin/run2_.inc'));
require_once(Fileup2('html_header_title.inc'));
require_once(Fileup2('.admin/vnejsi_adresati.inc'));


$vnejsiAdresati = getVnejsiAdresatiFromForm(array_merge($_GET, $_POST));
if ($DELETE_ID) {
  deleteVnejsiAdresati($DELETE_ID) ; 
}
else if ($EDIT_ID) {
  editVnejsiAdresati($EDIT_ID, $vnejsiAdresati);
}

$lastid = Run_(array(
  'outputtype' => 3, 
  'no_unsetvars' => true
));

if (!$DELETE_ID && !$EDIT_ID) {

  insertVnejsiAdresati($lastid, $vnejsiAdresati);  
}

require_once(Fileup2('html_footer.inc'));
