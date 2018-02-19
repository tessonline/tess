<?php
Function OrezZnaky($text)
{
  $text=strip_tags($text); 
  $text=str_replace(chr(13).chr(10),'',$text);
  $text=StrTr($text,"<>","()");
  return $text;
}

require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/db/db_posta.inc"));
Header("Pragma: no-cache");
Header("Cache-Control: no-cache");
Header("Content-Type: text/xml");

$q=new DB_POSTA;
$a=new DB_POSTA;
echo "<?xml version=\"1.0\" encoding=\"iso-8859-2\"?>\n";
echo "<STATISTIKA>";
$q->query("select distinct rok from posta order by rok asc");
while ($q->Next_Record())
{
  $rok=$q->Record["ROK"];
  $sql_prichozi="select count(id) as prichozi from posta where rok='$rok' and odeslana_posta='f'";
  $a->query($sql_prichozi);
  $a->Next_Record();
  $prichozi=$a->Record["PRICHOZI"];
  $sql_odchozi="select count(id) as odchozi from posta where rok='$rok' and odeslana_posta='t'";
  $a->query($sql_odchozi);
  $a->Next_Record();
  $odchozi=$a->Record["ODCHOZI"];
  echo '
   <ROK value="'.$rok.'">
     <PRICHOZI>'.$prichozi.'</PRICHOZI>
     <ODCHOZI>'.$odchozi.'</ODCHOZI>
   </ROK>';
   If ($rok==Date('Y'))
  echo '
   <AKTUALNE>
     <PRICHOZI>'.$prichozi.'</PRICHOZI>
     <ODCHOZI>'.$odchozi.'</ODCHOZI>
   </AKTUALNE>';
     
}




echo "
</STATISTIKA>
";
  
  
?>

