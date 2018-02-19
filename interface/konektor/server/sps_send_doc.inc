<?php
//Zpracovani udaju od czechpointu 
Function send_doc($session_id,$dokument_id,$data)
{
  If (!$software_id=JeNalogovan($session_id)) return VratChybu($session_id,'send_doc','Neprovedena identifikace');
  if (!$dokument_id) return VratChybu($session_id,'send_doc','Není zadán dokument_id');
  $stav=$GLOBALS["KONEKTOR"][$software_id]["STAV"]; //stav+1 = pozaduje se k vyrizeni v ext. programu
  $q=new DB_POSTA;
  if ($dokument_id) $sql="SELECT * FROM posta WHERE id = '".$dokument_id."'";
  $q->query($sql);
  $pocet=$q->Num_Rows();
  if ($pocet<1) return VratChybu($session_id,'send_doc','Nenalezen odpovídající dokument_id');
  $q->Next_Record();
  $stav_x=$q->Record["STAV"]-$stav;
//  if ($stav_x<1 || $stav_x>3) return VratChybu($session_id,'send_doc','Nemáte přístup k tomuto souboru');

  //nacteme si drobne udaje ze zalozeneho dokumentu
  $sql="select * from posta where id=".$dokument_id."";
  $q=new DB_POSTA;
  $q->query($sql);
  $q->Next_Record();

  if (!$data[SKARTACE_ID] && $data[SKARTACNI_KOD])
  {
    //jdeme najit ID skartacniho kodu
    $sql_skartace="select id from cis_posta_skartace where text like '".$data[SKARTACNI_KOD]." %'";
    $a=new DB_POSTA;
    $a->query($sql_skartace);
    $pocet=$a->Num_Rows();
    $a->Next_Record();
    If ($pocet==1) $data[SKARTACE_ID]=$a->Record["ID"]; else $data[SKARTACE_ID]=0;
  }

  
///  echo 'Jsem tu'; print_r($data);
  if (strpos($data['DATUM'],'T'))
    $datum_odeslani=ConvertDatumToString($data['DATUM']);
  else
    $datum_odeslani=$data['DATUM'];
  $obalka=$data['OBALKA']>0?$data['OBALKA']:$GLOBALS["KONEKTOR"][$software_id]["OBALKA"];
  $odeslani=$data['ODESLANI']>0?$data['ODESLANI']:$GLOBALS["KONEKTOR"][$software_id]["ODESLANI"];
  $typ_doc=$data['TYP_DOC']>0?$data['TYP_DOC']:1;
  $typ_adr=$data['TYP_ADR']?$data['TYP_ADR']:'F';
  $typ_odesl=$data['TYP_ADR']?$data['TYP_ADR']:'F';
  if ($typ_adr=='P')
  {
    //pravnicka osoba;
    $typ_odesl='P';
    $odesl_prijmeni=$data['ORGANIZACE'];
    $odesl_oddeleni=$data['ODDELENI'];
    $osoba=$data['OSOBA'];
  }
  if ($typ_adr=='F')
  {
    //fyzicka osoba;
    $typ_odesl='O';
    $odesl_prijmeni=$data['PRIJMENI'];
    $odesl_jmeno=$data['JMENO'];
  }
  if ($typ_adr=='Z')
  {
    //fyzicka osoba;
    $typ_odesl='Z';
    $odesl_prijmeni=$data['ORGANIZACE']?$data['ORGANIZACE']:$data['JMENO'].' '.$data['PRIJMENI'];
  }

  $odesl_ulice=$data['ULICE'];
  $odesl_cp=(int)$data['CP'];
  $odesl_cor=(int)$data['COR'];
  $odesl_posta=$data['MESTO'];
  $odesl_psc=$data['PSC'];
 
  $typ_posty=$data['TYP_DOC']; 
  if (!$typ_posty || $typ_posty<0 || $typ_posty=='?') $typ_posty=$GLOBALS["KONEKTOR"][$software_id]["DRUH_ZADOSTI"][$typ_doc]?$GLOBALS["KONEKTOR"][$software_id]["DRUH_ZADOSTI"][$typ_doc]:0;
  
  $sql="update posta set 
typ_posty=".$typ_posty.",
datum_podatelna_prijeti='".$datum_odeslani."',
odes_typ='".$typ_odesl."',
odesl_prijmeni='".$odesl_prijmeni."',
odesl_jmeno='".$odesl_jmeno."',
odesl_ico='".$data['RCIC']."',
odesl_odd='".$odesl_oddeleni."',
odesl_ulice='".$odesl_ulice."',
odesl_datschranka='".$data['DS']."',
jejich_cj='".$data['ADRESAT_CJ']."',
";
if ($data['VEC']) $sql.="vec='".$data['VEC']."',";
if ($data['ZMOCNENI_ZAKON']) $sql.="zmocneni_zakon='".$data['ZMOCNENI_ZAKON']."',";
if ($data['ZMOCNENI_ROK']) $sql.="zmocneni_rok='".$data['ZMOCNENI_ROK']."',";
if ($data['ZMOCNENI_PAR']) $sql.="zmocneni_par='".$data['ZMOCNENI_PAR']."',";
if ($data['ZMOCNENI_ODST']) $sql.="zmocneni_odst='".$data['ZMOCNENI_ODST']."',";
if ($data['ZMOCNENI_PISMENO']) $sql.="zmocneni_pismeno='".$data['ZMOCNENI_PISMENO']."',";


if ($odesl_cp>0) $sql.="odesl_cp='".$odesl_cp."',";
if ($odesl_cor>0) $sql.="odesl_cor='".$odesl_cor."',";

$sql.="
odesl_posta='".$odesl_posta."',
odesl_psc='".$odesl_psc."',
doporucene=$obalka,
vlastnich_rukou=$odeslani,
";

  If ($GLOBALS["KONEKTOR"][$software_id]["ZALOZIT_SPIS"])
{
  $nazev_spisu=$GLOBALS["KONEKTOR"][$software_id]["NAZEV_SPISU"]?$GLOBALS["KONEKTOR"][$software_id]["NAZEV_SPISU"]:'';
  $sql.="
cislo_spisu1=cislo_jednaci1,
cislo_spisu2=cislo_jednaci2,
nazev_spisu='".$nazev_spisu."',
";
}

  If ($data["SKARTACE_ID"]>0)
  $sql.="
skartace=".$data["SKARTACE_ID"].",";

$LAST_USER_ID = $GLOBALS["LAST_USER_ID"]?$GLOBALS["LAST_USER_ID"]:$GLOBALS["KONEKTOR"][$software_id]["LAST_USER_ID"];

$LAST_TIME=Date('H:i');
$LAST_DATE=Date('Y-m-d');

  $sql.="
last_date='".$LAST_DATE."',
last_time='".$LAST_TIME."',
last_user_id=".$LAST_USER_ID.",
";

  $sql.="
poznamka='".$poznamka."'

where id=".$dokument_id."
";
//echo $sql;
//prekonvertujeme data do charsetu
$sql=TxtEncodingFromSoap($sql);

  If ($q->query($sql))
  {
    NastavStatus($dokument_id,$LAST_USER_ID);
    $text='(SEND_DOC) - dokument byl uložen - dokument ('.$dokument_id.')';
    WriteLog($software_id,$text,$session_id);
    $value = array('RESULT'=>'OK','DESCRIPTION'=>TxtEncoding4Soap($text));
    return VratVysledek($value);

  
  }
  else 
  {
    $text='(SEND_DOC) - nepodarilo se odeslat dokument ('.$dokument_id.')';
    VratChybu($session_id,'send_doc',$text);
  
  }
  
  return $return;
}
?>
