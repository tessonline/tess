<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('.admin/config.inc'));
require(FileUp2('.admin/db/db_posta_importer.inc'));

set_time_limit(0);
require(FileUp2('html_header_full.inc'));


if (!$imp) {
  echo "<h1>Dostupné importery</h2>";
  echo '<a href=index.php?imp=cerge>cerge</a>';
  require(FileUp2('html_footer.inc'));
  Die();
}

else {
  $dir = 'spisovky/' . $imp;
  $files = scandir($dir);
  foreach ($files as $file)
    if ($file<>'.' && $file<>'..') include($dir . '/' . $file);

}

require(FileUp2('html_footer.inc'));