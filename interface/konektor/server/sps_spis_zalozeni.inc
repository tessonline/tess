<?php
function spis_zalozeni($session_id,$dokument_id,$nazev_spisu)
{
  If (!$software_id=JeNalogovan($session_id)) return VratChybu($session_id,'spis_zalozeni','Neprovedena identifikace');
  if (!$dokument_id) return VratChybu($session_id,'spis_zalozeni','Není zadán dokument_id');
  $stav=$GLOBALS["KONEKTOR"][$software_id]["STAV"]+2; //stav+1 = pozaduje se k vyrizeni v ext. programu
  $q=new DB_POSTA;
  if ($dokument_id) $sql="SELECT * FROM posta WHERE id = '".$dokument_id."'";
//  $sql.=" AND stav in (".$stav.")";
  $q->query($sql);
  $pocet=$q->Num_Rows();
  if ($pocet<1) return VratChybu($session_id,'spis_zalozeni','Nenalezen odpovídající dokument_id');
  $q->Next_Record();
  //if ($q->Record["STAV"]<>$stav) return VratChybu($session_id,'spis_zalozeni','Nemáte přístup k tomuto souboru (stav není 2)');

  $dokumenty=VratDokumentyKeSpisu($dokument_id);
//print_r($dokumenty);
  if (is_array($dokumenty) && count($dokumenty)>0) return VratChybu($session_id,'spis_zalozeni','Spis již existuje');

  $sql='select * from posta where id='.$dokument_id;
  $q->query($sql);
  $q->Next_Record();
  $spis[CISLO_SPISU1]=$q->Record[CISLO_JEDNACI1];
  $spis[CISLO_SPISU2]=$q->Record[CISLO_JEDNACI2];
  $spis[NAZEV_SPISU]=TxtEncodingFromSoap($nazev_spisu);
// $spis=ConvertSpisId($dokument_id);

  $sql="update posta set cislo_spisu1=".$spis[CISLO_SPISU1].",cislo_spisu2=".$spis[CISLO_SPISU2].",nazev_spisu='".$spis[NAZEV_SPISU]."',".AddInfo($software_id)." where id=".$dokument_id;
//  echo $sql;
  if (!$q->query($sql)) return VratChybu($session_id,'spis_zalozeni','Vnitřní chyba databáze');
  $text='Operace proběhla v pořádku';
  $spisv[SPIS_CISLO]=$spis[CISLO_SPISU1]."/".$spis[CISLO_SPISU2];
  $spisv[SPIS_NAZEV]=TxtEncoding4Soap($spis[NAZEV_SPISU]);
    $spisv[SPIS_STAV]=$spis[SPIS_VYRIZEN]?'uzavren':'otevren';
  $spisv[SPIS_DOKUMENTY][0]=VratDokumentInfo($dokument_id);
  $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
  $vysledek = array(
    'return'=>new soapval('Result', 'tns:Result', $value),
    'spis'=>new soapval('spis', 'tns:spis',$spisv),
  );
  return $vysledek;

}
