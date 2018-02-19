<?php
$celek[0]=array('NAME'=>'Statistika za roli podatelna');

$pracovnici = $GLOBALS["POSTA_SECURITY"]->GetUsersForGroup('posta-podatelna-ruid');

//print_r($prac);
$stat_prac_celek = array();
//$pracovnici = VratPracovniky($GLOBALS['ODBOR']);
foreach($pracovnici as $key=>$val) {
  $prac = $GLOBALS["POSTA_SECURITY"]->GetUserInfo($val);
  $key = $prac['ID'];
  $val = $prac['FNAME']." ".$prac['LNAME'];
  $stat_pracovnici[$key]=array('NAME'=>$val,'SQL'=>" AND LAST_USER_ID IN (".$key.")");
  $stat_prac_celek[] = $key;
}
$GLOBALS['sql'] = 'select id  from posta_h';
$GLOBALS['sql_group_by'] = 'GROUP BY id';


$celek[0]=array('NAME'=>'Statistika za celek:');


$celek[0]['tabulka'][1]=array('NAME'=>"Souhn",'radky'=>array(
    'Celkem příchozí'=>VratPocet(array($STATISTIKA['PRICHOZI']," AND OWNER_ID IN (".implode(',',$stat_prac_celek).")")),
    'Celkem odchozí'=>VratPocet(array($STATISTIKA['ODCHOZI'],$hodnoty['SQL'])),
    'Součet'=>VratPocet(array($hodnoty['SQL'])),
  ),
);

$celek[0]['tabulka'][2]['NAME']="Zapsání příchozího dokumentu";
foreach($STATISTIKA['PRIJETI'] as $key => $val)
  $celek[0]['tabulka'][2]['radky'][$val['NAME']]=VratPocet(array($STATISTIKA['PRICHOZI']," AND OWNER_ID IN (".implode(',',$stat_prac_celek).")",$val['SQL']));

$celek[0]['tabulka'][3]['NAME']="Zapsání odeslaného dokumentu";
foreach($STATISTIKA['ODESLANI'] as $key => $val)
  $celek[0]['tabulka'][3]['radky'][$val['NAME']]=VratPocet(array($STATISTIKA['ODCHOZI'],$hodnoty['SQL'],$val['SQL']));
  



foreach($stat_pracovnici as $id_prac => $hodnoty) {
  $celek[$id_prac]=array('NAME'=>'zpracovatel: '.$hodnoty['NAME']);

  $celek[$id_prac]['tabulka'][1]=array('NAME'=>"Souhn",'radky'=>array(
      'Celkem příchozí'=>VratPocet(array($STATISTIKA['PRICHOZI']," AND OWNER_ID IN (".$id_prac.")")),
      'Celkem odchozí'=>VratPocet(array($STATISTIKA['ODCHOZI'],$hodnoty['SQL'])),
      'Součet'=>VratPocet(array($hodnoty['SQL'])),
    ),
  );
  
  $celek[$id_prac]['tabulka'][2]['NAME']="Zapsání příchozího dokumentu";
  foreach($STATISTIKA['PRIJETI'] as $key => $val)
    $celek[$id_prac]['tabulka'][2]['radky'][$val['NAME']]=VratPocet(array($STATISTIKA['PRICHOZI']," AND OWNER_ID IN (".$id_prac.")",$val['SQL']));
  
  $celek[$id_prac]['tabulka'][3]['NAME']="Zapsání odeslaného dokumentu";
  foreach($STATISTIKA['ODESLANI'] as $key => $val)
    $celek[$id_prac]['tabulka'][3]['radky'][$val['NAME']]=VratPocet(array($STATISTIKA['ODCHOZI'],$hodnoty['SQL'],$val['SQL']));
  
/*  $celek[$id_prac]['tabulka'][4]['NAME']="Druh dokumentů";
  foreach($STATISTIKA['TYP_DOC'] as $key => $val)
  {
    $pocet = VratPocet(array($STATISTIKA['PRICHOZI'],$hodnoty['SQL'],$val['SQL']));
    if ($pocet>0) $celek[$id_prac]['tabulka'][4]['radky'][$val['NAME']]=$pocet;
  }
*/
  
}


