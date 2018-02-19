<?php
require('tmapy_config.inc');
//echo "Odbor je".$GLOBALS['ODBOR'].' a oemz_prac je '.$GLOBALS['omez_prac'].' a js_odbor je '.$GLOBALS['JS_ODBOR'].'<br/>';
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('.admin/brow_func.inc'));
include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select.inc");
require_once(FileUp2(".admin/el/of_select_.inc"));

$EddSql = LoadClass('EedSql');

$fancybox_jquery = true;
require(FileUp2('html_header_full.inc'));

echo "<span style=\"font-size=12px; text-underline:none;\"><table border=0 width=100%><tr><td width='1%'><span class='caption'>Filtr&nbsp;výpisu:</td><td rowspan=4><form name='frm_change'>";
echo '<input type="hidden" name="ORDER_BYdenik" value="' . $GLOBALS['ORDER_BYdenik']. '">';
$rok = getSelectData(new of_select_rok(array()));
echo "&nbsp;&nbsp;&nbsp;<select name = 'omez_rok' onchange='document.frm_change.submit();'><option value=''></option>";
while (list($key,$val)=each($rok))
  echo "<option value='".$val."' ".($val==$omez_rok?'SELECTED':'').">".$val."</option>";
echo "</select>";
//print_r($rok);

$prac =  getSelectData(new of_select_superodbor(array()));
echo "&nbsp;&nbsp;&nbsp;<select name='omez_zarizeni' onchange='document.frm_change.submit();'><option value=''></option>";
while (list($key,$val)=each($prac))
  echo "<option value='".$key."' ".($key==$GLOBALS['omez_zarizeni']?'SELECTED':'').">".$val."</option>";
echo "</select>";


$GLOBALS['SUPERODBOR'] = $GLOBALS['omez_zarizeni'];
$odbory = getSelectData(new of_select_vsechny_spisuzly(array()));
echo "&nbsp;&nbsp;&nbsp;<select name = 'omez_uzel' onchange='document.frm_change.submit();'><option value=''></option>";
$unit_exists = false;
foreach ($odbory as $key => $val) {
  if ($GLOBALS['omez_uzel']==$key) $unit_exists = true;
  echo '<option value="'.$key.'" '.($GLOBALS['omez_uzel']==$key?'SELECTED':'').'>'.$val.'</option>';
}
if (!$unit_exists) $GLOBALS['omez_uzel'] = 0; //nekonzistence unit, z brow_func mame unitu, ktera neni v danem selectu
echo "</select>";

echo "<br/>";

if ($GLOBALS['omez_uzel'])
{
  $GLOBALS['ODBOR'] = $GLOBALS['omez_uzel'];
  $prac = getSelectData(new of_select_referent(array()));
  echo "&nbsp;&nbsp;&nbsp;<select name = 'omez_prac' onchange='document.frm_change.submit();'><option value=''></option>";
  foreach ($prac as $key => $val) {
    echo '<option value="'.$key.'" '.($GLOBALS['omez_prac']==$key?'SELECTED':'').'>'.$val.'</option>';
  }
  echo "</select>";
}

$stav =  getSelectData(new of_select_stavy_filtr(array()));

echo "&nbsp;&nbsp;&nbsp;<select name = 'omez_stav' onchange='document.frm_change.submit();'><option value=''></option>";
while (list($key,$val)=each($stav))
  echo "<option value='".$key."' ".($key==$GLOBALS['omez_stav']?'SELECTED':'').">".$val."</option>";
echo "</select>";


echo "</form></span></td>";

echo "<td rowspan=4 align=right valign=top NOWRAP width='10%'>&nbsp;</td>
<td rowspan=4 align=right valign=top NOWRAP>
naše čj:<input type='text' class='text' name='X_CISLO_SPISU1_TEXT' id='X_CISLO_SPISU1_TEXT' size='12'><br/>
vaše čj:<input type='text' name='X_JEJICH_CJ' id='X_JEJICH_CJ' size='12'><br/>
věc:<input type='text' name='X_VEC' id='X_VEC' size='12'>
</td>";
echo "</tr></table>    
    
    </span>";

