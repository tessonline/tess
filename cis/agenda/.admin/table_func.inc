<?php

function changeCellClass($t) {
  $neaktivni = $GLOBALS['NEAKTIVNI'];
  if ($neaktivni=='t')
    $t->classname = "brow_red";
  else
    $t->classname = "brow_gray";
    
}


function kopirovatAgendu($id) {
  $res = "";
  $res.='<a href="#" onclick="javascript:NewWindowKopirovatAgendu(\'kopirovat_agendu.php?id='.$id.'\')"\"><img src=' .  FileUpImage('images/add') . ' border="0" title="Kopírovat agendu"></a>';
  return $res;
}