<?php
include_once(FileUp2(".admin/upload_.inc"));

function ExportShowCJSpisovna($DOKUMENT_ID,$CISLO_SPISU1,$CISLO_SPISU2) {
  if ($DOKUMENT_ID>0) {
    $res = tableFormatCJednaci($DOKUMENT_ID, 0);
  }
  else {
    $res = $CISLO_SPISU1 . '/' . $CISLO_SPISU2;
  }
  $res = strip_tags($res);
  $res = str_replace('&nbsp;', ' ', $res);
  return $res;
}

function Listu($spis1,$spis2,$id=0) {
  $q=new DB_POSTA;
  $a=new DB_POSTA;
  if ($id>0) {
    $sql = 'select * from posta_spisovna where dokument_id='.$id;
    $q->query($sql); $q->Next_Record();
    if ($q->Record['LISTU']>0)
    {
      $res="<b>".wordwrap($q->Record['LISTU'],20, "<br />", true)."</b><br/>".wordwrap($q->Record['PRILOHY'],20, "<br />", true)."";
      return $res;
    }
  }
  If ($spis1 && $spis2) {
    $res="";
    $pocet_listu_celkem=0;
    $where_spis="(cislo_spisu1=".$spis1." and cislo_spisu2=".$spis2.")";
    $dalsi_spisy= VyhledejDalsiSpisy($spis1."/".$spis2);
    while (list($key,$val)=each($dalsi_spisy)) {
      list($cj1,$cj2)=explode('/',$val['spis']);
      $where_spis.=" OR (cislo_spisu1=".$cj1." and cislo_spisu2=".$cj2.")";
    }
//    $sql="select id,odes_typ,typ_dokumentu,skartace,pocet_listu,pocet_priloh,druh_priloh from posta where (".$where_spis.") and stornovano is null and superodbor in (".VratSuperOdbor().") ";
    $sql="select id,odes_typ,typ_dokumentu,skartace,pocet_listu,pocet_priloh,druh_priloh from posta where (".$where_spis.") and stornovano is null  ";
    $q->query ($sql);
    $id_dokumentu=0;
    while($q->next_record()) {
      if ($id_dokumentu==0) $id_dokumentu=$q->Record['ID'];
      $pocet_listu = $q->Record["POCET_LISTU"];
      $pocet_priloh = $q->Record["POCET_PRILOH"];
      $druh_priloh = trim($q->Record["DRUH_PRILOH"]);
      if ($q->Record['SKARTACE']==2398 || $q->Record['TYP_DOKUMENTU']=='D') {$pocet_listu=0; $pocet_priloh=0;}//neni urceno ke skartaci
//      if ($q->Record['SKARTACE']==2398 || $q->Record['TYP_DOKUMENTU']=='D' || $q->Record['ODES_TYP']=='X') {$pocet_listu=0; $pocet_priloh=0;}//neni urceno ke skartaci

      $pocet_listu_celkem=$pocet_listu_celkem+$pocet_listu;
      $pocet_priloh_celkem[$druh_priloh]=$pocet_priloh_celkem[$druh_priloh]+$pocet_priloh;


      $sql='select listu from posta_spisobal where posta_id='.$q->Record['ID'];
      $a->query($sql); $a->Next_Record();
      $pocet_prebal=$a->Record['LISTU'];
      if ($pocet_prebal>0 && $celkem_prebal<1) {$celkem_prebal=$pocet_prebal; }


    }
  }
//  if ($celkem_prebal>0) $pocet_listu_celkem.=" + ".$celkem_prebal; //pricteme spis obal a prehled
  while (list($key,$val)=@each($pocet_priloh_celkem)) if ($val>0) {$prilohy.="$key: $val\n"; $prilohy_celkem[$key]=$prilohy_celkem[$key]+$val;}
//  $pocet_listu_celkem=$pocet_listu_celkem+1;
 if ($celkem_prebal>0 && $GLOBALS['SHOW_CJ']<2) $pocet_listu_celkem=$pocet_listu_celkem+$celkem_prebal;
  return $pocet_listu_celkem.", ".$prilohy;

}

