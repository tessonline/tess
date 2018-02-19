<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/brow_func.inc"));

if (HasRole('access_all')) {
  include_once(FileUp2('.admin/brow_superodbor.inc'));
  if ($GLOBALS['omez_zarizeni']) $where2.= " AND id_superodbor=" . $GLOBALS['omez_zarizeni']; else
    $where2.= " AND id_superodbor is null";
} else
  $where2.=" AND ID_SUPERODBOR IN (". EedTools::VratSuperOdbor() .")";


if ($GLOBALS["CISLO_SPISU1"] && $GLOBALS['CISLO_SPISU2']) {
  $sql = 'select * from posta where main_doc=1 and cislo_spisu1 in ('.$GLOBALS["CISLO_SPISU1"].') and cislo_spisu2 in ('.$GLOBALS["CISLO_SPISU2"].')';
  $q = new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();
  $doc_id = $q->Record['ID'] ? $q->Record['ID'] : 0;
  $EedCj = LoadClass('EedCj', $doc_id);
  $ids = $EedCj->GetDocsInCj($doc_id);
  $GLOBALS['ID'] = $ids;
  $GLOBALS['ID'][] = $doc_id;
}

if ($GLOBALS['ID']) {
  $GLOBALS['DOC_ID'] = $GLOBALS['ID'];
  UNSET($GLOBALS['ID']);
}
Table(
  array(
    "showaccess" => true,
    "appendwhere"=>$where2,
    "showupload"=>false,
    "showinfo"=>false,
    "showedit"=>false,
    "showdelete"=>false,
    "showdekete"=>false,
  )
);

require(FileUp2("html_footer.inc"));
