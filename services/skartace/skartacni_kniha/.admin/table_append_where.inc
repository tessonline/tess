<?php

$where=str_replace(' superodbor',' p.superodbor',$where);


if ($GLOBALS["ROK_SKARTACE"] && !$GLOBALS['SPISOVNA_ID']) {
  $where.=" AND EXTRACT(YEAR FROM ((DATUM_PODATELNA_PRIJETI)))+k.DOBA+1=".$GLOBALS["ROK_SKARTACE"];
}
if ($GLOBALS['SKARTACNI_RIZENI_ID']) {
  UNSET($_SESSION['SPISOVNA_ID']);
  UNSET($GLOBALS['SPISOVNA_ID']);
}
If ($GLOBALS['LOKACE_ID']) {
  $cc = new DB_POSTA;
  $sql = 'select * from posta_spisovna_cis_lokace where id=' . $GLOBALS['LOKACE_ID'];
  $cc->query($sql);
  $cc->Next_Record();
  $GLOBALS['SPISOVNA_ID'] = $cc->Record['SPISOVNA_ID'];
}

Access;
if (HasRole('spisovna') || HasRole('spisovna-odbor')) $showedit=true;

$caption="Dokumenty ve spisovně";
$caption2 = "Dokumenty ve skartačním řízení";

if ($GLOBALS['PREDANI']) $caption="Dokumenty pro předání do spisovny";


if ($GLOBALS['PROTOKOL']) UNSET($GLOBALS['SPISOVNA_ID']);

// if (!$GLOBALS['SPISOVNA_ID'] && !$GLOBALS['SKARTACNI_RIZENI_ID'] && !$GLOBALS['SHOW_BOX']) {
//   $where2=" AND (p.spisovna_id=0 or p.spisovna_id is null)"; $caption="Dokumenty, které mohou být předány do spisovny"; $showedit=false;
//   $where2.= " AND p.id not in (select dalsi_spis_id from cis_posta_spisy where dalsi_spis_id<>spis_id)";
//   if ($GLOBALS['CONFIG']['USE_SUPERODBOR'] && !HasRole('spravce')) $where2 .= " AND superodbor in (" . EedTools::VratSuperOdbor() .") ";
//
// //  $where2 = "AND (exists (select spis_id from cis_posta_spisy WHERE p.id=cis_posta_spisy.spis_id and (dalsi_spis_id=spis_id or dalsi_spis_id=0)) OR (cislo_spisu1=0 and spisovna_id=0))";
// }

if (!$GLOBALS['SPISOVNA_ID'] && !$GLOBALS['SKARTACNI_RIZENI_ID'] && $GLOBALS['SHOW_BOX']) {
  $where2=" AND (spisovna_id=0 or spisovna_id is null)"; $caption="Archivační boxy, které mohou být předány do spisovny"; $showedit=false;
//  $where2.= " AND p.id not in (select dalsi_spis_id from cis_posta_spisy where dalsi_spis_id<>spis_id)";
  $where = '';
  $showedit = true;
  $agenda = 'POSTA_SPISOVNA_BOXY';
}

if ($GLOBALS['SPISOVNA_ID']) {
  $where2=" AND not exists (select spisovna_id from posta_skartace_id where s.id=posta_skartace_id.spisovna_id)";
}

if ($GLOBALS["CISLO_SPISU1_TEXT"])  {
  $GLOBALS['CISLO_SPISU1']=$GLOBALS["CISLO_SPISU1_TEXT"];
  //nejdriv pridelime cj k roku
  if (ereg('/',$GLOBALS["CISLO_SPISU1_TEXT"])) list($GLOBALS["CISLO_SPISU1"],$GLOBALS["CISLO_SPISU2"])=explode('/',$GLOBALS["CISLO_SPISU1_TEXT"]);
  //a pak ho zkusime parsovat na poradove cislo a podcislo
  if (ereg('-',$GLOBALS["CISLO_SPISU1_TEXT"])) list($GLOBALS["CISLO_SPISU1"],$GLOBALS["PODCISLO_SPISU"])=explode('-',$GLOBALS["CISLO_SPISU1_TEXT"]);
  if (!ereg('/',$GLOBALS["CISLO_SPISU1_TEXT"]) && !ereg('-',$GLOBALS["CISLO_SPISU1_TEXT"])) {$GLOBALS['CISLO_SPISU1']=$GLOBALS["CISLO_SPISU1_TEXT"]; $GLOBALS['CISLO_SPISU2']=Date('Y');}
}

