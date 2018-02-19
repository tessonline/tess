<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/funkce.inc"));

$q=new DB_POSTA;
$sql="select * from posta where odeslana_posta='t' and vlastnich_rukou like '5'
and (datum_vypraveni is null) and ODESL_EMAIL like '%@%' and stornovano is null order by id desc";
//echo $sql;
$q->query($sql);
while ($q->Next_Record())
{
    $href="<a title='Odeslat daný email' href='odeslat.php?ID_ODCHOZI=".$q->Record[ID]."'><img src='".FileUp2('images/ok_check.gif')."' border='0'></a>";
    $EMAIL_DATA[]=array("id"=>$q->Record["ID"],"datum"=>$q->Record[DATUM_PODATELNA_PRIJETI],"from"=>$q->Record[ODESL_EMAIL],"vec"=>$q->Record[VEC],"odkaz"=>$href);

}
if (count($EMAIL_DATA)>0)
  Table(array("showaccess" => true,"appendwhere"=>$where2,"showedit"=>false,"showinfo_extra"=>"&send=1","showdelete"=>false,"showselect"=>true,"multipleselect"=>true,
  "showediturl"=>"/ost/"));  
else
  echo "<h1>Odchozí emaily</h1><span class='text'><br/>Žádný dokument není určen k odeslání.</span>";
require(FileUp2("html_footer.inc"));