$where = " AND MAIN_DOC = 1";

//$where.= " AND CISLO_SPISU2 in (".$omez_rok.")";
if ($GLOBALS['omez_rok']) { $where.=" AND cislo_spisu2 in (".$GLOBALS['omez_rok'].")";}
if ($GLOBALS['omez_zarizeni']) { $where.=" AND superodbor in (".$GLOBALS['omez_zarizeni'].")";}
if ($GLOBALS['omez_stav']==1) {$where.=" AND status < 0";}
if ($GLOBALS['omez_stav']==2) {$where.=" AND status = 1";}
if ($GLOBALS['omez_stav']==3) {$where.=" AND status > 1";}  
if ($GLOBALS['omez_stav']==4) {$where.=" AND status in (5,6)";}
If ($GLOBALS['omez_stav']==5) {$where.=" AND main_doc=1 and (((DATUM_VYRIZENI)>lhuta_vyrizeni and datum_vyrizeni<>'' and lhuta_vyrizeni is not null) or (lhuta_vyrizeni<CURRENT_DATE and (status>1 and status<9) and (datum_vyrizeni is null or datum_vyrizeni='') and lhuta_vyrizeni is not null))";}

if ($GLOBALS['omez_uzel']>0 ) {
  $where_app = $EddSql->WhereOdborAndPrac($GLOBALS['omez_uzel']);
  $where.= " AND (".$where_app.")";
}
if ($GLOBALS['omez_prac']) {$where.=" AND referent in (".$GLOBALS['omez_prac'].")";}

//echo " a  odbor je ".$GLOBALS['ODBOR'];
//$GLOBALS['SUPERODBOR'] = $GLOBALS['omez_prac'];
/*
$count = Table(array(
  "tablename"=>"evidencepisemnosti",
  "caption"=>$caption,
  "showedit"=>false,
  "showdelete"=>false,
  "showpagging"=>true,
  "showexportall"=>false,
  "modaldialogs"=>false,
  "setvars"=>true,
  "formvars" => array('JS_ODBOR'),
//  "unsetvars"=>array("except"=>array("ODBOR")),
  "unsetvars"=>false,
  "showupload"=>false,
  "showhistory"=>false,
  "appendwhere"=>$where,
  "select_id"=>"ID" ,
  "page_size"=>$page_size,
  //a pridame neco, co umuzni editaci vedoucim...

));
*/
$count = Table(array(
  "tablename"=>"denik",
  "showedit"=>false,
  "showdelete"=>false,
  "setvars"=>true,
  "showupload"=>false,
  "showhistory"=>false,
  "appendwhere"=>$where,
  //a pridame neco, co umuzni editaci vedoucim...

));


//    document.getElementById('hidden_forms_objekty').innerHTML = '".$hidden_forms_objekty."';

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
    input1.setAttribute('type', 'hidden');
    input1.setAttribute('name', 'CISLO_SPISU1_TEXT');
    input1.setAttribute('value', document.getElementById('X_CISLO_SPISU1_TEXT').value);
    input2.setAttribute('type', 'hidden');
    input2.setAttribute('name', 'JEJICH_CJ');
    input2.setAttribute('value', document.getElementById('X_JEJICH_CJ').value);
    input3.setAttribute('type', 'hidden');
    input3.setAttribute('name', 'VEC');
    input3.setAttribute('value', document.getElementById('X_VEC').value);
    input4.setAttribute('type', 'hidden');
    input4.setAttribute('name', 'POSTA_VYHLEDAVANI');
    input4.setAttribute('value', '1');
    frm.appendChild(input1);            
    frm.appendChild(input2);            
    frm.appendChild(input3);            
    frm.appendChild(input4);            
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

require(FileUp2('html_footer.inc'));
