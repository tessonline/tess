<?php 
// V PHP 4.1.0 a pozdějších by mělo být použito $_FILES namísto $HTTP_POST_FILES.
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
if (is_uploaded_file($_FILES['userfile']['tmp_name'])) 
{
  $filename=$_FILES['userfile']['tmp_name'];
  //zkusime nacist ten soubor...
  $fp=FOpen($filename,'r');
  while (!feof($fp)) $sql.=FRead($fp,1024);
  FClose($fp);
  $sql=nl2br(strip_tags($sql));
  $sql2=array();
  $sql2=explode('<br />',$sql);
  while (list ($key, $val) = each ($sql2)) 
  {
    $hodnoty=array();
    $hodnoty=explode(';',$val);
    $jmeno=$hodnoty[10];
    $datum=$hodnoty[0]." ".$hodnoty[1];
    list($cj1,$cj2,$cj3)=explode('/',$hodnoty[14]);
    If (trim($cj1)=='') 
    {
      $jmeno=$jmeno." - <b>Nenalezeno číslo jednací</b>";
      echo $jmeno."<br/>";
    }
    else
    {
      //echo $datum." - ".$cj1."/".$cj2." ".$cj3." - ".$jmeno." - ";
      $sql="select id from posta where cislo_spisu1=".$cj1." and cislo_spisu2=".$cj2." and podcislo_spisu=".$cj3."";
      $q=new DB_DEFAULT;
      $q->query($sql);
      $pocet=$q->Num_Rows();
      If ($pocet==1) 
      {
        $q->Next_Record(); $idcko=$q->Record["ID"];
        $sql="update posta set datum_vypraveni='".$datum."' where id=".$idcko;
        NastavStatus($idcko);
//        echo $sql."<br/>";
        echo $jmeno." OK.<br/>";
        $q->query($sql);
      }
      else
      {
        $idcko=0;
        echo $jmeno." - <b>ID nenalezeno</b><br/>";
      }
    }
  }
  
}
else 
{
  echo "Nepovedlo se nahrat soubor na server. Filename: " . $HTTP_POST_FILES['userfile']['name'];
}
/* ...or... */
//move_uploaded_file($HTTP_POST_FILES['userfile']['tmp_name'], "/place/to/put/uploaded/file");
echo "<br/><p align=right><input type='button' class='button btn' onclick='window.close()' value='   Zavřít   '>&nbsp;&nbsp;&nbsp;</p><br /><br />";
require(FileUp2("html_footer.inc"));

?>
