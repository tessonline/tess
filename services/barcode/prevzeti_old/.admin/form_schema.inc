<script>
function Ukaz(a)
{
  var pole=a.value.split(str.indexOf("\n"));
  document.getElementById('text_cisla').innerHTML = pole[1];
  //alert(a.value);
}
</script>
<?php

$GLOBALS['ODBOR'] = VratOdbor();
if (!$GLOBALS['smer']) $GLOBALS['smer'] = 1;

  $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"select_vsechny_spisuzly", "name"=>"ODBOR","insertnull"=>false,"required"=>true, "not_disabled"),
            array( "type"=>"hidden", "name"=>"SMER","value"=>$GLOBALS["smer"]),
            ),
            "label"=>"Spisový uzel:");
            
            
//,"extrahtml"=>"onkeyup=Ukaz(this);"            
/*
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"textarea", "name"=>"CISLA","rows"=>25,"cols"=>15),   
            ),
            "format"=>"CISLA...'&nbsp;<span id=\"text_cisla\"></span>'",   
            "label"=>"Předaná čísla:");		
*/
/*
 $FORM_CONFIG["schema"][] = array("elements"=>array(
            array( "type"=>"text", "name"=>"CISLA[]","size"=>20,"extrahtml"=>"onblur=Ukaz(this);"),   
            ),
            "format"=>"CISLA[]...'&nbsp;<span id=\"text_cisla\"></span>'",   
            "label"=>"Předaná čísla:");		
*/

            $FORM_CONFIG['schema'][] = '&nbsp;';
            
         
$FORM_CONFIG["schema"][] = array("elements"=>array(
       array( "type"=>"button", "name" => "btn_dalsi", "value"=>"Další","onclick"=>"document.frm_edit.submit();"),
     //  array( "type"=>"button", "name" => "btn_close", "value"=>"Zavřít","onclick"=>"parent.$.fancybox.close();"),
       ),
       'format' => 'btn_dalsi...\'&nbsp;&nbsp;&nbsp;\'...btn_close',
       );
?>
