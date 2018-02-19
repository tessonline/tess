<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/status.inc"));
require(FileUp2(".admin/security_name.inc"));
require_once(Fileup2("html_header_title.inc"));
//Uprava datumu
$where="";
//$where.=" odbor IN (".$GLOBALS["ODBOR"].")";
If ($GLOBALS["CONFIG"]["DB"]=='psql')
{
  $where.=" (DATUM_PODATELNA_PRIJETI) >= ('".$GLOBALS["DATUM_OD"]."')";
  $where.=" AND (DATUM_PODATELNA_PRIJETI) <= ('".$GLOBALS["DATUM_DO"]."')";
}
If ($GLOBALS["CONFIG"]["DB"]=='mssql')
{
  $where.=" CONVERT(datetime,datum_podatelna_prijeti,104) >= CONVERT(datetime,'".$GLOBALS["DATUM_OD"]."',104)";
  $where.=" AND CONVERT(datetime,datum_podatelna_prijeti,104) <= CONVERT(datetime,'".$GLOBALS["DATUM_DO"]."',104)";
}

$EddSql = LoadClass('EedSql',$USER_INFO['ID']);
$where .= "AND (" . $EddSql->WhereOdborAndPrac($GLOBALS['ODBOR']) . ")";

$where .=" AND odeslana_posta='t'";
$where .=" AND vlastnich_rukou='1'";
$where .=" AND stornovano is null AND (datum_vypraveni is null)";
$where .=" AND hmotnost is null ";
 
UNSET($GLOBALS["ODBOR"]);
$filename='../../../../../data_upload/xertec/frama.csv';
If (file_exists($filename))  unlink($filename);

$q=new DB_POSTA;
$id=array();

//$where2=" AND (doporucene='1' or doporucene='2' or doporucene='3' or doporucene='4' or doporucene='5' or doporucene='Z')";
/*
$sql='select * from posta where '.$where.$where2.' order by id';
//echo $sql;
$q=new DB_POSTA;
$q->query($sql);
$id=array();
While ($q->Next_Record()) $id[]=$q->Record["ID"];
*/
//$GLOBALS["XERTEC_ID"]=$id;
//print_r($GLOBALS["XERTEC_ID"]);
echo "<h1>FRANKOVÁNÍ OBÁLEK</span></h1>
Nejdříve prosím seřaďte obálky tak, jak jsou uvedeny v tomto seznamu (první obálka bude úplně nahoře) - pokud nepoužíváte čárové kódy.<br/> Po zvážení všech obálek klikněte na odkaz <b>Načíst soubor z XERTECu</b>";


$where2=" AND doporucene='1'";
$sql='select * from posta where '.$where.$where2.' ORDER BY doporucene,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti';
$count = Table(array(
         "sql"=>$sql,
				 "caption"=>"Obyčejná pošta",
			   "appendwhere"=>$where.$where2,
         "page_size"=>500,
//         "agenda"=>"POSTA_C_JEDNACI",
         "showhistory"=>false,
				 "emptyoutput"=>true, 
         "maxnumrows"=>500,
				 "nopaging"=>true,
				 "showcount"=>true,
         "showdelete"=>false, 
         "showedit"=>false,
         "showinfo"=>false,	 
         "nocaption"=>false,
         "showaccess"=>true,
  	     "setvars"=>true, 
));
$q->query($sql);
While ($q->Next_Record()) $id[]=$q->Record["ID"];
//print_r($id);

$where2=" AND doporucene='2'";
$sql='select * from posta where '.$where.$where2.'ORDER BY doporucene,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti';
$count = Table(array(
         "sql"=>$sql,
				 "caption"=>"Doporučeně",
			   "appendwhere"=>$where.$where2,
         "page_size"=>500,
				 "emptyoutput"=>true, 
         "maxnumrows"=>500,
				 "nopaging"=>true,
				 "showcount"=>true,
         "showdelete"=>false, 
         "showedit"=>false,
         "showinfo"=>false,	 
         "nocaption"=>false,
         "showaccess"=>true,
  	     "setvars"=>true, 
));
$q->query($sql);
While ($q->Next_Record()) $id[]=$q->Record["ID"];
//print_r($id);


