<?php
include_once(FileUp2(".admin/status.inc"));
include_once(FileUp2(".admin/schvalovani.inc"));

Function NactiDataProSpisovnu($posta_id)
{
  $q = new DB_POSTA;
  $sql = 'select * from posta where id='.$posta_id;
  $q->query($sql);
  $q->Next_Record();
  $data = $q->Record;
  $datum_uzavreni=explode("-",$data[SPIS_VYRIZEN]);
  $skar_pole=Skartace_Pole($data['SKARTACE']);
//    echo $datum_vyrizeni;
  $datum_uzavreni=explode("-",$data[SPIS_VYRIZEN]);
  $rok_uzavreni=$datum_uzavreni[0];
  $rok_skartace=$rok_uzavreni+$skar_pole[doba]+1;

  $pole[CISLO_SPISU1]=$data['CISLO_SPISU1'];
  $pole[CISLO_SPISU2]=$data['CISLO_SPISU2'];
  $pole[SUPERODBOR]=$data['SUPERODBOR'];
  $pole[PROTOKOL_ID]=0;
  $pole[SKARTACE_ID]=$data['SKARTACE'];
  $pole[SPISOVNA_ID]=$data['SPISOVNA_ID'];
  $pole[VEC]=$data['VEC'];
  $pole[LISTU]=-1;
  $pole[PRILOHY]='';
  $pole[DIGITALNI]=-1;
  $pole[SKAR_ZNAK]=$skar_pole[znak];
  $pole[LHUTA]=$skar_pole[doba];
  $pole[ROK_PREDANI]=$rok_uzavreni;
  $pole[ROK_SKARTACE]=$rok_skartace;
  
  return $pole;
}

Function NaciUdajeZHistoriePosty($posta_id,$data)
{
  $q = new DB_POSTA;
  $sql = 'select * from posta_h where id='.$posta_id.' and status=-3 order by id_h asc limit 1';
  $q->query($sql); $q->Next_Record(); $pole = $q->Record;
  $data['LAST_DATE'] = $pole[LAST_DATE];
  $data['LAST_TIME'] = $pole[LAST_TIME];
  $data['OWNER_ID'] = $pole[LAST_USER_ID];
  $data['PREVZAL_ID'] = $pole[LAST_USER_ID];
  if ($data['SKARTACE_ID']<1) $data['SKARTACE_ID'] = $pole[SKARTACE];
  $data['VEC'] = $pole[VEC];
  $data['DATUM_PREDANI'] = $pole[LAST_DATE];  
  if ($data['SPISOVNA_ID']<1) $data['SPISOVNA_ID'] = $pole[SPISOVNA_ID];
  return $data;  
}

Function CreaSQLFromData($insert,$posta_id,$data)
{
  $sql="insert into posta_spisovna (superodbor,protokol_id,dokument_id,skartace_id,spisovna_id,cislo_spisu1,cislo_spisu2,vec,listu,prilohy,digitalni,skar_znak,lhuta,rok_predani,rok_skartace,datum_predani,last_date,last_time,last_user_id,owner_id,prevzal_id)
  VALUES ($data[SUPERODBOR],0,$posta_id,$data[SKARTACE_ID],$data[SPISOVNA_ID],$data[CISLO_SPISU1],$data[CISLO_SPISU2],'$data[VEC]',$data[LISTU],'$data[PRILOHY]',$data[DIGITALNI],'$data[SKAR_ZNAK]',$data[LHUTA],$data[ROK_PREDANI],$data[ROK_SKARTACE],'$data[LAST_DATE]','$data[LAST_DATE]','$data[LAST_TIME]',$data[OWNER_ID],$data[OWNER_ID],$data[PREVZAL_ID]);";
  return $sql;

  
}
