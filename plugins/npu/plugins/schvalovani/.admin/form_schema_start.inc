<?php
/*
require_once(FileUp2('plugins/npu/.admin/classes/PKident.inc'));

$cj_obj = LoadClass('EedCj',$GLOBALS['POSTA_ID']);
$cj_info = $cj_obj->GetCjInfo($GLOBALS['POSTA_ID']);
$spis_id = $cj_info['SPIS_ID'];

$pocet_pam =  PKIdent::getCountOfIdent($spis_id);


$sql = 'select * from posta where id='.$spis_id;
$q->query($sql); $q->Next_Record();
$klasifikace = $q->Record['TYP_POSTY']?$q->Record['TYP_POSTY']:0;
$faze = $doc['JINE']?$doc['JINE']:0;

if ($klasifikace>0) {
  $sql = 'select * from cis_posta_typ where id='.$klasifikace;
  $q->query($sql); $q->Next_Record();

  //95 - K dané věcné klasifikaci musí být i odkaz na památku (nebo je chybně určena věcná klasifikace) [tabulka Spis_vecklasif - v číselníku zpřesněn obsah sloupce Kpam pro zjednoduení kříové kontroly VecKlasif a odkazů na památky ve SpisPam: hodnota = 1 -> odkaz na památku musí být; hodnota = -1 -> odkaz na památku nesmí být (je-li, je chybně určena věcná klasifikace)
  if ($q->Record['KPAM'] == 1 && $pocet_pam == 0)  {
    require(FileUp2('html_footer.inc'));
    echo '<p><div class="alert alert-error darkest-color"> <img class="alert-img" src="'.FileUpImage('images/info').'">
    <h4 class="alert-title">CHYBA:</h4>
    <p class="info-msg">Vzhledem k věcné klasifikaci je nutné nejprve provést založení vazby do Památkového katalogu.</p> </div></p>';
    Die();
  }
}
*/