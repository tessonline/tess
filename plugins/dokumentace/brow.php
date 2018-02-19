<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('html_header_full.inc'));

if (HasRole('spravce')) {
  include_once(FileUp2('.admin/brow_superodbor.inc'));
}
echo "<p><form name='frm_doc'>";
echo '<div class="form darkest-color"> <div class="form-body"> <div class="form-row">';

echo '<div class="form-item"> <label class="form-label" for="placeholder">Hledat dokumentaci:</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište název dokumentace" type="text" size=80 id="X_NAZEV" name="X_NAZEV"> </div> </div> </div>';

echo '</div> </div> </div>';
echo "</form></p>";


if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) $where = " AND superodbor is null or superodbor=" . EedTools::VratSuperOdbor();
if (HasRole('spravce'))  $where = ' AND superodbor is null';

if ($GLOBALS['omez_zarizeni']) $where = " AND superodbor=" . $GLOBALS['omez_zarizeni'];

if (HasRole('lokalni-spravce') || HasRole('spravce'))  $can_edit = true; else $can_edit = false;

if ($GLOBALS['X_NAZEV']) $GLOBALS['NAZEV'] = "*" . $GLOBALS['X_NAZEV'] . "*";

Table(array(
  "appendwhere" => $where,
  "showupload" => true,
));

NewWindow(array("fname" => "Dokumentace", "name" => "Dokumentace", "header" => true, "cache" => false, "window" => "edit"));

if (HasRole('lokalni-spravce') || HasRole('spravce')) {
  echo '<a class="btn" href="javascript:NewWindowDokumentace(\'edit.php?insert&cache=\')" title="Vložit novou dokumentaci">Vložit novou dokumentaci</a>';
}

require(FileUp2("html_footer.inc"));