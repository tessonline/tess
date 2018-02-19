<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));

require(Fileup2('html_header.inc'));
?>
<link rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.16/themes/base/jquery-ui.css">
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.6.2/jquery.min.js"></script>
<script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.8/jquery-ui.min.js"></script>

</head>
<body>

<div class="demo">

<div class="ui-widget">
	<label for="birds">Birds: </label>
	<input id="birds" />
</div>

<div class="ui-widget" style="margin-top:2em; font-family:Arial">
	Result:
	<div id="log" style="height: 200px; width: 300px; overflow: auto;" class="ui-widget-content"></div>
</div>

</div><!-- End demo -->



<style>
.ui-autocomplete-loading { background: white url('ui-anim_basic_16x16.gif') right center no-repeat; }
</style>
<script>
$(function() {
    function log( message ) {
        $( "<div/>" ).text( message ).prependTo( "#log" );
        $( "#log" ).scrollTop( 0 );
    }

    $( "#birds" ).autocomplete({
        source: "search.php",
        minLength: 2,
        select: function( event, ui ) {
            log( ui.item ?
                "Selected: " + ui.item.value + " aka " + ui.item.id :
                "Nothing selected, input was " + this.value );
        }
    });
});
</script>


<?php
require(FileUp2("html_footer.inc"));
