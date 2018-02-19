<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/security_obj.inc"));
require(FileUp2(".admin/security_name.inc"));
require_once(Fileup2("html_header_title.inc"));
require_once(FileUp2(".admin/config.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$aa=new DB_POSTA;
$q=new DB_POSTA;
echo "onma".$GLOBALS['POCET'];

$superodbor=VratSuperOdbor();
$pole=OdborPrac($GLOBALS['REFERENT']);
$GLOBALS['ODBOR']=$pole['odbor']?$pole['odbor']:0;
$GLOBALS['ODDELENI']=$pole['oddeleni']?$pole['oddeleni']:0;

$columns=array('SUPERODBOR','ROK','ODESLANA_POSTA','DATUM_PODATELNA_PRIJETI','TYP_POSTY','ODES_TYP','REFERENT','DOPORUCENE','VLASTNICH_RUKOU','OWNER_ID','LAST_USER_ID','LAST_DATE','LAST_TIME','ODBOR','ODDELENI','VEC','STATUS');
$values=array($superodbor,Date('Y'),'t',Date('d.m.Y h:i'),$GLOBALS['CONFIG']['REZERVACE_TYP_POSTY'],'Z',$GLOBALS['REFERENT'],'X','4',$OWNER_ID,$OWNER_ID,$LAST_DATE,$LAST_TIME,$GLOBALS['ODBOR'],$GLOBALS['ODDELENI'],'rezervace čj.','9');

for ($a=1;$a<=$GLOBALS['POCET'];$a++)
{
  $sql="insert into posta (".implode(',',$columns).") VALUES ('".implode("','",$values)."')";
  echo $sql."<br/>";
  $q->query($sql);
}
//Die();
//$aa->query($sql);
//require_once(Fileup2("html_footer.inc"));  

?>
<script language="JavaScript" type="text/javascript">
  window.opener.document.location.reload();
  window.close();
</script>


