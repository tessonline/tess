<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
include_once(FileUp2("posta/.admin/config.inc"));
require_once(Fileup2("html_header_title.inc"));

$lastid = Run_(array("outputtype"=>1 ,"no_unsetvars"=>true,"to_history"=>false));

If (!$GLOBALS[EDIT_ID] && !$GLOBALS['DELETE_ID'])
{
  include_once('funkce.php');
  NactiPisemnosti($lastid,$GLOBALS["DATUM_OD"],$GLOBALS["DATUM_DO"],$GLOBALS["ODBOR"]);
  //vlozime idcka dokumentu, co se budou tisknout
}

If ($GLOBALS[DELETE_ID])
{
  //vymazeme idcka dokumentu, co se mely tisknout
  $q=new DB_POSTA;
  $sql='select * from posta_cis_dorucovatel where id='.$GLOBALS[DELETE_ID];
  $q->query($sql);
  $q->Next_Record();
  $GLOBALS[PROTOKOL]=$q->Record["PROTOKOL"];
  If ($q->Record["DATUM_VRACENI"] || $q->Record["DATUM_VYTISTENI"])
    Die('Protokol byl již vytištěn, záznam nelze smazat!');
  else
  {
    $sql='delete from posta_cis_dorucovatel_id where protokol_id='.$GLOBALS[DELETE_ID];
    $q->query($sql);
  }
}
  
If ($GLOBALS[EDIT_ID] && $GLOBALS[DATUM_VRACENI] && !$GLOBALS[DELETE_ID])
{
  //zapiseme datum, kdy dokumenty prevzala Ceska posta
  include_once(FileUp2(".admin/status.inc"));
  $w=new DB_POSTA;
  $q=new DB_POSTA;
  include_once(FileUp2(".admin/security_obj.inc"));
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  $LAST_USER_ID=$id_user;
  $OWNER_ID=$id_user;
  $LAST_TIME=Date('H:m:i');
  $LAST_DATE=Date('Y-m-d');
  $sql='select * from posta_cis_dorucovatel_id where protokol_id='.$GLOBALS[EDIT_ID];
  //echo $sql;
  $w->query($sql);
  while ($w->Next_Record())
  {
    $ID=$w->Record['PISEMNOST_ID'];    
    $sql="UPDATE posta SET datum_vypraveni='".$GLOBALS[DATUM_VRACENI]."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID  WHERE id=".$ID;
    echo $sql."<br/>";
    $q->query($sql);
    NastavStatus($ID);
    $sql='select * from posta_hromadnaobalka where obalka_id='.$ID;
    $q->query($sql);
    while ($q->Next_Record())
    {
      $ID=$q->Record['DOKUMENT_ID'];    
      $sql="UPDATE posta SET datum_vypraveni='".$GLOBALS[DATUM_VRACENI]."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID  WHERE id=".$ID;
      $a->query($sql);
      NastavStatus($ID);
      echo $sql."<br/>";
    }

  }
}
//Die();
echo '
<script language="JavaScript" type="text/javascript">
  if (window.opener.parent.frames[1]!=null) {
    window.opener.parent.frames[1].history.go(0);
  }
  window.close();
</script>
';

require_once(Fileup2("html_footer.inc"));  

?>

