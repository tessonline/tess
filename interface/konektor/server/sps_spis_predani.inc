<?php
function spis_predani($session_id,$spis_id,$zpracovatel_id)
{
  If (!$software_id=JeNalogovan($session_id)) return VratChybu($session_id,'spis_predani','Neprovedena identifikace');
  if (!$zpracovatel_id) return VratChybu($session_id,'spis_predani','Není zadán dokument_id');

  $spis=ConvertSpisId($spis_id);
  $dokumenty=VratDokumentyKeSpisu($spis_id);
  if ($spis[SPIS_VYRIZEN]) return VratChybu($session_id,'spis_predani','Spis je uzavřen, nelze ho upravovat');
  if ($spis[CISLO_SPISU1]<1) return VratChybu($session_id,'spis_predani','Spis nenalezen');

  $q=new DB_POSTA;
  $sql="update posta set referent=".$zpracovatel_id.",".AddInfo($software_id)." where cislo_spisu1=".$spis[CISLO_SPISU1]." and cislo_spisu2=".$spis[CISLO_SPISU2]."";
  if (!$q->query($sql)) return VratChybu($session_id,'spis_predani','Vnitřní chyba databáze');
//    echo $sql;

  $text='Operace proběhla v pořádku';
  $spisv[SPIS_CISLO]=$spis[CISLO_SPISU1]."/".$spis[CISLO_SPISU2];
  $spisv[SPIS_NAZEV]=TxtEncoding4Soap($spis[NAZEV_SPISU]);
  $spisv[SPIS_STAV]=$spis[SPIS_VYRIZEN]?'uzavren':'otevren';
  while (list($key,$val)=each($dokumenty))
  {
//      print_r(VratDokumentInfo($val));
      $spisv[SPIS_DOKUMENTY][$key]=VratDokumentInfo($val);
  }
  $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
  $vysledek = array(
    'return'=>new soapval('Result', 'tns:Result', $value),
    'spis'=>new soapval('spis', 'tns:spis',$spisv),
  );
  return $vysledek;


}
