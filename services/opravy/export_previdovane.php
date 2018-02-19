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



$sqla="select id,superodbor,status,odbor,referent from posta_view_spisy where cislo_spisu1 is not null order by superodbor,id asc ";
//$sqla="SELECT p.* from posta p WHERE p.ID in (select p.id from posta_h h LEFT JOIN posta p ON p.id=h.id where p.superodbor<>h.superodbor) AND STORNOVANO IS NULL ORDER BY ID DESC";
$q->query($sqla);
$celkovy_pocet=$q->Num_Rows();
$i=0;
$status = getSelectData(new of_select_status(array()));
$export = 'id;původní pracoviště;nové pracoviště;čj;nový útvar;nové jméno;status původní;status nový;spis znak' . $nl;
while ($q->Next_Record()) {
  $i++;
  $id = $q->Record['ID'];
  $sql = 'select * from posta_h where id in ('.$id.') order by id_h asc';
  $a->query($sql);
  $a->Next_Record();  
  if ($a->Record['SUPERODBOR'] <> $q->Record['SUPERODBOR']) {
    $so = VratSuperOdbor($q->Record['SUPERODBOR']);
    $so = $so + 300;
    $so_old = VratSuperOdbor($a->Record['SUPERODBOR']);
    $so_old = $so_old + 300;
    $doc = LoadClass('EedDokument', $id);
    $skartace = Skartace_Pole($a->Record['SKARTACE']);
    $cj = $doc->text_cj;
    if (strlen($cj)<10) $cj = FormatSpis($q->Record["ID"]);
    //print_r($skartace);
    $export .= $q->Record['ID'].';'.$so_old.';'.$so.';'.$cj.';'.UkazOdbor($q->Record['ODBOR']).';'.UkazUsera($q->Record['REFERENT']).';'.$status[$a->Record['STATUS']].';'.$status[$q->Record['STATUS']].';'.$skartace['kod'] . $nl;
  }

//čj. kdo vyřizuje věc status (ke dni převodu) status nyní spisový znak
  
  
}

Header("Content-Type: application/csv");
Header("Content-Disposition: attachment;filename=export-".Date('Y-m-d').".csv");
Header("Pragma: cache");
Header("Cache-Control: public");

echo iconv('ISO-8859-2','WINDOWS-1250',$export);

?>
