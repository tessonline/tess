<?php
 
Function work_on($session_id,$dokument_id,$work_status)
{
  If (!$software_id=JeNalogovan($session_id)) return VratChybu($session_id,'work_on','Neprovedena identifikace');
  if (!$dokument_id) return VratChybu($session_id,'work_on','Není zadán dokument_id');
  if (!isset($work_status)) return VratChybu($session_id,'work_on','Není zadán work_status');
  if ($work_status<>0 && $work_status<>2 && $work_status<>3) return VratChybu($session_id,'work_on','Nepovolená hodnota work_status');
  $stav=$GLOBALS["KONEKTOR"][$software_id]["STAV"]; //stav+1 = pozaduje se k vyrizeni v ext. programu
  $q=new DB_POSTA;
  if ($dokument_id) $sql="SELECT * FROM posta WHERE id = '".$dokument_id."'";
  $q->query($sql);
  $pocet=$q->Num_Rows();
  if ($pocet<1) return VratChybu($session_id,'get_files','Nenalezen odpovídající dokument_id');
  $q->Next_Record();
  $stav_x=$q->Record["STAV"]-$stav;
  if ($stav_x<1 || $stav_x>3) return VratChybu($session_id,'work_on','Nemáte přístup k tomuto souboru');
  
  $novy_stav=$stav+$work_status;
  //dodelat, ze pokud status bude 3, tak se dopise u prichozich datum vyrizeni.

  $LAST_USER_ID = $GLOBALS["LAST_USER_ID"]?$GLOBALS["LAST_USER_ID"]:$GLOBALS["KONEKTOR"][$software_id]["LAST_USER_ID"];

  $sql="update posta set stav=".$novy_stav.",last_user_id=".$LAST_USER_ID.",
  last_date='".Date('Y-m-d')."',last_time='".Date('h:i')."' where id=".$dokument_id;
  $vysledek=$q->query($sql);
  if (!$vysledek) return VratChybu($session_id,'work_on','Nepovedlo se nastavit work_status');
  $text='Operace proběhla v pořádku';
  $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
  $vysledek = array(
    'return'=>new soapval('Result', 'tns:Result', $value),
  );
  return VratVysledek($value);

}

