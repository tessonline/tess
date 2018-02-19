<?php
$celek[0]=array('NAME'=>'Statistika za odbor');

$pracovnici = VratPracovniky($GLOBALS['ODBOR']);
foreach($pracovnici as $key=>$val)
  $stat_pracovnici[$key]=array('NAME'=>$val,'SQL'=>"AND REFERENT IN (".$key.")");

//print_r($stat_pracovnici);


foreach($stat_pracovnici as $id_odboru => $hodnoty)
{
  $celek[$id_odboru]=array('NAME'=>'zpracovatel: '.$hodnoty['NAME']);

//  $celek[$id_odboru]['tabulka'][1]=array('NAME'=>"Souhn",'radky'=>array(
//      'Celkem příchozí'=>VratPocet(array($STATISTIKA['PRICHOZI'],$hodnoty['SQL'])),
//      'Celkem odchozí'=>VratPocet(array($STATISTIKA['ODCHOZI'],$hodnoty['SQL'])),
//    ),
//  );
  
  $celek[$id_odboru]['tabulka'][2]['NAME']="Přijetí dokumentů";
  foreach($STATISTIKA['PRIJETI'] as $key => $val)
    $celek[$id_odboru]['tabulka'][2]['radky'][$val['NAME']]=VratPocet(array($STATISTIKA['PRICHOZI'],$hodnoty['SQL'],$val['SQL']));
  
  $celek[$id_odboru]['tabulka'][3]['NAME']="Odesílání dokumentů";
  foreach($STATISTIKA['ODESLANI'] as $key => $val)
    $celek[$id_odboru]['tabulka'][3]['radky'][$val['NAME']]=VratPocet(array($STATISTIKA['ODCHOZI'],$hodnoty['SQL'],$val['SQL']));
  
  $celek[$id_odboru]['tabulka'][4]['NAME']="Druh dokumentů";
  foreach($STATISTIKA['TYP_DOC'] as $key => $val)
  {
    $pocet = VratPocet(array($STATISTIKA['PRICHOZI'],$hodnoty['SQL'],$val['SQL']));
    if ($pocet>0) $celek[$id_odboru]['tabulka'][4]['radky'][$val['NAME']]=$pocet;
  }

  
}


