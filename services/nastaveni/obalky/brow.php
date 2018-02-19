<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('html_header_full.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));
require(FileUp2(".admin/config.inc"));

$id=$GLOBALS[ID];

if (HasRole('access_all')) {
  $app_where = " AND id_superodbor is null";
  include_once(FileUp2('.admin/brow_superodbor.inc'));
  if ($GLOBALS['omez_zarizeni']) $app_where = " AND id_superodbor=" . $GLOBALS['omez_zarizeni'];
} else
  $app_where=" AND ID_SUPERODBOR IN (". EedTools::VratSuperOdbor() .")";

require_once(FileUp2('.admin/el/of_select_.inc'));
  
$count=Table(array('showaccess' => true,'showself'=>true,'tablename'=>'OBALKA',"appendwhere"=> $app_where));  

if ($id) {
  UNSET($GLOBALS[ID]);
  NewWindow(array('fname' => 'AgendaSpis', 'name' => 'AgendaSpis', 'header' => true, 'cache' => false, 'window' => 'edit'));
  $GLOBALS['OBALKA_ID']=$id;
  
    
  Table(array('showaccess' => true,'agenda'=>'POSTA_OBALKY_OBJEKTY','unsetvars'=>true,'tablename'=>'OBJEKT'));  

  echo "<a  class=\"btn btn-loading\" href=\"#\" onClick=\"javascript:NewWindowAgendaSpis('objekty/edit.php?insert&OBALKA_ID=".$id."&cacheid=')\">Přidat objekt</a>";

}
require(FileUp2('html_footer.inc'));
?>