function Digitalne($spis1,$spis2) {
  $q=new DB_POSTA;
  $a=new DB_POSTA;
  If ($spis1 && $spis2) {
    $res="";
    $pocet_listu_celkem=0;
    $where_spis="(cislo_spisu1=".$spis1." and cislo_spisu2=".$spis2.")";
    $dalsi_spisy= VyhledejDalsiSpisy($spis1."/".$spis2);
    while (list($key,$val)=each($dalsi_spisy)) {
      list($cj1,$cj2)=explode('/',$val['spis']);
      $where_spis.=" OR (cislo_spisu1=".$cj1." and cislo_spisu2=".$cj2.")";
    }
    $res="";
    $pocet_listu_celkem=0;
//    $sql="select id,odes_typ,typ_dokumentu,skartace,pocet_listu,pocet_priloh,druh_priloh from posta where (".$where_spis.") and stornovano is null and superodbor in (".VratSuperOdbor().") order by id asc";
    $sql="select id,odes_typ,typ_dokumentu,skartace,pocet_listu,pocet_priloh,druh_priloh from posta where (".$where_spis.") and stornovano is null order by id asc";
    $q->query ($sql);
    $id_dokumentu=0;
    $digitalnich=0;
    while($q->next_record()) {
      if ($q->Record['TYP_DOKUMENTU']=='D' && $q->Record['SKARTACE']<>2398) {$digitalnich++;}//neni urceno ke skartaci
//      if ($q->Record['SKARTACE']==2398 || $q->Record['TYP_DOKUMENTU']=='D' || $q->Record['ODES_TYP']=='X') {$pocet_listu=0; $pocet_priloh=0;}//neni urceno ke skartaci
    }
  }
  return "".$digitalnich."";

}

function SkartacniZnak($znak,$pole, $id=0) {
  static $q;
  If (!$q) $q=new DB_POSTA;
  if ($id>0) {
    $sql = 'select * from posta_spisovna where dokument_id='.$id;
    $q->query($sql); $q->Next_Record();
    if ($pole == 'DOBA') $pole = 'LHUTA';
    if ($q->Record[$pole]<>'') return $q->Record[$pole];
  }

  If ($znak) {
    $sql='select * from cis_posta_skartace where id='.$znak;
    $q->query($sql);
    $q->Next_Record();
    $pole_x=$q->Record;
    $pole_x['SPIS_CISLO']=substr($pole_x["TEXT"],0,strpos($pole_x["TEXT"],' '));
    return $pole_x[$pole];
  }
}

function UkazKdoSpisovna($datum,$id,$protokol) {
  $q=new DB_POSTA;
  $res=$q->dbdate2str($datum);
  $res.="<br/>".UkazUsera($id);
  $id=$GLOBALS['ID'];
  $GLOBALS['ID']=$protokol;
//  if ($protokol>0) $res.="<br/>".FormatSpis($protokol,-1);
  if ($protokol>0) {
    $sql='select * from posta where id='.$protokol;
    $q->query($sql); $q->Next_Record();
    $res.="<br/><a href='/ost/posta/brow.php?cislo_spisu1=".$q->Record['CISLO_SPISU1']."&cislo_spisu2=".$q->Record['CISLO_SPISU2']."'>protokol ".$q->Record['CISLO_SPISU1']."/".$q->Record['CISLO_SPISU2']."</a>";

  }
  $GLOBALS['ID']=$id;
  //$res.="<br/>".$protokol;
  return $res;

}

function Skartace($ida) {
  $res="<a href=\"skartovano.php?id=".$ida."\"><img src=".FileUpURL('images/trash.gif')." border=0 title='Skartovat písemnost'></a>";
  return $res;
}

function UkazPocetCJ($id) {
  $q=new DB_POSTA;
  $pocet = 0; $res="";
  if ($id>0) {
    $sql = 'select * from cis_posta_spisy where spis_id='.$id.' and dalsi_spis_id>0';
    $q->query($sql);
    $pocet = $q->Num_Rows();
  }
  if ($pocet>0) $res.="&nbsp;<b>(+".$pocet.")</b>";
  return $res;
}

function ExportSkartacniZnak($znak, $alt) {
  $res = $znak;
  return $res;
}

function ExportKdoSpisovna($datum,$id,$protokol) {
  $q=new DB_POSTA;
  $res=$q->dbdate2str($datum);
  $res.="<br/>".UkazUsera($id);
  $id=$GLOBALS['ID'];
  $GLOBALS['ID']=$protokol;
//  if ($protokol>0) $res.="<br/>".FormatSpis($protokol,-1);
  if ($protokol>0) {
    $sql='select * from posta where id='.$protokol;
    $q->query($sql); $q->Next_Record();
    $res.="<br/><a href='/ost/posta/brow.php?cislo_spisu1=".$q->Record['CISLO_SPISU1']."&cislo_spisu2=".$q->Record['CISLO_SPISU2']."'>protokol ".$q->Record['CISLO_SPISU1']."/".$q->Record['CISLO_SPISU2']."</a>";

  }
  $GLOBALS['ID']=$id;
  //$res.="<br/>".$protokol;
  $res = strip_tags($res);
  return $res;

}


