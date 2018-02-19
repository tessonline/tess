<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
require_once(Fileup2('html_header_title.inc'));

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
$sqla="select u.* ,g.name from security_user u LEFT join security_group g ON u.group_id = g.id where g.id=".$GLOBALS['so']." order by u.group_id asc,u.id asc";
//echo $sqla;
$q->query($sqla);
$celkovy_pocet=$q->Num_Rows();
$i=0;
$export = 'pracoviště;název útvaru;Jméno;otevřených čj;po termínu;čeká do spisovny;ve spisovně' . $nl;
while ($q->Next_Record()) {
  $i++;
  $id_user = $q->Record['ID'];
  
  $otevrenych = 0; $po_terminu = 0; $ceka = 0; $spisovne = 0;
  $so = VratSuperOdbor($q->Record['GROUP_ID']);
  $sql = 'select count(*) as pocet from posta where stornovano is null and main_doc=1 and referent in ('.$id_user.') and status>1';
  $a->query($sql); $a->Next_Record(); $otevrenych = $a->Record['POCET'];

  $sql = 'select count(*) as pocet from posta where stornovano is null and main_doc=1 and referent in ('.$id_user.') and status=6';
  $a->query($sql); $a->Next_Record(); $po_terminu = $a->Record['POCET'];
  
  $sql = 'select count(*) as pocet from posta where stornovano is null and main_doc=1 and referent in ('.$id_user.') and status=1';
  $a->query($sql); $a->Next_Record(); $ceka = $a->Record['POCET'];
  
  $sql = 'select count(*) as pocet from posta where stornovano is null and main_doc=1 and referent in ('.$id_user.') and status=-3';
  $a->query($sql); $a->Next_Record(); $spisovne = $a->Record['POCET'];
  
  if ($otevrenych>0 || $po_terminu>0 || $ceka>0 || $spisovne>0) {
    $export .= $so.';'.$q->Record['NAME'].';'.$q->Record['LNAME'] . ' ' . $q->Record['FNAME'] . ';' . $otevrenych . ';' . $po_terminu.';'.$ceka.';'.$spisovne.$nl;
  }
}

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

