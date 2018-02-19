<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
//require(FileUp2("html_header_full.inc"));
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2("html_header_title.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));
include_once(FileUp2(".admin/security_name.inc"));
?>

<script type="text/javascript">
	$(':checkbox:checked',window.parent.document).each(function() {
		$(this).prop('checked', false);
	});
</script>
<?php 

$q = new DB_POSTA;

$sql="select spis,posta_id from posta_pristupy where access='$pristup' and odbor=$uzel ";
if ($zpracovatel!="")
$sql.= " and referent=$zpracovatel";
//else $sql.= " and odbor=$uzel and referent = null";
else $sql.= " and referent is null";

$q->query($sql); 
while ($q->next_record()) {
  $posta_id = $q->Record["POSTA_ID"];
  ?>
  <script type="text/javascript">
  var posta_id = <?php echo $posta_id;?>;
  	var checkbox = $( "#"+posta_id ,window.parent.document);
  	checkbox.prop('checked', true);
  </script>
  <?php 
  if ($q->Record["SPIS"]==1) {
    ?>
    <script type="text/javascript">
		  $(".brow-main",window.parent.document).hide();
		  $("[name='RANGE']",window.parent.document).val('C'); 
    </script>
    <?php 
  } else {
    ?>
    <script type="text/javascript">
      $(".brow-main",window.parent.document).show();
  	  $("[name='RANGE']",window.parent.document).val('V'); 
    </script>
    <?php
  }
}
require(FileUp2("html_footer.inc"));
?>

