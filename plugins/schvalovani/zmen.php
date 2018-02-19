<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/security_name.inc"));
require(FileUp2("html_header_title.inc"));
include_once(FileUp2(".admin/db/db_posta.inc"));

if ($co==1)
  $a=GetGroupsInSuperOdbor();
else
  $a=GetAllGroupsInSuperOdbor(VratSuperOdbor());
print_r($a);
if (count($a)>0) $where="and group_id in (".implode(',',$a).")";

$sql="SELECT id,lname, fname FROM security_user WHERE active ='1' $where ORDER BY lname,fname";

$res='<select name="SCHVALUJICI_ID"><option value="" selected="selected"> </option>';
$a = new DB_POSTA;
$a->query($sql);
while ($a->Next_Record())
  $res.='<option value="'.$a->Record["ID"].'">'.$a->Record["LNAME"].' '.$a->Record["FNAME"].'</option>';
  
$res.='</select>';

echo '
<script language="JavaScript" type="text/javascript">
<!--
       var spn = window.parent.document.getElementById("schvalovatel");
//       var spn = window.opener.document.getElementById("schvalovatel");
       spn.innerHTML =  \''.$res.'\';
//-->
</script>

';

