<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));

require_once(FileUp2('.admin/oth_funkce_2D.inc'));
if (!HasRole('spravce') && !HasRole('lokalni-spravce')) {
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

  $user = LoadClass('EedUser', $USER_INFO['ID']);
  $GLOBALS['REFERENT'] = $user->id_user;

  $pole = OdborPrac($GLOBALS['REFERENT']);
  $GLOBALS['ODBOR'] = $pole['odbor'];
  $GLOBALS['SUPERODBOR'] = $pole['so'];
}
Run_(array("showaccess"=>true,"outputtype"=>3));
require_once(Fileup2("html_footer.inc"));  

