<?php
echo "<p><form name='frm_change'>";
echo '<input type="hidden" name="REFERENT" value="' . $GLOBALS['REFERENT']. '">';

if ($doc_id>0)
echo '<input type="hidden" name="doc_id" value="' . $doc_id. '">';

echo '<div class="form darkest-color"> <div class="form-body"> <div class="form-row">';

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/brow_filter_start.inc');
		if (File_Exists($file)) include($file);
  }
}

$omez_rok = $GLOBALS['omez_rok'];

echo '<div class="form-item"> <label class="form-label" for="select">Rok:</label> <div class="form-field-wrapper"> <div class="form-field">';
echo '<input type="hidden" name="ORDER_BYdenik" value="' . $GLOBALS['ORDER_BYdenik']. '">';
$rok = getSelectDataEed(new of_select_rok(array()));
echo "<select name = 'omez_rok' class='select' onchange='document.frm_change.submit();'><option value=''></option>";
while (list($key,$val)=each($rok))
  echo "<option value='".$val."' ".($val==$omez_rok?'SELECTED':'').">".$val."</option>";
echo "</select>";
echo '</div> </div> </div>';

// $prac =  getSelectData(new of_select_superodbor(array()));
// echo "&nbsp;&nbsp;&nbsp;<select name='omez_zarizeni' onchange='document.frm_change.submit();'><option value=''></option>";
// while (list($key,$val)=each($prac))
//   echo "<option value='".$key."' ".($key==$GLOBALS['omez_zarizeni']?'SELECTED':'').">".$val."</option>";
// echo "</select>";
//



if ($GLOBALS['ODBOR']>0) {
  $GLOBALS['omez_uzel'] = $GLOBALS['ODBOR'];
}
if (isset($_GET['omez_uzel'])) {

  if (is_array($_GET['omez_uzel'])) $GLOBALS['omez_uzel'] = $_GET['omez_uzel'][0];
  
}


echo '<div class="form-item"> <label class="form-label" for="select">Útvar:</label> <div class="form-field-wrapper"> <div class="form-field">';
// $GLOBALS['SUPERODBOR'] = $GLOBALS['omez_zarizeni'];
if($GLOBALS["CONFIG"]["USE_SUPERODBOR"]) {
  $GLOBALS['SUPERODBOR'] = $GLOBALS['omez_zarizeni'];
}
$odbory = getSelectDataEed(new of_select_vsechny_spisuzly(array()));
//echo '<input type="hidden" name="isLoadedUnit" value="0">';
//echo "<select name = 'omez_uzel' onchange='document.frm_change.submit();' onmousedown='showUnitForm(this);' style='width:100px'><option value=''></option>";
echo "<select name = 'omez_uzel' onchange='document.frm_change.submit();'><option value=''></option>";
$unit_exists = false;
 foreach ($odbory as $key => $val) {
   if ($GLOBALS['omez_uzel']==$key) $unit_exists = true;
    if ((HasRole('zpracovatel') || HasRole('vedouci-odbor')) && $GLOBALS['ODBOR'] == $key) {$disabled='';  $GLOBALS['omez_uzel'] = $key;}
      else $disabled = 'DISABLED';
   if (HasRole('spravce') || HasRole('lokalni-spravce') || HasRole('podatelna')) $disabled = '';
   echo '<option value="'.$key.'" '.($GLOBALS['omez_uzel']==$key?'SELECTED':'').' '.$disabled.'>'.$val.'</option>';
 }
if (!$unit_exists) $GLOBALS['omez_uzel'] = 0; //nekonzistence unit, z brow_func mame unitu, ktera neni v danem selectu
echo "</select>";
echo '</div> </div> </div>';


