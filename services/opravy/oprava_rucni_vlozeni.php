<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));
include(FileUp2(".admin/security_obj.inc"));
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:m:i');
$LAST_DATE=Date('Y-m-d');
$dnes=Date('d.m.Y');
$q=new DB_POSTA;
$a=new DB_POSTA;
$sqla=" select * from posta_spisovna where registratura like '-1' order by dokument_id desc";
$q->query($sqla);
while ($q->Next_Record())
{

  $dokument_id = $q->Record["DOKUMENT_ID"];
  $id = $q->Record['ID'];
  $sql2="select * from posta where id=".$dokument_id."";
//  $pocet=$a->Num_Rows();
  $a->query($sql2);
  $pocet = $a->Num_Rows();
  echo "Hledam $dokument_id a nalezeno $pocet<br/>";
  if ($pocet<1)
  {
    $skartace = $GLOBALS['SKARTACE_ID'];
    if (!$skartace) {
      $sql = "select min(id) as MINID from cis_posta_skartace";
      $a->query($sql);
      $a->next_Record();
      $skartace = $a->Record['MINID'];
    }

    $text_cj = $q->Record['TEXT_CJ'];
    $odbor = $q->Record['ODBOR'] ? $q->Record['ODBOR'] : 0;
    $sql = "insert into posta (ROK,ODES_TYP,CISLO_JEDNACI1,CISLO_SPISU1,VEC,ODBOR,STORNOVANO,STATUS,SKARTACE,TEXT_CJ,MAIN_DOC,LAST_DATE,LAST_TIME,OWNER_ID,LAST_USER_ID) VALUES (
    ".$q->Record['ROK_PREDANI'].",'Z',-2,0,'" . $q->Record['VEC'] . "','" . $odbor . "','rucni vypujcka',-3,'$skartace','$text_cj',1,'$LAST_DATE','$LAST_TIME',$id_user,$id_user)";
    echo $sql . "<br/>";

    //$a->query($sql);
    //$posta_id = $q->getLastId('posta','id');

    $sql = "update posta_spisovna set dokument_id=$posta_id where id=".$id;
    echo $sql . "<br/>";
    //$a->query($sql);
  }
}

