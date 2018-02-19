<?php

//podle typu schvalovani (postup=2 schvaluji vsichni najednou, postup=1 shvaluji postupne za sebou) rekne
//jestli dotycny je na rade a muze schvalovat
function _JsemNaRade($posta_id, $prac = 0) {
  if (is_array($posta_id)) $posta_id = $posta_id[0];
  $pid = split(',',$posta_id);
  $posta_id = $pid[0];
  $sql = 'select * from posta_schvalovani where posta_id=' . $posta_id . ' and schvaleno=0 and stornovano is null order by id asc';
  $q = new DB_POSTA;
  $q->query($sql); 
  $q->Next_Record();
  if ($q->Record['POSTUP'] == 2 || ($q->Record['POSTUP'] == 1 && $q->Record['SCHVALUJICI_ID'] == $prac)) return true;
  else return false; 
}

function JeVeSchvaleni($id,$prac = 0) {
  if (is_array($id)) $id = $id[0];
  $pid = split(',',$id);
  $id = $pid[0];
  
  if ($prac>0) $add = ' and schvalujici_id=' . $prac;
  $sql = 'select posta_id from posta_schvalovani where posta_id=' . $id . ' ' . $add . ' and schvaleno=0 and typschvaleni=1 and stornovano is null ';
  $q = new DB_POSTA;
  //echo $sql . '<br/>';
  $q->query($sql);
  if ($q->Num_Rows()>0) return true;
  else return false;
}

function JeKPodpisu($id,$prac = 0) {
  if (is_array($id)) $id = $id[0];
  $pid = split(',',$id);
  $id = $pid[0];
  if ($prac>0) $add = ' and schvalujici_id = ' . $prac;
  $sql = 'select posta_id from posta_schvalovani where posta_id=' . $id . ' ' . $add . ' and schvaleno = 0 and typschvaleni=11 and stornovano is null ';
  $q = new DB_POSTA;
 // echo $sql;
  $q->query($sql);
  if ($q->Num_Rows()>0) return true;
  else return false;
}

function JeVeSchProcesu($id) {
  $pid = split(',',$id);
  $id = $pid[0];
  $sql = 'select posta_id from posta_schvalovani where posta_id=' . $id . ' and stornovano is null ';;
  $q = new DB_POSTA;
//  echo $sql . '<br/>';
  $q->query($sql);
  if ($q->Num_Rows()>0) return true;
  else return false;
}

function SeznamKeSchvaleni($prac) {
  $sql = 'select distinct(posta_id) from posta_schvalovani left join posta on posta_schvalovani.posta_id=posta.id where schvalujici_id=' . $prac . ' and typschvaleni=1 and schvaleno=0 and posta_schvalovani.stornovano is null and posta.status>1';
  $q = new DB_POSTA;
//  echo $sql;
  $q->query($sql);
  $id = array();
  while ($q->Next_Record()) {
    if (_JsemNaRade($q->Record['POSTA_ID'], $prac)) $id[] = $q->Record[POSTA_ID];
  }
  return $id;
}

function SeznamKPodpisu($prac) {
  $sql = 'select distinct(posta_id) from posta_schvalovani left join posta on posta_schvalovani.posta_id=posta.id where schvalujici_id = ' . $prac . ' and typschvaleni=11 and schvaleno=0  and posta_schvalovani.stornovano is null and posta.status>0';
  $q = new DB_POSTA;
  //echo $sql;
  $q->query($sql);
  $id = array();
  while ($q->Next_Record()) {
    if (_JsemNaRade($q->Record['POSTA_ID'], $prac)) $id[] = $q->Record[POSTA_ID];
  }
  return $id;
}

function SchvalenoKladne($id) {
  $pid = split(',',$id);
  $id = $pid[0];
  $je_ve_schvaleni = JeVeSchProcesu($id);
  if (JeKPodpisu($id)) return false;
//  $sql = 'select id from posta_schvalovani where posta_id=' . $id . ' and schvaleno in (11,1) and schvaleno not in (2,12) and stornovano is null';
  $sql = 'select id from posta_schvalovani where posta_id=' . $id . ' and schvaleno in (11) and schvaleno not in (2,12) and stornovano is null';
//echo $sql;
  $q = new DB_POSTA; $q->query($sql);
  $schvaleno = $q->Num_Rows();
  if ($schvaleno > 0 && $je_ve_schvaleni) return true;
  else return false;
}

