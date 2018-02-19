<iframe id="ifrm_get_value" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden" src="get_value.php">blabla</iframe>

<script language="JavaScript" type="text/javascript">
<!--
function ChangeZakazka(el) {

// newwindow = window.open('get_value.php?type=SUBZAK&ODBOR='+document.forms[0].ODBOR.value, 'ifrm_get_value', 'height=0px,width=0px,left=0,top=0,scrollbars,resizable');
//  newwindow.focus();
  
//  var ifrm = window.document.getElementById("ifrm_get_value");
//  ifrm.src = "get_value.php?type=SUBZAK&ODBOR="+el.options[el.selectedIndex].value;
  var ifrm = window.document.getElementById("ifrm_get_value");
  ifrm.src = "../get_value.php?type=SUBZAK&ODBOR="+el.options[el.selectedIndex].value;
  
  
}
//-->
 
</script>

<?php
   $FORM_CONFIG["schema"][] = array("label"=>"Adresáti:");		
    $FORM_CONFIG["schema"][] = array("elements"=>array(
              array( "type"=>"select_odbor", "name"=>"ODBOR2","extrahtml"=>"onchange=\"ChangeZakazka(this)\""),
              array( "type"=>"select_referent", "name"=>"REFERENT2","insertnull"=>true),
              array( "type"=>"hidden", "name"=>"PRIJEMCI","value"=>$GLOBALS["prijemci"]),
              ),
              "format"=>"ODBOR2...'&nbsp;&nbsp;&nbsp;{$GLOBALS["CONFIG"]["NAZEV_REFERENT"]}:&nbsp;<span id=\"REF2_span\">'...REFERENT2...'</span>'",
              "label"=>"Odbor:");							
?>
