<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/run2_.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require(FileUp2(".admin/funkce.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2("html_header.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/upload_.inc"));
require(FileUp2(".admin/status.inc"));
require(FileUp2(".admin/isds_.inc"));
$dbDS=new DB_POSTA;
$c=new DB_POSTA;
$a=new DB_POSTA;
require_once(FileUp2(".admin/upload_.inc"));
  

set_time_limit(0);

$USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$LAST_TIME=Date('H:i:s');
$LAST_DATE=Date('Y-m-d');

//inicializace NuSOAP
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php"); 
$eed_konektor=$GLOBALS["KONEKTOR"]["SOAP_SERVER"];

if (strpos($eed_konektor,'?')) $eed_konektor.='&LAST_USER_ID='.$USER_INFO["ID"];
else $eed_konektor.='?LAST_USER_ID='.$USER_INFO["ID"];

$add_info="last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=".$LAST_USER_ID;

echo '<div id="upl_wait_message" class="text" style="display:block"></div>';
echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Kontaktuji datovou schránku...'</script>";Flush();

$schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],'');

echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Načítám seznam doručenek...'</script>";Flush();

$sql="select * from posta_DS where odeslana_posta='t' and ((datum_precteni is NULL) or (datum_doruceni is NULL)) order by posta_id desc";
//echo $sql;
$b=0;
$dbDS->query($sql);
$pocet_dorucenek=$dbDS->Num_Rows();
while ($dbDS->Next_Record()) {
  include('.admin/dorucenky.inc');
  
  $DS_DATA[] = array(
      "id"=>$a->Record[ID],
      "nase_cj"=>$dbDS->Record[CISLO_SPISU1]."&nbsp;",
      "nas_spis"=>$dbDS->Record[CISLO_SPISU2]."&nbsp;",
      "datum"=>$a->Record[DATUM_PODATELNA_PRIJETI],
      "from"=>UkazAdresu($dbDS->Record[POSTA_ID],', '),
      "vec"=>$a->Record[VEC],
      "vypraveni"=>$doruceni_datum,
      "doruceni"=>$precteni."<br/>".$text_dorucenka,
      "odkaz"=>$href
  );
  unset($client);
  unset($soubor);
  //echo $sql;
}
echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
$db_arr = new DB_Sql_Array;
$db_arr->Data=$DS_DATA;

if (count($DS_DATA)>0)
  Table(array("db_connector" => &$db_arr,"showaccess" => true,"appendwhere"=>$where2,"showedit"=>false,"showdelete"=>false,"showselect"=>false,"showinfo"=>false,"multipleselect"=>false,"schema_file"=>".admin/table_schema_DORUCENKY.inc","caption"=>"Doručenky"));  
else
  echo "<span class='caption'>Doručenky</span><span class='text'><br/>Žádné doručenky nebyly nalezeny.</span>";



require(FileUp2("html_footer.inc"));
