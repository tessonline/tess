<?php
Function ConvertSpisId($spisID=0)
{
  static $q;
  if (!$q) $q=new DB_POSTA;
  if (strlen($spisID)<1) $spisID=0;
  if (!strpos($spisID,'/'))
  {
    $spis=array();
    $sql='select cislo_spisu1,cislo_spisu2,nazev_spisu,spis_vyrizen from posta where id='.$spisID;
//    echo $sql."<br/>";
    $q->query($sql);
    $q->Next_Record();
    //print_r($q->Record);
    $spis[CISLO_SPISU1]=$q->Record[CISLO_SPISU1];
    $spis[CISLO_SPISU2]=$q->Record[CISLO_SPISU2];
    $spis[NAZEV_SPISU]=$q->Record[NAZEV_SPISU];
    $spis[SPIS_VYRIZEN]=($q->Record[SPIS_VYRIZEN]<>'')?true:false;
  //print_r($spis);
//$spis[CISLO_SPISU1]=$spis[CISLO_SPISU1]?$spis[CISLO_SPISU1]:0;
    //$spis[CISLO_SPISU2]=$spis[CISLO_SPISU2]?$spis[CISLO_SPISU2]:0;
    return ($spis);
  }
  else
  {
    list($cs1,$cs2)=explode('/',$spisID);
    $sql='select id from posta where cislo_spisu1='.$cs1.' and cislo_spisu2='.$cs2;
    //echo $sql."<br/>";
    $q->query($sql);
    $q->Next_Record();
    $id=$q->Record[ID];
    //zavolame fci znova, aby se nam vratil i nazev spisu
    return ConvertSpisId($id);
  }
}

/*
Function VratVsechnyDokumentyKeSpisu($spis_id=0)
{
  static $q;
  if (!$q) $q=new DB_POSTA;
//echo 'SPis id '.$spis_id;Flush();
  $dokumenty=array();
  $spis=ConvertSpisID($spis_id);
//print_r($spis);
  if ($spis[CISLO_SPISU1]<1) return false;
  $sql='select id from posta where cislo_spisu1='.$spis[CISLO_SPISU1].' and cislo_spisu2='.$spis[CISLO_SPISU2];
  $q->query($sql);
  while ($q->Next_Record())  $dokumenty[]=$q->Record[ID];
  return $dokumenty;
}
*/
Function AddInfo($software_id)
{
  $LAST_USER_ID=$GLOBALS["KONEKTOR"][$software_id]["LAST_USER_ID"]?$GLOBALS["KONEKTOR"][$software_id]["LAST_USER_ID"]:0;
  $LAST_TIME=Date('H:i');
  $LAST_DATE=Date('Y-m-d');

  $res="
  last_date='".$LAST_DATE."',
  last_time='".$LAST_TIME."',
  last_user_id=".$LAST_USER_ID."
  ";
  return $res;

}

