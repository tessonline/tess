<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
include_once($GLOBALS["TMAPY_LIB"]."/oohforms.inc");
include_once($GLOBALS["TMAPY_LIB"]."/of_select.inc");
require_once(FileUp2(".admin/el/of_select_.inc"));

set_time_limit(0);
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$roky = array(2012,2013);

$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y');
$q=new DB_POSTA;
$nl = chr(10);
$a=new DB_POSTA;
$c=new DB_POSTA;
$sqla = "select distinct superodbor from posta where superodbor<1000 and superodbor>0 and superodbor=2 order by superodbor";
$q->query($sqla);
$i=0;
while ($q->Next_Record()) {
  $i++;
  $so = VratSuperOdbor($q->Record['SUPERODBOR']);
  $export .= $so . $nl;
  $export .= 'kod;pocet 2012; pocet 2013' . $nl;
  $sql = 'select * from cis_posta_skartace order by id asc';
  $a->query($sql);
  while ($a->Next_Record()) {
    $skartace_id = $a->Record['ID'];
    $sql = 'select count(*) as pocet from posta where skartace='.$skartace_id.' and rok=2012';
    $c->query($sql); $c->Next_Record(); $rok2012 = $c->Record['POCET'];
    $sql = 'select count(*) as pocet from posta where skartace='.$skartace_id.' and rok=2013';
    $c->query($sql); $c->Next_Record(); $rok2013 = $c->Record['POCET'];
      
    if ($rok2012>0 || $rok2013>0) {
      $skartace = Skartace_Pole($skartace_id);
      $export .= $skartace['kod'].';'.$rok2012.';'.$rok2013.$nl;
      
    }    
  }
  $export .= $nl;
}

Header("Content-Type: application/csv");
Header("Content-Disposition: attachment;filename=export-".Date('Y-m-d').".csv");
Header("Pragma: cache");
Header("Cache-Control: public");

echo iconv('ISO-8859-2','WINDOWS-1250',$export);

?>
