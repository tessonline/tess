<?php 

if ($command == 'closeDIL') {
  $q = new DB_POSTA;
  $sql = 'select * from cis_posta_spisy where id=' . $ID;
  $q->query($sql);
  $q->Next_Record();
  $puvDIL = $q->Record;
  $sql = "select * from cis_posta_spisy where typovy_spis_id=$puvDIL[TYPOVY_SPIS_ID] and soucast=$puvDIL[SOUCAST] and dil=$puvDIL[DIL] and dalsi_spis_id=0";
  $q->query($sql);
  $q->Next_Record();
  $puvSPIS = $q->Record;

  UzavritSpis($puvSPIS['SPIS_ID']);

//  $sql = "update cis_posta_spisy set datum_uzavreni='".Date('Y-m-d')."' where id=" . $ID;
  $sql = "update cis_posta_spisy set datum_uzavreni='".Date('Y-m-d')."' where id=" . $puvSPIS['SPIS_ID'];
  $q->query($sql);


  $cj_obj = LoadClass('EedCj', $puvSPIS['SPIS_ID']);
  $cj_info = $cj_obj->GetCjInfo($puvSPIS['SPIS_ID']);

  $text = 'díl ' . $cj_info['CELY_NAZEV'] . ' byl uzavřen.';
  EedTransakce::ZapisLog($puvSPIS['SPIS_ID'], $text, 'SPIS');
  include_once(FileUp2('.admin/run2_.inc'));
  foreach($puvSPIS as $key => $val) $GLOBALS[$key] = $val;
  unset($GLOBALS['ID']);
  $GLOBALS['LAST_DATE'] = $GLOBALS['DATUM_OTEVRENI'] = Date('Y-m-d');
  $GLOBALS['LAST_TIME'] = Date('H:i:s');
  $GLOBALS['NOVY_SPIS'] = $GLOBALS['PUVODNI_SPIS'];
  $GLOBALS['DIL'] = $GLOBALS['DIL'] + 1;
  $GLOBALS['DALSI_SPIS_ID'] = -1;

  run_(
  		array(
  				'agenda' => 'POSTA_TYP_SPIS',
  				'outputtype' => 1

  		)
  	);
  	echo 'zalozeno';
	$text = 'původní díl ' . $cj_info['CELY_NAZEV'] . ' byl uzavřen a byl vytvořen nový díl.';
	EedTransakce::ZapisLog($puvSPIS['SPIS_ID'], $text, 'SPIS');
	echo '
<script language="JavaScript" type="text/javascript">
window.opener.document.location.reload();
window.close();
</script>
  ';
Die();
}


if ($command == 'smazatDIL') {
	$q = new DB_POSTA;
	$sql = 'select * from cis_posta_spisy where id=' . $ID;
	$q->query($sql);
	$q->Next_Record();
	$puvDIL = $q->Record;

	$puvDIL[DIL] = $puvDIL[DIL] - 1;
	$sql = "select * from cis_posta_spisy where typovy_spis_id=$puvDIL[TYPOVY_SPIS_ID] and soucast=$puvDIL[SOUCAST] and dil=$puvDIL[DIL] and dalsi_spis_id=-1";
echo $sql.'<br/>';
	$q->query($sql);
	$q->Next_Record();
	$puvSPIS = $q->Record;
	$sql = "update cis_posta_spisy set datum_uzavreni=NULL where id=" . $puvSPIS['ID'];
echo $sql.'<br/>';
	$q->query($sql);
	
	$sql = "delete from cis_posta_spisy where id=" . $ID;
echo $sql.'<br/>';
	$q->query($sql);

	$sql = "select * from cis_posta_spisy where typovy_spis_id=$puvDIL[TYPOVY_SPIS_ID] and soucast=$puvDIL[SOUCAST] and dil=$puvDIL[DIL] and dalsi_spis_id=0";
	$q->query($sql);
	$q->Next_Record();
	$puvSPIS = $q->Record;
	$sql = "update cis_posta_spisy set datum_uzavreni=NULL where id=" . $puvSPIS['ID'];
echo $sql.'<br/>';
	$q->query($sql);

	OtevritSpis($puvSPIS['SPIS_ID']);
	
	$cj_obj = LoadClass('EedCj', $puvSPIS['SPIS_ID']);
	$cj_info = $cj_obj->GetCjInfo($puvSPIS['SPIS_ID']);
	
	$text = 'původní díl byl smazán (byl prázdný) a původní díl ' . $cj_info['CELY_NAZEV'] . ' byl otevřen.';
	EedTransakce::ZapisLog($puvSPIS['SPIS_ID'], $text, 'SPIS');
	
	echo "uzavreno";

	echo '
<script language="JavaScript" type="text/javascript">
window.opener.document.location.reload();
window.close();
</script>
  ';
  Die();
}

