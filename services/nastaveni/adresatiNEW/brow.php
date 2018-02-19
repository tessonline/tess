<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
//require(FileUp2('html_header_title.inc'));
require(FileUpUrl('html_header.inc'));
//require(FileUpUrl('html_header_jquery.inc'));
echo '<script src="./javascript/jquery.min.js"></script>';
echo '<script src="./javascript/ajax_inicialize.js"></script>';
echo'</head><body>';
Table(array(
  'showaccess'=>true
));

require(FileUp2('html_footer.inc'));