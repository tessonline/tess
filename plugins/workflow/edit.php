<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));
require_once(FileUp2(".admin/el/of_select_.inc"));

?>
<link rel="stylesheet" href="/theme/square/plugins/jquery-ui/jquery-ui-1.10.3.custom.min.js">
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
        source: "getName.php",
        minLength: 3,
        select: function( event, ui ) {
            //alert(ui.item.id + ui.item.value);
            if(ui.item) {
                $("#userId").val(ui.item.id);
                var zpracovatele = $("[name=SCHVALUJICI_ID]");
                zpracovatele.append('<option value="'+ui.item.id+'" selected="selected">'+ui.item.value+'</option>');
            }
        },
        change: function(event, ui) {
            if(!ui.item) {
                $("#userId").val(0);
                $(this).val("");
            }
        }
    });
});

</script>
</head>
<body>
<?php


/*$GLOBALS['referent'] = getSelectDataEed(new of_select_referent(array('fullselect'=>true)));

function ukazJmeno($ref_id) {
  $ret = $GLOBALS['referent'][$ref_id];
  if (!$ret) $ret = $ref_id;
  return $ret;
}
*/



Form_(array("showaccess" => true));

require(FileUp2("html_footer.inc"));

require_once('.admin/javascript.inc');

if ($GLOBALS['ID_WORKFLOW'] != 2) {
?>
<script type="text/javascript">
jQuery(window).load(function () {
		// $( "input[name='SCHVALUJICI_TEXT']" ).closest( "div[class='form-row']" ).css( "display", "none" );
		// $( "select[name='TYPSCHVALENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );
		// $( "select[name='SCHVALUJICI_ID']" ).closest( "div[class='form-row']" ).css( "display", "none" );
	WorkflowChange(<?php echo $GLOBALS['ID_WORKFLOW'];?>);
});
</script>
<?php 
} else {
  ?>
<script type="text/javascript">
jQuery(window).load(function () {
	// $( "select[name='SCHVALUJICI_ID']" ).closest( "div[class='form-row']" ).css( "display", "none" );
	// $( "select[name='PROMENNA']" ).closest( "div[class='form-row']" ).css( "display", "none" );
	// $( "input[name='HODNOTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );
	WorkflowChange(<?php echo $GLOBALS['ID_WORKFLOW'];?>);
});
</script>
<?php
}