if (($GLOBALS['ODBOR']>0)&&($GLOBALS['VYHLEDAVANI']!=1)) {
  unset($GLOBALS['ODBOR']);
}
/*if ($GLOBALS['omez_uzel'])
{
  $GLOBALS['ODBOR'] = $GLOBALS['omez_uzel'];
  $prac = getSelectData(new of_select_referent(array()));
  echo "&nbsp;&nbsp;&nbsp;<select name = 'omez_prac' onchange='document.frm_change.submit();'><option value=''></option>";
  foreach ($prac as $key => $val) {
    echo '<option value="'.$key.'" '.($GLOBALS['omez_prac']==$key?'SELECTED':'').'>'.$val.'</option>';
  }
  echo "</select>";
}
*/
$stavy =  getSelectDataFull(new of_select_stavy_filtr(array()));

if (!isset($_GET['omez_stav']) && !isset($GLOBALS['VYHLEDAVANI']) && !isset($GLOBALS['FROM_EVIDENCE'])) { $GLOBALS['omez_stav'] = $GLOBALS['CONFIG_POSTA_DEFAULT']['DEFAULT_STAV']; }

echo '<div class="form-item"> <label class="form-label" for="select">Stav:</label> <div class="form-field-wrapper"> <div class="form-field">';
echo "<select name = 'omez_stav' onchange='document.frm_change.submit();'><option value=''></option>";
foreach($stavy as $stav) {

//   if ($stav['value']>0 && $stav['value']<13) {
//     $pocet = EedTools::UkazPocetDleStatus($stav['value'], $where);
//     echo "<option value='".$stav['value']."' ".($stav['value']==$GLOBALS['omez_stav']?'SELECTED':'')." ".$stav['add']." style=\"".$stav['style']."\">".$stav['label']." (".$pocet.")</option>";
//   }
//   else
    echo "<option value='".$stav['value']."' ".($stav['value']==$GLOBALS['omez_stav']?'SELECTED':'')." ".$stav['add']." style=\"".$stav['style']."\">".$stav['label']."</option>";
}
echo "</select>";
echo '</div> </div> </div>';

//echo '</div> </div> ';

/*
echo "<td rowspan=4 align=right valign=top NOWRAP width='10%'>&nbsp;</td>
<td rowspan=4 align=right valign=top NOWRAP>
naše čj:<input class='select' type='text' class='text' name='X_CISLO_SPISU1_TEXT' id='X_CISLO_SPISU1_TEXT' size='12'><br/>
vaše čj:<input type='text' name='X_JEJICH_CJ' id='X_JEJICH_CJ' size='12'><br/>
věc:<input type='text' name='X_VEC' id='X_VEC' size='12'>
</td>";
echo "</tr></table>    
    
    </span>";
*/


//echo '<div class="form-body"> <div class="form-row">';

echo '<div class="form-item"> <label class="form-label" for="placeholder">JID, čárový kód:</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište JID nebo ČK" type="text" id="X_ID" name="X_ID"> </div> </div> </div>';
echo '<div class="form-item"> <label class="form-label" for="placeholder">Číslo jednací:</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište čj." type="text" id="X_CISLO_SPISU1_TEXT" name="X_CISLO_SPISU1_TEXT"> </div> </div> </div>';
echo '<div class="form-item"> <label class="form-label" for="placeholder">Jejich čj:</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište čj." type="text" id="X_JEJICH_CJ" name="X_JEJICH_CJ"> </div> </div> </div>';
echo '<div class="form-item"> <label class="form-label" for="placeholder">Věc:</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište věc" type="text" id="X_VEC" name="X_VEC"> </div> </div> </div>';
echo '<div class="form-item"> <label class="form-label" for="placeholder">Název spisu:</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište název spisu" type="text" id="X_NAZEV_SPISU" name="X_NAZEV_SPISU"> </div> </div> </div>';

echo '</div> </div> </div>';
echo "<div id='test'></div>";
echo "</form></p>";

