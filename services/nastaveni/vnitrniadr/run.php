<?php

require('tmapy_config.inc');
require(FileUp2('.admin/run2_.inc'));
require_once(Fileup2('html_header_title.inc'));
require_once(Fileup2('.admin/vnitrni_adresati.inc'));

$vnitrniAdresati = getVnitrniAdresatiFromForm(array_merge($_GET, $_POST));
if ($DELETE_ID) {
  deleteVnitrniAdresati($DELETE_ID) ; 
}
else if ($EDIT_ID) {

  editVnitrniAdresati($EDIT_ID, $vnitrniAdresati);
}

$lastid = Run_(array(
  'outputtype' => 3, 
  'no_unsetvars' => true
));

if (!$DELETE_ID && !$EDIT_ID) {

  insertVnitrniAdresati($lastid, $vnitrniAdresati);  
}

require_once(Fileup2('html_footer.inc'));
