<?php
function ChangeStornovano($t) {
  static $i=1;
  if (_JsemNaRade($GLOBALS['POSTA_ID'], $GLOBALS['SCHVALUJICI_ID']) && $GLOBALS['SCHVALENO'] == 0) $color_radek = "_red";
  if ($i):
    $t->classname = "posta_brow".$color_radek;
    $i = 0;
  else:
    $t->classname = "posta_browdark".$color_radek;
    $i = 1;
  endif;
  If ($GLOBALS['STORNOVANO'] <> '') {
    $t->classname = 'gray_line';
  } // skrtnute pismo.
  $t->schema[6]['class']='posta_browdark'.$color_radek;

  //$t->classname="yellow_line";

}

function JeNaRade($posta_id, $prac) {
  if (_JsemNaRade($posta_id, $prac) && $GLOBALS['SCHVALENO'] == 0 && $GLOBALS['STORNOVANO'] == '') return '<img title="Aktuální schvalující" src="/images/navig/nav_nn.gif">&nbsp;';
  else return '';
}

function ShowPoznamka($poznamka, $stornovano) {
  if ($stornovano<>'') $res = $stornovano;
  else $res = $poznamka;
  return $res;
}

function StanoviskoSchvalovani($cislo, $column = 'ODPOVED') {
  foreach($GLOBALS['CONFIG']['SCHVALOVANI'] as $key => $val) {
    if ($val['VALUE'] == $cislo) $res = $val[$column];
  }
  return $res;
}

$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
 'delete' => array ('theme'=>array('dropdown'=>true, 'column'=>true)),
);

echo "
  <script>
  <!--

  function newVedouci(id) {
    NewWindowAgenda('plugins/schvalovani/edit.php?insert&POSTA_ID='+id);
  }

 //-->
</script>
";
