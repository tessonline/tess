<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(Fileup2('html_header.inc'));
//<script src="/tmapy/lib/jquery/1.7/jquery-1.7.min.js"></script>
//<script src="/tmapy/lib/jqueryui/1.8/jquery-ui.min.js"></script>

?>
<link rel="stylesheet" href="/ost/posta/plugins/npu/services/spisovka/ukladaci_znacky/jquery-ui.css">
<style>
.ui-autocomplete-loading { background: white url('ui-anim_basic_16x16.gif') right center no-repeat;
}
.ui-autocomplete { position: absolute; cursor: default;z-index:30 !important;}
.shadow {
  -moz-box-shadow:    2px 2px 2px 1px #ccc;
  -webkit-box-shadow: 2px 2px 2px 1px #ccc;
  box-shadow:         2px 2px 2px 1px #ccc;
}

</style>
<script>
$(function() {
    $( "#txtAuto" ).autocomplete({
        source: "getMarksByName.php",
        minLength: 3,
        select: function( event, ui ) {
            //alert(ui.item.id + ui.item.value);
            if(ui.item)
                $("#znackaId").val(ui.item.id);
        },
        change: function(event, ui) {
            if(!ui.item) {
                $("#znackaId").val(0);
                $(this).val("");
            }
        }
    });
});
</script>
</head>
<body>
<?php

Form_(array("showaccess"=>true, "nocaption"=>false));
echo '<table height=400><tr><td valign=top>
<input type="hidden" name="znackaId" id="znackaId">
';
echo '</td></tr></table>';
require(FileUp2("html_footer.inc"));

