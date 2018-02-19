<?php
$celek[0]=array('NAME'=>'Statistika za celý úřad');


$celek[0]['tabulka'][1]=array('NAME'=>"Souhn",'radky'=>array(
    'Celkem_prichozi'=>VratPocet(array($STATISTIKA['PRICHOZI'])),
    'Celkem_odchozi'=>VratPocet(array($STATISTIKA['ODCHOZI'])),
  ),
);

$celek[0]['tabulka'][2]['NAME']="Přijetí dokumentů";
foreach($STATISTIKA['PRIJETI'] as $key => $val)
  $celek[0]['tabulka'][2]['radky'][$val['NAME']]=VratPocet(array($STATISTIKA['PRICHOZI'],$val['SQL']));

$celek[0]['tabulka'][3]['NAME']="Odesílání dokumentů";
foreach($STATISTIKA['ODESLANI'] as $key => $val)
  $celek[0]['tabulka'][3]['radky'][$val['NAME']]=VratPocet(array($STATISTIKA['ODCHOZI'],$val['SQL']));




foreach($STATISTIKA['ODBORY'] as $id_odboru => $hodnoty)
{
  $celek[$id_odboru]=array('NAME'=>'Statistika za odbor - '.UkazOdbor($id_odboru));

  $celek[$id_odboru]['tabulka'][1]=array('NAME'=>"Souhn",'radky'=>array(
      'Celkem příchozí'=>VratPocet(array($STATISTIKA['PRICHOZI'])),
      'Celkem odchozí'=>VratPocet(array($STATISTIKA['ODCHOZI'])),
    ),
  );
  
  $celek[$id_odboru]['tabulka'][2]['NAME']="Přijetí dokumentů";
  foreach($STATISTIKA['PRIJETI'] as $key => $val)
    $celek[$id_odboru]['tabulka'][2]['radky'][$val['NAME']]=VratPocet(array($STATISTIKA['PRICHOZI'],$hodnoty['SQL'],$val['SQL']));
  
  $celek[$id_odboru]['tabulka'][3]['NAME']="Odesílání dokumentů";
  foreach($STATISTIKA['ODESLANI'] as $key => $val)
    $celek[$id_odboru]['tabulka'][3]['radky'][$val['NAME']]=VratPocet(array($STATISTIKA['ODCHOZI'],$hodnoty['SQL'],$val['SQL']));
  
}


