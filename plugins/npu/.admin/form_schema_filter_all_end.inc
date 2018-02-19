<?php
$FORM_CONFIG['schema'][] = array(
  'label' => 'Rejst.číslo, ukl. značka',
  'visible' => true,
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'column' => 1,
      )
    )
  )
);


  $FORM_CONFIG["schema"][] = array("elements"=>array(
      array( "type"=>"text_number","name"=>"PAMATKA_REJSTRC_TEXT","size"=>10,"label"=>"Část rejstř. čísla před lomítkem"),
      array( "type"=>"text_number","name"=>"PAMATKA_IDREG_TEXT","size"=>10,"label"=>"PrStavId hodnota"),
    ),
    "format"=>"'Rejsříkové&nbsp;číslo:(před&nbsp;lomítkem)&nbsp;'...PAMATKA_REJSTRC_TEXT...'&nbsp;&nbsp;&nbsp;IdReg:&nbsp;'...PAMATKA_IDREG_TEXT",
    "label"=>"Vyhledání dle památky:"
  );

  $FORM_CONFIG["schema"][] = array("elements"=>array(
    array( "type"=>"text", "name"=>"ZNACKA_ID_AUTOCOMPLETE", 'size'=>50, 'add'=>'id="txtAuto"'),
    array( "type"=>"hidden", "name"=>"ZNACKA_ID", 'add'=>'id="znackaId"')
//        array( "type"=>"text","name"=>"UKLADACI_ZNACKA_TEXT","size"=>80)
    ),
    "label"=>"Ukládací značka:"
  );

?>
<script>
$(function() {
    $( "#txtAuto" ).autocomplete({
        source: "/ost/posta/plugins/npu/services/spisovka/ukladaci_znacky/getMarksByName.php",
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
<link rel="stylesheet" href="/ost/posta/plugins/npu/services/spisovka/ukladaci_znacky/jquery-ui.css">
