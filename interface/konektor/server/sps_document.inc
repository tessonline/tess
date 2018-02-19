<?php
function document($session_id,$dokument_id,$data)
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

  $sql='';

  $pole_prepis=array(
    'ZPRACOVATEL'=>'REFERENT',
    'VEC'=>'VEC',
    'OBALKA'=>'DOPORUCENE',
    'ODESLANI'=>'VLASTNICH_RUKOU',
    'SKARTACE_ID'=>'SKARTACE',
    'DATUM_PRECTENI'=>'DATUM_REFERENT_PRIJETI',
    'DATUM_VYRIZENI'=>'DATUM_VYRIZENI',
    'ZPUSOB_VYRIZENI'=>'VYRIZENO',
    'DATUM'=>'DATUM_PODATELNA_PRIJETI',
  );
//  print_r($data);
  foreach($data as $k => $v) {
      if (trim($v)<>'' && $v<>'?' && $pole_prepis[$k])
      {
        if ($pole_prepis[$k]=='DATUM_REFERENT_PRIJETI') $v=ConvertDatumToString($v);
        if ($pole_prepis[$k]=='VEC') $v=TxtEncodingFromSoap($v);
        if ($pole_prepis[$k]=='DATUM_VYRIZENI') $v=ConvertDatumToString($v);
        if ($pole_prepis[$k]=='DATUM_PODATELNA_PRIJETI') $v=ConvertDatumToString($v);
        $sql.=$pole_prepis[$k]."='".$v."',";
      }
   //     print "\$a[$k] => $v.\n";
  }

  $sql="update posta set ".$sql.AddInfo($software_id)." where id=".$dokument_id;
//  echo $sql;
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
