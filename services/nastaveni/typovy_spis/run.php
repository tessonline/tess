<?php
require('tmapy_config.inc');
require_once(FileUp2('.admin/run2_.inc'));
require_once(FileUp2('.admin/status.inc'));
require_once(Fileup2('html_header_title.inc'));

//EedTransakce::ZapisLog($id_posta, $text, 'DOC');

Run_(array('outputtype'=>3,'to_history'=>false));

require_once(Fileup2('html_footer.inc'));
