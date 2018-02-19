<?php
require("tmapy_config.inc");

$q = new DB_POSTA;

$sql = "SELECT * FROM posta_spisovna_cis_lokace WHERE id_parent = '".$GLOBALS["DELETE_ID"]."' ";
$q->query($sql);
if($q->next_record()) $smaz = FALSE;
else $smaz = TRUE;

if($smaz === FALSE) {
  require_once(FileUp2("html_header_full.inc"));
  echo "Lokace má alespoň jednu podlokaci.<br />
        Pro smazání záznamu, nejdříve odstraňte všechny dokumenty v dané lokaci.
        <br /><br />";
  echo '<button class="btn" onclick="parent.$.fancybox.close()">Zavřít okno</a>';
  require_once(FileUp2("html_footer.inc"));
}
else {
  require(FileUp2(".admin/delete_.inc"));
}