Function VratDokumentInfo($i)
{
  static $q;
  if (!$q) $q=new DB_POSTA;
  $sql='select * from posta where id='.$i;
  $q->query($sql);
  $q->Next_Record();
     $cislo_spisu=FormatSpis($q->Record["CISLO_SPISU1"],$q->Record["CISLO_SPISU2"],$q->Record["REFERENT"],$q->Record["ODBOR"],$q->Record["NAZEV_SPISU"],$q->Record["PODCISLO_SPISU"]);
    If ($GLOBALS["CONFIG"]["SHOW_C_JEDNACI"])
        $cislo_jednaci=strip_tags(FormatCJednaci($q->Record["CISLO_JEDNACI1"],$q->Record["CISLO_JEDNACI2"],$q->Record["REFERENT"],$q->Record["ODBOR"]));
      else
        $cislo_jednaci=strip_tags(FormatSpis($q->Record["EV_CISLO"],$q->Record["ROK"],$q->Record["REFERENT"],$q->Record["ODBOR"],'',$q->Record["PODCISLO_SPISU"]));

    $dokument[DOKUMENT_ID]=$q->Record["ID"];
    $dokument[TYP_DOC]=$q->Record["ODES_TYP"];
    $dokument[EV_CISLO]=$q->Record["EV_CISLO"]."/".$q->Record["ROK"];
    $dokument[CISLO_JEDNACI]=TxtEncoding4Soap($cislo_jednaci);
    $dokument[CISLO_SPISU]=TxtEncoding4Soap($cislo_spisu);
    $dokument[NAZEV_SPISU]=TxtEncoding4Soap($q->Record["NAZEV_SPISU"]);
    $dokument[DATUM]=ConvertDatumToXML($q->Record["DATUM_PODATELNA_PRIJETI"]);
    $dokument[VEC]=TxtEncoding4Soap($q->Record["VEC"]);
    $dokument[TYP_ADR]=$q->Record["ODES_TYP"];;
    $dokument[PRIJMENI]=TxtEncoding4Soap($q->Record["ODESL_PRIJMENI"]);
    $dokument[JMENO]=TxtEncoding4Soap($q->Record["ODESL_JMENO"]);
    $dokument[ORGANIZACE]=TxtEncoding4Soap($q->Record["ODESL_PRIJMENI"]);
    $dokument[ODDELENI]=TxtEncoding4Soap($q->Record["ODESL_ODD"]);
    $dokument[OSOBA]=TxtEncoding4Soap($q->Record["ODESL_OSOBA"]);
    $dokument[ULICE]=TxtEncoding4Soap($q->Record["ODESL_ULICE"]);
    $dokument[CP]=TxtEncoding4Soap($q->Record["ODESL_CP"]);
    $dokument[COR]=TxtEncoding4Soap($q->Record["ODESL_COR"]);
    $dokument[MESTO]=TxtEncoding4Soap($q->Record["ODESL_POSTA"]);
    $dokument[PSC]=TxtEncoding4Soap($q->Record["ODESL_CP"]);
    $dokument[DS]=TxtEncoding4Soap($q->Record["ODESL_DATSCHRANKA"]);
    $dokument[ADRESAT_CJ]=TxtEncoding4Soap($q->Record["JEJICH_CJ"]);
    $dokument[ODBOR]=$q->Record["ODBOR"];
    $dokument[ZPRACOVATEL]=$q->Record["REFERENT"];
    $dokument[OBALKA]=$q->Record["DOPORUCENE"];;
    $dokument[ODESLANI]=$q->Record["VLASTNICH_RUKOU"];
    $dokument[SKARTACE_ID]=$q->Record["SKARTACE"];
    $dokument[ZMOCNENI_ZAKON]=TxtEncoding4Soap($q->Record["ZMOCNENI_ZAKON"]);
    $dokument[ZMOCNENI_ROK]=TxtEncoding4Soap($q->Record["ZMOCNENI_ROK"]);
    $dokument[ZMOCNENI_PAR]=TxtEncoding4Soap($q->Record["ZMOCNENI_PAR"]);
    $dokument[ZMOCNENI_ODST]=TxtEncoding4Soap($q->Record["ZMOCNENI_ODST"]);
    $dokument[ZMOCNENI_PISMENO]=TxtEncoding4Soap($q->Record["ZMOCNENI_PISMENO"]);
    $dokument[DATUM_VYPRAVENI]=ConvertDatumToXML($q->Record["DATUM_VYPRAVENI"]);
    $dokument[DATUM_DORUCENI]=ConvertDatumToXML($q->Record["DATUM_DORUCENI"]);
    $dokument[SPIS_CISLO]=$q->Record["CISLO_SPISU1"].'/'.$q->Record["CISLO_SPISU2"];
    $dokument[SPIS_NAZEV]=TxtEncoding4Soap($q->Record["NAZEV_SPISU"]);
    $dokument[POZNAMKA]=TxtEncoding4Soap($q->Record["POZNAMKA"]);

  return $dokument;
}
 
