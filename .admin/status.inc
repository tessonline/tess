<?php
include_once(FileUp2('services/spisovka/uzavreni_spisu/funkce.inc'));

function NastavStatus($id,$LAST_USER_ID=0) {
  if (!$id) return false;

  if (!$GLOBALS["CONFIG"]["DB"])
    include_once(FileUp2("posta/.admin/config.inc"));

  if ($GLOBALS['CONFIG']['DB']=='psql') {
     $where_cervene = " DATUM_PODATELNA_PRIJETI+CAST( LHUTA || ' days' AS interval ) < CURRENT_DATE AS cervena";
     $where_zlute = " DATUM_PODATELNA_PRIJETI+CAST( LHUTA-5 || ' days' AS interval ) < CURRENT_DATE AS zluta";
  }
  if ($GLOBALS['CONFIG']['DB']=='mssql')  {
    $where_cervene = " CONVERT(datetime,DATUM_PODATELNA_PRIJETI,104)+LHUTA < GETDATE() AS cervena";
    $where_zlute = " CONVERT(datetime,DATUM_PODATELNA_PRIJETI,104)+LHUTA-5 < GETDATE() AS zluta";

    $where_cervene = " CONVERT(datetime,DATUM_PODATELNA_PRIJETI,104)+LHUTA AS cervena";
    $where_zlute = " CONVERT(datetime,DATUM_PODATELNA_PRIJETI,104)+LHUTA-5 AS zluta,GETDATE() as dnesni_datum";
  
  }

  $sql="/*NO LOAD BALANCE*/ SELECT $where_cervene,$where_zlute,* FROM posta WHERE ID IN (".$id.")";
  //tak uzivatel kliknul, ze si chce danou pisemnost precist
  $q=new DB_POSTA;
  $w=new DB_POSTA;
  //echo $sql;
  $q->query($sql);
  $q->Next_Record();
  
  switch ($q->Record["ODESLANA_POSTA"]) {
    case 'f': {
      $status = 2;
      if ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"]) $datum_predani=$q->Record["DATUM_PREDANI"]; else $datum_predani='1.1.2008';
      //pokud je povoleno datum predani a neni tam datum
//      if ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"] && strlen($datum_predani)<1 && $q->Record["ODES_TYP"]<>'X') $status = 7;
      if ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"] && strlen($datum_predani)<1) $status = 7;

      if ($q->Record['ODBOR']<1 && $q->Record['REFERENT']<1) $status = 7;


      if ($GLOBALS['CONFIG_POSTA']['PLUGINS']['schvalovani']['enabled'] == true) {
        include_once(FileUp2('posta/plugins/schvalovani/.admin/schvalovani.inc'));
        if (JeVeSchvaleni($id)) {$status = 11; break;}
        if (JeKPodpisu($id)) {$status = 11; break;}
      }

      //vyrizene
      if (strlen($q->Record["DATUM_VYRIZENI"])>1 && strlen($q->Record["VYRIZENO"])<3) {$status = 4; break;}
      if (strlen($q->Record["DATUM_VYRIZENI"])>1 && strlen($q->Record["VYRIZENO"])>3) {$status = 1; break;}

      if (strlen($q->Record["DATUM_VYRIZENI"])>1) {$status = 1; break;}

      //zelene
      if ($q->Record["REFERENT"]<1 && $q->Record['ODBOR']>0 && strlen($q->Record["DATUM_REFERENT_PRIJETI"])<1 && strlen($q->Record["DATUM_VYRIZENI"])<1 && strlen($datum_predani)>1 && $q->Record["ZLUTA"]<>'t' && $q->Record["CERVENA"]<>'t') {$status = 2; break;}
      //modre
      if ($q->Record["REFERENT"]>1 && strlen($q->Record["DATUM_REFERENT_PRIJETI"])<1 && strlen($q->Record["DATUM_VYRIZENI"])<1 && strlen($datum_predani)>1 && $q->Record["ZLUTA"]<>'t' && $q->Record["CERVENA"]<>'t') {$status = 3; break;}
      //cerne
      if ($q->Record["REFERENT"]>1 && strlen($q->Record["DATUM_REFERENT_PRIJETI"])>1 && strlen($q->Record["DATUM_VYRIZENI"])<1 && strlen($datum_predani)>1 && $q->Record["ZLUTA"]<>'t' && $q->Record["CERVENA"]<>'t') {$status = 4; break;}

      if ($q->Record["ZLUTA"]=='t') $status = 5;
      if ($q->Record["CERVENA"]=='t') $status = 6;
      if ($GLOBALS["CONFIG"]["DB"]=="mssql") {
			  if ($q->Record["ZLUTA"]<$q->Record["DNESNI_DATUM"]) $status = 5;
			  if ($q->Record["CERVENA"]<$q->Record["DNESNI_DATUM"]) $status = 6;
			}


      break;
    }
    case 't': {
      $status = 8;

//      if (JeVeSchvaleni($id) && (strlen($q->Record["DATUM_VYPRAVENI"])<1)) {$status = 11; break;}

      if ($GLOBALS['CONFIG_POSTA']['PLUGINS']['schvalovani']['enabled'] == true) {
        include_once(FileUp2('posta/plugins/schvalovani/.admin/schvalovani.inc'));
        if (JeVeSchvaleni($id)) {$status = 11; break;}
        if (JeKPodpisu($id)) {$status = 11; break;}
      }


      //ty, ktere jsou nejsou odeslane
      if (strlen($q->Record["DATUM_PODATELNA_PRIJETI"])<1 && $GLOBALS['ODES_TYP']<>'Z') {$status = 4; break;}

      if ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"]) $datum_predani=$q->Record["DATUM_PREDANI_VEN"]; else $datum_predani='1.1.2008';

      //ty, ktere jsou nejsou odeslane,ale jsou predane
      if (strlen($datum_predani)>5 && strlen($q->Record["DATUM_VYPRAVENI"])<1 && $GLOBALS['ODES_TYP']<>'Z') {$status = 13; break;}

      //ty, ktere jsou nejsou odeslane,a jsou jeste nepredane
      if (strlen($q->Record["DATUM_VYPRAVENI"])<1 && $GLOBALS['ODES_TYP']<>'Z') {$status = 12; break;}

      //ty, ktere jsou dorucene
      if (strlen($q->Record["DATUM_DORUCENI"])>1) $status = 1;

      //zkontrolujeme, jestli se ma hlidat dorucenka.
      $sedive=false;
      reset($GLOBALS["CONFIG"]["TYP_ODESLANI"]);  
      while (list($key,$val)=each($GLOBALS["CONFIG"]["TYP_ODESLANI"])) {
//        If ($val['VALUE']==$q->Record['DOPORUCENE'] && $val['DORUCENKA']==0 && $val['DORUCENKA']==4) $sedive=true;
        If ($val['VALUE']==$q->Record['DOPORUCENE'] && $val['DORUCENKA']==0) $sedive=true;
      }    
//      If ($GLOBALS["ODESLANA_POSTA"]=='t' && ($q->Record["ODES_TYP"]=='X' || $q->Record["ODES_TYP"]=='Z')) $sedive=true;
      //If ($GLOBALS["ODESLANA_POSTA"]=='t' && ($q->Record["ODES_TYP"]=='Z')) $sedive=true;

      if ((($GLOBALS["CONFIG"]["PREDANI_PRES_CK"] && strlen($q->Record["DATUM_PREDANI_VEN"])<1)&&strlen($q->Record["DATUM_VYPRAVENI"])<1)&&($q->Record["DOPORUCENE"]=='1' || $q->Record["DOPORUCENE"]=='2')) $status = 8; 

      //vsechny obycejne jsou vyrizene
      if ($sedive && $q->Record["VLASTNICH_RUKOU"]<3 && strlen($q->Record['DATUM_VYPRAVENI'])>4) {$status = 1; break;}

      if (($q->Record["ODES_TYP"]<>'Z' && strlen($q->Record["DATUM_VYPRAVENI"])<1)) {$status = 12; break;}

      //vlastni zaznamy bez CJ taky nejsou uzavrene
      //if (($q->Record["ODES_TYP"]=='Z' && strlen($q->Record["DATUM_VYPRAVENI"])<1)) {$status = 9; break;}

      //vsechny obycejne jsou vyrizene
      if ($sedive && $q->Record["VLASTNICH_RUKOU"]<3 && ($q->Record['DOPORUCENE']==2 ||$q->Record['DOPORUCENE']==1)) {$status = 9; break;}
      //vsechny obycejne jsou vyrizene
      if ($sedive && $q->Record["VLASTNICH_RUKOU"]<3 ) {$status = 1; break;}


      //vsechny vnitrni postou a vlastni zaznamy jsou vyrizene
      if (($q->Record["ODES_TYP"]=='X' && strlen($q->Record["DATUM_VYPRAVENI"])>1) || $q->Record["ODES_TYP"]=='Z') {$status = 1; break;}
     
      //vsechny co se nedorucuji jsou vyrizene
      if (($q->Record["DOPORUCENE"]=='X' && strlen($q->Record["DATUM_VYPRAVENI"])<1)) {$status = 9; break;}
      if (($q->Record["DOPORUCENE"]=='X' && strlen($q->Record["DATUM_VYPRAVENI"])>1)) {$status = 1; break;}
     

      //vsechny, co jsou jinak nez ceskou postou a ma dorucenku 
      if (strlen($q->Record["DATUM_DORUCENI"])>3) {$status = 1;break;}


      //vsechny, co jsou jinak nez ceskou postou a maji dorucenku a nebo jsou sedive
      if ($q->Record["VLASTNICH_RUKOU"]>2 && ((strlen($q->Record["DATUM_VYPRAVENI"])>1 && strlen($q->Record["DATUM_DORUCENI"])>3))) {$status = 1;break;}

      //vsechny, co jsou emailem vypravene
      if ($q->Record["VLASTNICH_RUKOU"]==5 && (strlen($q->Record["DATUM_VYPRAVENI"])>1)) {$status = 1;break;}
      //vsechny, co jsou jinak nez ceskou postou a maji dorucenku a nebo jsou sedive
      if ($q->Record["VLASTNICH_RUKOU"]>2 && (strlen($q->Record["DATUM_VYPRAVENI"])<1)) {$status = 9;break;}
      //je to uz na podatelne (ty, ktere nejsou vypravene)
      if ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"] && strlen($q->Record["DATUM_PREDANI_VEN"])>1 && strlen($q->Record["DATUM_VYPRAVENI"])<1) $status = 7; 

      break;
    }
  }  

  if ($id==999999999) $status = 9;
  //dokumenty ve spisu - uzavrene dokumenty
  if ($q->Record["CISLO_SPISU1"]>0 && strlen($q->Record["SPIS_VYRIZEN"])>0) $status = 1;

//  //ty, ktere jsou ve spisu, ktery neni uzavren - rozsireno, ukazuje se nenevyrizene pouze majiteli
//  if ($status == 1 && $q->Record["CISLO_SPISU1"]>0 && strlen($q->Record["SPIS_VYRIZEN"])<1 && MajitelSpisu($id)==$q->Record['REFERENT']) $status = 9;
  if ($status == 1 && $q->Record["CISLO_SPISU1"]>0 && strlen($q->Record["SPIS_VYRIZEN"])<1) $status = 9;


  if ($q->Record["STAV"]==2) $status = 101;


  if ($q->Record['SPIS_VYRIZEN']>0) {
    $cj_obj = LoadClass('EedCj',$id);
    $cj_info = $cj_obj->GetCjInfo($id);
    $spis_id = $cj_info['SPIS_ID'];

    $sql="SELECT * FROM posta_spisovna WHERE DOKUMENT_ID IN (".$spis_id.")";
    $w->query($sql); $w->Next_Record();
    if (strlen($w->Record["REGISTRATURA"])>1 && $w->Record["SPISOVNA_ID"]<1 && strlen($q->Record["SPIS_VYRIZEN"])>0) $status = -4;
    if (strlen($w->Record["REGISTRATURA"])<1 && $w->Record["SPISOVNA_ID"]<1 && strlen($q->Record["SPIS_VYRIZEN"])>0) $status = 1;

  }


//   if ($q->Record['SPIS_VYRIZEN']>0) {
//     $cj_obj = LoadClass('EedCj',$id);
//     $cj_info = $cj_obj->GetCjInfo($id);
//     $spis_id = $cj_info['SPIS_ID'];
//
//     $cj_obj = LoadClass('EedCj',$spis_id);
//     $cj_info = $cj_obj->GetCjInfo($spis_id);
//     if ($cj_info['STATUS'] == -4) $status = -4;
//     if ($cj_info['STATUS'] <> -4) $status = -4;
//   }
//


//  echo "zluta je ".$q->Record["ZLUTA"];
//  echo "<br/>cervena je ".$q->Record["CERVENA"]."<br/>";

  if (strlen($q->Record["STORNOVANO"])>0) $status = -1;
  if (strlen($q->Record["SKARTOVANO"])>0) $status = -2;
  if ($q->Record["SPISOVNA_ID"]>0) $status = -3;

  


  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  if (!$LAST_USER_ID) $LAST_USER_ID=$id_user;
  $OWNER_ID=$id_user;
  $LAST_TIME=Date('H:i:s');
  $LAST_DATE=Date('Y-m-d');

  $login = getEnv("REMOTE_USER");
  $logged_user = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo($login,true);
  if ($logged_user[ID]>0) {
    $LAST_USER_ID= $logged_user[ID];
  }
  if ($status) {
    $sql="UPDATE posta SET status=$status,last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID WHERE id=".$id;
    $q->query($sql);
  }
  return $status;
}
/*
Nahrazeno EedTools::UkazPocetDleStatus(11, $where)

function UkazPocetDleStatus($status,$where="") {
  $so=VratSuperOdbor();
  $sql="SELECT id FROM posta p WHERE 1=1  $where and status IN (".$status.") and stornovano is null" ;
  $q=new DB_POSTA;
//  echo $sql . '<br/>';
  $q->query($sql);
  $pocet=$q->Num_Rows();
  if ($pocet>0) return "<b>".$pocet."</b>";
  else
    return $pocet;
}
*/

