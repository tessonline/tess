<?php
require('tmapy_config.inc');
require_once(FileUp2('.admin/run2_.inc'));
require_once(Fileup2('html_header_title.inc'));

$except = array('eid','OWNER_ID');

foreach($_GET as $key => $val) {
  if (!in_array($key, $except)) {
    if (is_array($val)) $val = ','.implode(',',$val);
  }
  if ($key<>'OWNER_ID') $uloz[] = $key.'='.$val;
}


$GLOBALS['NASTAVENI'] = implode('|', $uloz);
$GLOBALS['EDIT_ID'] = $eid;


Run_(array('outputtype'=>3,'to_history'=>false));

require_once(Fileup2('html_footer.inc'));