function VratIdZPostaId($id_array) {
  $res = array();
  $sql = "select id from posta_schvalovani where posta_id in (".implode(',' , $id_array). ")";
  $q = new DB_POSTA; $q->query($sql);
  while ($q->Next_Record()) {
    $res[] = $q->Record['ID'];
  }
  return $res;
}

function VratImgKeSchvalovani($id) {
  $img = "person-2";
  $barva = "";
  $title = 'Zahájit schvalovací proces';
  $je_ve_schvaleni = JeVeSchProcesu($id);

  if ($je_ve_schvaleni)  {
//    $barva = "yellow";
    $barva = "-moz-linear-gradient(right, yellow, #CCCCCC); background: -webkit-linear-gradient(right, yellow, #CCCCCC); background-image:-ms-linear-gradient(right, yellow, #CCCCCC);";
    $title = "Schvalovací proces probíhá";
  }
  $sql = 'select posta_id from posta_schvalovani left join posta on posta_schvalovani.posta_id=posta.id where posta_id=' . $id . ' and schvaleno in (1) and posta_schvalovani.stornovano is null and posta.status>0';
  $q = new DB_POSTA; 
  $q->query($sql);
  $schvaleno = $q->Num_Rows();
  if ($schvaleno>0 && $je_ve_schvaleni) {
    $barva = "green";
    $barva = "-moz-linear-gradient(right, green, #CCCCCC); background: -webkit-linear-gradient(right, green, #CCCCCC); background-image:-ms-linear-gradient(right, green, #CCCCCC);";
    $title = "Schvalovací proces ukončen, souhlasné stanovisko";
  }

  $sql = 'select posta_id from posta_schvalovani left join posta on posta_schvalovani.posta_id=posta.id where posta_id=' . $id . ' and schvaleno=11 and posta_schvalovani.stornovano is null and posta.status>0';
  $q = new DB_POSTA; $q->query($sql);
  $neschvaleno = $q->Num_Rows();
  if ($neschvaleno>0 && $je_ve_schvaleni) {
    $barva = "green";
    $img = "ok-2";
    $title = "Schvalovací proces ukončen, dokument je podepsán";
  }


  $sql = 'select posta_id from posta_schvalovani left join posta on posta_schvalovani.posta_id=posta.id where posta_id=' . $id . ' and schvaleno=0 and posta_schvalovani.stornovano is null and posta.status>0';
  $q = new DB_POSTA; 
  $q->query($sql);
  $probihajici = $q->Num_Rows(); 
  $q->Num_Rows();
  if ($probihajici>0 && $je_ve_schvaleni) {
    $barva = "-moz-linear-gradient(right, yellow, #CCCCCC); background: -webkit-linear-gradient(right, yellow, #CCCCCC); background-image:-ms-linear-gradient(right, yellow, #CCCCCC)";
//    $barva = "yellow";
    $title = "Schvalovací proces probíhá";
  }

  $sql = 'select posta_id from posta_schvalovani left join posta on posta_schvalovani.posta_id=posta.id where posta_id=' . $id . ' and schvaleno=2 and posta_schvalovani.stornovano is null and posta.status>0';
  $q = new DB_POSTA; $q->query($sql);
  $neschvaleno = $q->Num_Rows();
  if ($neschvaleno>0 && $je_ve_schvaleni) {
    $barva = "red";
    $title = "Ve schvalovacím procesu je nesouhlasné stanovisko";
  }

  $sql = 'select posta_id from posta_schvalovani left join posta on posta_schvalovani.posta_id=posta.id where posta_id=' . $id . ' and schvaleno=12 and posta_schvalovani.stornovano is null and posta.status>0';
  $q = new DB_POSTA; $q->query($sql);
  $neschvaleno = $q->Num_Rows();
  if ($neschvaleno>0 && $je_ve_schvaleni) {
    $img = "person-2";
    $title = "Ve schvalovacím procesu je záporné stanovisko";
  }

  return '<img src="' . FileUpImage("images/" . $img) . '" title="' . $title . '" alt="' . $title . '" border="0" '. ($barva ? 'style="background:' . $barva . ';" ':'').'>';
//  return '<img src="' . FileUpImage("images/" . $img) . '" title="' . $title . '" alt="' . $title . '" border="0" '. ($barva ? 'style="background:-webkit-linear-gradient(right, '.$barva.', #CCCCCC);;" ':'').'>';

}
