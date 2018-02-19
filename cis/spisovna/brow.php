<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require_once(Fileup2(".admin/security_.inc"));
require_once(Fileup2(".admin/security_name.inc"));
require(FileUp2("html_header_full.inc"));
// if (!$GLOBALS['SUPERODBOR'])
//   $GLOBALS['SUPERODBOR']=VratSuperOdbor();

if (HasRole('access_all')) {
  include_once(FileUp2('.admin/brow_superodbor.inc'));
}

if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) $where = " AND superodbor=" . EedTools::VratSuperOdbor();
if (HasRole('access_all'))  $where = ' AND superodbor is null';

if ($GLOBALS['omez_zarizeni']) $where = " AND superodbor=" . $GLOBALS['omez_zarizeni'];

Table(
  array(
    "showaccess" => true,
    "appendwhere" => $where,
  )
);
require(FileUp2("html_footer.inc"));
?>
