<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2("posta/.admin/config.inc"));
include(FileUp2(".admin/status.inc"));
require_once(Fileup2("html_header_title.inc"));
//require(FileUp2(".admin/oth_funkce.inc"));
require(FileUp2(".admin/security_name.inc"));
require(FileUp2(".admin/security_obj.inc"));
require(FileUp2(".config/settings/agenda_path.inc"));

include_once(FileUp2(".admin/oth_funkce.inc"));

Function Uprav($text)
{ $text=trim($text);
  If ($text=="F") return 0;
  If ($text=="T") return 1;
	
}

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y H:m');

$GLOBALS["XERTEC_ID"]=explode(',',$id);
//$filename='../../../../../data_upload/xertec/frama.csv';
$cesta='../../../../../data_upload/xertec';
$cesta=$GLOBALS["TMAPY_DIR"].$SERVER_CONFIG["AGENDA_PATH"]["UPLOAD_SERVER_DIR"]."/xertec/";
$q=new DB_POSTA;

$file=array();
if (!$filename)
{
  $d = dir($cesta);
  //echo "Path: ".$d->path."<br>\n";
  while($entry=$d->read()) {
  if ($entry<>'.' && $entry<>'..' && substr($entry,-3)=="csv")
    $file[]=$entry;
  }
}
if (count($file)>1) 
{
  echo "<h3 align=center>Nalezeno více souborů</h3>
  <span class=text>Klikněte prosím na soubor, který chcete načíst.</span><br/><span class=text><br/>";

  while (list($key,$val)=each($file))
    echo "<a href='xertec.php?id=".$id."&povoleni=&filename=".$val."'><b>".$val."<a/> z ".Date('d.m.Y H:m:s',filemtime($cesta.$val))."</b><br/><br/>";
  
  require_once(Fileup2("html_footer.inc"));  
  Die();
}
elseif (!$filename)
  $filename=$file[0];


$filexertec=$cesta.$filename;
//echo $filexertec;
$file="";
if(File_Exists($filexertec)) {$param="r";} else Die("<h1>Chyba, soubor nenalezen</h1>");
$fp=FOpen($filexertec,$param);
while (!feof($fp)) $file.=FRead($fp,1024);
FClose($fp);
$radky=array();
$file=nl2br($file);
$radky=explode('<br />',$file);
$zbytek=array_pop($radky);

If (!(count($GLOBALS["XERTEC_ID"])==count($radky)) && !$povoleni) {
  echo "<h1>Chyba</h1>Obálek bylo ke zvážení: ".count($GLOBALS["XERTEC_ID"])." ks<br/>zváženo bylo ".count($radky)."</span><br /><br />";
  echo "<center><input type='button' class='btn' value='Zpět pro nové vážení' onclick=\"history.go(-1)\"></center><br/>";

  echo "<center><input type='button' class='btn' value='Skutečně načíst!' onclick=\"window.location.href='xertec.php?id=".$id."&povoleni=true&filename=".$filename."'\"></center>";
  require_once(Fileup2("html_footer.inc"));  
}
else {
  $sql="select max(xertec_id) as max_id from posta";
//$sql="update posta set druhe_dodani=".$xertec[10]." where id=".$GLOBALS["XERTEC_ID"][$i];
	$q->query($sql);
	$q->Next_Record();

	$a=$q->Record["MAX_ID"];
	$a++;
	$i=0;
  $xertec=array();
  echo '<h1 align=center>Načtené obálky</h1>';
  echo '<table width="80%" align=center class="table-body">
  <thead><tr><th width="10%">pořadí</th><th width="10%">Čárový kód</th><th width="40%">Adresát</th><th width="15%">cena</th><th width="15%">hmotnost</th></tr></thead>';
//  echo "<hr/>";
  while (list ($key, $val) = each ($radky)) 
	{
//    echo $val."<br/>";
    $xertec=explode(';',$val);
  			
  /*		
  1. IDKODU = obsah čárového kódu
  2. HMOTNOST = hmotnost zásilky v g
  3. CENA = poątovne v kč format 0.00 / bez uvedení Kč, oddělovač tečka-možno změnit /
  4. DATUM = formát DDMMRR např. 31.12.2003 jako 311203 ( možno upravit )
  5. DRUHZASILKY = číselná zkratka / max 2 znaky číslo 0-10 /
     0 = Psaní
     1 = Cenné psaní
     2 = Doporučené psaní
     3 = Psaní standard / za 6.40 /
     4 = Psaní obchodní
     5 = balíky
     6 = cenné balíky
     7 = doporučené balíky
     8 = poukázka				
     9 = EMS
    10 = jiný druh - poątovné nastaveno uživatelem /DSET na stroji /
  
  6. TUZEMSKO = zásilka do ČR / Ano/Ne = zkratkou T/F (true/false)
  7. DODEJKA = zásilka má dodejku / Ano/Ne = zkratkou T/F (true/false)
  8. VLRUKOU = zásilka je do vl. rukou / Ano/Ne = zkratkou T/F (true/false)
  9. DOBIRKA = zásilka má dobírku / Ano/Ne = zkratkou T/F (true/false)
  10. UDANACENA = zásilka má udanou cenu / Ano/Ne = zkratkou T/F (true/false)
  11. DRUHE DODANI = zásilka má službu druhé dodání / Ano/Ne = zkratkou T/F (true/false)		
  */
//    print_r($xertec);
		
		$idcko = PrevedCPnaID($xertec[0]);
    if (!$idcko) $idcko = $GLOBALS["XERTEC_ID"][$i];
    if ($idcko>1) {
      $class = 'table-row-even';
      if ($i%2 == 0) $class = 'table-row-odd';
      echo '<tr class="brow '.$class.'"><td>'.($i+1).'</td><td>'.$xertec[0].'</td><td>'.UkazAdresu($idcko,', ').'</td><td>'.$xertec[2].'</td><td>'.$xertec[1].'</td></tr>';
	  	$sql="update posta set hmotnost=".$xertec[1].",cena=".$xertec[2].",druh_zasilky=".$xertec[4].",druhe_dodani=".Uprav($xertec[10]).",xertec_id=".$a.",last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id=".$idcko;
//      echo $sql . '<br/>';
  		$q->query($sql);
      NastavStatus($idcko);
    }
    else
      echo '<tr style="color:red"><td>'.($i+1).'</td><td>'.$xertec[0].'</td><td>Obálka nenalezena!</td><td>'.$xertec[2].'</td><td>'.$xertec[1].'</td></tr>';
   
//		echo $sql."<br/>";
    $i++;
		$a++;

  }
  echo "</table>";
  echo "<p align=center><input type='button' class='btn' value='Hotovo, zpracováno ".$i." obálek'></p>";
//  chmod ($filename, 777); 
  //unlink($filexertec);
  require_once(Fileup2("html_footer.inc"));  

}
?>