function ZapisCJ($id,$text)
{
  $q=new DB_POSTA;
  $id=(int)$id;
  if ($id<0 || $id=='') return false;
  $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  if (!$LAST_USER_ID) $LAST_USER_ID=$id_user;
  $OWNER_ID=$id_user;
  $LAST_TIME=Date('H:i:s');
  $LAST_DATE=Date('Y-m-d');

  $sql="update posta set text_cj='".$text."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id=".$id;
  $q->query($sql);
  
}

FUnction Skartace_Pole($skartace)
{
  $res="";
  If ($skartace>0)
  {
    $a=new DB_POSTA;
    $sql='select kod, skar_znak, doba, text from cis_posta_skartace where id='.$skartace;
    $a->query($sql);
    $a->Next_Record();
    $text_skartace=str_replace('STARE - ','',$a->Record["TEXT"]);
    $text=substr($text_skartace,0,strpos($text_skartace,' '));
//    $res=$text." ".$a->Record["SKAR_ZNAK"]."/".$a->Record["DOBA"];
    $res=array('kod'=>$a->Record['KOD'],'znak'=>$a->Record['SKAR_ZNAK'],'doba'=>$a->Record['DOBA'],'text'=>$text_skartace);

  }
  return $res;
}

Function NajdiSpisZnak($cs1=0,$cs2=0) {
  $sql="select id,skartace from posta where cislo_spisu1=".$cs1." and cislo_spisu2=".$cs2." and stornovano is null and main_doc=1 order by id asc";
  $a=new DB_POSTA;
  $a->query($sql);
  while ($a->Next_Record())
  {
    $skartace=$a->Record['SKARTACE'];
    $id=$a->Record['ID'];
    $pole=Skartace_Pole($skartace);
    if ($pole['znak']<>'X') return $pole;
  }
//   if (!$id or $id==0) {
//     $sql="select id,skartace from posta_stare_zaznamy where cislo_spisu1=".$cs1." and cislo_spisu2=".$cs2." and stornovano is null and main_doc=1 order by id asc";
//     $a=new DB_POSTA;
//     $a->query($sql);
//     while ($a->Next_Record()) {
//       $skartace=$a->Record['SKARTACE'];
//       $id=$a->Record['ID'];
//       $pole=Skartace_Pole($skartace);
//       if ($pole['znak']<>'X') return $pole;
//     }
//     if ($cs2==2011) $pole = array(); //na zadost p. Krejsarove
//
//   }

  return $pole;
}

