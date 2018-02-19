<?php
function spis_stav($session_id,$spis_id,$akce)
{
  If (!$software_id=JeNalogovan($session_id)) return VratChybu($session_id,'spis_stav','Neprovedena identifikace');
  if (!$spis_id) return VratChybu($session_id,'spis_stav','Není zadán spis_id');
 if (!($akce)) return VratChybu($session_id,'spis_stav','Není zadána akce');

$q=new DB_POSTA;
/*
  if ($dokument_id) $sql="SELECT * FROM posta WHERE id = '".$dokument_id."'";
//  $sql.=" AND stav in (".$stav.")";
  $q->query($sql);
  $pocet=$q->Num_Rows();
  if ($pocet<1) return VratChybu($session_id,'spis_stav','Nenalezen odpovídající dokument_id'.$dokument_id);
  $q->Next_Record();
//  if ($q->Record["STAV"]<>$stav) return VratChybu($session_id,'spis_zalozeni','Nemáte přístup k tomuto souboru (stav není 2)');
*/

  $spis=ConvertSpisId($spis_id);
  $dokumenty=VratDokumentyKeSpisu($spis_id);
//  print_r($dokumenty);
  if (is_array($dokumenty) && count($dokumenty)>0)
  {
    if ($akce=='list')
    {
      //vylistujeme pouze dokumenty, neni potreba nic delat
    }
    elseif ($akce=='otevrit')
    {
      if (!$spis[SPIS_VYRIZEN]) return VratChybu($session_id,'spis_stav','Spis není uzavřen, nemohu ho otevřít');
      $sql="update posta set spis_vyrizen=NULL,".AddInfo($software_id)." where cislo_spisu1=".$spis[CISLO_SPISU1]." and cislo_spisu2=".$spis[CISLO_SPISU2]."";
      if (!$q->query($sql)) return VratChybu($session_id,'spis_stav','Vnitřní chyba databáze');
//      echo $sql;
      $spis[SPIS_VYRIZEN]=false;
    }
    elseif ($akce=='uzavrit')
    {
      if ($spis[SPIS_VYRIZEN]) return VratChybu($session_id,'spis_stav','Spis je uzavřen, nelze ho upravovat');
      $sql="update posta set spis_vyrizen='".Date('Y-m-d')."',".AddInfo($software_id)." where cislo_spisu1=".$spis[CISLO_SPISU1]." and cislo_spisu2=".$spis[CISLO_SPISU2]."";
      if (!$q->query($sql)) return VratChybu($session_id,'spis_stav','Vnitřní chyba databáze');
//      echo $sql;
      $spis[SPIS_VYRIZEN]=true;
    }
    else return VratChybu($session_id,'spis_stav','Nesprávný typ akce');

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
  else
   return VratChybu($session_id,'spis_stav','Neexistující spis');
}
