<?php
require("tmapy_config.inc");
require(FileUp2(".admin/history_.inc"));
require(FileUp2("html_header_full.inc"));


//$uplobj=Upload(array('create_only_objects'=>true,'noshowheader'=>true));

$cj_obj = LoadClass('EedCj', $GLOBALS['HISTORY_ID']);
$caption = $cj_obj->cislo_jednaci;
echo '<h1 align="center">'.$caption.'</h1>';
if (!$show_old) $show_old = false;
if ($typ=='SPIS') {$where.=" and typ like 'SPIS'";}

$q = new DB_POSTA;
$q->query('select * from posta_transakce where doc_id in ('.$GLOBALS['HISTORY_ID'].') '.$where.' order by id desc');
if ($q->Num_Rows() == 0 || $show_old) {
  echo '<p><input type="button" class="btn" onclick="document.location.href=\'history.php?HISTORY_ID=' . $GLOBALS['HISTORY_ID'] . '&show_old=1\'" value="Zobrazit transakční protokol"></p>';
  History(array('table_schema_file'=>'.admin/table_schema_simple.inc'));
}
else {
  echo '<p><input type="button" class="btn" onclick="document.location.href=\'history.php?HISTORY_ID=' . $GLOBALS['HISTORY_ID'] . '&show_old=1\'" value="Zobrazit podrobnější (DB) historii"></p>';
  $count = Table(array(
    'tablename' => 'history',
    'sql' => 'select * from posta_transakce where doc_id in ('.$GLOBALS['HISTORY_ID'].') '.$where.' order by id desc',
    'setvars' => true,
    'caption' => 'Transakční protokol - provedené změny',
    'appendwhere' => $where,
    'schema_file' => '.admin/table_schema_history.inc',
    'showinfo' => false,
    'showedit' => false,
    'showdelete' => false,


  ));
}

require(FileUp2("html_footer.inc")); 
?>
