<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
//require(FileUp2("html_header_title.inc"));
require(Fileup2('html_header_full.inc'));

$co=StrTok($GLOBALS["QUERY_STRING"], '&');
if ($app == 'import') {
  Form_(array("showaccess" => true,"script_extension" => $app . ".php", "method"=>"POST","myform_schema"=>".admin/form_schema_import.inc" ));
  echo '<table height="400"><tr><td><p></p></td></tr></table>';
  require(FileUp2("html_footer.inc"));
  Die();
}
if ($app == 'csv') {
  Form_(array("showaccess" => true,"script_extension" => $app . ".php", "method"=>"POST","myform_schema"=>".admin/form_schema_csv.inc" ));
  require(FileUp2("html_footer.inc"));
  Die();
}


If ($co<>"edit") {
    Access(array('agenda'=>'POSTA'));
    Form_(array("showaccess" => true));
}
else
  Form_(array("showaccess" => true,"myform_schema"=>".admin/form_schema_spisovna.inc"));

?>
<link rel="stylesheet" href="jquery-ui.css">

<style>

.ui-helper-hidden-accessible {
    border: 0;
    clip: rect(0 0 0 0);
    height: 1px;
    margin: -1px;
    overflow: hidden;
    padding: 0;
    position: absolute;
    width: 1px;
}
.ui-autocomplete {
     z-index: 9999 !important;
}

</style>
<script>
$(function() {
    $( "#txtAuto" ).autocomplete({
        source: "getLokace.php?spisovna_id=<?php echo $GLOBALS['SPISOVNA_ID']; ?>",
        minLength: 3,
        select: function( event, ui ) {
            if(ui.item) {
                $("#LokaceId").val(ui.item.id);
            }
        },
        change: function(event, ui) {
            if(!ui.item) {
                $("#LokaceId").val(0);
                $(this).val("");
            }
        }
    });
});
</script>
<?php

if ($co=='filter') {
  unset($_SESSION['SESSION_SPISOVNA_ID']);
 echo "<script>DruhAdresataFilter('')</script>";
}



require(FileUp2("html_footer.inc"));
?>
