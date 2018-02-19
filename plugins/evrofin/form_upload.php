<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
echo '
<form enctype="multipart/form-data" action="'.GetAgendaPath('POSTA_NEOPOST',false,true).'/upload.php" method="post">
<input type="hidden" name="MAX_FILE_SIZE" value="100000">
Vybrat soubor: <input name="userfile" type="file" >
&nbsp;&nbsp;&nbsp;<input type="submit" class="button" value="Odeslat soubor">
</form>
';
require(FileUp2("html_footer.inc"));

?>