Function RokSkartace($cs1=0,$cs2=0)
{
  if ($cs2 == 0) {
    $sql="select skartace,cislo_spisu1,datum_vyrizeni,spis_vyrizen,datum_vypraveni,datum_doruceni,datum_podatelna_prijeti,odeslana_posta from posta
     where id=$cs1";
  }
  else
    $sql="select skartace,cislo_spisu1,datum_vyrizeni,spis_vyrizen,datum_vypraveni,datum_doruceni,datum_podatelna_prijeti,odeslana_posta from posta
    where cislo_jednaci1=".$cs1." and cislo_jednaci2=".$cs2." and stornovano is null order by id asc";
  $a=new DB_POSTA;
  $a->query($sql);
  while ($a->Next_Record()) {
    $skartace=$a->Record['SKARTACE'];

    $datum = $a->Record['SPIS_VYRIZEN'];
    if ($a->Record['SPIS_VYRIZEN']=='') {
      if ($a->Record['CISLO_SPISU1'] == '' and $a->Record['ODESLANA_POSTA']=='f') {
        $datum=$a->Record['DATUM_VYRIZENI'];
      } 
      if ($a->Record['SPIS_VYRIZEN']=='' and $a->Record['CISLO_SPISU1']=='' and $a->Record['ODESLANA_POSTA']=='t') {
        if ($a->Record['DATUM_VYPRAVENI']<>'') $datum = $a->Record['DATUM_VYPRAVENI'];
        if ($a->Record['DATUM_DORUCENI']<>'') $datum = $a->Record['DATUM_DORUCENI'];
        if (strlen($a->Record['DATUM_PODATELNA_PRIJETI'])>1) $datum = $a->Record['DATUM_PODATELNA_PRIJETI'];
      }  
      $datum_temp = explode(' ', $datum);
      $datum_temp_eng = explode('.', $datum_temp[0]);
      $datum = $datum_temp_eng[2] . '-' . $datum_temp_eng[1] . '-' . $datum_temp_eng[0];
    } 

    $pole=Skartace_Pole($skartace);
    if ($pole['znak']<>'X') {
      $date1=explode("-",$datum);
      $rok=$date1[0];
      $rok=$rok+$pole['doba']+1;   
      return $rok;
    }
  }
}

