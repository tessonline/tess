<?php
include_once(FileUp2(".admin/upload_.inc"));
function ShowCJSpisovna($DOKUMENT_ID,$CISLO_SPISU1,$CISLO_SPISU2) {
  if ($GLOBALS['REGISTRATURA'] <> '-1') {
    $res = tableFormatCJednaci($DOKUMENT_ID, '1');
  }
  else {
      $res = $CISLO_SPISU1 . '/' . $CISLO_SPISU2;
      if ($res <> '/')  $res .= ' - ';
      if ($GLOBALS['TEXT_CJ']<>'') $res .= $GLOBALS['TEXT_CJ'];
  }
  return $res;
}

function Box($DOKUMENT_ID) {
  $sql = 'select b.* from posta_spisovna_boxy_ids i LEFT JOIN posta_spisovna_boxy b ON b.id=i.box_id where posta_id=' . $DOKUMENT_ID.' ';
  $q = new DB_POSTA;
  $q->query($sql);
  $res = array();
  while ($q->Next_Record()) {
    $res[] = $q->Record['EV_CISLO'].'/'.$q->Record['ROK'] .' - '. $q->Record['NAZEV'];
  }
  return implode('<br/>', $res);
}

function Listu($spis1,$spis2,$id=0) {
  $q=new DB_POSTA;
  $a=new DB_POSTA;
  if ($id>0) {
    $sql = 'select * from posta_spisovna where dokument_id='.$id;
    $q->query($sql); $q->Next_Record();
    if ($q->Record['LISTU']>0) {
      $res="<b>".wordwrap($q->Record['LISTU'],20, "<br />", true)."</b><br/>".wordwrap($q->Record['PRILOHY'],20, "<br />", true)."";
      return $res;
    }
  }
  If ($spis1 && $spis2) {
    $res="";
    $pocet_listu_celkem=0;
    $cj=new EedCj($id);
    $dalsi_dokumenty=$cj->GetDocsInCj($id);
    $where_spis = "id in (" . $id . "," . implode(',',$dalsi_dokumenty).")";
    if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) $where_spis = "( " . $where_spis . ") AND superodbor=" . EedTools::VratSuperOdbor();

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


//       $sql='select listu from posta_spisobal where posta_id='.$q->Record['ID'];
//       $a->query($sql); $a->Next_Record();
//       $pocet_prebal=$a->Record['LISTU'];
//       if ($pocet_prebal>0 && $celkem_prebal<1) {$celkem_prebal=$pocet_prebal; }


    }
  }
//  if ($celkem_prebal>0) $pocet_listu_celkem.=" + ".$celkem_prebal; //pricteme spis obal a prehled
  while (list($key,$val)=@each($pocet_priloh_celkem)) if ($val>0) {$prilohy.="$key: $val\n"; $prilohy_celkem[$key]=$prilohy_celkem[$key]+$val;}
//  $pocet_listu_celkem=$pocet_listu_celkem+1;
 if ($celkem_prebal>0 && $GLOBALS['SHOW_CJ']<2) $pocet_listu_celkem=$pocet_listu_celkem+$celkem_prebal;
  return "<b>".wordwrap($pocet_listu_celkem,40, "<br />", true)."</b><br/>".wordwrap($prilohy,40, "<br />", true);

}

