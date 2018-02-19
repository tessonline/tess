<?php
function spis_vlozeni($session_id,$dokument_id,$spis_id)
{
  If (!$software_id=JeNalogovan($session_id)) return VratChybu($session_id,'spis_vlozeni','Neprovedena identifikace');
  if (!$dokument_id) return VratChybu($session_id,'spis_vlozeni','Není zadán dokument_id');
  $stav=$GLOBALS["KONEKTOR"][$software_id]["STAV"]+2; //stav+1 = pozaduje se k vyrizeni v ext. programu
  $q=new DB_POSTA;
  if ($dokument_id) $sql="SELECT * FROM posta WHERE id = '".$dokument_id."'";
//  $sql.=" AND stav in (".$stav.")";
  $q->query($sql);
  $pocet=$q->Num_Rows();
  if ($pocet<1) return VratChybu($session_id,'spis_vlozeni','Nenalezen odpovídající dokument_id'.$dokument_id);
  $q->Next_Record();
//  if ($q->Record["STAV"]<>$stav) return VratChybu($session_id,'spis_zalozeni','Nemáte přístup k tomuto souboru (stav není 2)');


  $spis=ConvertSpisId($spis_id);
  if ($spis[SPIS_VYRIZEN]) return VratChybu($session_id,'spis_vlozeni','Spis je uzavřen, nelze ho upravovat');
  if ($spis[CISLO_SPISU1]<1) return VratChybu($session_id,'spis_vlozeni','Spis nenalezen');
  $dokumenty=VratDokumentyKeSpisu($spis_id);
//  print_r($dokumenty);
  if (is_array($dokumenty) && count($dokumenty)>0)
  {
    //spis existuje (je v nem alespon jeden dokument)
    $sql="update posta set cislo_spisu1=".$spis[CISLO_SPISU1].",cislo_spisu2=".$spis[CISLO_SPISU2].",nazev_spisu='".$spis[NAZEV_SPISU]."',".AddInfo($software_id)." where id=".$dokument_id;
//    echo $sql;
    $q->query($sql);
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
   return VratChybu($session_id,'spis_vlozeni','Neexistující spis');
}
