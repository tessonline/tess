<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

$file='nastaveni.eed';
//$file='http://demo.tmapserver.cz/ost/posta/services/nastaveni/konfigurace/nastaveni.eed';
//$file = 'http://demo-zis.tmapserver.cz/ost/posta/services/nastaveni/konfigurace/nastaveni.eed';
$fp=fopen($file,'r');
while (!feof($fp)) {
  $data .= fread($fp, 8192);
}

fclose($fp);

$q=new DB_POSTA;

$radky=explode('|||',$data);

while (list($key,$val)=each($radky))
{
  if (strlen($val)>2)
  {
    $hodnoty=explode('|',$val);
    $sql="select id from posta_konfigurace where kategorie like '".$hodnoty[0]."' and parametr like '".$hodnoty[2]."' and superodbor is null";
    $q->query($sql);
    $pocet=$q->Num_Rows();
    
    if ($pocet==1)
    {
      echo "Parametr ".$hodnoty[2]." už je<br/>";
      $sql="update posta_konfigurace set popis='".$hodnoty[3]."' where parametr like '".$hodnoty[2]."'";  
      $q->query($sql);  
    }
    else
    {
       //jdeme ulozit
      $sql="insert into posta_konfigurace (kategorie,typ,parametr,popis) values ('".$hodnoty[0]."','".$hodnoty[1]."','".$hodnoty[2]."','".$hodnoty[3]."')";  
      echo "Přidávám parametr ".$hodnoty[2]." , doplňte hodnotu<br/>";
      //echo $sql."<br/>";
      $q->query($sql);  
    }
  }
}
//print_r($radky);
require(FileUp2("html_footer.inc"));
