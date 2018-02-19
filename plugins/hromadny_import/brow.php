<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('html_header_title.inc'));

$GLOBALS['ZAKAZ_ROZSIRENI_VIDITELNOSTI']=true;
include_once(FileUp2('.admin/brow_access.inc'));

Access();


$where = str_replace("referent", "owner_id", mb_strtolower($where));

$tid = $GLOBALS['TID'];

if (strlen($where)<3) $where.= "(1=1) ";

Table(array(
  'showaccess'=>false,
  'showupload'=>true,
  'setvars'=>true,
  'showself'=>true,
  'appendwhere' => $where,
));

$GLOBALS['FILEUPURL_AGENDA']="POSTA_HROMADNY_IMPORT";


if (isset($tid)) {
  unset($GLOBALS['LAST_DATE']);
  unset($GLOBALS['LAST_TIME']);
  /*unset($GLOBALS['LAST_USER_ID']);*/
  unset($GLOBALS['STAV']);
  $where = " AND p.ID IN (SELECT id_posta FROM ".$GLOBALS['PROPERTIES']['AGENDA_TABLE']."_POSTA WHERE id_import=".$GLOBALS['TID'].")";

  Table(array(
    "tablename" => "postahr",
    "agenda" => "POSTA",
    'setvars' => true,
    'showupload' => true,
    'showhistory' => true,
    'showexportall' => true,
    "showedit"=>true, 
    "showdelete"=>true, 
    "showinfo" =>true,
    "appendwhere" => $where,
    "schema_file" => ".admin/table_schema_spis.inc",
  ));
  unset($GLOBALS['TID']);
}


echo '<form>';
echo "<input type=\"submit\" class=\"btn button\" value=\"" . $GLOBALS['RSTR_IMPORT']['import_novy_import']  . "\" onClick=\"javascript:NewWindowEdit('edit.php?insert');return false;\">\n";
echo '</form>';


echo '<p><span class="caption">' . $GLOBALS['RSTR_IMPORT']['import_strucny_navod'] . ':</span></p>';
echo '<p>
<ul>
<li>1. ' . $GLOBALS['RSTR_IMPORT']['import_vytvorit_novy_radek']  . ' <img src="'.FileUpUrl('images/novy_import.jpg').'"></li>
<li>2. ' . $GLOBALS['RSTR_IMPORT']['import_nahrat_priloh_csv_soubor'] . '</li>
<li>3. ' . $GLOBALS['RSTR_IMPORT']['import_nahrani_soubor_importer'] . '</li>
<li>4. ' . $GLOBALS['RSTR_IMPORT']['import_postup_dle_pokynu'] . '</li>
</ul>
</p>';
require(FileUp2('html_footer.inc'));

