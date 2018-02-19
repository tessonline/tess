<?php
require('tmapy_config.inc');
require_once(FileUp2('.admin/config.inc'));
require_once(FileUp2('.config/config.inc'));
require(FileUp2('.admin/brow_.inc'));
require_once(FileUp2('.admin/security_obj.inc'));
require_once(FileUp2('.admin/security_name.inc'));
require_once(Fileup2('html_header_title.inc'));
include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select.inc");
require_once(FileUp2(".admin/el/of_select_.inc"));

echo '
<link rel="stylesheet" href="/tmapy/lib/jqueryui/1.8/jquery-ui.css">
<script src="/tmapy/lib/jquery/1.7/jquery-1.7.min.js"></script>
<script src="/tmapy/lib/jqueryui/1.8/jquery-ui.min.js"></script>
<script type="text/javascript">
  function show(a) {
    var url = "export_"+a.report.value+".php?so="+a.superodbor.value;
//    alert(url);
     document.getElementById(\'upl_wait_message\').style.display = \'block\';
     $( "#tab").load(url);
  }
</script>
 ';


$so = getSelectData(new of_select_superodbor(array()));

echo '<p class="caption">Reporty</a></p>';
echo '<p><form method="GET" onSubmit="show(this); return false;">';
echo '<p>Report pro pracoviště: <select name="superodbor">';
foreach($so as $key => $value) {
  echo '<option value="'.$key.'">'.$value.'</option>';
}
echo '</select></p>';

echo '<p>Report: <select name="report">';
foreach($reporty as $key => $value) {
  echo '<option value="'.$value['key'].'">'.$value['value'].'</option>';
}
echo '</select>';
echo '<input type="submit" value="Spustit report" class="button">';

$img_wait = FileUpUrl('images/progress.gif');

echo '<div id="upl_wait_message" style="display:none"><p><img src="' . $img_wait . '" title="pracuji ..." alt="pracuji ..."></p></div>';
print '<div id="tab">' . "\n";
print '</div>' . "\n";


require(FileUp2('html_footer.inc'));

