<?php
require('tmapy_config.inc');
include_once(FileUp2('.admin/brow_.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
include_once(FileUp2('.admin/el/of_select_.inc'));
require(FileUp2("html_header_full.inc"));
Access(array('agenda'=>'POSTA'));

$ofselect = $_GET['ofselect'];

?>
  <script language="JavaScript" type="text/javascript">
	  var hodnota;
  	hodnota = $('select[name=HODNOTA]', window.parent.document);
	  if (hodnota.length ==0) {
    		hodnota = $('input[name=HODNOTA]', window.parent.document);
    		//alert(hodnota.length);
	  }
	</script>
<?php 
if ($ofselect == "undefined") {
  //element je pouhy text
  ?>
  	<script language="JavaScript" type="text/javascript">
			hodnota.replaceWith('<input name="HODNOTA" value="" type="text" maxlength="100" size="100" id="5">');
  	</script>
  <?php 
} else {
  //element je select
  $params = array(
    "name" => "HODNOTA",
    "enable_disabled" => true,
    "fullselect" => true,
  );
  $classname = "of_".$ofselect;
  $val = new $classname($params);
  $x = 5;
  $select = $val->self_get("", "", $x);
  $select = str_replace("\n", '', $select);
  ?>
  <script language="JavaScript" type="text/javascript">
		hodnota.replaceWith('<?php echo $select; ?>')
  </script>
  <?php 
}

require(FileUp2("html_footer.inc"));
