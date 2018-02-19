<?php
if ($_GET['SELECT_ID']) $pole = explode(',', $_GET['SELECT_ID']);
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require(FileUp2(".admin/el/of_select_.inc"));
require(FileUp2("html_header_title.inc"));

$boxy = getSelectDataEed(new of_select_archivni_box(array()));
$boxy_id = array_flip($boxy);

if (!is_array($SELECT_ID)) {
  require(FileUp2("html_footer.inc"));
  Die('Chyba: nenašel jsem spisy, které se budou vkládat do boxu. Nejdříve musíte vybrat spisy, které chcete vložit do krabice.');

}

if (!$_GET['BOX_ID']) {
  echo '<h1>Vyberte box, do kterého chcete vložit spisy</h1>';
  echo '<table width="100%"><tr>';
  foreach($boxy as $key=>$val) {
    $box = LoadClass('EedArchivacniBox', $key);
    echo '<td width="25%" NOWRAP><a href="?BOX_ID=' . $key . '&SELECT_ID=' . implode(',',$SELECT_ID) . '"><img src="/images/select.gif" width=50><br/>' . $box->ev_cislo . '<br/>' . $val
    . '<br/>Skartace:&nbsp;' . $box->skar_znak . '/' . $box->skar_lhuta . '</td>';
    if ($i%4) echo '</tr><tr>';

    $box->PrepocitatArchivaci($key);
    $i++;
  }
  echo '</tr></table>';
}
else {

  foreach($pole as $key => $val) {
    $sql = 'insert into posta_spisovna_boxy_ids (POSTA_ID,BOX_ID) VALUES (' . $val . ',' . $BOX_ID . ')';
    $q = new DB_POSTA;
    $q->query($sql);
    echo $sql.'<br/>';
  }

  $box = LoadClass('EedArchivacniBox', $BOX_ID);
  $box->PrepocitatArchivaci($BOX_ID);


echo '
<script language="JavaScript" type="text/javascript">
<!--
  window.opener.location.reload();
  window.close();
//-->
</script>
';
}

require(FileUp2("html_footer.inc"));

