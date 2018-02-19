<?php
require('tmapy_config.inc');
include_once(FileUp2('.admin/brow_.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
include_once(FileUp2('.admin/el/of_select_workflow.inc'));
require(FileUp2("html_header_full.inc"));

$params = array(
  'workflow' => $_GET['WORKFLOW'],
  'dokument' => $_GET['DOKUMENT'],
);

$val = new of_select_promenna($params);

$opt = "";
foreach ($val->options as $option) {
  $opt .= "<option value=\"".$option['value']."\">".$option['label']."</option>";
}

?>
    <script language="JavaScript" type="text/javascript">
       if ($('select[name=\'<?php echo $vysledek;?>\']', window.parent.document)) {
         var select = $('select[name=\'<?php echo $vysledek;?>\']', window.parent.document);
         select.empty();
         select.append('<?php echo $opt;?>');
       }
    </script>
<?php

require(FileUp2("html_footer.inc"));
