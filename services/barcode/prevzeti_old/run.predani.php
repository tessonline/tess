<?php
session_start();
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

$GLOBALS["ODESLANA_POSTA"] = ($GLOBALS["SMER"]==1?'f':'t');

$user_obj = LoadClass('EedUser',$USER_INFO['ID']);
$EddSql = LoadClass('EedSql',$USER_INFO['ID']);

$podrizene_unity = $user_obj->VratPodrizeneUnity($GLOBALS['ODBOR']);
$where_app = $EddSql->WhereOdborAndPrac($GLOBALS['ODBOR']);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];

$where_app2 = '';
if ($GLOBALS['SMER'] == 1) {
  $where_app2 = " AND STATUS IN (5,6,7) AND DATUM_PREDANI is null";

  $prevzeti = 'Převzetí';
  $prevzit = 'PŘEVZÍT';
  $prebirajici = 'Přebírající';
}
else {
  $where_app2 = " AND datum_vypraveni is null AND STATUS IN (8,12) and odesl_prijmeni not like '%VITA%' and vlastnich_rukou like '1' and odes_typ<>'Z' AND DATUM_PREDANI_VEN is null";

  $prevzeti = 'Předání';
  $prevzit = 'PŘEDAT';
  $prebirajici = 'Předávající';
}

require_once(FileUp2('.admin/oth_funkce_2D.inc'));
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once(FileUp2('.admin/el/of_select_.inc'));

$referenti = getSelectDataEed(new of_select_referent(array()));

//print_r($referent);

UNSET($GLOBALS['ODBOR']);
echo '<table><tr>';

echo '<td width="60%" valign="top">
<h1>'.$prevzeti.' pomocí výběru:</h1>';
$count = Table(array(
  'agenda' => 'POSTA',
  'showdelete' => false,
  'tablename' => 'posta',
  'appendwhere' => "and (".$where_app.")" . $where_app2,
  'showedit' => false,
  'showinfo' => false,
  'setvars' => true,
  'showselect' => true,
  'maxnumrows' => 500,
  'page_size' =>500,
  'multipleselect' => true,
  'multipleselectsupport' => true,
  'schema_file' => GetAgendaPath('POSTA') . '/.admin/table_schema_simple.inc',
));

echo '</td><td valign="center">nebo</td><td width="40%" valign="top">';
echo '<h1>'.$prevzeti.' pomocí čárového kódu:</h1>';
echo ' <div class="form darkest-color">


  <div class="form-body"><table><tr><td valign="top"><textarea id="carKod" rows="20" cols="15" onkeypress="Nacti(this,event);"></textarea></td><td valign="top">
  <div id="span_text_CK"></div>
  <div id="hledam" style="visibility:hidden">Hledám...</div>
  </td></tr></table></div></div>';
echo '</td></tr></table>';

echo '<div class="form darkest-color"> <div class="form-body"> <div class="form-row">';

echo '<form method="POST" action="run.php" onSubmit="if (Send()) return true; else return false; ">';
echo '<p>'.$prebirajici.' osoba:&nbsp;<select name="PREBRAL_ID" id="PREBRAL_ID"><option value=""></option>';
foreach($referenti as $key => $jmeno)
  if (strlen($jmeno)>5) {
    if ($key == $id_user) $selected = 'SELECTED'; else $selected = '';
    echo '<option value="' . $key . '" ' . $selected . '>' . $jmeno . '</option>';

  }
echo '</select>&nbsp;&nbsp;&nbsp;';
echo '<input type="hidden" name="PREDAT_ID" id="PREDAT_ID">';
echo '<input type="hidden" name="SMER" value="'.$GLOBALS['SMER'].'">';
echo '<input type="submit" name="SEND" value =" '.$prevzit.' DOKUMENTY " class="btn">';

echo'</form>';

echo '</div></div></div>';
echo "
<iframe id='ifrm_get_value' name='ifrm_get_value' style='position:absolute;z-index:0;left:10;top:10;visibility:hidden'></iframe>";
?>
<script>
function Nacti(test,e) {
  if (e.keyCode == 13) {
    document.getElementById('hledam').style = 'block';
    var data = test.value.replace(new RegExp('\r?\n','g'), '|');
    window.open('getCK.php?smer=<?php echo $GLOBALS['SMER'];?>&odbor=&id='+data,'ifrm_get_value');
    window.focus(); 
  }
}

function Send() {
  var ids = document.querySelectorAll('input[name="SELECT_IDposta[]"]:checked');
//  var ids = document.querySelector('input:checked');
  if (ids) {
    if (ids.length == 0) {
      alert('Vyberte dokumenty pro předání.');
      return false;
    }
     var action = '';
     for (i=0; i<ids.length; i++){
           action = action + ',' + ids[i].value;
     }
     document.getElementById('PREDAT_ID').value = action;
  } else {
    alert('Vyberte dokumenty.');
    return false;
  }

  if (!document.getElementById('PREBRAL_ID').value) {
    alert('Vyberte osobu, která přebírá dokumenty.');
    return false;
  }
  return true;
}

</script>

<?php
require(FileUp2("html_footer.inc"));
