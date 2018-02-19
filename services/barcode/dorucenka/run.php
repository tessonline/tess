<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
include(FileUp2(".admin/config.inc"));
include(FileUp2(".admin/status.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(FileUp2(".admin/security_name.inc"));
require_once(FileUp2(".admin/oth_funkce_2D.inc"));
require_once(FileUp2("html_header_full.inc"));

$q=new DB_POSTA;
$a=new DB_POSTA;
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$aktual=Date('d.m.Y H:m:i');
//print_r($GLOBALS["ODBOR"]); 
$predana_cisla=explode('<br />',nl2br($GLOBALS["CISLA"]));
echo "<div class=text>";
while (list($key,$val)=each($predana_cisla))
{
  If ($val)
  {
    $id = PrevedCPnaID($val,'');
//    $id=$val;
    echo "Doručenka u ".$val." je zapsána.<br/>";
    $sql="update posta set datum_doruceni='".$GLOBALS["DATUM"]." ".Date('H:m:s')."',last_date='".$LAST_DATE."',last_time='".$LAST_TIME."',last_user_id=".$LAST_USER_ID." where id=".$id;
    $q->query($sql);
    NastavStatus($id);  
    $sql='select * from posta_hromadnaobalka where obalka_id='.$id;
    $q->query($sql);
    while ($q->Next_Record())
    {
      $ID=$q->Record['DOKUMENT_ID'];    
      $sql="UPDATE posta SET datum_doruceni='".$GLOBALS["DATUM"]." ".Date('H:m:s')."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID  WHERE id=".$ID;
      $a->query($sql);
      NastavStatus($ID);
//      echo $sql."<br/>";
    }
  }
}

echo "Hotovo.";
//Die();

require_once(FileUp2("html_footer.inc"));
?>