$where2=" AND doporucene='3'";
$sql='select * from posta where '.$where.$where2.' ORDER BY doporucene,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti';
$count = Table(array(
         "sql"=>$sql,
				 "caption"=>"Dodejky",
			   "appendwhere"=>$where.$where2,
         "page_size"=>500,
         "maxnumrows"=>500,
//         "agenda"=>"POSTA_C_JEDNACI",
         "showhistory"=>false,
				 "nopaging"=>true,
				 "showcount"=>true,
				 "emptyoutput"=>true, 
         "showdelete"=>false, 
         "showedit"=>false,
         "showinfo"=>false,	 
         "nocaption"=>false,
         "showaccess"=>true,
  	     "setvars"=>true, 
));
$q->query($sql);
While ($q->Next_Record()) $id[]=$q->Record["ID"];
//print_r($id);


$where2=" AND doporucene='4'";
$sql='select * from posta where '.$where.$where2.' ORDER BY doporucene,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti';
$count = Table(array(
         "sql"=>$sql,
				 "caption"=>"Dodejky do vlastních rukou",
			   "appendwhere"=>$where.$where2,
//         "agenda"=>"POSTA_C_JEDNACI",
         "showhistory"=>false,
         "page_size"=>500,
         "maxnumrows"=>500,
				 "nopaging"=>true,
				 "showcount"=>true,
         "showdelete"=>false, 
         "showedit"=>false,
         "showinfo"=>false,	 
				 "emptyoutput"=>true, 
         "nocaption"=>false,
         "showaccess"=>true,
  	     "setvars"=>true, 
));
$q->query($sql);
While ($q->Next_Record()) $id[]=$q->Record["ID"];
//print_r($id);



$where2=" AND doporucene='5'";
$sql='select * from posta where '.$where.$where2.' ORDER BY doporucene,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti';
$count = Table(array(
         "sql"=>$sql,
				 "caption"=>"Dodejky pro zástupce",
			   "appendwhere"=>$where.$where2,
         "page_size"=>500,
//         "agenda"=>"POSTA_C_JEDNACI",
         "showhistory"=>false,
         "maxnumrows"=>500,
				 "nopaging"=>true,
				 "showcount"=>true,
         "showdelete"=>false, 
				 "emptyoutput"=>true, 
         "showedit"=>false,
         "showinfo"=>false,	 
         "nocaption"=>false,
         "showaccess"=>true,
  	     "setvars"=>true, 
));
$q->query($sql);
While ($q->Next_Record()) $id[]=$q->Record["ID"];


$where2=" AND doporucene='Z'";
$sql='select * from posta where '.$where.$where2.' ORDER BY doporucene,cislo_jednaci2,cislo_jednaci1,datum_podatelna_prijeti';
$count = Table(array(
         "sql"=>$sql,
				 "caption"=>"Do zahraničí",
			   "appendwhere"=>$where.$where2,
         "page_size"=>500,
//         "agenda"=>"POSTA_C_JEDNACI",
         "showhistory"=>false,
         "maxnumrows"=>500,
				 "nopaging"=>true,
				 "showcount"=>true,
         "showdelete"=>false, 
				 "emptyoutput"=>true, 
         "showedit"=>false,
         "showinfo"=>false,	 
         "nocaption"=>false,
         "showaccess"=>true,
  	     "setvars"=>true, 
));
$q->query($sql);
While ($q->Next_Record()) $id[]=$q->Record["ID"];
//print_r($id);





If (count($id)>0)
echo "<center>
<input type='button' class='btn' value='Vytisknout seznam&nbsp;&nbsp;&nbsp;' onclick=\"window.print();\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<input type='button' class='btn' value='Načíst soubor z XERTECu' onclick=\"window.open('xertec.php?id=".implode(',',$id)."', 'xertex', 'height=10px,width=10px,left=0,top=0,scrollbars,resizable');\">
</center>";
require_once(Fileup2("html_footer.inc"));  

?>