if ($command == 'closeSOUCAST') {
  $cjObj = LoadClass('EedCj', 0);
  $soucast = $cjObj->GetSoucast($ID);

  $soucastID = $soucast['ID'];
  $dily = $cjObj->SeznamDiluvTypovemSpisuSoucasti($soucast['TYPOVY_SPIS_ID'], $soucast['SOUCAST']);

  foreach ($dily as $id => $dil ) {

  //uzavreme vsechny dily
    if ($dil['DATUM_UZAVRENI'] == '') {
      $q = new DB_POSTA;
      $ID = $dil['ID'];
      $sql = 'select * from cis_posta_spisy where id=' . $ID;
      $q->query($sql);
      $q->Next_Record();
      $puvDIL = $q->Record;
      $sql = "select * from cis_posta_spisy where typovy_spis_id=$puvDIL[TYPOVY_SPIS_ID] and soucast=$puvDIL[SOUCAST] and dil=$puvDIL[DIL] and dalsi_spis_id=0";
      $q->query($sql);
      $q->Next_Record();
      $puvSPIS = $q->Record;

      if ($puv['SPIS_ID']>0) UzavritSpis($puvSPIS['SPIS_ID']);

      $sql = "update cis_posta_spisy set datum_uzavreni='".Date('Y-m-d')."' where id=" . $ID;
      $q->query($sql);

    }
  }
  //a uzavreme souvast
  $sql = "update cis_posta_spisy set datum_uzavreni='".Date('Y-m-d')."' where id=" . $soucastID;
  $q->query($sql);


  $text = 'součást ' . $soucast['NAZEV_SPISU'] . ' byla uzavřena.';
  EedTransakce::ZapisLog($soucast['ID'], $text, 'SPIS');
  EedTransakce::ZapisLog($soucast['TYPOVY_SPIS_ID'], $text, 'SPIS');
  echo "Uzavreno";
	echo '
<script language="JavaScript" type="text/javascript">
window.opener.document.location.reload();
window.close();
</script>
  ';
Die();
}

if ($command == 'openSOUCAST') {
  $cjObj = LoadClass('EedCj', 0);
  $soucast = $cjObj->GetSoucast($ID);

  $soucastID = $soucast['ID'];

  //a otevreme souvast
  $sql = "update cis_posta_spisy set datum_uzavreni=NULL where id=" . $soucastID;
echo "soucast $sql <br/>";
  $q->query($sql);


  $text = 'součást ' . $soucast['NAZEV_SPISU'] . ' byla uzavřena.';
  EedTransakce::ZapisLog($soucast['ID'], $text, 'SPIS');
  EedTransakce::ZapisLog($soucast['TYPOVY_SPIS_ID'], $text, 'SPIS');


  //a otevreme posledni dil
  $dily = $cjObj->SeznamDiluvTypovemSpisuSoucasti($soucast['TYPOVY_SPIS_ID'], $soucast['SOUCAST']);
  $puvDIL = end($dily);
  print_r($dil);

  	$sql = "select * from cis_posta_spisy where typovy_spis_id=$puvDIL[TYPOVY_SPIS_ID] and soucast=$puvDIL[SOUCAST] and dil=$puvDIL[DIL] and dalsi_spis_id=-1";
echo $sql.'<br/>';
	$q->query($sql);
	$q->Next_Record();
	$poslDIL = $q->Record;

	$sql = "update cis_posta_spisy set datum_uzavreni=NULL where id=" . $poslDIL['ID'];
echo $sql.'<br/>';
	$q->query($sql);

	OtevritSpis($poslDIL['SPIS_ID']);

	$cj_obj = LoadClass('EedCj', $poslDIL['SPIS_ID']);
	$cj_info = $cj_obj->GetCjInfo($poslDIL['SPIS_ID']);

	$text = 'díl byl otevřen pro zápis.';
	EedTransakce::ZapisLog($poslDIL['SPIS_ID'], $text, 'SPIS');


	echo '
<script language="JavaScript" type="text/javascript">
window.opener.document.location.reload();
window.close();
</script>
  ';
Die();
}

if ($command == 'closeTYPSPIS') {
  $casti = EedTools::GetSoucastiTypovehoSpisu($doc_id);
  $uzavreno = true;
  while (list($idSoucast, $soucast) = each($casti)) {
    if ($soucast['DATUM_UZAVRENI'] == '') $uzavreno = false;
  }

  if (!$uzavreno) {
     require(FileUp2('html_footer.inc'));
     Die('Je nutne uzavřít všechny součásti');
  }

  $sql = "update cis_posta_spisy set datum_uzavreni='".Date('Y-m-d')."' where id=" . $typ_spis;
//echo $sql;
  $q->query($sql);

  $sql = "update posta set status=-8 where id=" . $doc_id;
//echo $sql;
  $q->query($sql);

	$text = 'typový spis byl uzavřen.';
	EedTransakce::ZapisLog($doc_id, $text, 'SPIS');

	echo '
<script language="JavaScript" type="text/javascript">
window.opener.document.location.reload();
window.close();
</script>
  ';
Die();
}

if ($command == 'openTYPSPIS') {

  $sql = "update cis_posta_spisy set datum_uzavreni=NULL where id=" . $typ_spis;
//echo $sql;
  $q->query($sql);

	$text = 'typový spis byl otevřen.';
	EedTransakce::ZapisLog($doc_id, $text, 'SPIS');

  $sql = "update posta set status=-7 where id=" . $doc_id;
//echo $sql;
  $q->query($sql);

	echo '
<script language="JavaScript" type="text/javascript">
window.opener.document.location.reload();
window.close();
</script>
  ';
Die();
}
