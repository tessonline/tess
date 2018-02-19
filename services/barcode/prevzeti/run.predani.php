<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

$GLOBALS["ODESLANA_POSTA"] = ($GLOBALS["SMER"]==1?'f':'t');

require_once(FileUp2('.admin/oth_funkce_2D.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

//print_r($referent);
if ($GLOBALS['SMER'] == 1) {
  $prevzeti = 'Převzetí';
  $prevzit = 'PŘEVZÍT';
  $prebirajici = 'Přebírající';
}
else {
  $prevzeti = 'Předání';
  $prevzit = 'PŘEDAT';
  $prebirajici = 'Předávající';
}


UNSET($GLOBALS['ODBOR']);
echo '<h1>'.$prevzeti.' pomocí čárového kódu:</h1>';
echo ' <div class="form darkest-color">

<table border=0 cellpadding=5 width="100%"><tr><td valign="top" width="10%">
  <div class="form-body">Sejměte čárový kód:<br/><textarea id="carKod" rows="3" cols="45" onkeypress="Nacti(this,event);"></textarea>&nbsp;&nbsp;&nbsp;</td>
  <td valign="center">&nbsp;&nbsp;&nbsp;Výsledek:
  <table cellpadding=10><tr>
    <td valign="top" NOWRAP><span id="image_ok" style="display:none"><img src="'.FileUpImage('images/ok').'" style="background:green;">
   </td>
    <td valign="top" NOWRAP></span><span id="image_error" style="display:none"><img src="'.FileUpImage('images/remove').'" style="background:red;"></span>
   </td>
    <td valign="top">
    <b>ID:</b>&nbsp;<span id="span_ID_CK"></span><br/>
    <b>Adresát:</b>&nbsp;<span id="span_adresat_CK"></span><br/>
    <b>Věc:</b>&nbsp;<span id="span_vec_CK"></span><br/>
    <b>Stav:</b>&nbsp;<span id="span_text_CK"></span>
    <div id="hledam" style="visibility:hidden">Hledám...</div>
  </td></tr></table>

</td></tr></table>

';

echo '</select>&nbsp;&nbsp;&nbsp;';
echo '<input type="hidden" name="PREDAT_ID" id="PREDAT_ID">';
echo '<input type="hidden" name="SMER" value="'.$GLOBALS['SMER'].'">';

echo'</form>';

echo '</div></div></div>';

echo '<input type="button" name="SEND" value =" Obnovit " class="btn" onclick="document.location.reload()">';

echo "
<iframe id='ifrm_get_value' name='ifrm_get_value' style='position:absolute;z-index:0;left:10;top:10;visibility:hidden'></iframe>";
?>
<script>
window.onload = function() {
  var input = document.getElementById("carKod").focus();
}

function Nacti(test,e) {
  if (e.keyCode == 13) {
    document.getElementById('hledam').style = 'block';
    var data = test.value.replace(new RegExp('\r?\n','g'), '|');
    window.open('getCK.php?smer=<?php echo $GLOBALS['SMER'];?>&odbor=<?php echo $_GET['ODBOR'];?>&id='+data,'ifrm_get_value');
    window.focus(); 
  }
}
</script>

<?php
require(FileUp2("html_footer.inc"));