Function JeVeSpisovne($cs1=0,$cs2=0,$skok=0)
{
  $sql="select * from posta_spisovna where cislo_spisu1=".$cs1." and cislo_spisu2=".$cs2." order by id asc";
  $a=new DB_POSTA;
  $a->query($sql);
  $pocet=$a->Num_Rows();
  if ($pocet>0)
  {
    $a->Next_Record();
    $data=$a->Record;
    /*$datum=$a->Record['DATUM_PREDANI'];
    $datum=$a->dbdate2str($datum);
    $skartace=$a->Record['ROK_SKARTACE'];
    $listu=$a->Record['LISTU'];*/
    return $data;
  }
  if ($skok==0) //abychom necyklili
  {
    //Koukneme, jestli to neni ve sloucene s jinym cislem jednaci
    include_once(FileUp2('/services/spisovka/uzavreni_spisu/funkce.inc'));
    $dalsi_spisy=VyhledejDalsiSpisy($cs1.'/'.$cs2);
    while (list($key,$val)=each($dalsi_spisy))
    {
      list($cj1,$cj2)=explode('/',$val['spis']);
      if ($cj1<>$cs1)
        if ($vysl=JeVeSpisovne($cj1,$cj2,1)) return (array('PREEVIDOVANO'=>" spis ".$cj1."/".$cj2));
    }

    return false;
  }
  return $data;
}