if ($GLOBALS['CISLO_SPISU1']<>'') $GLOBALS['CISLO_SPISU1']=(int)$GLOBALS['CISLO_SPISU1']; 


if ($GLOBALS['SKAR_ZNAK'] && !$GLOBALS['SPISOVNA_ID'] && !$GLOBALS['SKARTACNI_RIZENI_ID']) {$where.=" AND k.skar_znak like '".$GLOBALS['SKAR_ZNAK']."'";}
if ($GLOBALS['DOBA'] && !$GLOBALS['SPISOVNA_ID']) {$where.=" AND k.doba = ".$GLOBALS['DOBA'];}
if ($GLOBALS['DOBA'] && $GLOBALS['SPISOVNA_ID']) {$where.=" AND s.lhuta = ".$GLOBALS['DOBA'];}
$je_spisovna=false;$show_select=true;

if ($GLOBALS['POZNAMKA'] && $GLOBALS['SPISOVNA_ID']) $where.=" and s.poznamka like '%".$GLOBALS['POZNAMKA']."%'";

if ($GLOBALS['ODBOR']) {
  $prvni = $GLOBALS['ODBOR'];
  $EedUser = LoadClass('EedUser', $USER_INFO['ID']);
  
  $pole_pom=VratSpisUzly($EedUser->VratSpisUzelZOdboru($prvni));
  $GLOBALS['ODBOR'] = array();
  $GLOBALS['ODBOR'][] = $prvni;
  while (list($key,$val)=each($pole_pom)) //prekreslime
    $GLOBALS['ODBOR'][] = $key;
}


if ($GLOBALS['ODBOR'] && $GLOBALS['REFERENT']) UNSET($GLOBALS['ODBOR']); //vyhledavame jen podle referenta, kasleme na utvar, co kdyz se stehoval?


if ($GLOBALS['SPISOVNA_ID'])  {

  $spisovna = getSelectDataEed(new of_select_spisovna(array()));
  $nazev_spisovny = $spisovna[$GLOBALS['SPISOVNA_ID']];
  $caption .= ' - ' . $nazev_spisovny;
  $caption2 .= ' - ' . $nazev_spisovny;

  $where = '';
  //pridame pro jistotu podminku na superodbor - casem ji vypodminkujeme, az bude hlavni spravce spisoven
//   if (HasRole('spisovna')||HasRole('access_all')) {
//     if ($GLOBALS['omez_zarizeni'])
//       $where .= ' AND s.superodbor in ('.$GLOBALS['omez_zarizeni'].')';
//   }
//   else
//  $where .= ' AND s.superodbor in (' . EedTools::VratSuperOdbor() .')';

  //UNSET($GLOBALS['SKAR_ZNAK']); 
  $je_spisovna=true;
  if ($GLOBALS['REFERENT']) $where.=" and p.referent in (".$GLOBALS['REFERENT'].")";
  if ($GLOBALS['TYP_POSTY']) $where.=" and p.typ_posty in (".$GLOBALS['TYP_POSTY'].")";
  $show_select=true;
//  $where.=" and datum_skartace is null and (zapujcka_id is null or zapujcka_id=0)";
  $where.=" and datum_skartace is null and (zapujcka_id is null or zapujcka_id=0)";

  if ($GLOBALS['CISLO_SPISU1']) {
    if (!$GLOBALS['CISLO_SPISU2']) $GLOBALS['CISLO_SPISU2']=Date('Y');
    $dalsi_spisy= VyhledejDalsiSpisy($GLOBALS['CISLO_SPISU1']."/".$GLOBALS['CISLO_SPISU2']);

    while (list($key,$val)=each($dalsi_spisy)) {
      list($cj1,$cj2)=explode('/',$val['spis']);
      $GLOBALS['CISLO_SPISU1']=$GLOBALS['CISLO_SPISU1'].",".$cj1;
      $GLOBALS['CISLO_SPISU2']=$GLOBALS['CISLO_SPISU2'].",".$cj2;

    }

    
  }
  
  $where=str_replace('p.superodbor','s.superodbor',$where);
}

