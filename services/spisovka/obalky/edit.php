<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));
require(FileUp2(".admin/javascript.inc"));
$run = GetAgendaPath('POSTA',false,true) . '/output/pdf/obalka.php';

Form_(
  array(
    'showaccess' => true,
    'caption' => 'Obálky',
    'action' => $run
  )
);

require(FileUp2("html_footer.inc"));