echo "
    <script>
    <!--
      function NewWindow(script) {
        newwindow = window.open(script, 'ifrm_get_value','height=550,width=600,left=300,top=50,scrollbars,resizable');
        newwindow.focus();
      }
      function UkazSP(script) {
        window.top.location = script;
      }
  function navigate(e) {
    if (!e) {
      e = window.event;
    }
    if(e.keyCode == 13)  //enter pressed
        Prehled_Vyhledat(this);
  }
  document.onkeypress=navigate;


  function Prehled_Vyhledat(hodnota) {
   if(document.getElementById('wait_label')) document.getElementById('wait_label').style.display = 'block';
    var formular = hodnota.name;
    var frm = document.prehled_vyhledavani;

    var input1 = document.createElement('INPUT');
    var input2 = document.createElement('INPUT');
    var input3 = document.createElement('INPUT');
    var input4 = document.createElement('INPUT');
    var input5 = document.createElement('INPUT');
    var input6 = document.createElement('INPUT');
    input1.setAttribute('type', 'hidden');
    input1.setAttribute('name', 'ID_X');
    input1.setAttribute('value', document.getElementById('X_ID').value);

    input6.setAttribute('type', 'hidden');
    input6.setAttribute('name', 'CISLO_SPISU1_TEXT');
    input6.setAttribute('value', document.getElementById('X_CISLO_SPISU1_TEXT').value);

    input2.setAttribute('type', 'hidden');
    input2.setAttribute('name', 'JEJICH_CJ');
    input2.setAttribute('value', document.getElementById('X_JEJICH_CJ').value);

    input3.setAttribute('type', 'hidden');
    input3.setAttribute('name', 'VEC');
    input3.setAttribute('value', document.getElementById('X_VEC').value);

    input4.setAttribute('type', 'hidden');
    input4.setAttribute('name', 'VYHLEDAVANI');
    input4.setAttribute('value', '1');

    input5.setAttribute('value', document.getElementById('X_NAZEV_SPISU').value)
    input5.setAttribute('type', 'hidden');
    input5.setAttribute('name', 'NAZEV_SPISU_TEXT');

    frm.appendChild(input1);
    frm.appendChild(input2);
    frm.appendChild(input3);
    frm.appendChild(input4);
    frm.appendChild(input5);
    frm.appendChild(input6);
//        document.getElementById(formular).value=hodnota.value;
//       alert(document.getElementById(formular));
    frm.method='GET';
    var act = frm.action;
    frm.action = 'brow.php';
    frm.submit();
  }


  function showUnitForm(a) {
    if (document.frm_change.isLoadedUnit.value == 0) {
       // $('select[name=omez_uzel]').empty();
        $('select[name=omez_uzel]').append('<option value=0 selected=\"selected\"><i>nahrávám...</i></option>');
        $('select[name=omez_uzel]').append('<option value=0 selected=\"selected\"></option>');
        $('select[name=omez_uzel]').append('<option value=0 selected=\"selected\"></option>');
        $('select[name=omez_uzel]').append('<option value=0 selected=\"selected\"></option>');
        $('select[name=omez_uzel]').append('<option value=0 selected=\"selected\"></option>');
        $('select[name=omez_uzel]').append('<option value=0 selected=\"selected\"></option>');
        $('select[name=omez_uzel]').append('<option value=0 selected=\"selected\"></option>');
        $('select[name=omez_uzel]').append('<option value=0 selected=\"selected\"></option>');
        $('select[name=omez_uzel]').append('<option value=0 selected=\"selected\"></option>');
        $('select[name=omez_uzel]').append('<option value=0 selected=\"selected\"></option>');

        $('#test').load('ajax.php?cmd=unity',function() {
//var i = 0;
//$('select[name=omez_uzel]> option').each(function() {
//$(this).css('width',150);
//});


        });
//        $('#test').focus();

    }
  }



    //-->
    </script>
    <form name='prehled_vyhledavani'>
    </form>
    ";

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/brow_filter_end.inc');
		if (File_Exists($file)) include($file);
  }
}

