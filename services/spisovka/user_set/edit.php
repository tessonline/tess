<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_full.inc"));

require(FileUp2(".admin/brow_.inc"));

$GLOBALS['CAST'] = 1;
Form_(array("showaccess"=>true, "nocaption"=>false));

echo "<script>

  function showChecksTable(check) {
    if (check.checked) {
      $('input[name*=\"TABLE[\"]').attr(\"disabled\", true);
      $('input[name*=\"TABLE[\"]').attr(\"title\", \"Lze vybrat jen, pokud je vypnutá volba 'Zobrazovat detaily čj. v přehledu'\");
    }
    else {
      $('input[name*=\"TABLE[\"]').removeAttr(\"disabled\");
    }
  }
  showChecksTable(document.frm_edit.UKAZOVAT_OBALKY);
</script>";

require(FileUp2("html_footer.inc"));
?>
