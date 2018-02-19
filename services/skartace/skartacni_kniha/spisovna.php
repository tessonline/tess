<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
include(FileUp2(".admin/edit_.inc"));
include_once(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/security_name.inc"));
include_once(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));
include_once(FileUp2(".admin/security_obj.inc")); 
include_once(FileUp2(".admin/oth_funkce_2D.inc"));
include_once(FileUp2("html_header_full.inc"));
include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select_db.inc");
require_once(FileUp2(".admin/el/of_select_.inc"));

echo '
<link rel="stylesheet" href="jquery-ui.css">

<style>

.ui-helper-hidden-accessible {
    border: 0;
    clip: rect(0 0 0 0);
    height: 1px;
    margin: -1px;
    overflow: hidden;
    padding: 0;
    position: absolute;
    width: 1px;
}
.ui-autocomplete {
     z-index: 9999 !important;
}

</style>
<script>
$(function() {
    $( "#txtAuto" ).autocomplete({
        source: "getLokace.php?spisovna_id=' . $_POST['spisovna'] . '",
        minLength: 3,
        select: function( event, ui ) {
            if(ui.item) {
                document.getElementById(\'lokace_id\').value = ui.item.id;
                $("#LokaceId").val(ui.item.id);
            }
        },
        change: function(event, ui) {
            if(!ui.item) {
                $("#LokaceId").val(0);
                $(this).val("");
            }
        }
    });
});
</script>
';

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$last_date=Date('Y-m-d');
$last_time=Date('H:i:s');
$datum=date('d.m.Y H:m');

if (is_array($_POST['SELECT_ID']) && !$_POST['box']) {
  if (count($_POST['SELECT_ID'])>0)
    $_POST['sql'] = str_replace(' ORDER BY ', 'and p.id in (' . implode(',',$_POST['SELECT_ID']). ') ORDER BY ', $_POST['sql']);
}

$q=new DB_POSTA;
$a=new DB_POSTA;
$b=new DB_POSTA;
$c=new DB_POSTA;
$q->query($sql);
$pocitadlo=0;
$spis_counter=0;


if ($_POST['box'] == 1) {
  if (count($_POST['SELECT_ID'])>0)
    $_POST['sql'] = str_replace(' ORDER BY ', 'and id in (' . implode(',',$_POST['SELECT_ID']). ') ORDER BY ', $_POST['sql']);
  $q->query($_POST['sql']);
  while ($q->Next_Record()) {
    $box_id = $q->Record['ID'];
    $a->query('SELECT * from posta_spisovna_boxy_ids where box_id=' . $box_id);
    while ($a->Next_Record()) {
      $IDcka[] = $a->Record['POSTA_ID'];
    }
  }
  if (count($IDcka)>0) {
    $sql = 'SELECT p.* from posta_view_spisy p LEFT JOIN cis_posta_skartace k ON p.skartace = k.id WHERE ( (p.status=1 or p.status=-4 or p.status=-5) and p.skartace<>0 ) AND exists (select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id and (dalsi_spis_id=spis_id or dalsi_spis_id=0)) and WHEREPODMINKA ORDER BY p.cislo_spisu2 asc, p.cislo_spisu1 asc, p.ID ASC';
    $wherepodminka = 'p.id in (' . implode(',', $IDcka) . ')';
    $sql = str_replace('WHEREPODMINKA', $wherepodminka, $sql);
    $_POST['sql'] = $sql;
  }
  else {
    include(FileUp2('html_footer.inc'));
    Die('V boxech nebyly nalezeny žádné dokumenty');
  }

}


$sql=$_POST['sql'];
$sql_zaklad=$_POST['sql'];
//echo $sql;
$spisovna_id=$_POST['spisovna'];


$uloz=false;

//print_r($_POST);Die();
$protokol=false;

if ($_POST['protokol']) $protokol=true;
if ($_POST['uloz']) $uloz=true;
if ($_POST['protokol_id']) $pred_protokol_id=$_POST['protokol_id']?$_POST['protokol_id']:0;
$skartace=array();



$cs1=array();

$sqla='select * from posta_cis_spisovna where id=' . $spisovna_id;
$a->query($sqla);
$a->Next_Record();
$spisovna_nazev = $a->Record['SPISOVNA'];

$q->query($sql);

$lokace_id = $_POST['LOKACE_ID'] ? $_POST['LOKACE_ID'] : 0;

$files_to_convert = array();

$celkem=$q->Num_Rows();
$puvodni_skartace=0;
$superodbor=VratSuperOdbor();

while ($q->Next_Record()) {
  $data=$q->Record; $pocitadlo++;
  $digitalnich=0;
  //echo "Zpracovavam ".$data['ID']." - ".$data['CISLO_SPISU1']."<br/>";
//  $pred_protokol_id=$data['ID']; //sem ulozime ID spisu, ktery bude posledni... ten ulozime jako cislo protokolu...
  $pocet_priloh_celkem=array();
  if ($data['CISLO_SPISU1']>0) {

//    if (!$_POST['box'])
    {
      $cj=LoadClass('EedCj', $data['ID']);
      $cj_so = $cj->superodbor;
      $skar_rezim = $cj->getSkartacniRezim($data['ID']);
      $dalsi_dokumenty=$cj->GetDocsInCj($data['ID']);
      $where_spis = "id in (" . $data['ID'] . "," . implode(',',$dalsi_dokumenty).")";
      $sqla='select * from posta where ('.$where_spis.') and stornovano is null and superodbor in ('.$cj_so.') order by id asc';
  //    $sqla='select * from posta where ('.$where_spis.') and stornovano is null order by id asc';
      $a->query($sqla);
      $a->Next_Record();
      $id=$a->Record['ID'];
  //    echo "ID".$id."<br/>";
      $skartace[]=$a->Record['ID'];
      if (!in_array($a->Record['CISLO_SPISU1'],$cs1))
       {
         $spis_counter++;
         $cs1[$spis_counter]=$a->Record['CISLO_SPISU1'];
         $cs2[$spis_counter]=$a->Record['CISLO_SPISU2'];
       }
      $skartace_id=$a->Record['SKARTACE'];
      if ($skartace_id<1 || $skartace_id=='') $skartace_id=$puvodni_skartace;
      else
        $puvodni_skartace=$skartace_id;
      $skar_pole=Skartace_Pole($skartace_id);
      $skar_pole = $cj->SpisZnak($id);
      if ($skar_pole[znak]=='X') $skar_pole[znak]="";
      if ($skar_pole[znak]=='') $skar_pole[znak]="";
      if ($skar_pole[doba]=='') $skar_pole[doba]="-1";

      if ($skar_rezim['znak']<>'') $skar_pole['znak'] = $skar_rezim['znak'];
      if ($skar_rezim['doba']>0) $skar_pole['doba'] = $skar_rezim['doba'];

  //    print_r($skar_pole);
      $dokument_id=$a->Record['ID'] ? $a->Record['ID'] : 0;

      $sql = 'select * from posta_spisovna where dokument_id='.$dokument_id;
      $c->query($sql); $c->Next_Record();
//       $skartace_id_nove = $c->Record['SKARTACE_ID'] ? $c->Record['SKARTACE_ID'] : 0;
//       if ($skartace_id_nove>0) {
//         $skar_pole=Skartace_Pole($skartace_id_nove);
//       }


      $c->query('SELECT * from posta_spisovna_boxy_ids where posta_id=' . $dokument_id);
      while ($c->Next_Record()) {
        $BOX[] = $c->Record['BOX_ID'];
      }


      $sql = 'select * from posta_spisovna where dokument_id='.$dokument_id;
      $c->query($sql); $c->Next_Record();


      $vec=$a->Record['VEC'];

      $cj_obj = LoadClass('EedCj',$dokument_id);

      $cj_info = $cj_obj->GetCjInfo($dokument_id);
      $c_jednaci = $cj_obj->cislo_jednaci;
      $nazev_spisu = $cj_info['NAZEV_SPISU'];
      $cislo_spisu = $cj_info['CELE_CISLO'];

      if ($nazev_spisu<>'') $vec = $nazev_spisu;

      $pocet_listu_celkem=$a->Record['POCET_LISTU'];
      $pocet_priloh = $a->Record["POCET_PRILOH"];
      $druh_priloh = trim($a->Record["DRUH_PRILOH"]);
      if ($a->Record['SKARTACE']==2398 || $a->Record['TYP_DOKUMENTU']=='D') {$pocet_listu_celkem=0; $pocet_priloh=0;}//neni urceno ke skartaci
      if ($a->Record['TYP_DOKUMENTU']=='D' && $a->Record['SKARTACE']<>2398 ) {$digitalnich++;}//neni urceno ke skartaci
      $spis_vyrizen=$a->Record['SPIS_VYRIZEN'];
      $pocet_priloh_celkem[$druh_priloh]=$pocet_priloh_celkem[$druh_priloh]+$pocet_priloh;
  //       echo "$druh_priloh x $pocet_priloh - ".count($pocet_priloh_celkem)."<br/>";
      $id=$a->Record['ID']?$a->Record['ID']:0;

//        $upl_obj = LoadClass('EedUploadPdf', $dokument_id);
//
//       if (!$uloz) $files_to_convert = $upl_obj->testPDF();
//       if ($uloz) $files_to_convert = $upl_obj->registerPDF();

      while ($a->Next_Record()) {
        $skartace[]=$a->Record['ID'];
        if ($skar_pole[znak]=="") {
          $skar_pole=Skartace_Pole($a->Record['SKARTACE']);
  //        print_r($skar_pole);
          if ($skar_pole[znak]=='X') $skar_pole[znak]="";
          if ($skar_pole[doba]=='') $skar_pole[doba]="-1";
          if ($skar_rezim['znak']<>'') $skar_pole['znak'] = $skar_rezim['znak'];
          if ($skar_rezim['doba']>0) $skar_pole['doba'] = $skar_rezim['doba'];
        }
  //    echo "ID".$a->Record['ID']."<br/>";
        if (!in_array($a->Record['CISLO_SPISU1'],$cs1)) {
          $spis_counter++;
          $cs1[$spis_counter]=$a->Record['CISLO_SPISU1'];
          $cs2[$spis_counter]=$a->Record['CISLO_SPISU2'];
        }
        $pocet_listu = $a->Record["POCET_LISTU"];
        $pocet_priloh = $a->Record["POCET_PRILOH"];
        $druh_priloh = $a->Record["DRUH_PRILOH"];
  //      if ($a->Record['SKARTACE']==2398 || $a->Record['TYP_DOKUMENTU']=='D' || $a->Record['ODES_TYP']=='X') {$pocet_listu=0; $pocet_priloh=0;}//neni urceno ke skartaci
        if ($a->Record['SKARTACE']==2398 || $a->Record['TYP_DOKUMENTU']=='D') {$pocet_listu=0; $pocet_priloh=0;}//neni urceno ke skartaci
        if ($a->Record['TYP_DOKUMENTU']=='D' && $a->Record['SKARTACE']<>2398 ) {$digitalnich++;}//neni urceno ke skartaci

        $pocet_listu_celkem=$pocet_listu_celkem+$pocet_listu;
        $pocet_priloh_celkem[$druh_priloh]=$pocet_priloh_celkem[$druh_priloh]+$pocet_priloh;
  //     echo "$druh_priloh x $pocet_priloh - ".count($pocet_priloh_celkem)."<br/>";

//       $sql='select listu from posta_spisobal where posta_id='.$a->Record['ID'];
// //      echo $sql;
//       $b->query($sql); $b->Next_Record();
//       $pocet=$b->Record['LISTU']; if (!$pocet) $pocet==0;
//   //    if ($pocet>0 && !$protokol) $pocet_listu_celkem=$pocet_listu_celkem+$pocet; //pricteme spis obal a prehled
//       //if ($pocet>0 && !$protokol) {echo $sql; $pocet_listu_celkem=$pocet_listu_celkem+$pocet; }//pricteme spis obal a prehled
//       //pricteme pouze jednou, jde o spisy (vice cj, pokud maji kazdy vlastni pocet listu)
//       if ($pocet>0 && !$protokol && !$uz_nacteno) {$uz_nacteno=true; $pocet_listu_celkem=$pocet_listu_celkem+$pocet; }//pricteme spis obal a prehled
      }
      $datum_uzavreni=explode("-",$spis_vyrizen);
  //    echo $datum_vyrizeni;
      $rok_uzavreni=$datum_uzavreni[0];
      if ($rok_uzavreni == 0) $rok_uzavreni = Date('Y');
    //tady pricist pripadne prebal
      $prilohy="";
  //    print_r($pocet_priloh_celkem);
      while (list($key,$val)=each($pocet_priloh_celkem)) { if ($val>0) $prilohy.="$key: $val<br/>";}
  //     echo "$druh_priloh x $pocet_priloh - ".count($pocet_priloh_celkem)."<br/>";

      if ($pricist_listy && $pocitadlo==$celkem)
        $pocet_listu_celkem=$pocet_listu_celkem+$pricist_listy; //echo "Pricitam";

      if (!$pocet_listu_celkem || $pocet_listu_celkem<0) $pocet_listu_celkem=0;

      if ($skar_rezim['znak']<>'') $skar_pole['znak'] = $skar_rezim['znak'];
      if ($skar_rezim['doba']>0) $skar_pole['doba'] = $skar_rezim['doba'];
      $rok_skartace=$rok_uzavreni+$skar_pole[doba]+1;


      if ($rok_skartace<1900) {
        $rok_skartace = RokSkartace($id);

        $rok_uzavreni = $rok_skartace -$skar_pole[doba] - 1;
      }
    }
//     else {
//       $data['CISLO_SPISU1'] = $data['EV_CISLO'] ? $data['EV_CISLO'] : 0;
//       $data['CISLO_SPISU2'] = $data['ROK'];
//       $vec = $data['NAZEV'];
//       $skar_pole[doba] = $data['SKAR_LHUTA'];
//       $skar_pole[znak] = $data['SKAR_ZNAK'];
//       $rok_uzavreni = $data['ROK_UZAVRENI'];
//       $pocet_listu_celkem = $data['POCET_LISTU'];
//       $prilohy = $data['PRILOHY'];
//       $rok_skartace=$rok_uzavreni+$skar_pole[doba]+1;
//
//       $dokument_id = $data['ID'];
//
//     }

  }
  else {
    $dokument_id = $data['ID']; //pro rucni vypujcky a ukladani dokumentu bez cj do spisovny
    $sql = 'select * from posta where id = ' . $dokument_id;
    $a->query($sql); $a->Next_Record();
    $data = $a->Record;
    $data['CISLO_SPISU1'] = $data['CISLO_SPISU1'] ? $data['CISLO_SPISU1'] : 0;
    $data['CISLO_SPISU2'] = $data['CISLO_SPISU2'] ? $data['CISLO_SPISU2'] : 0;
    $skartace_id = $a->Record['SKARTACE'];
    $vec=$a->Record['VEC'];

    $pocet_listu_celkem=$a->Record['POCET_LISTU'];
    $pocet_priloh = $a->Record["POCET_PRILOH"];
    $druh_priloh = trim($a->Record["DRUH_PRILOH"]);

//    $skar_pole=Skartace_Pole($skartace_id);
    if ($skar_pole[znak]=='X') $skar_pole[znak]="";
    if ($skar_pole[znak]=='') $skar_pole[znak]="";
    if ($skar_pole[doba]=='') $skar_pole[doba]="-1";


  }



  $sql = 'select * from posta_spisovna where dokument_id='.$dokument_id;
  $c->query($sql);
  if ($c->Num_Rows()>0) {
    $c->Next_Record();
    if ($c->Record['LISTU']>0 && $pocet_listu_celkem<1) $pocet_listu_celkem = $c->Record['LISTU'] ? $c->Record['LISTU'] : 0;
    if ($c->Record['PRILOHY']>0 && $prilohy == '') $prilohy = $c->Record['PRILOHY'];
    if ($c->Record['ROK_PREDANI']>0 && $rok_uzavreni<1900) $rok_uzavreni = $c->Record['ROK_PREDANI'];
    if ($c->Record['SKAR_ZNAK']<>'' && $skar_pole['znak'] == '') $skar_pole[znak] = $c->Record['SKAR_ZNAK'];
    if ($c->Record['LHUTA']>0 && $skar_pole['doba'] < 0) $skar_pole[doba] = $c->Record['LHUTA'];
    if ($c->Record['ROK_SKARTACE']>0 && $rok_skartace < 1900) $rok_skartace = $c->Record['ROK_SKARTACE'];
  }

  $odbor = $data['ODBOR'] ? $data['ODBOR'] : 0;
//    if (!$digitalnich) $digitalnich=0;
  if (!$pocet_listu_celkem) $pocet_listu_celkem = 0;
  $ukladam[$pocitadlo]=array('ID'=>$pocitadlo,'CISLO_SPISU'=>$data['CISLO_SPISU1'].'/'.$data['CISLO_SPISU2'],'VEC'=>$vec,'ZNAK'=>$skar_pole[znak].'/'.$skar_pole[doba],'LISTU'=>$pocet_listu_celkem,'PRILOHY'=>$prilohy,'DIGITALNE'=>$digitalnich);

  if (!$skar_pole[doba] || $skar_pole[doba]<0) $skar_pole[doba] = 0;
  $sql="select * from posta_spisovna WHERE (cislo_spisu1=".$data['CISLO_SPISU1']." and cislo_spisu2=".$data['CISLO_SPISU2']." and superodbor in (".$cj_so.") or (dokument_id in (".$dokument_id.")))";
  $c->query($sql);
//    echo $sql;
  if (!$protokol) $pred_protokol_id=0; //pokud jde o predani cj, pak nebudeme ukladat cislo protokolu
  if ($c->Num_Rows()>0) {
    $c->Next_Record();
    $zapujcka_id=$c->Record['ZAPUJCKA_ID'];
    $pred_cs1=$c->Record['CISLO_SPISU1'];
    $pred_cs2=$c->Record['CISLO_SPISU2'];
    if ($zapujcka_id) {
      $vraceno[$zapujcka_id]=array('ID'=>$zapujcka_id,'CISLO_SPISU'=>$c->Record['CISLO_SPISU1'].'/'.$c->Record['CISLO_SPISU2'],'VEC'=>$c->Record['VEC']);
    }

    $odbor = $data['ODBOR'] ? $data['ODBOR'] : 0;
//      //vracime do spisovny, zrejme ze zapujcky... tak to vynulujeme...
    $sql="update posta_spisovna set cislo_spisu1=".$data['CISLO_SPISU1'].",cislo_spisu2=".$data['CISLO_SPISU2'].",odbor=$odbor,superodbor=$superodbor,protokol_id=$pred_protokol_id,skartace_id=$skartace_id,spisovna_id=$spisovna_id,vec='$vec',listu=$pocet_listu_celkem,prilohy='$prilohy',digitalni=$digitalnich,skar_znak='$skar_pole[znak]',lhuta=$skar_pole[doba],rok_predani=$rok_uzavreni,rok_skartace=$rok_skartace,datum_predani='".Date('Y-m-d')."',last_date='".Date('Y-m-d')."',last_time='$last_time',last_user_id=$id_user,prevzal_id=$id_user,lokace_id=$lokace_id,zapujcka_id=NULL where dokument_id=$dokument_id";
//echo $sql.'<br/>';
    if ($uloz) {
      $c->query($sql);
      $text = 'zápujčka dokumentu byla ukončena';
      EedTransakce::ZapisLog($dokument_id, $text, 'DOC', $id_user);
    }
    $sql="update posta_spisovna_zapujcky set vraceno='".Date('Y-m-d')."',vraceno_komu=$id_user where id=".$zapujcka_id;
    if ($uloz && $zapujcka_id>0) $c->query($sql);

  }
  else {
    $sql="insert into posta_spisovna (odbor,superodbor,protokol_id,dokument_id,skartace_id,spisovna_id,cislo_spisu1,cislo_spisu2,vec,listu,prilohy,digitalni,skar_znak,lhuta,rok_predani,rok_skartace,datum_predani,last_date,last_time,last_user_id,owner_id,prevzal_id,lokace_id)
    VALUES ($odbor,$superodbor,$pred_protokol_id,$dokument_id,$skartace_id,$spisovna_id,$data[CISLO_SPISU1],$data[CISLO_SPISU2],'$vec',$pocet_listu_celkem,'$prilohy',$digitalnich,'$skar_pole[znak]',$skar_pole[doba],$rok_uzavreni,$rok_skartace,'".Date('Y-m-d')."','".Date('Y-m-d')."','$last_time',$id_user,$id_user,$id_user,$lokace_id);";
//echo $sql.'<br/>';

  //Die();
    if ($uloz) $a->query($sql);
  }
}
  //prevod do spisovny
//   else
//     Die('chyba, nenalezeno odpovídající číslo pro předání');

//}



//print_r($files_to_convert);
if (!$uloz) {

  include_once(FileUp2(".admin/brow_.inc"));

  //print_r($DS_DATA2);
  include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
  $db_arr = new DB_Sql_Array;
  $db_arr->Data=$ukladam;
//print_r($DS_DATA);
  $caption='Čj./spisy, které budou předány do spisovny';
  $GLOBALS['SPISOVNA_PREDANI']=1;
  if (count($ukladam)>0)
    Table(array("db_connector" => &$db_arr,"caption"=>$caption,"showaccess" => false,"page_size"=>"500","schema_file"=>".admin/table_schema_predani.inc","showedit"=>false,"showhistory"=>false,"showdelete"=>false,"showselect"=>false,"showinfo"=>false));
  if (count($vraceno)>0){
    $db_arr = new DB_Sql_Array;
    $db_arr->Data=$vraceno;
  //print_r($DS_DATA);
    $caption='Zápůjčky, které budou označeny jako vrácené';
    $GLOBALS['SPISOVNA_PREDANI']=1;
    Table(array("db_connector" => &$db_arr,"caption"=>$caption,"showaccess" => false,"page_size"=>"500","schema_file"=>".admin/table_schema_predani.inc","showhistory"=>false,"showedit"=>false,"showdelete"=>false,"showselect"=>false,"showinfo"=>false));

  }

  if (count($BOX)>0) {
    $caption='Archivační boxy, které budou předány do spisovny';
    $appendwhere = "and id in (" . implode(',', array_unique($BOX)) . ")";
    $count=Table(array(
      "agenda" => "POSTA_SPISOVNA_BOXY",
      "appendwhere" => $appendwhere,
      "showdelete" => true,
      'showcount' => false, //protahuje to tabulku
      "caption" => $caption,
      "showedit" => false,
      "showinfo" => false,
      //"nocaption" => true,
      "showaccess" => true,
      "setvars" => true,
      "unsetvars" => true,
      "emptyoutput" => false,
    ));

  }
  if (count($files_to_convert)>1){
    $db_arr = new DB_Sql_Array;
    $db_arr->Data=$files_to_convert;
  //print_r($DS_DATA);
    $caption='Soubory, které budou založeny pro dlouhodobou archivaci časového razítka';
    $GLOBALS['SPISOVNA_PREDANI']=1;
    Table(array("db_connector" => &$db_arr,"caption"=>$caption,"showaccess" => false,"page_size"=>"500","schema_file"=>".admin/table_schema_files.inc","showedit"=>false,"showdelete"=>false,"showselect"=>false,"showinfo"=>false));
//
  }

  foreach(explode(',',$_POST['rucne_vlozene']) as $hodnota) {
    if ($hodnota<0) $delimitace[] = $hodnota;
  }
  if (count($delimitace)>0){
    $sql = 'select * from posta_spisovna where dokument_id in (' . implode(',', $delimitace).')';
    $GLOBALS['RUCNE_VLOZENE'] = $GLOBALS['ID'];
    $GLOBALS['SPISOVNA_ID'] = $spisovna_id;
    $count=Table(array(
      "sql" => $sql,
      "setvars"=>true,
      "caption"=>'Dokumenty, které budou delimitovány do této spisovny',
    //  "showself"=>true,
      //"select_id"=>ID2,
      "showinfo"=>false,
      'showexportall' => true,
      "showselect"=>$show_select,
      "multipleselect"=>true,
      "multipleselectsupport"=>true,
      "showedit"=>$showedit,
      "showdelete"=>$showedit,
      "showhistory"=>$showedit,
    //  "return_sql"=>true,
      "page_size"=>"25",
    ));

  }


  //lokace ve spisovně
  Form_(array(
    "showaccess" => true,
    "nocaption" => true,
    "myform_schema"=>".admin/form_schema_lokace.inc",
    "showbuttons" => false,
  ));

  echo '<form method="POST" action="spisovna.php?insert">
  <input type="hidden" name="sql" value="'.$sql_zaklad.'">
  <input type="hidden" name="rucne_vlozene" value="'.$_POST['rucne_vlozene'].'">
  <input type="hidden" name="spisovna" value="'.$spisovna_id.'">
  <input type="hidden" id="lokace_id" name="lokace_id" value="0">
  <input type="hidden" name="protokol_id" value="'.$_POST['protokol_id'].'">
  <input type="hidden" name="uloz" value="1">
  <input type="hidden" name="protokol" value="'.$_POST["protokol"].'">
  ';
  echo "<input type='submit' name='' value='  Skutečně uložit   ' class='btn'>";
  echo "</form>";
  include_once(FileUp2("html_footer.inc")); 


  Die();
}
//print_r($skartace);
//Die();
//print_r($skartace);



while (list($key,$val)=each($cs1)) {
  if ($val>0)  {
//    $sql="update posta SET status=-3,spisovna_id=".$spisovna_id.",last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where id=".$val;
    $sql="update posta SET status=-3,spisovna_id=".$spisovna_id.",last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where cislo_spisu1=".$cs1[$key]." and cislo_spisu2=".$cs2[$key]." and superodbor in (".$cj_so.")";
//    $sql="update posta SET status=-3,spisovna_id=".$spisovna_id.",last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where cislo_spisu1=".$cs1[$key]." and cislo_spisu2=".$cs2[$key]." ";
//echo $sql.'<br/>';
    $q->query($sql);
    if ($spisovna_id==0) NastavStatus($val);
  }
}

$lokace_text = EedTools::GetLokace($lokace_id);
while (list($key, $val) = each($skartace)) {
  $EedCj = LoadClass('EedCj', $val);
  $docs = $EedCj->GetDocsInCJ($val);
  while (list($key2, $val2) = each($docs)) {
    $sql="update posta SET status=-3,spisovna_id=".$spisovna_id.",last_date='".Date('Y-m-d')."',last_time='".Date('H:i:s')."',last_user_id=".$id_user." where id=".$val2;
//echo $sql.'<br/>';
    $q->query($sql);

    $text = 'dokument byl uložen do spisovny <b>' . $spisovna_nazev . '</b>, lokace ve spisovně: ' . $lokace_text;
    EedTransakce::ZapisLog($val2, $text, 'DOC', $id_user);

  }
}

if ($uloz) {
  foreach(explode(',',$_POST['rucne_vlozene']) as $hodnota) {
    if ($hodnota<0) $delimitace[] = $hodnota;
  }
  if (count($delimitace)>0){
    $sql = 'update posta_spisovna set spisovna_id='.$spisovna_id.' where dokument_id in (' . implode(',', $delimitace).')';
    $q->query($sql);
  }

  if (count($BOX)>0) {
    $sql = "update posta_spisovna_boxy set spisovna_id=$spisovna_id where id in (" . implode(',', array_unique($BOX)) . ")";
    $q->query($sql);
  }


}


echo "<br/><br/><h1>Hotovo, dokumenty převedeny</h1><br/>";
echo "
<input type='button' onclick='document.location.href=\"edit.php?filter\";' value='Vrátit se' class='btn'>";
include_once(FileUp2("html_footer.inc")); 
