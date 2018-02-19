<?php
echo "<p>
<form name='frm_change'>";

echo '<div class="form darkest-color"> <div class="form-body"> <div class="form-row">';

echo '<div class="form-item"> <label class="form-label" for="placeholder">Protokol:</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište(sejměte) číslo protokolu" type="text" id="X_PROTOKOL_TEXT" name="X_PROTOKOL_TEXT"> </div> </div> </div>';
echo '<div class="form-item"> <label class="form-label" for="placeholder">JID, čárový kód:</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište JID nebo ČK" type="text" id="X_ID" name="X_ID"> </div> </div> </div>';
echo '<div class="form-item"> <label class="form-label" for="placeholder">Číslo jednací:</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište čj." type="text" id="X_CISLO_SPISU1_TEXT" name="X_CISLO_SPISU1_TEXT"> </div> </div> </div>';
echo '<div class="form-item"> <label class="form-label" for="placeholder">'.$GLOBALS['CONFIG']['NAZEV_JEJICH_CJ_VYBER'].':</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište čj." type="text" id="X_JEJICH_CJ" name="X_JEJICH_CJ"> </div> </div> </div>';
echo '<div class="form-item"> <label class="form-label" for="placeholder">Věc:</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište věc" type="text" id="X_VEC" name="X_VEC"> </div> </div> </div>';
echo '<div class="form-item"> <label class="form-label" for="placeholder">Název spisu:</label> <div class="form-field-wrapper"> <div class="form-field">
 <input placeholder="zapište název spisu" type="text" id="X_NAZEV_SPISU" name="X_NAZEV_SPISU"> </div> </div> </div>';

echo '</div> </div> </div>';

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
    var input7 = document.createElement('INPUT');
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

    input4.setAttribute('value', document.getElementById('X_PROTOKOL_TEXT').value)
    input4.setAttribute('type', 'hidden');
    input4.setAttribute('name', 'PROTOKOL');

    input5.setAttribute('value', document.getElementById('X_NAZEV_SPISU').value)
    input5.setAttribute('type', 'hidden');
    input5.setAttribute('name', 'NAZEV_SPISU_TEXT');

    input7.setAttribute('type', 'hidden');
    input7.setAttribute('name', 'VYHLEDAVANI');
    input7.setAttribute('value', '1');


    frm.appendChild(input1);
    frm.appendChild(input2);
    frm.appendChild(input3);
    frm.appendChild(input4);
    frm.appendChild(input5);
    frm.appendChild(input6);
    frm.appendChild(input7);

";

if ($GLOBALS['SPISOVNA_ID']) {
echo "
    var input7 = document.createElement('INPUT');
    input7.setAttribute('value', " . $GLOBALS['SPISOVNA_ID'] . ")
    input7.setAttribute('type', 'hidden');
    input7.setAttribute('name', 'SPISOVNA_ID');

    frm.appendChild(input7);

";

}
echo "

//        document.getElementById(formular).value=hodnota.value;
//       alert(document.getElementById(formular));
    frm.method='GET';
    var act = frm.action;
    frm.action = 'brow.php';
    frm.submit();
  }


    //-->
    </script>
    <form name='prehled_vyhledavani'>
    </form>
    ";
// if (!$GLOBALS['SPISOVNA_ID']) {
// echo '<p><div class="form darkest-color"> <div class="form-body"> <div class="form-row">';
//
//
// echo '
// <span class="text">Filtr na protokoly:</span><div class="form dark-color"><div class="form-body"><div class="form-row">
// <a href="?" class="'.($GLOBALS["filtr_protokol"]<1?'':'btn').'">Vąe</a>&nbsp;
// <a href="?filtr_protokol=1" class="'.($GLOBALS["filtr_protokol"]==1?'':'btn').'">jen na protokolu</a>&nbsp;
// <a href="?filtr_protokol=2" class="'.($GLOBALS["filtr_protokol"]==2?'':'btn').'">bez protokolu</a>&nbsp;
// </div></div></div>';
//
// echo '</div> </div> </div><p>';
// }
