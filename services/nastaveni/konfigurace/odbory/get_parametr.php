<?php
require("tmapy_config.inc");
include_once(FileUp2(".admin/brow_.inc"));
include_once ($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once (FileUp2('.admin/el/of_select_.inc'));
include_once(FileUp2("posta/.admin/el/of_select_.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2("html_header_full.inc"));

$parametry = getSelectDataEed(new of_select_nastaveni_kategorie_parametr(array("kategorie"=>$kategorie)));
if (count($parametry)>0) {

   foreach($parametry as $key => $val) {
    $opt .= "<option value=\"" . $key ."\">" . $val ."</option>";
    $a ++;
  }


  $subzak = str_replace("'","",$opt);
}
else {
  $subzak = '';
}
    ?>
    <script language="JavaScript" type="text/javascript">
    <!--
       if ($('select[name=PARAMETR]', window.parent.document)) {
         var skar = $('select[name=PARAMETR]', window.parent.document);
         skar.empty();
         skar.append('<?php echo $subzak;?>');
       }
    //-->
    </script>
    <?php

require(FileUp2("html_footer.inc"));
?>

