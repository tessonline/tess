<?php
require_once(FileUpUrl('.admin/security_obj.inc'));
require_once($GLOBALS['TMAPY_LIB'] . '/iszr/twist/TwistRenderer.inc');
require_once($GLOBALS['TMAPY_LIB'] . '/iszr/twist/TwistDataLoader.inc');
$USER_INFO = $GLOBALS['TMAPY_SECURITY']->GetUserInfo();

$f->dont_disabled_submit_button = true;
 
$x = TwistDataLoader::getRolesForUser($USER_INFO['ID']);

$renderer = new TwistRenderer('ISZR_NAHLED');
 
$GLOBALS['IDENT'] = 'E35'; 
ob_start();
$renderer->showFormAgendaRole($x, true, 'ident=' . $GLOBALS['ident'], true, 'frm_edit');
$frmAgendaRole = ob_get_contents();
ob_end_clean();
echo '<h1>Základní registry - agenda-role</h1>';
echo '<div class="form darkest-color"> <div class="form-body"> <div class="form-row">';
echo '<form name="frm_edit" action="javascript:GuideSubmit(1)" method="GET" target="_self" class="editForm" onsubmit="">
<input type="hidden" name="TYP" value="'.$GLOBALS['TYP'].'">
<input type="hidden" name="ICO" value="'.$GLOBALS['ICO'].'">
<input type="hidden" name="JMENO" value="'.$GLOBALS['JMENO'].'">
<input type="hidden" name="PRIJMENI" value="'.$GLOBALS['PRIJMENI'].'">
<input type="hidden" name="DATNAR" value="'.$GLOBALS['DATNAR'].'">
<input type="hidden" name="GUIDE_DIRECTION" value="0">
<input type="hidden" name="GUIDE_ID" value="0">
<input type="hidden" name="G_NAME" value="posta_iszr">
<table>' . $frmAgendaRole . $format . '</table></form>';
echo '</div> </div> </div>';
