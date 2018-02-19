<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2(".admin/brow_.inc"));
require(Fileup2('html_header_full.inc'));

EedTools::MaPristupKDokumentu($GLOBALS['POSTA_ID'], 'schvalovani');
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



$id_zal = $GLOBALS['ID'];

$GLOBALS['ID'] = $GLOBALS['POSTA_ID'];
//$GLOBALS['ukaz_ovladaci_prvky'] = false;

iF ($GLOBALS['POSTA_ID']) {
  $table = GetAgendaPath('POSTA') . '/.admin/table_schema_simple.inc';
  Table(
    array(
      'agenda' => 'POSTA',
      'schema_file' => $table,
      'appendwhere' => 'AND p.ID IN ('.$GLOBALS['POSTA_ID'].')',
      'showinfo' => false,
      'showedit' => false,
      'setvars' => true,
      'showcount' => false, //protahuje to tabulku
      'unsetvars' => true,
      'showhistory' => false,
      'caption' => 'Schvalovací proces pro dokument',
      'showdelete' => false));

  $GLOBALS['ID'] = $id_zal;
}

echo "<div>";
Form_(array('showaccess'=>true, 'nocaption'=>true,"noshowclose"=>true,"showbuttons"=>false));
/*
    echo '
<iframe id='ifrm_get_value' name='ifrm_get_value' style='position:absolute;z-index:0;left:10;top:10;visibility:hidden'></iframe>
<script language='JavaScript' type='text/javascript'>
newwindow = window.open(\'zmen.php?co=1\',\'ifrm_get_value2\',\'\');
newwindow.focus();
</script> 
';
*/

echo "</div>";

Table(
  array(
    'showinfo'=>false,
    'caption'=>'Již vybraní schvalovatelé',
    'showedit' => false,
    setvars=>true
  )
);



echo '<input type="button" name="close" value="Zavřít" onclick="window.opener.document.location.reload();" class="btn">';

require(FileUp2('html_footer.inc'));
?>
