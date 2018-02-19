<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

$where = " AND SPISOVNA_ID IS NULL ";
if (!HasRole('spravce')) {
  $odbor = VratOdbor();
  if (HasRole('zpracovat-odbor')) {
    $EedUser = LoadClass('EedUser',0);
    $id = GetParentGroup($EedUser->VratOdborZSpisUzlu($odbor));
    if ($id>0) {
      $odbor = $EedUser->VratSpisUzelZOdboru($id);
      $odbor =  $odbor['ID'];
    }
  }
  $where .= ' AND ODBOR in (' . $odbor . ')';
}

$count = Table(
  array(
    'tablename' => 'box_seznam',
    'showaccess' => true,
    'appendwhere' => $where,
    'showself' => true,
  )
);

if ($count == 1 && $GLOBALS['ID']) {
  $box_id = $GLOBALS['ID'];
  UNSET($GLOBALS['ID']);
  if ($box_id>0) $where = "and id in (select posta_id from posta_spisovna_boxy_ids where box_id=" . $box_id .")";
  $count = Table(
    array(
      'caption' => 'Seznam spisů v daném boxu',
      'agenda' => 'POSTA',
      'tablename' => 'POSTA',
      'showaccess' => true,
      'appendwhere' => $where,
      'setvars' => true,
      'showself' => false,
    )
  );

}
require(FileUp2("html_footer.inc"));
?>
