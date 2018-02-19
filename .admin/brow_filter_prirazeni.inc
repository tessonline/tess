<?php
echo "<p><form name='frm_change'>";


echo '<div class="form darkest-color"> <div class="form-body"> <div class="form-row">';

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/brow_filter_prirazeni_start.inc');
		if (File_Exists($file)) include($file);
  }
}

$omez_druh_doc = $GLOBALS['omez_druh_doc'];

echo '<div class="form-item"> <label class="form-label" for="select">Druh dokumentu:</label> <div class="form-field-wrapper"> <div class="form-field">';
echo '<input type="hidden" name="ORDER_BYdenik" value="' . $GLOBALS['ORDER_BYdenik']. '">';
echo '<input type="hidden" name="STATUS" value="2">';
$druh_doc = getSelectDataEed(new of_select_typ_posty(array()));
echo "<select name = 'omez_druh_doc' class='select' onchange='document.frm_change.submit();'><option value=''></option>";
while (list($key,$val)=each($druh_doc))
  echo "<option value='".$key."' ".($key==$omez_druh_doc?'SELECTED':'').">".$val."</option>";
echo "</select>";
echo '</div> </div> </div>';


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
    var input8 = document.createElement('INPUT');
    input8.setAttribute('type', 'hidden');
    input8.setAttribute('name', 'omez_druh_doc');
    input8.setAttribute('value', 0);

    input1.setAttribute('type', 'hidden');
    input1.setAttribute('name', 'ID_X');
    input1.setAttribute('value', document.getElementById('X_ID').value);

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

    input6.setAttribute('type', 'hidden');
    input6.setAttribute('name', 'CISLO_SPISU1_TEXT');
    input6.setAttribute('value', document.getElementById('X_CISLO_SPISU1_TEXT').value);

    input7.setAttribute('type', 'hidden');
    input7.setAttribute('name', 'STATUS');
    input7.setAttribute('value', 2);


    frm.appendChild(input1);
    frm.appendChild(input2);
    frm.appendChild(input3);
    frm.appendChild(input4);
    frm.appendChild(input5);
    frm.appendChild(input6);
    frm.appendChild(input7);
    frm.appendChild(input8);

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

reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/.admin/brow_filter_prirazeni_end.inc');
		if (File_Exists($file)) include($file);
  }
}

