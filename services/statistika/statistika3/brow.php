<?php
require("tmapy_config.inc");
require(FileUp2(".admin/nocache.inc"));
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/brow_func.inc"));
require(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/security_name.inc"));
require(FileUp2("security/.admin/security_func.inc"));
include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select.inc");
require_once(GetAgendaPath('POSTA',false,false)."/.admin/el/of_select_.inc");
require(FileUp2("html_header_full.inc"));

while (list($key,$val)=each($GLOBALS["CONFIG"]["TYP_ODESLANI"]))
{
  $id=$val['VALUE'];
  $doporucene[$id] = $val['LABEL'];
}
$GLOBALS["DOPORUCENE"]=$doporucene;

If ($GLOBALS["MESIC"]=="") {$GLOBALS["MESIC"]='%';}
If ($GLOBALS["ROK"]=="") {$GLOBALS["ROK"]=date('Y');}
If ($ODBOR>0) {$GLOBALS["ODBOR"]=$ODBOR;}
if ($ODDELENI && !$ODBOR) 
{
   $jaky_odbor=UkazOdbor($ODD,0,0,1);
   $ODBOR= VratOdbor(GetParentGroup($jaky_odbor));
}

$cely_urad=true;

if ($GLOBALS["HISTORIE"]) $text="(včetně archívu)";

If ($GLOBALS["MESIC"]=="%") {  echo "<center><span class=\"caption\">Statistika evidence dokumentů za celý rok ".$GLOBALS["ROK"]." $text</span></center>";
}
else
{
  echo "<center><span class=\"caption\">Statistika evidence dokumentů za ".$GLOBALS["MESIC"].". měsíc ".$GLOBALS["ROK"]." $text</span></center>";
}
echo "<br/>";


$a=new DB_POSTA;

// tabulka za cely MU
$pole['MESIC']=$GLOBALS['MESIC'];
$pole['ROK']=$GLOBALS['ROK'];
$pole['HISTORIE']=$GLOBALS['HISTORIE'];

if ($typ_posty) $GLOBALS['TYP_POSTY']=explode(',',$typ_posty);
if ($GLOBALS['TYP_POSTY'])
{
  $pole['TYP_POSTY']=implode(',',$GLOBALS['TYP_POSTY']);
}
//  print_r($GLOBALS['TYP_POSTY']);
if (!$GLOBALS["ODBOR"])
{
  $odbor_vypis=getSelectData(new of_select_superodbor(array()));
  $column='SUPERODBOR';
}
if ($GLOBALS["ODBOR"])
{
  $cely_urad=false;
//  $sql="SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=".UkazOdbor($GLOBALS["ODBOR"],0,0,1)." ORDER BY g.name";
  $sql="SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=".$GLOBALS["ODBOR"]." ORDER BY g.name";
  $a->query($sql);
  while ($a->Next_Record())
    $odbor_vypis[$a->Record['ID']]=$a->Record['NAME'];
  $column='ODBOR';
}
if ($GLOBALS["ODBOR"] && $GLOBALS['REFERENT']==-1)
{
  $cely_urad=false;
       $odbor=UkazOdbor($GLOBALS['ODBOR'],0,0,1);
 //  $sql="SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=".UkazOdbor($GLOBALS["ODBOR"],0,0,1)." ORDER BY g.name";
   $where=" OR g.parent_group_id=".$odbor." or g.id=".$odbor;
   $sql="SELECT u.id,u.lname, u.fname FROM security_user u LEFT JOIN security_group g ON u.group_id=g.id where (u.group_id=".$odbor." $where) and active ORDER BY lname";
//echo $sql;
   $a->query($sql);
  while ($a->Next_Record())
    $odbor_vypis[$a->Record['ID']]=$a->Record['FNAME'].' '.$a->Record['LNAME'];
//  $odbor_vypis=getSelectData(new of_select_referent(array()));
  $column='REFERENT';
}


if ($cely_urad)
{
  $caption.="Celkem za úřad";
  $data=NactiData($pole,0);
  $POSTA_STATISTIKA_DATA=$data;
  echo "<table><tr><td align=left colspan=3><span class='caption'>".$caption."</span></td></tr><tr><td>";
  $count = Table(array("showaccess" => true, "maxnumrows"=>1000,"showcount"=>false,"showself"=>false,"showinfo"=>false, "unsetvars"=>true,"showedit"=>false,"showdelete"=>false,"nopaging"=>($GLOBALS["strankovat"]?false:true),nocaption=>true));
  $ukaz_obalka_pocet=0; $ukaz_obalka_text='';
  $ukaz_doruceni_pocet=0; $ukaz_doruceni_text='';
  while (list($key,$val)=each($data))
  {
    if ($val[id]=='a' && $val["POCET"]<>0) {$ukaz_obalka_pocet.=$val["POCET"].","; $ukaz_obalka_text.=$val["TEXT_GRAF"].",";}
    if ($val[id]=='b' && $val["POCET"]<>0) {$ukaz_doruceni_pocet.=$val["POCET"].","; $ukaz_doruceni_text.=$val["TEXT_GRAF"].",";}
  }
  $url_add="data=$ukaz_obalka_pocet&name=$ukaz_obalka_text&nadpis=Druhy obálek";
  echo "</td><td>";
  echo "<img src='graph.php?".$url_add."'>";
  $url_add="data=$ukaz_doruceni_pocet&name=$ukaz_doruceni_text&nadpis=Způsob doručení";
  echo "</td><td>";
  echo "<img src='graph.php?".$url_add."'>";
  echo "</td></tr></table>";
}

// tabulka za jednotlive odbory
while (list($key_odbor,$val_odbor)=each($odbor_vypis))
{
  echo "<hr/>";
  $odd=''; $odbor_xx=$key_odbor;
  $caption="";
  if ($column=='SUPERODBOR')
    $caption="<a title=\"Zobrazit statistiky podle oddělení tohoto odboru\" href=\"brow.php?ODBOR=".$odbor_xx."&MESIC=".$GLOBALS["MESIC"]."&ROK=".$GLOBALS["ROK"]."&typ_posty=".$pole['TYP_POSTY']."\"><img src=\"".FileUp2('images/self.gif')."\" border=0 alt=\"Zobrazit statistiky podle oddělení tohoto odboru\"></a>&nbsp;";
  if ($column=='ODBOR')
    $caption.="<a title=\"Zobrazit statistiky podle referentů tohoto odboru\" href=\"brow.php?ODBOR=".$odbor_xx."&REFERENT=-1&MESIC=".$GLOBALS["MESIC"]."&ROK=".$GLOBALS["ROK"]."&typ_posty=".$pole['TYP_POSTY']."\"><img src=\"".FileUp2('images/two_people.gif')."\" border=0 alt=\"Zobrazit statistiky podle referentů tohoto odboru\"></a>&nbsp;";
  $caption.="Celkem za: ".$val_odbor;
//  $data=NactiData($GLOBALS["MESIC"],$GLOBALS["ROK"],$odbor_xx,$oddeleni,'',0,$GLOBALS["HISTORIE"]);
  $pole[$column]=$key_odbor;
  $data=NactiData($pole,0);
  $POSTA_STATISTIKA_DATA=$data;
  echo "<table><tr><td align=left colspan=3><span class='caption'>".$caption."</span></td></tr><tr><td NOWRAP>";
  $count = Table(array("showaccess" => true, "maxnumrows"=>1000,"showcount"=>false,"showself"=>false,"showinfo"=>false, "unsetvars"=>true,"showedit"=>false,"showdelete"=>false,"nopaging"=>true,"nocaption"=>true,"modaldialogs"=>true));
  $ukaz_obalka_pocet=0; $ukaz_obalka_text='';
  $ukaz_doruceni_pocet=0; $ukaz_doruceni_text='';
  while (list($key,$val)=each($data))
  {
    if ($val[id]=='a' && $val["POCET"]<>0) {$ukaz_obalka_pocet.=$val["POCET"].","; $ukaz_obalka_text.=$val["TEXT_GRAF"].",";}
    if ($val[id]=='b' && $val["POCET"]<>0) {$ukaz_doruceni_pocet.=$val["POCET"].","; $ukaz_doruceni_text.=$val["TEXT_GRAF"].",";}
  }
  $url_add="data=$ukaz_obalka_pocet&name=$ukaz_obalka_text&nadpis=Druhy obálek";
  echo "</td><td>";
  echo "<img src='graph.php?".$url_add."'>";
  $url_add="data=$ukaz_doruceni_pocet&name=$ukaz_doruceni_text&nadpis=Způsob doručení";
  echo "</td><td>";
  echo "<img src='graph.php?".$url_add."'>";
  echo "</td></tr>";

  $data=NactiData($pole,1);
  $POSTA_STATISTIKA_DATA=$data;
  echo "<tr><td NOWRAP>";
  $count = Table(array("showaccess" => true, "maxnumrows"=>1000,"showcount"=>false,"showself"=>false,"showinfo"=>false, "unsetvars"=>true,"showedit"=>false,"showdelete"=>false,"nopaging"=>true,"caption"=>"Druh dokumentu","modaldialogs"=>true));
  $ukaz_obalka_pocet=0; $ukaz_obalka_text='';
  $ukaz_doruceni_pocet=0; $ukaz_doruceni_text='';
  while (list($key,$val)=each($data))
  {
    if ($val[id]=='c' && $val["POCET"]<>0) {$ukaz_obalka_pocet.=$val["POCET"].","; $ukaz_obalka_text.=$val["TEXT_GRAF"].",";}
  }
  $url_add="data=$ukaz_obalka_pocet&name=$ukaz_obalka_text&nadpis=Druhy dokumentů";
  echo "</td><td>";
  echo "<img src='graph.php?".$url_add."'>";
  echo "</td><td>";
  //echo "<img src='graph.php?".$url_add."'>";
  echo "</td></tr></table>";
  Flush();
  Flush();
}



   
echo '<hr/>';
echo '<center><font face=verdana size=1>vytištěno v programu Evidence dokumentů, (c) T-MAPY spol. s r.o., tisk dne '.Date("d.m.Y H:m").'</font></center>';

require(FileUp2("html_footer.inc"));
?>
