<?php
require("tmapy_config.inc");
include ($GLOBALS["TMAPY_LIB"]."/lib/jpgraph/jpgraph.php");
include ($GLOBALS["TMAPY_LIB"]."/lib/jpgraph/jpgraph_pie.php");
include ($GLOBALS["TMAPY_LIB"]."/lib/jpgraph/jpgraph_pie3d.php");


$data=substr($data,0,-1);
if (!$data) $data="1";
$name=substr($name,0,-1);
if (!$name) $name="bez dat";
$data = explode(',',$data);
$legenda = explode(',',$name);
$graph = new PieGraph(400,300,"auto");


$graph->SetShadow();

$graph->title->Set($nadpis);
$graph->title->SetFont(FF_FONT1,FS_BOLD);

$p1 = new PiePlot3D($data);
$p1->SetSize(0.4);
$p1->SetAngle(35);
$p1->SetCenter(0.45,0.5);
$p1->SetLegends($legenda);
$p1-> SetLabelType( "PIE_VALUE_ABS");

$graph->Add($p1);
$graph->Stroke();
?>
