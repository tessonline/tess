<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
include_once(FileUp2("posta/.admin/config.inc"));
include(FileUp2(".admin/status.inc"));
require_once(Fileup2("html_header_title.inc"));

$lastid = Run_(array("outputtype"=>1 ,"no_unsetvars"=>true,"to_history"=>false));
If (!$GLOBALS[EDIT_ID] && !$GLOBALS['DELETE_ID'])
{
  include('funkce.php');
  NactiPisemnosti($lastid,$GLOBALS["DATUM_OD"],$GLOBALS["DATUM_DO"],$GLOBALS["ODBOR"]);
//Die();
  //vlozime idcka dokumentu, co se budou tisknout
}

If ($GLOBALS[DELETE_ID])
{
  //vymazeme idcka dokumentu, co se mely tisknout
  $q=new DB_POSTA;
  $sql='select * from posta_cis_ceskaposta where id='.$GLOBALS[DELETE_ID];
  $q->query($sql);
  $q->Next_Record();
  $GLOBALS[PROTOKOL]=$q->Record["PROTOKOL"];
  If ($q->Record["DATUM_VRACENI"] || $q->Record["DATUM_VYTISTENI"])
    Die('Protokol byl již vytištěn, záznam nelze smazat!');
  else
  {
   $sql='delete from posta_cis_ceskaposta_id where protokol_id='.$GLOBALS[DELETE_ID];
    $q->query($sql);
  }
}
  
If ($GLOBALS[EDIT_ID] && $GLOBALS[DATUM_VRACENI] && !$GLOBALS[DELETE_ID])
{
  //zapiseme datum, kdy dokumenty prevzala Ceska posta
  $w=new DB_POSTA;
  $q=new DB_POSTA;
  $a=new DB_POSTA;
  include_once(FileUp2(".admin/security_obj.inc"));
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  $LAST_USER_ID=$id_user;
  $OWNER_ID=$id_user;
  $LAST_TIME=Date('H:m:i');
  $LAST_DATE=Date('Y-m-d');
 $sql='select * from posta_cis_ceskaposta_id where protokol_id='.$GLOBALS[EDIT_ID];
  //echo $sql;
  $w->query($sql);
  while ($w->Next_Record())
  {
    $ID=$w->Record['PISEMNOST_ID'];    
    $sql="UPDATE posta SET datum_vypraveni='".$GLOBALS[DATUM_VRACENI]."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID  WHERE id=".$ID;
//    echo $sql."<br/>";
    $q->query($sql);
    NastavStatus($ID);

    $text = 'dokument (<b>'.$ID.'</b>) byl vypraven Českou poštou';
    EedTransakce::ZapisLog($ID, $text, 'DOC', $id_user);

    $sql='select * from posta_hromadnaobalka where obalka_id='.$ID;
    $q->query($sql);
    $puvodni_id = $ID;
    while ($q->Next_Record())
    {
      $ID=$q->Record['DOKUMENT_ID'];    
      $sql="UPDATE posta SET datum_vypraveni='".$GLOBALS[DATUM_VRACENI]."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID  WHERE id=".$ID;
      $a->query($sql);
      NastavStatus($ID);
      $text = 'dokument (<b>'.$ID.'</b>) byl vypraven Českou poštou v obálce dokumentu <b>'.$puvodni_id.'</b>';
      //echo $sql."<br/>";
    }

  }
}
//Die();
echo '
<script language="JavaScript" type="text/javascript">
  if (window.opener.parent.frames[1]!=null) {
    window.opener.parent.frames[1].history.go(0);
  }
  if (window.opener.parent.frames.frame_info)
  {
    //mame frame vystup
//  window.opener.parent.frames.frame_info.document.location.reload();
  window.opener.parent.frames.frame_info.document.location.href=\'/ost/posta/services/frank/ceska_posta/brow.php\';
//    window.opener.parent.document.location.href=\'brow.php\';
  }
  else
  {
    //mame jenom vystup do puvodniho okna
//    window.opener.parent.document.location.href=\'brow.php\';
  }
  window.close();
</script>
';

require_once(Fileup2("html_footer.inc"));  

?>

