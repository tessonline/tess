<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
//include(Fileup2(".admin/functions.inc"));

//print_r($KOD);

while (list($key,$val)=each($KOD))
{
  $q=new DB_POSTA;
  $sql="select * from posta_hromadnaobalka where dokument_id=".$key." and obalka_id=".$GLOBALS["EDIT_ID"];
  $q->query($sql);
  $pocet=$q->Num_Rows();
  $q->Next_Record();
  if ($pocet>0)
  {
    $id=$q->Record["ID"];
    //budeme mazat z obalky...
    $sql="delete from posta_hromadnaobalka where id=$id";
  
  }
  else
  {
    //pridame do obalky
    $sql="insert into posta_hromadnaobalka (DOKUMENT_ID,OBALKA_ID) VALUES ($key,$GLOBALS[EDIT_ID])";
  
  }
  $q->query($sql);
}

header('Location: edit.php?edit&EDIT_ID='.$GLOBALS["EDIT_ID"].'&REFERENT='.$GLOBALS["REFERENT"].'');
//include('../../../output/pdf/obalky.php');

//echo "hotovo";
?>
