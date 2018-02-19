<?php
require('tmapy_config.inc');
require_once(FileUp2('.admin/run2_.inc'));
require_once(Fileup2('html_header_title.inc'));
include_once(FileUp2('.admin/classes/form/Multiple.php'));

//EedTransakce::ZapisLog($id_posta, $text, 'DOC');

 $spis_id = Run_(array('outputtype'=>3,'to_history'=>false));
 
 $db = new DB_POSTA();
 $mul = new Multiple ($db,"posta_typovy_spis_typ_posty","id_typovy_spis","id_typ_posty");
 
 if (!isset($GLOBALS['DELETE_ID'])) {
  //$item_names = array("TYP_POSTY");
   if (isset($GLOBALS['EDIT_ID'])) {
    $mul->edit($spis_id);
  }
   $mul->insert($spis_id,"TYP_POSTY");
 }
 


require_once(Fileup2('html_footer.inc'));
