<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/properties.inc"));
include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select.inc");
include_once($GLOBALS["TMAPY_LIB"]."/security/main.inc");
require_once(FileUp2(".admin/el/of_select_.inc"));

$sql="SELECT id,lname, fname FROM security_user WHERE active ORDER BY lname";
$a = new DB_POSTA;
$a->query($sql);

//$mo = getSelectData(new of_select_multiodbor(array()));
$mo = getSelectData(new of_select_spisuzly(array()));
//$ref = getSelectData(new of_select_referent(array()));
 
$text='<br/><select name="VNITRNI_POSTA_ODBOR['.$cislo.']"  onChange="ChangeZakazka(this,'.$cislo.')"><option value=""></value>';
while (list($key,$val)=each($mo))
  $text.='<option value="'. $key.'">'.$val.'</option>';
$text.='</select>&nbsp;&nbsp;&nbsp;&nbsp;Zpracovatel:&nbsp;&nbsp;<span id="REF2_'.$cislo.'_span"><select name=\"VNITRNI_POSTA_REFERENT[$cislo]\">';
$text.='<option value=""></option>';
while ($a->Next_Record())
  $text.='<option value="'. $key.'">'.$val.'</option>';
$text.='</select></span>';
$cislo=$cislo+1;
$text.='</span><br/><span id="adresat'.$cislo.'"><input type="button" id="pridat_adresata" class="button" value="Přidat adresáta" onclick="PridatVnitrnihoAdresata('.$cislo.')">';
echo '<script>
  window.parent.document.getElementById(\'adresat'.($cislo-1).'\').innerHTML = \''.$text.'\'
</script>
';
