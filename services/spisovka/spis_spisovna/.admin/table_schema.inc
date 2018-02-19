<?php

Function DatumArchivaceSpis($datum,$odhad) {
  $res = $datum;
  if ($odhad==1) 
  {
    global $img_alert;
    if (!$img_alert) $img_alert=FileUp2('images/alert.gif');
    $res.="<img src='".$img_alert."' border=0 title='odhad'>";
  }
  return $res;
}

Function UkazSpisovnu($spisovna_id,$datum,$user,$registratura) {
  $res='';
  if ($spisovna_id>0) {
    $q=new DB_POSTA;
    $sql='select spisovna from posta_cis_spisovna where id='.$spisovna_id;
    $q->query($sql);
    $q->Next_Record();
    $res=$q->Record['SPISOVNA'];
    $res.="<br/>".$q->dbdate2str($datum);
    $res.=", ".UkazUsera($user);
  } else {
    if (strlen($registratura)>1) $res = 'registratura:<br/>'.$registratura;
  }
  return $res;
}

Function UkazText($text, $id) {
  if (strlen($text)>0) {
    $res="<a href=\"javascript:NewWindowSpis('".getAgendaPath('POSTA_SPIS_SPISOVNA', false, true)."/edit.php?info&EDIT_ID=$id');\" title='".$text."'>".mb_substr($text,0,5);
    if (strlen($text)>5) $res.='...';
    $res.="</a>";
    return $res;
  }
  else
    return '';
}

$GLOBALS['dostupnost_souboru'] = getSelectDataEed(new of_select_dostupnost_souboru(array()));

function showVyhrazeno($id) {
  $ret = $GLOBALS['dostupnost_souboru'][$id];
  if (!$ret) $ret = 'Pro všechny';
  return $ret;
}

function SkartacniRezim($id) {
  $cj = LoadClass('EedCj', $id);
  $skar_rezim = $cj->getSkartacniRezim($id);
  if ($skar_rezim['znak']<>'') $ret = $skar_rezim['jid'] . '<br/>' . $skar_rezim['znak'] . '/' . $skar_rezim['doba'];
  return $ret;
}


$TABLE_CONFIG = array(
  "schema" => array( 
    array( field=>"LISTU", label=>"<font color=black>Listů</font>","width"=>"10%"),
    array( field=>"PRILOHY", label=>"<font color=black>Příloh</font>","width"=>"10%"),
    array( field=>"showVyhrazeno(VYHRAZENO)", label=>"<font color=black>dostupnost</font>","width"=>"10%"),
    array( field=>"DatumArchivaceSpis(ROK_PREDANI,DATUM_ARCHIVACE_ODHAD)", label=>"<font color=black>Rok začátku archivace</font>","width"=>"20%"),
    array( field=>"SkartacniRezim(DOKUMENT_ID)", label=>"<font color=black>Režim</font>","width"=>"20%"),
    array( field=>"UkazSpisovnu(SPISOVNA_ID,DATUM_PREDANI,PREVZAL_ID,REGISTRATURA)", label=>"<font color=black>Uloženo v registratuře/spisovně</font>","width"=>"40%"),
    array( field=>"UkazText(POZNAMKA,ID)", label=>"<font color=black>Pozn</font>","width"=>"20%","add"=> "NOWRAP"),
  )
);

$TABLE_CONFIG['syscolumns'] = array(
 'edit' => array ('theme'=>array('dropdown'=>true, 'column'=>true))
);



