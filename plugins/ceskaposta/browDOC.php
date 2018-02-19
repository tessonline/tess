<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

if (!$PROTOKOL_ID) $PROTOKOL_ID = 0;

$where = "AND p.ID IN (select pisemnost_id from posta_cis_ceskaposta_id where protokol_id in ($PROTOKOL_ID))";

$caption = "Seznam všech dokumentů, které odpovídají danému zařazení (včetně vypravení obyčejně)";
$count = Table(
  array(
    'appendwhere' => $where,
    'schema_file' => 'plugins/ceskaposta/.admin/table_schema_posta.inc',
    'agenda' => 'POSTA',
    'caption' => $caption,
    'maxnumrows' => 10,
    'nopaging' => $nopaging,
    'showdelete' => false,
    'showedit' => false,
    'showinfo' => false,
    'showself' => false,
    'nocaption' => false,
    'showaccess' => true,
    'setvars' => true,
  )
);


echo "<a  class=\"btn btn-loading\" href=\"brow.php\" onClick=\"javascript:NewWindowAgendaSpis('edit.php?insert&cacheid=')\">Zpět na přehled</a>";

require(FileUp2("html_footer.inc"));

?>
