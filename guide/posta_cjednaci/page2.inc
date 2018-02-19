<?php
//echo "IDP".$IDPSPISU;
//$where=' AND p.id!='.$IDPSPISU.'';
$where.= $_SESSION["WHERE_PODMINKA"];
$where.=" AND CISLO_JEDNACI1<>0";
if ($GLOBALS["CONFIG"]["DB"]=="mssql")
  $GLOBALS["ZADEJ_SQL"]="p.*";
else
  $GLOBALS["ZADEJ_SQL"]="DISTINCT ON (cislo_jednaci2,cislo_jednaci1) p.*";
$GLOBALS["ZADEJ_SQL"]="p.*";
$GLOBALS["ZADEJ_ORDER_BY"]="cislo_jednaci2 DESC, cislo_jednaci1 DESC";
//echo $where;
Table(array("agenda" => "POSTA_C_JEDNACI", "showselect"=>true, "showedit"=>false, "appendwhere"=>$where,
"showdelete"=>false, "showguide"=>true,"setvars"=>true, "nopaging"=>true,"showinfo"=>false,"showhistory"=>false,"action"=>"guide/posta_cjednaci/page3.inc"));
?>
