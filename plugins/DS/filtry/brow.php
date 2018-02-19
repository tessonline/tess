<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2(".config/config.inc"));
require(FileUp2('html_header_title.inc'));

Table(array(
  'showaccess'=>true
));

require(FileUp2('html_footer.inc'));
