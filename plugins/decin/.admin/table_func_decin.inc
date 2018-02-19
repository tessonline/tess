<?php

Function UkazDecin($STAV) {

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
      $color = 'red';
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
  {$res = "<img src=\"" . FileUpImage('images/back') . "\" title=\"Odchozí dokument\" style=\"background:".$color.";\">";}
  else {$res = "<img src=\"" . FileUpImage('images/forward') . "\" title=\"Příchozí dokument\" style=\"background:".$color.";\">";}
  If ($GLOBALS[ODES_TYP]=='Z') {
    $res = "<img src=\"" . FileUpImage('images/radiobtn-checked') . "\" title=\"Vlastní záznam\" style=\"background:".$color.";\">";
  }
  return $res;
}


