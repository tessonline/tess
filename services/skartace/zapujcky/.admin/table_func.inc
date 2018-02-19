<?php
if (!function_exists("ChangeClassBarva_AKCE")) {
  
  Function ChangeClassBarva_AKCE($t)  {
    if ($GLOBALS["STORNOVANO"]) $color = "_gray";
    $t->classname = "brow$color ";
  }

}

Function UkazDocZapujcka($id, $rucne = 0, $rucne_cj = '') {
  if ($rucne == 1) {
    $res = "<b>Ručně vložená zápujčka</b><br/>"; 
    $res .= nl2br($rucne_cj);
    return $res;
  }
  
  $spis_prvotni = '';
  $a = new DB_POSTA;
  $b = new DB_POSTA;
  $sql = 'select posta_id from posta_spisovna_zapujcky_id where zapujcka_id = ' . $id . ' order by posta_id asc';
  $b->query($sql);
  if ($b->Num_Rows()>10) $res[] = 'Obsahuje <b> ' . $b->Num_Rows().'<b> spisů';
  elseif ($b->Num_Rows() == 0) $res[] = 'žádné spisy';
  else
  while ($b->Next_Record()) {
    $sql = 'select * from posta_view_spisy where id = ' . $b->Record['POSTA_ID'];
    $a->query($sql); $pocet = $a->Num_Rows(); $a->Next_Record();

    if ($a->Record['ID'] > 0) {
      $doc = LoadClass('EedDokument', $a->Record['ID']);
      $res[$doc->cislo_jednaci] = "<b>" . $doc->cislo_jednaci . "</b> - " . $doc->vec;
    }
  }
/*
  $b->Next_Record();
  $sql = 'select * from posta_view_spisy where id = ' . $b->Record['POSTA_ID'];
  $a->query($sql); $pocet = $a->Num_Rows(); $a->Next_Record();

  if ($a->Record['ID'] > 0) {
    $doc = LoadClass('EedDokument', $a->Record['ID']);
    $res[$doc->cislo_jednaci] = "<b>" . $doc->cislo_jednaci . "</b> - " . $doc->vec;
  }
  if (is_array($res))
  {
    if ($spis_prvotni == '') {
      $spis_prvotni = VratPrvotniSpis($a->Record['CISLO_SPISU1'] . '/' . $a->Record['CISLO_SPISU2']);
      $text_cislospisu = $spis_prvotni;
    }
    if ($res[$text_cislospisu]<>'') $res_array[] = $res[$text_cislospisu];
    unset($res[$text_cislospisu]);
    while(list($key, $val) = each($res))
    $res_array[] = " ".$val;
    return implode('<br/>', $res_array);
  }
  else return '';
*/
  return implode('<br/>', $res);
}
Function UkazTisk($id) {
  $img = FileUpImage('images/pdf');
  $res = '<a target = "tisk" href = "../../../output/pdf/spisovna_zapujcka.php?id=' . $id . '"><img src = "' . $img . '" title = "Tisk zápujčního protokolu"></a>';
  if ($GLOBALS['STORNOVANO']) $res = "";
  return $res;
}

 
Function UkazVraceno($datum, $id, $rucne) {
  global $USER_INFO;
  $res = "<a href = '../skartacni_kniha/brow.php?ZAPUJCKA_ID=$id&PREDANI=1'>Vrátit</a>";
  if ($rucne) $res = '<a href = "javascript:edit_(\'' . $id . '&vraceno=1\')">Vrátit</a>';

  if ($datum<>'') $res = CZDate($datum);
  
  if ($GLOBALS['STORNOVANO']) $res = "";
  
  return $res;
}
