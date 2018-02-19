<?php
function storno($session_id,$dokument_id,$duvod)
{
  If (!$software_id=JeNalogovan($session_id)) return VratChybu($session_id,'document','Neprovedena identifikace');
  if (!$dokument_id) return VratChybu($session_id,'document','Není zadán dokument_id');
  $stav=$GLOBALS["KONEKTOR"][$software_id]["STAV"]; //stav+1 = pozaduje se k vyrizeni v ext. programu
  $q=new DB_POSTA;
  if ($dokument_id) $sql="SELECT * FROM posta WHERE id = '".$dokument_id."'";
  $q->query($sql);
  $pocet=$q->Num_Rows();
  if ($pocet<1) return VratChybu($session_id,'document','Nenalezen odpovídající dokument_id');
  $q->Next_Record();
  $stav_x=$q->Record["STAV"]-$stav;
//  if ($stav_x<1 || $stav_x>3) return VratChybu($session_id,'document','Nemáte přístup k tomuto souboru');

  $dnes=Date('d.m.Y');
  $LAST_TIME=Date('H:m:i');
  $jmeno=UkazUsera($id_user);
  $text='Dne <b>'.$dnes.'</b> v <b>'.$LAST_TIME.'</b> uzivatel <b>'.$software_id.'</b> stornoval tento zaznam. Duvod: <b>'.$duvod.'</b>';

  $sql="update posta set STORNOVANO='".TxtEncodingFromSoap($text)."',".AddInfo($software_id)." where id=".$dokument_id;
  echo $sql;

  $q=new DB_DEFAULT;
  if (!$q->query($sql)) return VratChybu($session_id,'document','Vnitřní chyba databáze');

//  $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
//  $vysledek = array(
//    'return'=>new soapval('Result', 'tns:Result', $value),
//  );
  $text='Operace proběhla v pořádku';
  $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
  return VratVysledek($value);
//  return $vysledek;




}
