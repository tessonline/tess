<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
include_once(FileUp2('.admin/oth_funkce_2D.inc'));
require(FileUp2("html_header_title.inc"));

include_once(FileUp2(".admin/javascript.inc"));

Form_(array("showaccess"=>true,));
if (!HasRole('cteni_zpracovatel'))
echo '<script>
  UkazPracovnika(document.frm_edit.ODBOR,"REFERENT");</script>
</script>
';
require(FileUp2("html_footer.inc"));
?>
