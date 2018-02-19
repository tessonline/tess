<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/security_obj.inc")); 
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$datum=date('d.m.Y H:m');
include_once(FileUp2("html_header_full.inc")); 

//print_r($_POST);
$skartace=array();
$rizeni_id = $_POST['RIZENI_ID'];
$q=new DB_POSTA;
$a=new DB_POSTA;

if (!$rizeni_id) Die('neni predan parametr');
$sqlax = 'select * from posta_skartace where id='.$rizeni_id;
$q->query($sqlax); $q->Next_Record();
$jid_rizeni = $q->Record['JID'];



$text_vypis = '';
if ($uloz == 1) {

  $sql = 'delete from posta_skartace_soubory where rizeni_id=' . $rizeni_id;
  $q->query($sql);

  foreach($_POST['SELECT_ID'] as $val ) {
    $sql = "insert into posta_skartace_soubory (RIZENI_ID,SPISOVNA_ID) VALUES ($rizeni_id,$val)";
    $q->query($sql);
  }
  $text_vypis = 'Uloženo, soubory u vybraných dokumentů nebudou smazány.';
}

echo "<script>
function insertIds(el) {
       var tablename = '';
       var f_t = document.getElementsByName('frm_'+tablename);
        f_t = f_t[0];
        if (f_t != null) {
          for (var i=f_t.length-1; i>=0; i--) {
            if (unescape(f_t[i].name)=='SELECT_ID'+tablename+'[]' &&
                f_t[i].checked) {
                var input = document.createElement('INPUT');
                input.setAttribute('type', 'hidden');
                input.setAttribute('name', 'SELECT_ID'+tablename+'[]');
                input.setAttribute('value', f_t[i].value);
                el.appendChild(input);
            }
          }
        }
}
</script>
";

$sql=$_POST['sql'];
$sql_zaklad=$sql;
$q->query($sql);
$pocitadlo=0;

while ($q->Next_Record()) {
  $data=$q->Record;
  if ($data['CISLO_SPISU1']>1) {
    $sqla='select id from posta where cislo_spisu1='.$data['CISLO_SPISU1'].' and cislo_spisu2='.$data['CISLO_SPISU2'];
//    echo $sqla;
    $a->query($sqla); while ($a->Next_Record()) $skartace[]=$a->Record['ID'];
  }
  else
    $skartace[]=$data['ID'];

//  $spisObj = LoadClass('EedSpisovnaSimple', $data['DOKUMENT_ID']);

  if ($data['DIGITALNI'] > 0)
    $ukladam[$pocitadlo]=array('ID'=>$data['ID'],'CISLO_SPISU'=>$data['CISLO_SPISU1'].'/'.$data['CISLO_SPISU2'],'VEC'=>$data['VEC'],'ZNAK'=>$data[SKAR_ZNAK].'/'.$data[LHUTA],'LISTU'=>$data['LISTU'],'PRILOHY'=>$data['PRILOHY'],'DIGITALNE'=>$data['DIGITALNI']);

  $cs1[$pocitadlo]=$data['CISLO_SPISU1'];
  $cs2[$pocitadlo]=$data['CISLO_SPISU2'];
  $pocitadlo++;
}
//print_r($skartace);


{
  echo '<h1>Vyberte, u kterých digitálních dokumentů režimu A nebo S chcete uchovat přílohy</h1>';

  $sql = 'select * from posta_skartace_soubory where rizeni_id=' . $rizeni_id;
  $q->query($sql);
  while ($q->Next_Record())
    $GLOBALS['SELECT_ID'][] = $q->Record['SPISOVNA_ID'];

  if (count($ukladam)>0) {
    //print_r($DS_DATA2);
    include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
    $db_arr = new DB_Sql_Array;
    $db_arr->Data=$ukladam;
  //print_r($DS_DATA);
    $caption='Skartační řízení: ' .$jid_rizeni. '';
    $GLOBALS['SPISOVNA_PREDANI']=1;
    Table(
      array(
        "db_connector" => &$db_arr,
        "caption"=>$caption,
        "showaccess" => true,
        "schema_file"=>".admin/table_schema_predani.inc",
        "showedit"=>false,
        "showhistory"=>false,
        "showselect" => true,
        "multipleselect" => true,
    "multipleselectsupport"=>true,
        "showdelete"=>false,
        "showinfo"=>false
      )
    );

    if (strlen($text_vypis)>0) echo '<p><b><font color=green><i>' . $text_vypis . '</i></font></b></p>';

    echo '<form method="POST" action="soubory.php" onsubmit="insertIds(this);">
    <input type="hidden" name="sql" value="'.$sql_zaklad.'">
    <input type="hidden" name="spisovna" value="'.$spisovna_id.'">
    <input type="hidden" name="RIZENI_ID" value="'.$rizeni_id.'">
    <input type="hidden" name="uloz" value="1">
    <input type="hidden" name="protokol" value="'.$_POST["protokol"].'">
    ';
    echo "<input type='submit' name='' value='  Ponechat soubory u vybraných   ' class='button btn'>";
  }
  else {
    echo '<form>Nenalezeny dokumenty odpovídající podmínce hledání (ve skartačním řízení nejsou digitální dokumenty)<br/>';

  }

echo "
<input type='button' onclick='document.location.href=\"brow.php?SKARTACNI_RIZENI_ID=$rizeni_id\";' value='   Vrátit se   ' class='button btn'>";
  echo "</form>";
  include_once(FileUp2("html_footer.inc"));
  Die();
}

include_once(FileUp2("html_footer.inc"));
