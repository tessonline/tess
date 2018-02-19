<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));


echo '<h1>Načtení pomocí čárového kódu:</h1>';
echo '<table border=0><tr><td width="50%" valign="top">';
echo ' <div class="form darkest-color">
  <div class="form-body"><table><tr><td valign="top">Zadejte čárový kód obálky:<br/><textarea id="carKod" rows="3" cols="50" onkeypress="NactiEed(this,event);"></textarea></td><td valign="top">
  <div id="hledamCK" style="visibility:hidden">Hledám...</div>
  </td></tr></table>
    <br/><div id="span_text_CK"></div>
</div></div>';
echo '</td><td width="50%" valign="top">';
echo ' <div class="form darkest-color">
  <div class="form-body"><table><tr><td valign="top">Zadejte čárový kód z frankovacího stroje:<br/><textarea id="carKod2" rows="3" cols="70" onkeypress="Nacti(this,event);" disabled></textarea></td><td valign="top">
  <div id="hledam" style="visibility:hidden">Hledám...</div>
  <div id="span_text_CK"></div>
  <input type="hidden" name="DOC_ID" id="DOC_ID" value="0">
  </td></tr></table>
      <br/><div id="span_text_CK2"></div>
</div></div>';

echo '</td></tr></table>';
//echo '<p align="left"><input type="button" class="button btn" onClick="window.close();" value="   Zavřít okno   "></p>';

?>
<iframe id='ifrm_get_value' name='ifrm_get_value' style='position:absolute;z-index:0;left:10;top:10;visibility:hidden'></iframe>

<script>
function NactiEed(test,e) {
  if (e.keyCode == 13) {
    document.getElementById('hledamCK').style = 'block';
    var data = test.value.replace(new RegExp('\r?\n','g'), '');
    window.open('getCK.php?id='+data,'ifrm_get_value');
    window.focus();
  }
}
function Nacti(test,e) {
  if (e.keyCode == 13) {
    document.getElementById('hledam').style = 'block';
    var data = test.value.replace(new RegExp('\r?\n','g'), '|');
    window.open('parseCK.php?data='+data+'&id='+document.getElementById('DOC_ID').value,'ifrm_get_value');
    window.focus();
  }
}
</script>



<?php
require(FileUp2("html_footer.inc"));

