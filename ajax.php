<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('.admin/brow_func.inc'));




if ($cmd == 'pocty') {
  $header_without_link = true;
  require(FileUp2('html_header.inc'));
  include('.admin/ajax_pocty.inc');
}

if ($cmd == 'unity') {
  require(FileUp2('html_header.inc'));
  include('.admin/ajax_unity.inc');
//  require(FileUp2('html_footer.inc'));
}