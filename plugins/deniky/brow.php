<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('html_header_full.inc'));
?>
<script type="text/javascript">
  function insert(script) {
    window.top.panel.NewWindow(script);
  }
</script>
<?php
$denik = array();
$denik[] = array(
  'ID'=>1,
  'NAZEV' => 'Hlavní evidence'
);

$sql = 'select * from posta_cis_deniky where aktivni=1 order by id asc';
$q = new DB_POSTA;
$q->query($sql);
while ($q->Next_Record()) {
  $id = $q->Record['ID'];
  $denik[$id]['ID']= $id;
  $denik[$id]['NAZEV']= $q->Record['NAZEV'];
}

include_once $GLOBALS["TMAPY_LIB"] . '/db/db_array.inc';
$db_arr = new DB_Sql_Array;
$db_arr->Data = $denik;

Table(
  array(
    'db_connector' => &$db_arr,
    'showaccess' => true,
    'showinfo' => false,
    'showedit' => false,
    'showdelete' => false,
    'showcount' => false,

    'caption' => 'Vyberte evidenci, do které chcete zapsat'
  )
);

require(FileUp2('html_footer.inc'));
