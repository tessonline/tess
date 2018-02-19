<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include_once(FileUp2(".admin/status.inc"));
include(FileUp2(".admin/security_obj.inc"));

require_once(GetAgendaPath('POSTA',false,false).'/.admin/classes/EedUser.inc');
$user_obj = new EedUser;

  $GLOBALS['ID'] = $ID;
  include('./../../.admin/has_access.inc');
  if (!MaPristupKSmazaniDokumentu($ID)) {
  	$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  	$user_id = $USER_INFO['ID'];
  	$EedUser = LoadClass('EedUser', $USER_INFO['ID']);
  	$text = 'Uživatel <b>' . $EedUser->cele_jmeno . '</b> (' . $EedUser->id_user. ') se snažil stornovat dokument <b>' . $GLOBALS['EDIT_ID'] . '</b>, na který nemá oprávnění.';
  	EedTransakce::ZapisLog(0, $text, 'SYS', $user_id);
    require(FileUp2('html_footer.inc'));
    Die('<br/><br/><h3>Nemáte právo pro storno tohoto dokumentu</h3>');;
  }


$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

$id_user=$USER_INFO["ID"];

$jmeno =$user_obj->GetUserName();
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y');
//$sql="update posta set spis_vyrizen=NULL,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID   where cislo_spisu1=".$spis1." and cislo_spisu2=".$spis2."";
$text='Dne <b>'.$dnes.'</b> v <b>'.$LAST_TIME.'</b> uživatel <b>'.$jmeno.'</b> stornoval tento záznam. Důvod: <b>'.$duvod.'</b>';
//echo $text;
//Die();
$q=new DB_POSTA;
//$sql="SELECT ID from posta where id=".$ID." and spis_vyrizen is NULL";
//$q->query($sql);
//If ($q->Num_Rows()>0)
  $sql="UPDATE posta SET STORNOVANO='$text',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$ID;
//else
//  $sql="UPDATE posta SET STORNOVANO='$text',spis_vyrizen='$LAST_DATE',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$ID;
//echo $sql;
//Die($sql);
$q->query($sql);
NastavStatus($ID);

EedTransakce::ZapisLog($ID, $text, 'DOC', $id_user);


?>
<script language="JavaScript" type="text/javascript">
  if (parent.document) {
    parent.document.location.reload();
  }
//  window.close();
</script>





