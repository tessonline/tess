<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/run2_.inc"));
include(FileUp2(".admin/upload_.inc"));
include_once(FileUp2(".admin/security_obj.inc"));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$datum=date('d.m.Y H:m');
include_once(FileUp2("html_header_full.inc")); 

$sql=$_POST['sql'];
$sql_zaklad=$sql;
//print_r($_POST);
$skartace=array();
$rizeni_id = $_POST['RIZENI_ID'];
$q=new DB_POSTA;
$a=new DB_POSTA;

if (!$rizeni_id) Die('neni predan parametr');
$sqlax = 'select * from posta_skartace where id='.$rizeni_id;
$q->query($sqlax); $q->Next_Record();
$jid_rizeni = $q->Record['JID'];

$q->query($sql);
$pocitadlo=0;
while ($q->Next_Record()) {

  $data=$q->Record;
  $skartace_main[] = $data['DOKUMENT_ID'];
//  echo "Zpracovavam ".$data['ID']." - ".$data['CISLO_SPISU1']."<br/>";
  if ($data['CISLO_SPISU1']>1) {
    $sqla='select id from posta where cislo_spisu1='.$data['CISLO_SPISU1'].' and cislo_spisu2='.$data['CISLO_SPISU2'].' and superodbor=' . $data['SUPERODBOR'];
    $a->query($sqla); while ($a->Next_Record()) $skartace[]=$a->Record['ID'];
  }
  else
    $skartace[]=$data['DOKUMENT_ID'];

  $data[SKAR_ZNAK] = ($data[SKAR_ZNAK_ALT] <> '') ? $data[SKAR_ZNAK_ALT] : $data[SKAR_ZNAK];
  $ukladam[$pocitadlo]=array('ID'=>$pocitadlo,'CISLO_SPISU'=>$data['CISLO_SPISU1'].'/'.$data['CISLO_SPISU2'],'VEC'=>$data['VEC'],'ZNAK'=>$data[SKAR_ZNAK].'/'.$data[LHUTA],'LISTU'=>$data['LISTU'],'PRILOHY'=>$data['PRILOHY'],'DIGITALNE'=>$data['DIGITALNI']);

  $cs1[$pocitadlo]=$data['CISLO_SPISU1'];
  $cs2[$pocitadlo]=$data['CISLO_SPISU2'];
  $ident[$pocitadlo]=$data['ID'];
  $pocitadlo++;

}
//print_r($skartace);

$soubory = array();
$sql = 'select * from posta_skartace_soubory where rizeni_id=' . $rizeni_id;
$q->query($sql);
while ($q->Next_Record()) {
  $sql = 'select * from posta_spisovna where id=' . $q->Record['SPISOVNA_ID'];
  $a->query($sql);
  $a->Next_Record(); $data = $a->Record;
  $data[SKAR_ZNAK] = ($data[SKAR_ZNAK_ALT] <> '') ? $data[SKAR_ZNAK_ALT] : $data[SKAR_ZNAK];
  $soubory[] = array('ID'=>$data['ID'],'CISLO_SPISU'=>$data['CISLO_SPISU1'].'/'.$data['CISLO_SPISU2'],'VEC'=>$data['VEC'],'ZNAK'=>$data[SKAR_ZNAK].'/'.$data[LHUTA],'LISTU'=>$data['LISTU'],'PRILOHY'=>$data['PRILOHY'],'DIGITALNE'=>$data['DIGITALNI']);
  $soubory_ponechat[] = $data['DOKUMENT_ID'];

}


if (!$uloz) {

  //print_r($DS_DATA2);
  include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
  $db_arr = new DB_Sql_Array;
  $db_arr->Data=$ukladam;
//print_r($DS_DATA);
  $caption='Skartační řízení: ' .$jid_rizeni. ' - Dokumenty, které budou finálně vyřazeny';
  $GLOBALS['SPISOVNA_PREDANI']=1;
  Table(array("db_connector" => &$db_arr,"caption"=>$caption,"showaccess" => false,"schema_file"=>".admin/table_schema_predani.inc","showedit"=>false,"showdelete"=>false,"showselect"=>false,"showinfo"=>false,"showhistory"=>false));


  if (count($soubory)>0) {
    $db_arr->Data=$soubory;
    $caption='Skartační řízení: ' .$jid_rizeni. ' - Dokumenty, kde budou zachovány soubory';
    $GLOBALS['SPISOVNA_PREDANI']=1;
    Table(array("db_connector" => &$db_arr,"caption"=>$caption,"showaccess" => false,"schema_file"=>".admin/table_schema_predani.inc","showedit"=>false,"showdelete"=>false,"showselect"=>false,"showinfo"=>false,"showhistory"=>false));
  }


  echo '<form method="POST" action="skartace.php">
  <input type="hidden" name="sql" value="'.$sql_zaklad.'">
  <input type="hidden" name="spisovna" value="'.$spisovna_id.'">
  <input type="hidden" name="RIZENI_ID" value="'.$rizeni_id.'">
  <input type="hidden" name="uloz" value="1">
  <input type="hidden" name="protokol" value="'.$_POST["protokol"].'">
  ';
  echo "<input type='submit' name='' value='  Skutečně vyřadit   ' class='button btn'>";
echo "
<input type='button' onclick='document.location.href=\"brow.php?SKARTACNI_RIZENI_ID=$rizeni_id\";' value='   Vrátit se   ' class='button btn'>";
  echo "</form>";
  include_once(FileUp2("html_footer.inc"));
  Die();
}

$uplobj = Upload(array(
            'create_only_objects' => true,
            'agenda' => 'POSTA',
            'noshowheader'=>true)
          );


Access(array("agenda"=>"POSTA"));
while (list($key,$val)=each($skartace_main)) {
  if ($val>0) {
    $sql = 'select * from posta_spisovna where dokument_id=' . $val;
    $a->query($sql);
    $a->Next_Record();
    if ($a->Record['SKAR_ZNAK'] == 'A') {$status = -6; $slovo = 'archivován';} else {$status = -2; $slovo = 'skartován';}
    $EedCj = LoadClass('EedCj', $val);
    $docs = $EedCj->GetDocsInCJ($val);
    while (list($key2, $val2) = each($docs)) {

      if (@in_array($val, $soubory_ponechat) || @in_array($val2, $soubory_ponechat)) {
      } else
      {
        $sql = "delete from files where agenda_ident like 'POSTA' and record_id=" . $val2;
        if ($uloz) $q->query($sql);
      }

      $text = 'dokument byl ' . $slovo . ' v rámci skartačního řízení <b>' . $jid_rizeni .'</b>';
      $sql="update posta SET status=$status,skartovano='".$datum."',last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where id=".$val2;
      if ($uloz) $q->query($sql);
      EedTransakce::ZapisLog($val2, $text, 'DOC', $id_user);

  //    echo $sql."<br/>";

    }
    EedTransakce::ZapisLog($val, $text, 'SPIS', $id_user);
  }
}



while (list($key,$val)=each($ident)) {

  $sql="update posta_spisovna set datum_skartace='".Date('Y-m-d')."',last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where id=". $val;
//    $sql="update posta SET status=-2,skartovano='".$datum."',last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where id=".$val;
    if ($uloz) $q->query($sql);
}
//Die();

echo "<br/><br/><span class='caption'>Hotovo, dokumenty byly  vyřazeny </span><br/>";
echo "
<input type='button' onclick='document.location.href=\"edit.php?filter\";' value='Vrátit se' class='button btn'>";
include_once(FileUp2("html_footer.inc")); 
