<?php
$sql = "SELECT popis FROM CIS_POSTA_TYP WHERE ID=".$typ_posty; 
$q=new DB_POSTA;
$q->query($sql);
$q->Next_Record();
$popis=$q->Record['POPIS'];
echo $popis;
$GLOBALS["NOTSHOW_DOKONCIT"] = 1;

?>

