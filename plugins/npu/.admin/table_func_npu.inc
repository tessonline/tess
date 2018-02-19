<?php
require_once(FileUp2('plugins/npu/.admin/classes/PKident.inc'));

Function UkazNPU($STAV) {

  switch($GLOBALS['STATUS']) {
    case '1':
      $color = 'silver';
      break;
    case '2':
      $color = 'green';
      break;
    case '3':
      $color = 'blue';
      break;
    case '4':
      $color = 'black';
      break;
    case '5':
      $color = '-webkit-linear-gradient(right, yellow, #CCCCCC); background-image:-moz-linear-gradient(right, yellow, #CCCCCC);';
      break;
    case '6':
      $color = 'red';
      break;
    case '7':
      $color = 'orange';
      break;
    case '8':
      $color = 'violet';
      break;
    case '11':
      $color = 'black';
      break;
    case '12':
      $color = 'violet';
      break;
    default:
      $color = 'silver';
      break;

  }
  If ($STAV=='t')
  {$res = "<img src=\"" . FileUpImage('images/back') . "\" title=\"Odchozí dokument\" style=\"background:".$color.";\" width=\"40\">";}
  else {$res = "<img src=\"" . FileUpImage('images/forward') . "\" title=\"Příchozí dokument\" style=\"background:".$color.";\" width=\"40\">";}
  If ($GLOBALS[ODES_TYP]=='Z') {
    $res = "<img src=\"" . FileUpImage('images/radiobtn-checked') . "\" title=\"Vlastní záznam\" style=\"background:".$color.";\" width=\"40\">";
  }
  return $res;

}

function PamKatalog($id, $pk_id) {
  if (!MaPristupKDokumentu_old($GLOBALS['REFERENT'])) return '';
  if ($GLOBALS['STATUS']<2) return '';
  static $img_museum, $doc_id;
  if (!$img_museum) $img_museum = FileUpImage('images/museum');
  $pocet = PKIdent::getCountOfIdent($id);
  $barva = '';
  if ($pocet>0) $barva = 'style="background:-webkit-linear-gradient(right, green, #CCCCCC); background-image:-moz-linear-gradient(right, green, #CCCCCC);" ';
  $res = "<a  href=\"\"
  onClick=\"javascript:NewWindowSpis('guide.php?G_NAME=posta_npu_pk_zalozeni&SPIS_ID=" . $id . "');return false;\"><img src='$img_museum' title='Vytvořit vazbu do památkového katalogu' $barva></a>\n";
  return $res;
}

