<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/oth_funkce_2D.inc"));

$ids = explode('|',$GLOBALS['id']);

$span = array();

if ($GLOBALS['smer'] == 1) {
  $sloupec_datum = 'DATUM_PREDANI';
}
else {
  $sloupec_datum = 'DATUM_PREDANI_VEN';
}

$q = new DB_POSTA;
if (count($ids)>0) {
  foreach($ids as $id) {
    if (strlen($id)>0) {

      $idCK = PrevedCPnaID($id,'');
      echo "Onma naleyeno id $idCK <br/>";
      if ($idCK>0) {
        $sql = 'select * from posta where id=' . $idCK;
        $q->query($sql);
        $q->Next_Record();

        if ($q->Record[$sloupec_datum]<>'') {
          $span[] = $id.'- <font color=red><b>CHYBA, už převedeno!</b></font>';
          $idok[] = $idCK;
        }
        else {
          $span[] = 'ok';
          $idok[] = $idCK;
        }
      }
      else
        $span[] = $id.'- <font color=red><b>nenalezeno!</b></font>';
    }
    else
      $span[] = '&nbsp;';
  }

  $res = implode('<br />', $span);
  echo $res;

  echo '<script type="text/javascript">

  window.parent.document.getElementById(\'span_text_CK\').innerHTML = \''.$res.'\';
  window.parent.document.getElementById(\'hledam\').style = \'visibility:hidden\';

  ';
  if (count($idok)>0)
  foreach($idok as $idk)
  echo '
  var f = window.parent.document.getElementById(\''.$idk.'\');
  if (f) f.checked=true;

  ';

  echo'
  //   var elements = window.parent.document.frm_posta.SELECT_IDposta;
  //        for (i=0; i<elements.length; i++){
  //            alert(elements[i].value);
  //         }

  </script>
  ';
}
