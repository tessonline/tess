<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/run2_.inc"));
include_once(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));
include_once(FileUp2(".admin/security_obj.inc"));
include_once(FileUp2(".admin/upload_.inc"));

include(FileUp2(".admin/oth_funkce.inc"));
include_once(FileUp2(".admin/security_name.inc"));

include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
require_once(FileUp2(".admin/el/of_select_.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$last_date=Date('Y-m-d');
$last_time=Date('H:i:s');
$datum=date('d.m.Y H:m');
include_once(FileUp2("html_header_full.inc"));


if (is_array($_POST['SELECT_ID']) && !$_POST['box']) {
  if (count($_POST['SELECT_ID'])>0)
    $_POST['sql'] = str_replace(' ORDER BY ', ' and s.id in (' . implode(',',$_POST['SELECT_ID']). ') ORDER BY ', $_POST['sql']);
}

$sql_zaklad=$_POST['sql'];
//echo $sql;
$spisovna_id=$_POST['predat_spisovna'];

$uloz=false;

$q = new DB_POSTA;
$a = new DB_POSTA;

$spisovna = getSelectDataEed(new of_select_spisovna(array()));

$spisovna_text = $spisovna[$spisovna_id];
$q->query($sql_zaklad);
while ($q->Next_Record()) {

  $id = $q->Record['ID'];
  $dokument_id = $q->Record['DOKUMENT_ID'] ? $q->Record['DOKUMENT_ID'] : 0;
//  $sql = 'update posta_spisovna set spisovna_id=' . $spisovna_id . ' where id=' . $id;
  $sqlb = 'update posta set spisovna_id=0,status=-5 where id=' . $dokument_id;

  $a->query($sql);
  $a->query($sqlb);

  $docObj = LoadClass('EedCj', $dokument_id);
  $cj = $docObj->cislo_jednaci_zaklad;
  $text = 'Spis/čj. <b>' . $cj. '</b> byl uvolněn z původní spisovny pro předání do jiné spisovny: <b>' . $spisovna_text . '</b>';
  EedTransakce::ZapisLog($dokument_id, $text, 'SPIS', $id_user);

}

echo '<h1>Dokumenty byly uvolněny pro předání.</h1>';
echo "
<input type='button' onclick='document.location.href=\"brow.php?SPISOVNA_ID=".$spisovna_id."\";' value='Pokračovat' class='btn'>";
include_once(FileUp2("html_footer.inc"));

$protokol=false;