function Digitalne($spis1,$spis2) {
  $q=new DB_POSTA;
  $a=new DB_POSTA;
  If ($spis1 && $spis2) {
    $res="";
    $pocet_listu_celkem=0;
    $cj=new EedCj($GLOBALS['ID']);
    $dalsi_dokumenty=$cj->GetDocsInCj($GLOBALS['ID']);
    $where_spis = "id in (" . $GLOBALS['ID'] . "," . implode(',',$dalsi_dokumenty).")";
    $res="";
    $pocet_listu_celkem=0;
    if ($GLOBALS['CONFIG']['USE_SUPERODBOR']) $where_spis = "( " . $where_spis . ") AND superodbor=" . EedTools::VratSuperOdbor();

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
  return "<b>".$digitalnich."</b>";

}

function SkartacniZnak($znak,$pole, $id = 0) {
  static $q;
  $cjObj = LoadClass('EedCj', $id);
  $skar_rezim = $cjObj->getSkartacniRezim($id);
  If (!$q) $q=new DB_POSTA;
  if ($id>0) {
    $sql = 'select * from posta_spisovna where dokument_id='.$id;
    $q->query($sql); $q->Next_Record();
    if ($pole == 'DOBA') $pole = 'LHUTA';
    $q->Record['TEXT'] = $q->Record['KOD'] . ' ' . $q->Record['TEXT'];
    if ($skar_rezim['znak']<>'') $q->Record['SKAR_ZNAK'] = $skar_rezim['znak'];
    if ($skar_rezim['doba']>0) $q->Record['LHUTA'] = $skar_rezim['doba'];
    if ($q->Record[$pole]<>'') return $q->Record[$pole];
  }

  If ($znak) {
    $sql='select * from cis_posta_skartace where id='.$znak;
    $q->query($sql);
    $q->Next_Record();
    $pole_x=$q->Record;
//    $pole_x['SPIS_CISLO']=substr($pole_x["TEXT"],0,strpos($pole_x["TEXT"],' '));
    $pole_x['SPIS_CISLO']=$pole_x["KOD"];
    return $pole_x[$pole];
  }
}

function SkartacniZnakDoc($znak,$pole, $id = 0) {
  static $q;
  $cjObj = LoadClass('EedCj', $id);
  $skar_rezim = $cjObj->getSkartacniRezim($id);
  If (!$q) $q=new DB_POSTA;
  if (count($skar_rezim)>0) {
    if ($skar_rezim['znak']<>'') $q->Record['SKAR_ZNAK'] = $skar_rezim['znak'];
    if ($skar_rezim['doba']>0) $q->Record['LHUTA'] = $skar_rezim['doba'];
    if ($q->Record[$pole]<>'') return $q->Record[$pole];
  }
  $skartace = $cjObj->SpisZnak($id);
  return $skartace[$pole];
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

function UkazEdit($id) {
  $q=new DB_POSTA;
  if ($id>0) {
    $sql = 'select * from posta_spisovna where dokument_id='.$id;
    $q->query($sql);
    if ($q->Num_Rows()>0) {
      $q->Next_Record(); $id=$q->Record['ID'];
      $href = "NewWindowSpisovna('".GetAgendaPath("POSTA_SPIS_SPISOVNA",false,true)."/edit.php?edit&EDIT_ID=".$id."')";
    }
    else
      $href = "NewWindowSpisovna('".GetAgendaPath("POSTA_SPIS_SPISOVNA",false,true)."/edit.php?insert&DOKUMENT_ID=".$id."')";

  }
  $res="<a href=\"#\" onclick=\"".$href."\"><img src=".FileUpImage('images/edit')." border=0 title='Editace'></a>";
  return $res;
}

function UkazInfo($id) {
  $q=new DB_POSTA;
  if ($id>0) {
    $sql = 'select * from posta_spisovna where dokument_id='.$id;
    $q->query($sql);
    if ($q->Num_Rows()>0) {
      $q->Next_Record(); $id=$q->Record['ID'];
      $href = "NewWindowSpisovna('".GetAgendaPath("POSTA_SPIS_SPISOVNA",false,true)."/edit.php?info&EDIT_ID=".$id."')";
    }
    else
      $href = "NewWindowSpisovna('".GetAgendaPath("POSTA_SPIS_SPISOVNA",false,true)."/edit.php?info&DOKUMENT_ID=".$id."')";

  }
  $res="<a href=\"#\" onclick=\"".$href."\"><img src=".FileUpImage('images/info_i')." border=0 title='Informace'></a>";
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

function ShowSkartacniZnak($znak, $alt) {
  if ($znak<>'V') return $znak;
  $res = $znak.'&nbsp;&nbsp;<select name="zmena" onChange="save(this,'.$GLOBALS['ID'].');">';
  $res .= '<option value=""></option>';
  $res .= '<option value="A" '.($alt=='A'?'SELECTED':'').'>A</option>';
  $res .= '<option value="S" '.($alt=='S'?'SELECTED':'').'>S</option>';
  $res .= '</select>';
  return $res;
}

Function ShowUploadPostaX($record_id=0, $registratura = -1) {
  if ($registratura<>'-1') return '';
  $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA_SPISOVNA','noshowheader'=>true));
  if ($record_id<0 || $record_id=='') return '&nbsp;';
  $upload_records = $uplobj['table']->GetRecordsUploadForAgenda($record_id);
  $pocet=count($upload_records);
  if ($pocet==0) $img='folder-empty'; else $img='folder';
//  $res='<a href="javascript:upload_KVP_AKCE('.$id_akce.')" class="image" title="('.$pocet.')"><img src="'.FileUp2('images/'.$img.'.gif').'" border="0"></a>';
  $res='<a href="#" onclick="upload_('.$record_id.')" class="image" title="('.$pocet.')"><img src="/'.FileUpImage('images/'.$img).'" border="0"></a>';

//  if (!MaPristupKDokumentu_table($GLOBALS['REFERENT'],$record_id)) $res='&nbsp;';
  return $res;
}

function showProtokol($ID) {
  $text = tableSpisACJ($ID, 1) . UkazPocetCJ($ID);
  static $qqqq;
  if (!$qqqq) $qqqq = new DB_POSTA;
  $sql = 'select * from posta_protokoly_ids where dokument_id=' . $ID;
  $qqqq->query($sql);

  if ($qqqq->Num_Rows()>0) {
    $text .= '<font color="green">';
    while ($qqqq->Next_Record()) {
      $text .= '<br/>Protokol: <a href="brow.php?PROTOKOL='.$qqqq->Record['CISLO'].'">'.$qqqq->Record['CISLO'] .'</a>';
    }
    $text .= '</font>';
  }
  return $text;

}

