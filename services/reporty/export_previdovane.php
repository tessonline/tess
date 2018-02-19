<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
include(FileUp2(".admin/oth_funkce.inc"));
include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select.inc");
require_once(FileUp2(".admin/el/of_select_.inc"));

set_time_limit(0);
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y');
$q=new DB_POSTA;
$nl = chr(10);
$a=new DB_POSTA;


$sqla="select id,superodbor,status,odbor,referent from posta_view_spisy where cislo_spisu1>0 and superodbor=".$so." order by id asc ";
//echo $sqla;
//$sqla="SELECT p.* from posta p WHERE p.ID in (select p.id from posta_h h LEFT JOIN posta p ON p.id=h.id where p.superodbor<>h.superodbor) AND STORNOVANO IS NULL ORDER BY ID DESC";
$q->query($sqla);
$celkovy_pocet=$q->Num_Rows();
$i=0;
echo '<div id="upl_wait_message3" class="text" style="display:block">Hotovo záznamů: 0/'.$celkovy_pocet.'</div>';
$status = getSelectData(new of_select_status(array()));
$export = 'id;původní pracoviště;nové pracoviště;čj;nový útvar;nové jméno;status původní;status nový;spis znak' . $nl;

while ($q->Next_Record()) {
  $i++;
  $id = $q->Record['ID'];
  if ($i%10000==0) {
    echo "<script>document.getElementById('upl_wait_message3').innerHTML = 'Hotovo záznamů: ".$i."/".$celkovy_pocet."'</script>";
    Flush();
  }
  $sql = 'select * from posta_h where id in ('.$id.') and superodbor<>'.$so.' order by id_h asc';
  $a->query($sql);
  $pocet = $a->Num_Rows();
  if ($pocet>0) {
    $so_new = VratSuperOdbor($q->Record['SUPERODBOR']);
    $a->Next_Record();
    $so_new = $so_new + 300;
    $so_old = VratSuperOdbor($a->Record['SUPERODBOR']);
    $so_old = $so_old + 300;
    $doc = LoadClass('EedDokument', $id);
    $skartace = Skartace_Pole($a->Record['SKARTACE']);
    $cj = $doc->text_cj;
    if (strlen($cj)<10) $cj = FormatSpis($q->Record["ID"]);
    //print_r($skartace);
    $export .= $q->Record['ID'].';'.$so_old.';'.$so_new.';'.$cj.';'.UkazOdbor($q->Record['ODBOR']).';'.UkazUsera($q->Record['REFERENT']).';'.$status[$a->Record['STATUS']].';'.$status[$q->Record['STATUS']].';'.$skartace['kod'] . $nl;
  }

//čj. kdo vyřizuje věc status (ke dni převodu) status nyní spisový znak
  
  
}
echo "<script>document.getElementById('upl_wait_message3').style.display = 'none'</script>";

include(FileUp2('.admin/upload_fce_.inc'));
$dir_arr=GetUploadDir('POSTA',1);
$filename='denik_'.$GLOBALS['SUPERODBOR'].'-'.$ROK.'.pdf';
$file = $dir_arr[0].$dir_arr[1]."export.csv";
//echo $file;
$fp = fopen($file, 'w');
fwrite($fp, iconv('ISO-8859-2','WINDOWS-1250',$export));
fclose($fp);
echo '<script>     document.getElementById(\'upl_wait_message\').style.display = \'none\';</script>';
echo '<a href="download.php?file=export.csv">Stáhnout exportovaný soubor</a>';

require_once(Fileup2('html_footer.inc'));

