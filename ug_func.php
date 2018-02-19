<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/upload_.inc"));
include_once(FileUp2("interface/.admin/upload_funkce.inc"));

if ($cmd == 'convert') {
  echo 'Jdeme konvertovat<br/>';
  $upl = LoadClass('EedUpload', $DOC_ID);
  foreach($upl->uplobj_records as $file) {
    if ($file['ID'] == $RECORD_ID) {
      if (!$a = $upl->ConvertFile($file['NAME'])) {
         include(FileUp2('html_header_full.inc'));
         echo "<font color=red>soubor se nepovedlo přeložit, proveďte konverzi ručně.</font>";
         echo '<p><input type="button" onclick="window.opener.document.location.reload();" value="   Zavřít   " class="btn"></p>';
         include(FileUp2('html_footer.inc'));
         Die();
      }
      else {

        echo 'Konverze hotova';
        include(FileUp2('html_header_full.inc'));
        echo '<script>';
        echo 'window.opener.document.location.reload();';
        echo 'window.close();';
        echo '</script>';
      }
    }
  }

}

if ($cmd == 'KonvezeEL') {

}