if ($GLOBALS['ZAPUJCKA_ID']) {
  $where.=" and p.id in (SELECT posta_id from posta_spisovna_zapujcky_id where zapujcka_id in (".$GLOBALS['ZAPUJCKA_ID'].") )";
  UNSET($GLOBALS['ZAPUJCKA_ID']);
}


if ($GLOBALS['SPIS_ZNAK']) {$where.=" AND text like '%".$GLOBALS['SPIS_ZNAK']."%'";}
if ($GLOBALS['SPIS_ZNAK_TEXT']) {$where.=" AND text like '%".$GLOBALS['SPIS_ZNAK_TEXT']."%'";}


if ($GLOBALS['PROTOKOL']) {
  $prot = LoadClass('EedProtokol', $GLOBALS['PROTOKOL']);
  $ids = $prot->VratIDSZProtokolu();
  $rucne_vlozene = true;
  if (count($ids)>0) {
    $where = "";
    $GLOBALS['ID'] = $ids;
    $caption .= ' - protokol ' . $GLOBALS['PROTOKOL'];
  }
  else {
    $GLOBALS['ID'] = -1; 
    $caption = 'Předávací protokol '. $GLOBALS['PROTOKOL'].' NENALEZEN';
    
  } 

  //protoze to zpusobovalo problemy, tak jsem to vypnul
  UNSET($GLOBALS['SPISOVNA_ID']);
}

if ($GLOBALS['TSA_od'] || $GLOBALS['TSA_do']) {
  $sql = 'select l.expiration,l.record_id as doc_id,f.* from upload_files_ltd l left join ' . $GLOBALS['SERVER_CONFIG']['UPLOAD_CONFIG']['MODULES']['table']['TABLE'] . ' f';
  $sql .= ' ON f.id=l.file_id';
  $cc = new DB_POSTA;
  $where_tsa = array();
  if ($GLOBALS['TSA_od']) $where_tsa[] = "expiration>'" . $cc->str2dbdate($GLOBALS['TSA_od'])."'";
  if ($GLOBALS['TSA_do']) $where_tsa[] = "expiration<'" . $cc->str2dbdate($GLOBALS['TSA_do'])."'";

  if (count($where_tsa)>0) {
    $sql .= " WHERE " . implode(' AND ', $where_tsa);
  }

  $count=Table(array(
  //  'showaccess' => true,
    'sql' => $sql,
    'setvars' => true,
    'caption' => 'Dokumenty s časovým razítkem',
  //  'showself'=>true,
    //'select_id'=>ID2,
    'showinfo'=>false,
    'schema_file' => '.admin/table_schema_files.inc',
    'showselect' => true,
    'multipleselect' => true,
    'multipleselectsupport' => true,
    'showedit' => false,
    'showdelete' => false,
    'showhistory' => false,
  //  'return_sql'=>true,
    'page_size'=>'50',
  ));

  $sql_select = stripslashes($GLOBALS['TABLE_SELECT']);

  $show.="<form action='soubory_update.php' method='post'><input type='hidden' name='sql' value=\"".$sql_select."\">";
  $show.="<input type='submit' name='' value='Aktualizovat časová razítka' class='btn'></form>";

  echo $show;
  include_once(FileUp2('html_footer.inc'));
  Die();
}

if ($GLOBALS['SKARTACNI_RIZENI_ID']) {
  $q = new DB_POSTA;
  $where=str_replace('p.superodbor','s.superodbor',$where);
  $sql = 'select * from posta_skartace where id='.$GLOBALS['SKARTACNI_RIZENI_ID'];
  $q->query($sql); $q->Next_Record();
  $caption = 'Skartační řízení: ' . $q->Record['JID'];
}

if (strlen($where)<3) $where = '';
$prefix = $GLOBALS['PREDANI'] ==1 ? "p" : "s";
/*if ($where == '')   $where = ' AND '.$prefix.'.superodbor in (' . EedTools::VratSuperOdbor() .')';*/

if (($where == '') && ($GLOBALS['PREDANI'] !=1 ) && !HasRole('spisovna') && !HasRole('access_all')) $where = ' AND '.$prefix.'.superodbor in (' . EedTools::VratSuperOdbor() .')';
