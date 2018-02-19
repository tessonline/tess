<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/security_name.inc"));
//require(FileUp2(".admin/security_.inc"));
require(FileUp2(".admin/status.inc"));
require_once(Fileup2("html_header_title.inc"));

$close_on_submit = $GLOBALS['CLOSE_ON_SUBMIT'];

$q=new DB_POSTA;

$posta_id = $GLOBALS['POSTA_ID'];
if ($GLOBALS[SCHVALENO]) {
  //$GLOBALS[MOJE_ID]
  $sql="update posta_schvalovani set schvaleno=".$GLOBALS[SCHVALENO].",datum_podpisu='".Date('d.m.Y H:i:s')."',
    LAST_DATE='".Date('Y-m-d')."',LAST_TIME='".Date('H:i:s')."',LAST_USER_ID=".$GLOBALS[MOJE_ID]." where 
    schvalujici_id=".$GLOBALS[MOJE_ID]." and posta_id=".$GLOBALS[POSTA_ID]." and datum_podpisu is null";
  $q->query($sql);
  NastavStatus($GLOBALS[POSTA_ID]);
    
}

if ($GLOBALS[POSTUP_ANO]>0) $GLOBALS['POSTUP'] = 2; else $GLOBALS['POSTUP'] = 1; 
  //$GLOBALS[MOJE_ID]
  $sql="update posta_schvalovani set postup='".$GLOBALS['POSTUP']."' where 
    posta_id=".$GLOBALS[POSTA_ID]." ";
  $q->query($sql);

if ($GLOBALS[POZNAMKA2]) {
  //$GLOBALS[MOJE_ID]
  $sql="update posta_schvalovani set poznamka2='".$GLOBALS[POZNAMKA2]."' where 
    schvalujici_id=".$GLOBALS[MOJE_ID]." and posta_id=".$GLOBALS[POSTA_ID]." and (datum_podpisu is null or datum_podpisu='".Date('d.m.Y H:i:s')."')";
//echo $sql; Die();
  $q->query($sql);

  NastavStatus($GLOBALS[POSTA_ID]);

}
if ($GLOBALS[KOPIE]) {
  $q=new DB_POSTA;
  $sql="insert into posta_schvalovani (POSTA_ID,SCHVALUJICI_ID,DATUM_ZALOZENI,POZNAMKA,LAST_DATE,LAST_TIME,LAST_USER_ID,OWNER_ID,TYPSCHVALENI)
  VALUES (".$GLOBALS[POSTA_ID].",".$GLOBALS[MOJE_ID].",'".Date('d.m.Y H:i:s')."','".$GLOBALS[POZNAMKA]."','".Date('Y-m-d')."',
  '".Date('H:i:s')."',".$GLOBALS[MOJE_ID].",".$GLOBALS[MOJE_ID].",".$GLOBALS[TYPSCHVALENI].")";
  $q->query($sql);    
  NastavStatus($GLOBALS[POSTA_ID]);

}

if ($GLOBALS[SCHVALUJICI_ID]>0) {
  UNSET($GLOBALS[SCHVALENO]);
  $posta_id=$GLOBALS[POSTA_ID];
  if ($GLOBALS['PREDVYBRANY_ID']) $no_unset = true; else $no_unset = false;
  Run_(array("showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>$no_unset));
  if ($posta_id)  NastavStatus($posta_id);
}

if ($GLOBALS[PREDVYBRANY_ID])
{
  $posta_id=$GLOBALS[POSTA_ID];
  UNSET($GLOBALS[SCHVALENO]);
  $datum_zalozeni=$GLOBALS[DATUM_ZALOZENI];
  $predvyber=$GLOBALS[PREDVYBRANY_ID];
  $poznamka=$GLOBALS[POZNAMKA];
  $typschvaleni=$GLOBALS[TYPSCHVALENI];
  while (list($id_prac,$vybran_prac)=each($predvyber))
  {
    if ($vybran_prac==1)
    {
      $GLOBALS['SCHVALUJICI_ID']=$id_prac;
      $GLOBALS[POSTA_ID]=$posta_id;
      $GLOBALS[POZNAMKA]=$poznamka;
      $GLOBALS[DATUM_ZALOZENI]=$datum_zalozeni;
      $GLOBALS[TYPSCHVALENI] = $typschvaleni;
      UNSET($GLOBALS['EDIT_ID']);
      Run_(array("showaccess"=>true,"outputtype"=>1,"unsetvars"=>true));
      UNSET($GLOBALS['EDIT_ID']);
      UNSET($GLOBALS['ID']);
    }    
  }
//  Die();
//  $posta_id=$GLOBALS[POSTA_ID];
  if ($posta_id)  NastavStatus($posta_id);
}


if ($GLOBALS[DELETE_ID])  
{
  $q=new DB_DEFAULT;
  $sql='select posta_id from posta_schvalovani where id='.$GLOBALS[DELETE_ID];
  $q->query($sql); $q->Next_Record();
  Run_(array("showaccess"=>true,"outputtype"=>1));
  NastavStatus($q->Record[POSTA_ID]);
}


require_once(Fileup2("html_footer.inc"));  

if ($close_on_submit!="true")
echo '
<script language="JavaScript" type="text/javascript">
   location.href="edit.php?insert&POSTA_ID='.$posta_id.'";
</script>
'; else 
  echo '
<script language="JavaScript" type="text/javascript">
  window.opener.document.location.reload();
</script>';

?>
  
