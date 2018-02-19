<?php
include_once(FileUp2('.admin/security_name.inc'));
include_once(FileUp2('.admin/oth_funkce.inc'));
include_once(FileUp2('.admin/table_funkce_denik.inc'));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

$a = new DB_POSTA;
$b = new DB_POSTA;



$TABLE_CONFIG["callback"] = "ChangeClassBarva_AKCE";
$TABLE_CONFIG['schema'][] = array( 'field' => 'ID', 'label' => 'ID zápůjčky', 'width' => '4%');
$TABLE_CONFIG['schema'][] = array( field => 'UkazDocZapujcka(ID, RUCNE, RUCNE_CJ)', 'label' => 'seznam dokumentů', 'order_by' => '', width => '45%', 'add' => 'NOWRAP');

$TABLE_CONFIG['schema'][] = array( 'field' => "CZDate(VYTVORENO)", 'label' => 'Zapůjčeno', 'width' => '10%');
$TABLE_CONFIG['schema'][] = array( 'field' => 'UkazUsera(PUJCENO_KOMU)', 'label' => 'Komu', 'width' => '20%');
$TABLE_CONFIG['schema'][] = array( 'field' => 'UkazVraceno(VRACENO, ID, RUCNE)', 'label' => 'Vráceno', 'width' => '20%');
$TABLE_CONFIG['schema'][] = array( 'field' => 'UkazTisk(ID)', 'label' => '&nbsp;', 'width' => '1%', 'class' => 'image');
//$TABLE_CONFIG['schema'][] = array( 'field' => 'Skartace(ID)', 'label' => '', 'add' => 'align = center');


?>
<script>
  function NewWindowEdit(script) {
    if (window.name == 'Edit') {
      window.location.href = script;
    } else {
      newwindow = window.open(script, 'Edit','height=570,width=790,left=1,top=1,scrollbars,resizable');
      newwindow.focus();
    }
  }
function edit_ (id) {
  NewWindowEdit('edit.php?edit&EDIT_ID='+id);
}
</script>