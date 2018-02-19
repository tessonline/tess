<?php
require('tmapy_config.inc');
require(FileUp2('.admin/run2_.inc'));
require_once(Fileup2('html_header_title.inc'));

Run_(array(
  'outputtype' => 3, 
  'no_unsetvars' => true
));

require_once(Fileup2('html_footer.inc'));
